#START STEP 1 PART 1
cd ${workingdir}/Tuning_rel21/run
. setup.sh
cp calibJson/template_step1.json calibJson/${tag}_step1.json
sed -i "s/DATE/${date}/" calibJson/${tag}_step1.json
bash ${workingdir}/autorun/run_analysis_array.sh 1
for sample in $samples; do 
    srun -p htc python mergeFiles.py -dir slurm_arrays/slurm_${date}_${sample}_step1 -what RefHistos
done
