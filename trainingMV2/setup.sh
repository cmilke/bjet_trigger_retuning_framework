setupATLAS --quiet

#rootVersion=5.34.25-x86_64-slc6-gcc48-opt
rootVersion=6.04.02-x86_64-slc6-gcc48-opt #for compatibility with TMVA-agile
localSetupROOT $rootVersion --quiet
echo "==> Setting up ROOT version: "$rootVersion
