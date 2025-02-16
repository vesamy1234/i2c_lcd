################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../i2c/i2c.c 

OBJS += \
./i2c/i2c.o 

C_DEPS += \
./i2c/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
i2c/%.o i2c/%.su i2c/%.cyclo: ../i2c/%.c i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32_workspace_IDE/i2c_lcd/i2c" -I"D:/STM32_workspace_IDE/i2c_lcd/i2c" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I"D:/STM32_workspace_IDE/i2c_lcd/keypad" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-i2c

clean-i2c:
	-$(RM) ./i2c/i2c.cyclo ./i2c/i2c.d ./i2c/i2c.o ./i2c/i2c.su

.PHONY: clean-i2c

