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
./clear.c \
./compare.c \
./copy.c \
./gen_uuid.c \
./isnull.c \
./pack.c \
./parse.c \
./unpack.c \
./unparse.c \
._time.c 

OBJS += \
./clear.o \
./compare.o \
./copy.o \
./gen_uuid.o \
./isnull.o \
./pack.o \
./parse.o \
./unpack.o \
./unparse.o \
._time.o 

C_DEPS += \
./clear.d \
./compare.d \
./copy.d \
./gen_uuid.d \
./isnull.d \
./pack.d \
./parse.d \
./unpack.d \
./unparse.d \
._time.d 


# Each subdirectory must supply rules for building sources it contributes
./%.o: ./%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -fshort-enums -std=c99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


