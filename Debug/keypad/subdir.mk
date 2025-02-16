################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../keypad/kp.c 

OBJS += \
./keypad/kp.o 

C_DEPS += \
./keypad/kp.d 


# Each subdirectory must supply rules for building sources it contributes
keypad/%.o keypad/%.su keypad/%.cyclo: ../keypad/%.c keypad/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32_workspace_IDE/i2c_lcd/i2c" -I"D:/STM32_workspace_IDE/i2c_lcd/i2c" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I"D:/STM32_workspace_IDE/i2c_lcd/keypad" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-keypad

clean-keypad:
	-$(RM) ./keypad/kp.cyclo ./keypad/kp.d ./keypad/kp.o ./keypad/kp.su

.PHONY: clean-keypad

