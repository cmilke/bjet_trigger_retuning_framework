#include "../util/titles.hh"

const int _num_helix_params = 5;
const int _num_plot_types = 17;
const float _pt_min_cutoff = 55*1000; //= 55 GeV
const float _eta_min_cutoff = 2.5; //= 55 GeV

string _value_name[_num_plot_types] = {
/*00*/     "pt",
/*01*/     "d0",
/*02*/     "d0_err",
/*--*/     "d0_sig",
/*03*/     "z0",
/*04*/     "z0_err",
/*--*/     "z0_sig",
/*05*/     "phi0",
/*06*/     "phi0_err",
/*--*/     "phi0_sig",
/*07*/     "theta",
/*08*/     "theta_err",
/*--*/     "theta_sig",
/*09*/     "qOverP",
/*10*/     "qOverP_err",
/*--*/     "qOverP_sig",
/*--*/     "eta"
};

float _plot_range[_num_plot_types][2] = {
     {0, 1e5},          //pt
     {-100, 100},       //d0
     {0, 1e2},          //d0_err
     {-1e3, 1e3},         //d0_sig
     {1e4, 1e4},         //z0
     {0, 1e2},          //z0_err
     {-1e4, 1e4},          //z0_sig
     {-M_PI, M_PI},       //phi0
     {0, 0.1},       //phi0_err
     {-1e5, 1e5},       //phi0_sig
     {0, M_PI},       //theta
     {0, 0.1},       //theta_err
     {0, 1e6},       //theta_sig
     {-1e-2, 1e-2},         //qOverP
     {0, 1e-3},         //qOverP_err
     {-1e3, 1e3},          //qOverP_sig
     {-10,10}        //eta
};


vector< vector<TH1F*>* >* make_histograms(string label) {
    vector< vector<TH1F*>* >* histogram_vector_list = new vector< vector<TH1F*>* >();
    for (int jettype_index = 0; jettype_index < 3; jettype_index++) {
        vector<TH1F*>* histogram_vector = new vector<TH1F*>();
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            float xmin = _plot_range[plot_index][0];
            float xmax = _plot_range[plot_index][1];
            int num_bins = 1e6;//_plot_resolution[plot_index]*(xmax-xmin);

            string name = label+"_"+_value_name[plot_index]+"_"+to_string(jettype_index);
            TH1F* new_hist = new TH1F( name.c_str(), name.c_str(), num_bins, xmin, xmax );
            histogram_vector->push_back(new_hist);
        }
        histogram_vector_list->push_back(histogram_vector);
    }

    return histogram_vector_list;
}


void fill_histograms(TFile& data_file, vector< vector<TH1F*>* >* histogram_vector_list) {
    TTreeReader tree_reader("bTag_TriggerJets", &data_file);
    TTreeReaderValue< vector<int> > coneID_vector_reader(tree_reader, "jet_truthflav");
    TTreeReaderValue<   vector<  vector< vector<float> >  >   > track_info_reader(tree_reader, "track_info");

    int event_number = 0;
    //cout << "Iterating over event indices..." << endl;
    while ( tree_reader.Next() ) {
        vector<int> coneID_vector = *coneID_vector_reader;
        vector<  vector< vector<float> >  > track_information = *track_info_reader;
        //cout << "|---Iterating over jet indices..." << endl;
        for (int jet_index = 0; jet_index < coneID_vector.size(); jet_index++) {
            int jettype_index;
            switch (coneID_vector[jet_index]) {
                case 5: jettype_index=0; break;
                case 4: jettype_index=1; break;
                default: jettype_index=2; break;
            }

            vector< vector<float> > track_container = track_information[jet_index];
            //cout << "|   |---Iterating over tracks..." << endl;
            for (vector<float> track : track_container) {
                histogram_vector_list->at(jettype_index)->at(0)->Fill(track[0]);
                //cout << "|   |   |---Iterating over helix parameters..." << endl;
                for (int helix_param = 0; helix_param < _num_helix_params; helix_param++) {
                    float parameter = track[helix_param*2+1];
                    float error = track[helix_param*2+2];
                    float significance = parameter / error;
                    //cout << "|   |   |   |---helix: ";
                    //cout << helix_param << " " << parameter << " " << " " << error << " " << significance << endl;

                    histogram_vector_list->at(jettype_index)->at(helix_param*3+1)->Fill(parameter);
                    histogram_vector_list->at(jettype_index)->at(helix_param*3+2)->Fill(error);
                    histogram_vector_list->at(jettype_index)->at(helix_param*3+3)->Fill(significance);
                }
                float theta = track[7];
                float eta = -log(tan(theta/2.0));
                histogram_vector_list->at(jettype_index)->at(16)->Fill(eta);
            }
        }
        //if (event_number++ > 10) break;
    }
}


void save_histograms(vector< vector<TH1F*>* >* histogram_vector_list, string label) {
    TFile root_file( ("extracted_"+label+".root").c_str(), "recreate");
    for (int jettype_index = 0; jettype_index < 3; jettype_index++) {
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            string name = label+"_"+_value_name[plot_index]+"_"+to_string(jettype_index);
            histogram_vector_list->at(jettype_index)->at(plot_index)->Write();
        }
    }
}


void record_flavntuple( string flavntuple_name, string label) {
    cout << "Initializing histograms..." << endl;
    vector< vector<TH1F*>* >* histogram_vector_list = make_histograms(label);
    cout << "Reading " << flavntuple_name << "..." << endl;
    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    cout << "Filling Histograms..." << endl;
    fill_histograms(flavntuple_file, histogram_vector_list);
    cout << "Saving Histograms..." << endl;
    save_histograms(histogram_vector_list, label);
}


void record_tracks( string flavntuple_name, string label) {
    record_flavntuple(flavntuple_name, label);
}


void record_track_info() {
    //record_tracks("/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/manual_tests/track_test/flavntuple_htl.root", "hlt_test");
    record_tracks(_slurm_arrays+"slurm_20190612_hlt_track_study_ttbar_410470_small_step1/merged_flavntuple.root", "hlt");
    record_tracks(_slurm_arrays+"slurm_20190612_ftk_track_study_ttbar_410470_small_step1/merged_flavntuple.root", "ftk_idtrig");
    record_tracks(_slurm_arrays+"slurm_20190612_ftkRefit_track_study_ttbar_410470_small_step1/merged_flavntuple.root", "ftkRefit_idtrig");
    //record_tracks(_slurm_arrays+"slurm_20190420_ftkVtx_ttbar_41000valid1_full_step1/merged_flavntuple.root", "ftkVtx");
}
