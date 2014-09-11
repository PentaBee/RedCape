################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/i2c_drv.c \
../src/mpu6000.c \
../src/mpu6000_demo.c 

OBJS += \
./src/i2c_drv.o \
./src/mpu6000.o \
./src/mpu6000_demo.o 

C_DEPS += \
./src/i2c_drv.d \
./src/mpu6000.d \
./src/mpu6000_demo.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


