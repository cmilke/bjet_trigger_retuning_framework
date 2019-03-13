suffix=$1
file="RefFile_${suffix}.root"
coolHist_setFileIdentifier.sh $file
coolHist_insertFileToCatalog.py  $file
coolHist_setReference.py OFLP200 /GLOBAL/TrigBTagCalib/RUN12 1 $suffix $file
echo -e 'setchan /GLOBAL/TrigBTagCalib/RUN12 1 RUN12\nexit\n' | AtlCoolConsole.py "sqlite://;schema=mycool.db;dbname=OFLP200"
echo
