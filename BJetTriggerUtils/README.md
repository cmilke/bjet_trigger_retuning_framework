# Table of Contents

- [How to set things up](#how-to-set-things-up)
- [Instructiond for tuning](#instructions-for-tuning)
- [Example of workflow](#example-of-workflow-to-create-a-new-hybrid-tuning-from-scratch)

# Intro
This repo contains a number of useful scripts to work on the b-jet trigger tuning.

# How to set things up
Here the following directory structure is assumed:
```
workingdir> ls -l
calibFilePreparator
plots
trainingMV2
Tuning_rel21
```
Clone this repo in `workingdir`. Then `cd` to `BJetTriggerUtils` and run `python setup.py`. This script links the relevant scripts in the directories where they are needed.

## Other assumptions (or suggestions)
As mentioned later, a clean directory is needed for each calibration tag in order not to mess things up with the `mycool.db` file. So the suggestion is to have a new sub-directory inside `calibFilePreparator` for each calibration tag. The scripts provided in this repo assume this directory structure is used.

# Content
- `prepare_*.py`: scripts to submit jobs either to the grid or to a slurm system (see below), also the corresponding templates are there
- `findFailedJobs.py` and `mergeFiles.py`: scripts to check the outcome of the slurm jobs and to merge the output ntuples
- `createRefFile.py` a script to create the `RefFile` for the calibration
- `mixOnlineTrees.py` a script made to merge the ntuples from Zprime and ttbar in order to create a proper input tree for the hybrid tuning. The different internal structure for grid output and slurm output is handled.
- `calibJson/`: a directory containing json files for the calibrations. They contain some relevant parameters: `date`, `step` (see the instructions below for the details), `calibtag`, `jettype` (SplitJet/GSCJet)
- `NtupConverter.*`: ROOT Class to convert the online TTree into an offline TTree (see below for details)


# Interesting links:

- [intro](https://indico.cern.ch/event/605185/contributions/2439468/attachments/1402291/2140801/intro_26Jan.pdf) from Alessandro with info about hybrid tuning
- [this](https://indico.cern.ch/event/605185/contributions/2455722/attachments/1402252/2140824/Algo_trainings.pdf) about MV2 evolutions
- [JIRA ticket](https://its.cern.ch/jira/browse/ATR-17508) where hybrid tuning for trigger is discussed
- notes about flavor tagging tunings: [2016](http://cdsweb.cern.ch/record/2160731) and [2017](https://cds.cern.ch/record/2273281)

# Instructions for tuning

Mainly taken from the [twiki](https://twiki.cern.ch/twiki/bin/view/Atlas/BTriggerTuning).  
All the "additional" files needed in the following instructions can be found in `/eos/atlas/atlascerngroupdisk/trig-bjet/Year-2018/hybrid_tuning/`

- step 1 (as in the [twiki]((https://twiki.cern.ch/twiki/bin/view/Atlas/BTriggerTuning)): run testBTriggerTuning.py with `"RETAG = False"`

- step 1.1 (still in step 1): create a local calibration tag:

  - [package](https://svnweb.cern.ch/trac/atlas-mociduki/browser/btag/calibFilePreparator/trunk/README)
  - update setup.sh, if needed, to match the release used in step 1
  - this step **has to be done in a clean directory**, i.e. a new directory for each calibration tag is needed!
  - instructions from Ruchi:

    ```
    hadd RefFileWithAllTaggers.root SomeFileWithMissingTaggers.root  RefHistoFromStep1.root
    file="RefFileWithAllTaggers.root"
    suffix="WhateverYouWant"
    coolHist_setFileIdentifier.sh $file
    coolHist_insertFileToCatalog.py  $file
    coolHist_setReference.py OFLP200 /GLOBAL/TrigBTagCalib/RUN12 1 $suffix $file
    AtlCoolConsole.py "sqlite://;schema=mycool.db;dbname=OFLP200"
    (from inside the python shell) setchan /GLOBAL/TrigBTagCalib/RUN12 1 RUN12
    ```

    the above creates a `mycool.db` file which contains the new tuning. I used the following naming convention:

    - suffix: `<date>_<step>`
    - root file: `RefFile_<date>_<step>.root`
    - `<step>` corresponding to the step in this list, `<date>` in the format of YYYYMMDD, `a/b/c/...` for several iterations (or with other additional strings)
    - files `mycool.db`, the `xml` files and `RefFileWithAllTaggers.root` should be copied in the tuning directory
    - the DB uses the `LocalCalibSuffix` to point to a given root file. This is done via the `xml` files which stores the `GUID` referenced by the calib tag and links it to a rootfile

- step 2 (as in the [twiki](https://twiki.cern.ch/twiki/bin/view/Atlas/BTriggerTuning)):
  rerun testBTriggerTuning.py with `"RETAG = True"` and `"LocalCalibSuffix"` set equal to the `$suffix` used above The flavntuple.root obtained now will be used in step 3.  
  If you are producing an hybrid training, flavntuples from ttbar and Zprime should be **mixed and merged** at this stage using the `mixOnlineTrees.py` script.

- step 3:

  - tune MV2 [README](https://svnweb.cern.ch/trac/atlas-mociduki/browser/btag/trainingMV2/trunk/README): (probably better to do this in a clean shell since a different setup is needed to deal with TMVA) check if the proper weight file is there
    ```
    python run.py <weight file> <input dir> <jet algorithm>
    ```
    the `weights/<same weight as before>.weights.xml` file should be used in the next step

  - go back to calibFilePreparator

    ```
     root -l convertXml2ROOT.C+
     xml2Root("<the weight xml file produced in the previous step>", \"MV2c00\")
     xml2Root("<the weight xml file produced in the previous step>", \"MV2c10\")
     xml2Root("<the weight xml file produced in the previous step>", \"MV2c20\")
    ```

    (in the above MV2C00 and MV2C20 are produced only because all the taggers are needed) the above lines produce three root files, one for each tagger.

    ```
     hadd <the three files produced above> <file with the other taggers> <RefHistoFromStep1>
    ```

    the "other" file is `BTagCalibRUN2Onl-08-05_2.root`

  - produce a new calibration tag out of this new file (i.e. redo step 1.1)

- step 4: rerun testBJetTriggerTuning.py using the calibration tag produced in step 3: `"RETAG = True"` and `"LocalCalibSuffix"` equal to the `$suffix` used in step 3

To run with the real ATLAS DB configuration, replace these lines:

```
if RETAG & (LocalCalibSuffix!='WHATEVER') :
    BTaggingFlags.CalibrationFromLocalReplica = True
    BTaggingFlags.TrigCalibrationFolderRoot = '/GLOBAL/TrigBTagCalib/'
    BTaggingFlags.TrigCalibrationTag = LocalCalibSuffix
```

with these ones:

```
if RETAG:
    BTaggingFlags.TrigCalibrationFolderRoot = '/GLOBAL/TrigBTagCalib/'
    BTaggingFlags.TrigCalibrationTag = 'TrigBTagCalibRUN12-08-12'
```
In the example above `TrigBTagCalibRUN12-08-12` is just an example of calibration tag. Here is a list of the "interesting" calibraion tags available so far:
- `TrigBTagCalibRUN12-08-12` : the latest tag with standard training
- `TrigBTagCalibRUN12Onl-08-13` : the first (and so far only) tag with hybrid training

# How to launch jobs
Jobs can be submitted either to the grid or to a slurm system.

## Jobs on the grid
Jobs on the grid are launched with the `prepare_grid_job.py` script:
```
python prepare_grid_job.py -input <path_to/json_file_for_calib_tag> -sample <ttbar/Zprime>
```
This submits a job to the grid (using `testBJetTrigger_grid.py` as a template for the JO), some of the parameters are tunable from inside the script:
- `nfilesperjob` sets the argument of the `--nFilesPerJob` option
- `postfix` sets a suffix to the name of the output dataset
- `outDS` is built from some of the arguments given as input
- `inputdir` is the directory where the calibration tags are stored (basically the full path to `calibFilePreparator`)

## Jobs on slurm
Jobs on slurm are submitted with the `prepare_slurm_array.py` script:
```
python prepare_slurm_array.py -input <path_to/json_file_for_calib_tag> -sample <ttbar/Zprime>
```
This script creates a script `launch_slurm_<suffix>.py` which is the script that shall be used to submit the job. The job is actually a slurm array in which each task processes 2500 events. Instructions on how to launch the job are printed by the `prepare_slurm_array.py` script.

The directory which is creted is named after the calibration tag and the sample (exactly as the `launch_slurm_<>.py`) script: `slurm_<>/`. It contains all the job options (generated using `testBTriggerTuning_template.py` as a template), and contains a subdirectory `t_N` for each of the N tasks.

# Example of workflow to create a new hybrid tuning from scratch
This is basically a guide through the 4 steps explained above, including all the technicalities.
General: when creating an hybrid tuning all the steps include a mixture of ttbar and Zprime. Also the [TrigBtagAnalysis](https://gitlab.cern.ch/atlas-trigger/b-jet/TrigBtagAnalysis) has a dedicate branch for the hybrid tuning, so make sure to check it out before going through this. There are 2 main differences wrt/ the master:
- [reference histograms are filled](https://gitlab.cern.ch/atlas-trigger/b-jet/TrigBtagAnalysis/blob/hybrid/src/BTriggerTuning.cxx#L579) only for jets good for the hybrid tuning
- some [track variables](https://gitlab.cern.ch/atlas-trigger/b-jet/TrigBtagAnalysis/blob/hybrid/src/BTriggerTuning.cxx#L175) are included

## step1
Info about the calibration and the step are stored in the json files in `calibJson/`. So create the corresponding json file containing the following info:
```
{"date" : "<date>", "step" : "step1", "calibtag" : "WHATEVER", "jettype" : "SplitJet"}
```
In particular I use to name calibration tags as `<date>_<step>`. Of course this is arbitrary, but the code is expecting this naming convention. For this example I'll use `20060709`.
Now set things up for the actual jobs:
```
python prepare_slurm_array.py -input <path/to/20060709_step1.json> -sample ttbar
python prepare_slurm_array.py -input <path/to/20060709_step1.json> -sample Zprime
```
Two remarks about the above command:
- if you want to run on grid just replace `prepare_slurm_array.py` with `prepare_grid_job.py`
- if you are running locally (i.e. on SLURM) you need two txt files containing a local copy of the input datasets, one for Zprime and one for ttbar, e.g.:
```
[flosterzo@login05 run]$ cat sample_ttbar.txt
/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000011.pool.root.1
/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000012.pool.root.1
/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000013.pool.root.1
/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000014.pool.root.1
/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000015.pool.root.1
(...)
```

Each of the above commands will create a directory containing everything that is needed to run the full job. Let's call it `job_20060709_<sample>_step1` (of course you'll have one for Zprime and one for ttbar).
Again, there is a difference if you run on grid or on SLURM:
- *grid*: a single job is submitted, usually 1 job per file is submitted (if you try to submit more than 1 file per job, most likely the job will fail because of memory issues)
- *slurm*: thanks to SLURM arrays, everything can be highly paralellized: in particular here each file is split in 4 different jobs, each analysing 2500 events (this is tuned from inside the JobOption, see `jp.AthenaCommonFlags.SkipEvents.set_Value_and_Lock( MYSTART )` and `jp.AthenaCommonFlags.EvtMax.set_Value_and_Lock( vars().get('EVTMAX', 2500) )`). The material for each task is contained in a dedicated subdirectory `job_20060709/t_<taskID>`, and so will be the outputs.

If you run a grid job, the actual command will be stored in `job_20060709_<sample>_step1/command`, and you just need to source that. If you run on slurm, the command to submit the slurm array is printed out by the `prepare_slurm_array.py` script. Take note of the `jobId`.

Once the SLURM jobs are completed, you need to check whether any of them has failed (usually the failure rate around a few percents). You can do this by running:
```
python findFailedJobs.py -dir job_20060709_<sample>_step1 -job <jobId>
```
where `jobId` is the ID of the slurm array. If there are any faild tasks, the command to resubmit them is printed out, when you resubmit take note of the new `jobId` in order to redo this procedure.

Once all the jobs are done for both ttbar and Zprime, run the following command to merge the `RefHistos` files from all the subjobs/subtasks:
```
python mergeFiles.py -dir job_20060709_<sample>_step1 -what RefHistos
```
This script creates a `merge.sh` which you have to source. This script simply `hadd`s all the RefHistos created so far, the output name is created given the input names.

Now we need to create a calibration tag as in step 1.1 in the above instructions. Log into a clean shell and move to the `calibFilePreparator` directory. Set things up with:
```
setupATLAS
asetup 21.0.13.1,AtlasProduction,64,here,gcc49,slc6
```
Copy over the `RefHistos_20060709_<sample>_step1.root` here, also the `SomeFileWithMissingTaggers.root` has to be in this directory. Create a new directory, I usually name it `20060709_step1`. This directory has to contain two files:
- `filesToHadd.txt`: as from the name, this file contains the list of files which has to be merged together, one per line. At this step three files are needed: `RefHistos_20060709_ttbar_step1.root`, `RefHistos_20060709_Zprime_step1.root` and `SomeFileWithMissingTaggers.root`.
- `coolScript.sh`: containing the following list of commands:
```
file="RefFile_20060709_step1.root"
suffix="20060709_step1"
coolHist_setFileIdentifier.sh $file
coolHist_insertFileToCatalog.py  $file
coolHist_setReference.py OFLP200 /GLOBAL/TrigBTagCalib/RUN12 1 $suffix $file
AtlCoolConsole.py "sqlite://;schema=mycool.db;dbname=OFLP200"
```
Move into this directory and run - **pay attention to `file` and `suffix`**: the former is the name of the root file you just created, the second is the name of the calibration tag, again usually `<date>_<step>`.
```
python ../createRefFile.py
```
This script opens `filesToHadd.txt` and hadds its content. This of course could have been done by hand, but this procedure with a dedicated txt file helps keeping track of what files go into which calibration tag.  

After that just run `source coolScript.sh` and at the end, from inside the python REPL which is open, run:
```
setchan /GLOBAL/TrigBTagCalib/RUN12 1 RUN12
```

After this, the directory should contain these additional files: `mycool.db`, `coolhist_guid.tmp`, `coolhist_tempcat.xml`, `PoolFileCatalog.xml`.

## step2
Log back in, go to `Tuning_rel21/run/` and setup the proper release (as from the [twiki](https://twiki.cern.ch/twiki/bin/viewauth/Atlas/BTriggerTuning)). As above, create a new calibration json file `calibJson/20060709_step2.json`:
```
{"date" : "20060709", "step" : "step2", "calibtag" : "20060709_step1", "jettype" : "SplitJet"}
```
Now run again the preparation scripts as above, but using the new json file and submit the new jobs.

Once all the jobs are completed we need to prepare the input for the step3, i.e. propely mix the `flavntuple`-s obtained at this step. Open the `mixOnlineTrees.py` script and edit the `path_ttbar` and `path_zprime` to the (full) path to the directories containing the outputs of the jobs. Also edit `out_dir` and `out_name` to whatever you want, for consistency in this example they will be `mix_20060709` and `hybrid_20060709_mix.root` respectively. Now run `python mixOnlineTrees.py`, this will create a `merge.sh` script which you have to source.

*Note*: if you are running a standard training (or a training bases only on Zprime), you don't need to mix ttbar and Zprime but just run `python mergeFiles.py -dir job_20060709_<sample>_step1 -what flavntuple`.

## step3
As far as I understand this step can only be run on SLURM, as it requires **a lot** of memory.
Log into a clean shell and move to `trainingMV2`. Set things up with (just dumping my `setup.sh` script):
```
setupATLAS --quiet
#rootVersion=5.34.25-x86_64-slc6-gcc48-opt
rootVersion=6.04.02-x86_64-slc6-gcc48-opt #for compatibility with TMVA-agile
localSetupROOT $rootVersion --quiet
echo "==> Setting up ROOT version: "$rootVersion
```

Follow instruction from [here](https://svnweb.cern.ch/trac/atlas-mociduki/browser/btag/trainingMV2/trunk/README). Some info about the varlist file: this file contains the list of relevant variables and types, e.g.:
```
pt,     D
```
Its name instead contains the hyperparameters of the algorithm (details are given in the above link). In order to activate the hybrid tuning the name has to contain `HybridTune`. An example file can be found in `/eos/atlas/atlascerngroupdisk/trig-bjet/Year-2018/hybrid_tuning/auxfiles/`. For the sake of cleanliness, the weight files are stored in the `weight/` directory.

The inputs for the training (i.e. the flavntuples from the previous steps) should be in the `inputs/<date>` directory.
The job is set up with the `submit_slurm_training.py` script. You just need to set the proper `input_dir` and the `weights_file` and then launch it. This will submit a slurm jobs that usually takes 20-24 hours.

If the job is successful, a number of new files are created in the `weights/` directory. They are all named as the original `varlist` file, but with different extensions:
```
[flosterzo@login05 trainingMV2]$ ll weights/
-rw-rw-r-- 1 flosterzo flosterzo   32071584 May 30 07:44 <original name of the varlist file>_BDTG.class.C
-rw-rw-r-- 1 flosterzo flosterzo  164678053 May 30 07:43 <original name of the varlist file>_BDTG.weights.xml
-rw-r--r-- 1 flosterzo flosterzo     833551 May 30 10:22 <original name of the varlist file>.graphs.root
-rw-r--r-- 1 flosterzo flosterzo     190521 May 30 10:22 <original name of the varlist file>.hists.root
-rw-r--r-- 1 flosterzo flosterzo 1462675384 May 30 09:19 <original name of the varlist file>.root
-rw-r--r-- 1 flosterzo flosterzo        259 May 29 05:28 <original name of the varlist file>.varlist
```
After this go back to `calibFilePreparator` and (after the proper setup) run:
```
root -l convertXml2ROOT.C+
xml2Root("<the weight xml file produced in the previous step>", \"MV2c00\")
xml2Root("<the weight xml file produced in the previous step>", \"MV2c10\")
xml2Root("<the weight xml file produced in the previous step>", \"MV2c20\")
```
Each of the above command creats a root file `MV2cXX_AntiKt4EMTopo.root`. Now create a new directory (in this example will be `20060709_step3`) with a new `filesToHadd.txt` and a new `coolScript.sh`. The former should contain:
- the two `RefHisto` files from step1
- the three `MV2cXX` files just created
- `BTagCalibRUN2Onl-08-05_2.root`

The `coolScript.sh` script is instead equivalent to the above, just change `step1` to `step3`. Again, run: `python createRefFile.py` and `source coolScript.sh` (and from inside the python REPL `setchan /GLOBAL/TrigBTagCalib/RUN12 1 RUN12`).

## step4
Log back in, go to `Tuning_rel21/run/` and setup the proper release (as from the [twiki](https://twiki.cern.ch/twiki/bin/viewauth/Atlas/BTriggerTuning)). As above, create a new calibration json file `calibJson/20060709_step4.json`.

Prepare and run the jobs. In case you are running on SLURM check the outcome of the jobs and eventually use the `mergeFiles.py` script to merge the `flavntuple`-s. In these flavntuples the jets are tagged using the new hybrid training and therefore should be used to study the performances.

# Log of (my) calibration tags

<!--
[bugged] **20171004**: standard (i.e. ttbar-based) calibration.  
Intermediate tags/files:
- 20171004_std_step1 : RefFile_20171004_ttbar_step1.root
- 20171004_std_step3 : RefFile_20171004_std_step3.root

[bugged] **20171010**: hybrid calibration.  
Intermediate tags/files:
- 20171010_tt_step1 : RefFile_20171010_ttbar_step1.root
- 20171010_zp_step1bis : RefFile_20171010_Zprime_step1.root
- 20171010_hyb_step4 : RefFile_20171010_Hybrid_step4.root

**20171023**: standard calibration.  
Intermediate tags/files:
- 20171023_std_step1 : RefFile_20171004_ttbar_step1.root
- 20171023_std_step3bis : RefFile_20171023_ttbar_step3bis.root

[bugged] **20171031**: hybrid calibration.  
The `jet_ForHybrid` flag is set wrong for ttbar high-pt jets
Intermediate tags/file:  
- 20171023_hyb_step1 : RefFile_20171031_hyb_step1.root  
- 20171031_hyb_step3bis : RefFile_20171031_step3bis.root  

[bugged] **20171206**: hybrid calibration.
The `jet_ForHybrid` flag is read wrong at the training step.

**20180109**: hybrid calibration.  
Fixed with proper handling of the `jet_ForHybrid` flag. Up to the training the same files/tags as 20171206 are used, since the bug was only at the training step.
- 20171023_hyb_step1 : RefFile_20171031_hyb_step1.root  
- 20180109_step3 : RefFile_20180109_step3.root

**20180122**: hybrid calibration.  
pt threshold for ttbar/Zprime mixing raised to 300 GeV in order to match the different pt scales between online and offline.  
- 20180122_step2 : RefFile_20180122_step2.root   
- 20180122_step3 : RefFile_20180122_step3.root  

**20180202**: standard calibration.  
Same input as 20171023, the pt/eta spectra are reweighted to b-jets (instead of l-jets as done so far)
- 20171023_std_step1: RefFile_20171004_ttbar_step1.root  
- 20180202_step3: RefFile_20180202_step3.root

**20180209**: hybrid calibration.  
ttbar-vs-Zprime splitting done based on the jet pt for all flavors (in order to have a pure ttbar sample at low pt and a pure Zprime sample at high-pt)  
- 20180209_step2: RefFile_20180209_step2.root
- 20180209_step3: RefFile_20180209_step3.root

[bugged] **20180302**: hybrid calibration.
standard settings (i.e. inputs from the latest hybrid calibration 20180109) / `puCut1` was used, and it doesn't make sense for online
- 20180302_step3: RefFile_20180302_step3.root

[bugged] **20180307**: hybrid calibration.
standard settings (i.e. inputs from the latest hybrid calibration 20180109). Variables in the xml file have the wrong name
- 20180307_step3: RefFile_20180307_step3.root

**20180307bis**: hybrid calibration.
standard settings (i.e. inputs from the latest hybrid calibration 20180109) - `sv1_lxy` and `sv1_l3d` moved to `sv1_Lxy` and `sv1_L3d` respectively in the xml file
- 20180307bis_step3: RefFile_20180307bis_step3.root

**20180319**: hybrid calibration.  
standard settings (i.e. inputs from the latest hybrid calibration 20180109) with pt/eta reweighting done using b-jets as a target. This is the reference online hybridr tuning.
- 20180319_step3: RefFile_20180319_step3.root  

**OFFLINE**: hybrid calibration.  
using the real offline training obtained from the xml obtained for the offline official training (offline training on offline jets).  
(for the rest the same info as 20180319 are used)
- OFFLINE: Ref_OFFLINE.root  

**ALLOFFLINE**: hybrid calibration.  
using full offline calibration, i.e. calib tag created out of the offline reffile.
- ALLOFFLINE: Ref_ALLOFFLINE.root (just a copy of: `/afs/cern.ch/atlas/groups/perf-flavtag/ReferenceHistograms/BTagCalibRUN2-08-40.root`)

**20180503**: hybrid calibration.  
full online hybrid calibration using hand-made reshuffling (alternate ttbar and Zprime files) and using 3M events for each sample (i.e. only the first 1.2k files from ttbar
in order to match the stats of Zprime). The input is built out of flavntuples (from step2) of 20171206, using the files with 2.5k events each:
- hybrid_20171206_mix.root <- 20171206_ttbar_step2 + 20171206_Zprime_step2
- 20180503_step3: RefFile_20180503_step3.root

-->

**20180507**: hybrid calibration on GSCJet  
full online hybrid calibration using hand-made reshuffling (alternate ttbar and Zprime files) and using 3M events for each sample (i.e. only the first 1.2k files from ttbar
in order to match the stats of Zprime).
- hybrid_20171206_mix.root <- 20171206_ttbar_step2 + 20171206_Zprime_step2  
- 20180503_step3: RefFile_20180503_step3.root

**20180514**: standard calibration on GSCJet  
- 20180514_step3: RefFile_20180514_step3.root

**20180522**: hybrid calibration on SplitJets  

**20180529**: ATLAS calibration on SplitJets

**20180619**: ATLAS calibration on GSCJets  

**20180709**: "hybrid*" training, i.e. hybrid training based on ttbar-only reference histograms

The relevant `RefFiles` and `flavntuples` are stored in `/eos/atlas/atlascerngroupdisk/trig-bjet/Year-2018/hybrid_tuning/` on lxplus.

# Usage of `NtupConverter`

`NtupConverter` is used to convert the online flavntuple to an offline-like flavntuple (basically mapping variable names and filling unused branches with dummy values). Usage:
```
root -l <name of the file you want to process>
root> .L NtupConverter.C++
root> NtupConverter *a = new NtupConverter(bTag_TriggerJets)
root> a->Loop("<output file name>", <# of events in the output files>)
```
If the second argument in the `NtupConverter::Loop()` method is set to a negative value, then the output is stored in a single file otherwise the output is split in >1 files, each containing up to the specified number of events.
