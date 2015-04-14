#!/usr/bin/python

import os
import glob
import platform
from subprocess import call

files = glob.glob('../data/flatbuffers/*.fbs')

print 'Starting code generation...'

for file in files:
    print 'Processing "{0}"'.format(file)
    
    if 'CYGWIN_NT' in platform.system():
        out = '../include/generated'
        input = file
        #call(['./flatc', '-n', input])
        call(['./flatc', '-o', out, '-c', input])
    else:
        out = os.path.realpath('../include/generated')
        input = os.path.realpath(file)
        call(['flatc', '-o', out, '-c', input])
	
print 'Done.'
