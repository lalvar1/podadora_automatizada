################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Inicializaciones/I2C.c \
../src/Inicializaciones/Kit_Principal.c \
../src/Inicializaciones/Oscilador.c \
../src/Inicializaciones/UART.c \
../src/Inicializaciones/WIFI.c \
../src/Inicializaciones/cr_startup_lpc175x_6x.c 

OBJS += \
./src/Inicializaciones/I2C.o \
./src/Inicializaciones/Kit_Principal.o \
./src/Inicializaciones/Oscilador.o \
./src/Inicializaciones/UART.o \
./src/Inicializaciones/WIFI.o \
./src/Inicializaciones/cr_startup_lpc175x_6x.o 

C_DEPS += \
./src/Inicializaciones/I2C.d \
./src/Inicializaciones/Kit_Principal.d \
./src/Inicializaciones/Oscilador.d \
./src/Inicializaciones/UART.d \
./src/Inicializaciones/WIFI.d \
./src/Inicializaciones/cr_startup_lpc175x_6x.d 


# Each subdirectory must supply rules for building sources it contributes
src/Inicializaciones/%.o: ../src/Inicializaciones/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Cristian\Documents\LPCXpresso_8.0.0_526\nuevo workspace\Plantilla\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


