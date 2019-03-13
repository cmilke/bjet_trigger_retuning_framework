# this script has to be run from inside the calibFilePreparator/<calibtag_dir>/ and needs a `filesToHadd.txt` file
# which includes the files (one per line) to be hadded together to create the RefFile
import os

app = ''

# automatically find dir name
dirname = os.getcwd().split('/')[-1]

# create output file name
if not app == '': app = '_' + app
outfilename = 'RefFile_' + dirname + app + '.root'

#inputName = dirname + '/' + 'filesToHadd.txt'
inputName = 'filesToHadd.txt'
inputFile = open(inputName, 'r')
inputList = []
for entry in inputFile.readlines():
	inputList.append('../' + entry.strip())
inputFile.close()

command = 'hadd {0} {1}'.format(outfilename, ' '.join(inputList))
os.system(command)
