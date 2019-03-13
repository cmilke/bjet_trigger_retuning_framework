import os

# relevant directories
source_dir = os.environ['PWD']
tuning_dir = '/'.join(source_dir.split('/')[:-1]) + '/Tuning_rel21/run'
calib_dir = '/'.join(source_dir.split('/')[:-1]) + '/calibFilePreparator'

# things to be linked in Tuning_rel21/run
tuning_links = [
    # grid stuff
    'prepare_grid_job.py',
    'testBTriggerTuning_grid.py',
    # slurm stuff
    'prepare_slurm_array.py',
    'slurm_array_template.py',
    'testBTriggerTuning_template.py',
    # check jobs
    'findFailedJobs.py',
    'mergeFiles.py',
    'calibJson'
]

calib_links = [
    'createRefFile.py'
]

for entry in tuning_links:
    os.system('ln -s {0}/{1} {2}/{1}'.format(source_dir, entry, tuning_dir))

for entry in calib_links:
    os.system('ln -s {0}/{1} {2}/{1}'.format(source_dir, entry, calib_dir))
