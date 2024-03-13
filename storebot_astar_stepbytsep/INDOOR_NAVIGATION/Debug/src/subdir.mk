################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/astar.c \
../src/cr_startup_lpc176x.c \
../src/display_func.c \
../src/functions.c \
../src/indooor_nav_main.c \
../src/obst_coordinate_to_grid.c \
../src/uart1.c 

OBJS += \
./src/astar.o \
./src/cr_startup_lpc176x.o \
./src/display_func.o \
./src/functions.o \
./src/indooor_nav_main.o \
./src/obst_coordinate_to_grid.o \
./src/uart1.o 

C_DEPS += \
./src/astar.d \
./src/cr_startup_lpc176x.d \
./src/display_func.d \
./src/functions.d \
./src/indooor_nav_main.d \
./src/obst_coordinate_to_grid.d \
./src/uart1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\jincy\Desktop\PROJECT\astar_stepbytsep\CMSISv2p00_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\jincy\Desktop\PROJECT\astar_stepbytsep\CMSISv2p00_LPC17xx\inc" -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


