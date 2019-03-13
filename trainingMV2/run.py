#!/bin/usr/python 

from ROOT import *
gROOT.SetBatch(1)
from array import array
import sys
import os
import os.path
import time
from datetime import datetime

rootsys= str(os.environ['ROOTSYS'])

if gROOT.GetVersion()>=6.04:
    if not os.path.exists("./TMVAMultiClassGui.h"):  os.system("ln -s "+rootsys+"/include/TMVA/TMVAMultiClassGui.h")
    if not os.path.exists("./TMVAMulticlass.C"):     os.system("ln -s "+rootsys+"/tutorials/tmva/TMVAMulticlass.C")
    if not os.path.exists("./tmvaglob.h"):           os.system("ln -s "+rootsys+"/include/TMVA/tmvaglob.h")
    if not os.path.exists("./TMVAGui.h"):            os.system("ln -s "+rootsys+"/include/TMVA/TMVAGui.h")
    if not os.path.exists("./TMVAClassification.C"): os.system("ln -s "+rootsys+"/tutorials/tmva/TMVAClassification.C")
else:
    if not os.path.exists("./TMVAMultiClassGui.C"): os.system("ln -s "+rootsys+"/tmva/test/TMVAMultiClassGui.C")
    if not os.path.exists("./tmvaglob.C"): os.system("ln -s "+rootsys+"/tmva/test/tmvaglob.C")
    if not os.path.exists("./TMVAGui.C"): os.system("ln -s "+rootsys+"/tmva/test/TMVAGui.C")
    pass

if not os.path.exists("./weights"): os.mkdir("./weights")
if not os.path.exists("./plots"):   os.mkdir("./plots")

exampleFileName="MV2_example_jvt02_puCut3_tm0_stat10k_cStat5k_BdtGrad_bin_cuts200_depth10_nTrees400_MNS05_c10.varlist"
if not os.path.exists("./weights/"+exampleFileName): os.system("ln -s $PWD/MV2_example.varlist ./weights/"+exampleFileName)

print "Compiling macros..."
cmpFailure=0;
# cmpFailure+=gROOT.ProcessLine(".L ntupInfo/bTag.C+")
# cmpFailure+=gROOT.ProcessLine(".L ntupInfo/bTagG.C+")
# cmpFailure+=gROOT.ProcessLine(".L ntupInfo/minibtag.C+")
cmpFailure+=gROOT.ProcessLine(".L tools/RejectionTool.C+")
cmpFailure+=gROOT.ProcessLine(".L btagRejGraphs.C+")
cmpFailure+=gROOT.ProcessLine(".L MulticlassTrainer.C+")
if cmpFailure:
    print "Compilation failure, aborting..."
    sys.exit(1)
    pass

inputStr      =""
inputDirectory=""
jetCollection =""
performOnlyTraining=0

try:
    inputStr = str(sys.argv[1])
except IndexError:
    print "No argument given."
    print "\tUsage==> python run.py trainingName inputDir jetCollection"
    print "\t- trainingName example : MV2_example_jvt02_tm0_stat10k_cStat5k_BdtGrad_bin_cWeight_cuts200_depth10_nTrees400_MNS05_c10"
    print "\t                       : There should be a file named:", exampleFileName
    print "\t                       : under ./ or weights/, containing the list of variables declared in minibtag.h, together with the variable type: I/F/D"
    print "\t- inputDir example     : /your/directory/containing/rootfiles*.root*"
    print "\t- jetCollection example: either of AntiKt4EMTopoJets or AntiKt4LCTopoJets"
    print "\t- Further details      : please check README."
    sys.exit(1)
    pass

try:
    inputDirectory=sys.argv[2]
except IndexError:
    print "No argument given for input directory"
    sys.exit(1)
    pass

try:
    jetCollection= sys.argv[3]
except IndexError:
    jetCollection="AntiKt4EMTopoJets"    
    print "No argument given for jetCollection, assigning jetCollection=", jetCollection
    #print "No argument exists. Try again."
    #print "python addBranch.py inputFile targetLabel"
    #sys.exit()
    pass

MulticlassTrainer(inputStr, inputDirectory, jetCollection)

if performOnlyTraining:
    sys.exit(0)
    pass

if inputStr.find(".varlist")>=0:
    inputStr=inputStr[0:inputStr.find(".varlist")]
    pass
if inputStr.find("/")>=0:
    inputStr=inputStr[inputStr.rfind("/")+1:len(inputStr)]
    pass
#print inputStr
#sys.exit(1)

btagRejGraphs("weights/"+inputStr+".root",0,1,inputStr)
