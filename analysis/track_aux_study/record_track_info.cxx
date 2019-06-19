#include "../util/titles.hh"

const int _num_jettypes = 1;
const int _num_helix_params = 5;
const int _num_plot_types = 6;
const float _pt_min_cutoff = 55*1000; //= 55 GeV
const float _eta_min_cutoff = 2.5; //= 55 GeV

string _value_name[_num_plot_types] = {
    "numPixelHits",
    "numSCTHits",
    "numPixelDeadSensors",
    "numSCTDeadSensors",
    "numPixelHoles",
    "numSCTHoles"
};

int _plot_range[_num_plot_types][2] = {
/*numPixelHits*/           {0, 10000},
/*numSCTHits*/             {0, 10000},
/*numPixelDeadSensors*/    {0, 10000},
/*numSCTDeadSensors*/      {0, 10000},
/*numPixelHoles*/          {0, 10000},
/*numSCTHoles*/            {0, 10000}
};


vector< vector<TH1I*>* >* make_histograms(string label) {
    vector< vector<TH1I*>* >* histogram_vector_list = new vector< vector<TH1I*>* >();
    for (int jettype_index = 0; jettype_index < _num_jettypes; jettype_index++) {
        vector<TH1I*>* histogram_vector = new vector<TH1I*>();
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            float xmin = _plot_range[plot_index][0];
            float xmax = _plot_range[plot_index][1];
            int num_bins = 1e6;//_plot_resolution[plot_index]*(xmax-xmin);

            string name = label+"_"+_value_name[plot_index]+"_"+to_string(jettype_index);
            TH1I* new_hist = new TH1I( name.c_str(), name.c_str(), num_bins, xmin, xmax );
            histogram_vector->push_back(new_hist);
        }
        histogram_vector_list->push_back(histogram_vector);
    }

    return histogram_vector_list;
}


void fill_histograms(TFile& data_file, vector< vector<TH1I*>* >* histogram_vector_list) {
    TTreeReader tree_reader("bTag_TriggerJets", &data_file);
    TTreeReaderValue< vector<int> > coneID_vector_reader(tree_reader, "jet_truthflav");
    TTreeReaderValue<   vector<  vector< vector<int> >  >   > track_info_reader(tree_reader, "track_aux_info");

    int event_number = 0;
    //cout << "Iterating over event indices..." << endl;
    while ( tree_reader.Next() ) {
        vector<int> coneID_vector = *coneID_vector_reader;
        vector<  vector< vector<int> >  > track_information = *track_info_reader;
        //cout << "|---Iterating over jet indices..." << endl;
        for (int jet_index = 0; jet_index < coneID_vector.size(); jet_index++) {
            //unset, uncomment below, and set _num_jettypes=3 to split jets
            int jettype_index = 0;
            /*switch (coneID_vector[jet_index]) {
                case 5: jettype_index=0; break;
                case 4: jettype_index=1; break;
                default: jettype_index=2; break;
            }*/

            vector< vector<int> > track_container = track_information[jet_index];
            //cout << "|   |---Iterating over tracks..." << endl;
            for (vector<int> track : track_container) {
                for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
                    histogram_vector_list->at(jettype_index)->at(plot_index)->Fill(track[plot_index]);
                }
            }
        }
        //if (event_number++ > 10) break;
    }
}


void save_histograms(vector< vector<TH1I*>* >* histogram_vector_list, string label) {
    TFile root_file( ("extracted_"+label+".root").c_str(), "recreate");
    for (int jettype_index = 0; jettype_index < _num_jettypes; jettype_index++) {
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            string name = label+"_"+_value_name[plot_index]+"_"+to_string(jettype_index);
            histogram_vector_list->at(jettype_index)->at(plot_index)->Write();
        }
    }
}


void record_flavntuple( string flavntuple_name, string label) {
    cout << "Initializing histograms..." << endl;
    vector< vector<TH1I*>* >* histogram_vector_list = make_histograms(label);
    cout << "Reading " << flavntuple_name << "..." << endl;
    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    cout << "Filling Histograms..." << endl;
    fill_histograms(flavntuple_file, histogram_vector_list);
    cout << "Saving Histograms..." << endl;
    save_histograms(histogram_vector_list, label);
}


void record_track_info() {
    //record_flavntuple("/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/manual_tests/auxdata_test/flavntuple_hlt_0.root", "test");
    record_flavntuple(_slurm_arrays+"slurm_20190612_hlt_track_study_ttbar_410470_small_step1/merged_flavntuple.root", "hlt");
    record_flavntuple(_slurm_arrays+"slurm_20190612_ftk_track_study_ttbar_410470_small_step1/merged_flavntuple.root", "ftk_idtrig");
    record_flavntuple(_slurm_arrays+"slurm_20190612_ftkRefit_track_study_ttbar_410470_small_step1/merged_flavntuple.root", "ftkRefit_idtrig");
}
