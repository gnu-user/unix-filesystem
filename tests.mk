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
./suite_blockio.c \
./suite_free_block_list.c \
./suite_glob_func.c \
./suite_index_block.c \
./unit_tests.c 

OBJS += \
./suite_blockio.o \
./suite_free_block_list.o \
./suite_glob_func.o \
./suite_index_block.o \
./unit_tests.o 

C_DEPS += \
./suite_blockio.d \
./suite_free_block_list.d \
./suite_glob_func.d \
./suite_index_block.d \
./unit_tests.d 


# Each subdirectory must supply rules for building sources it contributes
./%.o: ./%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -fshort-enums -std=c99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


