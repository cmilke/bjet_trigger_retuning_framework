#START STEP 3 PART 2
cd ${workingdir}/calibFilePreparator/
. setup.sh
mkdir ${tag}_step3
cd ${tag}_step3
root -l -q -b ../convertXml2ROOT.C+\(\"${workingdir}/trainingMV2/weights/${trainingprefix}_${tag}_${trainingsuffix}_BDTG.weights.xml\"\) #parenthesis are a special character in bash, so you need to escape them here
cp ../${tag}_step1/filesToHadd.txt .
for i in 00 10 20; do echo ${tag}_step3/MV2c${i}_AntiKt4EMTopo.root >> filesToHadd.txt; done
echo 'BTagCalibRUN2Onl-08-05_2.root' >> filesToHadd.txt
python ../createRefFile.py 
source ../coolScript.sh "${tag}_step3"
