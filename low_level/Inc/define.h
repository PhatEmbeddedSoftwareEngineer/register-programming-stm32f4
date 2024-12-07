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
#define APB1_BASE				(PERIPH_BASE + OFFSET_APB1)

#define OFFSET_TIM2				(0x0000UL)
#define TIM2_BASE				(APB1_BASE + OFFSET_TIM2)

#define OFFSET_TIM3				(0x0400UL)
#define TIM3_BASE				(APB1_BASE + OFFSET_TIM3)

#define OFFSET_TIM4				(0x0800UL)
#define TIM4_BASE				(APB1_BASE + OFFSET_TIM4)

#define OFFSET_TIM5 			(0x0C00UL)
#define TIM5_BASE				(APB1_BASE + OFFSET_TIM5)

#define OFFSET_RTC				(0x2800UL)
#define RTC_REGISTER_BASE		(OFFSET_RTC + APB1_BASE)

#define OFFSET_WWDG				(0x2C00UL)
#define WWDG_BASE				(OFFSET_WWDG + APB1_BASE)

#define OFFSET_IWDG				(0x3000UL)
#define IWDG_BASE				(OFFSET_IWDG + APB1_BASE)

#define OFFSET_I2S2ext			(0x3400UL)
#define I2S2ext_BASE			(OFFSET_I2S2ext + APB1_BASE)

#define OFFSET_SPI2				(0x3800UL)
#define SPI2_BASE				(OFFSET_SPI2 + APB1_BASE)

#define OFFSET_SPI3  			(0x3C00UL)
#define SPI3_BASE				(OFFSET_SPI3 + APB1_BASE)

#define OFFSET_I2S3				(0x4000UL)
#define IS23_BASE				(OFFSET_I2S3 + APB1_BASE)

#define OFFSET_USART2			(0x4400UL)
#define USART2_BASE				(OFFSET_USART2 + APB1_BASE)

#define OFFSET_I2C1				(0x5400UL)
#define I2C1_BASE				(OFFSET_I2C1 + APB1_BASE)

#define OFFSET_I2C2				(0x5800UL)
#define I2C2_BASE				(OFFSET_I2C2 + APB1_BASE)

#define OFFSET_I2C3				(0x5C00UL)
#define I2C3_BASE				(OFFSET_I2C3 + APB1_BASE)

#define OFFSET_PWR				(0x7000UL)
#define PWR_BASE				(OFFSET_PWR + APB1_BASE)

#define OFFSET_APB2				(0x00007400UL)
#define APB2_BASE				(OFFSET_APB2 + PERIPH_BASE) // (0x40000000UL) + (0x00007400UL) = 0x40007400

#define OFFSET_TIM1				(0x00010000UL)
#define TIM1_BASE				(OFFSET_TIM1 + APB2_BASE)

#define OFFSET_TIM8				(0x00010400UL)
#define TIM8_BASE				(OFFSET_TIM8 + APB2_BASE)

#define OFFSET_USART1			(0x00011000UL)
//#define USART1_BASE				(OFFSET_USART1 + APB2_BASE) // 0x40007400 + (0x00011000UL) 0x40018400
#define USART1_BASE            0x40011000UL
#define OFFSET_USART6			(0x00011400UL)
#define USART6_BASE				(OFFSET_USART6 + APB2_BASE)

#define OFFSET_ADC1				(0x00012000UL)
#define ADC1_BASE				(OFFSET_ADC1 + APB2_BASE)

#define OFFSET_SDIO				(0x00012C00UL)
#define SDIO_BASE				(OFFSET_SDIO + APB2_BASE)

#define OFFSET_SPI1				(0x00013000UL)
#define SPI1_BASE				(OFFSET_SPI1 + APB2_BASE)

#define OFFSET_SPI4				(0x00013400UL)
#define SPI4_BASE				(OFFSET_SPI4 + APB2_BASE)

#define OFFSET_SYSCFG			(0x00013800UL)
#define SYSCFG_BASE				(OFFSET_SYSCFG + APB2_BASE)

#define OFFSET_EXTI				(0x00013C00UL)
#define EXTI_BASE				(OFFSET_EXTI + APB2_BASE)

#define OFFSET_TIM9				(0x00014000UL)
#define TIM9_BASE				(OFFSET_TIM9 + APB2_BASE)

#define OFFSET_TIM10			(0x00014400UL)
#define TIM10_BASE				(OFFSET_TIM10 + APB2_BASE)

#define OFFSET_TIM11			(0x00014800UL)
#define TIM11_BASE				(OFFSET_TIM11 + APB2_BASE)

#define OFFSET_AHB2				(0x10000000UL)
#define AHB2_BASE				(OFFSET_AHB2 + PERIPH_BASE)

#define OFFSET_USB_OTG_FS		(0x0000UL)
#define USB_OTG_FS_BASE 		(OFFSET_USB_OTG_FS + AHB_BASE)

// continue
#define RCC_AHB1ENR_OFFSET			(0x30UL)
#define BASE_RCC_AHB1ENR			(*(volatile unsigned int*)(RCC_BASE + RCC_AHB1ENR_OFFSET))



#define GPIO_MODER_OFFSET		(0x00UL)
#define GPIOA_MODER				(*(volatile unsigned int*)(GPIOA_BASE + GPIO_MODER_OFFSET))

#define GPIO_ODR_OFFSET			(0x14UL)
#define GPIOA_ODR				(*(volatile unsigned int*)(GPIO_ODR_OFFSET + GPIOA_BASE))

#define PIN5					(1U<<5)
#define LED_PIN					PIN5