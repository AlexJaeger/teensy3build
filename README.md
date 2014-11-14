Teensy3build
============

Introduction
------------
This project aims to provide an easy to use Makefile build system for the Teensy 3/3.1 microcontroller platforms. I thought this would be a nice project because a Makefile build strategy allows easy compliation of multiple file projects (something the Arduino IDE doesn't accomplish very well).

The Teensy3build system essentially combines the Teensyduino plugin for Windows, Mac and Linux. The platform specific compiler binaries are located in the tools_win, tools_mac and tools_linux directories. When Make is invoked the OS is detected and the appropriate binaries are chosen to compile a project for the Teensy.


Prerequisites
-------------
1. Install Python 2.7
	- Ensure Python is in your system PATH (Google to find out how to do this).
2. (Windows user ONLY) After cloning the repository. Add GNU Make to your system PATH, located "C:\<yourdownloadsfolder>\teensy3build\tools_win\arm-none-eabi\bin"
3. A working Teensy 3 or 3.1 microcontroller.

Instructions
------------
1. Clone the repository (if you haven't done so already).
2. Change directory to the repository folder on the command line.
3. Run:	`git submodule init` and `git submodule update`
	This will update the teensy core files to the latest version
4. Copy and rename one of the example project folders, depending on your Teensy version. This is now your project folder
5. Change directory into your new project folder. You should see a 'Makefile' and 'main.cpp'
6. Type: `make`
 The example program should compile and the Teensy LED should blink (Pin 13)
Run the Makefile for your Teensy, and the example project should compile!

Acknowledgements
----------------
This repository contains a mixture of source code and binaries from the Arduino, PJRC's Teensyduino and GNU GCC Projects.
The teensy3build repository merely bundles these together and uses a Makefile (modifled from PJRC) to provide a 'ready-to-go' alternative to the Arduino IDE

(More Instructions to come)
