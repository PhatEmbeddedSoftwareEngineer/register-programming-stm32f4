#include <stdint.h>

#define RCC_BASE_ADDR	0x40023800
#define GPIOD_BASE_ADDR	0x40020C00


int main(void)
{
	uint32_t *RCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*RCC_AHB1ENR |= (1U << 3);

	uint32_t *GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR);
	*GPIOD_MODER |= (1U << 30);

	uint32_t *GPIOD_ODR = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
	while(1)
	{
		*GPIOD_ODR ^= (1U << 15);
		for(int i = 0; i < 1000000;i++);
	}

}
