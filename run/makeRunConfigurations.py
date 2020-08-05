#!/usr/bin/python
import os,re,shutil,conf,util
from util import * 


# Define functions


def runLoopOver(runinfo):
	# Define temporary file name
	tempfilename = "tmp.i"

	# Define output directory        
	dirname = runinfo.getDirName()
	
	for startevt in range(len(runinfo.startevts)-1):
		subdirname = "ev_" + str(runinfo.startevts[startevt]) + "-" + str(runinfo.startevts[startevt+1])
		makeDirectory(dirname+"/"+subdirname)

		#
		# step 1 ) Modify the template to be set output
		readfile = open(conf.inconf,'r') # open as read only
		writefile = open(tempfilename,'w') # open output file 
		# Read input configuration
		for line in readfile:
			if line[0] == '!':
			# Just copy if it is comment line
				writefile.write(line)
			else :
				if re.search("FILE=",line):
					writefile.write(re.sub("FILE=","FILE=\'"+dirname+"/"+subdirname+"/\'+",line))
				else :
				# Just copy unless we find the parameter name specified above 
					writefile.write(line)
		writefile.close()
		readfile.close()

		filename = dirname+'/'+subdirname+'/run' + runinfo.getRunID() + '.i'

		# copy the temporary file to "filename"
		shutil.copy(tempfilename,filename)

		#
		# step 2 ) Now we move to replace parameter values.
		#
		# loop over values
		for param in runinfo.params:	

			os.remove(tempfilename) # clear tempfilename
			writefile = open(tempfilename,'w') # open new file 
			readfile = open(filename,'r') # open as read only

			value = runinfo.values[runinfo.params.index(param)]
		
			# Read input configuration
			for line in readfile:
		
				if line[0] == '!':
				# Just copy if it is comment line
					writefile.write(line)
				else :
			
					if re.search(param+'=',line):
					# Replace values if we find the parameter name specified above. 
						parameterequal = param+'='
						frag = line.split(parameterequal)[1]
						# delimiter must be ',' or ';'
						if frag.find(',') > 0:
							frag = frag.split(',')[0]
						elif frag.find(';') > 0:
							frag = frag.split(';')[0]

						# special treatment for meta characters
						if frag.count('*') > 0:
							frag = re.sub("\*","\\*",frag)
						if frag.count('$') > 0:
							frag = re.sub("\$","\\$",frag)
						if frag.count('^') > 0:
							frag = re.sub("\^","\\^",frag)
						if frag.count('.') > 0:
							frag = re.sub("\.","\\.",frag)
						if frag.count('+') > 0:
							frag = re.sub("\+","\\+",frag)

						writefile.write(re.sub(frag,value,line))
					else :
					# Just copy unless we find the parameter name specified above 
						writefile.write(line)
						
			readfile.close()
			writefile.close()
			
			shutil.copy(tempfilename,filename)

		# Clean up. Delete a temporary file
		os.remove(tempfilename)

		print filename + " is created."
		# Function end.



#
# Main function starts from here. 
#

# Call functions

makeDirectory(conf.output_topdir)

# getRunInfoList function will collect information
# from conf.py, store the data in an object (RunParameterSet),
# which is defined in conf.py, and eventually return the list of the objects.
runinfolist = getRunInfoList() 


# loop over the list of RunParameterSet.
for runinfo in runinfolist:
	# Automatic directory name generation from parameters. 
	dirname = runinfo.getDirName()
	# make run directories
	makeDirectory(dirname)
	runLoopOver(runinfo)

