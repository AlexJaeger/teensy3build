# Written by Alexander Jaeger, University College Cork, Ireland


# FUNCTION: This file configures the temporary build folder
# WHEN CALLED: This file is run at the beginning of the Makefile
# WHAT DOES THIS FILE DO: The user selected libraries and all the teensy3 core files to BUILDDIR directory.


import os
import shutil
import sys

abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)


MAINFILE = 'main.cpp'
COREDIR = 'cores/teensy3'
BUILDDIR = 'build'
LIBDIR = 'libraries'

# IMPORTANT
# Add the names of the libraries you wish to use to this list.
LIBADD = [
'Wire',
'AccelStepper',
'Encoder'

]

if os.path.isdir(BUILDDIR):
    shutil.rmtree(BUILDDIR)
shutil.copytree(COREDIR,BUILDDIR)


os.chdir(BUILDDIR)
if os.path.isfile(MAINFILE):
	# Removes the template main.cpp file, originally located in the teensy3 cores directory.
	# Otherwise it will interfere with the main.cpp located in the examples folder.
    os.remove(MAINFILE)
os.chdir('..')

os.chdir(LIBDIR)
libraries = os.listdir('.')
libraries.sort()


for folder in libraries:
    if folder in LIBADD:
        os.chdir(folder)
        librarydir = os.listdir('.')
        for something in librarydir:
            if os.path.isfile(something):
                shutil.copyfile(something, '../../' + BUILDDIR + '/' + something)
            elif (something) == 'utility' and (folder == 'Encoder'):
                shutil.copytree(something, '../../' + BUILDDIR +'/'+ something)
        print "Added: ", folder
        os.chdir('..')