set -e
echo -e '\nSTART STEP 3 PART 1\n'
cd ${workingdir}/trainingMV2/
. setup.sh  || ((1)) 
newvarlist=${trainingprefix}_${calibtag_step3}_${trainingsuffix}
cp weights/${trainingtemplate} weights/${newvarlist}.varlist
jobid=$(python submit_slurm_training.py ${calibtag_step3} ${newvarlist} | sed -n "$jobidregex" )

echo 'Waiting for training to finish...'
while true; do
    jobStillRunning=$(squeue -u $(whoami) | grep $jobid | wc -l)
    if (( ! jobStillRunning )); then break; fi
    sleep 5m
done
echo -e '\nTraining Complete!\n'
