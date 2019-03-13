#!/usr/bin/env python

import subprocess
import sys
import os

if len(sys.argv) != 3:
    print("Usage: python submit_slurm_training.py <input_tag> <weights_file>")
    sys.exit(1)

input_tag = sys.argv[1]
weights_file = sys.argv[2]

input_dir = 'inputs/'+input_tag
script_name = input_tag+'_run.sh'
partition = 'standard-mem-s --mem=19000'
#weights_file = 'MV2_example_jvt02_puCut3_tm0_stat10k_cStat5k_BdtGrad_bin_cuts200_depth10_nTrees400_MNS05_c10.varlist'
#input_dir = 'inputs/20190212_ttbar_41000_med'
jet_algo = 'TriggerJets'

command_template = 'python run.py %s %s %s'

actual_command = command_template % (weights_file, input_dir, jet_algo)

## create bash script for slurm
bashscript = open(script_name, 'w')
bashscript.write('#!/bin/bash\n')
bashscript.write(actual_command)
bashscript.close()

slurm_command = 'sbatch -p %s %s' % (partition, script_name)

subprocess.call(slurm_command, shell=True)
#os.system(slurm_command)
#print slurm_command
