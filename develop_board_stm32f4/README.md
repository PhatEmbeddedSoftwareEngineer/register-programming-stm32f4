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

