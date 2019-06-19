set -e
lockvariables
echo -e '\nSTART STEP 3 PART 2\n'
cd ${workingdir}/calibFilePreparator/
. setup.sh || ((1)) 
mkdir ${calibtag_step3}
cd ${calibtag_step3}
weightfile=${workingdir}/trainingMV2/weights/${trainingprefix}_${calibtag_step3}_${trainingsuffix}_BDTG.weights.xml
root -l -q -b ../convertXml2ROOT.C+\(\"${weightfile}\"\) #parenthesis are a special character in bash, so you need to escape them here
cp ../${calibtag_step1}/filesToHadd.txt .
for i in 00 10 20; do echo ${calibtag_step3}/MV2c${i}_AntiKt4EMTopo.root >> filesToHadd.txt; done
echo 'BTagCalibRUN2Onl-08-05_2.root' >> filesToHadd.txt
python ../createRefFile.py 
source ../coolScript.sh ${calibtag_step3}
