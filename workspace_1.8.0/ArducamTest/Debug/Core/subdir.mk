################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/startup_stm32l1xx_hd.s \
../Core/startup_stm32l1xx_md.s \
../Core/startup_stm32l1xx_mdp.s \
../Core/startup_stm32l1xx_xl.s 

C_SRCS += \
../Core/system_stm32l1xx.c 

OBJS += \
./Core/startup_stm32l1xx_hd.o \
./Core/startup_stm32l1xx_md.o \
./Core/startup_stm32l1xx_mdp.o \
./Core/startup_stm32l1xx_xl.o \
./Core/system_stm32l1xx.o 

S_DEPS += \
./Core/startup_stm32l1xx_hd.d \
./Core/startup_stm32l1xx_md.d \
./Core/startup_stm32l1xx_mdp.d \
./Core/startup_stm32l1xx_xl.d 

C_DEPS += \
./Core/system_stm32l1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.s Core/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Core/%.o: ../Core/%.c Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core

clean-Core:
	-$(RM) ./Core/startup_stm32l1xx_hd.d ./Core/startup_stm32l1xx_hd.o ./Core/startup_stm32l1xx_md.d ./Core/startup_stm32l1xx_md.o ./Core/startup_stm32l1xx_mdp.d ./Core/startup_stm32l1xx_mdp.o ./Core/startup_stm32l1xx_xl.d ./Core/startup_stm32l1xx_xl.o ./Core/system_stm32l1xx.d ./Core/system_stm32l1xx.o

.PHONY: clean-Core

