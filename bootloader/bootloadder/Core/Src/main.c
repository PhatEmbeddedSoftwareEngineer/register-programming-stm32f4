#include <stdint.h>

int main(void)
{
	uint32_t *reset_handler = (uint32_t*)( 0x08004000 +  0x00000004);
	uint32_t reset_handler_address = *reset_handler;
	void (*handler)();
	handler = reset_handler_address;
	handler();
}
