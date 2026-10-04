// SPDX-License-Identifier: GPL-2.0
/* Platform driver: LED ngoai tren Raspberry Pi, cau hinh bang Device Tree. */

#include <linux/device.h>
#include <linux/err.h>
#include <linux/gpio/consumer.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/version.h>
#include <linux/workqueue.h>

#define DEFAULT_PERIOD_MS 1000U
#define MIN_PERIOD_MS 100U
#define MAX_PERIOD_MS 10000U

enum led_mode {
	LED_OFF,
	LED_ON,
	LED_BLINK,
};

static const char * const mode_names[] = { "off", "on", "blink" };

struct pi_gpio_led {
	struct gpio_desc *gpio;
	struct delayed_work blink_work;
	struct mutex lock;
	enum led_mode mode;
	u32 period_ms;
	bool state;
	bool stopping;
};

static int parse_mode(const char *buf)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mode_names); i++)
		if (sysfs_streq(buf, mode_names[i]))
			return i;

	return -EINVAL;
}

/* Goi khi dang giu lock. period_ms la ca chu ky sang + tat. */
static unsigned long blink_delay(struct pi_gpio_led *led)
{
	u32 on_ms = led->period_ms / 2;
	u32 delay_ms = led->state ? on_ms : led->period_ms - on_ms;

	return msecs_to_jiffies(delay_ms);
}

static void blink_work_fn(struct work_struct *work)
{
	struct pi_gpio_led *led = container_of(to_delayed_work(work),
						     struct pi_gpio_led, blink_work);

	mutex_lock(&led->lock);
	if (!led->stopping && led->mode == LED_BLINK) {
		led->state = !led->state;
		gpiod_set_value_cansleep(led->gpio, led->state);
		schedule_delayed_work(&led->blink_work, blink_delay(led));
	}
	mutex_unlock(&led->lock);
}

static ssize_t mode_show(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct pi_gpio_led *led = dev_get_drvdata(dev);
	ssize_t ret;

	mutex_lock(&led->lock);
	ret = sysfs_emit(buf, "%s\n", mode_names[led->mode]);
	mutex_unlock(&led->lock);

	return ret;
}

static ssize_t mode_store(struct device *dev,
			  struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct pi_gpio_led *led = dev_get_drvdata(dev);
	int mode = parse_mode(buf);

	if (mode < 0)
		return mode;

	mutex_lock(&led->lock);
	if (led->stopping) {
		mutex_unlock(&led->lock);
		return -ENODEV;
	}

	led->mode = mode;
	led->state = mode != LED_OFF;
	gpiod_set_value_cansleep(led->gpio, led->state);
	if (mode == LED_BLINK)
		mod_delayed_work(system_wq, &led->blink_work, blink_delay(led));
	else
		cancel_delayed_work(&led->blink_work);
	mutex_unlock(&led->lock);

	dev_info(dev, "mode=%s\n", mode_names[mode]);
	return count;
}
static DEVICE_ATTR_RW(mode);

static ssize_t period_ms_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct pi_gpio_led *led = dev_get_drvdata(dev);
	ssize_t ret;

	mutex_lock(&led->lock);
	ret = sysfs_emit(buf, "%u\n", led->period_ms);
	mutex_unlock(&led->lock);

	return ret;
}

static ssize_t period_ms_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct pi_gpio_led *led = dev_get_drvdata(dev);
	u32 period;
	int ret;

	ret = kstrtou32(buf, 10, &period);
	if (ret)
		return ret;
	if (period < MIN_PERIOD_MS || period > MAX_PERIOD_MS)
		return -EINVAL;

	mutex_lock(&led->lock);
	if (led->stopping) {
		mutex_unlock(&led->lock);
		return -ENODEV;
	}
	led->period_ms = period;
	if (led->mode == LED_BLINK)
		mod_delayed_work(system_wq, &led->blink_work, blink_delay(led));
	mutex_unlock(&led->lock);

	dev_info(dev, "period_ms=%u\n", period);
	return count;
}
static DEVICE_ATTR_RW(period_ms);

static struct attribute *pi_gpio_led_attrs[] = {
	&dev_attr_mode.attr,
	&dev_attr_period_ms.attr,
	NULL,
};

static const struct attribute_group pi_gpio_led_group = {
	.attrs = pi_gpio_led_attrs,
};

static void stop_led(struct device *dev, struct pi_gpio_led *led)
{
	int ret;

	mutex_lock(&led->lock);
	led->stopping = true;
	led->mode = LED_OFF;
	mutex_unlock(&led->lock);

	/* Khong giu mutex khi cho work ket thuc: tranh deadlock khi rmmod. */
	cancel_delayed_work_sync(&led->blink_work);
	gpiod_set_value_cansleep(led->gpio, 0);
	led->state = false;
	ret = gpiod_direction_input(led->gpio);
	if (ret)
		dev_warn(dev, "cannot change GPIO to input: %d\n", ret);
}

static int pi_gpio_led_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct pi_gpio_led *led;
	const char *default_mode;
	int ret;

	led = devm_kzalloc(dev, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	mutex_init(&led->lock);
	INIT_DELAYED_WORK(&led->blink_work, blink_work_fn);
	led->mode = LED_ON;
	led->period_ms = DEFAULT_PERIOD_MS;

	if (!of_property_read_u32(dev->of_node, "blink-period-ms", &led->period_ms)) {
		if (led->period_ms < MIN_PERIOD_MS || led->period_ms > MAX_PERIOD_MS)
			return dev_err_probe(dev, -EINVAL,
					     "blink-period-ms must be 100..10000\n");
	}
	if (!of_property_read_string(dev->of_node, "default-mode", &default_mode)) {
		ret = parse_mode(default_mode);
		if (ret < 0)
			return dev_err_probe(dev, ret,
					     "default-mode must be off/on/blink\n");
		led->mode = ret;
	}

	/* "led" tuong ung voi thuoc tinh led-gpios trong Device Tree. */
	led->gpio = devm_gpiod_get(dev, "led", GPIOD_OUT_LOW);
	if (IS_ERR(led->gpio))
		return dev_err_probe(dev, PTR_ERR(led->gpio), "cannot request LED GPIO\n");

	platform_set_drvdata(pdev, led);
	led->state = led->mode != LED_OFF;
	gpiod_set_value_cansleep(led->gpio, led->state);

	ret = sysfs_create_group(&dev->kobj, &pi_gpio_led_group);
	if (ret) {
		stop_led(dev, led);
		return ret;
	}

	mutex_lock(&led->lock);
	if (led->mode == LED_BLINK)
		mod_delayed_work(system_wq, &led->blink_work, blink_delay(led));
	dev_info(dev, "probe OK: mode=%s period_ms=%u\n",
		 mode_names[led->mode], led->period_ms);
	mutex_unlock(&led->lock);

	return 0;
}

static void pi_gpio_led_remove_common(struct platform_device *pdev)
{
	struct pi_gpio_led *led = platform_get_drvdata(pdev);

	/* Dong sysfs truoc khi dung work va tra GPIO. */
	sysfs_remove_group(&pdev->dev.kobj, &pi_gpio_led_group);
	stop_led(&pdev->dev, led);
	dev_info(&pdev->dev, "remove: LED off, GPIO input; releasing resources\n");
	/* devm_gpiod_get/devm_kzalloc duoc kernel giai phong sau remove. */
}

/* platform_driver.remove doi tu int sang void tu kernel 6.11. */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0)
static void pi_gpio_led_remove(struct platform_device *pdev)
{
	pi_gpio_led_remove_common(pdev);
}
#else
static int pi_gpio_led_remove(struct platform_device *pdev)
{
	pi_gpio_led_remove_common(pdev);
	return 0;
}
#endif

static void pi_gpio_led_shutdown(struct platform_device *pdev)
{
	stop_led(&pdev->dev, platform_get_drvdata(pdev));
}

static const struct of_device_id pi_gpio_led_of_match[] = {
	{ .compatible = "student,pi-gpio-led" },
	{ }
};
MODULE_DEVICE_TABLE(of, pi_gpio_led_of_match);

static struct platform_driver pi_gpio_led_driver = {
	.probe = pi_gpio_led_probe,
	.remove = pi_gpio_led_remove,
	.shutdown = pi_gpio_led_shutdown,
	.driver = {
		.name = "pi_gpio_led",
		.of_match_table = pi_gpio_led_of_match,
	},
};
module_platform_driver(pi_gpio_led_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student example");
MODULE_DESCRIPTION("Device Tree GPIO LED platform driver with adjustable blinking");
