#!/bin/bash
name=slurm_20170626Ruchi_step4
template=testBTriggerTuning_step4_template.py
mkdir $name
## pay attention to these lines!!!
cp mycool.db $name/.
cp RefFile_20170626Ruchi_step3.root $name/.
## ---

i=0
while read FILE
do
cd $name
Evt=0
FLAV="flavntuple_$i.root"
REF="RefHistos_$i.root"
#sed -e "s|MYFLAVFILE|$FLAV|g" -e "s|MYREFFILE|$REF|g" -e "s|MYINPUTFILE|$FILE|g" -e "s|MYSTART|$Evt|g" ../${template} > testBTrigger_$i.py 
sed -e "s|MYID|$i|g" -e "s|MYFLAVFILE|$FLAV|g" -e "s|MYREFFILE|$REF|g" -e "s|MYINPUTFILE|$FILE|g" -e "s|MYSTART|$Evt|g" ../${template} > testBTrigger_$i.py 
sbatch -p serial --mem=19000 athena.py testBTrigger_$i.py
i=$[$i +1]
Evt=$[$Evt +2500]
FLAV="flavntuple_$i.root"
REF="RefHistos_$i.root"
sed -e "s|MYID|$i|g" -e "s|MYFLAVFILE|$FLAV|g" -e "s|MYREFFILE|$REF|g" -e "s|MYINPUTFILE|$FILE|g" -e "s|MYSTART|$Evt|g" ../${template} > testBTrigger_$i.py 
#sed -e "s|MYFLAVFILE|$FLAV|g" -e "s|MYREFFILE|$REF|g" -e "s|MYINPUTFILE|$FILE|g" -e "s|MYSTART|$Evt|g" ../${template} > testBTrigger_$i.py 
sbatch -p serial --mem=19000 athena.py testBTrigger_$i.py
i=$[$i +1]
Evt=$[$Evt +2500]
FLAV="flavntuple_$i.root"
REF="RefHistos_$i.root"
#sed -e "s|MYFLAVFILE|$FLAV|g" -e "s|MYREFFILE|$REF|g" -e "s|MYINPUTFILE|$FILE|g" -e "s|MYSTART|$Evt|g" ../${template} > testBTrigger_$i.py 
sed -e "s|MYID|$i|g" -e "s|MYFLAVFILE|$FLAV|g" -e "s|MYREFFILE|$REF|g" -e "s|MYINPUTFILE|$FILE|g" -e "s|MYSTART|$Evt|g" ../${template} > testBTrigger_$i.py 
sbatch -p serial --mem=19000 athena.py testBTrigger_$i.py
i=$[$i +1]
Evt=$[$Evt +2500]
FLAV="flavntuple_$i.root"
REF="RefHistos_$i.root"
#sed -e "s|MYFLAVFILE|$FLAV|g" -e "s|MYREFFILE|$REF|g" -e "s|MYINPUTFILE|$FILE|g" -e "s|MYSTART|$Evt|g" ../${template} > testBTrigger_$i.py 
sed -e "s|MYID|$i|g" -e "s|MYFLAVFILE|$FLAV|g" -e "s|MYREFFILE|$REF|g" -e "s|MYINPUTFILE|$FILE|g" -e "s|MYSTART|$Evt|g" ../${template} > testBTrigger_$i.py 
sbatch -p serial --mem=19000 athena.py testBTrigger_$i.py
i=$[$i +1]
cd ..
done < sample_ttbar.txt
