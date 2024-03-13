################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: INDOOR_NAVIGATION.axf

# Tool invocations
INDOOR_NAVIGATION.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\jincy\Desktop\PROJECT\workingcode_obstacle\CMSISv2p00_LPC17xx\Debug" -Xlinker --gc-sections -Xlinker -Map=INDOOR_NAVIGATION.map -mcpu=cortex-m3 -mthumb -T "INDOOR_NAVIGATION_Debug.ld" -o "INDOOR_NAVIGATION.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) INDOOR_NAVIGATION.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size INDOOR_NAVIGATION.axf; arm-none-eabi-objcopy -O binary INDOOR_NAVIGATION.axf INDOOR_NAVIGATION.bin ; 	checksum -p LPC1768 -d INDOOR_NAVIGATION.bin;  	arm-none-eabi-objcopy -I binary INDOOR_NAVIGATION.bin -O ihex INDOOR_NAVIGATION.hex;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
