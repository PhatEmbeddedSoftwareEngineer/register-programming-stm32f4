#ifndef ETP_GPIO_H
#define ETP_GPIO_H
#include "std_type.h"
typedef struct
{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFR[2];
}GPIO_t;

typedef struct 
{
    GPIO_t *pGPIO;
    volatile u8 pinNumber;
    volatile u8 mode;
    volatile u8 speed;
    //volatile u8 pull_up_down;
    volatile u8 otype;
    //volatile u8 altMode;
}GPIO_Config_t;


// #define RCC_AHB1_ADDRESS_OFFSET 					0x30
// #define REG(base, offset) 			((*((volatile unsigned int *)(base + offset))))


#define GPIOA_ADDRESS						0x40020000
#define GPIOB_ADDRESS						0x40020400
#define GPIOC_ADDRESS						0x40020800
#define GPIOD_ADDRESS						0x40020C00
#define GPIOE_ADDRESS						0x40021000

#define GPIOA 			((GPIO_t*)GPIOA_ADDRESS)
#define GPIOC			((GPIO_t*)GPIOC_ADDRESS)
#define GPIOB           ((GPIO_t*)GPIOB_ADDRESS)
#define GPIOD           ((GPIO_t*)GPIOD_ADDRESS)
#define GPIOE           ((GPIO_t*)GPIOE_ADDRESS)

#define GPIO_PIN_SET            0x01
#define GPIO_PIN_RESET          0x00

#define OUTPUT         (0x01U)
#define INPUT          (0x00U)
#define ALTF           (0x02U)
#define ANALOG         (0x03U)

#define TYPE_OUTPUT_PUPL         (0x00U)
#define TYPE_OUTPUT_OPENDRAIN    (0x01U)

#define LOW_SPEED           (0x00U)
#define MEDIUM_SPEED        (0x01U)
#define HIGH_SPEED          (0x02U)
#define MAX_SPEED           (0x03U)

#define NO_PUPD             0x00
#define PULL_UP             0x01
#define PULL_DOWN           0x02
#define RESERVED            0x03

#define PIN_0               0
#define PIN_1               1
#define PIN_2               2
#define PIN_3               3
#define PIN_4               4
#define PIN_5               5
#define PIN_6               6
#define PIN_7               7
#define PIN_8               8
#define PIN_9               9
#define PIN_10              10
#define PIN_11              11
#define PIN_12              12
#define PIN_13              13
#define PIN_14              14
#define PIN_15              15


void ETP_Output(GPIO_Config_t *config)
{
    GPIO_Config_t gpio;
    gpio.pGPIO = config->pGPIO;
    gpio.pGPIO->MODER |= (OUTPUT << (config->pinNumber)*2);
    gpio.pGPIO->OTYPER |= (TYPE_OUTPUT_PUPL << (config->pinNumber));
    gpio.pGPIO->OSPEEDR |= (MAX_SPEED << (config->pinNumber)*2);
}

void ETP_GPIO_WritePin(GPIO_t *PORT,u8 pin,u8 state)
{
    switch(state)
    {
        case GPIO_PIN_RESET:
            PORT->ODR &= ~(1<<pin);
            break;
        case GPIO_PIN_SET:  
            PORT->ODR |= (1<<pin);
            break;
        default:
            break;
    }
}

u8 ETP_GPIO_ReadPin(GPIO_t *PORT, u8 pin)
{
    return ((PORT->IDR>>pin)&0x01);
}

void ETP_GPIO_TogglePin(GPIO_t* PORT, u8 pin)
{
    PORT->ODR ^= (1<<pin);
}

void delay()
{
    for(int i=0;i<1000000;i++);
}



#endif
