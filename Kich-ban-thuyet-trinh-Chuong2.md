# KỊCH BẢN THUYẾT TRÌNH — CHƯƠNG 2: EMBEDDED HARDWARE
### Trình bày toàn bộ 35 slide

> **Cách dùng:** Mỗi slide có sẵn đoạn văn nói tự nhiên — có thể học thuộc hoặc in ra cầm đọc.
> 👉 là gợi ý hành động (chỉ tay vào slide).
> 💡 là ghi chú riêng cho bạn (KHÔNG đọc lên), giúp trả lời khi thầy cô hỏi thêm.

---

## 🎤 MỞ ĐẦU

Kính chào thầy/cô và các bạn. Hôm nay em xin trình bày Chương 2 của môn Hệ thống nhúng, với chủ đề **"Embedded Hardware — Phần cứng Hệ thống nhúng."**

Nếu như ở Chương 1 chúng ta đã tìm hiểu hệ thống nhúng *là gì*, thì Chương 2 sẽ trả lời câu hỏi: *bên trong nó có những gì*. Bài trình bày của em gồm ba phần chính: thứ nhất là **kiến trúc phần cứng tổng quan**; thứ hai là **vi xử lý và vi điều khiển**; và thứ ba là **bộ nhớ**. Em xin bắt đầu.

---
---

# PHẦN 1 — KIẾN TRÚC PHẦN CỨNG TỔNG QUAN (Slide 1–3)

## SLIDE 1 — Trang bìa

Đây là trang bìa của chương. Chương 2 có tiêu đề **"Embedded Hardware"**, tức Phần cứng Hệ thống nhúng. Tài liệu do Phó Giáo sư, Tiến sĩ Trương Ngọc Sơn biên soạn, thuộc Khoa Điện – Điện tử, Trường Đại học Sư phạm Kỹ thuật Thành phố Hồ Chí Minh.

---

## SLIDE 2 — Embedded System Architecture

👉 *(Chỉ vào sơ đồ phân tầng)*

Slide này cho chúng ta cái nhìn tổng thể về kiến trúc một hệ thống nhúng. Các bạn có thể thấy hệ thống được chia thành **hai tầng lớn**: phía trên là **SW — phần mềm**, phía dưới đường kẻ đứt là **HW — phần cứng**.

Ở tầng phần mềm, từ trên xuống dưới lần lượt là: **Application** — ứng dụng, phần gần với người dùng nhất; **Middleware** — lớp trung gian; **Operating System** — hệ điều hành; và **Device Drivers** — trình điều khiển thiết bị.

Ở tầng phần cứng gồm ba khối: **SoC** — hệ thống trên một chip, **Memories** — các loại bộ nhớ, và **Peripherals** — thiết bị ngoại vi.

Điểm quan trọng ở đây là: **càng lên cao thì càng gần người dùng, càng xuống thấp thì càng gần phần cứng**. Và lớp **Device Drivers** đóng vai trò như một cây cầu nối — nó là lớp phần mềm cuối cùng, chịu trách nhiệm "nói chuyện" trực tiếp với phần cứng bên dưới.

💡 *Nếu bị hỏi "vì sao cần Device Drivers?" → vì phần mềm ứng dụng không thể trực tiếp điều khiển từng chân điện của chip; driver dịch lệnh cấp cao thành tín hiệu điện cụ thể.*

---

## SLIDE 3 — Architecture of Embedded Hardware

👉 *(Chỉ vào ba gạch đầu dòng, rồi vào sơ đồ)*

Slide này đi chi tiết hơn vào tầng phần cứng. Kiến trúc phần cứng của một hệ thống nhúng gồm **ba khối chính**: **Processor** — bộ xử lý; **Memory** — bộ nhớ; và **Input/Output** — các cổng vào ra.

👉 *(Chỉ vào sơ đồ khối)*

Sơ đồ bên dưới minh hoạ cách ba khối này kết nối trong thực tế. Ở trung tâm là **Processor**. Phía trên là **Memories**, trao đổi dữ liệu hai chiều với bộ xử lý. Bên phải là khối **Inputs/Outputs**. Bên trái là **User Interface** — giao diện người dùng, chẳng hạn màn hình và nút bấm. Phía dưới là **Power Supply** — khối nguồn.

Tất cả được đặt trong một **Enclosure** — vỏ máy, và giao tiếp ra ngoài qua các **Connectors** ở cạnh phải.

💡 *Liên hệ Chương 1: đây chính là bản chi tiết hoá của sơ đồ "Sensors → Microcomputer → Actuators".*

**🔄 Câu chuyển:** Sau khi đã có cái nhìn tổng quan, em xin đi sâu vào khối quan trọng nhất — bộ xử lý.

---
---

# PHẦN 2 — VI XỬ LÝ, VI ĐIỀU KHIỂN & RISC/CISC (Slide 4–16)

## SLIDE 4 — Từ Microprocessor đến Semiconductor

👉 *(Chỉ theo chuỗi mũi tên)*

Slide này cho thấy một con chip được tạo ra như thế nào, đi từ ngoài vào trong.

Bắt đầu từ bên trái là hình ảnh một **Microprocessor** hoàn chỉnh mà ta nhìn thấy bằng mắt thường. Đi sâu vào trong, nó là một **bản vẽ layout mạch** cực kỳ phức tạp. Phóng to hơn, ta thấy đó thực chất là các **cổng logic** cơ bản: AND, OR, NAND, NOR, NOT. Mỗi cổng logic lại được xây dựng từ các **transistor** theo công nghệ **CMOS**, với kích thước ngày càng nhỏ — từ 65 nanomet, xuống 20, rồi 17 nanomet. Và tận cùng, nền tảng của tất cả chính là **chất bán dẫn** silicon.

Ý chính: một con chip không tự nhiên mà có — nó bắt nguồn từ vật lý chất bán dẫn, qua thiết kế mạch logic, rồi mới thành sản phẩm.

💡 *"65nm, 20nm, 17nm" là kích thước transistor — càng nhỏ thì càng nhét được nhiều transistor trên 1 chip, nhanh hơn và tiết kiệm điện hơn.*

---

## SLIDE 5 — Microprocessor (CPU)

Slide này định nghĩa **Microprocessor**, hay còn gọi là **CPU**. Vi xử lý có hai nhiệm vụ cốt lõi: **đọc lệnh** — read instructions, và **xử lý dữ liệu nhị phân** — process binary data.

👉 *(Chỉ vào sơ đồ khối bên phải)*

Về cấu tạo, CPU chia thành ba phần: **ALU — Arithmetic/Logic Unit**, khối tính toán số học và logic, nơi thực hiện các phép cộng, trừ, so sánh. **Register Arrays** — các dãy thanh ghi, lưu tạm dữ liệu đang xử lý. Và **Control Unit** — khối điều khiển, điều phối hoạt động của toàn bộ CPU.

💡 *Ví von: ALU là "máy tính bỏ túi", Register là "giấy nháp", Control Unit là "người quản lý phân công việc".*

---

## SLIDE 6 — Kiến trúc Intel 8085

👉 *(Chỉ tổng thể vào sơ đồ, không đi chi tiết)*

Đây là sơ đồ kiến trúc chi tiết của vi xử lý **Intel 8085** — một vi xử lý thực tế.

Em không đi vào từng khối nhỏ, nhưng qua slide này ta thấy: một CPU trong thực tế **phức tạp hơn rất nhiều** so với sơ đồ ba khối đơn giản ở slide trước. Ở đây có thể nhận ra các thành phần quen thuộc như **ALU** ở giữa (khối màu đỏ), **Accumulator** và các **thanh ghi** B, C, D, E, H, L bên phải, **Instruction Decoder** — khối giải mã lệnh, khối **Timing and Control** ở dưới, và một **bus dữ liệu nội bộ 8 bit** chạy ngang slide.

Ý chính: các khối chức năng cơ bản vẫn là ALU, thanh ghi và điều khiển, nhưng được triển khai chi tiết cùng nhiều mạch hỗ trợ.

---

## SLIDE 7 — Microprocessor system

👉 *(Chỉ vào mũi tên System Bus màu xanh lá)*

Slide này cho thấy một điều quan trọng: **vi xử lý không thể hoạt động một mình**.

Bên trái là khối **Microprocessor**, gồm ALU, Registers và Control Unit. Nhưng để trở thành hệ thống hoàn chỉnh, nó cần được kết nối qua **System Bus** tới hai nhóm thành phần khác: phía trên là **I/O Devices** gồm thiết bị vào và ra; phía dưới là **Memory** gồm **RAM** và **ROM**.

Đây chính là **hệ thống dùng vi xử lý rời** — CPU một chip, RAM một chip, ROM một chip, nối với nhau trên bo mạch. Điều này sẽ tương phản với vi điều khiển ở slide tiếp theo.

---

## SLIDE 8 — Microcontroller (MCU)

Slide này định nghĩa **Microcontroller**, viết tắt **MCU** — vi điều khiển.

MCU là một thiết bị tính toán điện tử tích hợp, bao gồm **ba thành phần chính trên MỘT chip duy nhất**: **Microprocessor — MPU**; **Memory** — bộ nhớ; và **I/O ports** — các cổng vào ra.

👉 *(Chỉ vào bảng hình bên trái)*

Bảng bên trái minh hoạ các kiểu **vỏ chip** khác nhau: CPGA, SDIP, HDIP, PLCC, QFP, HSOP — mỗi loại có cách gắn và khả năng tản nhiệt khác nhau.

👉 *(Chỉ vào hình bên phải)*

Bên phải là các dòng vi điều khiển phổ biến hiện nay: **Atmel AVR, ATmega328P, PIC18F877A, 8051, Arduino, và ARM**.

💡 *Điểm nhấn quan trọng: So với slide 7 — vi xử lý cần lắp thêm RAM/ROM/IO rời, còn vi điều khiển đã có sẵn tất cả trong một chip, chỉ cần nạp code là chạy được.*

---

## SLIDE 9 — Bên trong một MCU thực tế (dòng PIC)

👉 *(Chỉ vào các mũi tên hội tụ vào con chip ở giữa)*

Slide này minh hoạ rất trực quan cho định nghĩa vừa rồi. Phía trên là các linh kiện **rời rạc**: bộ dao động Oscillator, bộ chuyển đổi A/D, bộ vi xử lý, RAM, và Program Memory.

Các mũi tên cho thấy tất cả những linh kiện rời này được **gộp lại và tích hợp vào bên trong một con chip duy nhất** — chính là con **Microcontroller** phía dưới.

Nhìn vào sơ đồ bên trong chip, ta thấy đầy đủ: **CPU** ở giữa, **Program Memory** và **RAM**, **EEPROM**, các bộ **Timers** T0-T3, khối truyền thông nối tiếp **SPI/I²C/USART**, bộ **A/D Converter**, khối **CCP/PWM**, các cổng **I/O Ports** từ Port A đến Port E, mạch **RESET** và khối nguồn 2 đến 5.5 volt.

Ý chính: **tất cả những gì cần thiết cho một hệ thống đều nằm gọn trong một con chip**.

---

## SLIDE 10 — MCU kết nối với thế giới thực

👉 *(Chỉ vào con chip μC ở giữa, rồi sang trái, sang phải)*

Slide này cho thấy vi điều khiển giao tiếp với thế giới bên ngoài như thế nào.

Ở giữa là con vi điều khiển, ký hiệu **μC**. Bên trái là các **thiết bị đầu vào**: cảm biến, nút nhấn, công tắc, biến trở, bàn phím. Bên phải là các **thiết bị đầu ra**: module thu phát vô tuyến, LED 7 đoạn, đèn báo, động cơ servo, động cơ bước, đồng hồ đo, màn hình LCD, và loa còi.

Phía dưới còn có kết nối hai chiều tới **bộ nhớ EEPROM ngoài** và **máy tính**.

💡 *Liên hệ Chương 1: đây chính là mô hình "Sensors → Microcomputer → Actuators" ở dạng chi tiết, với linh kiện cụ thể.*

---

## SLIDE 11 — Block Diagram tổng quát

Slide này đưa ra **sơ đồ khối tổng quát** của một vi điều khiển, ở dạng khái quát nhất.

👉 *(Chỉ vào sơ đồ)*

Phần trên gồm: **Microprocessor Unit — MPU** bên trái, kết nối qua đường **Bus** tới **Memory** và **I/O Ports** bên phải.

Phần dưới là nhóm **Support Devices** — thiết bị hỗ trợ, gồm: **Timers**, **A/D Converter**, **Serial I/O**, và **Other Devices**.

Đây là mô hình chuẩn mà mọi vi điều khiển đều tuân theo, dù của hãng nào — và ba slide tiếp theo sẽ chứng minh điều đó.

---

## SLIDE 12 — Block Diagram của 8051

Đây là sơ đồ khối của vi điều khiển **8051** — một dòng chip kinh điển.

Đối chiếu với mô hình chuẩn ở slide trước, ta thấy: **CPU** ở giữa bên trái; **On-chip ROM** chứa mã chương trình và **On-chip RAM** cho dữ liệu; khối **Timer/Counter** gồm Timer 0 và Timer 1; **4 cổng I/O** là P0, P1, P2, P3 phía dưới; **Serial Port** với hai chân TxD và RxD; cùng khối **Interrupt Control** xử lý ngắt ngoài và khối **OSC** — mạch dao động tạo xung nhịp.

---

## SLIDE 13 — Block Diagram của PIC12F617

Đây là ví dụ thứ hai — vi điều khiển **PIC12F617** của hãng Microchip.

Ta thấy: **CPU** ở giữa, sử dụng lệnh 14-bit với tổng cộng 35 lệnh; **Program Memory** lên tới 3.5 KB bên trái; **SRAM** 128 byte bên phải; **Internal Oscillator** 8 MHz; khối **8-Level Stack & Program Counter**.

Phía dưới là các khối ngoại vi: **Internal Voltage Reference**, **BOR và WDT** — mạch giám sát điện áp và watchdog timer, **ADC 10-bit 4 kênh**, **Comparator**, khối **Capture/Compare/PWM**, và các bộ **Timer**.

---

## SLIDE 14 — Block Diagram của AVR

Và đây là ví dụ thứ ba — kiến trúc **AVR**.

Sơ đồ này chi tiết hơn hai slide trước, nhưng ta vẫn nhận ra các thành phần quen thuộc: **AVR CPU** ở giữa với **ALU**, **Program Counter**, **Instruction Register**, **Instruction Decoder**, và **General Purpose Registers**; **Program Flash** và **SRAM**; **EEPROM**; các cổng **PORTA đến PORTD**; khối **ADC**; **Timers/Counters**; **Watchdog Timer**; và các giao tiếp **SPI**, **USART**, **TWI** — tức I²C.

💡 *Nếu thiếu thời gian, nói gộp 3 slide 12-13-14: "Đây là ba ví dụ vi điều khiển thực tế từ ba hãng khác nhau — 8051, PIC và AVR. Tuy khác nhà sản xuất và khác mức độ chi tiết, nhưng cả ba đều tuân theo cùng một mô hình khối ở slide 11: đều có CPU, bộ nhớ chương trình, bộ nhớ dữ liệu, cổng I/O, timer và các khối ngoại vi hỗ trợ."*

---

## SLIDE 15 — RISC

Hai slide tiếp theo nói về hai kiến trúc tập lệnh đối lập nhau, bắt đầu với **RISC**.

**RISC** là viết tắt của **Reduced Instruction Set Computer** — máy tính với tập lệnh rút gọn. Đây là một **chiến lược thiết kế CPU** dựa trên các lệnh đơn giản để đạt hiệu năng cao.

Đặc điểm của RISC gồm: thứ nhất, **tập lệnh nhỏ và đơn giản**; thứ hai, mỗi lệnh chỉ thực thi trong **một chu kỳ xung nhịp**; và thứ ba, hỗ trợ **Pipelining** — kỹ thuật cho phép thực thi **đồng thời nhiều giai đoạn** của các lệnh khác nhau, giúp xử lý lệnh hiệu quả hơn.

💡 *Giải thích Pipelining nếu bị hỏi: giống dây chuyền giặt đồ — trong khi mẻ 1 đang sấy thì mẻ 2 đã bắt đầu giặt, không cần chờ mẻ 1 xong hoàn toàn. Ví dụ thực tế của RISC là kiến trúc ARM — dùng trong hầu hết điện thoại thông minh.*

---

## SLIDE 16 — CISC

Slide này nói về kiến trúc đối lập: **CISC** — **Complex Instruction Set Computer**, máy tính với tập lệnh phức tạp.

Đặc điểm của CISC: chương trình viết ra **ngắn hơn**, vì CISC có **số lượng lớn các lệnh phức tạp**, mỗi lệnh làm được nhiều việc — nhưng đổi lại, mỗi lệnh **mất nhiều thời gian hơn để thực thi**. CISC đạt hiệu năng tốt dựa trên việc **đơn giản hoá trình biên dịch**.

Và điểm mấu chốt phân biệt hai kiến trúc nằm ở hai câu cuối: **cách tiếp cận của CISC là giảm thiểu SỐ LỆNH trên mỗi chương trình**; trong khi **RISC làm điều ngược lại — giảm SỐ CHU KỲ trên mỗi lệnh, đánh đổi bằng việc chương trình phải dùng nhiều lệnh hơn**.

💡 *Cách nhớ nhanh: CISC = ít lệnh nhưng mỗi lệnh nặng. RISC = nhiều lệnh nhưng mỗi lệnh nhẹ và nhanh.*

**🔄 Câu chuyển:** Như vậy em đã trình bày xong phần về bộ xử lý. Tiếp theo, em xin sang phần cuối cùng — nơi lưu trữ chương trình và dữ liệu, đó là bộ nhớ.

---
---

# PHẦN 3 — MEMORY (Slide 17–35)

## SLIDE 17 — Tổng quan các loại bộ nhớ

👉 *(Chỉ vào cây phân nhánh)*

Slide này đưa ra bức tranh tổng thể về các loại bộ nhớ dùng trong hệ thống nhúng. Từ gốc **Memory**, ta chia thành **ba nhánh chính**.

Nhánh thứ nhất là **RAM**, gồm **DRAM** và **SRAM**. Nhánh thứ hai là **ROM**, gồm **EPROM**, **PROM** và **Masked ROM**. Và ở giữa là nhánh **Hybrid** — bộ nhớ lai, gồm **NVRAM**, **Flash** và **EEPROM**.

Sở dĩ có nhóm "lai" ở giữa là vì các loại bộ nhớ này mang đặc điểm của cả hai bên: **vừa ghi/xoá được như RAM, lại vừa giữ được dữ liệu khi mất điện như ROM**.

Trong các slide tiếp theo, em sẽ đi lần lượt từ nhánh ROM, sang RAM, rồi tới bộ nhớ lai.

---

## SLIDE 18 — ROM

**ROM** là viết tắt của **Read Only Memory** — bộ nhớ chỉ đọc.

Các đặc điểm chính: thứ nhất, đây là loại bộ nhớ mà ta **chỉ có thể đọc, không thể ghi vào**. Thứ hai, ROM là bộ nhớ **non-volatile** — **không mất dữ liệu khi mất điện**. Thứ ba, thông tin được lưu **vĩnh viễn ngay từ lúc sản xuất**.

Và công dụng quan trọng nhất: ROM lưu trữ các **lệnh cần thiết để khởi động máy tính** — thao tác này được gọi là **bootstrap**.

💡 *"Non-volatile" là từ khoá quan trọng, đối lập với RAM (volatile — mất dữ liệu khi ngắt điện).*

---

## SLIDE 19 — PROM

**PROM** — **Programmable Read Only Memory**, tức ROM lập trình được.

Khác với ROM thường được ghi sẵn tại nhà máy, **PROM cho phép người dùng tự ghi dữ liệu vào — nhưng chỉ MỘT lần duy nhất**. Người dùng mua một con PROM trắng, rồi dùng một **máy nạp chuyên dụng** để ghi nội dung mong muốn.

Về nguyên lý: bên trong chip PROM có các **cầu chì nhỏ**, và trong quá trình lập trình, các cầu chì này sẽ bị **đốt đứt**. Vì cầu chì đã đứt thì không nối lại được, nên PROM **chỉ lập trình được một lần và không thể xoá**.

---

## SLIDE 20 — EPROM

**EPROM** — **Erasable and Programmable Read Only Memory**, ROM có thể **xoá và lập trình lại được**.

Đây là bước tiến so với PROM. EPROM có thể được xoá bằng cách **chiếu tia cực tím — tia UV** vào chip, trong khoảng thời gian lên tới **40 phút**.

Về nguyên lý: trong quá trình lập trình, một **điện tích được giữ lại trong vùng cổng cách điện**. Vì điện tích này **không có đường rò rỉ**, nên dữ liệu có thể được lưu giữ trong **hơn 10 năm**.

💡 *Chip EPROM có một "cửa sổ" bằng thạch anh trong suốt ở mặt trên (thấy trong hình slide) — chính là nơi để chiếu tia UV vào.*

---

## SLIDE 21 — EEPROM

**EEPROM** — **Electrically Erasable and Programmable Read Only Memory** — thêm chữ E, nghĩa là xoá bằng **điện**.

Đây là bước tiến tiếp theo, khắc phục nhược điểm của EPROM. EEPROM được **lập trình và xoá hoàn toàn bằng điện**, không cần đèn UV, không cần tháo chip ra khỏi mạch.

Về thông số: EEPROM có thể xoá và ghi lại khoảng **mười nghìn lần**; mỗi thao tác xoá hoặc ghi mất khoảng **4 đến 10 mili-giây**.

Ưu điểm lớn nhất: trong EEPROM, **bất kỳ vị trí nào cũng có thể được xoá và ghi một cách riêng lẻ** — khác với EPROM phải xoá toàn bộ chip cùng lúc.

💡 *Mạch nói xuyên suốt 4 slide 18-21: ROM → PROM → EPROM → EEPROM là một chuỗi tiến hoá, mỗi bước giải quyết một hạn chế của bước trước: không ghi được → ghi 1 lần → xoá lại được (bằng UV, chậm) → xoá bằng điện, nhanh, từng ô riêng lẻ.*

---

## SLIDE 22 — RAM tổng quan

Chuyển sang nhánh thứ hai: **RAM — Random Access Memory**, bộ nhớ truy cập ngẫu nhiên.

RAM được chia thành hai loại chính: **Static RAM**, viết tắt **SRAM**, và **Dynamic RAM**, viết tắt **DRAM**. Hai slide tiếp theo sẽ so sánh đặc điểm của từng loại.

---

## SLIDE 23 — Đặc điểm của SRAM

Slide này liệt kê các đặc điểm của **SRAM — RAM tĩnh**.

Về ưu điểm: **tuổi thọ dữ liệu dài**; **không cần refresh** — không cần làm tươi lại dữ liệu liên tục; **tốc độ nhanh hơn**; và chính vì nhanh nên SRAM thường được **dùng làm bộ nhớ cache**.

Về nhược điểm: **kích thước lớn**, **giá thành đắt**, và **tiêu thụ điện năng cao**.

👉 *(Chỉ vào sơ đồ mạch bên phải)*

Sơ đồ bên phải cho thấy một ô nhớ SRAM cần tới **6 transistor** — đó chính là lý do vì sao SRAM chiếm nhiều diện tích và đắt tiền.

---

## SLIDE 24 — Đặc điểm của DRAM

Ngược lại là **DRAM — RAM động**, với các đặc điểm gần như đối lập hoàn toàn.

Về nhược điểm: **tuổi thọ dữ liệu ngắn**; **cần được refresh liên tục**; và **chậm hơn so với SRAM**.

Về ưu điểm: **kích thước nhỏ gọn hơn**, **giá rẻ hơn**, và **tiêu thụ ít điện năng hơn**. Chính vì vậy, DRAM được **dùng làm RAM chính** của hệ thống.

👉 *(Chỉ vào sơ đồ bên dưới)*

Sơ đồ bên dưới cho thấy ô nhớ DRAM chỉ cần **1 transistor và 1 tụ điện** — đơn giản hơn nhiều so với 6 transistor của SRAM. Bit 1 được lưu bằng tụ điện tích điện, bit 0 là tụ không tích điện. Và vì tụ điện bị **rò rỉ điện tích theo thời gian**, nên DRAM mới cần được refresh liên tục.

💡 *Cách nhớ: SRAM nhanh-đắt-to → làm cache. DRAM chậm-rẻ-nhỏ → làm RAM chính. Đây là sự đánh đổi kinh điển giữa hiệu năng và chi phí.*

---

## SLIDE 25 — SDRAM và DDR-SDRAM

Slide này giới thiệu hai cải tiến quan trọng của DRAM.

Thứ nhất là **SDRAM — Synchronous DRAM**, tức DRAM **đồng bộ**. SDRAM được thiết kế để **đồng bộ hoạt động của DRAM với phần còn lại của hệ thống máy tính**, thay vì phải định nghĩa nhiều chế độ hoạt động dựa trên trình tự các tín hiệu điều khiển như CE, RAS, CAS và WE.

Thứ hai là **DDR-SDRAM — Double Data Rate SDRAM**. DDR tăng hiệu năng truyền dữ liệu bằng ba cách: **tăng tốc độ xung nhịp**, **truyền dữ liệu theo cụm — bursting**, và quan trọng nhất là **truyền được HAI bit dữ liệu trong MỘT chu kỳ xung nhịp** — đó chính là ý nghĩa của cái tên "Double Data Rate".

Các thế hệ tiếp theo gồm: **DDR2, DDR3, DDR4**, **LPDDR** — phiên bản tiết kiệm điện cho thiết bị di động, và **GDDR2 đến GDDR5** — phiên bản dành riêng cho card đồ hoạ.

👉 *(Chỉ vào bảng nhỏ bên phải)*

Bảng nhỏ minh hoạ mối quan hệ: DDR-266 có tốc độ dữ liệu 266 Mb/s trên mỗi chân, ứng với xung nhịp bộ nhớ 133 MHz — đúng bằng **hai lần** xung nhịp.

---

## SLIDE 26 — Flash memory

Chuyển sang nhánh thứ ba: **bộ nhớ lai**, đại diện tiêu biểu là **Flash memory**.

Flash thực chất là **EEPROM được sắp xếp theo cách đặc biệt**, giúp nó **chiếm ít diện tích hơn** so với EEPROM hay DRAM tổ chức theo cấu trúc khác.

Flash có hai loại chính: **NOR flash** và **NAND flash** — hai slide tiếp theo sẽ so sánh chúng.

---

## SLIDE 27 — NAND Flash

Slide này so sánh hai loại flash: **NAND và NOR** — hai loại có **đặc tính vật lý khá khác biệt**.

**NAND flash là công nghệ mới hơn NOR**, với hai điểm khác biệt chính:

Thứ nhất, **NAND lưu trữ được lượng dữ liệu gấp khoảng BỐN lần so với NOR flash ở cùng mức giá**.

Thứ hai, **NAND có tốc độ xoá và ghi nhanh hơn nhiều**, nên đây là lựa chọn ưu việt cho các ứng dụng **cần lưu trữ dữ liệu thường xuyên**.

💡 *Ứng dụng thực tế: NAND dùng trong USB, thẻ nhớ SD, ổ SSD. NOR thường dùng lưu firmware vì cho phép đọc ngẫu nhiên từng byte nhanh hơn.*

---

## SLIDE 28 — So sánh cấu trúc NAND vs NOR

👉 *(Chỉ vào bảng so sánh, đặc biệt dòng cuối)*

Slide này giải thích **lý do vật lý** đằng sau sự khác biệt vừa nói.

Bảng so sánh gồm bốn hàng: **Cell Array** — cách sắp xếp mảng ô nhớ; **Layout** — bố trí vật lý; **Cross Section** — mặt cắt ngang; và quan trọng nhất là **Cell Size** — kích thước ô nhớ.

Nhìn vào hàng cuối: **ô nhớ NAND chỉ chiếm 4F², trong khi NOR chiếm tới 10F²** — tức là ô nhớ NAND **nhỏ hơn khoảng 2.5 lần**.

Đây chính là lý do vì sao NAND lưu được nhiều dữ liệu hơn trên cùng một diện tích chip, và do đó rẻ hơn tính trên mỗi gigabyte.

---

## SLIDE 29 — Địa chỉ ảo và địa chỉ vật lý

Chuyển sang nội dung tiếp theo: **cấp phát và ánh xạ bộ nhớ**.

Slide này giới thiệu một khái niệm quan trọng: có **hai loại địa chỉ** trong hệ thống.

Thứ nhất, các địa chỉ bộ nhớ do **CPU tạo ra** được gọi là **địa chỉ ảo — virtual address**. Thứ hai, địa chỉ mà **bộ nhớ chính thực sự sử dụng** được gọi là **địa chỉ vật lý — physical address**.

Giữa CPU và bộ nhớ chính có một phần cứng trung gian gọi là **MMU — Memory Management Unit**. **Nhiệm vụ của MMU là dịch địa chỉ ảo thành địa chỉ vật lý**.

👉 *(Chỉ vào sơ đồ)*

Sơ đồ minh hoạ: CPU gửi địa chỉ ảo tới MMU, MMU tra cứu trong bảng **Page Map** rồi xuất ra địa chỉ vật lý tới DRAM. Và lưu ý dòng chữ đỏ bên trái: **không phải mọi địa chỉ ảo đều có bản dịch** — trường hợp này sẽ được xử lý ở slide tiếp theo.

💡 *Vì sao cần địa chỉ ảo? Để mỗi chương trình "tưởng" mình có toàn bộ bộ nhớ riêng, giúp bảo vệ chương trình này không ghi đè lên chương trình khác, và cho phép dùng bộ nhớ nhiều hơn RAM thật.*

---

## SLIDE 30 — Page Map

Slide này giải thích **cách MMU thực hiện việc dịch địa chỉ**.

MMU dịch địa chỉ ảo sang địa chỉ vật lý bằng một **phép tra bảng đơn giản**. Bảng này được gọi là **page map** hoặc **page table** — bảng trang.

Về nguyên lý: bộ nhớ vật lý được **chia thành các khối có kích thước cố định, gọi là các trang — pages**. Kích thước trang điển hình là **4KB đến 16KB**. Một địa chỉ ảo gồm hai phần: **số hiệu trang ảo** cộng với **các bit offset** — độ lệch trong trang. Tương tự, địa chỉ vật lý gồm **số hiệu trang vật lý** cộng **offset**.

MMU sẽ **ánh xạ trang ảo sang trang vật lý** thông qua page map. Và nếu trang ảo cần dùng **không có sẵn trong bộ nhớ vật lý**, hệ thống sẽ phát sinh một lỗi gọi là **page fault**.

👉 *(Chỉ vào dòng chữ trong khung xanh)*

Cuối cùng, kỹ thuật **dùng bộ nhớ chính như một bộ đệm cho các trang** được gọi là **paging** hoặc **demand paging**.

---

## SLIDE 31 — Ví dụ thiết kế bộ nhớ thực tế (board RK3399)

Chuyển sang nội dung cuối: **các ví dụ thiết kế bộ nhớ thực tế**.

👉 *(Chỉ vào chip lớn ở giữa)*

Đây là sơ đồ thiết kế của một bo mạch thương mại thật, sử dụng chip **RK3399** ở trung tâm.

Về phần bộ nhớ, chú ý phía dưới: có **hai chip LPDDR3, mỗi chip 2GB** — đây là RAM chính, kết nối qua hai kênh DRAM0 và DRAM1. Bên cạnh là **eMMC 5.1 dung lượng 16GB**, được đánh dấu **"Bootable"** — bộ nhớ lưu trữ có thể khởi động từ đó. Ngoài ra còn có khe **SDCARD** cũng có khả năng khởi động.

Xung quanh là các thành phần khác: màn hình LCD, module WiFi, khối quản lý nguồn PMIC, cổng USB 3.0, HDMI, và bo mạch âm thanh riêng bên phải.

Ý chính: đây là **ví dụ minh hoạ cách bộ nhớ được bố trí trong một sản phẩm thật**, chứ không chỉ là lý thuyết.

---

## SLIDE 32 — Giao tiếp bộ nhớ ngoài với 8051

Slide này minh hoạ cách **kết nối RAM và ROM ngoài với vi điều khiển 8051**, mỗi loại dung lượng 64K.

👉 *(Chỉ vào khối Latch)*

Điểm đáng chú ý nhất là khối **Latch** — mạch chốt. Lý do cần nó: cổng **P0** của 8051 phải **dùng chung cho cả địa chỉ và dữ liệu** — ký hiệu AD0 đến AD7. Nghĩa là cùng 8 chân đó, lúc thì mang địa chỉ, lúc lại mang dữ liệu.

Vì vậy cần một mạch chốt để **giữ lại phần địa chỉ** trong khi các chân đó chuyển sang truyền dữ liệu. Tín hiệu điều khiển việc chốt này là **ALE — Address Latch Enable**.

Các tín hiệu còn lại: **P2** cung cấp địa chỉ cao A8-A15; **WR và RD** điều khiển ghi và đọc RAM; và **PSEN** dùng riêng để đọc ROM chương trình.

---

## SLIDE 33 — Memory map của vi điều khiển

Slide này trình bày **bản đồ bộ nhớ** của một vi điều khiển, chia làm hai vùng riêng biệt.

👉 *(Chỉ vào cột bên trái)*

Bên trái là **Program Memory** — bộ nhớ chương trình, trải từ địa chỉ **$0000 đến $FFFF**. Vùng này chia thành **Application Flash Section** — chứa chương trình ứng dụng của chúng ta, và **Boot Flash Section** ở cuối — chứa chương trình khởi động.

👉 *(Chỉ vào cột bên phải)*

Bên phải là **Data Memory** — bộ nhớ dữ liệu, gồm nhiều vùng có địa chỉ cụ thể: **32 thanh ghi** từ $0000 đến $001F; **64 thanh ghi I/O** từ $0020 đến $005F; **160 thanh ghi I/O mở rộng** từ $0060 đến $00FF; tiếp theo là **SRAM nội** kích thước 4096 x 8 bit, từ $0100 đến $10FF; và cuối cùng là vùng dành cho **SRAM ngoài** từ $1100 trở đi.

Ý chính: mỗi vùng nhớ đều có **địa chỉ bắt đầu và kết thúc xác định**, và người lập trình cần biết bản đồ này để truy cập đúng vùng.

---

## SLIDE 34 — Thiết kế bộ nhớ ngoài cho AVR

Slide này tương tự slide 32, nhưng áp dụng cho vi điều khiển **AVR** kết nối với **SRAM ngoài**.

Nguyên lý hoạt động giống hệt: chân **AD7:0** của AVR dùng chung cho địa chỉ và dữ liệu, nên cần một mạch chốt ở giữa — với đầu vào D, đầu ra Q, và chân điều khiển G nối tới tín hiệu **ALE**.

Sau khi qua mạch chốt, tín hiệu tách thành **D[7:0]** — dữ liệu, và **A[7:0]** — địa chỉ thấp, đưa vào SRAM. Địa chỉ cao **A15:8** được đưa thẳng sang. Cuối cùng, hai tín hiệu **RD và WR** điều khiển việc đọc và ghi.

---

## SLIDE 35 — Giản đồ thời gian

Slide cuối cùng là **giản đồ thời gian** cho chu kỳ truy cập bộ nhớ dữ liệu ngoài.

👉 *(Chỉ theo trục thời gian T1 → T4)*

Trục ngang là thời gian, chia thành bốn chu kỳ **T1, T2, T3, T4** theo xung nhịp hệ thống **CLK_CPU** ở hàng trên cùng.

Các hàng bên dưới thể hiện trạng thái của từng tín hiệu tại mỗi thời điểm: tín hiệu **ALE** lên mức cao ở chu kỳ T2 để chốt địa chỉ; **A15:8** giữ địa chỉ cao; **DA7:0** chuyển từ địa chỉ sang dữ liệu; sau đó tín hiệu **WR** xuống mức thấp cho chu kỳ **ghi**, hoặc **RD** xuống mức thấp cho chu kỳ **đọc**.

Ý nghĩa: khi giao tiếp với bộ nhớ ngoài, các tín hiệu **không thể xuất hiện tuỳ tiện**, mà phải **tuân thủ đúng trình tự và đúng thời điểm**. Nếu sai một nhịp, dữ liệu đọc/ghi sẽ bị lỗi.

💡 *Liên hệ Chương 1: đây chính là minh hoạ cụ thể cho khái niệm "ràng buộc thời gian thực" — kết quả phải đúng cả về giá trị lẫn thời điểm.*

---
---

## 🎤 KẾT LUẬN

Như vậy, em đã trình bày xong toàn bộ Chương 2 — Embedded Hardware.

Tóm tắt lại: chúng ta đã đi qua **kiến trúc phần cứng tổng quan** với ba khối Processor, Memory và Input/Output; tiếp theo là **bộ xử lý**, với sự phân biệt giữa vi xử lý và vi điều khiển, cùng hai kiến trúc tập lệnh RISC và CISC; và cuối cùng là **bộ nhớ**, từ họ ROM, họ RAM, bộ nhớ Flash, cho tới cách quản lý bộ nhớ và các ví dụ thiết kế thực tế.

Đây là nền tảng phần cứng cần thiết trước khi chúng ta bước vào các chương tiếp theo.

Bài trình bày của em đến đây là kết thúc. Em xin cảm ơn thầy/cô và các bạn đã lắng nghe, và rất mong nhận được câu hỏi cùng góp ý ạ.

---
---

## ⏱️ GỢI Ý THỜI LƯỢNG

| Nội dung | Slide | Thời lượng |
|---|---|---|
| Mở đầu | — | ~30 giây |
| Phần 1 — Kiến trúc tổng quan | 1–3 | ~2 phút |
| Phần 2 — Vi xử lý & Vi điều khiển | 4–16 | ~8 phút |
| Phần 3 — Bộ nhớ | 17–35 | ~10 phút |
| Kết luận | — | ~30 giây |
| **TỔNG** | **35 slide** | **~21 phút** |

**Nếu chỉ có 10–12 phút, cắt gọn như sau:**
- Slide 6: nói 1 câu rồi lướt qua (chỉ cần nói "đây là ví dụ CPU thực tế, phức tạp hơn sơ đồ lý thuyết").
- Slide 12, 13, 14: gộp thành một lần nói (dùng câu gợi ý ở ghi chú slide 14).
- Slide 18–21: nói theo mạch tiến hoá liền một hơi, không tách 4 slide riêng.
- Slide 32 và 34: nói gộp vì nguyên lý giống hệt nhau, chỉ khác dòng chip.
- Slide 28, 31, 35: mỗi slide chỉ nói 1–2 câu ý chính.
