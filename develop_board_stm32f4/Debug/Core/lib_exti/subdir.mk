################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/lib_exti/exti.c 

OBJS += \
./Core/lib_exti/exti.o 

C_DEPS += \
./Core/lib_exti/exti.d 


# Each subdirectory must supply rules for building sources it contributes
Core/lib_exti/%.o Core/lib_exti/%.su Core/lib_exti/%.cyclo: ../Core/lib_exti/%.c Core/lib_exti/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/register-programming-stm32f4/develop_board_stm32f4/Core/lib_uart" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-lib_exti

clean-Core-2f-lib_exti:
	-$(RM) ./Core/lib_exti/exti.cyclo ./Core/lib_exti/exti.d ./Core/lib_exti/exti.o ./Core/lib_exti/exti.su

.PHONY: clean-Core-2f-lib_exti

