################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../dcmotor.c \
../ex_eeprom.c \
../i2c.c \
../main2.c \
../timer0.c \
../uart.c 

OBJS += \
./dcmotor.o \
./ex_eeprom.o \
./i2c.o \
./main2.o \
./timer0.o \
./uart.o 

C_DEPS += \
./dcmotor.d \
./ex_eeprom.d \
./i2c.d \
./main2.d \
./timer0.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


