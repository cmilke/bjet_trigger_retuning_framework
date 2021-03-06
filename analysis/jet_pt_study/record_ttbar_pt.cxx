string _slurm_arrays = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/";

void record_ttbar_pt(string title, string flavntuple_name) {
    TH1F* ttbar_pt_histogram = new TH1F(title.c_str(), "Pt Spectrum of T-Tbar Events", 1E4, 0, 1E4);

    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    TTreeReader collection_reader("bTag_TriggerJets", &flavntuple_file);
    TTreeReaderValue< vector<int> > coneID_vector_reader(collection_reader, "jet_truthflav");
    TTreeReaderValue< vector<float> > jet_pt_reader(collection_reader, "jet_pt");

    while ( collection_reader.Next() ) {
        vector<float> jet_pt_vector = *jet_pt_reader;
        vector<int> coneID_vector = *coneID_vector_reader;
        for (int vector_index = 0; vector_index < jet_pt_vector.size(); vector_index++) {
        vector<int> coneID_vector = *coneID_vector_reader;
            int coneID = coneID_vector[vector_index];
            float jet_pt = jet_pt_vector[vector_index];
            if ( coneID == 5 ) { ttbar_pt_histogram->Fill(jet_pt/1000.0); }
            //ttbar_pt_histogram->Fill(jet_pt); 
            //cout << vector_index << " " << jet_pt << endl;
        }
    }
    cout << "Generating Histograms\n\n";

    ttbar_pt_histogram->SaveAs( (title+".root").c_str() );
}
