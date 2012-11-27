################################################################################
# SneakyFS Makefile
#
# Jonathan Gillett
# Joseph Heron
# Daniel Smullen
#
################################################################################

-include ../makefile.init

# Every subdirectory with source files must be described here
SUBDIRS := \
tests \
src \
lib/uuid \

# Include the static math library
LIBS := -lm

# All of the sources involved in the build are defined here
-include src.mk
-include tests.mk
-include uuid.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Executable name
EXEC_NAME := sneakyfs

# Remove alias
RM := rm -rf

# Installation directory
INSTALL_DIR := /usr/bin/

# TODO REMOVE?
-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: sneakyfs

# Tool invocations
sneakyfs: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o $(EXEC_NAME) $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) sneakyfs
	-@echo ' '

# Install
install:
	@cp $(EXEC_NAME) $(INSTALL_DIR)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
