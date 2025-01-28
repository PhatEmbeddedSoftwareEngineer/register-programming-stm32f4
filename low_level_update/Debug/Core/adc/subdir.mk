################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/adc/adc.cpp 

OBJS += \
./Core/adc/adc.o 

CPP_DEPS += \
./Core/adc/adc.d 


# Each subdirectory must supply rules for building sources it contributes
Core/adc/adc.o: ../Core/adc/adc.cpp Core/adc/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/register-programming-stm32f4/low_level_update/Core/adc" -I"D:/register-programming-stm32f4/low_level_update/Core/adc" -I"D:/register-programming-stm32f4/low_level_update/Core/uart_lib" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-adc

clean-Core-2f-adc:
	-$(RM) ./Core/adc/adc.cyclo ./Core/adc/adc.d ./Core/adc/adc.o ./Core/adc/adc.su

.PHONY: clean-Core-2f-adc

