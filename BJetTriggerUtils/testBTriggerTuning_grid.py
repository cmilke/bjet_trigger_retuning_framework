## this is a template. Interesting parameters can be found looking for string "MY"
############# USER PARAMETERS ########
RETAG = MYRETAG
LocalCalibSuffix = "MYCALIB"
#####################################
### Define input xAOD and output ntuple file name
import glob
from AthenaCommon.AthenaCommonFlags import jobproperties as jp
#jp.AthenaCommonFlags.SkipEvents.set_Value_and_Lock( MYSTART )
#jp.AthenaCommonFlags.EvtMax.set_Value_and_Lock( vars().get('EVTMAX', 2500) )
evtPrintoutInterval = vars().get('EVTPRINT', 5000)
svcMgr += CfgMgr.AthenaEventLoopMgr( EventPrintoutInterval=evtPrintoutInterval )

jp.AthenaCommonFlags.FilesInput = [ 
    ###PLEASE USE a TTBAR xAOD file
    # Please give a mc16 sample file for running with rel21
    '/eos/user/l/losterzo/files/BJetTrigger/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000255.pool.root.1'
    ]
from PyUtils import AthFile
af = AthFile.fopen( jp.AthenaCommonFlags.FilesInput()[0] )
evtPrintoutInterval = vars().get('EVTPRINT', 5000)
svcMgr += CfgMgr.AthenaEventLoopMgr( EventPrintoutInterval=evtPrintoutInterval )
svcMgr += CfgMgr.THistSvc()
svcMgr.THistSvc.Output += ["TriggerJets DATAFILE='MYFLAVFILE' OPT='RECREATE'"]
svcMgr.THistSvc.Output += ["RefFile DATAFILE='MYREFFILE' OPT='RECREATE'"]

from AthenaCommon.DetFlags import DetFlags
DetFlags.BField_setOn()
DetFlags.ID_setOn()
DetFlags.Calo_setOff()
DetFlags.Muon_setOff()

from RecExConfig.RecFlags import rec
rec.doTrigger.set_Value_and_Lock(True)
from RecExConfig.RecAlgsFlags  import recAlgs
recAlgs.doTrigger.set_Value_and_Lock(True)
from TriggerJobOpts.TriggerFlags import TriggerFlags
TriggerFlags.doTriggerConfigOnly.set_Value_and_Lock(True)

from RecExConfig.RecFlags import rec
rec.doESD.set_Value_and_Lock        (False)
rec.doWriteESD.set_Value_and_Lock   (False)
rec.doAOD.set_Value_and_Lock        (False)
rec.doWriteAOD.set_Value_and_Lock   (False)
rec.doWriteTAG.set_Value_and_Lock   (False)
rec.doDPD.set_Value_and_Lock        (False)
rec.doTruth.set_Value_and_Lock      (False)

if af.fileinfos["metadata"]["/TagInfo"]["AtlasRelease"].__contains__("AtlasDerivation"):
    rec.doApplyAODFix.set_Value_and_Lock(False)

include ("RecExCommon/RecExCommon_topOptions.py")

from AthenaCommon.AlgSequence import AlgSequence
algSeq = AlgSequence()

### GEO Business 
from AthenaCommon.GlobalFlags import globalflags
print "detDescr from global flags= "+str(globalflags.DetDescrVersion)
from AtlasGeoModel.InDetGMJobProperties import GeometryFlags as geoFlags
print "geoFlags.Run()   = "+geoFlags.Run()
print "geoFlags.isIBL() = "+str(  geoFlags.isIBL() )

###############################################################
### THIS is the full retagging configuration
### this is if you want to re-tag with another calibration file
from BTagging.BTaggingConfiguration import getConfiguration
from BTagging.BTaggingFlags import BTaggingFlags

#### if the new file is already in the datatbase: simple edit the name
#BTaggingFlags.CalibrationTag = 'BTagCalibRUN12-08-18'
#### if you want to use your own calibration file use this part below
if RETAG & (LocalCalibSuffix!='WHATEVER') :
    BTaggingFlags.CalibrationFromLocalReplica = True
    BTaggingFlags.TrigCalibrationFolderRoot = '/GLOBAL/TrigBTagCalib/'
    BTaggingFlags.TrigCalibrationTag = LocalCalibSuffix
#### if you want to use the real actual calibration
#if RETAG:
#    BTaggingFlags.TrigCalibrationFolderRoot = '/GLOBAL/TrigBTagCalib/'
#    BTaggingFlags.TrigCalibrationTag = 'TrigBTagCalibRUN12-08-12'

#BTaggingFlags.Jets = ['AntiKt4EMTopo']

BTagConf = getConfiguration("Trig")
ip3d =BTagConf.getTool("IP3DTag", "BTagTrackToJetAssociator","AntiKt4EMTopo")
ip3dTrkSel=BTagConf.getTool("IP3DTrackSelector", "BTagTrackToJetAssociator","AntiKt4EMTopo")
ip3dLH=BTagConf.getTool("IP3DNewLikelihoodTool", "BTagTrackToJetAssociator","AntiKt4EMTopo")
ip2d  =BTagConf.getTool("IP2DTag", "BTagTrackToJetAssociator","AntiKt4EMTopo")
mv2c20 =BTagConf.getTool("MV2c20Tag", "BTagTrackToJetAssociator","AntiKt4EMTopo")

BTagConf.PrefixxAODBaseName(False)
BTagConf.PrefixVertexFinderxAODBaseName(False)
BTagConf.doNotCheckForTaggerObstacles()
NotInJetToolManager = [] # For jet collections

btagger = BTagConf.setupJetBTaggerTool(ToolSvc, "AntiKt4EMTopo", AddToToolSvc=True,
                                       SetupScheme="Trig",
                                       TaggerList=BTaggingFlags.TriggerTaggers
                                       )

from TrkVertexFitterUtils.TrkVertexFitterUtilsConf import Trk__TrackToVertexIPEstimator
ToolSvc+=Trk__TrackToVertexIPEstimator("trkIPEstimator")

alg1 = CfgMgr.BTriggerTuning()
### For FTK
#alg1.TriggerName = "HLT_j35_boffperf_split_FTK"
#alg1.Trig_JetKey = "SplitJet"
#alg1.Trig_PriVtxKey = "HLT_PrimVertexFTK"  # Primary vertices are not attached to the trigger navigation yet. Should be solved by 21.0.18
#alg1.Trig_TrackKey = "InDetTrigTrackingxAODCnv_Bjet_FTK_IDTrig"


#alg1.TriggerName = "HLT_j35_boffperf_split"
alg1.TriggerName = "HLT_j15_gsc35_boffperf_split"
alg1.Stream = "TriggerJets"
alg1.Trig_JetKey = "JETTYPE"
alg1.BTagTool           = BTagConf.getJetCollectionTool("AntiKt4EMTopo")
alg1.BTagTrackAssocTool = BTagConf.getJetCollectionMainAssociatorTool("AntiKt4EMTopo")
alg1.BTagSecVertexing   = BTagConf.getJetCollectionSecVertexingTool("AntiKt4EMTopo")
#alg1.Trig_PriVtxKey = "EFHistoPrmVtx"
alg1.debug = True
alg1.Retag = RETAG
alg1.WhichLabel = 1 # was 3 # FLS
## FLS - to augment track info
alg1.TrackToVertexIPEstimator = ToolSvc.trkIPEstimator

algSeq += alg1

## CAN UNCOMMENT FOR DETAILED DEBUGGING
#ToolSvc.IP2DTag_Trig.OutputLevel = DEBUG
#ToolSvc.MV2c20Tag.OutputLevel = DEBUG
#ToolSvc.BTagCalibrationBrokerTool_Trig.OutputLevel = DEBUG

#ToolSvc.MV2c00Tag_Trig.MV2CalibAlias = "AntiKt4EMTopo"
#ToolSvc.MV2c00Tag_Trig.MV2CalibAlias = "AntiKt4EMTopo"
#ToolSvc.MV2c20Tag_Trig.MV2CalibAlias = "AntiKt4EMTopo"

### Additional Tools needed by the algo
from TrackVertexAssociationTool.TrackVertexAssociationToolConf import CP__TightTrackVertexAssociationTool
ToolSvc+=CP__TightTrackVertexAssociationTool("TightVertexAssocTool",dzSinTheta_cut=3, doPV=True)

from InDetTrackSelectionTool.InDetTrackSelectionToolConf import InDet__InDetTrackSelectionTool
ToolSvc+=InDet__InDetTrackSelectionTool("InDetTrackSelTool", CutLevel="Loose", maxZ0SinTheta=3)


from TrigDecisionTool.TrigDecisionToolConf import Trig__TrigDecisionTool
ToolSvc += Trig__TrigDecisionTool( "TrigDecisionTool" )
from TrigEDMConfig.TriggerEDM import EDMLibraries
ToolSvc.TrigDecisionTool.Navigation.Dlls = EDMLibraries

