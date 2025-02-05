################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lib/adc.c \
../Core/lib/dma.c \
../Core/lib/exti.c \
../Core/lib/systick.c \
../Core/lib/timer.c \
../Core/lib/uart.c 

OBJS += \
./Core/lib/adc.o \
./Core/lib/dma.o \
./Core/lib/exti.o \
./Core/lib/systick.o \
./Core/lib/timer.o \
./Core/lib/uart.o 

C_DEPS += \
./Core/lib/adc.d \
./Core/lib/dma.d \
./Core/lib/exti.d \
./Core/lib/systick.d \
./Core/lib/timer.d \
./Core/lib/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lib/%.o Core/lib/%.su Core/lib/%.cyclo: ../Core/lib/%.c Core/lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lib

clean-Core-2f-lib:
	-$(RM) ./Core/lib/adc.cyclo ./Core/lib/adc.d ./Core/lib/adc.o ./Core/lib/adc.su ./Core/lib/dma.cyclo ./Core/lib/dma.d ./Core/lib/dma.o ./Core/lib/dma.su ./Core/lib/exti.cyclo ./Core/lib/exti.d ./Core/lib/exti.o ./Core/lib/exti.su ./Core/lib/systick.cyclo ./Core/lib/systick.d ./Core/lib/systick.o ./Core/lib/systick.su ./Core/lib/timer.cyclo ./Core/lib/timer.d ./Core/lib/timer.o ./Core/lib/timer.su ./Core/lib/uart.cyclo ./Core/lib/uart.d ./Core/lib/uart.o ./Core/lib/uart.su

.PHONY: clean-Core-2f-lib

