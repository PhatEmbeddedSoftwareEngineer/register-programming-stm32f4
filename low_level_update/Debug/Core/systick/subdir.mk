################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/systick/systick.cpp 

OBJS += \
./Core/systick/systick.o 

CPP_DEPS += \
./Core/systick/systick.d 


# Each subdirectory must supply rules for building sources it contributes
Core/systick/%.o Core/systick/%.su Core/systick/%.cyclo: ../Core/systick/%.cpp Core/systick/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/register-programming-stm32f4/low_level_update/Core/adc" -I"D:/register-programming-stm32f4/low_level_update/Core/adc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-systick

clean-Core-2f-systick:
	-$(RM) ./Core/systick/systick.cyclo ./Core/systick/systick.d ./Core/systick/systick.o ./Core/systick/systick.su

.PHONY: clean-Core-2f-systick

