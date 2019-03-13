import os,sys,json

# read arguments
if len(sys.argv) < 3:
  print 'ERROR: I need arguments!!!!' 
  print 'usage: python prepare_slurm_array.py <name of the json file (inluding path)> <ttbar/Zprime> <run=false>' 
  sys.exit()

injson = sys.argv[1]
sssample = sys.argv[2]
run = len(sys.argv) > 3


print 'json = %s' % injson
print 'sample = %s' % sssample

jsonstr = open(injson).read().strip()
data = json.loads(jsonstr)

# calibtration tag
calibtag = str(data['calibtag'])
jettype = str(data['jettype'])

retag = 'False'
if str(data['step']) == 'step2' or str(data['step']) == 'step4':
  retag = 'True'

# directory name
dirname = 'slurm_arrays/slurm_{0}_{1}_{2}'.format(str(data['date']),sssample,str(data['step']))

# sample
sample = 'samples/sample_{}.txt'.format(sssample)

# source directory for calibration tag
# !!! RefFile has to be the second element in the list!
inputdir = '/users/cmilke/qualification/bJetTrigger/calibFilePreparator'
calibtagdir = '{0}/{1}'.format(inputdir,str(data['calibtag']))
files_to_copy = ['mycool.db','coolhist_tempcat.xml','PoolFileCatalog.xml','RefFile_{0}.root'.format(str(data['calibtag']))]
if str(data['calibtag']) == 'WHATEVER': files_to_copy = []

# other
nevents_per_task = 2500

# build the array launcher
array_script_name = 'launch_' + dirname + '.py'

if __name__ == '__main__':
  
  # set things up
  if os.path.isdir(dirname):
    print('WARNING: are you sure? {0} already exists!'.format(dirname))
    sys.exit(1)
  os.makedirs(dirname)
  for entry in files_to_copy:
    os.system('cp {0}/{1} {2}/.'.format(calibtagdir, entry, dirname))
  
  in_sample_file = open(sample, 'r')

  # retrieve useful info
  jo_template = 'testBTriggerTuning_template.py'
  #jo_template = 'testBTriggerTuning_old_tune.py'

  njobs_tot = 0
  in_sample_list = in_sample_file.readlines()
  for line in in_sample_list:
    # handle the index
    file_idx = in_sample_list.index(line)
    
    line = line.strip('\n')

    subjob_range = range(0,4)
    for sub_idx in subjob_range:

      this_idx = len(subjob_range) * file_idx + sub_idx
      
      # make the subdir
      subdirname = 't_{0}'.format(this_idx)
      # set things up
      if os.path.isdir('{0}/{1}'.format(dirname, subdirname)):
        print('WARNING: are you sure? {0}/{1} already exists!'.format(dirname, subdirname))
      else:
        os.makedirs('{0}/{1}'.format(dirname, subdirname))
      
      # link the db
      if not str(data['calibtag']) == 'WHATEVER':
        pwd = os.environ['PWD']
        os.system('ln -s {0}/{1}/mycool.db {1}/{2}/mycool.db'.format(pwd,dirname,subdirname))
        os.system('ln -s {0}/{1}/coolhist_tempcat.xml {1}/{2}/coolhist_tempcat.xml'.format(pwd,dirname,subdirname))
        os.system('ln -s {0}/{1}/PoolFileCatalog.xml {1}/{2}/PoolFileCatalog.xml'.format(pwd,dirname,subdirname))
        os.system('ln -s {0}/{1}/{3} {1}/{2}/{3}'.format(pwd,dirname,subdirname,files_to_copy[-1]))

      # build the actual jO out of the template
      jo_custom = None
      with open(jo_template, 'r') as f_template:
        jo_custom = f_template.read()
      f_template.close()

      jo_custom = jo_custom.replace('MYCALIB', calibtag)
      jo_custom = jo_custom.replace('MYRETAG', retag)
      jo_custom = jo_custom.replace('MYID', str(this_idx))
      jo_custom = jo_custom.replace('MYFLAVFILE', 'flavntuple_{0}.root'.format(this_idx))
      jo_custom = jo_custom.replace('MYREFFILE', 'RefHistos_{0}.root'.format(this_idx))
      jo_custom = jo_custom.replace('JETTYPE', jettype)
      # first event
      firstevent = sub_idx * nevents_per_task
      jo_custom = jo_custom.replace('MYSTART', str(firstevent))
      # input file
      jo_custom = jo_custom.replace('MYINPUTFILE', line)

      #with open('{0}/{1}/testBTrigger_{2}.py'.format(dirname, subdirname, str(this_idx)), 'w') as jo_actual:
      with open('{0}/testBTrigger_{1}.py'.format(dirname, str(this_idx)), 'w') as jo_actual:
        jo_actual.write(jo_custom)
      jo_actual.close()
      njobs_tot += 1
  print njobs_tot

  array_custom = None
  with open('slurm_array_template.py', 'r') as array_template:
    array_custom = array_template.read()
  array_template.close()

  #array_custom = array_custom.replace('MYDIR', '{0}/{1}'.format(dirname, subdirname))
  array_custom = array_custom.replace('MYDIR', '{0}'.format(dirname))

  with open('{0}/launch.py'.format(dirname), 'w') as array_actual:
    array_actual.write(array_custom)
  array_actual.close()

  run_command = 'sbatch -p htc -a 0-{0} ./{1}/launch.py'.format(njobs_tot-1, dirname)

  if run:
    os.system(run_command)
  else:
    print('Now you can launch with: ' + run_command)
