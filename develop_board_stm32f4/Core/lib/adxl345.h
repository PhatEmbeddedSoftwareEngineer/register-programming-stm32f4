/*
 * adxl345.h
 *
 *  Created on: Mar 16, 2025
 *      Author: Phat
 */

#ifndef LIB_ADXL345_H_
#define LIB_ADXL345_H_

#include "i2c.h"
#include <stdint.h>

#define DEVID_R			0x00
#define DEVICE_ADDR		0x53
#define DATA_FORMAT_R	0x31
#define POWER_CTL_R		0x2D
// địa chỉ bắt đầu của thanh ghi DATAX0 của ADXL345
#define DATA_START_ADDR	0x32

// chọn resolution is +-4g rangge is 8g
#define FOUR_G			0x01

#define	RESET			0x00
#define	SET_MEASURE_B	0x08

/*
	giải thích scale factor
	vì phạm vi dải đo là +- 4 range ở phần cấu hình
	ta có độ phân giải là 10 bit
	nghĩa là tổng số bước: 1024 = 2^10
	vì dải đo là 8g (từ -4g đến +4g), mỗi bước sẽ tương ứng với gia tốc.
	scale factor = 8g/1024 = 0.00078g/step
*/
//const float FOUR_G_SCALE_FACT = 0.0078;

void adxl_init(void);
void adxl_read_values(uint8_t reg);


#endif /* LIB_ADXL345_H_ */
