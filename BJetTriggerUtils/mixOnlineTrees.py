# this macro starts from the (many) files obtained from the tuning jobs and merges them
# mixing the ttbar and Zprime samples. It basically hadds files, but alternating a file from
# ttbar with a file from Zprime (to mimick a reshuffling before the training)
################
# usage: set the parameters below and simply run it, then submit the output script to slurm: sbatch -p standard-mem-s merge.sh
################
## problem: ttbar has roughly 2 times the statistics of the Zprime sample (2000 files for ttbar vs 1200 files for Zprime, each with 2500 events)
## solution 0: use a subsample of the ttbar files of the same size of the Zprime files (i.e. only use the first 1.2k files from ttbar) -- people from the offline group say this is OK
import os
import sys

def getSubdirList(input_path):
    '''
    this function returns the list of subdirs in a given directory
    '''
    return [name for name in os.listdir(input_path) if os.path.isdir(input_path + '/' + name)]

def getListOfIdx(input_path, isFromGrid):
    '''
    this function returns the list of indexes contained in input_path. The additional argument is used
    to handle things depending on the different structure of slurm jobs wrt/ grid jobs. The list of indexes
    is needed (instead of the simple number of files) since some indexes might be missing.
    '''

    idx_list = []
    # when dealing with grid jobs, just count the number of root files
    if isFromGrid:
        # name template: user.losterzo.14391958.TriggerJets._<idx>.root
        for entry in os.listdir(input_path):
            tmp = entry.split('.')[-2]
            tmp = tmp.strip('_')
            idx_list.append(int(tmp))
    else:
        tmp_list = [name for name in os.listdir(input_path) if os.path.isdir(input_path + '/' + name)]
        for entry in tmp_list:
            idx_list.append( int(entry.split('_')[-1]) )

    return idx_list


inputFromGrid = False
#path_ttbar = '/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_20190111_ttbar_step2'
#path_zprime = '/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_20190111_Zprime_step2'
#out_dir = '/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/mix_20190111/'
#out_name = 'hybrid_20190111_mix.root'
if len( sys.argv ) != 5:
    print("Usage: python mixOnlineTrees.py path_ttbar path_zprime out_dir out_name")
    sys.exit(1)
path_ttbar = sys.argv[1]
path_zprime = sys.argv[2]
out_dir = sys.argv[3]
out_name = sys.argv[4]

flavntup_template = 't_{0}/flavntuple_{0}.root'
if inputFromGrid:
    flavntup_template = 'user.losterzo.*.TriggerJets._{0:06d}.root'


outscript = open(out_dir+'/merge.sh', 'w')
outscript.write('#!/bin/bash\n')

# create the output directory
if not os.path.exists(out_dir):
    #os.makedirs(out_dir)
    #print('mkdir {}'.format(out_dir))
    outscript.write('mkdir {}\n'.format(out_dir))

# as from "solution 0", restrict to a subset of the ttbar sample of the same size of the Zprime sample
#subdir_list = getSubdirList(path_zprime)

# get number of files to be used
idx_list = getListOfIdx(path_zprime, inputFromGrid)
idx_list.sort()

# now hadd files two by two
command_template = 'hadd {0}/mix_{1}.root {2} {3}\n'

mixlist = []
#for idx in range(len(subdir_list)):
#    filenum = subdir_list[idx].split('_')[-1]
#    tt_file_idx = '{0}/{1}/flavntuple_{2}.root'.format(path_ttbar, subdir_list[idx], filenum)
#    zp_file_idx = '{0}/{1}/flavntuple_{2}.root'.format(path_zprime, subdir_list[idx], filenum)
#    this_command = command_template.format(out_dir, idx, tt_file_idx, zp_file_idx)
#    mixlist.append('{0}/mix_{1}.root'.format(out_dir, idx))
#    #print(this_command)
#    outscript.write(this_command)

for idx in idx_list:

    flavntup_name = flavntup_template.format(idx)

    tt_file_full = '{0}/{1}'.format(path_ttbar, flavntup_name)
    zp_file_full = '{0}/{1}'.format(path_zprime, flavntup_name)

    mixlist.append('{0}/mix_{1}.root'.format(out_dir, idx))

    this_command = command_template.format(out_dir, idx, tt_file_full, zp_file_full)
    #print(this_command)
    outscript.write(this_command)

# first make chunks: strongly needed for slurm jobs since the output contains O(1k) files, can be used also for grid jobs
nfilesperchunk = 50

nchunks = (len(mixlist) // nfilesperchunk) + 1

for chunk in range(nchunks):
    start = chunk * nfilesperchunk
    #stop = ((chunk + 1) * nfilesperchunk) - 1
    stop = ((chunk + 1) * nfilesperchunk)
    mini_list = mixlist[start:stop]
    if len(mini_list) == 0: continue
    #file_list = [ inputdir + '/' + subdir + '/' + what + '_' + subdir.split('_')[1] + '.root' for subdir in mini_list]
    chunk_name = '{0}/mix_chunk_{1}.root'.format(out_dir,chunk)
    this_command = 'hadd {0} {1}\n'.format(chunk_name,' '.join(mini_list))
    #print this_command
    outscript.write(this_command)

last_command = 'hadd {0}/{1} {0}/mix_chunk_*.root\n'.format(out_dir, out_name)
clean_command = 'rm {}/mix_*root\n'.format(out_dir)
#print last_command
#print clean_command
outscript.write(last_command)
outscript.write(clean_command)
outscript.close()
