################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/I_node.c \
../src/blockio.c \
../src/close_file.c \
../src/create_file.c \
../src/delete_file.c \
../src/get_size.c \
../src/get_type.c \
../src/globdata.c \
../src/initialize.c \
../src/open_file.c \
../src/read_dir.c \
../src/read_file.c \
../src/sfstest.c \
../src/super_block.c \
../src/write_file.c 

OBJS += \
./src/I_node.o \
./src/blockio.o \
./src/close_file.o \
./src/create_file.o \
./src/delete_file.o \
./src/get_size.o \
./src/get_type.o \
./src/globdata.o \
./src/initialize.o \
./src/open_file.o \
./src/read_dir.o \
./src/read_file.o \
./src/sfstest.o \
./src/super_block.o \
./src/write_file.o 

C_DEPS += \
./src/I_node.d \
./src/blockio.d \
./src/close_file.d \
./src/create_file.d \
./src/delete_file.d \
./src/get_size.d \
./src/get_type.d \
./src/globdata.d \
./src/initialize.d \
./src/open_file.d \
./src/read_dir.d \
./src/read_file.d \
./src/sfstest.d \
./src/super_block.d \
./src/write_file.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -std=c99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


