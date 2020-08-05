#!/usr/bin/python
import os,re,conf

def makeDirectory(dirname):
        if not os.path.exists(dirname):
                os.mkdir(dirname)

def removeMetaCharacter(strin):
	strout = re.sub("\*","",strin)
	strout = re.sub("\,","",strout)
	strout = re.sub("\ ","",strout)
	return strout
	

class SetParameterValues():
	def __init__(self,param,values):
		self.param = param
		self.values = values
	def getParamWithValues(self):
		retvals = []
		for value in self.values:
			retvals.append(self.param+value)
		return retvals 

class RunParameterSet():
	def __init__(self):
		self.params = []
		self.values = []
		self.startevts = []
	def addParameterSet(self,param,value):
		if param not in self.params:
			self.params.append(param)	
			self.values.append(value)

	def addStartEvent(self,evt):
		self.startevts.append(evt)
		
	def getRunID(self):
		runid = ""
		for i in range(len(self.params)):
			runid += "_" + removeMetaCharacter(self.params[i]) + removeMetaCharacter(self.values[i]) 
		return runid
	def getDirName(self):
		dirname = conf.output_topdir + "/Run" + self.getRunID()
		return dirname 

def getRunInfoList():
	runinfolist = []
	for scanparameter in conf.scandata:
		if len(runinfolist) == 0:
			for value in scanparameter.values:
				newinfo = RunParameterSet()
				newinfo.addParameterSet(scanparameter.param,value)
				nsubmit = conf.nTotalEvents/conf.nEventPerSubmit + 1
				for isub in range(nsubmit):
					newinfo.addStartEvent(isub*conf.nEventPerSubmit+conf.startEvent)
				if conf.nTotalEvents > isub*conf.nEventPerSubmit:
					newinfo.addStartEvent(conf.nTotalEvents+conf.startEvent) # last event
				runinfolist.append(newinfo)
		else :
			newruninfolist = []
			for currentinfo in runinfolist:
				for value in scanparameter.values:
					newinfo = RunParameterSet()
					#duplicate existing info
					for i in range(len(currentinfo.params)):
						newinfo.addParameterSet(currentinfo.params[i],currentinfo.values[i])
					#add new info
					newinfo.addParameterSet(scanparameter.param,value)
					newruninfolist.append(newinfo)
			runinfolist = newruninfolist
		
	return runinfolist
