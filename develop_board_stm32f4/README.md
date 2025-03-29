# hiện tại đang code ở forder develop board stm32f4 đã test hết toàn bộ chức năng và chạy được.
# đây là một nguồn kiến thức bổ ích giúp tôi kiểm soát hoàn toàn, toàn bộ MCU và có thể tăng tốc, tốc độ thực thi của mã mà không cần sử dụng bất kỳ thi viện nào.

# phần note i2c:
tính năng chính I2C:

1. tính năng chính của I2C master:
	- tạo clock
	- tạo bắt đầu và kết thúc
2. tính năng chính của I2C slave:
	- lập trình phát hiện địa chỉ I2C
	- khả năng định địa chỉ kép để nhận biết 2 địa chỉ slave
	- phát hiện bit dừng

trạng thái cờ:
	- cờ chế độ người gửi hoặc người nhận
	- cờ kết thúc quá trình truyền
	- cờ bận I2C

cờ báo lỗi:
	- điều kiện mất quyền điều khiển chế độ master
	- lỗi không nhận được tính hiệu xác nhận sau khi truyền địa chỉ dữ liệu
	- phát hiện điều kiện bắt đầu hoặc dừng sai vị trí
	- quá tải dữ liêu hoặc thiếu dữ liệu nếu kéo dài xung nhịp không được kích hoạt

2 vector ngắt
	1 ngắt báo thành công cho giao tiếp địa chỉ hoặc giao tiếp dữ liệu
	1 ngắt báo cho điều kiện lỗi

bộ đệm 1 byte có khả năng hỗ trợ dma

cấu hình PEC (kiểm tra gói lỗi) tạo hoặc xác minh:
	PEC value có thể được truyền như là byte cuối trong chế độ TX
	PEC error kiểm tra cho nhận byte cuối

tương thích với SMBus 2.0
	độ trễ chờ hết hạn 25ms ở mức thấp của clock
	thời gian kéo dài trạng thái clock low tích lũy của master là 10ms
	thời gian kéo dài trạng thái clock low tích lũy của slave là 25ms
	phần cứng PEC tao/xác thực với điều khiển ACK
	hỗ trợ địa chỉ độ phân giải giao thức ARP
	
tương thích PMBus

Note: một vài tính năng trên có thể không có săn trong một số sản phẩm nhất định. Người dùng nên tham khảo data sheet, để xác định một vài tính năng cụ thể hổ trợ triển khai giao diện i2C.

một quá trình truyền bắt đầu từ điều kiện bắt đầu và điều kiện dừng 
cả hai điều kiện bắt đầu và kết thúc được tạo bởi master.

địa chỉ luôn luôn được transmit trong master mode 
byte đầu tiên (hoặc các byte đầu tiên) sau điều kiện bắt đầu chứa địa chỉ (một byte trong chế độ 7-bit, hai byte trong chế độ 10-bit).

nghĩa là sau điều kiện bắt đầu sẽ gửi byte địa chỉ nếu là mode 7-bit sẽ gửi 1 byte địa chỉ, nếu là 10-bit sẽ gửi 2 bytes địa chỉ.


điều kiện bắt đầu là SCL là xung cao và SDA là đang cao xuống thấp.
điều kiện dừng SCL là xung cao và SDA là xung thấp lên cao.

if (ADDR == 1) {READ SR1; READ SR2}
if (STOPF == 1) {READ SR1; WRITE CR1}

in 7-bit addressing mode
	- Để vào chế độ người gửi, một master phải gửi địa chỉ slave với bit có trọng số thấp nhất là 0.
	- Để vào chế độ người nhận, một master phải gửi địa chỉ slave với bit có trọng số thấp nhất là 1.

trong chế độ 10 bit địa chỉ:
	- để vào chế độ người gửi, một master cần phải gửi một header như sau (11110xx0) và sau đó gửi địa chỉ slave (xx là hai bit có trọng số cao nhất của địa chỉ).
	- để vào chế độ người nhận, một master cần phải gửi một header như sau (11110xx0) và sau đó gửi địa chỉ slave. Sau đó nên gửi lại điều kiện bắt đầu tiếp theo là gửi header (11110xx1), với xx là hai bit có trọng số cao nhất của địa chỉ slave.

bit TRA chỉ ra rằng master đang trong chế độ người gửi hoặc người nhận.


các bước cấu hình chế độ truyền master i2c

trường hợp 1 với 7 bit address:

Start
while(!SB);
READ SR1;
WRITE DR with address
ACK
while(!ADDR);
READ SR1 
READ SR2
while(!TxE);
WRITE DR
ACK
....
while(!TxE);
while(!BTF);


trường hợp 2 với 10 bit address:

Start
while(!SB);
READ SR1 
WRITE DR WITH ADDRESS
HEADER
ACK
while(!ADD10);
READ SR1
WRITE DR with ADDRESS
ACK
while(!ADDR);
READ SR1
READ SR2
while(!TxE);
WRITE DATA
while(!TxE);
WRITE DATA
.......
WHILE(!TxE);
while(!BTF);

transmission using DMA

chế độ DMA có thể kích hoạt cho truyền bằng cách thiết lập bit DMAEN in I2C_CR2 register. Data sẽ được tải từ khu vực memory sử dụng ngoại vi DMA đến thanh ghi I2C_DR bất cứ khi nào bit TxE được set. Điều này có nghĩa là khi bit TxE được set dữ liệu sẽ tự động truyền từ khu vực memory đến vị trí của thanh ghi DR. Để ánh xạ một luồng DMA x cho quá trình truyền I2C (x ở đây là con số của stream x), thực hiện tuần tự theo các bước sau:

1. Set địa chỉ của thanh ghi I2C_DR trong thanh ghi DMA_SxPAR. Data sẽ được di chuyển đến địa chỉ này từ memory sau mỗi sự kiện TxE.

2. set địa chỉ memory trong thanh ghi DMA_SxMA0R (và trong thanh ghi DMA_SxMA1R trong trường hợp của double buffer mode). Data sẽ được loaded vào thanh ghi I2C_DR từ memory này sau mỗi sự kiện TxE.

3. cấu hình tổng số lượng bytes để truyền trong thanh ghi DMA_SxNDTR. Sau mỗi sự kiện TxE, giá trị này sẽ được giảm.

4. cấu hình độ ưu tiên của luồng DMA sử dụng bit PL[0:1] trong thanh ghi DMA_SxCR

5. set bit DIR trong thanh ghi DMA_SxCR và cấu hình ngắt sau khi truyền một nữa dữ liệu hoặc truyền đầy đủ dữ liệu dựa trên yêu cầu của ứng dụng.

6. kích hoạt luồng bằng cách thiết lập bit EN trong thanh ghi DMA_SxCR.

khi số lượng dữ liệu truyền đã được lập trình trong thanh ghi DMA Controller đạt được, bộ điều khiển DMA gửi tín hiệu kết thúc truyền EOT/EOT_1 đến giao diện I2C và DMA tạo một ngắt, nếu kích hoạt, trên luồng DMA ngắt vector.

Note: Không kích hoạt bit ITBUFEN trong thanh ghi I2C_CR2 nếu DMA được sử dụng để truyền.

Nhận dữ liệu sử dụng DMA

chế độ DMA có thể được kích hoạt cho nhận dữ liệu bằng cách thiết lập bit DMAEN trong thanh ghi I2C_CR2. Data sẽ được tải từ thanh ghi I2C_DR đến khu vực memory đã cấu hình sử dụng ngoại vi DMA bất cứ khi nào một byte data được nhận. Để ánh xạ luồng DMA x cho nhận I2C, thực hiện theo các bước sau.

1. set địa chỉ tranh ghi I2C_DR trong thanh ghi DMA_SxPAR. Data sẽ được di chuyển từ địa chỉ này đến memory sau mỗi sự kiện RxNE.

2. set địa chỉ memory trong thanh ghi DMA_SxMA0R ( và trong thanh ghi DMA_SxMA1R trong trường hợp của chế độ bộ đệm đôi). Data sẽ được tải từ thanh ghi I2C_DR đến khu vực memory này sau mỗi sự kiện RxNE.

3. cấu hình tổng số lượng bytes để truyền trong thanh ghi DMA_SxNDTR. Sau mỗi sự kiện RxNE, giá trị này sẽ được giảm xuống.

4. cấu hình luồng ưu tiên sử dụng bit PL[0:1] trong thanh ghi DMA_SxCR.

5. reset bit DIR và cấu hình ngắt trong thanh ghi DMA_SxCR sau khi truyền được một nữa dữ liệu hoặc truyền đầy đủ dữ liệu dựa trên yêu cầu của ứng dụng.

6. Kích hoạt luồng bằng cách thiết lập bit EN trong thanh ghi DMA_SxCR.

Khi số lượng dữ liệu truyền được lập trình trong thanh ghi điều khiển DMA đạt được, bộ điều khiển DMA gửi một tín hiệu kết thúc truyền EOT/EOT_1 đến giao diện I2C và DMA tạo ra một ngắt. Nếu kích hoạt, trên luồng DMA ngắt vector.

Note: Không được enable bit ITBUFEN trong thanh ghi I2C_CR2 nếu DMA được sử dụng để nhận.

Paket error checking (kiểm tra gói lỗi)

một phép tính PEC được thực hiện để cải thiện độ tin cậy của giao tiếp. PEC được tính toán bằng cách sử dụng C(x) = x^8 + x^2 + x + 1 đa thức CRC-8 thực hiện tuần tự trên từng bit.

việc tính toán PEC được enabled bằng cách thiết lập bit ENPEC trong thanh ghi I2C_CR1. PEC được tính toán CRC-8 trên tất cả các bytes tin nhắn thêm cả địa chỉ và bit R/W.
	Trong chế độ truyền: set bit PEC transfer trong thanh ghi I2C_CR1 sau khi bit TXE của bytes cuối cùng được gửi. PEC được chuyển đi sau bytes cuối cùng được gửi.

	Trong chế độ nhận: set bit PEC trong thanh ghi I2C_CR1 sau sự kiện RxNE tương ứng byte cuối nên là người nhận sẽ gửi NACK nếu bytes nhận được tiếp theo không bằng phép tính PEC ở bên trong. Trong trường hợp của master - receiver, một NACK phải theo sau PEC bất kể kết quả phép tính là gì. PEC phải được set trước ACK của CRC nhận trong slave mode. Nó phải là set khi ACK là set low trong mode master.

nếu DMA và phép tính PEC cả hai đều được enabled:
- Trong transmission: khi giao diện I2C nhận một tín hiệu EOT từ bộ điều khiển DMA, nó sẽ tự động gửi PEC sau byte cuối cùng.
- Trong reception: khi giao diện I2C nhận một tín hiệu EOT_1 từ bộ điều khiển DMA, nó sẽ tự động cân nhắc byte tiếp theo như là một PEC và sẽ kiểm tra nó. Một phản hồi DMA được tạo ra sau khi nhận PEC.


Để cho phép gửi PEC trung gian, một bit điều khiển là có sẵn trong thanh ghi I2C_CR2 (LAST bit) để xác định nếu nó có thực là lần transfer DMA cuối cùng hoặc không. Nếu nó là phản hôi DMA cuối cùng cho một master receiver, một NACK sẽ tự động gửi sau byte cuối cùng.

phép tính PEC sẽ bị hỏng do bị mất quyền điều khiển.

# các bước để khởi tạo một I2C từ thanh ghi.
1. Enable gpio sử dụng làm chân SCL và SDA
2. chọn cấu hình alternate cho 2 chân đó trong thanh ghi GPIOx_MODER
3. chọn output là open drain cho 2 chân đó
4. kéo hai chân SCL và SDA là pull-up (nghĩa là điện trở kéo lên cho 2 chân này)
5. set alternate funtion trong thanh ghi GPIOx_AFRL
6. enable clock i2c
7. set bit software reset i2c để release cái bus
8. disable software reset i2c để bất đầu cấu hình
9. chọn frequency cho protocol i2c
10. chọn standard mode cho protocol i2c
11. set 100khz cho protocol i2c
12. set rise time cho i2c
13. enable peripheral i2c.

```c
// PB8 - I2C1 SCL
// PB9 - I2C1 SDA

#define GPIOB_BASE_ADDR	0x40020400
#define RCC_BASE_ADDR	0x40023800
#define I2C1_BASE_ADDR	0x40005400

void init_i2c1(void)
{
	// step 1
	uint32_t *RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*RCC_AHB1ENR |= (1U << 1);

	// step 2
	uint32_t *GPIOB_MODER = (uint32_t*)(GPIOB_BASE_ADDR + 0x00);
	*GPIOB_MODER |= (2U << 16) | (2U << 18);

	// step 3
	uint32_t *GPIOB_OTYPER = (uint32_t*)(GPIOB_BASE_ADDR + 0x04);
	*GPIOB_OTYPER |= (1U << 8) | (1U << 9);

	// step 4
	uint32_t *GPIOB_PUPDR = (uint32_t*)(GPIOB_BASE_ADDR + 0x0C);
	*GPIOB_PUPDR |= (1U << 16) | (1U << 18);

	// step 5
	uint32_t *GPIOB_AFRH = (uint32_t*)(GPIOB_BASE_ADDR + 0x24);
	*GPIOB_AFRH |= (4U << 0) | (4U << 4);
	
	// step 6
	uint32_t *RCC_APB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x40);
	*RCC_APB1ENR |= (1U << 21);

	// step 7
	uint32_t *I2C1_CR1 = (uint32_t*)(I2C1_BASE_ADDR);
	*I2C1_CR1 |= (1U << 15);
	
	// step 8
	*I2C1_CR1 &= ~ (1U << 15);

	// step 9
	uint32_t *I2C1_CR2 = (uint32_t*)(I2C1_BASE_ADDR + 0x04);
	*I2C1_CR2 |= (16 << 0);

	// step 10
	uint32_t *I2C1_CCR = (uint32_t*)(I2C1_BASE_ADDR + 0x1C);
	*I2C1_CCR &= ~ (1U << 15);

	// step 11
	*I2C1_CCR |= (80 << 0);
	
	// step 12
	uint32_t *I2C1_TRISE = (uint32_t*)(I2C1_BASE_ADDR + 0x20);
	*I2C1_TRISE |= (17U << 0);
	
	// step 13
	I2C1_CR1 |= (1U << 0);
}



```
master receiver
cái này là dành cho giao tiếp với cảm biến ADXL345
các bước để đọc một bytes từ i2c master receiver

input: 1 byte saddr, 1 byte maddr , data 
output: non

1. khởi tạo một biến volatile int tempory để đọc thanh ghi SR2
2. chờ cho đến khi bit BUSY = 0
3. tạo một điều kiện bắt đầu 
4. chờ cho đến khi khi điều kiện tạo start được tạo bằng cách kiểm tra bit SB trong thanh ghi SR1
5. ghi địa chỉ slave address vào thanh ghi DR
6. chờ bit ADDR trong thanh ghi SR1 là 1
7. đọc thanh ghi SR2 bằng cách gán nó vào biến tempory
8. gửi memory address bằng cách ghi vào thanh ghi DR
9. chờ bit SR1_TXE là 1 là truyền xong
10. tạo lại điều kiện bắt đầu
11. chờ bit SB trong thanh ghi SR1 là 1
12. gửi địa chỉ slave với bit LSB là 1 (yêu cầu đọc)
13. chờ chơ bit ADDR trong thanh ghi SR1 là 1
14. disable ack 
15. đọc thanh ghi SR2 để xóa bit ADDR 
16. tạo điều kiện dừng set bit STOP trong thanh ghi CR1
17. chờ cho bit RXNE trong thanh ghi SR1 là 1
18. gán thanh ghi DR vào con trỏ data để lưu trữ dữ liệu đọc được.

let's go

```c
void i2c_readByte(char saddr, char maddr, char *data)
{
	volatile int temp;
	
	uint32_t *I2C1_SR2 = (uint32_t*)(I2C1_BASE_ADDR + 0x18);
	while(*I2C1_SR2 & (1U << 1));
	
	uint32_t *I2C1_CR1 = (uint32_t*)(I2C1_BASE_ADDR);
	*I2C1_CR1 |= (1U << 8);

	uint32_t *I2C1_SR1 = (uint32_t*)(I2C1_BASE_ADDR + 0x14);
	while(!(*I2C1_SR1 & (1U << 0)));

	uint32_t *I2C1_DR = (uint32_t*)(I2C1_BASE_ADDR + 0x10);
	*I2C1_DR |= (saddr << 1);

	while(!(*I2C1_SR1 & (1U << 1)));
	temp = *I2C1_SR2;

	*I2C1_DR = maddr;

	while(!(*I2C1_SR1 & (1U << 7)));
	
	*I2C1_CR1 |= (1U << 8);
	while(!(*I2C1_SR1 & (1U << 0)));
	
	*I2C1_DR = (saddr << 1) | 1;
	while(!(*I2C1_SR1 & (1U << 1)));
	temp = *I2C1_SR2;
	
	*I2C1_CR1 |= (1U << 10);
	*I2C1_CR1 |= (1U << 9);

	while(!(*I2C1_SR1 & (1U << 6)));
	*data++ = *I2C1_DR;
}


```
cách viết hàm burstRead i2c protocol

input: 1 byte saddr , 1 byte maddr, 4 byte n , data
output: none

1. khởi tạo biến volatile int tempory.
2. wait until bit BUSY in SR2 register into zero
3. wait until bit SB in SR1 register into 1
4. write saddr << 1 into DR register
5. wait until bit ADDR in SR1 register into 1
6. clear addr flag by assign SR2 register into tempory
7. wait until bit TXE in SR1 register into 1
8. assign maddr into DR register
9. wait until bit TXE in SR1 register into 1
10. generate restart by set bit START in CR1 register
11. wait until bit SB in SR1 register into 1
12. assign saddr with bit LSB is 1 (for read) into DR register
13. wait until bit ADDR in SR1 register into 1
14. clear bit ADDR by assign SR2 register into tempory
15. enable bit ACK in CR1 register
16. create loop with condition is n > 0U
	inside loop 
	compare if (n == 1U)
	implementation: 
	1. disable ack by clear bit ACK in CR1 register
	2. generate STOP
	3. wait bit RXNE in SR1 register into 1
	4. assign DR register into data

	else 
	implementation:
	1. wait bit RXNE in SR1 register into 1
	2. assign DR register into data
	3. n--


triển khai một hàm i2c1_burstWrite 
input: 1 byte saddr, 1 byte maddr, 4 byte size, pointer for data
output: none

1. initialise variable volatile integers tempory (for read SR2 register)
2. generate start by set bit START inton CR1 register
3. wait until bit SB in SR1 register into 1
4. assign saddr << 1 into DR register
5. wait until bit ADDR in SR1 register into 1
6. clear bit ADDR by assign SR2 register into tempory
7. wait until bit TXE in SR1 register into 1
8. assign maddr into DR register
9. create loop with condition 
	for(int i = 0; i < n; i++)
	{
		implementation
		1. wait until bit TXE in SR1 register into 1
		2. assign data into DR 
	}
10. wait until bit BTF in SR1 register into 1

# document adxl345
Document I2C ADXL345

Khi chân CS được nối cao với VDD I/O, ADXL345 sẽ ở chế độ I2C, chỉ yêu cầu kết nối 2 dây đơn giản như hình mình họa trong hình 8.


Nó hỗ trợ các chế độ truyền dữ liệu tiêu chuẩn (100 kHz) và nhanh (400 kHz) nếu các thông số thời gian được đưa ra trong **Bảng 11** và **Hình 10** được đáp ứng.

table 11.

1 Các giới hạn dựa trên kết quả đặc trưng, với fSCL = 400 kHz và dòng tiêu hao 3 mA; không được kiểm tra trong sản xuất.
2 Tất cả các giá trị được tham chiếu đến các mức VIH và VIL được đưa ra trong Bảng 10.
3 t6 là thời gian giữ dữ liệu được đo từ cạnh xuống của SCL. Nó áp dụng cho dữ liệu trong thời gian truyền và thời gian xác nhận.
4 Một thiết bị truyền dữ liệu phải tự nội bộ cung cấp thời gian giữ đầu ra ít nhất 300 ns cho tín hiệu SDA (so với VIH(min) của tín hiệu SCL) để vượt qua vùng không xác định ở cạnh xuống của SCL.
5 Giá trị tối đa của t6 chỉ cần được đáp ứng nếu thiết bị không kéo dài khoảng thời gian thấp (t3) của tín hiệu SCL.
6 Giá trị tối đa của t6 là một hàm của thời gian mức thấp của xung đồng hồ (t3), thời gian tăng của xung đồng hồ (t10), và thời gian thiết lập dữ liệu tối thiểu (t5(min)). Giá trị này được tính bằng công thức t6(max) = t3 − t10 − t5(min).
7 Cb là tổng điện dung của một đường dẫn bus, tính bằng picofarad.

hình 10.

giải thích bảng table 11
Bảng mà bạn cung cấp mô tả các tham số thời gian của giao tiếp I²C trong một số điều kiện cụ thể: nhiệt độ 25°C (T_A), điện áp nguồn 2.5 V (V_S), và điện áp đầu vào/đầu ra là 1.8 V (V_DD I/O). Dưới đây là các thông tin chi tiết từ bảng:

parameter là các thông số 
Limit là giới hạn
Min là giá trị min
Max là giá trị max 
Unit là đơn vị
Description là mô tả

fSCL có mô tả là : tần số xung nhịp SCL (clock)
t1 : chu kỳ xung nhịp SCL(t_SCL)
t2: thời gian SCL ở mức cao (t_high)
t3: thời gian SCL ở mức thấp (t_low)
t4: thời gian giữ trạng thái khởi đầu hoặc lặp lại (t_HD,STA)
t5: thời gian thiết lập dữ liệu (t_SU,DAT)
t6: thời gian giữ dữ liệu (t_HD,DAT)
t7: thời gian thiết lập trạng thái lặp lại (t_SU,STA)
t8: thời gian thiết lập trạng thái dừng (t_SU,STO)
t9: thời gian trống giữa trạng thái dừng và khởi đầu (t_BUF)
t10: thời gian tăng (rise time) của cả SCL và SDA khi nhận dữ liệu hoặc transmitting.
t11: thời gian cạnh xuống của SDA khi nhận 
	thời gian cạnh xuống của cả SCL và SDA khi truyền
	thời gian cạnh xuống của cả SCL và SDA khi truyền hoặc nhận 
	
cb: tải điện dung của từng đường bus

hỗ trợ đọc hoặc viết một byte hoặc nhiều byte như hình 9 

giải thích hình số 9 I2C device addresing.

Single-byte write (ghi 1 byte):
1. Master gửi tín hiệu START
2. gửi địa chỉ slave (slave address) kèm theo bit chỉ định "WRITE".
3. Gửi địa chỉ thanh ghi (Register Address) để chỉ định nơi ghi dữ liệu
4. Gửi dữ liệu (DATA)
5. Kết thúc bằng tín hiệu STOP.

Multiple-byte write (ghi nhiều byte)
tương tự như ghi 1 byte, nhưng master có thể gửi liên tiếp nhiều dữ liệu trước khi kết thúc bằng tín hiệu STOP.

thực hiện như sau:
1. master gửi tín hiệu START
2. gửi địa chỉ slave address + write
3. gửi địa chỉ thanh ghi (register address) để chỉ định nơi ghi dữ liệu
4. gửi dữ liệu data
5. gửi dữ liệu data
....
kết thúc bằng tín hiệu STOP.

Single-byte read (đọc 1 byte)
follow step by step:
1. master gửi tín hiệu START
2. gửi địa chỉ SLAVE ADDRESS + WRITE
3. gửi địa chỉ thanh ghi muốn đọc REGISTER ADDRESS
4. gửi lại tín hiệu start là restart 
5. gửi địa chỉ SLAVE ADDRESS + READ
6. đọc dữ liệu
7. gửi NACK và gửi STOP

Multiple-byte read
follow step by step:
1. master gửi tín hiệu START
2. gửi địa chỉ SLAVE ADDRESS + WRITE
3. gửi địa chỉ thanh ghi cần đọc REGISTER ADDRESS
4. gửi lại tín hiệu restart 
5. gửi địa chỉ SLAVE ADDRESS + READ
6. chờ đọc dữ liệu
7. gửi ACK
8. chờ đọc dữ liệu 
9. gửi NACK + STOP.


với chân SDO/ALT ADDRESS được đặt ở mức cao, địa chỉ I2C 7 bit của thiết bị là 0x1D, tiếp theo là bit R/W (đọc/ghi).

Điều này được chuyển đổi thành 0x3A cho thao tác ghi và 0x3B cho thao tác đọc.
Điều này có nghĩa là nếu bạn nối chân SDO/ALT ADDRESS (Pin 12) với đất (ground), thiết bị sẽ sử dụng địa chỉ I²C thay thế là 0x53. Địa chỉ này được sử dụng kèm với bit R/W (Đọc/Ghi) để xác định thao tác đọc hoặc ghi trên bus I²C.

Điều này có nghĩa là khi sử dụng địa chỉ I2C thay thế 0x53 (khi chân SDO/ALT ADDRESS được nối đất), địa chỉ này sẽ được kết hợp với bit R/W để xác định thao tác cụ thể:
- 0xA6 được sử dụng cho thao tác ghi (WRITE).
- 0xA7 được sử dụng cho thao tác đọc (READ).

cách tính: địa chỉ 7-bit 0x53 được chuyển thành 8 bit bằng cách thêm bit R/W ở vị trí bit 0.Bit R/W = 0 cho ghi, và R/W = 1 cho đọc. Điều này sẽ tạo ra địa chỉ 8 bit là 0xA6 (ghi) và 0xA7(đọc).

Điều này có nghĩa là nếu trên cùng một bus I²C có các thiết bị khác được kết nối, mức điện áp hoạt động danh định (nominal operating voltage) của các thiết bị đó không được vượt quá mức điện áp VDD I/O của thiết bị đang đề cập quá 0.3 V.

Lý do của giới hạn này:

Đảm bảo tương thích điện áp giữa các thiết bị trên cùng bus I²C.

Ngăn ngừa hư hỏng thiết bị hoặc gây nhiễu tín hiệu khi các mức điện áp không đồng nhất.

Ví dụ: Nếu VDD I/O của thiết bị chính (master) là 3.3 V, các thiết bị khác trên bus không được có mức điện áp hoạt động danh định vượt quá 3.6 V (3.3 V + 0.3 V). Điều này đảm bảo tất cả thiết bị hoạt động ổn định trong cùng hệ thống.

register map 
giải thích cách dùng bảng register map 
địa chỉ của thanh ghi gồm hai địa chỉ là địa chỉ hexa và địa chỉ dec

1. thanh ghi DEVID 
address: 0x00
type: R
reset value: 1110 0101
description: Device ID

2. thanh ghi THRESH_TAP
address: 0x1D
type: R/W
reset vlaue: 0000 0000
deteils: tap threshold
giải thích: ngưỡng này giúp phát hiện một hành đồng "gõ" hoặc "chạm" có diễn ra hay không ? có thể dùng để loại bỏ các hành động "gõ" hoặc thực hiện một chức năng phản ứng khi có hành động "rõ".

3. thanh ghi OFSX
address: 0x1E
type: R/W 
reset value: 0000 0000
deteils: X-axis offset (bù trục x)
giải thích: Bù trục X (X-axis offset) là một giá trị được sử dụng để hiệu chỉnh sai lệch hoặc độ lệch không mong muốn trên trục X trong các thiết bị cảm biến, như gia tốc kế hoặc con quay hồi chuyển
Trong thực tế, các cảm biến có thể không hoàn hảo và có thể xuất hiện sai số ở vị trí "không" (zero point) của từng trục. Ví dụ, khi thiết bị nằm yên hoàn toàn, giá trị đo trên trục X có thể không phải là 0 như mong đợi mà có một giá trị nhỏ hơn hoặc lớn hơn, đó gọi là độ lệch (offset).

Giá trị bù trục X giúp hiệu chỉnh lại sai lệch này bằng cách cộng hoặc trừ một giá trị cụ thể để đưa điểm "không" (zero) về đúng vị trí.

4. thanh ghi OFSY
addr: 0x1F
type: R/W
reset value: 0000 0000
deteils: Y-axis offset

5. thanh ghi OFSZ
addr: 0x20
type: R/W 
reset value: 0000 0000
deteils: Z-axis offset

6. thanh ghi DUR
addr: 0x21
type: R/W
reset value: 0000 0000
deteils: Tap duration. 
Tap Duration (thời gian gõ) là một tham số quan trọng được sử dụng để xác định khoảng thời gian tối đa mà một cú gõ (tap) được coi là hợp lệ.

7. thanh ghi Latent
addr: 0x22 
type: R/W
reset value: 0000 0000
deteils: Tap latency. 
Tap latency là khoảng thời gian tối thiểu giữa hai cú gõ (tap) liên tiếp để chúng được coi là các sự kiện riêng biệt. Tham số này được sử dụng trong cảm biến, chẳng hạn như gia tốc kế ADXL345, để tránh nhầm lẫn giữa một cú gõ đơn và các chuỗi gõ liên tiếp như gõ đôi (double tap).

8. thanh ghi Window
addr: 0x23
type: R/W
reset value: 0000 0000
deteils: tap window
Tap Window là khoảng thời gian cho phép nhận diện cú gõ thứ hai (tap) sau cú gõ đầu tiên trong các thao tác như gõ đôi (double tap). Đây là một tham số quan trọng trong cảm biến, ví dụ như gia tốc kế ADXL345, dùng để phân biệt gõ đơn và gõ đôi.

9. thanh ghi THRESH_ACT
addr: 0x24
type: R/W
reset value: 0000 0000
deteils: Activity threshold.
Activity threshold (Ngưỡng hoạt động) trong cảm biến gia tốc, chẳng hạn như ADXL345, là một giá trị được sử dụng để xác định ngưỡng gia tốc tối thiểu để cảm biến nhận diện rằng thiết bị đang hoạt động hoặc chuyển động.

10. thanh ghi THRESH_INACT
addr: 0x25
type: R/W
reset value: 0000 0000
deteils: Inactivity threshold. 
Inactivity threshold (Ngưỡng không hoạt động) trong cảm biến, chẳng hạn như ADXL345, là một giá trị được đặt để xác định trạng thái không chuyển động của thiết bị. Nó giúp cảm biến nhận biết khi nào thiết bị đang ở trạng thái tĩnh hoặc ít chuyển động, từ đó có thể kích hoạt các hành động như chuyển sang chế độ tiết kiệm năng lượng.

11. thanh ghi TIME_INACT
addr: 0x26
type: R/W
reset value: 0000 0000
deteils: Inactivity time.
Inactivity time (Thời gian không hoạt động) là khoảng thời gian mà gia tốc trên tất cả các trục (X, Y, và Z) phải duy trì ở dưới mức Inactivity Threshold (Ngưỡng không hoạt động) để cảm biến nhận diện rằng thiết bị đang ở trạng thái không hoạt động.\

12. thanh ghi ACT_INACT_CTL
addr: 0x27
type: R/W
reset value: 0000 0000
deteils: Axis enable control for activity and inactivity detection. (Điều khiển kích hoạt trục để phát hiện hoạt động và không hoạt động.)
Axis enable control for activity and inactivity detection nghĩa là việc kiểm soát kích hoạt các trục (X, Y, Z) để phát hiện hoạt động và không hoạt động của thiết bị. Đây là cách mà cảm biến, chẳng hạn như ADXL345, cho phép bạn chọn những trục nào sẽ được theo dõi khi phát hiện trạng thái hoạt động hoặc không hoạt động.

13. thanh ghi THRESH_FF
addr: 0x28
type: R/W
reset value: 0000 0000
deteils: Free-fall threshold. (Ngưỡng rơi tự do.)
Free-fall threshold (Ngưỡng rơi tự do) là một giá trị được sử dụng trong các cảm biến, như gia tốc kế ADXL345, để xác định khi thiết bị đang trong trạng thái rơi tự do. Trong trạng thái này, cảm biến nhận thấy không còn gia tốc nào đáng kể được áp dụng (ngoài lực hấp dẫn) trên các trục X, Y, và Z.

14. thanh ghi TIME_FF
addr: 0x29
type: R/W
reset value: 0000 0000
deteils: Free-fall time. (Thời gian để xác định là đang bị rơi tự do)
Free-fall time (Thời gian rơi tự do) là khoảng thời gian mà cảm biến, chẳng hạn như ADXL345, xác định rằng gia tốc trên tất cả các trục (X, Y, và Z) đều ở dưới mức ngưỡng rơi tự do (Free-fall threshold). Đây là tham số quan trọng giúp cảm biến quyết định khi nào thiết bị thực sự ở trạng thái rơi tự do.

15. thanh ghi TAP_AXES
addr: 0x2A
type: R/W
reset value: 0000 0000
deteils: Axis control for tap/double tap. (Điều khiển trục cho gõ/nhấn đúp.)
Axis control for tap/double tap đề cập đến việc kiểm soát các trục (X, Y, Z) mà cảm biến sẽ theo dõi để phát hiện sự kiện gõ (tap) hoặc nhấn đúp (double tap). Điều này giúp lập trình viên lựa chọn cụ thể các trục cần giám sát khi kích hoạt tính năng cảm ứng gõ/nhấn.

16. thanh ghi ACT_TAP_STATUS
addr: 0x2B
type: R
reset value: 0000 0000
deteils:Source of tap/double tap. (Nguồn gốc của gõ/nhấn đúp.)
Source of tap/double tap (Nguồn gốc của gõ/nhấn đúp) đề cập đến việc xác định trục hoặc hướng cụ thể (X, Y, Z) đã tạo ra sự kiện gõ hoặc nhấn đúp. Trong cảm biến gia tốc như ADXL345, thông tin này giúp bạn biết được cú gõ hoặc nhấn đúp được phát hiện từ trục nào.

17. thanh ghi BW_RATE
addr: 0x2C
type: R/W
reset value: 00001010
deteils: Data rate and power mode control. (Điều khiển tốc độ dữ liệu và chế độ tiêu thụ năng lượng.)
Data rate and power mode control là cơ chế trong cảm biến, như ADXL345, được sử dụng để thiết lập:
Tốc độ truyền dữ liệu (Data rate): Quyết định tần suất cảm biến cập nhật dữ liệu gia tốc.
Chế độ tiêu thụ năng lượng (Power mode): Liên quan đến mức năng lượng mà cảm biến sử dụng tùy thuộc vào cài đặt và nhu cầu hoạt động.

18. thanh ghi POWER_CTL
addr: 0x2D
type: R/W
reset value: 0000 0000
deteils: Power-saving features control.  (Điều khiển các tính năng tiết kiệm năng lượng)
Power-saving features control đề cập đến các cơ chế hoặc cấu hình trong cảm biến, chẳng hạn như ADXL345, cho phép thiết bị tiết kiệm năng lượng khi không cần hoạt động liên tục hoặc khi ở trạng thái tĩnh.

19. thanh ghi INT_ENABLE
addr: 0x2E
type: R/W
reset value: 0000 0000
deteils: Interrupt enable control. (điều khiển kích hoạt ngắt)
Interrupt enable control là cơ chế cho phép lập trình viên kích hoạt hoặc vô hiệu hóa các tín hiệu ngắt (interrupts) trên cảm biến, chẳng hạn như ADXL345. Các ngắt này được sử dụng để thông báo cho bộ vi xử lý (microcontroller) về các sự kiện cụ thể được phát hiện bởi cảm biến, như chuyển động, gõ, hoặc trạng thái rơi tự do.

20. thanh ghi INT_MAP
addr: 0x2F
type: R/W
reset value: 0000 0000
deteils: Interrupt mapping control. (điều khiển ánh xạ ngắt)
Interrupt mapping control liên quan đến việc gán (mapping) các ngắt (interrupts) đến một chân (pin) đầu ra cụ thể của cảm biến, chẳng hạn như cảm biến ADXL345. Điều này cho phép bạn tùy chỉnh cách mà các ngắt được báo hiệu tới bộ vi xử lý (microcontroller) hoặc hệ thống điều khiển.

21. thanh ghi INT_SOURCE
addr: 0x30
type: R
reset value: 00000010
deteils: Source of interrupts.  (Nguồn gốc của ngắt.)
Source of interrupts (Nguồn gốc của ngắt) đề cập đến việc xác định sự kiện hoặc trạng thái nào đã kích hoạt một tín hiệu ngắt (interrupt) trong cảm biến, chẳng hạn như ADXL345. Thông tin này rất quan trọng để hiểu lý do tại sao ngắt được kích hoạt và để hệ thống có thể xử lý sự kiện tương ứng.

22. thanh ghi DATA_FORMAT
addr: 0x31
type: R/W
reset value: 00000000
deteils: Data format control. (Điều khiển định dạng dữ liệu.)
Data format control (Điều khiển định dạng dữ liệu) đề cập đến việc cấu hình cách dữ liệu được biểu diễn hoặc xuất ra từ cảm biến, chẳng hạn như ADXL345. Điều này bao gồm định dạng, độ phân giải, chế độ dữ liệu và căn chỉnh dữ liệu.

23. thanh ghi DATAX0
addr: 0x32
type: R
reset value: 00000000
deteils: X-Axis Data 0. (Dữ liệu trục X - Byte 0)
X-Axis Data 0 trong cảm biến như ADXL345 đại diện cho byte đầu tiên (byte thấp hơn - Least Significant Byte, LSB) trong dữ liệu gia tốc thu được từ trục X. Đây là một phần của dữ liệu 16-bit biểu diễn giá trị gia tốc trên trục X.

24. thanh ghi DATAX1
addr: 0x33
type: R
reset value: 00000000
deteils: X-Axis Data 1.  
note: gộp 2 thanh ghi này lại ta có giá trị của trục x 16 bit

25. thanh ghi DATAY0
addr: 0x34
type: R
reset value: 00000000
deteils: Y-Axis Data 0. 

26. thanh ghi DATAY1
addr: 0x35
type: R
reset value: 00000000
deteils: Y-Axis Data 1.

27. thanh ghi  DATAZ0
addr: 0x36
type: R
reset value:  00000000
deteils: Z-Axis Data 0.

28. thanh ghi DATAZ1
addr: 0x37
type: R
reset value: 00000000
deteils: Z-Axis Data 1.

29. thanh ghi FIFO_CTL
addr: 0x38
type: R/W
reset value: 00000000
deteils: FIFO control. 
FIFO control (Điều khiển FIFO) đề cập đến việc cấu hình và quản lý bộ đệm FIFO (First In, First Out) trong các cảm biến như ADXL345. FIFO là một cơ chế lưu trữ tạm thời dữ liệu, giúp giảm tải cho bộ vi xử lý bằng cách lưu trữ dữ liệu đầu ra của cảm biến trước khi chúng được xử lý hoặc đọc.

30. thanh ghi FIFO_STATUS
addr: 0x39
type: R
reset value: 00000000
deteils: FIFO status. 
FIFO status (Trạng thái FIFO) trong cảm biến như ADXL345 cung cấp thông tin về trạng thái hiện tại của bộ đệm FIFO (First In, First Out). Nó cho phép bạn theo dõi số lượng dữ liệu đã được lưu trữ trong bộ đệm và phát hiện các tình trạng như đầy bộ đệm hoặc dữ liệu bị tràn.

//////////////////////////////////////////

REGISTER DEFINITIONS (định nghĩa các thanh ghi)
Register 0x00-DEVID (Read Only)
______________________________________
D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
___|____|____|____|____|____|____|____|
1  |  1 |   1|  0 | 0  | 1  | 0  |  1 |
___|____|____|____|____|____|____|____|


Thanh ghi DEVID lưu trữ một mã định danh thiết bị cố định là 0xE5 (345 hệ bát phân).

Khi bắt đầu kết nối đến thiết bị qua giao tiếp I2C thì mình có thể đọc giá trị của thanh ghi này để xác định xem là có phải đúng là thiết bị ADXL345 hay không vì nếu đúng thì nó sẽ trả về 0xE5 tương ứng với giá trị 345 trong hệ bát phân

Register 0x31 - DATA FORMAT (Read/Write)
____________________________________________________________________
D7        | D6   | D5          | D4 | D3       | D2       | D1 | D0 |
__________|______|_____________|____|__________|__________|____|____|
SELF_TEST |  SPI |   INT_INVERT|  0 |   FUL_RES|  Justify |   Range |
__________|______|_____________|____|__________|__________|_________|

Thanh ghi DATA_FORMAT kiểm soát cách dữ liệu được trình bày từ thanh ghi 0x32 đến thanh ghi 0x37. Tất cả dữ liệu, ngoại trừ dữ liệu trong dải ±16 g, phải được cắt bớt để tránh hiện tượng tràn số (rollover).

Giải thích:
1.Thanh ghi DATA_FORMAT:
- Đây là thanh ghi trong cảm biến ADXL345 được sử dụng để định cấu hình cách dữ liệu 	gia tốc được trình bày.

- Dữ liệu được xuất ra từ các thanh ghi DATAX0 (0x32) đến DATAZ1 (0x37), tương ứng 	với giá trị gia tốc trên các trục X, Y, và Z.

2. Quy tắc về giới hạn dữ liệu (Clipping):
- Dữ liệu từ cảm biến phải nằm trong khoảng hợp lệ, tùy thuộc vào dải đo được chọn (±	2g, ±4g, ±8g, hoặc ±16g).

- Với các dải ±2g, ±4g, và ±8g, nếu giá trị vượt ra ngoài phạm vi, dữ liệu phải được "cắt bớt" (clipped) để tránh hiện tượng tràn số (rollover).

- Hiện tượng tràn số xảy ra khi giá trị dữ liệu vượt quá giới hạn mà nó có thể lưu trữ, dẫn đến kết quả không chính xác.

3. Dải đo ±16g:
- Trong trường hợp dải ±16g, dữ liệu không cần bị cắt bớt vì đây là dải rộng nhất và có thể chứa toàn bộ các giá trị gia tốc mà cảm biến có thể đo được

4. Ứng dụng thực tế:
- Đảm bảo độ chính xác: Việc cắt bớt dữ liệu ngoài phạm vi giúp ngăn chặn các lỗi đo lường.
- Tùy chỉnh dải đo: Lựa chọn và cấu hình dải đo phù hợp giúp tối ưu hóa hiệu suất cảm biến trong các ứng dụng cụ thể, ví dụ:
±2g: Nhạy cảm với các chuyển động nhỏ.
±16g: Đo chuyển động mạnh, chẳng hạn như rung động lớn.

giải thích các bit.

SELF_TEST Bit 
set bit này là 1 sẽ áp dụng tự kiểm tra SELT_TEST lên cảm biến, làm thay đổi dữ liệu đầu ra. set 0 sẽ disable feature này. 
bit này dùng trong kiểm thử thiết bị

SPI Bit 
Giá trị 1 trong bit SPI đặt thiết bị ở chế độ SPI 3 dây, còn giá trị 0 đặt thiết bị ở chế độ SPI 4 dây.

INT_INVERT Bit 
Giá trị 0 trong bit INT_INVERT đặt ngắt (interrupts) ở trạng thái hoạt động mức cao (active high), còn giá trị 1 đặt ngắt ở trạng thái hoạt động mức thấp (active low).

FULL_RES Bit

Khi bit này được đặt giá trị 1, thiết bị ở chế độ độ phân giải đầy đủ (full resolution mode), trong đó độ phân giải đầu ra tăng theo dải gia tốc g được cài đặt bởi các bit phạm vi (range bits), duy trì hệ số tỷ lệ 4 mg/LSB. Khi bit FULL_RES được đặt giá trị 0, thiết bị ở chế độ 10-bit, và các bit phạm vi xác định dải g tối đa cũng như hệ số tỷ lệ.

set bit này là 1 nó sẽ tự động điều chỉnh độ phân giải theo dải gia tốc g được cài đặt bởi các bit phạm vi, duy trì hệ số tỷ lệ 4 mg/LSB. 
bit này = 0 thì nó sẽ cố định độ phân giải là 10 bit và nó sẽ phụ thuộc vào nhiều hơn về range của g do đó nó chỉ phù hợp với một vài trường hợp nhất định như tiết kiệm năng lượng.

Justify Bit 

Cài đặt giá trị 1 trong bit justify chọn chế độ căn chỉnh về bên trái (left-justified) với phần quan trọng nhất (MSB - Most Significant Bit) ở đầu. Cài đặt giá trị 0 chọn chế độ căn chỉnh về bên phải (right-justified) kèm theo phần mở rộng dấu (sign extension).

căn chỉnh bên trái các bit quan trọng sẽ là MSB các bit khác sẽ được lắp đầy là 0
ví dụ nếu dữ liệu cảm biến là 6 bit: 101101 
thì dữ liệu output là: 10110100

nếu trường hợp căn chỉnh bên phải thì đầu ra sẽ như sau nếu dữ liệu nguyên thủy là -3 thì kết quả đầu ra là 1111 1101.

Range Bits 

D1 | D0      | g Range
0  |  0      |   +- 2g
0  |  1      |   +- 4g
1  |  0      |   +- 8g
1  |  1      |   +- 16g

giải thích thanh ghi POWER_CTL

Register 0x2D - POWER_CTL (Read/Write)
______________________________________________________
D7 | D6 | D5  | D4          | D3     | D2   | D1 | D0 |
___|____|_____|_____________|________|______|____|____|
0  | 0  | Link| AUTO_SLEEP  | Measure| Sleep| Wakeup  |
___|____|_____|_____________|________|______|_________|

Link Bit 
Khi bit link được đặt giá trị 1, và cả hai chức năng hoạt động (activity) và không hoạt động (inactivity) được kích hoạt, thì chức năng hoạt động sẽ bị trì hoãn cho đến khi không hoạt động được phát hiện. Sau khi hoạt động được phát hiện, chế độ phát hiện không hoạt động sẽ bắt đầu, ngăn cản việc phát hiện hoạt động. Bit này liên kết tuần tự hai chức năng hoạt động và không hoạt động. Khi bit này được đặt giá trị 0, các chức năng không hoạt động và hoạt động hoạt động đồng thời. Thông tin bổ sung có thể được tìm thấy trong phần Link Mode. Khi xóa giá trị của bit link, nên đặt thiết bị vào chế độ chờ (standby mode) và sau đó chuyển lại về chế độ đo lường (measurement mode) bằng một thao tác ghi tiếp theo. Điều này được thực hiện để đảm bảo rằng thiết bị được bù chính xác nếu chế độ ngủ (sleep mode) bị vô hiệu hóa thủ công; nếu không, vài mẫu dữ liệu đầu tiên sau khi bit link bị xóa có thể chứa thêm nhiễu, đặc biệt nếu thiết bị đang ở trạng thái ngủ khi bit được xóa.

Giải thích chi tiết:
Bit link và chức năng tuần tự (Serial Linking):
- Khi link bit = 1, các chức năng hoạt động (activity) và không hoạt động (inactivity) được kích hoạt tuần tự:
- Đầu tiên, chế độ activity không được kích hoạt cho đến khi trạng thái không hoạt động (inactivity) được phát hiện.
- Sau khi trạng thái không hoạt động chuyển thành hoạt động (activity), chế độ không hoạt động sẽ tự động bắt đầu.
- Điều này đảm bảo rằng hai chức năng không xung đột và chỉ một trạng thái được phát hiện tại một thời điểm.

Chức năng đồng thời (Concurrent):
- Khi link bit = 0, hai chức năng hoạt động và không hoạt động hoạt động đồng thời. Điều này cho phép thiết bị giám sát cả hai trạng thái một cách độc lập mà không cần tuần tự hóa.

Cách xử lý khi xóa bit link:
- Chuyển chế độ Standby trước khi xóa link bit:
  *Đặt thiết bị vào chế độ chờ sẽ đảm bảo các thành phần bên trong cảm biến được ổn định lại.
- Trở về chế độ đo lường:
* Sau khi xóa bit, chế độ đo lường được kích hoạt lại để tiếp tục thu thập dữ liệu.
- Tránh nhiễu ban đầu:
* Nếu thiết bị đang ở chế độ ngủ khi xóa bit mà không tuân theo quy trình chuẩn, dữ liệu đầu ra có thể chứa nhiễu.

AUTO_SLEEP Bit (bit tự động ngủ)

Nếu link bit được đặt, việc đặt giá trị 1 trong bit AUTO_SLEEP sẽ cho phép ADXL345 tự động chuyển sang chế độ ngủ (sleep mode) khi trạng thái không hoạt động (inactivity) được phát hiện (tức là khi gia tốc thấp hơn giá trị THRESH_INACT trong ít nhất khoảng thời gian được chỉ định bởi TIME_INACT). Việc đặt giá trị 0 sẽ tắt tính năng tự động chuyển sang chế độ ngủ. Xem phần mô tả về sleep bit trong tài liệu này để biết thêm thông tin. Khi xóa giá trị của bit AUTO_SLEEP, nên đặt thiết bị vào chế độ chờ (standby mode) và sau đó đưa trở lại chế độ đo (measurement mode) bằng một thao tác ghi tiếp theo. Điều này đảm bảo rằng thiết bị được bù chính xác nếu chế độ ngủ bị vô hiệu hóa thủ công; nếu không, vài mẫu dữ liệu đầu tiên sau khi xóa AUTO_SLEEP có thể chứa thêm nhiễu, đặc biệt nếu thiết bị đang ở chế độ ngủ khi bit được xóa. 

Giải thích chi tiết:
1. Tự động chuyển chế độ ngủ (AUTO_SLEEP)
Khi AUTO_SLEEP bit = 1:
- Cảm biến sẽ giám sát trạng thái gia tốc. Nếu gia tốc thấp hơn ngưỡng không hoạt động (THRESH_INACT) trong khoảng thời gian tối thiểu (TIME_INACT), cảm biến tự động chuyển sang chế độ ngủ (sleep mode).
- Chế độ ngủ giúp giảm mức tiêu thụ năng lượng.
Khi AUTO_SLEEP bit = 0:
- Chức năng chuyển sang chế độ ngủ tự động bị vô hiệu hóa. Cảm biến sẽ không chuyển sang chế độ ngủ dù trạng thái không hoạt động được phát hiện.

2. Liên kết với link bit:
- Link bit cho phép kết hợp chức năng hoạt động (activity) và không hoạt động (inactivity). Nếu link bit = 1, tính năng tự động ngủ sẽ được kích hoạt khi cảm biến phát hiện trạng thái không hoạt động.

3.Lưu ý khi xóa AUTO_SLEEP bit:
Chuyển sang chế độ Standby:
- Điều này cần thiết để đảm bảo các linh kiện bên trong cảm biến được bù chính xác, đặc biệt khi chế độ ngủ bị tắt thủ công.

Quay lại chế độ đo lường:
- Sau khi chỉnh sửa AUTO_SLEEP bit, chuyển cảm biến trở lại chế độ đo lường để hoạt động chính xác.

Tránh nhiễu ban đầu:
- Nếu cảm biến đang trong chế độ ngủ khi xóa AUTO_SLEEP bit mà không qua chế độ standby, dữ liệu đầu ra ban đầu có thể chứa nhiễu.

Measure Bit (bit đo lường)

Cài đặt giá trị 0 trong bit measure đưa thiết bị vào chế độ chờ (standby mode), và cài đặt giá trị 1 đưa thiết bị vào chế độ đo lường (measurement mode). Cảm biến ADXL345 khởi động ở chế độ chờ với mức tiêu thụ năng lượng tối thiểu.




