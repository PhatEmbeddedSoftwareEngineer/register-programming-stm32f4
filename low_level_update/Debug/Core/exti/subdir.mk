################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/exti/exti.cpp 

OBJS += \
./Core/exti/exti.o 

CPP_DEPS += \
./Core/exti/exti.d 


# Each subdirectory must supply rules for building sources it contributes
Core/exti/exti.o: ../Core/exti/exti.cpp Core/exti/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"D:/register-programming-stm32f4/low_level_update/Core/adc" -I"D:/register-programming-stm32f4/low_level_update/Core/exti" -I"D:/register-programming-stm32f4/low_level_update/Core/uart_lib" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-exti

clean-Core-2f-exti:
	-$(RM) ./Core/exti/exti.cyclo ./Core/exti/exti.d ./Core/exti/exti.o ./Core/exti/exti.su

.PHONY: clean-Core-2f-exti

