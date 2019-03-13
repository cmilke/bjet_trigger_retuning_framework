void print_info() {
    vector<string> file_list{
        "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000230.pool.root.1"
        //"/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavntuple_20181122_ttbar_step1.root"
        //"/scratch/users/ssekula/data/mc16_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.merge.AOD.e6337_e5984_s3126_d1480_d1471_r10681_r10682/AOD.15265992._000001.pool.root.1"
    };

    for ( string file_name : file_list ) {
        cout << "Reading " << file_name << endl << endl;
        TFile file( file_name.c_str(), "read" );
        //file.ls();
        TTree* tree;
        file.GetObject("CollectionTree", tree);
        tree->Scan("HLT_TrigPassBitsCollection_passbits");
        //file.GetObject("bTag_TriggerJets", tree);
        //tree->Print();
    }
}
