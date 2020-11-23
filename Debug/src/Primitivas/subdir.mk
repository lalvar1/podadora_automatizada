################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Primitivas/IMU.c \
../src/Primitivas/Serie.c \
../src/Primitivas/control.c \
../src/Primitivas/mensaje.c 

OBJS += \
./src/Primitivas/IMU.o \
./src/Primitivas/Serie.o \
./src/Primitivas/control.o \
./src/Primitivas/mensaje.o 

C_DEPS += \
./src/Primitivas/IMU.d \
./src/Primitivas/Serie.d \
./src/Primitivas/control.d \
./src/Primitivas/mensaje.d 


# Each subdirectory must supply rules for building sources it contributes
src/Primitivas/%.o: ../src/Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Cristian\Documents\LPCXpresso_8.0.0_526\nuevo workspace\Plantilla\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


