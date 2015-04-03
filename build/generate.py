#!/usr/bin/python

import os
import glob
from subprocess import call

files = glob.glob('../data/flatbuffers/*.fbs')
out = os.path.realpath('../include/generated')

print 'Starting code generation...'

for file in files:
    print 'Processing "{0}"'.format(file)
    input = os.path.realpath(file)
    call(['flatc', '-o', out, '-c', input])
	
print 'Done.'
