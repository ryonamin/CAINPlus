#!/usr/bin/python
from util import SetParameterValues
# Setting 

# number of jobs per submit.
nEventPerSubmit = 10  # 10 events takes ~ 2 hours.
nTotalEvents = 100    # N = nTotalEvents/nEventPerSubmit will be # of submit jobs.
startEvent = 0        # Set last event number if exist.

inconf = "templates/beam_250.i"

# Set parameter name and its values (array).
# Use SetParameterValues("NAME",[X1,X2,X3,...]) for each parameter.
# Add SetParameterValues to scandata (array) as many as you want.
scandata = [
    SetParameterValues("SigxFactor", ["1.0"]),
    #SetParameterValues("SigxFactor", ["0.6","0.8", "1.0", "1.2", "1.4"]),
    #SetParameterValues("SigyFactor", ["0.6","0.8", "1.0", "1.2", "1.4"]),
	   ]

output_topdir = "outputs" # No need to change, but you can.
