#!/usr/bin/env python
#SBATCH -J Tune # job name
#SBATCH -o MYDIR/log_tuning-%A_%a.out
#SBATCH -e MYDIR/log_tuning-%A_%a.out
#SBATCH -p medium-mem-1-s
# can also go with this: -p standard-mem-s --mem=15000

import os
import subprocess
from random import randint

if __name__ == '__main__':
  
  # "build" the array
  SLURM_ARRAY_JOB_ID=os.environ["SLURM_ARRAY_JOB_ID"]
  SLURM_ARRAY_TASK_ID=os.environ["SLURM_ARRAY_TASK_ID"]

  #command = 'cd MYDIR; athena.py testBTrigger_{0}.py'.format(SLURM_ARRAY_TASK_ID)
  command = 'cd MYDIR/t_{0}; athena.py ../testBTrigger_{0}.py'.format(SLURM_ARRAY_TASK_ID)
  os.system(command)
