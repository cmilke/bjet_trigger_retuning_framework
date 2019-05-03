set -e
echo -e '\nSTART STEP 4\n'
cd ${workingdir}/Tuning_rel21/run/
. setup.sh || ((1)) 
bash ${workingdir}/BJetTriggerUtils/autorun/run_analysis_array.sh 4
for sample in ${samples_step4}; do 
    srun --mem=2G --time=10 -p $partition python mergeFiles.py -dir slurm_arrays/slurm_${date}_${sample}_step4 -what flavntuple
done
