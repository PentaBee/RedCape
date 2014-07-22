################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/fpga_drv.o \
../src/i2c_drv.o \
../src/pwm_drv.o \
../src/pwm_marshal.o \
../src/pwm_server.o \
../src/tcp_marshal.o \
../src/tcpnet.o 

C_SRCS += \
../src/fpga_drv.c \
../src/i2c_drv.c \
../src/pwm_drv.c \
../src/pwm_marshal.c \
../src/pwm_server.c \
../src/tcp_marshal.c \
../src/tcpnet.c 

OBJS += \
./src/fpga_drv.o \
./src/i2c_drv.o \
./src/pwm_drv.o \
./src/pwm_marshal.o \
./src/pwm_server.o \
./src/tcp_marshal.o \
./src/tcpnet.o 

C_DEPS += \
./src/fpga_drv.d \
./src/i2c_drv.d \
./src/pwm_drv.d \
./src/pwm_marshal.d \
./src/pwm_server.d \
./src/tcp_marshal.d \
./src/tcpnet.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -DM_LITTLE_ENDIAN -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


