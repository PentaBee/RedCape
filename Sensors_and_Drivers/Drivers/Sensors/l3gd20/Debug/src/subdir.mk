################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/demo_l3gd20.c \
../src/i2c_drv.c \
../src/l3gd20.c 

OBJS += \
./src/demo_l3gd20.o \
./src/i2c_drv.o \
./src/l3gd20.o 

C_DEPS += \
./src/demo_l3gd20.d \
./src/i2c_drv.d \
./src/l3gd20.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


