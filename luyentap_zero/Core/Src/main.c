#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

// PB6 TX USART1
#define RCC_BASE_ADDR	0x40023800
#define GPIOD_BASE_ADDR 0x40020C00
#define SYSCFG_BASE_ADDR 0x40013800
#define EXTI_BASE_ADDR	0x40013C00
#define NVIC_ISER_BASE_ADDR 0xE000E100
#define VECTOR_TABLE_BASE_ADDR 0xE000ED08
#define GPIOA_BASE_ADDR	0x40020000
#define GPIOB_BASE_ADDR  0x40020400
#define USART1_BASE_ADDR  0x40011000


void initUsart1()
{
	// init clock gpiob
	uint32_t *RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*RCC_AHB1ENR |= (1U << 1);

	// init gpio pb6
	uint32_t *GPIOB_MODER = (uint32_t*)(GPIOB_BASE_ADDR);
	*GPIOB_MODER |= (0b10 << 12);

	uint32_t *GPIOB_AFRL = (uint32_t*)(GPIOB_BASE_ADDR + 0x20);
	*GPIOB_AFRL |= (0b0111 << 24);

	// init clock usart1
	uint32_t *RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0x44);
	*RCC_APB2ENR |= (1U << 4);

	uint32_t *USART_CR1 = (uint32_t*)(USART1_BASE_ADDR + 0x0C);
	*USART_CR1 &= ~ (1U << 15);

	*USART_CR1 &= ~ (1U << 12);

	uint32_t *USART_CR2 = (uint32_t*)(USART1_BASE_ADDR + 0x10);
	*USART_CR2 &= ~ (3U << 12);

	uint32_t *USART_BRR = (uint32_t*)(USART1_BASE_ADDR + 0x08);
	*USART_BRR = (8U << 4) | (11U << 0);

	*USART_CR1 |= (1U << 3);

	*USART_CR1 |= (1U << 13);

}

void transmissionEachByte(char *buf)
{
	uint32_t *USART_DR = (uint32_t*)(USART1_BASE_ADDR + 0x04);
	uint32_t *USART_SR = (uint32_t*)(USART1_BASE_ADDR );
	while(*buf)
	{
		while(!(*USART_SR & (1U << 6)));
		*USART_DR = *buf++;
		while(!(*USART_SR & (1U << 7)));
	}
}

void my_printf(const char *fmt,...)
{
	va_list args;
	va_start(args,fmt);
	char buffer[256];
	vsnprintf(buffer,sizeof(buffer),fmt,args);
	transmissionEachByte(buffer);
	va_end(args);
}

void initLed(void)
{
	uint32_t *RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*RCC_AHB1ENR |= (1U << 3);
	*RCC_AHB1ENR |= (1U << 0);

	uint32_t *GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR);
	*GPIOD_MODER &= 0b00000000;
	*GPIOD_MODER |= 0b01010101;



}

bool readStatePA0()
{
	uint32_t *GPIOA_IDR = (uint32_t*)(GPIOA_BASE_ADDR + 0x10);
	return *GPIOA_IDR & 0b1;
}
void gpioPD15SetHigh()
{
	uint32_t *GPIOD_ODR = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
	*GPIOD_ODR |= (1U << 15);
}
void gpioPD15SetLow()
{
	uint32_t *GPIOD_ODR = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
	*GPIOD_ODR &= ~ (1U << 15);
}
void my_handler()
{
	if(readStatePA0())
	{
		gpioPD15SetHigh();
		my_printf("high\n");
	}
	else
	{
		gpioPD15SetLow();
		my_printf("low\n");
	}
	uint32_t *EXTI_PR = (uint32_t*)(EXTI_BASE_ADDR + 0x14);
	*EXTI_PR |= (1U << 0);
	//myPrintf("hello world\n");
}
void button_interrupt_init()
{
	//enable clock for SYSCFG_EN
	uint32_t *RCC_APB2ENR = (uint32_t*)(RCC_BASE_ADDR + 0X44);
	*RCC_APB2ENR |= (1U << 14);

	// choose port 0 for EXTI
	uint32_t *SYSCFG_EXTICR1 = (uint32_t*)(SYSCFG_BASE_ADDR+0x08);
	*SYSCFG_EXTICR1 &= (0b0000 << 0);

	// choose falling edge
	uint32_t *EXTI_FTSR = (uint32_t *)(EXTI_BASE_ADDR + 0x0C);
	*EXTI_FTSR |= (1 << 0);

	// choose rising edge
	uint32_t *EXTI_RTSR = (uint32_t*)(EXTI_BASE_ADDR + 0x08);
	*EXTI_RTSR |= (1U << 0);

	// choose interrupt mask register
	uint32_t *EXTI_IMR = (uint32_t *)(EXTI_BASE_ADDR);
	*EXTI_IMR |= (1U << 0);

	// config NVIC accept signal from EXTI
	uint32_t *NVIC_ISER0 = (uint32_t*)NVIC_ISER_BASE_ADDR;
	*NVIC_ISER0 |= (1U << 6);

	// copy vector table from 0x00 up 0x20000000
	char *vector_table = 0x00;
	char *ram = (char*)0x20000000;

	for(int i = 0; i < 0x194; i++)
	{
		ram[i] = vector_table[i];
	}

	// notify with vector table
	uint32_t *VTOR = (uint32_t*)(VECTOR_TABLE_BASE_ADDR);
	*VTOR = 0x20000000;

	uint32_t *ptr =(uint32_t*) 0x20000058;
	*ptr = (uint32_t)my_handler;
}

void initButton()
{
	uint32_t *RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*RCC_AHB1ENR |= (1U << 0);
	uint32_t *GPIOA_MODER = (uint32_t*)(GPIOA_BASE_ADDR);
	*GPIOA_MODER &= ~ (3U << 0);
}

void initGpioPD15_output()
{
	uint32_t *RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*RCC_AHB1ENR |= (1U << 3);
	uint32_t *GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR);
	*GPIOD_MODER |= (0b01<<30);
}

int main(void)
{
	initButton();
	initGpioPD15_output();
	button_interrupt_init();
	initUsart1();
	//int cnt = 0;
	while(1)
	{
		//cnt++;
		//for(int i = 0; i < 100000;i++);
	}
}
