# use Steve's method to submit job arrays
# see: ~sekula/scratch/ATLAS/bjet_trigger/bJetTrigger_CPUOptimisation/run/cpustudy.p

#!/usr/bin/env python
#SBATCH -J tuning    # job name 
#SBATCH --exclusive 
#SBATCH -p serial  # queue (partition) -- batch, parallel, etc.  parallel-medium
#SBATCH --mail-user=flosterzo@smu.edu 
#SBATCH --mail-type=fail    # email me when the job finishes 

import os

dir = 'slurm_20170608_step1'
filelist = 'sample_ttbar.txt'
template = 'testBTriggerTuning_step1_template.py'

## open the file and read the inputs
inputfile = open(filelist, 'r')
fileList = inputfile.readlines()
inputfile.close()

## make the dir and move in there
os.system('mkdir %s' % dir)
#os.system('cd %s' % dir)

commandtemplate = 'sed -e "s|MYFLAVFILE|%s|g" -e "s|MYREFFILE|%s|g" -e "s|MYINPUTFILE|%s|g" -e "s|MYSTART|%d|g" %s > %s/testBTrigger_%d.py'
## loop on files
idx = 0
flavname = ''
refname = ''
start = 0
for filename in fileList:
    filename = filename.strip()
    #print filename
    for subidx in range(0,4):
	flavname = 'flavntuple_%d.root' % idx
	refname = 'RefHistos_%d.root' % idx
	actualcommand = commandtemplate % (flavname, refname, filename, start, template, dir, idx)
	os.system(actualcommand)
	idx += 1
	start += 2500
