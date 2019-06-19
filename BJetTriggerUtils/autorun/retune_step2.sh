set -e
lockvariables
echo -e '\nSTART STEP 2\n'
cd ${workingdir}/Tuning_rel21/run
. setup.sh || ((1)) 
bash ${workingdir}/BJetTriggerUtils/autorun/run_analysis_array.sh 2
mkdir ${workingdir}/trainingMV2/inputs/$calibtag_step3
if [[ -n $hybridtuning ]]; then
    python mixOnlineTrees.py slurm_arrays/slurm_${date}_${ttbar}_${size2}_step2 slurm_arrays/slurm_${date}_${zprime}_${size2}_step2 ${workingdir}/trainingMV2/inputs/${calibtag_step3} hybrid_flavntuple.root
    srun --mem=2G --time=30 -p $partition bash ${workingdir}/trainingMV2/inputs/${calibtag_step3}/merge.sh
else
    srun --mem=2G --time=30 -p $partition python mergeFiles.py -dir slurm_arrays/slurm_${date}_${eventtype}_${size2}_step2 -what flavntuple
    cp slurm_arrays/slurm_${date}_${eventtype}_${size2}_step2/merged_flavntuple.root ${workingdir}/trainingMV2/inputs/${calibtag_step3}/${eventtype}_${size2}_flavntuple.root
fi
