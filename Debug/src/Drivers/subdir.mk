################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers/FW_ADC.c \
../src/Drivers/FW_IMU.c \
../src/Drivers/FW_TIMERS.c \
../src/Drivers/FW_UART.c \
../src/Drivers/GPIO.c \
../src/Drivers/IAP.c \
../src/Drivers/PWM.c \
../src/Drivers/Systick.c 

OBJS += \
./src/Drivers/FW_ADC.o \
./src/Drivers/FW_IMU.o \
./src/Drivers/FW_TIMERS.o \
./src/Drivers/FW_UART.o \
./src/Drivers/GPIO.o \
./src/Drivers/IAP.o \
./src/Drivers/PWM.o \
./src/Drivers/Systick.o 

C_DEPS += \
./src/Drivers/FW_ADC.d \
./src/Drivers/FW_IMU.d \
./src/Drivers/FW_TIMERS.d \
./src/Drivers/FW_UART.d \
./src/Drivers/GPIO.d \
./src/Drivers/IAP.d \
./src/Drivers/PWM.d \
./src/Drivers/Systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/%.o: ../src/Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Cristian\Documents\LPCXpresso_8.0.0_526\nuevo workspace\Plantilla\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


