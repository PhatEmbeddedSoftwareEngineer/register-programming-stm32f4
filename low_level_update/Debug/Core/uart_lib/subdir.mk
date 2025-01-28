################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/uart_lib/uart.cpp 

OBJS += \
./Core/uart_lib/uart.o 

CPP_DEPS += \
./Core/uart_lib/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/uart_lib/uart.o: ../Core/uart_lib/uart.cpp Core/uart_lib/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"D:/register-programming-stm32f4/low_level_update/Core/uart_lib" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/register-programming-stm32f4/low_level_update/Core/exti" -I"D:/register-programming-stm32f4/low_level_update/Core/systick" -I"D:/register-programming-stm32f4/low_level_update/Core/adc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-uart_lib

clean-Core-2f-uart_lib:
	-$(RM) ./Core/uart_lib/uart.cyclo ./Core/uart_lib/uart.d ./Core/uart_lib/uart.o ./Core/uart_lib/uart.su

.PHONY: clean-Core-2f-uart_lib

