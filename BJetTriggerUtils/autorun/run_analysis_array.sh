set -e

stepnum=$1
case $stepnum in
    1) samples=${samples_step1}; calibtag='WHATEVER';;
    2) samples=${samples_step2}; calibtag=${calibtag_step1};;
    4) samples=${samples_step4}; calibtag=${calibtag_step3};;
    *) echo "HOW ARE YOU RUNNING ME ON STEP $stepnum?!?!"; exit 1;;
esac
echo 'RUN ANALSYSIS'
echo $samples
echo $calibtag

wait_for_jobs_to_finish() {
    set -e
    echo 'Waiting for slurm arrays to finish...'
    echo -n 'Jobs remaining: '

    jobids=''
    for sample in $samples; do
        jobids="$jobids $(cat ${date}_${sample}_step${stepnum}_jobid.tmp)"
    done
    while true; do
        runningjobs=$(squeue -u $(whoami))
        jobsleft=0
        for id in $jobids; do
            numMatchedJobs=$(echo "$runningjobs" | grep $id | wc -l)
            jobsleft=$((jobsleft + numMatchedJobs))
        done
        echo -n "$jobsleft "
        if (( jobsleft == 0 )); then break; fi
        sleep 1m
    done
    echo -e '\nJobs Complete!\n'
}

echo 'Preparing slurm arrays...'
for sample in $samples; do
    title="${date}_${sample}_step${stepnum}"
    ./prepare_slurm_array.sh $stepnum $sample $calibtag $partition
    batch_output=$(bash slurm_arrays/slurm_${title}/run.sh)
    echo $batch_output | sed -n "$jobidregex" > ${date}_${sample}_step${stepnum}_jobid.tmp
done
wait_for_jobs_to_finish
echo 'Identifying failed jobs:'
while true; do 
    failedArrays=0
    for sample in $samples; do
        title="${date}_${sample}_step${stepnum}"
        if [[ -a ${title}_jobid.tmp ]]; then
            ./findFailedJobs.sh slurm_arrays/slurm_${title} $(cat ${title}_jobid.tmp) ${title}_rerun.sh || exit 1
            if [[ -a ${title}_rerun.sh ]]; then
                failedArrays=$((failedArrays+1))
                bash ${title}_rerun.sh | sed -n "$jobidregex" > ${title}_jobid.tmp
            else
                rm ${title}_jobid.tmp 2> /dev/null
            fi
        fi
    done
    echo "failedArrays: $failedArrays"
    if ((failedArrays == 0)); then break; fi
    wait_for_jobs_to_finish
done
