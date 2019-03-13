import os,sys,json

# read arguments
if len(sys.argv) < 5:
  print('ERROR: I need arguments!!!!')
  print('usage: python prepare_grid_job.py -input <name of the json file (inluding path)> -sample <ttbar/Zprime>')
  sys.exit()

###
filesperjob = 1
postfix = 'v00'
excludedSites = []

injson = ''
sssample = ''
for arg in sys.argv:
  idx = sys.argv.index(arg)
  if arg == '-input':
    injson = sys.argv[idx+1]
  if arg == '-sample':
    sssample = sys.argv[idx+1]

print('json = %s' % injson)
print('sample = %s' % sssample)

jsonstr = open(injson).read().strip()
data = json.loads(jsonstr)

# calibtration tag
calibtag = str(data['calibtag'])
jettype = str(data['jettype'])

retag = 'False'
if str(data['step']) == 'step2' or str(data['step']) == 'step4':
  retag = 'True'

if postfix:
  postfix = '_' + postfix

# directory name
dirname = 'grid_{0}_{1}_{2}{3}'.format(str(data['date']),sssample,str(data['step']), postfix)

# source directory for calibration tag
# !!! RefFile has to be the second element in the list!
inputdir = '/afs/cern.ch/work/l/losterzo/BJetTrigger/calibFilePreparator'
calibtagdir = '{0}/{1}'.format(inputdir,str(data['calibtag']))
files_to_copy = ['mycool.db','coolhist_tempcat.xml','PoolFileCatalog.xml','RefFile_{0}.root'.format(str(data['calibtag']))]
if str(data['calibtag']) == 'WHATEVER': files_to_copy = []

# input parameters
inDS = None
if sssample == 'ttbar':
  inDS = 'mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906'
elif sssample == 'Zprime':
  inDS = 'mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906'

outDS = 'user.losterzo.{0}_{1}_{2}{3}'.format(str(data['date']), sssample, str(data['step']), postfix)

extfiles = ','.join(files_to_copy)

if __name__ == '__main__':
  
  # set things up
  if os.path.isdir(dirname):
    print('WARNING: are you sure? {0} already exists!'.format(dirname))
    sys.exit(1)
  os.makedirs(dirname)
  for entry in files_to_copy:
    os.system('cp {0}/{1} {2}/.'.format(calibtagdir, entry, dirname))
  
  # retrieve useful info
  jo_template = 'testBTriggerTuning_grid.py'

  # build the actual jO out of the template
  jo_custom = None
  with open(jo_template, 'r') as f_template:
    jo_custom = f_template.read()
  f_template.close()

  jo_custom = jo_custom.replace('MYCALIB', calibtag)
  jo_custom = jo_custom.replace('MYRETAG', retag)
  jo_custom = jo_custom.replace('MYFLAVFILE', 'flavntuple')
  jo_custom = jo_custom.replace('MYREFFILE', 'RefHistos')
  jo_custom = jo_custom.replace('JETTYPE', jettype)
  # first event
  firstevent = 0
  jo_custom = jo_custom.replace('MYSTART', str(firstevent))
  # input file
  #jo_custom = jo_custom.replace('MYINPUTFILE', line)

  with open('{}/testBTriggerTuning.py'.format(dirname), 'w') as jo_actual:
    jo_actual.write(jo_custom)
  jo_actual.close()
  
  command = 'pathena testBTriggerTuning.py --inDS={0} --outDS={1} --nFilesPerJob={2} --nGBPerJob=2'.format(inDS, outDS, filesperjob)

  reffile = ''
  if retag == 'True':
    reffile = files_to_copy[-1]
    command = command + ' --addPoolFC={}'.format(reffile)
    command = command + ' --extFile={}'.format(extfiles)
  
  if len(excludedSites) > 0:
    command = command + ' --excludedSite=' + ','.join(excludedSites)
  f_command = open('{}/command'.format(dirname), 'w')
  f_command.write(command)
  f_command.close()
