stepnum=$1

wait_for_jobs_to_finish() {
  echo 'Waiting for slurm arrays to finish...'
  echo -n 'Jobs remaining: '
  while true; do
      runningjobs=$(squeue -u $(whoami))
      jobsleft=0
      for jobid in $(cat ${date}_*_${size}_step${stepnum}_jobid.tmp); do
          numMatchedJobs=$(echo "$runningjobs" | grep $jobid | wc -l)
          ((jobsleft+=numMatchedJobs))
      done
      echo -n "$jobsleft "
      if (( jobsleft == 0 )); then break; fi
      sleep 5m
  done
  echo -e '\nJobs Complete!\n'
}

echo 'Preparing slurm arrays...'
for sample in $samples; do
    echo $sample
    python prepare_slurm_array.py calibJson/${tag}_step${stepnum}.json ${sample} run | sed -n "$jobidregex" > ${date}_${sample}_step${stepnum}_jobid.tmp
done
wait_for_jobs_to_finish
echo 'Identifying failed jobs:'
while true; do 
    failedArrays=0
    for sample in $samples; do
        title="${date}_${sample}_step${stepnum}"
        if [[ -a ${title}_jobid.tmp ]]; then
            ./findFailedJobs.sh slurm_arrays/slurm_${title} $(cat ${title}_jobid.tmp) ${title}_rerun.sh
            if [[ -a ${title}_rerun.sh ]]; then
                ((failedArrays++))
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
