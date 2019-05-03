set -e
echo -e '\nSTART STEP 1 PART 1\n'
cd ${workingdir}/Tuning_rel21/run
. setup.sh || ((1)) 
bash ${workingdir}/BJetTriggerUtils/autorun/run_analysis_array.sh 1
for sample in ${samples_step1}; do 
    #srun --mem=2G --time=10 -p $partition python mergeFiles.py -dir slurm_arrays/slurm_${date}_${sample}_step1 -what RefHistos
    #only use the below line to study step 1 output
    srun --mem=2G --time=10 -p $partition python mergeFiles.py -dir slurm_arrays/slurm_${date}_${sample}_step1 -what flavntuple 
done
