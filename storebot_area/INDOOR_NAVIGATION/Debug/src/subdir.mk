################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc176x.c \
../src/display_func.c \
../src/functions.c \
../src/i2c.c \
../src/indooor_nav_main.c \
../src/lsm303.c \
../src/motor_and_encoder.c \
../src/uart1.c \
../src/ultrasonic.c 

OBJS += \
./src/cr_startup_lpc176x.o \
./src/display_func.o \
./src/functions.o \
./src/i2c.o \
./src/indooor_nav_main.o \
./src/lsm303.o \
./src/motor_and_encoder.o \
./src/uart1.o \
./src/ultrasonic.o 

C_DEPS += \
./src/cr_startup_lpc176x.d \
./src/display_func.d \
./src/functions.d \
./src/i2c.d \
./src/indooor_nav_main.d \
./src/lsm303.d \
./src/motor_and_encoder.d \
./src/uart1.d \
./src/ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\jincy\Desktop\PROJECT\workingcode_area\CMSISv2p00_LPC17xx\inc" -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\jincy\Desktop\PROJECT\workingcode_area\CMSISv2p00_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


