#START STEP 2
cd ${workingdir}/Tuning_rel21/run
. setup.sh
cp calibJson/${tag}_step1.json calibJson/${tag}_step2.json 
sed -i "s/step1/step2/" calibJson/${tag}_step2.json
sed -i "s/WHATEVER/${tag}_step1/" calibJson/${tag}_step2.json
bash ${workingdir}/autorun/run_analysis_array.sh 2
mkdir ${workingdir}/trainingMV2/inputs/${tag}
if [[ -n $hybridtuning ]]; then
    python mixOnlineTrees.py slurm_arrays/slurm_${date}_${ttbar}_${size}_step2 slurm_arrays/slurm_${date}_${zprime}_${size}_step2 ${workingdir}/trainingMV2/inputs/${tag} hybrid_flavntuple.root
    srun -p htc bash ${workingdir}/trainingMV2/inputs/${tag}/merge.sh
else
    srun -p htc python mergeFiles.py -dir slurm_arrays/slurm_${date}_${eventtype}_${size}_step2 -what flavntuple
    cp slurm_arrays/slurm_${date}_${eventtype}_${size}_step2/merged_flavntuple.root ${workingdir}/trainingMV2/inputs/${tag}/${eventtype}_${size}_flavntuple.root
fi
