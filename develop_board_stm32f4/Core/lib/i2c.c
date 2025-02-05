#include "i2c.h"



void init_i2c1(void)
{
    // Enable clock access to GPIOB due to we are use PB8 and PB9 as if SCL , SDA
    RCC->RCC_AHB1ENR |= GPIOB_EN;
    // set PB8 and PB9 mode to alternate function
    GPIOB->GPIO_MODER |= (2U << 16); // for PB8
    GPIOB->GPIO_MODER |= (2U << 18); // for PB9
    /*set PB8 and PB9 is output type open drain */
    GPIOB->GPIO_OTYPER |= (1U << 8); // for PB8
    GPIOB->GPIO_OTYPER |= (1U << 9); // for PB9
    /*Enable pull-up for PB8 and PB9*/
    GPIOB->GPIO_PUPDR |= (1U << 16); // for PB8
    GPIOB->GPIO_PUPDR |= (1U << 18); // for PB9
    /*set alternate function*/
    GPIOB->GPIO_AFR[1] |= (4U << 0); // AF4 for I2C1_SCL for PB8
    GPIOB->GPIO_AFR[1] |= (4U << 4); // AF4 for I2C1_SDA for PB9

    /*enable clock access to I2C1 */
    RCC->RCC_APB1ENR |= I2C1_EN;
    /*Software reset */
    I2C1->I2C_CR1 |= (1U << 15); 
    /*Come out of reset mode*/
    I2C1->I2C_CR1 &= ~(1U << 15);
    /*Set peripheral clock frequency*/
    // due to we are use hsi default 16mhz 
    I2C1->I2C_CR2 |= (1U << 4); // 16mhz 
    /*Set I2C to standard mode, 100Khz clock*/
    I2C1->I2C_CCR &= ~(1U << 15); // Standby mode
    // Cách tính đã ghi rõ trong document embedded thực thụ
    I2C1->I2C_CCR |= (I2C1_100KHZ_HSI << 0);
    /*Set rise time*/
    // Tại sao lại là 17 đã ghi rõ trong embedded document thực thụ
    I2C1->I2C_TRISE |= (MAX_RISE_TIME_SM_MODE << 0);
    /*Enable I2C1 module */
    I2C1->I2C_CR1 |= PERIPHERAL_EN;

}

/**
 * params: saddr: address slave 
 *         maddr: memory address
 *         data: store data
 */

void I2C1_byteRead(char saddr, char maddr, char *data)
{
    volatile int temp; // for read SR2
    
    /*Wait until bus not busy*/
    while( (I2C1->I2C_SR2 & SR2_BUSY) );

    /*generate start */
    I2C1->I2C_CR1 |= CR1_START;

    /*Wait until Start condition generated. */
    while(!(I2C1->I2C_SR1 & SR1_SB));
    /*Transmit slave address + write*/
	// explain: địa chỉ này dịch trái 1 bit ví dụ 
	// saddr = 0000 1101 sau dòng mã này se là 
	// 0001 1010 , bit cuối của byte này là 0 điều đó có nghĩa là bit 
	// r/w là write cho phép ghi
	// còn 0001 101 là địa chỉ của slave 
	I2C1->I2C_DR = saddr << 1; 

    /*wait end of address transmission */
    while(!(I2C1->I2C_SR1 & SR1_ADDR));

    /*Clear addr flag*/
	/*Read value SR2 that also means clear SR1_ADDR*/
    temp = I2C1->I2C_SR2;
    
    /*Send memory address*/
    I2C1->I2C_DR = maddr;

    /*Wait complete transmission */
    while(!(I2C1->I2C_SR1 & SR1_TXE));

    /*generate restart*/
    I2C1->I2C_CR1 |= CR1_START;

    /*Wait until Start condition generated. */
    while(!(I2C1->I2C_SR1 & SR1_SB));

    /*Transmit slave address + read
    bit r/w = 1 is read
    */
	I2C1->I2C_DR = saddr << 1 | 1;

    /*wait end of address transmission */
    while(!(I2C1->I2C_SR1 & SR1_ADDR));

    /*Disable Acknowledge*/
	I2C1->I2C_CR1 &= ~ CR1_ACK;

    /*Clear addr flag*/
	temp = I2C1->I2C_SR2;

    /*Generate stop after data received*/
	I2C1->I2C_CR1 |= CR1_STOP; 

    /*Wait until RxNE flag is set tức là nó không empty*/
	while(!(I2C1->I2C_SR1 & SR1_RXNE));

    /*Data not empty that also mean have data in DR register*/
	*data++ = I2C1->I2C_DR;


}