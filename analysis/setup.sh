#setupATLAS &&
#lsetup "asetup 21.0.13.1,AtlasProduction,64,gcc49"
#source /users/cmilke/qualification/bJetTrigger/Tuning_rel21/build/x86_64-centos7-gcc49-opt/setup.sh
setupATLAS && lsetup "asetup 21.0.13.1"

broot() { 
    macro=$(echo $@ | sed "s/${1}\s\?/${1}(\"/") #add opening paren
    macro=$(echo $macro | sed 's/ /\",\"/g')\"\) #add comma and quote seperated arguments + closing paren
    macro=$(echo $macro | sed 's/\"\"//') #get rid of inner quotes if there were no arguments
    root -l -b -q "$macro"
}
