# GIẢI THÍCH SÂU TỪNG SLIDE — CHƯƠNG 2: EMBEDDED HARDWARE
### Bản đầy đủ: kiến thức nền + đoạn văn nói sẵn cho từng slide

> **Cấu trúc mỗi slide:**
> - 📖 **Kiến thức nền** — giải thích sâu để bạn HIỂU, không chỉ đọc
> - ❓ **Câu hỏi thầy cô hay hỏi** — kèm câu trả lời
> - 🎤 **Đoạn văn nói** — đọc/học thuộc khi thuyết trình

---
---

# PHẦN 1 — KIẾN TRÚC PHẦN CỨNG TỔNG QUAN (Slide 1–3)

## SLIDE 1 — Trang bìa

### 🎤 Đoạn văn nói
Đây là trang bìa của chương. Chương 2 có tiêu đề **"Embedded Hardware"**, tức Phần cứng Hệ thống nhúng. Tài liệu do Phó Giáo sư, Tiến sĩ Trương Ngọc Sơn biên soạn, thuộc Khoa Điện – Điện tử, Trường Đại học Sư phạm Kỹ thuật Thành phố Hồ Chí Minh.

---

## SLIDE 2 — Embedded System Architecture

### 📖 Kiến thức nền

**Tầng SOFTWARE — 4 lớp từ trên xuống:**

**1️⃣ Application (Ứng dụng)** — chứa **logic nghiệp vụ của sản phẩm**, tức cái mà người dùng thực sự mua thiết bị về để dùng. Ví dụ máy lạnh thông minh: Application là đoạn code *"Nếu nhiệt độ > 26°C thì bật máy nén"*. Lớp này **không hề biết** cảm biến nối chân số mấy hay phải ghi giá trị gì vào thanh ghi nào. Gọi là "gần người dùng nhất" vì mọi lớp bên dưới đều tồn tại để **phục vụ** cho lớp này chạy được.

**2️⃣ Middleware (Lớp trung gian)** — nằm **giữa Application (trên) và Operating System (dưới)**. Tồn tại vì có những chức năng **quá phức tạp để viết lại mỗi lần**, nhưng cũng **không thuộc về hệ điều hành**. Ví dụ:

| Middleware | Nhiệm vụ |
|---|---|
| TCP/IP stack | Xử lý giao thức mạng — Application chỉ cần gọi `send(data)` |
| MQTT / HTTP client | Giao thức IoT gửi dữ liệu lên server |
| File system (FAT32) | Ghi file lên thẻ SD, không cần tự quản lý từng sector |
| Thư viện GUI | Vẽ nút bấm, menu lên màn hình LCD |
| USB stack | Xử lý giao thức USB phức tạp |
| TLS/AES | Mã hoá bảo mật dữ liệu |

*Ví von:* Middleware giống **nhà thầu phụ chuyên môn** — chủ nhà (Application) muốn nước sạch, không tự đào giếng mà thuê nhà thầu xử lý nước.

**3️⃣ Operating System** — quản lý và phân chia **tài nguyên**: quản lý CPU (quyết định tác vụ nào chạy lúc nào), quản lý bộ nhớ (cấp phát/thu hồi RAM), điều phối tranh chấp (2 tác vụ cùng muốn dùng UART thì ai được trước). **Không phải hệ thống nhúng nào cũng có OS** — liên hệ phân loại Chương 1: Small scale → không OS (**bare-metal**); Medium → **RTOS**; Sophisticated → **Linux**.

**4️⃣ Device Drivers** — lớp phần mềm **DUY NHẤT biết chi tiết phần cứng**: biết chân nào, địa chỉ thanh ghi nào, ghi giá trị gì. Minh hoạ sự "dịch thuật":

```
Application nói:    "Gửi ký tự 'A' ra cổng nối tiếp"
        ↓
Driver dịch thành:  UART0->DR = 0x41;
```

**Ý nghĩa cốt lõi của việc phân tầng:** nếu đổi từ chip STM32 sang ESP32, **chỉ cần viết lại lớp Driver**, lớp Application giữ nguyên → tiết kiệm rất nhiều công sức.

**Vì sao sơ đồ có dạng BẬC THANG và mũi tên HAI CHIỀU?**
- **Mũi tên dài từ Application xuống thẳng Device Drivers:** Application **có thể bỏ qua** Middleware và OS → đây là hệ thống **bare-metal**.
- **Mũi tên hai chiều:** dữ liệu đi cả hai hướng — Application gửi lệnh xuống, phần cứng gửi dữ liệu/ngắt lên.
- **Dạng bậc thang:** các lớp **không bắt buộc xếp chồng cứng nhắc** — tuỳ hệ thống mà lớp nào có, lớp nào không.

**Tầng HARDWARE — 3 khối:**

| Khối | Giải thích |
|---|---|
| **SoC** (System on Chip) | Chip chính tích hợp CPU + GPU + bộ điều khiển bộ nhớ + ngoại vi trên **một đế silicon**. Mạnh hơn MCU nhiều (Snapdragon, RK3399) |
| **Memories** | RAM (chạy chương trình) + Flash/ROM (lưu chương trình) |
| **Peripherals** | Cảm biến, màn hình, WiFi, USB, động cơ... |

### ❓ Câu hỏi thầy cô hay hỏi
- *"Có bắt buộc phải đủ 4 lớp phần mềm không?"* → **Không.** Hệ thống nhỏ chỉ cần Application + Driver. Càng phức tạp càng cần thêm OS và Middleware.
- *"Vì sao cần Device Drivers?"* → Vì Application không thể trực tiếp điều khiển từng chân điện; driver dịch lệnh cấp cao thành tín hiệu điện cụ thể.

### 🎤 Đoạn văn nói
Slide này cho chúng ta cái nhìn tổng thể về kiến trúc một hệ thống nhúng, chia thành hai tầng: phần mềm ở trên và phần cứng ở dưới đường kẻ đứt.

Ở tầng phần mềm, trên cùng là **Application** — nơi chứa logic nghiệp vụ của sản phẩm, tức chức năng mà người dùng thực sự mua thiết bị về để dùng. Ví dụ với máy lạnh thông minh, Application chính là đoạn code quyết định "khi nào bật máy nén". Lớp này không cần biết cảm biến nối vào chân nào của chip.

Ngay bên dưới là **Middleware** — lớp trung gian nằm giữa Application và hệ điều hành. Nó cung cấp các dịch vụ dùng chung mà nếu để Application tự viết thì rất mất công, ví dụ bộ giao thức mạng TCP/IP, hệ thống file, hay thư viện giao diện đồ hoạ.

Tiếp theo là **Operating System** — hệ điều hành, phân chia tài nguyên: quyết định tác vụ nào chạy lúc nào, cấp phát bộ nhớ ra sao. Cần lưu ý không phải hệ thống nhúng nào cũng có lớp này — hệ thống nhỏ có thể chạy không cần hệ điều hành, gọi là bare-metal.

Dưới cùng là **Device Drivers** — lớp phần mềm duy nhất biết chi tiết về phần cứng: biết địa chỉ thanh ghi, biết phải ghi giá trị gì để điều khiển. Nó đóng vai trò cầu nối, dịch các lệnh cấp cao thành tín hiệu điện cụ thể.

Ý nghĩa lớn nhất của việc phân tầng này là: nếu chúng ta đổi sang con chip khác, chỉ cần viết lại lớp Driver, còn lớp Application phía trên giữ nguyên — giúp tiết kiệm rất nhiều công sức.

---

## SLIDE 3 — Architecture of Embedded Hardware

### 📖 Kiến thức nền

**Vì sao lại là BA khối Processor – Memory – I/O?** Xuất phát từ **mô hình máy tính von Neumann** kinh điển:

> Nhập dữ liệu (I/O) → Lưu trữ (Memory) → Xử lý (Processor) → Xuất kết quả (I/O)

Bất kỳ máy tính nào — từ siêu máy tính đến chip trong lò vi sóng — đều tuân theo mô hình này.

**Chi tiết từng thành phần trong sơ đồ:**

- 🔶 **Processor (trung tâm)** — "bộ não", nằm ở giữa vì mọi luồng dữ liệu đều đi qua nó.
- 🟢 **Memories (trên)** — mũi tên **hai chiều** vì CPU cần cả **đọc** (lấy lệnh/dữ liệu) lẫn **ghi** (lưu kết quả).
- 🟣 **Inputs/Outputs (phải)** — hai chiều vì có tín hiệu **vào** (cảm biến) và **ra** (cơ cấu chấp hành).
- 🟡 **User Interface (trái)** — **vì sao tách riêng khỏi I/O?** Vì User Interface giao tiếp với **CON NGƯỜI** (màn hình, nút bấm, đèn LED — ba chấm đỏ-xanh-vàng ở góc), còn Inputs/Outputs giao tiếp với **MÁY MÓC** (cảm biến, động cơ). Không phải hệ thống nhúng nào cũng có UI — bộ điều khiển động cơ giấu trong xe hơi không có màn hình nào cả.
- 🔵 **Power Supply (dưới)** — thường bị xem nhẹ nhưng **cực kỳ quan trọng**: chuyển điện áp (12V ắc quy → 3.3V/5V), **lọc nhiễu** (nguồn bẩn → vi điều khiển reset ngẫu nhiên hoặc đọc sai dữ liệu). Liên hệ Chương 1: đây là nơi quyết định đặc điểm **Energy efficiency**.
- ⬜ **Enclosure (vỏ máy)** — **vì sao vẽ vào?** Vì với hệ thống nhúng, vỏ máy là một phần của thiết kế phần cứng: **tản nhiệt**, **chống nước/bụi** (chuẩn IP), **chắn nhiễu điện từ (EMC)**, **chịu rung động**.
- 🟩 **Connectors (cột phải)** — **ranh giới vật lý** giữa hệ thống và thế giới bên ngoài. Mọi thứ vào/ra đều qua đây.

### 🎤 Đoạn văn nói
Slide này đi sâu vào tầng phần cứng vừa nói. Kiến trúc phần cứng nhúng gồm ba khối chính: **Processor**, **Memory** và **Input/Output**. Ba khối này không phải chọn ngẫu nhiên, mà xuất phát từ mô hình máy tính von Neumann: nhập dữ liệu vào, lưu trữ, xử lý, rồi xuất kết quả ra.

Nhìn vào sơ đồ bên dưới, ở trung tâm là **Processor** — bộ xử lý, đóng vai trò bộ não, mọi luồng dữ liệu đều đi qua nó.

Phía trên là **Memories**, nối với bộ xử lý bằng mũi tên hai chiều — vì bộ xử lý vừa cần đọc lệnh và dữ liệu ra, vừa cần ghi kết quả vào.

Bên phải là khối **Inputs/Outputs** — giao tiếp với cảm biến và cơ cấu chấp hành. Bên trái là **User Interface** — giao diện người dùng. Hai khối này vẽ tách riêng vì mục đích khác nhau: User Interface giao tiếp với **con người** — màn hình, nút bấm, đèn LED báo trạng thái như ba chấm tròn ở góc; còn Inputs/Outputs giao tiếp với **máy móc và hệ thống khác**.

Phía dưới là **Power Supply** — khối nguồn. Đây là thành phần thường bị xem nhẹ nhưng rất quan trọng, vì nó không chỉ cấp điện mà còn phải lọc nhiễu — nếu nguồn không ổn định, vi điều khiển có thể reset ngẫu nhiên hoặc đọc sai dữ liệu.

Cuối cùng, toàn bộ được đặt trong một **Enclosure** — vỏ máy. Với hệ thống nhúng, vỏ máy cũng là một phần của thiết kế phần cứng, vì nó đảm nhận việc tản nhiệt, chống nước, chống bụi và chắn nhiễu điện từ. Và **Connectors** ở cạnh phải chính là ranh giới vật lý giữa hệ thống với thế giới bên ngoài.

**🔄 Câu chuyển:** Sau khi đã có cái nhìn tổng quan, em xin đi sâu vào khối quan trọng nhất — bộ xử lý.

---
---

# PHẦN 2 — VI XỬ LÝ, VI ĐIỀU KHIỂN & RISC/CISC (Slide 4–16)

## SLIDE 4 — Từ Microprocessor đến Semiconductor

### 📖 Kiến thức nền

**Ý tưởng cốt lõi của slide:** đây là hành trình **"phóng to dần"** (zoom-in) qua các **mức trừu tượng** của thiết kế chip. Mỗi mức là một chuyên ngành riêng, có kỹ sư riêng làm việc ở đó.

| Mức | Nội dung | Ai làm việc ở đây |
|---|---|---|
| 1. Chip hoàn chỉnh | Con vi xử lý ta cầm trên tay | Người dùng, kỹ sư nhúng |
| 2. Layout mạch | Bản vẽ hàng tỷ transistor được sắp xếp | Kỹ sư thiết kế vật lý (VLSI) |
| 3. Cổng logic | AND, OR, NAND, NOR, NOT | Kỹ sư thiết kế số |
| 4. Transistor CMOS | Mạch điện gồm PMOS + NMOS | Kỹ sư thiết kế mạch |
| 5. Chất bán dẫn | Tinh thể silicon pha tạp | Nhà vật lý, kỹ sư vật liệu |

**Chi tiết hình chất bán dẫn (giữa slide):** hình vẽ mạng tinh thể **silicon (Si)** — mỗi nguyên tử Si có **4 electron hoá trị**, liên kết với 4 nguyên tử xung quanh. Khi pha thêm nguyên tử **Boron (B)** — chỉ có 3 electron hoá trị — sẽ tạo ra một **"lỗ trống" (hole)** thiếu electron. Đây gọi là **pha tạp loại P**. Ngược lại pha Phốt-pho (5 electron) tạo bán dẫn loại **N** (dư electron). Chính việc ghép các vùng P và N lại mới tạo ra transistor.

**Chi tiết hình MOSFET (dưới phải):** thấy rõ **Source (n+)**, **Drain (n+)**, **Gate** (điện cực điều khiển, làm bằng Poly-silicon), lớp cách điện **SiO₂**, và nền **Substrate (p)**. Nguyên lý: đặt điện áp vào Gate → tạo kênh dẫn giữa Source và Drain → transistor "bật". Đây chính là **công tắc điện tử** cơ bản.

**CMOS là gì và vì sao quan trọng?** CMOS = **Complementary MOS** — dùng **cặp** transistor PMOS và NMOS bù nhau. Ưu điểm quyết định: **gần như KHÔNG tiêu thụ điện ở trạng thái tĩnh**, chỉ tốn điện khi chuyển trạng thái 0↔1. Đây chính là lý do hệ thống nhúng có thể **chạy pin nhiều năm** — liên hệ trực tiếp đặc điểm *Energy efficiency* ở Chương 1.

**65nm, 20nm, 17nm nghĩa là gì?** Là **kích thước đặc trưng của transistor** (chiều dài kênh dẫn). Càng nhỏ thì:
- Nhét được **nhiều transistor hơn** trên cùng diện tích → chip mạnh hơn
- Transistor chuyển trạng thái **nhanh hơn** → xung nhịp cao hơn
- **Tốn ít điện hơn** cho mỗi lần chuyển trạng thái

Đây là biểu hiện của **Định luật Moore** — số transistor trên chip tăng gấp đôi sau mỗi ~2 năm.

### ❓ Câu hỏi thầy cô hay hỏi
- *"1 nanomet là bao nhiêu?"* → 1 phần tỷ mét. Để so sánh: một sợi tóc người dày khoảng 80,000–100,000 nm.
- *"Vì sao dùng silicon mà không phải vật liệu khác?"* → Silicon rẻ (cát là SiO₂), dễ tạo lớp oxit cách điện chất lượng cao (SiO₂), và có tính chất bán dẫn phù hợp ở nhiệt độ phòng.

### 🎤 Đoạn văn nói
Slide này cho thấy một con chip được tạo ra như thế nào, thông qua một hành trình phóng to dần từ ngoài vào trong.

Bắt đầu từ bên trái là hình ảnh một **Microprocessor** hoàn chỉnh mà ta nhìn thấy bằng mắt thường. Đi sâu vào trong, nó là một **bản vẽ layout mạch** cực kỳ phức tạp với hàng tỷ transistor được sắp xếp. Phóng to hơn nữa, ta thấy đó thực chất là các **cổng logic** cơ bản: AND, OR, NAND, NOR và NOT. Mỗi cổng logic này lại được xây dựng từ các **transistor** theo công nghệ **CMOS** — như hình mạch điện bên phải. Và tận cùng, nền tảng của tất cả chính là **chất bán dẫn silicon**, như hình mạng tinh thể ở giữa slide, nơi các nguyên tử silicon được pha thêm tạp chất như Boron để tạo ra tính chất dẫn điện đặc biệt.

Về công nghệ CMOS, điểm quan trọng nhất cần biết là: CMOS gần như **không tiêu thụ điện khi ở trạng thái tĩnh**, chỉ tốn điện khi chuyển trạng thái. Đây chính là lý do vì sao các thiết bị nhúng có thể chạy bằng pin trong thời gian rất dài.

Còn các con số 65 nanomet, 20 nanomet, 17 nanomet là **kích thước của transistor**. Kích thước càng nhỏ thì càng nhét được nhiều transistor trên cùng diện tích, chip chạy nhanh hơn và tiết kiệm điện hơn.

Ý chính của slide này: một con chip không tự nhiên mà có — nó bắt nguồn từ vật lý chất bán dẫn, qua thiết kế mạch transistor, lên thành cổng logic, rồi mới thành sản phẩm mà chúng ta sử dụng.

---

## SLIDE 5 — Microprocessor (CPU)

### 📖 Kiến thức nền

**"Đọc lệnh và xử lý dữ liệu nhị phân" thực chất là chu trình gì?**

CPU hoạt động theo **chu trình Fetch – Decode – Execute** lặp đi lặp lại hàng triệu lần mỗi giây:

1. **Fetch (Nạp lệnh):** lấy lệnh tiếp theo từ bộ nhớ vào CPU
2. **Decode (Giải mã):** phân tích xem lệnh đó yêu cầu làm gì
3. **Execute (Thực thi):** thực hiện phép tính hoặc thao tác tương ứng

**Vì sao là "dữ liệu NHỊ PHÂN"?** Vì transistor chỉ có **2 trạng thái ổn định**: dẫn (1) và không dẫn (0). Mọi thứ — số, chữ, hình ảnh, âm thanh — đều phải mã hoá thành chuỗi 0 và 1.

**Ba khối chi tiết:**

**🔹 ALU (Arithmetic/Logic Unit)** — "bàn tay tính toán":
- **Phép số học:** cộng, trừ, nhân, chia
- **Phép logic:** AND, OR, XOR, NOT, dịch bit (shift), quay bit (rotate)
- **Xuất ra cờ trạng thái (flags):** Zero (kết quả = 0), Carry (có nhớ), Overflow (tràn số), Negative (kết quả âm) — các cờ này dùng cho lệnh rẽ nhánh (if/else)

**🔹 Register Arrays (Dãy thanh ghi)** — "giấy nháp siêu nhanh":
- Là bộ nhớ **nhanh nhất** trong hệ thống, nằm **ngay bên trong CPU**
- Tốc độ: truy cập trong **1 chu kỳ xung nhịp** (so với RAM ngoài mất hàng chục chu kỳ)
- Các loại thanh ghi quan trọng:
  - **PC (Program Counter):** giữ địa chỉ lệnh **tiếp theo** sẽ thực hiện
  - **IR (Instruction Register):** giữ lệnh **đang** được giải mã
  - **Accumulator:** thanh ghi tích luỹ kết quả phép tính
  - **SP (Stack Pointer):** trỏ tới đỉnh ngăn xếp
  - **Flag/Status Register:** chứa các cờ trạng thái từ ALU
  - **General Purpose Registers:** thanh ghi đa dụng cho lập trình viên

**🔹 Control Unit (Khối điều khiển)** — "nhạc trưởng":
- Giải mã lệnh trong IR
- Phát ra các **tín hiệu điều khiển** tới ALU, thanh ghi, bộ nhớ
- Quyết định **thứ tự và thời điểm** mỗi khối hoạt động
- Tăng PC để trỏ sang lệnh kế tiếp

### ❓ Câu hỏi thầy cô hay hỏi
- *"Thanh ghi khác RAM ở điểm nào?"* → Thanh ghi nằm **trong CPU**, cực nhanh, số lượng rất ít (vài chục). RAM nằm **ngoài CPU**, chậm hơn nhiều, nhưng dung lượng lớn.
- *"Program Counter dùng để làm gì?"* → Giữ địa chỉ lệnh tiếp theo. Khi có lệnh nhảy (jump/call), giá trị PC bị thay đổi → chương trình rẽ sang nhánh khác.

### 🎤 Đoạn văn nói
Slide này định nghĩa **Microprocessor**, hay còn gọi là **CPU**. Vi xử lý có hai nhiệm vụ cốt lõi: **đọc lệnh** — read instructions, và **xử lý dữ liệu nhị phân** — process binary data.

Thực chất hai nhiệm vụ này diễn ra theo một chu trình lặp đi lặp lại gọi là **Fetch – Decode – Execute**: nạp lệnh từ bộ nhớ, giải mã xem lệnh đó yêu cầu gì, rồi thực thi. Chu trình này lặp lại hàng triệu lần mỗi giây. Còn sở dĩ gọi là dữ liệu "nhị phân" vì transistor chỉ có hai trạng thái ổn định — dẫn và không dẫn, tương ứng với bit 1 và bit 0.

Về cấu tạo, sơ đồ bên phải chia CPU thành ba phần.

Thứ nhất là **ALU — Arithmetic/Logic Unit**, khối tính toán số học và logic. Đây là nơi thực hiện các phép cộng, trừ, so sánh, và các phép logic như AND, OR, XOR. Ngoài kết quả, ALU còn xuất ra các **cờ trạng thái** như cờ Zero hay cờ Carry — được dùng cho các lệnh rẽ nhánh.

Thứ hai là **Register Arrays** — các dãy thanh ghi. Đây là bộ nhớ nhanh nhất trong hệ thống vì nằm ngay bên trong CPU, truy cập chỉ mất một chu kỳ xung nhịp. Một số thanh ghi quan trọng là **Program Counter** giữ địa chỉ lệnh tiếp theo, **Instruction Register** giữ lệnh đang được giải mã, và **Accumulator** tích luỹ kết quả phép tính.

Thứ ba là **Control Unit** — khối điều khiển, đóng vai trò như một nhạc trưởng. Nó giải mã lệnh, phát ra các tín hiệu điều khiển tới ALU và thanh ghi, và quyết định thứ tự cũng như thời điểm mỗi khối hoạt động.

---

## SLIDE 6 — Kiến trúc Intel 8085

### 📖 Kiến thức nền

**Cách tiếp cận slide này:** không học thuộc, mà **nhận diện** các khối đã biết từ slide 5, đồng thời **ghi nhận vài chi tiết sẽ dùng lại ở cuối chương**.

**Nhận diện các khối tương ứng slide 5:**
- **ALU** (khối màu đỏ ở giữa) ← chính là ALU
- **Accumulator (8 Bit)**, **Temp Register**, **Flag Register (8 Bit)** ← thuộc nhóm thanh ghi
- **Register array**: B, C, D, E, H, L (mỗi cái 8 bit), **Stack Pointer (16 Bit)**, **Program Counter (16 Bit)** ← thanh ghi
- **Instruction Register** + **Instruction Decoder and Machine Cycle Encoding** ← thuộc Control Unit
- **Timing and Control** (khối dài phía dưới) ← Control Unit

**Ba chi tiết quan trọng cần chú ý (sẽ dùng lại về sau):**

**① Bus dữ liệu nội bộ 8 bit** (dải xám ngang giữa slide) → 8085 là vi xử lý **8-bit** — xử lý 8 bit dữ liệu mỗi lần.

**② Bus địa chỉ 16 bit** (A8–A15 và A0–A7 ở dưới phải) → khả năng địa chỉ hoá:

> 2^16 = 65,536 ô nhớ = **64 KB**

Con số 64K này sẽ **xuất hiện lại ở slide 32** (giao tiếp bộ nhớ ngoài 8051 cũng 64K) — không phải trùng hợp, mà vì cả hai đều dùng bus địa chỉ 16 bit.

**③ AD0–AD7 và tín hiệu ALE** (góc dưới phải) → chân **AD0-AD7 dùng chung cho cả địa chỉ và dữ liệu** (multiplexed). Cần khối **Address Latch** (thấy trong sơ đồ) và tín hiệu **ALE** để tách ra. **Đây chính xác là vấn đề sẽ được giải thích kỹ ở slide 32 và 34** — hãy nhớ chi tiết này!

**Các khối bổ sung mà slide 5 không có:**
- **Interrupt Control** (trên trái): xử lý ngắt — cho phép thiết bị ngoài "xin phép" CPU tạm dừng việc đang làm để xử lý việc gấp
- **Serial I/O Control** (trên phải): truyền dữ liệu nối tiếp (SID/SOD)
- **CLK GEN** (dưới trái): mạch tạo xung nhịp từ thạch anh X1, X2

### ❓ Câu hỏi thầy cô hay hỏi
- *"Vì sao bus địa chỉ 16 bit lại cho 64KB?"* → Vì 2^16 = 65,536 địa chỉ, mỗi địa chỉ trỏ tới 1 byte → 65,536 byte = 64 KB.
- *"Ngắt (interrupt) để làm gì?"* → Để CPU phản ứng ngay với sự kiện gấp mà không phải liên tục đi hỏi thăm (polling) — tiết kiệm thời gian và điện năng.

### 🎤 Đoạn văn nói
Đây là sơ đồ kiến trúc chi tiết của vi xử lý **Intel 8085** — một vi xử lý thực tế.

Em sẽ không đi vào từng khối nhỏ, nhưng qua slide này chúng ta có thể nhận ra tất cả các thành phần đã học ở slide trước, chỉ là ở dạng chi tiết hơn. Cụ thể: khối màu đỏ ở giữa chính là **ALU**. Xung quanh nó là các **thanh ghi** — Accumulator, Flag Register, và dãy thanh ghi B, C, D, E, H, L bên phải, cùng với Stack Pointer và Program Counter 16 bit. Còn khối **Instruction Decoder** và khối **Timing and Control** phía dưới chính là phần Control Unit.

Có ba chi tiết em muốn các bạn chú ý vì sẽ liên quan đến phần sau của bài.

Thứ nhất, dải xám chạy ngang giữa slide là **bus dữ liệu nội bộ 8 bit** — cho thấy đây là vi xử lý 8-bit.

Thứ hai, ở góc dưới phải là **bus địa chỉ 16 bit**, gồm A0 đến A15. Với 16 bit địa chỉ, vi xử lý này có thể truy cập được 2 mũ 16, tức 65,536 ô nhớ — bằng **64 kilobyte**. Con số 64K này sẽ xuất hiện lại ở phần bộ nhớ sau này.

Thứ ba, các chân **AD0 đến AD7** được dùng chung cho cả địa chỉ và dữ liệu, nên cần một khối **Address Latch** cùng tín hiệu **ALE** để tách chúng ra. Đây chính là vấn đề mà em sẽ giải thích kỹ ở slide về thiết kế bộ nhớ ngoài.

Ý chính của slide: các khối chức năng cơ bản vẫn là ALU, thanh ghi và điều khiển, nhưng trong thực tế được triển khai chi tiết hơn nhiều, cùng với các mạch hỗ trợ như điều khiển ngắt và tạo xung nhịp.

---

## SLIDE 7 — Microprocessor system

### 📖 Kiến thức nền

**"System Bus" thực chất gồm BA bus riêng biệt:**

| Bus | Hướng truyền | Nhiệm vụ |
|---|---|---|
| **Address Bus** | Một chiều (CPU → thiết bị) | CPU nói "tôi muốn truy cập ô nhớ số mấy" |
| **Data Bus** | **Hai chiều** | Dữ liệu thực sự được truyền qua đây |
| **Control Bus** | Hỗn hợp | Các tín hiệu RD, WR, CLK, RESET, INT... |

*Ví von:* Address Bus = **địa chỉ nhà**, Data Bus = **hàng hoá trong xe tải**, Control Bus = **lệnh giao hay nhận**.

**Vì sao cần CẢ RAM và ROM?**

| | ROM | RAM |
|---|---|---|
| Lưu gì | **Chương trình** (code) | **Biến số, dữ liệu tạm** |
| Mất điện | Giữ nguyên (non-volatile) | Mất sạch (volatile) |
| Vì sao cần | Bật máy lên phải có sẵn code để chạy | Cần chỗ ghi/xoá liên tục khi chạy |

Nếu chỉ có RAM: mất điện là mất chương trình → bật lên không biết làm gì.
Nếu chỉ có ROM: không có chỗ lưu biến số đang tính toán.

**Nhược điểm của hệ thống vi xử lý rời** (điều dẫn tới sự ra đời của MCU ở slide 8):
- Cần **nhiều chip** → tốn diện tích bo mạch
- Cần **nhiều đường mạch** nối bus giữa các chip → dễ nhiễu, khó thiết kế
- **Giá thành cao** hơn (nhiều chip, bo mạch to)
- **Tiêu thụ điện nhiều** hơn
- **Kém tin cậy** hơn (nhiều mối hàn = nhiều điểm có thể hỏng)

**Ưu điểm còn lại:** rất **linh hoạt** — muốn thêm RAM thì thay chip RAM lớn hơn, không bị giới hạn bởi nhà sản xuất.

### 🎤 Đoạn văn nói
Slide này cho thấy một điều rất quan trọng: **vi xử lý không thể hoạt động một mình**.

Bên trái là khối **Microprocessor**, gồm ALU, Registers và Control Unit như chúng ta vừa học. Nhưng để trở thành một hệ thống hoàn chỉnh, nó cần được kết nối qua **System Bus** — mũi tên lớn màu xanh lá ở giữa — tới hai nhóm thành phần khác: phía trên là **I/O Devices** gồm thiết bị vào và thiết bị ra; phía dưới là **Memory** gồm **RAM** và **ROM**.

Về System Bus, thực chất nó gồm ba bus riêng: **Address Bus** để CPU chỉ định muốn truy cập ô nhớ nào, **Data Bus** để truyền dữ liệu thực sự, và **Control Bus** mang các tín hiệu điều khiển như đọc hay ghi.

Còn về bộ nhớ, hệ thống cần **cả RAM lẫn ROM** vì mỗi loại có vai trò khác nhau: **ROM** lưu chương trình và không mất khi cúp điện — nhờ vậy bật máy lên là có sẵn code để chạy; còn **RAM** lưu biến số và dữ liệu tạm trong lúc chạy, có thể ghi xoá liên tục nhưng sẽ mất khi ngắt điện.

Đây chính là **hệ thống dùng vi xử lý rời** — nghĩa là CPU nằm một chip, RAM một chip, ROM một chip, được nối với nhau trên bo mạch. Cách làm này rất linh hoạt nhưng có nhược điểm là tốn diện tích, nhiều đường mạch dễ gây nhiễu, giá thành cao và tiêu thụ nhiều điện. Chính những nhược điểm này đã dẫn tới sự ra đời của vi điều khiển mà em trình bày ở slide tiếp theo.

---

## SLIDE 8 — Microcontroller (MCU)

### 📖 Kiến thức nền

**Định nghĩa cốt lõi:** MCU = **MPU + Memory + I/O ports** trên **MỘT chip**.

**So sánh trực tiếp với slide 7:**

| | Vi xử lý (Slide 7) | Vi điều khiển (Slide 8) |
|---|---|---|
| Số chip cần | Nhiều (CPU, RAM, ROM, I/O riêng) | **Một** |
| Diện tích bo mạch | Lớn | Nhỏ |
| Giá thành hệ thống | Cao | Thấp |
| Tiêu thụ điện | Nhiều | Ít |
| Độ tin cậy | Thấp hơn (nhiều mối hàn) | Cao hơn |
| Tính linh hoạt | Cao (nâng RAM tuỳ ý) | Thấp (bị giới hạn bởi chip) |
| Hiệu năng tối đa | Cao | Thấp hơn |

**Bảng Packages (vỏ chip) — vì sao quan trọng?**

Chia thành **2 nhóm lớn**:

**🔸 Xuyên lỗ (Through-hole)** — chân cắm xuyên qua bo mạch:
- **CPGA** (Ceramic Pin Grid Array): vỏ gốm, chân dạng lưới — dùng cho chip cao cấp, tản nhiệt tốt
- **SDIP** (Plastic through-hole): vỏ nhựa, 2 hàng chân — **dễ cắm breadboard, phù hợp học tập/làm mẫu**
- **HDIP**: giống SDIP nhưng **tản nhiệt tốt hơn**

**🔸 Dán bề mặt (Surface Mount - SMD)** — hàn trực tiếp lên mặt bo mạch:
- **PLCC** (Plastic Leaded Chip Carrier): chân quặp dưới thân
- **QFP** (Quad Flat Package): chân dẹt 4 cạnh — **phổ biến nhất trong sản xuất hàng loạt**
- **HSOP**: dạng dẹt, **tản nhiệt cao**

**Vì sao kỹ sư nhúng cần quan tâm vỏ chip?**
1. **Kích thước sản phẩm** — SMD nhỏ hơn nhiều
2. **Khả năng tản nhiệt** — chip chạy nóng cần vỏ phù hợp
3. **Cách sản xuất** — SMD cần máy dán tự động, DIP có thể hàn tay
4. **Giai đoạn phát triển** — làm mẫu thì dùng DIP cho dễ, sản xuất thật thì chuyển SMD

**Các dòng MCU trong hình:**
- **Atmel AVR / ATmega328P**: 8-bit, RISC — nổi tiếng vì là chip trên **Arduino Uno**
- **PIC18F877A**: 8-bit của Microchip, rất phổ biến trong giảng dạy
- **8051**: dòng kinh điển từ Intel (1980), vẫn được dùng và dạy đến nay
- **Arduino**: thực ra là **bo mạch phát triển**, không phải chip — dùng chip AVR
- **ARM**: kiến trúc **32-bit RISC**, mạnh nhất trong nhóm — dùng trong điện thoại, STM32

### ❓ Câu hỏi thầy cô hay hỏi
- *"Khi nào dùng vi xử lý, khi nào dùng vi điều khiển?"* → Dùng **MCU** cho hầu hết ứng dụng nhúng (chi phí thấp, đơn giản). Dùng **MPU** khi cần hiệu năng rất cao hoặc cần lượng RAM lớn tuỳ biến (ví dụ máy tính nhúng chạy Linux).
- *"Arduino là vi điều khiển?"* → Không hẳn. Arduino là **bo mạch phát triển** có sẵn chip AVR, mạch nạp, và nguồn — giúp người mới bắt đầu dễ dàng hơn.

### 🎤 Đoạn văn nói
Slide này định nghĩa **Microcontroller**, viết tắt là **MCU** — vi điều khiển.

Định nghĩa như sau: MCU là một thiết bị tính toán điện tử tích hợp, bao gồm **ba thành phần chính trên MỘT chip duy nhất**: **Microprocessor — MPU**, tức bộ vi xử lý; **Memory** — bộ nhớ; và **I/O ports** — các cổng vào ra.

Đây chính là điểm khác biệt cốt lõi so với slide trước: nếu hệ thống vi xử lý cần nhiều chip riêng lẻ nối với nhau, thì vi điều khiển đã gói gọn tất cả vào một con chip. Nhờ vậy nó **nhỏ gọn hơn, rẻ hơn, tiết kiệm điện hơn và đáng tin cậy hơn** — đổi lại thì kém linh hoạt hơn vì ta không thể tự nâng cấp dung lượng RAM.

Bảng bên trái minh hoạ các kiểu **vỏ chip** khác nhau. Chúng được chia thành hai nhóm: nhóm **xuyên lỗ** như CPGA, SDIP, HDIP — có chân cắm xuyên qua bo mạch, dễ cắm breadboard nên phù hợp cho học tập và làm mẫu; và nhóm **dán bề mặt** như PLCC, QFP, HSOP — hàn trực tiếp lên mặt bo mạch, nhỏ gọn hơn nên dùng cho sản xuất hàng loạt. Ngoài ra, một số kiểu vỏ như HDIP và HSOP còn được thiết kế để **tản nhiệt tốt hơn**.

Và bên phải là các dòng vi điều khiển thực tế phổ biến hiện nay: **Atmel AVR** và **ATmega328P** — chính là chip dùng trên bo Arduino; **PIC18F877A** của Microchip; **8051** — dòng kinh điển vẫn được dạy đến nay; và **ARM** — kiến trúc 32-bit mạnh nhất trong nhóm, dùng trong điện thoại thông minh và các dòng STM32.

---

## SLIDE 9 — Bên trong một MCU thực tế (dòng PIC)

### 📖 Kiến thức nền

**Ý nghĩa các mũi tên:** các linh kiện rời ở trên (Oscillator, A/D Converter, Microprocessor, RAM, Program Memory) **được "hút" vào** thành một chip duy nhất phía dưới. Đây là minh hoạ trực quan cho định nghĩa MCU ở slide 8.

**Giải thích từng khối bên trong chip:**

| Khối | Chức năng | Ví dụ ứng dụng |
|---|---|---|
| **CPU** | Bộ xử lý trung tâm | Chạy chương trình |
| **Program Memory** | Flash lưu **code** | Chương trình của bạn |
| **RAM** | Lưu **biến** khi chạy | Giá trị nhiệt độ đang đo |
| **EEPROM** | Lưu **cài đặt** không mất khi tắt máy | Nhiệt độ người dùng đặt cho máy lạnh |
| **Oscillator 0-40MHz + PLL** | Tạo xung nhịp | Quyết định tốc độ chạy của CPU |
| **Timers T0-T3** | Đếm thời gian/sự kiện | Tạo độ trễ, đo tần số |
| **A/D Converter + Vref** | Đổi tín hiệu **analog → digital** | Đọc cảm biến nhiệt độ (điện áp) |
| **CCP1/CCP2, CCP/PWM** | Capture/Compare/PWM | Điều khiển độ sáng LED, tốc độ động cơ |
| **SPI, I²C, USART** | Truyền thông nối tiếp | Nói chuyện với cảm biến, máy tính |
| **WDT (Watchdog Timer)** | Tự reset nếu chương trình treo | **Đảm bảo Dependability** (Chương 1!) |
| **Interrupts** | Xử lý sự kiện gấp | Nút nhấn khẩn cấp |
| **I/O Ports A-E** | Chân vào/ra số | Bật LED, đọc nút bấm |
| **RESET** | Khởi động lại chip | |
| **Power Supply 2-5.5V** | Dải điện áp hoạt động | Chạy được cả pin 3V lẫn nguồn 5V |

**Hai khối đáng chú ý nhất:**

**🔹 A/D Converter — vì sao cực kỳ quan trọng?** Thế giới thực là **tương tự** (nhiệt độ, ánh sáng, âm thanh biến thiên liên tục), nhưng CPU chỉ hiểu **số**. ADC là cây cầu bắt buộc phải có. Không có ADC thì MCU không đọc được hầu hết cảm biến.

**🔹 Watchdog Timer (WDT) — liên hệ trực tiếp Chương 1:** Là một bộ đếm ngược. Chương trình phải liên tục "vỗ về" nó (reset bộ đếm). Nếu chương trình bị **treo** → không vỗ về nữa → WDT đếm về 0 → **tự động reset chip**. Đây chính là cơ chế đảm bảo thuộc tính **Reliable** và **Available** trong Dependability.

### ❓ Câu hỏi thầy cô hay hỏi
- *"Vì sao dải điện áp là 2 đến 5.5V?"* → Để chip dùng được với nhiều nguồn khác nhau: 2 pin AA (3V), pin lithium (3.7V), hay nguồn USB (5V) — tăng tính linh hoạt cho thiết kế.
- *"PWM là gì?"* → Pulse Width Modulation — điều chế độ rộng xung. Bật/tắt rất nhanh với tỉ lệ thời gian bật khác nhau để tạo ra mức trung bình mong muốn, dùng điều khiển độ sáng LED hoặc tốc độ động cơ.

### 🎤 Đoạn văn nói
Slide này minh hoạ rất trực quan cho định nghĩa vừa rồi. Các bạn thấy ở phía trên là các linh kiện **rời rạc**: bộ dao động Oscillator, bộ chuyển đổi A/D, bộ vi xử lý, RAM, và Program Memory — bộ nhớ chương trình.

Các mũi tên cho thấy tất cả những linh kiện rời này được **gộp lại và tích hợp vào bên trong một con chip duy nhất** — chính là con **Microcontroller** ở phía dưới.

Nhìn vào sơ đồ bên trong chip, ta thấy đầy đủ mọi thứ cần thiết. Về xử lý và lưu trữ, có **CPU** ở giữa, **Program Memory** để lưu chương trình, **RAM** để lưu biến khi chạy, và **EEPROM** để lưu các cài đặt không bị mất khi tắt nguồn.

Về các khối ngoại vi, có **Oscillator** từ 0 đến 40 megahertz để tạo xung nhịp; các bộ **Timers** T0 đến T3 để đếm thời gian; khối **A/D Converter** — đây là khối rất quan trọng vì nó chuyển tín hiệu tương tự từ cảm biến thành tín hiệu số mà CPU hiểu được; khối **CCP/PWM** dùng để điều khiển độ sáng LED hoặc tốc độ động cơ; các giao tiếp nối tiếp **SPI, I²C và USART**; cùng các cổng **I/O Ports** từ Port A đến Port E.

Ngoài ra còn có một khối đáng chú ý là **WDT — Watchdog Timer**. Đây là bộ đếm ngược mà chương trình phải liên tục làm mới. Nếu chương trình bị treo và không làm mới nữa, watchdog sẽ tự động reset chip — đây chính là cơ chế đảm bảo tính tin cậy mà chúng ta đã học ở Chương 1.

Cuối cùng, chip hoạt động ở dải điện áp từ 2 đến 5.5 volt, cho phép dùng được với nhiều loại nguồn khác nhau.

Ý chính: **tất cả những gì cần thiết cho một hệ thống đều nằm gọn trong một con chip**.

---

## SLIDE 10 — MCU kết nối với thế giới thực

### 📖 Kiến thức nền

**Ý nghĩa MÀU SẮC của các mũi tên trong slide:**
- **Mũi tên xanh dương (trái):** dữ liệu đi **VÀO** MCU
- **Mũi tên nâu (phải):** dữ liệu đi **RA** từ MCU
- **Mũi tên xanh lá (dưới):** **HAI CHIỀU** — vừa đọc vừa ghi

**Phân tích các thiết bị INPUT — mỗi loại cần cách xử lý khác nhau:**

| Thiết bị | Loại tín hiệu | MCU cần gì để đọc |
|---|---|---|
| **Sensors** (cảm biến nhiệt độ, áp suất) | **Tương tự** (analog) | Cần **ADC** |
| **Push buttons, Switches** | **Số** (digital 0/1) | Chỉ cần chân GPIO, nhưng cần **chống dội phím (debouncing)** |
| **Potentiometers** (biến trở) | **Tương tự** | Cần **ADC** |
| **Keypads** (bàn phím ma trận) | Số, nhiều phím | Cần kỹ thuật **quét ma trận (scanning)** để tiết kiệm chân |

💡 **Chống dội phím (debouncing) là gì?** Khi nhấn nút cơ khí, tiếp điểm **nảy** vài lần trong khoảng vài mili-giây → MCU có thể hiểu nhầm là nhấn nhiều lần. Phải lọc bằng phần mềm (chờ ổn định) hoặc phần cứng (tụ điện).

**Phân tích các thiết bị OUTPUT:**

| Thiết bị | MCU điều khiển bằng cách nào |
|---|---|
| **Radio link** | Truyền nối tiếp (UART/SPI) |
| **7-segment displays** | Xuất mã số ra nhiều chân, thường dùng kỹ thuật **quét (multiplexing)** |
| **Indicators (LED)** | Bật/tắt chân GPIO |
| **Servo engines** | **PWM** — độ rộng xung quyết định góc quay |
| **Step motors** | Xuất **chuỗi xung theo thứ tự** vào các cuộn dây |
| **Analogue devices** (đồng hồ kim) | **PWM lọc thành mức DC**, hoặc DAC |
| **LCD & VFD displays** | Giao thức song song hoặc I²C/SPI |
| **Buzzers, speakers** | Xuất **sóng vuông** với tần số tương ứng nốt nhạc |

**Hai kết nối HAI CHIỀU (dưới):**
- **EEPROM memories:** bộ nhớ ngoài để lưu thêm dữ liệu, thường qua **I²C hoặc SPI**
- **Computer link:** kết nối máy tính để nạp chương trình hoặc gỡ lỗi, thường qua **UART/USB**

### 🎤 Đoạn văn nói
Slide này cho thấy vi điều khiển giao tiếp với thế giới bên ngoài như thế nào — đây chính là hình ảnh cụ thể của mô hình "cảm biến, xử lý, cơ cấu chấp hành" mà chúng ta đã học ở Chương 1.

Ở giữa là con vi điều khiển, ký hiệu **μC**. Các mũi tên màu xanh dương bên trái là dữ liệu đi **vào**, màu nâu bên phải là dữ liệu đi **ra**, và màu xanh lá phía dưới là kết nối **hai chiều**.

Bên trái là các **thiết bị đầu vào**: cảm biến, nút nhấn, công tắc, biến trở, và bàn phím. Điều đáng chú ý là mỗi loại cần cách xử lý khác nhau. Cảm biến và biến trở cho tín hiệu **tương tự**, nên MCU phải dùng bộ **ADC** để chuyển đổi. Còn nút nhấn và công tắc cho tín hiệu **số**, nhưng lại cần kỹ thuật **chống dội phím** — vì khi nhấn, tiếp điểm cơ khí nảy vài lần khiến MCU có thể hiểu nhầm là nhấn nhiều lần.

Bên phải là các **thiết bị đầu ra**: module thu phát vô tuyến, LED 7 đoạn, đèn báo, động cơ servo, động cơ bước, đồng hồ đo, màn hình LCD, và loa còi. Cách điều khiển cũng khác nhau: LED chỉ cần bật tắt chân, động cơ servo cần tín hiệu **PWM** với độ rộng xung quyết định góc quay, còn động cơ bước cần một **chuỗi xung theo đúng thứ tự** vào các cuộn dây.

Phía dưới là hai kết nối hai chiều: **bộ nhớ EEPROM ngoài** để lưu thêm dữ liệu, và **kết nối máy tính** để nạp chương trình hoặc gỡ lỗi.

---

## SLIDE 11 — Block Diagram tổng quát

### 📖 Kiến thức nền

**Đây là mô hình CHUẨN mà mọi MCU đều tuân theo** — ba slide sau (12, 13, 14) sẽ chứng minh bằng 3 chip thật của 3 hãng khác nhau.

**Phần lõi (trên):**
- **MPU** — bộ xử lý
- **Bus** — đường truyền nối tất cả lại
- **Memory** — bộ nhớ
- **I/O Ports** — cổng vào ra

**Phần Support Devices (dưới) — vì sao gọi là "hỗ trợ"?**

Đây là các khối ngoại vi có nhiệm vụ **"gánh việc" thay cho CPU**. Khái niệm quan trọng ở đây là **offload** — giảm tải cho CPU.

**Ví dụ minh hoạ sức mạnh của offload:**

Giả sử cần tạo tín hiệu PWM bật/tắt 1000 lần mỗi giây:
- **Không có Timer:** CPU phải liên tục đếm và bật/tắt → **CPU bận 100%**, không làm được việc gì khác
- **Có Timer/PWM:** CPU chỉ **cài đặt một lần** ("hãy tạo PWM tần số 1kHz, độ rộng 50%") rồi **đi làm việc khác**. Khối phần cứng tự chạy độc lập.

Đây chính là lý do vì sao MCU có nhiều ngoại vi tích hợp — nó cho phép **một CPU chậm vẫn xử lý được nhiều việc cùng lúc**, đáp ứng ràng buộc thời gian thực.

**Bốn nhóm Support Devices:**
- **Timers** — đếm thời gian, tạo PWM, đo tần số
- **A/D Converter** — đọc cảm biến tương tự
- **Serial I/O** — truyền thông UART/SPI/I²C
- **Other Devices** — Watchdog, DMA, Comparator, RTC...

### 🎤 Đoạn văn nói
Slide này đưa ra **sơ đồ khối tổng quát** của một vi điều khiển, ở dạng khái quát nhất.

Phần trên là phần lõi, gồm: **Microprocessor Unit — MPU** ở bên trái, kết nối qua một đường **Bus** tới **Memory** và **I/O Ports** ở bên phải.

Phần dưới là nhóm **Support Devices** — các thiết bị hỗ trợ, gồm **Timers**, **A/D Converter**, **Serial I/O**, và **Other Devices**.

Em muốn nhấn mạnh vai trò của nhóm Support Devices này. Chúng được gọi là "hỗ trợ" vì nhiệm vụ chính là **gánh việc thay cho CPU**. Ví dụ, nếu muốn tạo tín hiệu PWM bật tắt một nghìn lần mỗi giây mà không có khối Timer, CPU sẽ phải liên tục đếm và bật tắt, tức là bận đến một trăm phần trăm và không làm được việc gì khác. Nhưng khi có khối Timer/PWM, CPU chỉ cần cài đặt một lần rồi đi làm việc khác, còn khối phần cứng tự chạy độc lập.

Chính nhờ cơ chế này mà một vi điều khiển với CPU không quá mạnh vẫn có thể xử lý nhiều việc cùng lúc và đáp ứng được ràng buộc thời gian thực.

Đây là mô hình chuẩn mà mọi vi điều khiển đều tuân theo, dù của hãng nào đi nữa — và ba slide tiếp theo sẽ chứng minh điều đó.

---

## SLIDE 12 — Block Diagram của 8051

### 📖 Kiến thức nền

**Thông số cơ bản của 8051** (chip kinh điển từ Intel, ra đời 1980, vẫn được dạy đến nay):
- **4 KB** ROM trên chip (chứa chương trình)
- **128 byte** RAM trên chip
- **2 bộ Timer** (Timer 0, Timer 1)
- **4 cổng I/O** × 8 chân = **32 chân vào/ra**
- **1 cổng nối tiếp** (UART)
- **6 nguồn ngắt**

**Đối chiếu với mô hình chuẩn slide 11:**

| Mô hình chuẩn | Trong 8051 |
|---|---|
| MPU | **CPU** (khối xanh giữa trái) |
| Memory | **On-chip ROM** + **On-chip RAM** |
| I/O Ports | **4 I/O Ports** (P0, P1, P2, P3) |
| Timers | **Timer 0, Timer 1** |
| Serial I/O | **Serial Port** (TxD, RxD) |
| Other Devices | **Interrupt Control**, **Bus Control**, **OSC** |

**Chi tiết quan trọng cần chú ý:**

**🔸 Dòng chữ "Address/Data" dưới P0-P3** → Đây chính là vấn đề **bus dùng chung** đã gặp ở slide 6 (8085) và sẽ giải thích kỹ ở **slide 32**. Cổng P0 và P2 vừa là cổng I/O thường, vừa có thể chuyển thành bus địa chỉ/dữ liệu khi cần nối bộ nhớ ngoài.

**🔸 Khối OSC với ký hiệu thạch anh và 2 tụ điện** → Mạch dao động cần **thạch anh ngoài** (thường 11.0592 MHz cho 8051). Vì sao con số lẻ này? Vì nó **chia hết** cho các tốc độ truyền UART chuẩn (9600, 19200 baud...).

**🔸 External interrupts (trên trái)** → Chân ngắt ngoài, cho phép thiết bị bên ngoài báo cho CPU sự kiện gấp.

**🔸 Bus Control** → Khối phát ra các tín hiệu điều khiển bus khi giao tiếp bộ nhớ ngoài (ALE, PSEN...).

### 🎤 Đoạn văn nói
Đây là sơ đồ khối của vi điều khiển **8051** — một dòng chip kinh điển của Intel, ra đời từ năm 1980 nhưng vẫn được sử dụng và giảng dạy đến ngày nay.

Đối chiếu với mô hình chuẩn ở slide trước, ta nhận ra đầy đủ: **CPU** ở giữa bên trái tương ứng với MPU; **On-chip ROM** dùng để chứa mã chương trình và **On-chip RAM** dùng cho dữ liệu — tương ứng với khối Memory; **4 cổng I/O** là P0, P1, P2, P3 ở phía dưới; khối **Timer/Counter** gồm Timer 0 và Timer 1 ở bên phải; và **Serial Port** với hai chân TxD và RxD.

Ngoài ra còn có các khối hỗ trợ khác: **Interrupt Control** xử lý các ngắt ngoài, **Bus Control** điều khiển bus khi giao tiếp bộ nhớ ngoài, và khối **OSC** — mạch dao động, cần nối thêm thạch anh và hai tụ điện bên ngoài để tạo xung nhịp.

Về thông số, 8051 có 4 kilobyte ROM, 128 byte RAM, 2 bộ định thời, 32 chân vào ra và một cổng nối tiếp.

Một chi tiết đáng chú ý là dòng chữ **"Address/Data"** ngay dưới các cổng P0 đến P3. Điều này có nghĩa các cổng này vừa dùng làm cổng vào ra thông thường, vừa có thể chuyển thành bus địa chỉ và dữ liệu khi cần nối với bộ nhớ ngoài — vấn đề em sẽ giải thích kỹ ở phần sau.

---

## SLIDE 13 — Block Diagram của PIC12F617

### 📖 Kiến thức nền

**Thông số nổi bật:**
- **CPU 14-bit instructions**, chỉ **35 lệnh tổng cộng**
- **Program Memory 3.5 KB** (tương đương 2K lệnh)
- **SRAM 128 byte**
- **Internal Oscillator 8 MHz**
- **8-Level Stack**
- **ADC 10-bit, 4 kênh**

**Ba điểm cực kỳ đáng chú ý:**

**🔥 ① "35 Total Instructions" = BẰNG CHỨNG của RISC!**

Đây là **liên kết trực tiếp tới slide 15**. Chỉ **35 lệnh** — đây chính là "tập lệnh rút gọn" (Reduced Instruction Set). So sánh: vi xử lý x86 (CISC) có **hàng nghìn lệnh**. Khi thuyết trình, hãy chỉ vào con số này và nói: *"Đây là ví dụ cụ thể cho kiến trúc RISC mà em sắp trình bày."*

**🔥 ② "Internal Oscillator 8 MHz" — vì sao quan trọng?**

Khác với 8051 (slide 12) cần **thạch anh ngoài**, PIC này có **dao động tích hợp sẵn**. Lợi ích:
- **Tiết kiệm 3 linh kiện** (1 thạch anh + 2 tụ)
- **Tiết kiệm 2 chân chip** → có thêm chân dùng cho I/O
- **Bo mạch nhỏ hơn, rẻ hơn**

Đánh đổi: dao động nội **kém chính xác hơn** thạch anh (sai số ~1% so với ~0.005%), nên không dùng được cho ứng dụng cần độ chính xác thời gian cao.

**🔥 ③ "8-Level Stack" — hạn chế cần biết!**

Stack (ngăn xếp) dùng để lưu địa chỉ quay về khi gọi hàm. **Chỉ 8 mức** nghĩa là hàm chỉ được gọi lồng nhau tối đa 8 tầng. Nếu gọi sâu hơn → **tràn stack (stack overflow)** → chương trình chạy sai.

Đây là ví dụ điển hình của **ràng buộc tài nguyên** trong hệ thống nhúng — liên hệ đặc điểm *Code size* ở Chương 1.

**Các khối ngoại vi phía dưới:**
- **Internal Voltage Reference:** điện áp tham chiếu cho ADC/Comparator
- **BOR (Brown-out Reset):** tự reset khi **điện áp sụt** dưới ngưỡng an toàn → tránh chip chạy sai khi nguồn yếu
- **WDT (Watchdog Timer):** reset khi chương trình treo
- **10-bit ADC 4 channels:** đọc được 4 cảm biến tương tự, độ phân giải 2^10 = **1024 mức**
- **Comparator:** so sánh 2 điện áp, nhanh hơn ADC
- **Capture/Compare/PWM:** điều khiển động cơ, đo độ rộng xung
- **Two 8-bit Timers + One 16-bit Timer**

**"With Self Read-Write Capabilities"** (ghi chú dưới Program Memory) → chip có thể **tự ghi vào bộ nhớ chương trình của chính nó** → cho phép làm **bootloader**, tức cập nhật firmware mà không cần máy nạp.

### 🎤 Đoạn văn nói
Đây là ví dụ thứ hai — vi điều khiển **PIC12F617** của hãng Microchip.

Nhìn vào sơ đồ, ta thấy **CPU** ở giữa sử dụng lệnh 14-bit, với **tổng cộng chỉ 35 lệnh**. Em muốn nhấn mạnh con số này, vì đây chính là bằng chứng cụ thể cho kiến trúc **RISC — tập lệnh rút gọn** mà em sẽ trình bày ở slide sau. Để so sánh, các vi xử lý theo kiến trúc CISC như dòng x86 có tới hàng nghìn lệnh.

Về bộ nhớ, chip có **Program Memory** lên tới 3.5 kilobyte, tương đương 2000 lệnh, và **SRAM** 128 byte. Đáng chú ý là dòng ghi chú "With Self Read-Write Capabilities" — nghĩa là chip có thể tự ghi vào bộ nhớ chương trình của chính nó, cho phép cập nhật firmware mà không cần máy nạp.

Một điểm khác biệt so với 8051 là chip này có **Internal Oscillator 8 megahertz** — tức dao động tích hợp sẵn bên trong, không cần thạch anh ngoài. Điều này giúp tiết kiệm linh kiện và tiết kiệm được hai chân chip để dùng cho việc khác.

Ngoài ra còn có khối **8-Level Stack** — tức ngăn xếp chỉ có 8 mức, nghĩa là các hàm chỉ được gọi lồng nhau tối đa 8 tầng. Đây là một ví dụ điển hình cho ràng buộc tài nguyên trong hệ thống nhúng.

Phía dưới là các khối ngoại vi: **Internal Voltage Reference** tạo điện áp tham chiếu; **BOR** tự reset khi điện áp sụt xuống mức nguy hiểm và **WDT** reset khi chương trình treo — cả hai đều nhằm đảm bảo độ tin cậy; **ADC 10-bit 4 kênh** cho phép đọc 4 cảm biến tương tự với độ phân giải 1024 mức; **Comparator** để so sánh điện áp; khối **Capture/Compare/PWM**; và các bộ **Timer**.

---

## SLIDE 14 — Block Diagram của AVR

### 📖 Kiến thức nền

**Điểm quan trọng nhất của slide này: KIẾN TRÚC HARVARD**

Nhìn kỹ sơ đồ, bạn sẽ thấy **PROGRAM FLASH** và **SRAM** là **hai khối riêng biệt**, mỗi khối có đường bus riêng nối tới CPU. Đây gọi là **kiến trúc Harvard**.

**So sánh hai kiến trúc:**

| | **Von Neumann** | **Harvard** |
|---|---|---|
| Bộ nhớ | **Chung** cho lệnh và dữ liệu | **Tách riêng** lệnh / dữ liệu |
| Bus | Một bus dùng chung | **Hai bus riêng** |
| Tốc độ | Chậm hơn (phải chờ lượt) | **Nhanh hơn** — nạp lệnh và đọc dữ liệu **cùng lúc** |
| Ví dụ | 8085, x86 | **AVR, PIC, ARM Cortex-M** |

**Vì sao Harvard nhanh hơn?** Vì CPU có thể **vừa nạp lệnh tiếp theo, vừa đọc/ghi dữ liệu cho lệnh hiện tại** trong cùng một chu kỳ — không phải xếp hàng chờ. Đây là điều kiện quan trọng để đạt được **1 lệnh/chu kỳ** như RISC yêu cầu (slide 15).

**Các khối trong AVR CPU (khung nét đứt):**
- **Program Counter** — địa chỉ lệnh tiếp theo
- **Stack Pointer** — trỏ đỉnh ngăn xếp (AVR dùng stack trong SRAM → **không giới hạn 8 mức như PIC**)
- **Instruction Register** + **Instruction Decoder** → giải mã lệnh
- **General Purpose Registers** với **X, Y, Z** — đây là 3 **thanh ghi con trỏ 16-bit** đặc biệt, dùng để truy cập bộ nhớ gián tiếp (giống con trỏ trong C)
- **ALU** — khối tính toán
- **Status Register** — chứa các cờ
- **Control Lines** — tín hiệu điều khiển

**Các ngoại vi bên phải:**
- **TWI** = **Two-Wire Interface** = tên gọi khác của **I²C** (Atmel tránh vấn đề bản quyền tên I²C nên đặt tên khác)
- **USART** — truyền nối tiếp
- **SPI** — truyền nối tiếp tốc độ cao
- **Timers/Counters** + **Oscillator**
- **Watchdog Timer** + **Internal Calibrated Oscillator**
- **Interrupt Unit** — quản lý ngắt
- **EEPROM** — lưu dữ liệu không mất khi tắt nguồn
- **MCU CTRL & TIMING** — điều khiển chế độ hoạt động, kết nối chân **RESET**

**Các cổng I/O (4 phía):** PORTA, PORTB, PORTC, PORTD — mỗi cổng có **2 lớp**:
- **PORTx DIGITAL INTERFACE** — logic điều khiển
- **PORTx DRIVERS/BUFFERS** — mạch đệm công suất, thực sự đẩy dòng điện ra chân

**Chân nguồn:** VCC, GND cho phần số; **AVCC, AREF** riêng cho phần ADC (analog) — tách riêng để **giảm nhiễu** từ mạch số sang mạch tương tự.

### ❓ Câu hỏi thầy cô hay hỏi
- *"Vì sao AVCC tách riêng khỏi VCC?"* → Vì mạch số chuyển trạng thái liên tục gây nhiễu lên đường nguồn. ADC cần nguồn sạch để đo chính xác, nên phải cấp nguồn riêng có lọc.
- *"Thanh ghi X, Y, Z dùng làm gì?"* → Là các thanh ghi con trỏ 16-bit, dùng để truy cập bộ nhớ theo địa chỉ động — tương đương con trỏ trong ngôn ngữ C.

### 🎤 Đoạn văn nói
Và đây là ví dụ thứ ba — kiến trúc **AVR**, chính là dòng chip dùng trên bo Arduino.

Sơ đồ này chi tiết hơn hai slide trước, nhưng ta vẫn nhận ra các thành phần quen thuộc. Trong khung nét đứt là **AVR CPU**, gồm **ALU**, **Program Counter**, **Instruction Register** và **Instruction Decoder**, **Status Register**, cùng **General Purpose Registers** với ba thanh ghi con trỏ đặc biệt là X, Y, Z.

Điểm quan trọng nhất em muốn các bạn chú ý ở slide này là: **Program Flash** và **SRAM** được vẽ thành **hai khối riêng biệt, có đường bus riêng**. Đây gọi là **kiến trúc Harvard** — tức bộ nhớ chương trình và bộ nhớ dữ liệu tách rời nhau. Ưu điểm của kiến trúc này là CPU có thể **vừa nạp lệnh tiếp theo, vừa đọc dữ liệu cho lệnh hiện tại trong cùng một chu kỳ**, thay vì phải xếp hàng chờ như kiến trúc von Neumann dùng bus chung. Chính điều này giúp AVR đạt được tốc độ một lệnh trên một chu kỳ — đặc trưng của kiến trúc RISC mà em sắp trình bày.

Về ngoại vi, bên phải có các khối: **TWI** — đây là tên gọi khác của giao tiếp I²C; **USART** và **SPI** để truyền nối tiếp; **Timers/Counters**; **Watchdog Timer**; **Interrupt Unit** quản lý ngắt; và **EEPROM** để lưu dữ liệu không mất khi tắt nguồn.

Bốn phía là các cổng **PORTA đến PORTD**, mỗi cổng có hai lớp: lớp giao tiếp số phía trong và lớp **Drivers/Buffers** phía ngoài — lớp này là mạch đệm công suất, thực sự đẩy dòng điện ra chân.

Cuối cùng, chú ý là chân nguồn cho phần tương tự **AVCC** được tách riêng khỏi nguồn số **VCC** — nhằm giảm nhiễu từ mạch số sang bộ chuyển đổi ADC, giúp phép đo chính xác hơn.

💡 *Nếu thiếu thời gian, nói gộp 3 slide 12-13-14: "Đây là ba ví dụ vi điều khiển thực tế từ ba hãng khác nhau — 8051, PIC và AVR. Tuy khác nhà sản xuất, nhưng cả ba đều tuân theo cùng một mô hình khối ở slide 11: đều có CPU, bộ nhớ chương trình, bộ nhớ dữ liệu, cổng I/O, timer và các khối ngoại vi hỗ trợ."*

---

## SLIDE 15 — RISC

### 📖 Kiến thức nền

**RISC = Reduced Instruction Set Computer** — chiến lược thiết kế CPU dựa trên **lệnh đơn giản, hiệu năng nhanh**.

**Ba đặc điểm trong slide, giải thích sâu:**

**① "RISC is small or reduced set of instructions" — Tập lệnh nhỏ**

Ví dụ minh hoạ: để nhân hai số trong bộ nhớ,
- **CISC** có sẵn 1 lệnh: `MUL [địa chỉ A], [địa chỉ B]`
- **RISC** phải viết 4 lệnh: `LOAD R1,[A]` → `LOAD R2,[B]` → `MUL R1,R2` → `STORE [A],R1`

RISC dùng **kiến trúc Load/Store**: chỉ 2 lệnh LOAD và STORE được phép chạm vào bộ nhớ, mọi phép tính khác **chỉ làm việc trên thanh ghi**.

**② "One Cycle Execution Time" — Mỗi lệnh 1 chu kỳ**

Vì lệnh đơn giản và **có độ dài cố định** (ví dụ AVR: mọi lệnh đều 16 bit), CPU biết chính xác lệnh bắt đầu/kết thúc ở đâu → giải mã nhanh, thực thi trong 1 chu kỳ.

**Lợi ích lớn cho hệ thống nhúng:** thời gian thực thi **dự đoán được** — liên hệ trực tiếp đặc điểm **Real-time constraints** (tính determinism) ở Chương 1!

**③ "Pipelining" — Kỹ thuật quan trọng nhất, cần hiểu kỹ**

**Không pipelining** (tuần tự) — mỗi lệnh mất 3 bước, phải xong hẳn mới sang lệnh sau:

```
Lệnh 1:  [Fetch][Decode][Execute]
Lệnh 2:                          [Fetch][Decode][Execute]
Lệnh 3:                                                   [Fetch]...
→ 3 lệnh mất 9 chu kỳ
```

**Có pipelining** — các giai đoạn **chồng lấn** nhau:

```
Chu kỳ:    1       2        3        4        5
Lệnh 1: [Fetch][Decode][Execute]
Lệnh 2:        [Fetch] [Decode][Execute]
Lệnh 3:                [Fetch] [Decode][Execute]
→ 3 lệnh chỉ mất 5 chu kỳ
```

**Ví von dễ nhớ — dây chuyền giặt đồ:** Trong khi mẻ 1 đang **sấy**, mẻ 2 đã bắt đầu **giặt**. Không cần chờ mẻ 1 xong hoàn toàn mới bắt đầu mẻ 2. Máy giặt và máy sấy chạy **song song**.

**Kết quả:** sau khi pipeline "đầy", CPU hoàn thành **1 lệnh mỗi chu kỳ** dù mỗi lệnh vẫn cần 3 bước.

**Các đặc điểm RISC khác (không có trong slide nhưng nên biết):**
- **Nhiều thanh ghi** hơn CISC → giảm truy cập bộ nhớ chậm
- **Độ dài lệnh cố định** → dễ giải mã, dễ pipelining
- **Ít chế độ địa chỉ** (addressing modes)

**Ví dụ thực tế:** **ARM** (điện thoại, STM32), **AVR** (Arduino), **PIC**, **MIPS**, **RISC-V**

### ❓ Câu hỏi thầy cô hay hỏi
- *"Pipelining có nhược điểm không?"* → Có. Khi gặp **lệnh rẽ nhánh** (if/jump), CPU đã nạp sẵn các lệnh tiếp theo nhưng lại phải nhảy đi chỗ khác → phải **xả pipeline** và nạp lại → mất vài chu kỳ. Gọi là **pipeline hazard**.
- *"Vì sao RISC phù hợp với hệ thống nhúng?"* → Vì đơn giản → ít transistor → **rẻ, ít tốn điện**; và thời gian thực thi **dự đoán được** → đáp ứng real-time.

### 🎤 Đoạn văn nói
Hai slide tiếp theo nói về hai kiến trúc tập lệnh đối lập nhau, bắt đầu với **RISC**.

**RISC** là viết tắt của **Reduced Instruction Set Computer** — máy tính với tập lệnh rút gọn. Đây là một **chiến lược thiết kế CPU** dựa trên các lệnh đơn giản để đạt hiệu năng cao.

Đặc điểm thứ nhất: **tập lệnh nhỏ và đơn giản**. Ví dụ để nhân hai số trong bộ nhớ, kiến trúc CISC có sẵn một lệnh làm hết, còn RISC phải viết bốn lệnh: nạp số thứ nhất vào thanh ghi, nạp số thứ hai, thực hiện phép nhân, rồi lưu kết quả trở lại. RISC dùng kiến trúc gọi là **Load/Store** — chỉ hai lệnh nạp và lưu được phép chạm vào bộ nhớ, còn mọi phép tính khác chỉ làm việc trên thanh ghi.

Đặc điểm thứ hai: mỗi lệnh chỉ thực thi trong **một chu kỳ xung nhịp**. Điều này có được nhờ lệnh đơn giản và có độ dài cố định. Với hệ thống nhúng, đây là lợi thế rất lớn vì thời gian thực thi trở nên **dự đoán được** — đúng như yêu cầu về ràng buộc thời gian thực mà chúng ta đã học ở Chương 1.

Đặc điểm thứ ba là **Pipelining** — kỹ thuật cho phép thực thi **đồng thời nhiều giai đoạn** của các lệnh khác nhau. Em xin giải thích bằng ví dụ: nếu không có pipelining, ba lệnh mỗi lệnh gồm ba bước sẽ mất chín chu kỳ vì phải làm tuần tự. Nhưng với pipelining, trong khi lệnh thứ nhất đang ở bước thực thi, thì lệnh thứ hai đã ở bước giải mã và lệnh thứ ba đã ở bước nạp — nhờ vậy ba lệnh chỉ mất năm chu kỳ.

Cách dễ hình dung nhất là ví như dây chuyền giặt đồ: trong khi mẻ đồ thứ nhất đang sấy thì mẻ thứ hai đã bắt đầu giặt, không cần chờ mẻ một xong hoàn toàn.

Các ví dụ thực tế của kiến trúc RISC gồm **ARM** — dùng trong hầu hết điện thoại thông minh, **AVR** trên Arduino, và **PIC** mà chúng ta vừa xem ở slide trước với chỉ 35 lệnh.

---

## SLIDE 16 — CISC

### 📖 Kiến thức nền

**CISC = Complex Instruction Set Computer** — tập lệnh phức tạp.

**Bối cảnh lịch sử — vì sao CISC ra đời trước?**

Vào những năm 1970-80:
- **Bộ nhớ RAM cực kỳ đắt và ít** → chương trình phải càng **ngắn** càng tốt
- **Trình biên dịch còn sơ khai** → cần CPU có sẵn lệnh mạnh để compiler dễ sinh mã

→ Giải pháp: làm mỗi lệnh **mạnh hơn**, làm được nhiều việc → chương trình ngắn hơn. Đó là CISC.

Sau này khi RAM rẻ đi và compiler thông minh hơn, RISC mới trở nên hợp lý.

**Bốn ý trong slide, giải thích:**

**① "Computers have shorted programs"** → Chương trình ngắn hơn vì mỗi lệnh làm được nhiều việc.

**② "Large number of complex instructions, takes long time to execute"** → Đánh đổi: mỗi lệnh cần **nhiều chu kỳ**. Lệnh CISC thường được thực hiện bằng **microcode** — tức bên trong CPU có một "chương trình con" nhỏ chạy để hoàn thành lệnh phức tạp đó.

**③ "Good performances based on the simplification of program compilers"** → CISC giúp compiler đơn giản hơn vì đã có sẵn lệnh mạnh, không cần compiler tự ghép nhiều lệnh nhỏ.

**④ Hai câu cuối — ĐÂY LÀ MẤU CHỐT PHÂN BIỆT:**
- **CISC Approach:** giảm thiểu **số LỆNH trên mỗi chương trình**
- **RISC Approach:** giảm **số CHU KỲ trên mỗi lệnh**, đánh đổi bằng số lệnh nhiều hơn

**🔑 CÔNG THỨC VÀNG — giải thích trọn vẹn cả hai kiến trúc:**

$$\text{Thời gian chạy} = \frac{\text{Số lệnh}}{\text{Chương trình}} \times \frac{\text{Số chu kỳ}}{\text{Lệnh}} \times \frac{\text{Thời gian}}{\text{Chu kỳ}}$$

- **CISC** tối ưu **thừa số thứ nhất** (giảm số lệnh) — chấp nhận thừa số thứ hai lớn
- **RISC** tối ưu **thừa số thứ hai** (giảm chu kỳ/lệnh về 1) — chấp nhận thừa số thứ nhất lớn

**Cả hai đều nhằm giảm tổng thời gian, chỉ khác cách tiếp cận.**

Nếu thầy cô hỏi "kiến trúc nào tốt hơn?", câu trả lời chuẩn: **không có cái nào tuyệt đối tốt hơn** — tuỳ ứng dụng. RISC thắng ở thiết bị di động/nhúng (tiết kiệm điện, dự đoán được); CISC vẫn mạnh ở máy tính để bàn/server (x86).

**Thực tế hiện đại:** ranh giới đã mờ đi. CPU Intel x86 hiện nay **bên ngoài là CISC** (để tương thích phần mềm cũ) nhưng **bên trong dịch lệnh CISC thành các micro-op giống RISC** rồi mới thực thi.

**Bảng so sánh tổng kết:**

| Tiêu chí | RISC | CISC |
|---|---|---|
| Số lệnh | Ít (35–200) | Nhiều (hàng nghìn) |
| Độ dài lệnh | **Cố định** | **Thay đổi** |
| Chu kỳ/lệnh | 1 | Nhiều |
| Số lệnh/chương trình | Nhiều | Ít |
| Số thanh ghi | Nhiều | Ít |
| Truy cập bộ nhớ | Chỉ LOAD/STORE | Nhiều lệnh truy cập được |
| Pipelining | Dễ | Khó |
| Tiêu thụ điện | Thấp | Cao |
| Ví dụ | ARM, AVR, PIC, RISC-V | x86, 8051 |

### 🎤 Đoạn văn nói
Slide này nói về kiến trúc đối lập: **CISC** — **Complex Instruction Set Computer**, máy tính với tập lệnh phức tạp.

Trước hết, xin nói qua về bối cảnh lịch sử: CISC ra đời trước RISC, vào thời kỳ mà bộ nhớ RAM còn rất đắt và rất ít. Khi đó, mục tiêu quan trọng nhất là làm sao cho chương trình **càng ngắn càng tốt** để tiết kiệm bộ nhớ. Giải pháp là làm mỗi lệnh mạnh hơn, làm được nhiều việc hơn.

Đặc điểm của CISC theo slide: thứ nhất, chương trình viết ra **ngắn hơn**. Thứ hai, CISC có **số lượng lớn các lệnh phức tạp**, và mỗi lệnh **mất nhiều thời gian hơn để thực thi**. Thứ ba, CISC đạt hiệu năng tốt dựa trên việc **đơn giản hoá trình biên dịch** — vì đã có sẵn lệnh mạnh nên compiler không cần tự ghép nhiều lệnh nhỏ lại.

Và điểm mấu chốt để phân biệt hai kiến trúc nằm ở hai câu cuối slide: **cách tiếp cận của CISC là giảm thiểu SỐ LỆNH trên mỗi chương trình**; trong khi **RISC làm điều ngược lại — giảm SỐ CHU KỲ trên mỗi lệnh, đánh đổi bằng việc chương trình phải dùng nhiều lệnh hơn**.

Để hiểu trọn vẹn, ta có thể nhìn vào công thức tính thời gian chạy chương trình: thời gian bằng **số lệnh trên chương trình**, nhân với **số chu kỳ trên mỗi lệnh**, nhân với **thời gian mỗi chu kỳ**. CISC tối ưu thừa số thứ nhất, còn RISC tối ưu thừa số thứ hai. Cả hai đều nhằm giảm tổng thời gian, chỉ khác cách tiếp cận.

Vì vậy, không có kiến trúc nào tuyệt đối tốt hơn — tuỳ vào ứng dụng. RISC chiếm ưu thế trong thiết bị di động và hệ thống nhúng nhờ tiết kiệm điện và thời gian dự đoán được, còn CISC vẫn mạnh trong máy tính để bàn và máy chủ.

**🔄 Câu chuyển:** Như vậy em đã trình bày xong phần về bộ xử lý. Tiếp theo, em xin sang phần cuối cùng — nơi lưu trữ chương trình và dữ liệu, đó là bộ nhớ.

---
---

# PHẦN 3 — MEMORY (Slide 17–35)

## SLIDE 17 — Tổng quan các loại bộ nhớ

### 📖 Kiến thức nền

**Trục phân loại cốt lõi: VOLATILE hay NON-VOLATILE?**

Đây là câu hỏi quyết định mọi thứ trong sơ đồ cây này:

| | **Volatile (bay hơi)** | **Non-volatile (không bay hơi)** |
|---|---|---|
| Mất điện | **Mất sạch dữ liệu** | **Giữ nguyên dữ liệu** |
| Loại | RAM (SRAM, DRAM) | ROM, PROM, EPROM, EEPROM, Flash |
| Tốc độ ghi | **Rất nhanh** | Chậm hơn nhiều |
| Số lần ghi | **Vô hạn** | **Có giới hạn** (10K–100K lần) |
| Dùng để | Lưu **biến** khi chạy | Lưu **chương trình**, cài đặt |

**Vì sao có nhánh HYBRID ở giữa?**

Nhóm lai mang **đặc điểm của cả hai bên**:
- Giống **ROM**: giữ dữ liệu khi mất điện (non-volatile)
- Giống **RAM**: ghi/xoá được nhiều lần trong lúc hệ thống đang chạy

Nhưng vẫn không thay thế được RAM vì: **ghi chậm hơn nhiều** và **số lần ghi có giới hạn**.

**Vì sao EEPROM xuất hiện ở CẢ nhánh Hybrid?** Vì EEPROM ban đầu thuộc họ ROM (đọc là chính), nhưng do có thể xoá/ghi bằng điện ngay trong mạch nên được xếp thêm vào nhóm lai.

**NVRAM là gì?** = Non-Volatile RAM. Thường là **SRAM + pin nhỏ (battery-backed)** hoặc SRAM ghép với EEPROM. Có tốc độ ghi nhanh như RAM nhưng không mất dữ liệu — dùng cho đồng hồ thời gian thực (RTC) hoặc lưu log quan trọng.

**Một hệ thống nhúng điển hình dùng ĐỒNG THỜI nhiều loại:**
- **Flash** → lưu chương trình (firmware)
- **SRAM** → chạy chương trình, lưu biến
- **EEPROM** → lưu cài đặt người dùng (nhiệt độ đặt, mật khẩu WiFi)

### 🎤 Đoạn văn nói
Slide này đưa ra bức tranh tổng thể về các loại bộ nhớ dùng trong hệ thống nhúng. Từ gốc **Memory**, ta chia thành **ba nhánh chính**.

Nhánh thứ nhất là **RAM**, gồm **DRAM** và **SRAM**. Nhánh thứ ba là **ROM**, gồm **EPROM**, **PROM** và **Masked ROM**. Và ở giữa là nhánh **Hybrid** — bộ nhớ lai, gồm **NVRAM**, **Flash** và **EEPROM**.

Tiêu chí phân loại cốt lõi ở đây là: bộ nhớ có **giữ được dữ liệu khi mất điện hay không**. RAM thuộc loại **volatile** — mất điện là mất sạch dữ liệu, nhưng bù lại ghi rất nhanh và ghi được vô hạn lần. Ngược lại, ROM thuộc loại **non-volatile** — giữ nguyên dữ liệu khi mất điện, nhưng ghi chậm và số lần ghi có giới hạn.

Sở dĩ có nhóm **lai** ở giữa là vì các loại bộ nhớ này mang đặc điểm của cả hai bên: **vừa ghi xoá được ngay trong lúc hệ thống chạy như RAM, lại vừa giữ được dữ liệu khi mất điện như ROM**. Tuy nhiên chúng vẫn không thay thế được RAM vì tốc độ ghi chậm hơn nhiều và số lần ghi bị giới hạn.

Trong thực tế, một hệ thống nhúng thường dùng **đồng thời cả ba loại**: Flash để lưu chương trình, SRAM để chạy chương trình và lưu biến, còn EEPROM để lưu các cài đặt của người dùng.

Trong các slide tiếp theo, em sẽ đi lần lượt từ nhánh ROM, sang RAM, rồi tới bộ nhớ lai.

---

## SLIDE 18 — ROM

### 📖 Kiến thức nền

**Loại ROM ở slide này là "Masked ROM"** (thấy trong cây phân loại slide 17).

**"Masked" nghĩa là gì?** Trong quá trình sản xuất chip, người ta dùng các tấm **mặt nạ quang khắc (photomask)** để in mạch lên silicon. Dữ liệu của ROM được **khắc luôn vào mặt nạ** → nội dung được quyết định **ngay từ khâu chế tạo**, không thể thay đổi được nữa.

**Ưu — nhược điểm:**

| Ưu điểm | Nhược điểm |
|---|---|
| **Rẻ nhất** khi sản xuất số lượng lớn (hàng triệu chip) | **Không sửa được** — sai một chút là bỏ cả lô |
| **Bền nhất**, không lo mất dữ liệu | Chi phí làm mặt nạ ban đầu **rất đắt** |
| Mật độ cao, chiếm ít diện tích | Thời gian sản xuất lâu (vài tuần) |

→ Chỉ dùng cho sản phẩm đã **hoàn thiện 100%** và sản xuất số lượng cực lớn (đồ chơi, điều khiển TV...).

**"Bootstrap" — vì sao lại có tên lạ vậy?**

Xuất phát từ thành ngữ tiếng Anh *"pull oneself up by one's bootstraps"* — tự kéo dây giày để nhấc mình lên. Ý nói làm điều tưởng như bất khả thi bằng chính sức mình.

**Nghịch lý khởi động:** Khi bật nguồn, CPU cần **chương trình** để biết phải làm gì. Nhưng chương trình lại nằm trong bộ nhớ. Vậy ai nạp chương trình vào? Nếu chỉ có RAM (trống rỗng khi bật máy) → **bế tắc**.

**Giải pháp:** ROM đã có sẵn code từ trước. CPU khi reset sẽ **luôn nhảy tới một địa chỉ cố định** (thường là 0x0000) — nơi đặt ROM — và bắt đầu chạy từ đó. Chương trình này gọi là **bootloader/bootstrap**, có nhiệm vụ khởi tạo phần cứng rồi nạp hệ điều hành hoặc chương trình chính.

Từ "boot" trong "khởi động máy tính" chính là rút gọn của **bootstrap** này.

### ❓ Câu hỏi thầy cô hay hỏi
- *"ROM có thực sự không ghi được không?"* → Masked ROM thì đúng là không. Nhưng "ROM" ngày nay thường được dùng như tên gọi chung cho cả họ (kể cả Flash) — thực tế Flash ghi được.
- *"Vì sao gọi là bootstrap?"* → Từ thành ngữ "tự kéo dây giày nhấc mình lên" — máy tính tự khởi động chính nó bằng đoạn code có sẵn trong ROM.

### 🎤 Đoạn văn nói
**ROM** là viết tắt của **Read Only Memory** — bộ nhớ chỉ đọc.

Các đặc điểm chính: thứ nhất, đây là loại bộ nhớ mà ta **chỉ có thể đọc, không thể ghi vào**. Thứ hai, ROM là bộ nhớ **non-volatile** — tức **không mất dữ liệu khi mất điện**. Thứ ba, thông tin được lưu **vĩnh viễn ngay từ lúc sản xuất** — cụ thể là dữ liệu được khắc thẳng vào mặt nạ quang khắc trong quá trình chế tạo chip, nên không thể thay đổi được nữa.

Chính vì vậy, ROM chỉ phù hợp cho những sản phẩm đã hoàn thiện hoàn toàn và sản xuất với số lượng cực lớn — khi đó giá thành trên mỗi chip là rẻ nhất.

Và công dụng quan trọng nhất: ROM lưu trữ các **lệnh cần thiết để khởi động máy tính** — thao tác này được gọi là **bootstrap**.

Em xin giải thích thêm về khái niệm này. Khi bật nguồn, CPU cần có chương trình để biết phải làm gì, nhưng chương trình lại nằm trong bộ nhớ. Nếu hệ thống chỉ có RAM — vốn trống rỗng khi vừa bật máy — thì sẽ rơi vào bế tắc. ROM giải quyết vấn đề này: nó đã có sẵn code từ trước, và CPU khi reset sẽ luôn nhảy tới một địa chỉ cố định nơi đặt ROM để bắt đầu chạy. Từ "boot" trong "khởi động máy tính" mà chúng ta hay dùng chính là rút gọn của chữ **bootstrap** này.

---

## SLIDE 19 — PROM

### 📖 Kiến thức nền

**PROM giải quyết vấn đề gì của ROM?** ROM phải đặt hàng nhà máy khắc sẵn → không phù hợp cho **số lượng nhỏ** hoặc **giai đoạn thử nghiệm**. PROM cho phép **người dùng tự ghi**.

**Nguyên lý cầu chì (fuse) — giải thích chi tiết:**

Chip PROM xuất xưởng với **tất cả các cầu chì còn nguyên** — mọi bit đều đọc ra là 1 (hoặc 0 tuỳ thiết kế).

Khi lập trình, máy nạp đưa **dòng điện lớn** vào những vị trí cần thay đổi → cầu chì **nóng chảy và đứt** → bit đó vĩnh viễn đổi thành 0.

```
Trước khi nạp:  1 1 1 1 1 1 1 1   (mọi cầu chì còn nguyên)
Sau khi nạp:    1 0 1 1 0 0 1 0   (các cầu chì bị đốt đứt = 0)
                  ↑     ↑ ↑   ↑
              đã đốt, KHÔNG nối lại được
```

**Vì sao không xoá được?** Vì đây là thay đổi **vật lý không thể đảo ngược** — cầu chì đã đứt thì không có cách nào nối lại.

**Thuật ngữ chuyên ngành:** PROM còn được gọi là **OTP** — **One Time Programmable** (lập trình một lần). Bạn sẽ thấy chữ "OTP" trên datasheet của nhiều vi điều khiển giá rẻ.

**Ưu — nhược:**

| Ưu điểm | Nhược điểm |
|---|---|
| Người dùng tự ghi được, không cần đặt nhà máy | **Sai là bỏ chip** — không sửa được |
| Rẻ hơn EPROM/EEPROM | Không dùng được cho giai đoạn phát triển |
| Phù hợp sản xuất số lượng vừa | Lãng phí nếu firmware cần cập nhật |

### 🎤 Đoạn văn nói
**PROM** — **Programmable Read Only Memory**, tức ROM lập trình được.

PROM ra đời để giải quyết một hạn chế của ROM: ROM phải đặt hàng nhà máy khắc sẵn nên không phù hợp cho sản xuất số lượng nhỏ hay giai đoạn thử nghiệm. Với PROM, **người dùng có thể tự ghi dữ liệu vào — nhưng chỉ MỘT lần duy nhất**. Người dùng mua một con PROM trắng, rồi dùng một **máy nạp chuyên dụng** để ghi nội dung mong muốn vào.

Về nguyên lý hoạt động: bên trong chip PROM có các **cầu chì nhỏ**. Khi xuất xưởng, tất cả cầu chì đều còn nguyên. Trong quá trình lập trình, máy nạp sẽ đưa dòng điện lớn vào những vị trí cần thay đổi, khiến các cầu chì đó **nóng chảy và đứt**.

Và vì đây là một thay đổi **vật lý không thể đảo ngược** — cầu chì đã đứt thì không có cách nào nối lại được — nên PROM **chỉ lập trình được một lần và không thể xoá**. Trong tài liệu kỹ thuật, loại bộ nhớ này còn được gọi tắt là **OTP**, tức One Time Programmable.

---

## SLIDE 20 — EPROM

### 📖 Kiến thức nền

**EPROM giải quyết vấn đề gì của PROM?** PROM sai là bỏ chip — quá lãng phí cho giai đoạn phát triển. EPROM cho phép **xoá đi ghi lại**.

**Nguyên lý cổng nổi (floating gate) — công nghệ nền tảng của mọi bộ nhớ flash hiện đại:**

Transistor EPROM có **hai cổng** thay vì một:

```
        Control Gate  ← điện cực điều khiển (nối ra ngoài)
     ═══════════════
        lớp cách điện SiO₂
     ┌───────────────┐
     │ FLOATING GATE │  ← cổng NỔI: bị bao quanh hoàn toàn
     └───────────────┘     bởi lớp cách điện, KHÔNG nối đi đâu cả
        lớp cách điện SiO₂
     ═══════════════
     Source ────── Drain
```

**Ghi dữ liệu:** đặt điện áp cao → electron có đủ năng lượng **xuyên qua lớp cách điện** vào floating gate → bị **mắc kẹt** ở đó.

**Vì sao giữ được >10 năm?** Vì floating gate **bị bao quanh hoàn toàn bởi lớp cách điện SiO₂** — như slide viết: *"the charge has no leakage path"* — không có đường thoát. Electron bị nhốt vĩnh viễn (về mặt thực tế).

**Xoá bằng tia UV — nguyên lý:** Tia cực tím có **năng lượng photon cao**. Khi chiếu vào, electron trong floating gate **hấp thụ năng lượng** đủ lớn để **vượt qua rào cản cách điện** và thoát ra → chip trở về trạng thái trắng.

**Vì sao mất tới 40 phút?** Vì phải chiếu đủ lâu để **toàn bộ** electron ở **mọi ô nhớ** đều thoát hết.

**Vì sao chip EPROM có cửa sổ thạch anh?**

Nhìn hình trong slide, bạn thấy một **ô tròn trong suốt** trên lưng chip. Đó là **cửa sổ thạch anh (quartz window)** — vì:
- Nhựa/gốm thường **chặn tia UV**
- Thạch anh **cho tia UV đi qua**

→ Không có cửa sổ này thì không xoá được.

⚠️ **Lưu ý thực tế:** sau khi nạp xong, phải **dán băng keo đen che cửa sổ** — nếu không, ánh sáng mặt trời (có chứa UV) có thể **xoá dần dữ liệu** sau vài năm.

**Nhược điểm lớn của EPROM:**
- Phải **tháo chip ra khỏi mạch** để xoá → rất bất tiện
- Chờ **40 phút** mỗi lần xoá
- Cần thiết bị đèn UV chuyên dụng
- **Xoá là xoá TOÀN BỘ chip**, không xoá riêng lẻ được

→ Chính những nhược điểm này dẫn tới EEPROM ở slide sau.

### 🎤 Đoạn văn nói
**EPROM** — **Erasable and Programmable Read Only Memory**, tức là ROM có thể **xoá và lập trình lại được**.

Đây là bước tiến so với PROM, vì với PROM thì ghi sai là phải bỏ chip — quá lãng phí trong giai đoạn phát triển sản phẩm.

EPROM có thể được xoá bằng cách **chiếu tia cực tím — tia UV** vào chip, trong khoảng thời gian lên tới **40 phút**.

Về nguyên lý hoạt động: trong quá trình lập trình, một **điện tích được giữ lại trong vùng cổng cách điện** — thuật ngữ chuyên môn gọi là **cổng nổi**, tức một cổng bị bao quanh hoàn toàn bởi lớp cách điện và không nối ra đâu cả. Electron được đẩy vào đó rồi bị mắc kẹt lại. Vì **điện tích này không có đường rò rỉ**, nên dữ liệu có thể được lưu giữ trong **hơn 10 năm**.

Còn khi chiếu tia UV, các electron hấp thụ đủ năng lượng để vượt qua lớp cách điện và thoát ra ngoài, đưa chip trở về trạng thái trắng.

Các bạn có thể thấy trong hình, chip EPROM có một **ô tròn trong suốt** ở lưng — đó là **cửa sổ bằng thạch anh**, vì vỏ nhựa thông thường sẽ chặn tia UV, còn thạch anh thì cho tia UV đi qua. Trong thực tế, sau khi nạp xong người ta phải dán băng keo đen che cửa sổ này lại, nếu không ánh sáng mặt trời có thể xoá dần dữ liệu sau vài năm.

Tuy nhiên EPROM vẫn còn nhiều bất tiện: phải **tháo chip ra khỏi mạch** để xoá, phải chờ **40 phút**, cần thiết bị đèn UV chuyên dụng, và mỗi lần xoá là **xoá toàn bộ chip**. Chính những hạn chế này dẫn tới sự ra đời của EEPROM ở slide tiếp theo.

---

## SLIDE 21 — EEPROM

### 📖 Kiến thức nền

**EEPROM giải quyết TẤT CẢ nhược điểm của EPROM:**

| Vấn đề của EPROM | EEPROM giải quyết thế nào |
|---|---|
| Phải tháo chip ra khỏi mạch | **Xoá/ghi ngay trong mạch** (in-circuit) |
| Chờ 40 phút | Chỉ **4–10 mili-giây** |
| Cần đèn UV | Chỉ cần **điện áp** |
| Xoá toàn bộ chip | **Xoá từng byte riêng lẻ** |

**Nguyên lý xoá bằng điện — hiệu ứng đường hầm Fowler-Nordheim:**

Vẫn dùng floating gate như EPROM, nhưng lớp cách điện được làm **mỏng hơn nhiều**. Khi đặt điện áp đủ cao, electron có thể **"chui hầm" (tunneling)** xuyên qua lớp cách điện mỏng này theo cả hai chiều — vào để ghi, ra để xoá. Đây là hiệu ứng lượng tử.

**"Khoảng 10,000 lần" — vì sao có giới hạn? (ENDURANCE)**

Mỗi lần electron xuyên qua lớp cách điện, nó **làm hỏng cấu trúc** của lớp SiO₂ một chút — giống như đâm kim qua tờ giấy nhiều lần. Sau hàng nghìn lần, lớp cách điện bị **hư hại đến mức không giữ được electron nữa** → ô nhớ chết.

Thuật ngữ chuyên ngành: **endurance** (độ bền ghi/xoá).

⚠️ **Hệ quả thực tế cực kỳ quan trọng cho lập trình viên nhúng:**

```c
// ❌ CODE SAI — sẽ phá hỏng EEPROM!
while(1) {
    doNhietDo();
    EEPROM_write(0, nhietDo);   // ghi liên tục
    delay(100);                  // 10 lần/giây
}
// → 10 lần/giây × 3600 giây = 36,000 lần/giờ
// → EEPROM CHẾT sau chưa tới 1 giờ!
```

```c
// ✅ CODE ĐÚNG — chỉ ghi khi thực sự cần
if (giaTriMoi != giaTriCu) {
    EEPROM_write(0, giaTriMoi);  // chỉ ghi khi thay đổi
    giaTriCu = giaTriMoi;
}
```

Kỹ thuật chuyên nghiệp hơn gọi là **wear leveling** — luân phiên ghi vào nhiều vị trí khác nhau để phân tán số lần ghi.

**"4 đến 10 ms" — nhanh hay chậm?** So sánh:
- Ghi RAM: vài **nano-giây**
- Ghi EEPROM: 4–10 **mili-giây** → **chậm hơn khoảng 1 TRIỆU lần!**

→ Đây là lý do EEPROM **không thể thay thế RAM**, chỉ dùng lưu dữ liệu ít thay đổi.

**Ứng dụng điển hình:** lưu cài đặt người dùng (nhiệt độ đặt cho máy lạnh, mật khẩu WiFi, số lần sử dụng, hiệu chuẩn cảm biến).

### ❓ Câu hỏi thầy cô hay hỏi
- *"Vì sao EEPROM chỉ ghi được 10,000 lần?"* → Mỗi lần electron xuyên qua lớp cách điện làm hỏng cấu trúc của nó một chút; sau nhiều lần thì không giữ được điện tích nữa.
- *"Nếu cần ghi liên tục thì làm sao?"* → Dùng RAM để ghi liên tục, chỉ lưu vào EEPROM khi cần thiết (ví dụ lúc sắp mất điện, hoặc khi giá trị thực sự thay đổi).

### 🎤 Đoạn văn nói
**EEPROM** — **Electrically Erasable and Programmable Read Only Memory** — thêm một chữ E, nghĩa là xoá bằng **điện**.

Đây là bước tiến khắc phục toàn bộ nhược điểm của EPROM. EEPROM được **lập trình và xoá hoàn toàn bằng điện**, nên không cần đèn UV, và quan trọng là **không cần tháo chip ra khỏi mạch**.

Về thông số: EEPROM có thể xoá và ghi lại khoảng **mười nghìn lần**; mỗi thao tác xoá hoặc ghi mất khoảng **4 đến 10 mili-giây**. Và ưu điểm lớn nhất: **bất kỳ vị trí nào cũng có thể được xoá và ghi một cách riêng lẻ** — khác với EPROM phải xoá toàn bộ chip cùng lúc.

Em muốn nhấn mạnh hai con số này vì chúng có ý nghĩa thực tế rất quan trọng khi lập trình.

Thứ nhất là giới hạn **mười nghìn lần ghi**. Nguyên nhân là mỗi lần electron xuyên qua lớp cách điện, nó làm hỏng cấu trúc lớp đó một chút, và sau nhiều lần thì ô nhớ không giữ được dữ liệu nữa. Hệ quả là nếu ta viết chương trình ghi vào EEPROM liên tục, chẳng hạn mười lần mỗi giây, thì chỉ sau chưa tới một giờ là EEPROM sẽ hỏng. Vì vậy nguyên tắc là **chỉ ghi khi giá trị thực sự thay đổi**.

Thứ hai là tốc độ **4 đến 10 mili-giây**. Nghe có vẻ nhanh, nhưng so với RAM chỉ mất vài nano-giây thì EEPROM **chậm hơn khoảng một triệu lần**. Đây chính là lý do EEPROM không thể thay thế RAM, mà chỉ dùng để lưu những dữ liệu ít thay đổi như cài đặt của người dùng.

💡 *Mạch nói xuyên suốt 4 slide 18-21: ROM → PROM → EPROM → EEPROM là một chuỗi tiến hoá, mỗi bước giải quyết một hạn chế của bước trước.*

---

## SLIDE 22 — RAM tổng quan

### 📖 Kiến thức nền

**"Random Access" nghĩa là gì? — Hay bị hiểu nhầm!**

**KHÔNG phải** "truy cập lung tung/ngẫu nhiên". Ý nghĩa thật là: **truy cập bất kỳ ô nhớ nào cũng mất THỜI GIAN NHƯ NHAU**.

**Đối lập với gì?** Với **Sequential Access** (truy cập tuần tự) — như băng từ cassette: muốn nghe bài số 10 phải tua qua 9 bài trước.

| | Random Access | Sequential Access |
|---|---|---|
| Ví dụ | RAM, ROM | Băng từ, băng cassette |
| Truy cập ô cuối | Nhanh như ô đầu | Phải đi qua toàn bộ |

💡 Lưu ý: theo định nghĩa này thì **ROM cũng là "random access"**, nhưng tên gọi RAM đã được dùng theo thói quen để chỉ bộ nhớ đọc-ghi.

**Hai loại RAM sẽ so sánh ở 2 slide sau:**
- **SRAM** = **Static** RAM — "tĩnh" vì dữ liệu **đứng yên**, không cần làm mới
- **DRAM** = **Dynamic** RAM — "động" vì dữ liệu **liên tục suy giảm**, phải làm mới liên tục

### 🎤 Đoạn văn nói
Chuyển sang nhánh thứ hai: **RAM — Random Access Memory**, bộ nhớ truy cập ngẫu nhiên.

Em xin làm rõ thuật ngữ "truy cập ngẫu nhiên" vì đây là khái niệm hay bị hiểu nhầm. Nó **không có nghĩa là truy cập lung tung**, mà nghĩa là **truy cập bất kỳ ô nhớ nào cũng mất thời gian như nhau**. Khái niệm này đối lập với truy cập tuần tự — như băng từ cassette, muốn nghe bài thứ mười thì phải tua qua chín bài trước đó.

RAM được chia thành hai loại chính: **Static RAM**, viết tắt là **SRAM**, và **Dynamic RAM**, viết tắt là **DRAM**. Chữ "tĩnh" và "động" ở đây nói về việc dữ liệu có cần được làm mới liên tục hay không — SRAM thì dữ liệu đứng yên, còn DRAM thì dữ liệu liên tục suy giảm nên phải làm mới. Hai slide tiếp theo sẽ so sánh chi tiết đặc điểm của từng loại.

---

## SLIDE 23 — Đặc điểm của SRAM

### 📖 Kiến thức nền

**Sơ đồ mạch trong slide: ô nhớ SRAM 6 transistor (6T cell)**

```
        WL (Word Line - chọn hàng)
         │
    ┌────┴────┐
   M5         M6      ← 2 transistor "cổng truy cập"
    │          │
    ├──[M2/M1]─┤      ← 2 cặp inverter nối chéo nhau
    │  [M4/M3] │        (M1,M2 và M3,M4)
   Q̄          Q       ← 2 điểm lưu trạng thái (đối nghịch)
    │          │
   BL̄         BL      ← Bit Line (đường dữ liệu)
```

**Nguyên lý — mạch chốt bistable:** Hai cổng đảo (inverter) nối **chéo** nhau tạo thành vòng phản hồi:
- Nếu Q = 1 → inverter đẩy Q̄ = 0 → inverter kia lại củng cố Q = 1
- Trạng thái **tự duy trì mãi mãi** miễn là còn điện

**→ Đây là lý do "No need to refresh" và "Long life"** — mạch tự giữ trạng thái, không cần ai làm mới.

**Giải thích từng đặc điểm trong slide:**

| Đặc điểm | Nguyên nhân sâu xa |
|---|---|
| **Long life** | Mạch chốt tự duy trì trạng thái |
| **No need to refresh** | Không dùng tụ điện → không rò rỉ điện tích |
| **Faster** | Đọc ra tín hiệu **mạnh, rõ ràng** ngay lập tức — không phải "dò" điện tích yếu như DRAM |
| **Used as cache memory** | Vì nhanh → dùng làm bộ đệm giữa CPU và RAM chính |
| **Large size** | **6 transistor** cho mỗi 1 bit → tốn diện tích |
| **Expensive** | Diện tích lớn → mỗi wafer silicon làm được ít chip → đắt |
| **High power consumption** | 6 transistor luôn có dòng rò; nhiều transistor = nhiều dòng rò |

**Cache là gì và vì sao cần?**

Vấn đề: **CPU nhanh hơn RAM rất nhiều lần**. CPU phải "ngồi chờ" RAM → lãng phí.

Giải pháp: đặt một lớp SRAM nhỏ nhưng cực nhanh **ngay cạnh CPU**, chứa những dữ liệu **hay dùng nhất**.

```
CPU  ←→  Cache (SRAM)  ←→  RAM chính (DRAM)  ←→  Ổ cứng
      1 chu kỳ      ~50 chu kỳ         ~1 triệu chu kỳ
      Rất nhỏ (KB)   Vừa (GB)           Rất lớn (TB)
      Rất đắt/byte                       Rất rẻ/byte
```

Đây gọi là **phân cấp bộ nhớ (memory hierarchy)** — càng gần CPU thì càng nhanh, càng nhỏ, càng đắt.

**Trong vi điều khiển:** SRAM chính là **RAM chính** luôn (không phải cache), vì MCU chỉ cần vài KB — dùng SRAM cho nhanh và đơn giản, không cần mạch refresh.

### 🎤 Đoạn văn nói
Slide này liệt kê các đặc điểm của **SRAM — RAM tĩnh**.

Về ưu điểm: **tuổi thọ dữ liệu dài**; **không cần refresh** — tức không cần làm tươi lại dữ liệu liên tục; **tốc độ nhanh hơn**; và chính vì nhanh nên SRAM thường được **dùng làm bộ nhớ cache**.

Về nhược điểm: **kích thước lớn**, **giá thành đắt**, và **tiêu thụ điện năng cao**.

Sơ đồ mạch bên phải giải thích nguyên nhân của tất cả các đặc điểm trên. Các bạn có thể đếm được **sáu transistor** từ M1 đến M6 — đó là số transistor cần thiết để lưu **chỉ một bit** dữ liệu. Trong đó, bốn transistor ở giữa tạo thành **hai cổng đảo nối chéo nhau**, hình thành một mạch chốt tự duy trì trạng thái: nếu điểm Q đang là 1 thì mạch sẽ liên tục củng cố để nó giữ nguyên là 1, chừng nào còn cấp điện.

Chính cơ chế tự duy trì này là lý do SRAM **không cần refresh** và có **tuổi thọ dữ liệu dài**. Nó cũng là lý do SRAM **nhanh**, vì khi đọc, tín hiệu xuất ra mạnh và rõ ràng ngay lập tức.

Nhưng đổi lại, việc cần tới sáu transistor cho mỗi bit khiến SRAM **chiếm nhiều diện tích**, do đó **đắt tiền** và **tiêu thụ nhiều điện** hơn.

Về ứng dụng làm bộ nhớ cache: vấn đề đặt ra là CPU chạy nhanh hơn RAM chính rất nhiều lần, nên CPU thường phải ngồi chờ. Giải pháp là đặt một lớp SRAM nhỏ nhưng cực nhanh ngay cạnh CPU để chứa những dữ liệu hay dùng nhất. Đây gọi là **phân cấp bộ nhớ**: càng gần CPU thì càng nhanh, càng nhỏ và càng đắt.

Riêng trong vi điều khiển, do chỉ cần vài kilobyte bộ nhớ, người ta dùng luôn SRAM làm RAM chính để đơn giản hoá thiết kế, không cần mạch refresh.

---

## SLIDE 24 — Đặc điểm của DRAM

### 📖 Kiến thức nền

**Sơ đồ mạch trong slide: ô nhớ DRAM 1T1C (1 transistor + 1 tụ điện)**

```
   wordline ──┬──[Transistor]──── bitline
              │
            ═╪═  Tụ điện
              │
             GND

   Bit '1' = tụ TÍCH ĐIỆN (dấu +++ trong slide)
   Bit '0' = tụ KHÔNG tích điện
```

So sánh trực quan: **DRAM 1T1C vs SRAM 6T** → DRAM chỉ cần **1 transistor + 1 tụ**, nhỏ hơn nhiều.

**Vì sao phải REFRESH? — Vấn đề rò rỉ điện tích**

Tụ điện trong DRAM **cực kỳ nhỏ** (cỡ femtofarad). Điện tích trong nó **rò rỉ dần** qua transistor và chất nền, nên sau khoảng **64 mili-giây** dữ liệu sẽ mất.

**Cơ chế refresh:** mạch điều khiển phải **đọc từng hàng và ghi lại** giá trị đó liên tục — như "tiếp nước" cho một cái xô bị rò.

**Hệ quả của refresh:**
- **Tốn điện năng** ngay cả khi không ai truy cập
- **Chậm hơn** — trong lúc đang refresh, CPU **không truy cập được** ô nhớ đó, phải chờ
- Cần **mạch điều khiển refresh** phức tạp (thường tích hợp trong memory controller)

**Vì sao DRAM chậm hơn SRAM? — Hai nguyên nhân:**

**① Tín hiệu yếu, phải "dò":** Điện tích trên tụ rất nhỏ. Khi đọc, mạch phải dùng **sense amplifier** để khuếch đại tín hiệu yếu này lên → mất thời gian. SRAM thì tín hiệu ra mạnh sẵn.

**② Đọc là phá huỷ (destructive read):** Khi đọc DRAM, điện tích trên tụ **bị xả ra** → sau mỗi lần đọc phải **ghi lại** giá trị vừa đọc. Thao tác thêm này làm chậm.

**③ Chờ refresh:** như đã nói ở trên.

**Bảng so sánh tổng kết SRAM vs DRAM:**

| Tiêu chí | SRAM | DRAM |
|---|---|---|
| Cấu trúc 1 bit | 6 transistor | 1 transistor + 1 tụ |
| Refresh | **Không cần** | **Cần** (~64ms) |
| Tốc độ | **Nhanh** | Chậm hơn |
| Mật độ | Thấp | **Cao** |
| Giá/bit | **Đắt** | **Rẻ** |
| Điện năng khi chạy | Cao | Thấp hơn |
| Dùng làm | **Cache**, RAM của MCU | **RAM chính** của máy tính |

### ❓ Câu hỏi thầy cô hay hỏi
- *"Vì sao máy tính dùng DRAM mà không dùng SRAM cho RAM chính?"* → Vì cần dung lượng lớn (nhiều GB). Nếu dùng SRAM thì chip sẽ quá to và quá đắt — có thể đắt gấp hàng chục lần.
- *"Refresh có làm mất dữ liệu không?"* → Không. Refresh chính là đọc rồi ghi lại đúng giá trị cũ, nhằm nạp lại điện tích cho tụ.

### 🎤 Đoạn văn nói
Ngược lại là **DRAM — RAM động**, với các đặc điểm gần như đối lập hoàn toàn.

Về nhược điểm: **tuổi thọ dữ liệu ngắn**; **cần được refresh liên tục**; và **chậm hơn so với SRAM**. Về ưu điểm: **kích thước nhỏ gọn hơn**, **giá rẻ hơn**, và **tiêu thụ ít điện năng hơn**. Chính vì vậy, DRAM được **dùng làm RAM chính** của hệ thống.

Sơ đồ bên dưới giải thích tất cả. Một ô nhớ DRAM chỉ cần **một transistor và một tụ điện** — so với sáu transistor của SRAM thì nhỏ gọn hơn rất nhiều. Bit 1 được biểu diễn bằng tụ điện tích điện, như dấu cộng trong hình bên trái; còn bit 0 là tụ không tích điện, như hình bên phải.

Nhưng chính cấu trúc dùng tụ điện này lại gây ra nhược điểm. Tụ điện trong DRAM cực kỳ nhỏ, và điện tích trong nó **rò rỉ dần** — chỉ sau khoảng 64 mili-giây là dữ liệu sẽ mất. Vì vậy mạch điều khiển phải liên tục **đọc từng hàng rồi ghi lại** để nạp lại điện tích, giống như liên tục tiếp nước cho một cái xô bị rò. Đó chính là quá trình **refresh**.

Việc phải refresh gây ra hai hệ quả: thứ nhất là **tốn điện** ngay cả khi không ai truy cập; thứ hai là **làm chậm hệ thống**, vì trong lúc một hàng đang được refresh thì CPU không truy cập được hàng đó mà phải chờ.

Ngoài ra, DRAM còn chậm vì tín hiệu đọc ra rất yếu, phải qua mạch khuếch đại mới nhận biết được, và vì thao tác đọc làm xả điện tích trên tụ nên sau mỗi lần đọc lại phải ghi lại giá trị vừa đọc.

Tóm lại, đây là một sự đánh đổi kinh điển: **SRAM nhanh, đắt, tốn diện tích nên dùng làm cache; còn DRAM chậm hơn, rẻ, nhỏ gọn nên dùng làm RAM chính** với dung lượng lớn.

---

## SLIDE 25 — SDRAM và DDR-SDRAM

### 📖 Kiến thức nền

**① SDRAM — Synchronous DRAM**

**Vấn đề của DRAM cũ (asynchronous):** CPU gửi yêu cầu rồi phải **đợi không biết bao lâu** cho tới khi DRAM trả lời. Trong lúc đợi, CPU **không làm gì được** vì không biết khi nào dữ liệu về.

**Giải pháp SDRAM:** đồng bộ DRAM với **xung nhịp hệ thống**. Bây giờ DRAM trả lời **sau đúng N chu kỳ xung nhịp** → CPU biết chính xác khi nào có dữ liệu → có thể **làm việc khác trong lúc chờ** rồi quay lại đúng lúc.

*Ví von:* Như đặt đồ ăn.
- **Async (không đồng bộ):** "Cứ chờ đó, xong tôi gọi" → phải đứng chờ mãi
- **Sync (đồng bộ):** "15 phút nữa có" → đi làm việc khác, 15 phút sau quay lại

**Các tín hiệu trong slide:**
- **CE#** = Chip Enable (dấu # nghĩa là **tích cực mức thấp** — kéo xuống 0 thì mới hoạt động)
- **RAS#** = Row Address Strobe — chốt địa chỉ **hàng**
- **CAS#** = Column Address Strobe — chốt địa chỉ **cột**
- **WE#** = Write Enable — cho phép ghi

💡 **Vì sao địa chỉ chia thành hàng và cột?** Vì DRAM tổ chức thành **ma trận 2 chiều**. Nếu có 1 triệu ô, thay vì cần 20 chân địa chỉ, ta chia thành ma trận 1024×1024 → chỉ cần **10 chân**, gửi địa chỉ hàng trước rồi địa chỉ cột sau. **Tiết kiệm một nửa số chân chip!**

**② DDR — Double Data Rate**

**Nguyên lý cốt lõi:** SDRAM thường chỉ truyền dữ liệu ở **sườn lên** của xung nhịp. DDR truyền ở **CẢ sườn lên VÀ sườn xuống** → gấp đôi tốc độ mà **không cần tăng tần số xung nhịp**.

```
Xung nhịp:   ┌──┐  ┌──┐  ┌──┐
             ┘  └──┘  └──┘  └──

SDR (thường):  ↑     ↑     ↑        → 3 lần truyền
DDR:           ↑  ↓  ↑  ↓  ↑  ↓     → 6 lần truyền (gấp đôi!)
```

**Vì sao không đơn giản tăng tần số?** Vì tần số cao gây **nhiễu điện từ**, **tốn điện** và khó thiết kế mạch. DDR là cách khéo léo để tăng băng thông mà không phải tăng tần số.

**Giải thích bảng trong slide:**

| DDR SDRAM | Data Rate | Memory Clock |
|---|---|---|
| DDR-266 | 266 Mb/s/pin | **133 MHz** |
| DDR-333 | 333 Mb/s/pin | **166 MHz** |
| DDR-400 | 400 Mb/s/pin | **200 MHz** |

👉 Chú ý: **266 = 133 × 2** — tốc độ dữ liệu đúng bằng **gấp đôi** xung nhịp. Đây chính là bằng chứng của "Double Data Rate".

**"Bursting" là gì?** Thay vì mỗi lần chỉ lấy 1 ô, DRAM lấy **cả một cụm ô liên tiếp** cùng lúc. Vì chương trình thường truy cập dữ liệu **liền kề nhau** (mảng, chuỗi), nên lấy sẵn cả cụm sẽ nhanh hơn nhiều.

**Các biến thể:**
- **DDR2, DDR3, DDR4** — mỗi thế hệ tăng tốc độ, giảm điện áp (DDR: 2.5V → DDR4: 1.2V)
- **LPDDR** = **Low Power DDR** — dành cho **điện thoại, thiết bị nhúng chạy pin**. Đây chính là loại dùng trên board RK3399 ở slide 31!
- **GDDR2–GDDR5** = **Graphics DDR** — cho card đồ hoạ, ưu tiên **băng thông cực lớn** hơn là độ trễ thấp

### 🎤 Đoạn văn nói
Slide này giới thiệu hai cải tiến quan trọng của DRAM.

Thứ nhất là **SDRAM — Synchronous DRAM**, tức DRAM **đồng bộ**. Để hiểu vì sao cần cải tiến này, ta xét vấn đề của DRAM đời cũ: CPU gửi yêu cầu rồi phải **đợi mà không biết bao lâu** mới có dữ liệu, nên đành đứng chờ. SDRAM giải quyết bằng cách **đồng bộ hoạt động của DRAM với xung nhịp hệ thống** — nhờ vậy CPU biết chính xác sau bao nhiêu chu kỳ thì có dữ liệu, và có thể tranh thủ làm việc khác trong lúc chờ.

Như slide viết, SDRAM cũng giúp loại bỏ việc phải định nghĩa nhiều chế độ hoạt động dựa trên trình tự các tín hiệu điều khiển như CE, RAS, CAS và WE. Trong đó **RAS là tín hiệu chốt địa chỉ hàng** và **CAS là chốt địa chỉ cột** — sở dĩ địa chỉ chia thành hàng và cột là vì DRAM được tổ chức thành ma trận hai chiều, cách này giúp **tiết kiệm một nửa số chân địa chỉ** trên chip.

Thứ hai là **DDR-SDRAM — Double Data Rate SDRAM**. DDR tăng hiệu năng bằng ba cách: tăng tốc độ xung nhịp, truyền dữ liệu theo cụm gọi là **bursting**, và quan trọng nhất là **truyền được HAI bit dữ liệu trong MỘT chu kỳ xung nhịp**.

Nguyên lý của điều này là: bộ nhớ thường chỉ truyền dữ liệu ở **sườn lên** của xung nhịp, còn DDR truyền ở **cả sườn lên lẫn sườn xuống** — nhờ vậy gấp đôi tốc độ mà không cần tăng tần số. Đây là giải pháp khéo léo, vì tăng tần số sẽ gây nhiễu điện từ và tốn điện hơn.

Bảng nhỏ bên phải chứng minh điều này: DDR-266 có tốc độ dữ liệu 266 megabit mỗi giây trên mỗi chân, trong khi xung nhịp bộ nhớ chỉ là 133 megahertz — đúng bằng **một nửa**. Tương tự với DDR-333 và DDR-400.

Các thế hệ tiếp theo gồm **DDR2, DDR3, DDR4** — mỗi thế hệ tăng tốc độ và giảm điện áp; **LPDDR** tức Low Power DDR — phiên bản tiết kiệm điện dùng cho điện thoại và thiết bị nhúng chạy pin, và chúng ta sẽ gặp lại loại này ở slide ví dụ thiết kế thực tế; cùng **GDDR2 đến GDDR5** dành riêng cho card đồ hoạ.

---

## SLIDE 26 — Flash memory

### 📖 Kiến thức nền

**Flash khác EEPROM ở điểm nào? — Đây là mấu chốt**

Cả hai đều dùng cùng công nghệ floating gate, nhưng:

| | EEPROM | Flash |
|---|---|---|
| Đơn vị xoá | **Từng byte** | **Cả khối (block)** — vài KB đến vài trăm KB |
| Số transistor/ô | Cần thêm transistor chọn | **Ít hơn** |
| Diện tích | Lớn hơn | **Nhỏ hơn** ← chính là điều slide nói |
| Giá/bit | Đắt | **Rẻ** |
| Dung lượng | Nhỏ (vài KB) | **Lớn** (GB, TB) |

**Vì sao xoá theo khối lại tiết kiệm diện tích?** Vì để xoá **từng byte riêng lẻ**, mỗi byte cần thêm mạch điều khiển riêng. Flash bỏ khả năng đó đi → **bớt được mạch** → ô nhớ nhỏ hơn → nhét được nhiều hơn trên cùng diện tích.

**Đánh đổi thực tế:** muốn sửa **1 byte** trong Flash → phải:
1. Đọc **cả khối** ra RAM
2. Sửa byte đó trong RAM
3. **Xoá cả khối** trên Flash
4. Ghi lại **cả khối**

→ Rất chậm và tốn tài nguyên! Đây là lý do vi điều khiển vẫn giữ **cả EEPROM lẫn Flash**: Flash lưu chương trình (ít sửa), EEPROM lưu cài đặt (sửa từng byte).

**"Flash" — tên gọi từ đâu?** Do kỹ sư Toshiba đặt, vì quá trình xoá cả khối cùng lúc gợi liên tưởng tới **đèn flash máy ảnh** — loé một cái là xong cả vùng.

### 🎤 Đoạn văn nói
Chuyển sang nhánh thứ ba: **bộ nhớ lai**, mà đại diện tiêu biểu là **Flash memory**.

Theo slide, Flash thực chất là **EEPROM được sắp xếp theo cách đặc biệt**, giúp nó **chiếm ít diện tích hơn** so với EEPROM hay DRAM tổ chức theo cấu trúc khác.

Em xin giải thích rõ hơn điểm khác biệt then chốt này. Cả EEPROM và Flash đều dùng chung công nghệ cổng nổi, nhưng khác nhau ở **đơn vị xoá**: EEPROM xoá được **từng byte riêng lẻ**, còn Flash phải xoá **cả một khối lớn** cùng lúc.

Chính vì bỏ đi khả năng xoá từng byte mà Flash **tiết kiệm được rất nhiều mạch điều khiển**, nhờ đó mỗi ô nhớ nhỏ hơn, nhét được nhiều dữ liệu hơn trên cùng diện tích chip, và giá thành trên mỗi bit rẻ hơn nhiều. Đó là lý do Flash có thể đạt dung lượng hàng gigabyte, trong khi EEPROM thường chỉ vài kilobyte.

Đánh đổi là: nếu muốn sửa chỉ một byte trong Flash, ta phải đọc cả khối ra, sửa, xoá cả khối, rồi ghi lại toàn bộ — rất chậm. Đây chính là lý do vì sao các vi điều khiển vẫn giữ **cả hai loại**: Flash để lưu chương trình vốn ít khi sửa, còn EEPROM để lưu cài đặt cần sửa thường xuyên từng chút một.

Flash có hai loại chính: **NOR flash** và **NAND flash** — hai slide tiếp theo sẽ so sánh chúng.

---

## SLIDE 27 — NAND Flash

### 📖 Kiến thức nền

**Tên NAND và NOR từ đâu ra?** Từ **cách mắc các ô nhớ**:
- **NAND:** các ô nhớ mắc **NỐI TIẾP** thành chuỗi — giống cấu trúc cổng logic NAND
- **NOR:** các ô nhớ mắc **SONG SONG** — giống cổng logic NOR

**Hai điểm khác biệt trong slide, giải thích nguyên nhân:**

**① "NAND lưu gấp ~4 lần NOR ở cùng giá"**

Vì mắc **nối tiếp**, các ô NAND **dùng chung đường tiếp xúc (contact)** — cả một chuỗi 32 hoặc 64 ô chỉ cần 2 contact ở hai đầu.

Còn NOR mắc **song song**, mỗi ô cần **contact riêng** → tốn diện tích hơn nhiều.

→ Dẫn tới con số **4F² vs 10F²** ở slide 28.

**② "NAND xoá/ghi nhanh hơn nhiều"**

Vì NAND xoá theo khối lớn và ghi theo trang → thao tác trên **nhiều ô cùng lúc** → tính trung bình mỗi byte thì nhanh hơn.

**Nhưng NOR có ưu điểm gì mà vẫn tồn tại?**

Đây là câu hỏi hay bị hỏi. Trả lời: **NOR đọc ngẫu nhiên từng byte rất nhanh**, vì mỗi ô truy cập độc lập được.

→ NOR hỗ trợ **XIP — eXecute In Place**: CPU có thể **chạy chương trình TRỰC TIẾP từ NOR flash**, không cần chép vào RAM trước.

NAND thì không làm được vì phải đọc theo cả trang.

**Bảng ứng dụng thực tế:**

| | **NOR Flash** | **NAND Flash** |
|---|---|---|
| Mắc ô nhớ | Song song | Nối tiếp |
| Đọc ngẫu nhiên | **Rất nhanh** | Chậm (theo trang) |
| Ghi/xoá | Chậm | **Nhanh** |
| Mật độ | Thấp | **Cao (~4x)** |
| Giá/GB | Đắt | **Rẻ** |
| XIP (chạy trực tiếp) | **Có** | Không |
| Dùng cho | **Firmware, BIOS, boot code** | **USB, thẻ SD, SSD, eMMC** |

💡 **Liên hệ slide 31:** board RK3399 dùng **eMMC** — chính là NAND flash đóng gói sẵn với bộ điều khiển.

### ❓ Câu hỏi thầy cô hay hỏi
- *"Vì sao vẫn dùng NOR khi NAND rẻ hơn?"* → Vì NOR cho phép CPU chạy chương trình trực tiếp từ đó (XIP), phù hợp lưu firmware khởi động. NAND phải chép vào RAM trước mới chạy được.
- *"SSD dùng loại nào?"* → NAND, vì cần dung lượng lớn và giá rẻ.

### 🎤 Đoạn văn nói
Slide này so sánh hai loại flash: **NAND và NOR** — hai loại có **đặc tính vật lý khá khác biệt**.

Trước hết, tên gọi NAND và NOR xuất phát từ **cách mắc các ô nhớ**: ở NAND, các ô nhớ được mắc **nối tiếp** thành chuỗi, còn ở NOR thì mắc **song song**.

Theo slide, **NAND flash là công nghệ mới hơn NOR**, và có hai điểm khác biệt chính.

Thứ nhất, **NAND lưu trữ được lượng dữ liệu gấp khoảng BỐN lần so với NOR flash ở cùng mức giá**. Nguyên nhân là do mắc nối tiếp, cả một chuỗi vài chục ô nhớ NAND chỉ cần hai điểm tiếp xúc ở hai đầu; trong khi NOR mắc song song nên mỗi ô cần điểm tiếp xúc riêng, tốn diện tích hơn nhiều.

Thứ hai, **NAND có tốc độ xoá và ghi nhanh hơn nhiều**, nên đây là lựa chọn ưu việt cho các ứng dụng **cần lưu trữ dữ liệu thường xuyên**.

Tuy nhiên, NOR vẫn có chỗ đứng riêng nhờ một ưu điểm: **đọc ngẫu nhiên từng byte rất nhanh**, vì mỗi ô truy cập độc lập được. Nhờ vậy NOR hỗ trợ tính năng gọi là **XIP — Execute In Place**, tức CPU có thể chạy chương trình **trực tiếp từ NOR flash** mà không cần chép vào RAM trước. NAND thì không làm được điều này.

Vì vậy trong thực tế, hai loại được dùng cho hai mục đích khác nhau: **NOR** dùng lưu firmware và mã khởi động; còn **NAND** dùng cho USB, thẻ nhớ SD, ổ SSD và chip eMMC — loại mà chúng ta sẽ gặp ở slide ví dụ thiết kế thực tế.

---

## SLIDE 28 — So sánh cấu trúc NAND vs NOR

### 📖 Kiến thức nền

**Đọc bảng theo 4 hàng:**

**Hàng 1 — Cell Array (mảng ô nhớ):**
- **NAND (trái):** các transistor xếp **nối tiếp thành cột dọc**, chỉ có **1 contact** ở đầu chuỗi nối lên Bit line
- **NOR (phải):** mỗi transistor có **contact riêng** nối thẳng lên Bit line (thấy các vòng tròn trắng)

👉 Đếm số vòng tròn "Contact" trong hình: NOR có **nhiều hơn hẳn** → đó chính là nguyên nhân tốn diện tích.

**Hàng 2 — Layout (bố trí vật lý):**
- **NAND:** ô nhớ có kích thước **2F × 2F**
- **NOR:** ô nhớ có kích thước **2F × 5F**

**Hàng 3 — Cross Section (mặt cắt ngang):** NOR có thêm các vùng tiếp xúc (màu vàng) mà NAND không có.

**Hàng 4 — Cell Size:** **NAND = 4F²** vs **NOR = 10F²**

**"F" là gì?** = **Feature size** — kích thước đặc trưng nhỏ nhất mà công nghệ chế tạo đạt được. Chính là các con số **65nm, 20nm, 17nm** đã gặp ở **slide 4**!

**Tính toán cụ thể:** Với công nghệ 20nm (F = 20nm):
- Ô NAND: 4 × (20nm)² = 4 × 400 = **1,600 nm²**
- Ô NOR: 10 × (20nm)² = 10 × 400 = **4,000 nm²**

→ **NAND nhỏ hơn 2.5 lần** → trên cùng diện tích chip, NAND nhét được **2.5 lần số ô nhớ**.

💡 Kết hợp với công nghệ **MLC/TLC** (lưu nhiều bit trong 1 ô), tổng lợi thế lên tới **~4 lần** như slide 27 nói.

**Vì sao dùng đơn vị F² thay vì nm²?** Vì F² là **đơn vị chuẩn hoá** — cho phép so sánh **hiệu quả thiết kế** giữa các loại bộ nhớ mà **không phụ thuộc vào công nghệ chế tạo**. Dù làm ở 65nm hay 20nm, NAND vẫn luôn là 4F² và NOR vẫn là 10F².

### 🎤 Đoạn văn nói
Slide này giải thích **lý do vật lý** đằng sau sự khác biệt vừa nói.

Bảng so sánh gồm bốn hàng. Hàng đầu là **Cell Array** — cách sắp xếp mảng ô nhớ. Nhìn vào hình, ta thấy ở **NAND** bên trái, các transistor được xếp **nối tiếp thành một chuỗi dọc**, và cả chuỗi chỉ cần **một điểm tiếp xúc** ở đầu để nối lên đường Bit line. Còn ở **NOR** bên phải, mỗi transistor có **điểm tiếp xúc riêng** — chính là các vòng tròn trắng mà ta đếm được nhiều hơn hẳn.

Hàng thứ hai là **Layout** — bố trí vật lý, cho thấy ô nhớ NAND có kích thước 2F nhân 2F, còn NOR là 2F nhân 5F. Hàng thứ ba là mặt cắt ngang.

Và quan trọng nhất là hàng cuối cùng — **Cell Size**: **ô nhớ NAND chỉ chiếm 4F bình phương, trong khi NOR chiếm tới 10F bình phương** — tức là ô nhớ NAND **nhỏ hơn khoảng 2.5 lần**.

Ở đây, chữ **F** là viết tắt của **feature size** — tức kích thước đặc trưng nhỏ nhất mà công nghệ chế tạo đạt được, chính là các con số 65 nanomet, 20 nanomet mà chúng ta đã gặp ở slide đầu chương. Sở dĩ người ta dùng đơn vị F bình phương thay vì nanomet vuông là để **so sánh hiệu quả thiết kế một cách chuẩn hoá**, không phụ thuộc vào công nghệ chế tạo cụ thể.

Đây chính là lý do vì sao NAND lưu được nhiều dữ liệu hơn trên cùng một diện tích chip, và do đó rẻ hơn tính trên mỗi gigabyte.

---

## SLIDE 29 — Địa chỉ ảo và địa chỉ vật lý

### 📖 Kiến thức nền

**Vì sao cần địa chỉ ảo? — BA lý do quan trọng**

**① Bảo vệ và cách ly (Protection & Isolation)**

Không có địa chỉ ảo: mọi chương trình cùng nhìn thấy **một không gian nhớ chung** → chương trình A có thể **ghi đè** lên vùng nhớ của chương trình B → sập hệ thống, hoặc virus đọc trộm dữ liệu.

Có địa chỉ ảo: mỗi chương trình có **bản đồ riêng**, MMU chỉ cho phép truy cập vùng đã được cấp → **không thể chạm vào chương trình khác**.

**② Đơn giản hoá lập trình**

Mỗi chương trình đều "tưởng" mình bắt đầu từ địa chỉ 0 và có toàn bộ bộ nhớ. Lập trình viên **không cần biết** chương trình sẽ được nạp vào chỗ nào trong RAM thật.

**③ Dùng nhiều bộ nhớ hơn RAM thật có**

Phần dữ liệu ít dùng được đẩy tạm ra **ổ cứng (Disk)** — thấy trong sơ đồ slide. Khi cần lại thì nạp về RAM. Nhờ vậy có thể chạy chương trình cần 8GB trên máy chỉ có 4GB RAM thật.

**Giải thích sơ đồ trong slide:**

```
CPU ──[Virtual Address]──> MMU ──[Physical Address]──> DRAM
                            │
                        Page Map
                        (bảng tra)
                            │
                            └──────────────────────> Disk
                                              (nếu không có trong RAM)
```

**Dòng chữ đỏ "Not all virtual addresses may have a translation"** → có 3 trường hợp:
1. Trang đang ở **RAM** → dịch bình thường
2. Trang đang bị đẩy ra **ổ cứng** → gây **page fault**, phải nạp về (chậm!)
3. Địa chỉ **không hợp lệ** → lỗi **segmentation fault** → chương trình bị dừng

⚠️ **LƯU Ý CỰC KỲ QUAN TRỌNG cho môn Hệ thống nhúng:**

**Đa số vi điều khiển KHÔNG có MMU!** 8051, PIC, AVR, ARM Cortex-M (STM32) đều **không có MMU** — chúng truy cập **thẳng địa chỉ vật lý**.

| Loại chip | Có MMU? | Chạy được Linux? |
|---|---|---|
| 8051, PIC, AVR | ❌ Không | Không |
| ARM Cortex-M (STM32) | ❌ Không (chỉ có MPU đơn giản) | Không (chỉ RTOS) |
| ARM Cortex-A (RK3399, Raspberry Pi) | ✅ Có | **Có** |

→ Liên hệ **Chương 1**: đây chính là ranh giới giữa **Medium scale** (không MMU, chạy RTOS) và **Sophisticated scale** (có MMU, chạy Linux)!

**MPU khác MMU:** MPU (Memory Protection Unit) chỉ **bảo vệ** vùng nhớ, **không dịch địa chỉ**. Đơn giản và nhẹ hơn MMU.

### ❓ Câu hỏi thầy cô hay hỏi
- *"Vi điều khiển có MMU không?"* → Đa số **không**. Chỉ các vi xử lý ứng dụng cao cấp (ARM Cortex-A) mới có, và đó là điều kiện bắt buộc để chạy được Linux đầy đủ.
- *"MMU nằm ở đâu?"* → Là **phần cứng nằm trong CPU**, giữa lõi xử lý và bus bộ nhớ.

### 🎤 Đoạn văn nói
Chuyển sang nội dung tiếp theo: **cấp phát và ánh xạ bộ nhớ**.

Slide này giới thiệu một khái niệm quan trọng: có **hai loại địa chỉ** trong hệ thống. Thứ nhất, các địa chỉ bộ nhớ do **CPU tạo ra** được gọi là **địa chỉ ảo — virtual address**. Thứ hai, địa chỉ mà **bộ nhớ chính thực sự sử dụng** được gọi là **địa chỉ vật lý — physical address**. Giữa CPU và bộ nhớ chính có một phần cứng trung gian gọi là **MMU — Memory Management Unit**, có nhiệm vụ **dịch địa chỉ ảo thành địa chỉ vật lý**.

Vậy vì sao lại cần thêm một lớp trung gian phức tạp như vậy? Có ba lý do chính.

Thứ nhất là **bảo vệ và cách ly**: nếu không có địa chỉ ảo, mọi chương trình cùng nhìn thấy một không gian nhớ chung, nên một chương trình lỗi có thể ghi đè lên vùng nhớ của chương trình khác. Với địa chỉ ảo, mỗi chương trình có bản đồ riêng và không thể chạm vào chương trình khác.

Thứ hai là **đơn giản hoá lập trình**: mỗi chương trình đều tưởng mình bắt đầu từ địa chỉ 0, lập trình viên không cần biết chương trình thực sự được nạp vào chỗ nào trong RAM.

Thứ ba là **dùng được nhiều bộ nhớ hơn RAM thật có**: phần dữ liệu ít dùng được đẩy tạm ra ổ cứng — chính là khối **Disk** trong sơ đồ, và nạp lại khi cần.

Nhìn vào sơ đồ: CPU gửi địa chỉ ảo tới MMU, MMU tra cứu trong bảng **Page Map** rồi xuất ra địa chỉ vật lý tới DRAM. Và lưu ý dòng chữ đỏ bên trái: **không phải mọi địa chỉ ảo đều có bản dịch** — trường hợp này sẽ được xử lý ở slide tiếp theo.

Cuối cùng, em xin lưu ý một điểm rất quan trọng với môn học của chúng ta: **đa số vi điều khiển đều KHÔNG có MMU**. Các chip như 8051, PIC, AVR hay cả dòng ARM Cortex-M đều truy cập thẳng địa chỉ vật lý. Chỉ những vi xử lý ứng dụng cao cấp như dòng ARM Cortex-A mới có MMU — và đây chính là điều kiện bắt buộc để chạy được Linux. Liên hệ với Chương 1, đây cũng chính là ranh giới phân biệt giữa hệ thống **medium scale** chạy RTOS và hệ thống **sophisticated** chạy Linux.

---

## SLIDE 30 — Page Map

### 📖 Kiến thức nền

**Vì sao chia bộ nhớ thành TRANG (page)?**

Nếu ánh xạ **từng byte** một: RAM 4GB = 4 tỷ byte → bảng tra cần **4 tỷ dòng** → bảng còn to hơn cả bộ nhớ! Vô lý.

Giải pháp: gom thành **khối 4KB** → 4GB / 4KB = **1 triệu trang** → bảng chỉ cần 1 triệu dòng. **Giảm 4000 lần!**

**Cấu trúc địa chỉ — giải thích hình bên phải slide:**

```
Địa chỉ ảo 32 bit:
┌────────────────────────┬──────────────┐
│  Virtual Page # (32-p) │  offset (p)  │
└────────────────────────┴──────────────┘
         ↓ dịch qua Page Map      ↓ giữ nguyên
┌────────────────────────┬──────────────┐
│  Physical Page #       │  offset (p)  │
└────────────────────────┴──────────────┘
Địa chỉ vật lý
```

**🔑 Trả lời câu hỏi trong slide: "Why use lower bits as offset?"**

Đây là câu hỏi thầy cô rất hay hỏi. Câu trả lời:

Vì kích thước trang là **luỹ thừa của 2** (4KB = 2^12), nên việc tách địa chỉ chỉ đơn giản là **cắt chuỗi bit làm hai phần** — **không cần phép chia hay phép nhân nào cả**.

**Ví dụ cụ thể với trang 4KB (p = 12 bit):**

```
Địa chỉ ảo:  0x00003A7C
Nhị phân:    0000 0000 0000 0000 0011 1010 0111 1100
             └──────── 20 bit ────────┘└─── 12 bit ───┘
                  Số hiệu trang           Offset
                    = 0x00003              = 0xA7C
```

**Lợi ích:**
1. **Phần cứng cực đơn giản** — chỉ cần đi dây, không cần mạch tính toán
2. **Offset giữ nguyên** không cần dịch → chỉ dịch phần số hiệu trang
3. **Nhanh** — thực hiện trong 1 chu kỳ

Nếu kích thước trang không phải luỹ thừa của 2 (ví dụ 5000 byte), sẽ phải làm phép **chia** — cực kỳ chậm và tốn mạch.

**Page fault — chuyện gì xảy ra?**

1. CPU yêu cầu địa chỉ ảo X
2. MMU tra page map → thấy trang **không có trong RAM**
3. → Phát sinh **page fault** (một loại ngắt)
4. Hệ điều hành tạm dừng chương trình
5. HĐH đọc trang đó **từ ổ cứng** vào RAM (chậm — hàng triệu chu kỳ!)
6. Cập nhật page map
7. Chạy lại lệnh vừa rồi

**"Demand paging"** = chỉ nạp trang vào RAM **khi thực sự cần** (khi có yêu cầu), thay vì nạp sẵn tất cả. Giúp tiết kiệm RAM và khởi động chương trình nhanh hơn.

**"Using main memory as a page cache"** = coi RAM như một **bộ đệm** cho ổ cứng — RAM giữ những trang hay dùng, ổ cứng giữ toàn bộ.

### 🎤 Đoạn văn nói
Slide này giải thích **cách MMU thực hiện việc dịch địa chỉ**.

MMU dịch địa chỉ ảo sang địa chỉ vật lý bằng một **phép tra bảng đơn giản**. Bảng này được gọi là **page map** hoặc **page table** — bảng trang.

Về nguyên lý: bộ nhớ vật lý được **chia thành các khối có kích thước cố định, gọi là các trang — pages**, với kích thước điển hình từ **4 đến 16 kilobyte**. Sở dĩ phải chia thành trang là vì nếu ánh xạ từng byte một thì với 4 gigabyte RAM, bảng tra sẽ cần tới 4 tỷ dòng — còn to hơn cả bộ nhớ. Khi gom thành các trang 4 kilobyte, bảng chỉ còn khoảng một triệu dòng, tức giảm được 4000 lần.

Về cấu trúc địa chỉ: một địa chỉ ảo gồm hai phần — **số hiệu trang ảo** cộng với **các bit offset**, tức độ lệch bên trong trang. Tương tự, địa chỉ vật lý gồm **số hiệu trang vật lý** cộng **offset**. Khi dịch, chỉ phần số hiệu trang được tra bảng và thay đổi, còn phần offset **giữ nguyên**.

Slide có đặt một câu hỏi: **vì sao lại dùng các bit thấp làm offset?** Câu trả lời là: vì kích thước trang luôn là **luỹ thừa của 2**, nên việc tách địa chỉ chỉ đơn giản là **cắt chuỗi bit làm hai phần**, không cần bất kỳ phép chia hay phép nhân nào. Điều này giúp phần cứng cực kỳ đơn giản, chỉ cần đi dây chứ không cần mạch tính toán, và thực hiện được trong một chu kỳ.

Tiếp theo, nếu trang ảo cần dùng **không có sẵn trong bộ nhớ vật lý**, hệ thống sẽ phát sinh một lỗi gọi là **page fault**. Khi đó hệ điều hành sẽ tạm dừng chương trình, đọc trang cần thiết từ ổ cứng vào RAM, cập nhật lại bảng trang, rồi cho chạy lại lệnh vừa rồi.

Và cuối cùng, như dòng chữ trong khung xanh: kỹ thuật **dùng bộ nhớ chính như một bộ đệm cho các trang** được gọi là **paging** hoặc **demand paging** — nghĩa là chỉ nạp trang vào RAM khi thực sự có nhu cầu, thay vì nạp sẵn tất cả.

---

## SLIDE 31 — Ví dụ thiết kế bộ nhớ thực tế (board RK3399)

### 📖 Kiến thức nền

**RK3399 là gì?** SoC của hãng Rockchip (Trung Quốc), dùng **ARM Cortex-A72 + A53** (big.LITTLE), chạy được **Linux/Android** đầy đủ.

→ Liên hệ Chương 1: đây là **Sophisticated embedded system**!

**Phân tích phần BỘ NHỚ (trọng tâm của slide):**

**① Hai chip LPDDR3 2GB — vì sao chia làm HAI?**

Nhìn sơ đồ: hai chip nối vào SoC qua **DRAM0** và **DRAM1** riêng biệt → đây là **dual-channel** (hai kênh).

**Lợi ích:** hai kênh hoạt động **song song** → **băng thông gấp đôi** so với một kênh 4GB. Giống như mở 2 làn đường thay vì 1 làn rộng.

**Vì sao LPDDR3 mà không phải DDR3 thường?** LP = **Low Power** — điện áp thấp hơn (1.2V so với 1.5V), có chế độ ngủ sâu → phù hợp thiết bị nhúng/di động. Liên hệ **slide 25** nơi đã nhắc tới LPDDR!

**② eMMC 5.1 16GB — đánh dấu "Bootable"**

**eMMC** = **embedded MultiMediaCard** = **NAND flash + bộ điều khiển** đóng gói sẵn thành 1 chip hàn thẳng lên bo.

→ Liên hệ **slide 27**: đây chính là ứng dụng thực tế của NAND flash!

**Vì sao cần bộ điều khiển tích hợp?** Vì NAND flash "trần" cần quản lý rất phức tạp: **wear leveling** (phân tán số lần ghi), **bad block management** (đánh dấu khối hỏng), **ECC** (sửa lỗi bit). eMMC gói sẵn tất cả → chip chủ chỉ cần gửi lệnh đọc/ghi đơn giản.

**"Bootable"** = hệ thống có thể **khởi động từ đây** — chứa bootloader, kernel Linux, và hệ thống file.

**③ SDCARD cũng "Bootable"**

**Vì sao cần 2 nguồn boot?** Rất thực dụng:
- **Phát triển/sửa chữa:** boot từ thẻ SD (dễ tháo ra ghi lại bằng máy tính)
- **Sản phẩm hoàn chỉnh:** boot từ eMMC (nhanh hơn, bền hơn, không rơi mất)
- **Cứu hộ:** nếu eMMC hỏng firmware, vẫn boot được bằng thẻ SD để sửa

**Phân cấp bộ nhớ trên board này:**

| Cấp | Linh kiện | Vai trò |
|---|---|---|
| Nhanh nhất | Cache trong SoC (SRAM) | Bộ đệm CPU |
| Trung gian | LPDDR3 4GB | **RAM chính** — chạy chương trình |
| Lưu trữ | eMMC 16GB | **Ổ cứng** — lưu OS, ứng dụng, dữ liệu |
| Tháo rời | SD card | Mở rộng, boot dự phòng |

**Các thành phần khác (nói lướt):**
- **PMIC RK808** = Power Management IC — quản lý nguồn, tạo nhiều mức điện áp khác nhau cho SoC
- **Module WiFi AP6236** — kết nối không dây qua SDIO
- **LCD RGB 24 Bit**, **HDMI**, **USB 3.0** — giao diện người dùng
- **Audio_Board** riêng với codec Realtek — tách riêng để **giảm nhiễu** cho mạch âm thanh

### 🎤 Đoạn văn nói
Chuyển sang nội dung cuối: **các ví dụ thiết kế bộ nhớ thực tế**.

Đây là sơ đồ thiết kế của một bo mạch thương mại thật, sử dụng chip **RK3399** ở trung tâm — đây là một SoC dùng lõi ARM Cortex-A, chạy được Linux và Android đầy đủ, tức thuộc nhóm hệ thống nhúng **sophisticated** theo phân loại ở Chương 1.

Về phần bộ nhớ, các bạn chú ý ở phía dưới: có **hai chip LPDDR3, mỗi chip 2GB** — đây là RAM chính, kết nối qua **hai kênh riêng biệt** là DRAM0 và DRAM1. Sở dĩ chia làm hai chip thay vì một chip 4GB là để hai kênh hoạt động **song song**, cho **băng thông gấp đôi** — giống như mở hai làn đường thay vì một làn rộng. Và loại được chọn là **LPDDR3** — tức Low Power DDR, phiên bản tiết kiệm điện mà em đã nhắc tới ở slide về DDR.

Bên cạnh là chip **eMMC 5.1 dung lượng 16GB**, được đánh dấu **"Bootable"**. eMMC thực chất chính là **NAND flash tích hợp sẵn bộ điều khiển** trong cùng một chip. Sở dĩ cần bộ điều khiển tích hợp là vì NAND flash trần đòi hỏi quản lý rất phức tạp như phân tán số lần ghi, đánh dấu khối hỏng và sửa lỗi bit — eMMC gói sẵn tất cả những việc đó.

Ngoài ra còn có khe **SDCARD** cũng có khả năng khởi động. Việc có hai nguồn boot rất thực dụng: trong giai đoạn phát triển thì boot từ thẻ SD cho dễ tháo ra ghi lại; còn sản phẩm hoàn chỉnh thì boot từ eMMC vì nhanh và bền hơn; và nếu firmware trên eMMC bị lỗi, vẫn có thể dùng thẻ SD để cứu hộ.

Xung quanh là các thành phần khác: màn hình LCD, module WiFi, khối quản lý nguồn PMIC, cổng USB 3.0, HDMI, và bo mạch âm thanh riêng bên phải — được tách riêng nhằm giảm nhiễu cho mạch âm thanh.

Ý chính: đây là **ví dụ minh hoạ cách bộ nhớ được bố trí trong một sản phẩm thật**, với đầy đủ phân cấp từ RAM chính đến bộ nhớ lưu trữ.

---

## SLIDE 32 — Giao tiếp bộ nhớ ngoài với 8051

### 📖 Kiến thức nền

**Vì sao cần bộ nhớ NGOÀI khi 8051 đã có ROM/RAM trong?** Vì bộ nhớ trong quá nhỏ: chỉ **4KB ROM + 128 byte RAM**. Ứng dụng phức tạp cần nhiều hơn.

**🔑 VẤN ĐỀ CỐT LÕI: BUS DÙNG CHUNG (Multiplexed Bus)**

**Bài toán:** Để truy cập 64KB bộ nhớ cần **16 đường địa chỉ** + **8 đường dữ liệu** = **24 chân**. Nhưng 8051 chỉ có **40 chân tổng cộng** — nếu dành 24 chân cho bus thì gần như **không còn chân nào** cho I/O!

**Giải pháp:** dùng **chung 8 chân** (P0) cho **cả địa chỉ thấp lẫn dữ liệu**, chia theo **thời gian**:

```
Thời điểm 1: P0 mang ĐỊA CHỈ thấp (A0-A7)  → chốt vào Latch
Thời điểm 2: P0 mang DỮ LIỆU (D0-D7)       → truyền dữ liệu thật
```

→ Tiết kiệm được **8 chân**!

**Vai trò của LATCH — giải thích chi tiết:**

```
      ┌─────────────────────────────────────┐
      │  Bước 1: ALE = 1                    │
      │  P0 xuất địa chỉ A0-A7 → Latch MỞ   │
      │  → Latch ghi nhớ địa chỉ            │
      ├─────────────────────────────────────┤
      │  Bước 2: ALE = 0                    │
      │  Latch ĐÓNG, GIỮ NGUYÊN địa chỉ     │
      │  → P0 rảnh, chuyển sang mang dữ liệu│
      └─────────────────────────────────────┘
```

**Kết quả:** cùng lúc, bộ nhớ nhận được:
- **Địa chỉ** từ đầu ra Latch (được giữ ổn định)
- **Dữ liệu** trực tiếp từ P0

**ALE = Address Latch Enable** — tín hiệu "hãy chốt địa chỉ lại". Chúng ta đã gặp tín hiệu này ở **slide 6 (8085)** — cùng một nguyên lý.

**Phân tích các tín hiệu trong sơ đồ:**

| Tín hiệu | Vai trò |
|---|---|
| **P0 (AD0-7)** | Địa chỉ thấp **+** dữ liệu (dùng chung) |
| **P2 (A8-15)** | Địa chỉ cao — **không** dùng chung, xuất trực tiếp |
| **ALE** | Điều khiển chốt địa chỉ |
| **WR** | Ghi vào **RAM** |
| **RD** | Đọc từ **RAM** |
| **PSEN** | Đọc từ **ROM** (Program Store Enable) |

**🔑 Vì sao có CẢ RD lẫn PSEN? — Kiến trúc Harvard!**

8051 tách riêng:
- **Bộ nhớ chương trình** (ROM) — đọc bằng **PSEN**
- **Bộ nhớ dữ liệu** (RAM) — đọc bằng **RD**, ghi bằng **WR**

→ Nhờ vậy, 8051 có thể truy cập **64KB ROM + 64KB RAM = tổng 128KB**, dù bus địa chỉ chỉ 16 bit! Vì hai không gian nhớ **độc lập** nhau, phân biệt bằng tín hiệu điều khiển khác nhau.

→ Liên hệ **slide 14 (AVR)**: cũng là kiến trúc Harvard.

**Vì sao là 64K?** Vì bus địa chỉ **16 bit** → 2^16 = 65,536 = 64K. Giống hệt 8085 ở slide 6.

### ❓ Câu hỏi thầy cô hay hỏi
- *"Nếu bỏ Latch đi thì sao?"* → Bộ nhớ sẽ không biết địa chỉ nào, vì khi dữ liệu xuất hiện trên P0 thì địa chỉ đã biến mất. Bắt buộc phải có Latch để **giữ** địa chỉ.
- *"Vì sao P2 không cần latch?"* → Vì P2 chỉ mang địa chỉ cao, **không dùng chung** với dữ liệu, nên tín hiệu luôn ổn định.

### 🎤 Đoạn văn nói
Slide này minh hoạ cách **kết nối RAM và ROM ngoài với vi điều khiển 8051**, mỗi loại dung lượng 64K.

Trước hết, vì sao cần bộ nhớ ngoài? Vì bộ nhớ tích hợp sẵn trong 8051 quá nhỏ — chỉ 4 kilobyte ROM và 128 byte RAM, không đủ cho ứng dụng phức tạp.

Điểm đáng chú ý nhất trong sơ đồ là khối **Latch** — mạch chốt. Em xin giải thích vì sao cần nó.

Bài toán đặt ra là: để truy cập 64 kilobyte bộ nhớ, ta cần 16 đường địa chỉ cộng 8 đường dữ liệu, tổng cộng 24 chân. Nhưng 8051 chỉ có 40 chân, nếu dành 24 chân cho bus thì gần như không còn chân nào cho việc khác.

Giải pháp là **dùng chung 8 chân của cổng P0 cho cả địa chỉ thấp lẫn dữ liệu**, chia theo thời gian — ký hiệu là AD0 đến AD7. Nghĩa là ở thời điểm đầu, P0 mang địa chỉ; sau đó P0 chuyển sang mang dữ liệu.

Nhưng vấn đề là bộ nhớ cần **cả địa chỉ lẫn dữ liệu cùng lúc**. Vì vậy cần một mạch chốt để **giữ lại phần địa chỉ**. Cách hoạt động như sau: khi tín hiệu **ALE — Address Latch Enable** lên mức cao, mạch chốt mở ra và ghi nhớ địa chỉ đang có trên P0. Sau đó ALE xuống thấp, mạch chốt đóng lại và giữ nguyên địa chỉ đó ở đầu ra, trong khi P0 được giải phóng để truyền dữ liệu. Nhờ vậy bộ nhớ nhận được đồng thời cả hai.

Các tín hiệu còn lại: **P2** cung cấp địa chỉ cao từ A8 đến A15 — cổng này không dùng chung nên không cần chốt. Tín hiệu **WR và RD** điều khiển ghi và đọc **RAM**. Còn **PSEN** dùng riêng để đọc **ROM** chương trình.

Việc có hai tín hiệu đọc riêng biệt — RD cho RAM và PSEN cho ROM — cho thấy 8051 dùng **kiến trúc Harvard**, tách riêng bộ nhớ chương trình và bộ nhớ dữ liệu. Nhờ vậy nó truy cập được tổng cộng 128 kilobyte, gồm 64K ROM và 64K RAM, dù bus địa chỉ chỉ có 16 bit.

---

## SLIDE 33 — Memory map của vi điều khiển

### 📖 Kiến thức nền

**Memory map là gì?** Là **bản đồ** cho biết **địa chỉ nào tương ứng với cái gì**. Người lập trình bắt buộc phải biết để truy cập đúng.

### **Cột trái — PROGRAM MEMORY (Flash)**

Chia làm 2 vùng:

**🔸 Application Flash Section** — chứa **chương trình chính** của bạn

**🔸 Boot Flash Section** — chứa **bootloader**

**Bootloader là gì và để làm gì?**

Là một chương trình nhỏ chạy **đầu tiên** khi bật máy. Nhiệm vụ:
1. Kiểm tra xem có yêu cầu **cập nhật firmware** không
2. Nếu có → nhận firmware mới qua UART/USB/WiFi → **tự ghi vào Application Section**
3. Nếu không → nhảy sang chạy chương trình chính

**Vì sao phải để riêng một vùng?** Vì bootloader phải **ghi đè lên Application Section**. Nếu nó nằm chung vùng đó → **tự xoá chính mình** giữa chừng → chip thành cục gạch!

→ Đây chính là ứng dụng của tính năng **"Self Read-Write Capabilities"** đã thấy ở **slide 13**!

💡 **Ví dụ thực tế:** Arduino có bootloader — nhờ vậy bạn nạp code qua cổng USB mà **không cần máy nạp chuyên dụng**.

### **Cột phải — DATA MEMORY**

| Vùng | Địa chỉ | Nội dung |
|---|---|---|
| **32 Registers** | $0000–$001F | 32 thanh ghi đa dụng của CPU |
| **64 I/O Registers** | $0020–$005F | Thanh ghi điều khiển ngoại vi |
| **160 Ext I/O Reg.** | $0060–$00FF | Thanh ghi ngoại vi mở rộng |
| **Internal SRAM** | $0100–$10FF | RAM trong chip (4096 × 8 = **4KB**) |
| **External SRAM** | $1100–$FFFF | RAM ngoài (tối đa 64K) |

**🔑 KHÁI NIỆM QUAN TRỌNG NHẤT: MEMORY-MAPPED I/O**

Chú ý điều kỳ lạ: **thanh ghi CPU và thanh ghi ngoại vi cũng nằm trong bản đồ bộ nhớ**, có địa chỉ như ô nhớ bình thường!

**Ý nghĩa:** điều khiển phần cứng **giống hệt như ghi vào biến trong bộ nhớ**.

```c
// Bật đèn LED ở chân PB5 — chỉ cần "ghi vào bộ nhớ"!
*(volatile uint8_t*)0x25 = 0x20;   // ghi vào địa chỉ thanh ghi PORTB

// Hoặc dùng tên định nghĩa sẵn:
PORTB = 0x20;    // PORTB thực chất là địa chỉ 0x25
```

**Lợi ích:** CPU **không cần lệnh đặc biệt** để điều khiển ngoại vi — chỉ cần các lệnh đọc/ghi bộ nhớ thông thường. Đơn giản hoá tập lệnh → phù hợp triết lý **RISC** (slide 15)!

*Đối lập:* một số kiến trúc (như x86) dùng **Port-mapped I/O** với lệnh riêng `IN`/`OUT`.

**Tại sao thanh ghi lại ở địa chỉ THẤP nhất ($0000)?** Vì các lệnh truy cập địa chỉ thấp thường **ngắn gọn hơn** (dùng ít bit để mã hoá địa chỉ) → tiết kiệm bộ nhớ chương trình và chạy nhanh hơn. Mà thanh ghi lại là thứ **truy cập nhiều nhất**.

**Ký hiệu "$":** là cách viết số **thập lục phân (hex)** trong tài liệu Atmel/Motorola. $FFFF = 0xFFFF = 65535.

### ❓ Câu hỏi thầy cô hay hỏi
- *"Vì sao Boot Flash Section để riêng?"* → Vì bootloader cần ghi đè lên vùng ứng dụng; nếu nằm chung sẽ tự xoá chính mình.
- *"Memory-mapped I/O là gì?"* → Là cách ánh xạ thanh ghi ngoại vi vào không gian địa chỉ bộ nhớ, cho phép điều khiển phần cứng bằng lệnh đọc/ghi bộ nhớ thông thường.

### 🎤 Đoạn văn nói
Slide này trình bày **bản đồ bộ nhớ** của một vi điều khiển — tức bảng cho biết địa chỉ nào tương ứng với cái gì. Người lập trình bắt buộc phải nắm được bản đồ này để truy cập đúng vùng.

Bên trái là **Program Memory** — bộ nhớ chương trình, trải từ địa chỉ **$0000 đến $FFFF**. Vùng này chia thành hai phần: **Application Flash Section** — nơi chứa chương trình ứng dụng của chúng ta, và **Boot Flash Section** ở cuối — nơi chứa **bootloader**.

Em xin giải thích về bootloader vì đây là khái niệm quan trọng. Bootloader là một chương trình nhỏ chạy đầu tiên khi bật máy, có nhiệm vụ kiểm tra xem có yêu cầu cập nhật firmware không. Nếu có, nó sẽ nhận firmware mới qua cổng UART hoặc USB rồi **tự ghi vào vùng Application**. Nếu không, nó nhảy sang chạy chương trình chính.

Sở dĩ bootloader phải được để riêng một vùng là vì nó cần ghi đè lên vùng ứng dụng — nếu nằm chung vùng đó thì nó sẽ **tự xoá chính mình** giữa chừng và làm hỏng chip. Đây cũng chính là ứng dụng của tính năng "Self Read-Write" mà chúng ta đã thấy ở slide về chip PIC. Ví dụ thực tế quen thuộc là bo Arduino — nhờ có bootloader mà ta nạp code qua cổng USB được, không cần máy nạp chuyên dụng.

Bên phải là **Data Memory** — bộ nhớ dữ liệu, gồm nhiều vùng có địa chỉ cụ thể: **32 thanh ghi** từ $0000 đến $001F; **64 thanh ghi I/O** từ $0020 đến $005F; **160 thanh ghi I/O mở rộng** từ $0060 đến $00FF; tiếp theo là **SRAM nội** kích thước 4096 nhân 8 bit, tức 4 kilobyte, từ $0100 đến $10FF; và cuối cùng là vùng dành cho **SRAM ngoài** từ $1100 trở đi.

Điều đáng chú ý nhất ở đây là: **các thanh ghi của CPU và thanh ghi điều khiển ngoại vi cũng nằm trong bản đồ bộ nhớ**, có địa chỉ như những ô nhớ bình thường. Cơ chế này gọi là **memory-mapped I/O**, và ý nghĩa của nó là: ta có thể **điều khiển phần cứng giống hệt như ghi vào một biến trong bộ nhớ**. Ví dụ, để bật một đèn LED, ta chỉ cần ghi một giá trị vào đúng địa chỉ thanh ghi cổng tương ứng.

Lợi ích của cách làm này là CPU **không cần thêm lệnh đặc biệt** nào để điều khiển ngoại vi, chỉ dùng các lệnh đọc ghi bộ nhớ thông thường — điều này giúp giữ tập lệnh nhỏ gọn, đúng với triết lý RISC mà em đã trình bày.

---

## SLIDE 34 — Thiết kế bộ nhớ ngoài cho AVR

### 📖 Kiến thức nền

**Nguyên lý HOÀN TOÀN GIỐNG slide 32** — chỉ khác dòng chip. Điều này cho thấy đây là **giải pháp phổ quát** trong thiết kế nhúng, không riêng hãng nào.

**Đọc sơ đồ:**

```
AVR                    Latch                SRAM
────                   ─────                ────
AD7:0 ──┬──────────────────────────────────> D[7:0]  (dữ liệu)
        │
        └──> D ──[Latch]── Q ──────────────> A[7:0]  (địa chỉ thấp)
ALE ─────────> G

A15:8 ──────────────────────────────────────> A[15:8] (địa chỉ cao)
RD  ────────────────────────────────────────> RD
WR  ────────────────────────────────────────> WR
```

**Chú ý mũi tên hai chiều ở AD7:0** — vì dữ liệu đi **cả hai hướng** (đọc và ghi).

**Chân Latch:**
- **D** = Data input (nhận từ AD7:0)
- **G** = Gate/Enable (điều khiển bởi ALE)
- **Q** = Output (giữ địa chỉ, đưa sang SRAM)

**Khác biệt nhỏ so với 8051:** AVR chỉ nối **SRAM** (dữ liệu), không nối ROM ngoài — vì AVR đã có Flash trong đủ lớn, chỉ thiếu RAM.

**Vạch trên đầu RD, WR** (RD̄, WR̄) = **tích cực mức thấp** — kéo xuống 0V mới thực hiện. Vì sao dùng mức thấp? Do đặc tính mạch CMOS, và để tránh kích hoạt nhầm khi hệ thống khởi động/nhiễu.

### 🎤 Đoạn văn nói
Slide này tương tự slide trước, nhưng áp dụng cho vi điều khiển **AVR** kết nối với **SRAM ngoài**. Việc cùng một giải pháp xuất hiện ở cả hai dòng chip khác hãng cho thấy đây là **cách làm phổ quát** trong thiết kế nhúng.

Nguyên lý hoạt động giống hệt: chân **AD7:0** của AVR dùng chung cho địa chỉ và dữ liệu — các bạn để ý mũi tên ở đây là **hai chiều**, vì dữ liệu đi cả hai hướng khi đọc và khi ghi.

Vì dùng chung nên cần một mạch chốt ở giữa. Mạch chốt này có ba chân: **D** là đầu vào nhận tín hiệu từ AD7:0, **G** là chân điều khiển được nối tới tín hiệu **ALE**, và **Q** là đầu ra giữ địa chỉ.

Sau khi qua mạch chốt, tín hiệu tách thành hai đường: **D[7:0]** mang dữ liệu đi thẳng vào SRAM, và **A[7:0]** mang địa chỉ thấp lấy từ đầu ra của mạch chốt. Địa chỉ cao **A15:8** được đưa thẳng sang mà không cần chốt vì không dùng chung.

Cuối cùng, hai tín hiệu **RD và WR** điều khiển việc đọc và ghi. Các bạn để ý có **vạch ngang phía trên** tên hai tín hiệu này — ký hiệu đó nghĩa là chúng **tích cực ở mức thấp**, tức phải kéo xuống 0 volt thì thao tác mới được thực hiện.

Một khác biệt nhỏ so với slide trước là AVR chỉ nối thêm SRAM chứ không nối ROM ngoài — vì AVR đã có sẵn bộ nhớ Flash trong chip đủ lớn để chứa chương trình, chỉ thiếu RAM mà thôi.

---

## SLIDE 35 — Giản đồ thời gian

### 📖 Kiến thức nền

**Giản đồ thời gian (timing diagram) là gì?** Là biểu đồ cho biết **tín hiệu nào phải ở mức nào, tại thời điểm nào**. Đây là **tài liệu bắt buộc** khi thiết kế mạch số — nếu sai timing, mạch sẽ không chạy dù nối dây đúng.

**Đọc giản đồ theo trình tự thời gian:**

```
Chu kỳ:        T1        T2        T3        T4
CLK_CPU:    ┌──┐      ┌──┐      ┌──┐      ┌──┐
            ┘  └──────┘  └──────┘  └──────┘  └──

ALE:        ────────┐        ┌──────────────
                    └────────┘
                    ↑ Chốt địa chỉ tại đây

A15:8:      Prev.addr ╳══════ Address ═══════╳

DA7:0:      Prev.data ╳ Addr ╳XX╳══ Data ════╳
                        ↑        ↑
                    địa chỉ    dữ liệu
                    (cùng 8 chân, khác thời điểm!)

WR:         ──────────────────┐         ┌────
                              └─────────┘    ← Chu kỳ GHI

RD:         ──────────────────┐         ┌────
                              └─────────┘    ← Chu kỳ ĐỌC
```

**Diễn giải từng bước:**

| Chu kỳ | Chuyện gì xảy ra |
|---|---|
| **T1** | Kết thúc chu kỳ trước (Prev. addr / Prev. data) |
| **T2** | **ALE lên cao** → xuất địa chỉ ra DA7:0 → **chốt vào Latch**. ALE xuống → địa chỉ được giữ |
| **T3** | DA7:0 chuyển sang mang **dữ liệu**. **WR hoặc RD xuống thấp** → thực hiện ghi/đọc |
| **T4** | WR/RD lên lại → kết thúc. Dữ liệu được chốt vào bộ nhớ (ghi) hoặc vào CPU (đọc) |

**🔑 Vì sao TRÌNH TỰ quan trọng đến vậy? — 3 khái niệm cần biết:**

**① Setup time (thời gian thiết lập):** dữ liệu phải **ổn định TRƯỚC** khi tín hiệu điều khiển tác động. Nếu WR xuống quá sớm khi dữ liệu chưa ổn định → **ghi nhầm giá trị rác**.

**② Hold time (thời gian giữ):** dữ liệu phải **giữ nguyên MỘT LÚC SAU** khi tín hiệu điều khiển kết thúc. Nếu bỏ đi quá sớm → bộ nhớ chưa kịp "ngậm" xong dữ liệu.

**③ Ký hiệu "XX" và các đường chéo ╳:** biểu thị khoảng thời gian tín hiệu **không xác định (không ổn định)** — đang chuyển đổi. **Không được đọc/ghi trong khoảng này!**

**Ý nghĩa tiêu đề "without Wait-state (SRWn1=0 and SRWn0=0)":**

**Wait state** = **chu kỳ chờ** được chèn thêm. Dùng khi nào?

Khi bộ nhớ ngoài **chậm hơn CPU**. Ví dụ: CPU chạy 16MHz muốn đọc xong trong 62.5ns, nhưng chip SRAM rẻ tiền cần 100ns mới trả lời → **phải chèn thêm chu kỳ chờ**, nếu không CPU sẽ đọc phải dữ liệu **chưa sẵn sàng** → sai.

**SRWn1, SRWn0** là các **bit cấu hình** trong thanh ghi của AVR, cho phép lập trình viên **chọn số chu kỳ chờ** (0, 1, 2, hoặc 3). Slide này minh hoạ trường hợp **không có wait state** — tức dùng với bộ nhớ đủ nhanh.

**Hai dòng DA7:0 (XMBK=0 và XMBK=1)** — XMBK là bit bật/tắt **bus keeper**, mạch giữ mức tín hiệu khi bus thả nổi, tránh nhiễu.

**🔗 LIÊN HỆ CHƯƠNG 1 — điểm nhấn để kết thúc bài:**

Đây là minh hoạ **cụ thể và thuyết phục nhất** cho khái niệm **Real-time constraints**:
- Tín hiệu **đúng logic** thôi **chưa đủ**
- Phải **đúng thời điểm** — sớm hay muộn vài nano-giây đều gây lỗi
- Và phải **dự đoán được** (deterministic) — đúng T1, T2, T3, T4 theo xung nhịp

Đúng như slide 14 Chương 1: *"Kết quả phải đúng cả về logic lẫn thời điểm xuất ra."*

### ❓ Câu hỏi thầy cô hay hỏi
- *"Wait state để làm gì?"* → Để CPU chờ bộ nhớ chậm kịp phản hồi. Nếu không chờ, CPU sẽ đọc dữ liệu chưa sẵn sàng và bị sai.
- *"Nếu sai timing thì hậu quả gì?"* → Đọc/ghi sai dữ liệu, chương trình chạy sai hoặc treo. Nguy hiểm là lỗi này **không ổn định** — lúc chạy đúng lúc sai, rất khó tìm.

### 🎤 Đoạn văn nói
Slide cuối cùng là **giản đồ thời gian** cho chu kỳ truy cập bộ nhớ dữ liệu ngoài. Đây là loại tài liệu bắt buộc phải có khi thiết kế mạch số, vì nếu sai về mặt thời gian thì mạch sẽ không chạy đúng dù ta nối dây hoàn toàn chính xác.

Trục ngang là thời gian, chia thành bốn chu kỳ **T1, T2, T3, T4** theo xung nhịp hệ thống **CLK_CPU** ở hàng trên cùng.

Diễn biến như sau. Tại chu kỳ **T2**, tín hiệu **ALE** lên mức cao — lúc này địa chỉ được xuất ra trên đường DA7:0 và được **chốt vào mạch latch**. Sau đó ALE xuống thấp, địa chỉ được giữ lại ổn định.

Sang chu kỳ **T3**, đường DA7:0 chuyển sang mang **dữ liệu**, và tín hiệu **WR xuống mức thấp** nếu là chu kỳ ghi, hoặc **RD xuống thấp** nếu là chu kỳ đọc — như hai nhóm được đánh dấu Write và Read ở bên phải slide.

Đến chu kỳ **T4**, các tín hiệu này trở lại mức cao, kết thúc thao tác.

Có hai khái niệm quan trọng ở đây. Thứ nhất là **thời gian thiết lập** — dữ liệu phải ổn định **trước** khi tín hiệu điều khiển tác động; nếu WR xuống quá sớm khi dữ liệu chưa ổn định thì sẽ ghi nhầm giá trị rác. Thứ hai là **thời gian giữ** — dữ liệu phải được giữ nguyên **một lúc sau** khi tín hiệu kết thúc, để bộ nhớ kịp tiếp nhận.

Các bạn cũng để ý các ký hiệu **XX** và các đường chéo trong giản đồ — chúng biểu thị khoảng thời gian tín hiệu **không ổn định**, đang trong quá trình chuyển đổi, và tuyệt đối không được đọc hay ghi trong khoảng này.

Cuối cùng, tiêu đề slide ghi **"without Wait-state"** — tức không có chu kỳ chờ. Chu kỳ chờ là các chu kỳ được chèn thêm khi bộ nhớ ngoài chậm hơn CPU; nếu không chèn, CPU sẽ đọc phải dữ liệu chưa sẵn sàng và bị sai.

Ý nghĩa lớn nhất của slide này: khi giao tiếp với bộ nhớ ngoài, các tín hiệu **không thể xuất hiện tuỳ tiện**, mà phải **tuân thủ đúng trình tự và đúng thời điểm** tính đến từng nano-giây. Đây chính là minh hoạ cụ thể nhất cho khái niệm **ràng buộc thời gian thực** mà chúng ta đã học ở Chương 1: kết quả phải đúng cả về mặt logic lẫn về mặt thời điểm.

---
---

## 🎤 KẾT LUẬN

Như vậy, em đã trình bày xong toàn bộ Chương 2 — Embedded Hardware.

Tóm tắt lại: chúng ta đã đi qua **kiến trúc phần cứng tổng quan** với hai tầng phần mềm - phần cứng và ba khối Processor, Memory, Input/Output; tiếp theo là **bộ xử lý**, với sự phân biệt giữa vi xử lý cần lắp thêm linh kiện rời và vi điều khiển tích hợp sẵn trên một chip, cùng hai kiến trúc tập lệnh RISC và CISC với hai triết lý tối ưu trái ngược nhau; và cuối cùng là **bộ nhớ**, từ chuỗi tiến hoá của họ ROM, sự đánh đổi giữa SRAM và DRAM, công nghệ Flash NAND và NOR, cho tới cách quản lý bộ nhớ ảo và các ví dụ thiết kế thực tế.

Xuyên suốt cả chương, chúng ta thấy một chủ đề lặp đi lặp lại: mọi lựa chọn trong thiết kế nhúng đều là một **sự đánh đổi** — giữa tốc độ và giá thành, giữa dung lượng và độ bền, giữa tính linh hoạt và mức độ tích hợp. Đây chính là nền tảng phần cứng cần thiết trước khi chúng ta bước vào các chương tiếp theo.

Bài trình bày của em đến đây là kết thúc. Em xin cảm ơn thầy/cô và các bạn đã lắng nghe, và rất mong nhận được câu hỏi cùng góp ý ạ.

---
---

## ⏱️ GỢI Ý THỜI LƯỢNG

| Nội dung | Slide | Thời lượng |
|---|---|---|
| Mở đầu | — | ~30 giây |
| Phần 1 — Kiến trúc tổng quan | 1–3 | ~3 phút |
| Phần 2 — Vi xử lý & Vi điều khiển | 4–16 | ~10 phút |
| Phần 3 — Bộ nhớ | 17–35 | ~13 phút |
| Kết luận | — | ~30 giây |
| **TỔNG (bản đầy đủ)** | **35 slide** | **~27 phút** |

**Nếu chỉ có 10–12 phút, cắt gọn như sau:**
- Slide 6: nói 1 câu rồi lướt ("đây là ví dụ CPU thực tế, phức tạp hơn sơ đồ lý thuyết")
- Slide 12, 13, 14: gộp thành một lần nói
- Slide 18–21: nói theo mạch tiến hoá liền một hơi, không tách 4 slide riêng
- Slide 28, 31, 35: mỗi slide chỉ nói 1–2 câu ý chính
- Slide 32 và 34: nói gộp vì nguyên lý giống hệt nhau

---

## 🔗 CÁC MỐI LIÊN HỆ XUYÊN SUỐT (điểm cộng khi thuyết trình)

Nhắc lại những liên kết này sẽ khiến bài nói mạch lạc và có chiều sâu:

| Liên hệ | Từ slide | Tới slide |
|---|---|---|
| Bus dùng chung AD0-7 + tín hiệu ALE | 6 (8085) | 32, 34, 35 |
| Con số 64K từ bus địa chỉ 16 bit | 6 | 32 |
| CMOS tiết kiệm điện → Energy efficiency | 4 | Chương 1 |
| Watchdog Timer → Dependability | 9, 13 | Chương 1 |
| "35 lệnh" của PIC → bằng chứng RISC | 13 | 15 |
| Kiến trúc Harvard | 14 (AVR) | 32 (8051) |
| Feature size F (65nm, 20nm) | 4 | 28 (4F² vs 10F²) |
| LPDDR tiết kiệm điện | 25 | 31 (board RK3399) |
| NAND flash | 27 | 31 (eMMC) |
| Self Read-Write → bootloader | 13 | 33 |
| MMU → ranh giới Medium/Sophisticated | 29 | Chương 1 |
| Timing → Real-time constraints | 35 | Chương 1 |
