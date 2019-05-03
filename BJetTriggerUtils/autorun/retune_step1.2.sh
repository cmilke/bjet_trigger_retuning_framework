set -e
echo -e '\nSTART STEP 1 PART 2\n'
cd ${workingdir}/calibFilePreparator/
. setup.sh || ((1)) 
mkdir $calibtag_step1
for sample in ${samples_step1}; do
    cp ${workingdir}/Tuning_rel21/run/slurm_arrays/slurm_${date}_${sample}_step1/merged_RefHistos.root ${calibtag_step1}/${sample}_RefHistos.root
    echo "${calibtag_step1}/${sample}_RefHistos.root" >> ${calibtag_step1}/filesToHadd.txt
done
cd $calibtag_step1
python ../createRefFile.py 
source ../coolScript.sh "$calibtag_step1"
