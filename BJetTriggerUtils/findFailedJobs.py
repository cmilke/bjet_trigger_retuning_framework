import os,subprocess,glob,sys
from  __builtin__ import any as b_any

# read arguments
if len(sys.argv) < 5:
  print 'ERROR: I need arguments!!!!' 
  print 'usage: python findFailedJobs.py -dir <directory name> -job <jobId>'
  sys.exit()


thedir = ''
jobid = ''
for arg in sys.argv:
  idx = sys.argv.index(arg)
  if arg == '-dir':
    thedir = sys.argv[idx+1]
  if arg == '-job':
    jobid = sys.argv[idx+1]

## find the slurm*out files which do not contain the 'successful run' string

#thedir = 'slurm_20171031_Zprime_step2'
#jobid = '616984'
themagicpattern = 'successful run'
memoryerror = 'slurmstepd: error: Exceeded step memory limit at some point.'
chappyerror = 'problem running chappy!'
typeerror = 'TypeError'

## default
theList = glob.glob(thedir + '/log_tuning-' + jobid + '_*.out')

## special -- comment it out and use 'default'
#theList = []
#for entry in jobid_list:
#  thislist = glob.glob(thedir + '/log_tuning-' + jobid + '_*.out')
#  for line in thislist:
#    theList.append(line)

nDone = 0
nFail = 0
nWrong = 0
nMem = 0
nChappy = 0
nType = 0
failedList = []
completedList = []
for line in sorted(theList):
  line = line.strip()
  taskid = line.split('_')[-1].split('.')[0]
  logfilename = line
  #if themagicpattern not in open(logfilename, 'r').read():
  if not b_any(themagicpattern in x for x in open(logfilename, 'r').readlines()[-30:]):
    ## look for the subjob id printed on purpose in the jO:
    ## FLS: subjob number <MYID>
    fullline, err = subprocess.Popen('grep FLS %s' % logfilename, stdout=subprocess.PIPE, shell=True).communicate()
    fullline = fullline.strip()
    if fullline == '':
      print 'have to skip job %s because of some strange error' % taskid
      nWrong += 1
      failedList.append(taskid)
      continue
    print 'failed task id %s' % (taskid)
    failedList.append(taskid)
    nFail += 1
  # some jobs might look ok, but will have this line at the end resulting in an
  # unusable root file
  # slurmstepd: error: Exceeded step memory limit at some point.
  #elif memoryerror in open(logfilename, 'r').read():
  memerrorstr, err = subprocess.Popen('grep "%s" %s' % (memoryerror, logfilename), stdout=subprocess.PIPE, shell=True).communicate()
  chappyerrorstr, err = subprocess.Popen('grep "%s" %s' % (chappyerror, logfilename), stdout=subprocess.PIPE, shell=True).communicate()
  typeerrorstr, err = subprocess.Popen('grep "%s" %s' % (typeerror, logfilename), stdout=subprocess.PIPE, shell=True).communicate()
  if memerrorstr:
    print 'too bad, task %s was good but had memory errors' % taskid
    #failedList.append(taskid)
    nMem += 1
  elif chappyerrorstr:
    print 'a \'chappy error\' was found in task %s' % taskid
    #failedList.append(taskid)
    nChappy += 1
  elif typeerrorstr:
    print 'a TypeError was found in task %s' % taskid
    #failedList.append(taskid)
    nType += 1
  else:
    completedList.append(taskid)
    nDone += 1
    #print 'job %s is OK!!' % logfilename.split('/')[1].strip('slurm-').strip('.out')
print 'out of %d jobs: done %d -- failed %d -- wrong %d -- memory problem %d -- chappy error %d -- type error %d' % (len(theList), nDone, nFail, nWrong, nMem, nChappy, nType)
if len(completedList) > 0:
  print 'if you want to take a look, here is an example of a succeded task : %s' % completedList[0]

if len(failedList) > 0:
  print 'resubmit command : sbatch -a %s ./launch_%s.py' % (','.join(failedList), thedir)
# split in smaller resubmissions: 20 tasks per array
if len(failedList) > 20:
  print 'split command:'
  chunksize = 20
  total = len(failedList)
  firstidx = 0
  lastidx = 0
  for i in range(0, total/chunksize):
    firstidx = chunksize*i
    lastidx = (i+1)*chunksize
    #print '%d -> %d' % (firstidx, lastidx)
    chunk = failedList[firstidx : lastidx]
    print 'sbatch -a %s ./launch_%s.py' % (','.join(chunk), thedir)
  lastchunk = failedList[lastidx : ]
  print 'sbatch -a %s ./launch_%s.py' % (','.join(lastchunk), thedir)
