A. Lập trình I/O:
1. Mục đích:
	- hiểu về lập trình Input/Output digital trên một chân của MCU
	- hướng dẫn những bước căn bản để phân tích thông tin HW/SW cần xây dựng một chương trình điều khiển I/O

2. Yêu cầu cần có để bắt đầu bài học này:
	- cần có 1 board vi điều khiển "STM32F0 Discovery". Nếu không có thì có thể sử dụng một loại board khác
	- tài liệu reference manual của con chíp (stm32f051r8)
	- makefile project mẫu
	- Ozone Segger và biết cách sử dụng phần mềm Ozone
	- Jlink debugger

3. Nội dung:
	- những bước để bắt đầu làm quen với ngoại vi
	- hướng dân cách viết chương trình đọc/ghi dữ liệu I/O trên một chân của MCU bẳng sử dụng ngôn ngữ C

4. Chi tiết
	- hướng dẫn cách đọc một block diagram
	- Liệt kê những ngoại vi sẽ được sử dụng cho lập trình I/O
		-> GPIO (chính)
		-> RCC (khối ngoại vi clock)
	- Cách thức điều khiển ngoại vi
		-> Thanh ghi:
			--> xác định address của những thanh ghi sẽ sử dụng
			--> xác định/tìm hiểu những trường bít trong thanh ghi có ý nghĩa/điều khiển gì ?
			--> xác định giá trị của trường bit sẽ phản ánh điều gì ?
			--> giá trị mặc định (phụ)
	- Viết chương trình bằng sử dụng ngôn ngữ C
		-> Liệt kê những thanh ghi sẽ tương tác/làm việc, địa chỉ cụ thể của những thanh ghi đó ?
			--> mode
			--> thiết lập chức năng GPIO cho chân sử dụng
			--> chiều dữ liệu (input/output)
			--> ghi dữ liệu ra trên thanh ghi nào ?
				==> ghi dữ liệu theo pin
				==> ghi dữ liệu theo port
			--> đọc dữ liệu về trên thanh ghi nào ?
			--> một số option thiết lập cho pin (pull-up/down)
		-> Trình tự điều khiển ngoại vi (trình tự ghi giá trị tới thanh ghi)
		-> Triển khai phương pháp/thuật toán để ứng dụng viết chương trình

***********************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////
***********************************************************************************************************

B. NVIC (Nested Vectored Interrupt Controller):

1. Chi tiết
	- Xác định ID ngắt cần sử dụng: EXTI0 -> ID interrupt = 5 -> PA0
	- Cập nhận handler interrupt tương ứng trong bảng software vector
	- Thiết lập cho phép ngắt ở mức ngoại vi
		-> GPIO: Input
		-> EXTI:
			--> EXTI_IMR
			--> thiết lập sường ngắt
		-> SYSCFG : SYSCFG_EXTICR1[EXTI0[3:0]]

	- Thiết lập mức priority
		-> NVIC_IPR
	- Xoá cờ ngắt
	- Enable interrupt từ NVIC
	- Bật ngắt toàn cục (enable global interrupt) bằng việc sử dụng lệnh ASM: cpsie i

	- Khi ra khỏi ngắt cần phải xóa cờ ngắt trong NVIC và trong ngoại vi
2. Debug NVIC
Những điểm cần lưu ý với Interrupt trên MCU:
(*) Bắt buộc hiểu quá trình: enable ngắt trên: Core + NVIC + Peripheral

Một số lỗi có thể xảy ra với interrupt, cách thức debug:
1. Thiết lập ngoại vi sai:
- Stop debugger (phụ)
- Mình set cờ pending tương ứng với ngắt trong NVIC
- Đặt breakpoint trong interrupt handler
- Go debugger
-> nếu PC dừng lại ở breakpoint của interrut handler => kết luận: NVIC + Core đã thiết lập đúng
-> Đọc và tìm hiểu ngoại vi xem đang sai ở đâu

2. Thiết lập NVIC sai:
- Kiểm tra thanh ghi pending để xem cờ ngắt được gửi về thực sự tương ứng với ID interrupt nào ?


3. Thiết lập Core sai:
- liên quan đến thanh ghi PRIMASK

- Cách thức để kiểm tra
	-> Kiểm tra xem cờ pending của ngoại vi + NVIC đã được bật chưa => kết luận luôn là có thể core đang bị sai

***********************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////
***********************************************************************************************************

C. USART (Universal synchronous asynchronous receiver transmitter)

1. Danh sánh những module liên quan:
- Clock (RCC):
	-> Tính toán giá trị clock chính xác cấp cho USART1
	-> Enable clock gate cho UART module
- GPIO:
	-> khởi tạo mode cho Tx/Rx chân
- USART:
	-> khởi tạo module.
	-> viết hàm truyền/nhận dữ liệu
- NVIC:
	-> khởi tạo và cho phép ngắt của USART1
	-> interrupt handler

2. USART:
2.1. Khởi tạo:
- Disable USART module -> USART_CR1[UE] = 0;
- Data = 8 bits -> USART_CR1[M1:M0]
- Parity = none -> USART_CR1[PCE]
- Stop = 1 bit  -> USART_CR2[STOP]
- Baudrate = 9600 bps -> thiết lập oversample1 USART_CR1[OVER8] = 16 bits
- Enable USART module -> USART_CR1[UE] = 1;
- Enable Tx -> USART_CR1[TE]
- Enable Rx -> USART_CR1[RE]

2.2. Quá trình truyền dữ liệu:
- Cần kiểm tra cờ USART_ISR[TXE]
	-> Nếu USART_ISR[TXE] = 1 -> tiến hành ghi dữ liệu vào USART_TDR = <data> (lưu ý là ghi 1 byte dữ liệu)
	-> Nếu USART_ISR[TXE] = 0 -> không ghi dữ liệu vào USART_TDR
- Truyền đc dữ liệu

2.3. Quá trình nhận dữ liệu:
- Cần kiểm tra cờ USART_ISR[RXNE]
- Nếu USART_ISR[RXNE] = 1 -> tiến hành đọc dữ liệu trên thanh ghi USART_RDR[8:0]
- Xóa cờ ngắt USART_ISR[RXNE] bằng việc đọc dữ liệu tren USART_RDR hoặc ghi 1 tới bít USART_RQR[RXFRQ]

2.4. Những phần tài liệu cần đọc:
- 27.5.2./ 27.5.3/ 27.5.4/ 27.5.9/ 27.8


3. Phụ lục
3.1. Driver cho PL2303: làm theo hướng dẫn theo link http://www.totalcardiagnostics.com/support/Knowledgebase/Article/View/92/20/prolific-usb-to-serial-fix-official-solution-to-code-10-error

***********************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////
***********************************************************************************************************

D. System timer (Systick)

1. Danh sánh những module liên quan:
- Clock (RCC):
	-> Tính toán giá trị clock chính xác cấp cho System Timer (Systick)
- System Timer:
	-> khởi tạo module.
	-> viết hàm start/get_state
- NVIC:
	-> khởi tạo và cho phép ngắt của Systick
	-> interrupt handler

2. System Timer:
2.1. Khởi tạo:
- Disable systick
- Lựa chọn source clock cho Systick
- Set giá trị bằng 0 cho SYST_SCR register

2.2. Start timer:
- Ghi giá trị cho thanh ghi reload
- Ghi giá trị bằng 0 cho current value register
- Ghi 1 tới bit enable Systick

2.3. Kiểm tra trạng thái của cờ tràn
- đọc giá trị bit COUNTFLAG trong thanh ghi SYST_CSR