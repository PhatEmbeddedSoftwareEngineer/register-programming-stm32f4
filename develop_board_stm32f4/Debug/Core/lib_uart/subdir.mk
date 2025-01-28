################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lib_uart/uart.c 

OBJS += \
./Core/lib_uart/uart.o 

C_DEPS += \
./Core/lib_uart/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lib_uart/%.o Core/lib_uart/%.su Core/lib_uart/%.cyclo: ../Core/lib_uart/%.c Core/lib_uart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lib_uart

clean-Core-2f-lib_uart:
	-$(RM) ./Core/lib_uart/uart.cyclo ./Core/lib_uart/uart.d ./Core/lib_uart/uart.o ./Core/lib_uart/uart.su

.PHONY: clean-Core-2f-lib_uart

