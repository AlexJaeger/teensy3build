

import os
import shutil
import sys

MAINFILE = 'main.cpp'
COREDIR = 'cores/teensy3'
BUILDDIR = 'build'

LIBADD = [
'Wire'

]

if os.path.isdir(BUILDDIR):
    shutil.rmtree(BUILDDIR)
shutil.copytree(COREDIR,BUILDDIR)


os.chdir(BUILDDIR)
if os.path.isfile(MAINFILE):
    os.remove(MAINFILE)
os.chdir('..')

os.chdir('libraries')
libraries = os.listdir('.')
libraries.sort()


for folder in libraries:
    if folder in LIBADD:
        os.chdir(folder)
        librarydir = os.listdir('.')
        for somefile in librarydir:
            if os.path.isfile(somefile):
                shutil.copyfile(somefile, '../../build/' + somefile)
        print "Added: ", folder
        os.chdir('..')
