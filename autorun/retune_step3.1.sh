#START STEP 3 PART 1
cd ${workingdir}/trainingMV2/
. setup.sh 
cp weights/${trainingtemplate} weights/${trainingprefix}_${tag}_${trainingsuffix}.varlist
jobid=$(python submit_slurm_training.py ${tag} ${trainingprefix}_${tag}_${trainingsuffix}.varlist | sed -n "$jobidregex" )

echo 'Waiting for training to finish...'
while true; do
    jobStillRunning=$(squeue -u $(whoami) | grep $jobid | wc -l)
    if (( ! jobStillRunning )); then break; fi
    sleep 5m
done
echo -e '\nTraining Complete!\n'
