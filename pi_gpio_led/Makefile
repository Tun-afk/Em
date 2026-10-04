ifneq ($(KERNELRELEASE),)
obj-m := pi_gpio_led.o
else
KDIR ?= /lib/modules/$(shell uname -r)/build
DTC ?= dtc
.DEFAULT_GOAL := all

.PHONY: all module overlay clean
all: module overlay

module:
	@test -f "$(KDIR)/Makefile" || { \
		printf '%s\n' "Thieu headers cho kernel dang chay: $(KDIR)" \
		"Cai headers dung phien ban tren Pi, reboot neu kernel vua cap nhat." >&2; \
		exit 1; }
	$(MAKE) -C "$(KDIR)" M="$(CURDIR)" modules

overlay: pi-gpio-led.dtbo

pi-gpio-led.dtbo: pi-gpio-led-overlay.dts
	$(DTC) -@ -I dts -O dtb -o $@ $<

clean:
	@if [ -f "$(KDIR)/Makefile" ]; then \
		$(MAKE) -C "$(KDIR)" M="$(CURDIR)" clean; \
	fi
	$(RM) pi-gpio-led.dtbo
endif
