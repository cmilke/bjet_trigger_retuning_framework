void record_Zprime_pt() {
    TH1F* Zprime_pt_histogram = new TH1F("pt_Zprime", "Pt Spectrum of Z\' Events", 1E4, 0, 1E4);

    string flavntuple_name = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavntuple_20181122_Zprime_test_step4.root";
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
            if ( coneID == 5 ) { Zprime_pt_histogram->Fill(jet_pt/1000.0); }
            //Zprime_pt_histogram->Fill(jet_pt); 
            //cout << vector_index << " " << jet_pt << endl;
        }
    }
    cout << "Generating Histograms\n\n";

    Zprime_pt_histogram->SaveAs("Zprime_pt_histogram.root");
}
