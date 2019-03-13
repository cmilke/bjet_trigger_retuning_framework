#!/bin/bash

printinterval='200'

dir=$1
job=$2
rerunout=$3

echo "Checking $dir $job..."

failedjobs=''
totaljobs=0
numfailed=0
for log in $(ls -v "${dir}/log_tuning-${job}_"*); do
    lognumber=$(echo $log | sed 's/.*_\([0-9]\+\)\.out/\1/')
    exitregex='s/Py:Athena\s\+INFO leaving with code \([0-9]\+\):.*/\1/p'
    exitcode=$(tail -n10 $log | sed -n "$exitregex")
    if [[ $exitcode != '0' ]]; then
        if [[ -z $failedjobs ]]; then
            failedjobs="$lognumber"
        else
            failedjobs="$failedjobs,$lognumber"
        fi
        ((numfailed++))
    fi
    if (( ++totaljobs % printinterval == 0 )); then
        if ((totaljobs == printinterval)); then
            echo -n "checked $totaljobs"
        else
            echo -n " $totaljobs" 
        fi
    fi
done
if ((totaljobs >= printinterval)); then echo; fi
echo

if ((numfailed)); then
    echo "Found ${numfailed} errors in ${dir}, job ${job}"
    reruncommand="sbatch -a $failedjobs ${dir}/launch.py"
    echo $reruncommand > ${rerunout}
    echo "Rerun with 'bash ${rerunout}_rerun.sh'"
else
    echo "All jobs from ${dir}, job ${job} successful"
    rm ${rerunout} &> /dev/null
fi
echo
