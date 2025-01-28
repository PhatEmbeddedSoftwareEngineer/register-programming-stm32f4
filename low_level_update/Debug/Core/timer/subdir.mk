################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/timer/timer.cpp 

OBJS += \
./Core/timer/timer.o 

CPP_DEPS += \
./Core/timer/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/timer/%.o Core/timer/%.su Core/timer/%.cyclo: ../Core/timer/%.cpp Core/timer/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/register-programming-stm32f4/low_level_update/Core/adc" -I"D:/register-programming-stm32f4/low_level_update/Core/adc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-timer

clean-Core-2f-timer:
	-$(RM) ./Core/timer/timer.cyclo ./Core/timer/timer.d ./Core/timer/timer.o ./Core/timer/timer.su

.PHONY: clean-Core-2f-timer

