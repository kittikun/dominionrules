#!/usr/bin/python

import glob
from subprocess import call

files = glob.glob('../data/flatbuffers/*.fbs')

print 'Starting code generation...'

for file in files:
	print 'Processing "{0}"'.format(file)
	call(["./flatc", '-o', '../include/generated/', '-c', file])
	
print 'Done.'