# This Makefile forms the basis of the teensy3build system.
# It is a modified version of the makefile distributed created by Paul Stoffregan with Teensyduino (www.pjrc.com).
# Modified by Alexander Jaeger, University College Cork, Ireland.

# How it works:
# On invoking Make
# 1. The makefile runs the python script to configure the build folder.
# 2. Make detects your OS, and then proceeds to compile everything in the build folder
#    along with your project, located for example in the '_exampleproject_Teensy3.0' folder.
# 3. Make then links the resultant .o and produces a .hex file as the final output
# 4. This file is then uploaded to the Teensy using Teensyloader.





# The name of your project (used to name the compiled .hex file)
TARGET = main

# configurable options
OPTIONS = -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH

# options needed by many Arduino libraries to configure for Teensy 3.0
OPTIONS += -D__MK20DX256__ -DARDUIO=105
# Spelling mistake here, intentioanl or not? If corrected the standard Makefile provided doesnt compile as it the #if !def(ARDUINO) clause is true instad of false
# This leaves undeclared definitions setup() and loop() in main.cpp and causes compile to fail.

#************************************************************************
# Location of Teensyduino utilities, Toolchain, and Arduino Libraries.
# To use this makefile without Arduino, copy the resources from these
# locations and edit the pathnames.  The rest of Arduino is not needed.
#************************************************************************



# Path location for Teensy Loader, teensy_post_compile and teensy_reboot
# Operating system detection selectes the appropriate  build folder here.

# Object files to be cleaned on 'make clean'
RMOBJECTS := *.o *.d $(TARGET).elf $(TARGET).hex

# Execute the python script to configure the build directory
PYTHONSCRIPT :=  python ../config.py
BLANK := $(shell $(PYTHONSCRIPT))

ifeq ($(OS),Windows_NT)
	RMCMD = del
	MYDIR = echo %cd%
    TOOLSPATH = ../tools_win
    # path location for the arm-none-eabi compiler
    COMPILERPATH = $(TOOLSPATH)/arm-none-eabi/bin
else
	RMCMD = rm
    UNAME_S := $(shell uname -s)
    MYDIR = pwd
    ifeq ($(UNAME_S),Linux)
    	UNAME_P := $(shell uname -p)
    	ifeq ($(UNAME_P),x86_64)
        	TOOLSPATH = ../tools_linux
        	COMPILERPATH = $(TOOLSPATH)/arm-none-eabi/bin
        endif
    endif
    ifeq ($(UNAME_S),Darwin)
        TOOLSPATH = ../tools_mac
        COMPILERPATH = $(TOOLSPATH)/arm-none-eabi/bin
    endif
endif

BUILDPATH = ../build




#************************************************************************
# Settings below this point usually do not need to be edited
#************************************************************************

# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -g -Os -mcpu=cortex-m4 -mthumb -nostdlib -MMD $(OPTIONS) -I. -I$(BUILDPATH)/

# compiler options for C++ only
CXXFLAGS = -std=gnu++0x -felide-constructors -fno-exceptions -fno-rtti

# compiler options for C only
CFLAGS =

# linker options
LDFLAGS = -Os -Wl,--gc-sections -mcpu=cortex-m4 -mthumb -T$(BUILDPATH)/mk20dx256.ld

# additional libraries to link, math
LIBS = -lm


# names for the compiler programs
CC = $(abspath $(COMPILERPATH))/arm-none-eabi-gcc
CXX = $(abspath $(COMPILERPATH))/arm-none-eabi-g++
OBJCOPY = $(abspath $(COMPILERPATH))/arm-none-eabi-objcopy
SIZE = $(abspath $(COMPILERPATH))/arm-none-eabi-size


# All the source file names BUILDPATH are gathered
C_FILES := $(wildcard *.c) \
	      $(wildcard $(addprefix $(BUILDPATH)/, *.c)) \

CPP_FILES := $(wildcard *.cpp) \
		  $(wildcard $(addprefix $(BUILDPATH)/, *.cpp)) \

OBJS := $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o)



# The actual makefile rules (all .o files built by GNU make's default implicit rules)

all: $(TARGET).hex

$(TARGET).elf: $(OBJS) $(BUILDPATH)/mk20dx256.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS) $(L_INC)

%.hex: %.elf
	$(SIZE) $<
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	$(abspath $(TOOLSPATH))/teensy_post_compile -file=$(basename $@) -path=$(shell $(MYDIR)) -tools=$(abspath $(TOOLSPATH))
	-$(abspath $(TOOLSPATH))/teensy_reboot

# compiler generated dependency info
-include $(OBJS:.o=.d)

clean:
	-$(RMCMD) $(RMOBJECTS)