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
./src/I_node.c \
./src/block_func.c \
./src/blockio.c \
./src/close_file.c \
./src/create_file.c \
./src/delete_file.c \
./src/error.c \
./src/free_block_list.c \
./src/get_size.c \
./src/get_type.c \
./src/glob_func.c \
./src/index_block.c \
./src/initialize.c \
./src/mount.c \
./src/open_file.c \
./src/read_dir.c \
./src/read_file.c \
./src/sfstest.c \
./src/super_block.c \
./src/system_open_file_table.c \
./src/traverse_tree.c \
./src/write_file.c 

OBJS += \
./src/I_node.o \
./src/block_func.o \
./src/blockio.o \
./src/close_file.o \
./src/create_file.o \
./src/delete_file.o \
./src/error.o \
./src/free_block_list.o \
./src/get_size.o \
./src/get_type.o \
./src/glob_func.o \
./src/index_block.o \
./src/initialize.o \
./src/mount.o \
./src/open_file.o \
./src/read_dir.o \
./src/read_file.o \
./src/sfstest.o \
./src/super_block.o \
./src/system_open_file_table.o \
./src/traverse_tree.o \
./src/write_file.o 

C_DEPS += \
./src/I_node.d \
./src/block_func.d \
./src/blockio.d \
./src/close_file.d \
./src/create_file.d \
./src/delete_file.d \
./src/error.d \
./src/free_block_list.d \
./src/get_size.d \
./src/get_type.d \
./src/glob_func.d \
./src/index_block.d \
./src/initialize.d \
./src/mount.d \
./src/open_file.d \
./src/read_dir.d \
./src/read_file.d \
./src/sfstest.d \
./src/super_block.d \
./src/system_open_file_table.d \
./src/traverse_tree.d \
./src/write_file.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ./src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -fshort-enums -std=c99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

