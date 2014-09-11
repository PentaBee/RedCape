################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/demo_ds1339.c \
../src/ds1339.c \
../src/i2c_drv.c 

OBJS += \
./src/demo_ds1339.o \
./src/ds1339.o \
./src/i2c_drv.o 

C_DEPS += \
./src/demo_ds1339.d \
./src/ds1339.d \
./src/i2c_drv.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


