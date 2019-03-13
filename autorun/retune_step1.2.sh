#START STEP 1 PART 2
cd ${workingdir}/calibFilePreparator/
. setup.sh
mkdir ${tag}_step1
for sample in $samples; do
    cp ${workingdir}/Tuning_rel21/run/slurm_arrays/slurm_${date}_${sample}_step1/merged_RefHistos.root ${tag}_step1/${sample}_RefHistos.root
    echo "${tag}_step1/${sample}_RefHistos.root" >> ${tag}_step1/filesToHadd.txt
done
cd ${tag}_step1/
python ../createRefFile.py 
source ../coolScript.sh "${tag}_step1"
