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
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
Space_invaders.elf.size \

ELFCHECK += \
Space_invaders.elf.elfcheck \


# All Target
all: Space_invaders.elf secondary-outputs

# Tool invocations
Space_invaders.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../Space_invaders_bsp/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.b -mno-xl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "Space_invaders.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Space_invaders.elf.size: Space_invaders.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size Space_invaders.elf  |tee "Space_invaders.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

Space_invaders.elf.elfcheck: Space_invaders.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck Space_invaders.elf -hw ../../TREX_hw_platform/system.xml -pe microblaze_0  |tee "Space_invaders.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) Space_invaders.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
