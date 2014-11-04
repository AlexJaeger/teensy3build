Teensy3build
============

Introduction
------------
This project aims to provide an easy to use Makefile build system for the Teensy 3/3.1 microcontroller platforms. I thought this would be a nice project because a Makefile build strategy allows easy compliation of multiple file projects (something the Arduino IDE doesn't accomplish very well).

The Teensy3build system essentially combines the Teensyduino plugin for Windows, Mac and Linux. The platform specific compiler binaries are located in the tools_win, tools_mac and tools_linux directories. When Make is invoked the OS is detected and the appropriate binaries are chosen to compile a project for the Teensy.


Prerequesites
-------------
1. Install Python 2.7
	- Ensure Python is in your system PATH (Google to find out how to do this).
2. (Windows user ONLY) Add GNU Make to your system PATH, located "C:\<yourdownloadsfolder>\teensy3build\tools_win\arm-none-eabi\bin"
3. A working Teensy 3 or 3.1 microcontroller.

Run the Makefile for your Teensy, and the example project should compile!

(More Instruction to come)
