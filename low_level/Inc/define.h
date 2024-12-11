#define PERIPH_BASE 			(0x40000000UL)

#define AHB1_BASE_OFFSET		(0x00020000UL)
#define AHB1_BASE  				(PERIPH_BASE + AHB1_BASE_OFFSET)

#define OFFSET_GPIOA			(0x0000UL)
#define GPIOA_BASE				(AHB1_BASE + OFFSET_GPIOA)

#define OFFSET_RCC				(0x3800UL)
#define RCC_BASE				(AHB1_BASE + OFFSET_RCC)

#define OFFSET_GPIOB			(0x0400UL)
#define GPIOB_BASE				(AHB1_BASE + OFFSET_GPIOB)

#define OFFSET_GPIOC			(0x0800UL)
#define GPIOC_BASE				(AHB1_BASE + OFFSET_GPIOC)

#define OFFSET_GPIOD			(0x0C00UL)
#define GPIOD_BASE				(AHB1_BASE + OFFSET_GPIOD)

#define OFFSET_GPIOE			(0x1000UL)
#define	GPIOE_BASE				(AHB1_BASE + OFFSET_GPIOE)

#define OFFSET_GPIOH			(0x1C00UL)
#define GPIOH_BASE				(AHB1_BASE + OFFSET_GPIOH)

#define OFFSET_CRC				(0x3000UL)
#define CRC_BASE				(AHB1_BASE + OFFSET_CRC)

#define OFFSET_FLASH			(0x3C00UL)
#define FLASH_BASE				(AHB1_BASE + OFFSET_FLASH)

#define OFFSET_DMA1				(0x6000UL)
#define DMA1_BASE				(AHB1_BASE + OFFSET_DMA1)

#define OFFSET_DMA2				(0x6400UL)
#define DMA2_BASE				(AHB1_BASE + OFFSET_DMA2)

#define OFFSET_APB1				(0x00000000UL)
#define APB1_BASE				(0x40000000UL)
#define TIM2_BASE				( 0x40000000UL)
#define TIM3_BASE				(0x40000400UL)
#define TIM4_BASE				(0x40000800UL)
#define TIM5_BASE				(0x40000C00UL )
#define RTC_REGISTER_BASE		(0x40002800UL)
#define WWDG_BASE				(0x40002C00UL)
#define IWDG_BASE				( 0x40003000UL)
#define I2S2ext_BASE			( 0x40003400UL)
#define SPI2_BASE				( 0x40003800UL )
#define SPI3_BASE				( 0x40003C00UL)
#define IS23_BASE				( 0x40004000UL)
#define USART2_BASE				( 0x40004400UL)
#define I2C1_BASE				(0x40005400UL)
#define I2C2_BASE				(0x40005800UL)
#define I2C3_BASE				( 0x40005C00UL)
#define PWR_BASE				(0x40007000UL)
#define APB2_BASE				( 0x40010000UL) // (0x40000000UL) + (0x00007400UL) = 0x40007400
#define TIM1_BASE				(0x40010000UL)
#define TIM8_BASE				(0x40010400UL)
#define USART1_BASE             (0x40011000UL)
#define USART6_BASE				(0x40011400UL)
#define ADC1_BASE				( 0x40012000UL)
#define SDIO_BASE				( 0x40012C00UL)
#define SPI1_BASE				(0x40013000UL)
#define SPI4_BASE				(0x40013400UL)
#define SYSCFG_BASE				(0x40013800UL)
#define EXTI_BASE				( 0x40013C00UL)
#define TIM9_BASE				(0x40014000UL)
#define TIM10_BASE				(0x40014400UL)
#define TIM11_BASE				(0x40014800UL)
#define AHB2_BASE				(0x50000000UL)
#define USB_OTG_FS_BASE 		(0x50000000UL)

// continue
#define RCC_AHB1ENR_OFFSET			(0x30UL)
#define BASE_RCC_AHB1ENR			(*(volatile unsigned int*)(RCC_BASE + RCC_AHB1ENR_OFFSET))

#define GPIO_MODER_OFFSET		(0x00UL)
#define GPIOA_MODER				(*(volatile unsigned int*)(GPIOA_BASE + GPIO_MODER_OFFSET))

#define GPIO_ODR_OFFSET			(0x14UL)
#define GPIOA_ODR				(*(volatile unsigned int*)(GPIO_ODR_OFFSET + GPIOA_BASE))

typedef struct 
{
	volatile uint32_t GPIO_MODER; // 0x00
	volatile uint32_t GPIO_OTYPER; // 0x04
	volatile uint32_t GPIO_OSPEEDR; // 0x08
	volatile uint32_t GPIO_PUPDR; // 0x0C
	volatile uint32_t GPIO_IDR; // 0x10
	volatile uint32_t GPIO_ODR; // 0x14
	volatile uint32_t GPIO_BSRR; // 0x18
	volatile uint32_t GPIO_LCKR; // 0x1C
	volatile uint32_t GPIO_AFR[2]; // 0x20 - 0x24  // 0 is low and 1 is high 
}GPIO_Typedef;

typedef struct 
{
	volatile uint32_t RCC_CR; 
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	uint32_t RESERVED[2];
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	uint32_t RESERVED2[2];
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	uint32_t RESERVED3[2];
	volatile uint32_t RCC_AHB1LENR; 
	volatile uint32_t RCC_AHB2LENR;
	uint32_t RESERVED4[2];
	volatile uint32_t RCC_APB1LENR;
	volatile uint32_t RCC_APB2LENR;
	uint32_t RESERVED5[2];
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	uint32_t RESERVED6[2];
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	uint32_t RESERVED7;
	volatile uint32_t RCC_DCKCFGR;

}RCC_Typedef;

typedef struct 
{
	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;
}USART_Typedef;

