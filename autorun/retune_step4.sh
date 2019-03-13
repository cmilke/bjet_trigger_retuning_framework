#START STEP 4
cd ${workingdir}/Tuning_rel21/run/
. setup.sh
cp calibJson/${tag}_step1.json calibJson/${tag}_step4.json
sed -i "s/step1/step4/" calibJson/${tag}_step4.json
sed -i "s/WHATEVER/${tag}_step3/" calibJson/${tag}_step4.json
bash ${workingdir}/autorun/run_analysis_array.sh 4
for sample in $samples; do 
    srun -p htc python mergeFiles.py -dir slurm_arrays/slurm_${date}_${sample}_step4 -what flavntuple
done
