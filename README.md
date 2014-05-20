Teensy3build
============

Introduction
------------
This project aims to provide an easy to use Makefile build system for the Teensy 3/3.1 microcontroller platforms. I thought this would be a nice to do because the Makefile build strategy allows multiple file projects easy to manage (something the Arduino IDE doesn't accomplish all too well).

The teensy3build system is essentially combines the Teensyduino plugin from Windows, Mac and Linux. The platform specific compiler binaries are located in the tools_win, tools_mac and tools_linux directories. When Make is invoked the system operating system is detected and the appropriate binaries are chosen to compile a project for the Teensy.


Prerequesites
-------------
1. Install Python 2.7
	- Ensure Python is in your system PATH (Google to find out how to do this)
2. A working Teensy 3 or 3.1 microcontroller.

(More Instruction to come)
