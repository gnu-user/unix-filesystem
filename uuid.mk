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
./lib/uuid/clear.c \
./lib/uuid/compare.c \
./lib/uuid/copy.c \
./lib/uuid/gen_uuid.c \
./lib/uuid/isnull.c \
./lib/uuid/pack.c \
./lib/uuid/parse.c \
./lib/uuid/unpack.c \
./lib/uuid/unparse.c \
./lib/uuid/uuid_time.c 

OBJS += \
./lib/uuid/clear.o \
./lib/uuid/compare.o \
./lib/uuid/copy.o \
./lib/uuid/gen_uuid.o \
./lib/uuid/isnull.o \
./lib/uuid/pack.o \
./lib/uuid/parse.o \
./lib/uuid/unpack.o \
./lib/uuid/unparse.o \
./lib/uuid/uuid_time.o 

C_DEPS += \
./lib/uuid/clear.d \
./lib/uuid/compare.d \
./lib/uuid/copy.d \
./lib/uuid/gen_uuid.d \
./lib/uuid/isnull.d \
./lib/uuid/pack.d \
./lib/uuid/parse.d \
./lib/uuid/unpack.d \
./lib/uuid/unparse.d \
./lib/uuid/uuid_time.d 


# Each subdirectory must supply rules for building sources it contributes
lib/uuid/%.o: ./lib/uuid/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -fshort-enums -std=c99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


