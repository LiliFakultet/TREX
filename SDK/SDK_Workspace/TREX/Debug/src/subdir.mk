################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cactus.c \
../src/collision.c \
../src/input.c \
../src/main.c \
../src/platform.c \
../src/player.c \
../src/sprite.c \
../src/vga.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/cactus.o \
./src/collision.o \
./src/input.o \
./src/main.o \
./src/platform.o \
./src/player.o \
./src/sprite.o \
./src/vga.o 

C_DEPS += \
./src/cactus.d \
./src/collision.d \
./src/input.d \
./src/main.d \
./src/platform.d \
./src/player.d \
./src/sprite.d \
./src/vga.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -pedantic -Os -g3 -c -fmessage-length=0 -I../../TREX_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.b -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


