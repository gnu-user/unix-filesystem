################################################################################
# SneakyFS Makefile
#
# Jonathan Gillett
# Joseph Heron
# Daniel Smullen
#
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
./I_node.c \
./block_func.c \
./blockio.c \
./close_file.c \
./create_file.c \
./delete_file.c \
./error.c \
./free_block_list.c \
./get_size.c \
./get_type.c \
./glob_func.c \
./index_block.c \
./initialize.c \
./mount.c \
./open_file.c \
./read_dir.c \
./read_file.c \
./sfstest.c \
./super_block.c \
./system_open_file_table.c \
./traverse_tree.c \
./write_file.c 

OBJS += \
./I_node.o \
./block_func.o \
./blockio.o \
./close_file.o \
./create_file.o \
./delete_file.o \
./error.o \
./free_block_list.o \
./get_size.o \
./get_type.o \
./glob_func.o \
./index_block.o \
./initialize.o \
./mount.o \
./open_file.o \
./read_dir.o \
./read_file.o \
./sfstest.o \
./super_block.o \
./system_open_file_table.o \
./traverse_tree.o \
./write_file.o 

C_DEPS += \
./I_node.d \
./block_func.d \
./blockio.d \
./close_file.d \
./create_file.d \
./delete_file.d \
./error.d \
./free_block_list.d \
./get_size.d \
./get_type.d \
./glob_func.d \
./index_block.d \
./initialize.d \
./mount.d \
./open_file.d \
./read_dir.d \
./read_file.d \
./sfstest.d \
./super_block.d \
./system_open_file_table.d \
./traverse_tree.d \
./write_file.d 


# Each subdirectory must supply rules for building sources it contributes
./%.o: ./%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -fshort-enums -std=c99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


