import os,sys

if len(sys.argv) < 5:
  print 'ERROR: I need arguments!!!!'
  print 'usage: python mergeFiles.py -dir <directory name> -what <RefHistos/flavntuple>'
  sys.exit()

inputdir = ''
what = ''
for arg in sys.argv:
  idx = sys.argv.index(arg)
  if arg == '-dir':
    inputdir = sys.argv[idx+1]
  if arg == '-what':
    what = sys.argv[idx+1]

# build output suffix
#out_suffix = '_'.join(inputdir.split('_')[1:])

# count dirs named 't_*'
dirlist = [name for name in os.listdir(inputdir) if os.path.isdir(inputdir + '/' + name)]
numfiles = len(dirlist)

# slice list
nfilesperchunk = 50

nchunks = (numfiles // 50) + 1

for chunk in range(nchunks):
    start = chunk * nfilesperchunk
    stop = ((chunk + 1) * nfilesperchunk) - 1
    mini_list = dirlist[start:stop]
    if len(mini_list) == 0: continue
    file_list = [ inputdir + '/' + subdir + '/' + what + '_' + subdir.split('_')[1] + '.root' for subdir in mini_list]
    chunk_name = '{0}/{1}_chunk_{2}.root'.format(inputdir,what,chunk)
    this_command = 'hadd {0} {1}'.format(chunk_name,' '.join(file_list))
    os.system(this_command)
    #print(this_command)

#output_name = '{0}_{1}.root'.format(what, out_suffix)
output_name = 'merged_{0}.root'.format(what)
#print 'hadd {0}/{1} {0}/{2}_chunk_*root'.format(inputdir, output_name, what)
#print 'rm {0}/{1}_chunk_*'.format(inputdir,what)
os.system('hadd {0}/{1} {0}/{2}_chunk_*root'.format(inputdir, output_name, what))
os.system('rm {0}/{1}_chunk_*'.format(inputdir,what))
