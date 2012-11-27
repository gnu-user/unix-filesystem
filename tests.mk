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
./tests/suite_blockio.c \
./tests/suite_free_block_list.c \
./tests/suite_glob_func.c \
./tests/suite_index_block.c \
./tests/unit_tests.c 

OBJS += \
./tests/suite_blockio.o \
./tests/suite_free_block_list.o \
./tests/suite_glob_func.o \
./tests/suite_index_block.o \
./tests/unit_tests.o 

C_DEPS += \
./tests/suite_blockio.d \
./tests/suite_free_block_list.d \
./tests/suite_glob_func.d \
./tests/suite_index_block.d \
./tests/unit_tests.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ./tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -fshort-enums -std=c99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

