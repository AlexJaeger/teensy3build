
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

# path location for Teensy Loader, teensy_post_compile and teensy_reboot


ifeq ($(OS),Windows_NT)
	RMOBJECTS = *.o *.d $(TARGET).elf $(TARGET).hex teensy3/*.o teensy3/*.d 
	MYDIR = echo %cd%
    TOOLSPATH = tools
    COMPILERPATH = tools_win/arm-none-eabi/bin
else
    UNAME_S := $(shell uname -s)
    MYDIR = pwd
    ifeq ($(UNAME_S),Linux)
    	UNAME_P := $(shell uname -p)
    	ifeq ($(UNAME_P),x86_64)
        	TOOLSPATH = tools_linux
        	COMPILERPATH = tools_linux/arm-none-eabi/bin
        endif
    endif
    ifeq ($(UNAME_S),Darwin)
        TOOLSPATH = tools_mac
        COMPILERPATH = tools_mac/arm-none-eabi/bin
    endif
endif

BUILDPATH = build


#TOOLSPATH = ../../../tools/avr/bin   # on Mac or Windows

# path location for Arduino libraries (currently not used)
LIBRARYPATH = build

# path location for the arm-none-eabi compiler


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

# additional libraries to link
LIBS = -lm


# names for the compiler programs
CC = $(abspath $(COMPILERPATH))/arm-none-eabi-gcc
CXX = $(abspath $(COMPILERPATH))/arm-none-eabi-g++
OBJCOPY = $(abspath $(COMPILERPATH))/arm-none-eabi-objcopy
SIZE = $(abspath $(COMPILERPATH))/arm-none-eabi-size

# automatically create lists of the sources and objects
# TODO: this does not handle Arduino libraries yet...
LC_FILES := $(wildcard $(LIBRARYPATH)/*/*.c)
LCPP_FILES := $(wildcard $(LIBRARYPATH)/*/*.cpp)

C_FILES := $(wildcard *.c) \
	      $(wildcard $(addprefix $(BUILDPATH)/, *.c)) \
		  #$(wildcard $(addprefix $(BUILDPATH)/util, *.c)) \
		  #$(wildcard $(addprefix $(BUILDPATH)/avr, *.c))
CPP_FILES := $(wildcard *.cpp) \
		  $(wildcard $(addprefix $(BUILDPATH)/, *.cpp)) \
		  #$(wildcard $(addprefix $(BUILDPATH)/util, *.cpp)) \
		  #$(wildcard $(addprefix $(BUILDPATH)/avr, *.cpp))
OBJS := $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o)

#L_INC := $(foreach lib,$(filter %/, $(wildcard $(LIBRARYPATH)/*/)), -I$(lib))

# the actual makefile rules (all .o files built by GNU make's default implicit rules)

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
	# ifeq ($(OS),Windows_NT)
		rm *.o 
		rm *.d 
		rm $(TARGET).hex
		rm teensy3/*.o
		rm teensy3/*.d
	# else
	# 	rm *.o 
	# 	rm *.d 
	# 	rm $(TARGET).elf 
	# 	rm $(TARGET).hex
	# 	rm teensy3/*.o
	# 	rm teensy3/*.d
	# endif
	


