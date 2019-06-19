#include "../util/titles.hh"

const int _num_float_types = 20;
const int _num_int_types = 5;

string _float_value_name[_num_float_types] = {
    "jet_pt",
    "jet_eta",
    "jet_ip2d_pb",
    "jet_ip2d_pc",
    "jet_ip2d_pu",
    "jet_ip3d_pb",
    "jet_ip3d_pc",
    "jet_ip3d_pu",
    "jet_sv1_m",
    "jet_sv1_efc",
    "jet_sv1_Lxy",
    "jet_sv1_L3d",
    "jet_sv1_sig3d",
    "jet_sv1_dR",
    "jet_jf_m",
    "jet_jf_efc",
    "jet_jf_deta",
    "jet_jf_dphi",
    "jet_jf_sig3d",
    "jet_jf_ntrkAtVx"
};


string _int_value_name[_num_int_types] = {
    "jet_sv1_ntrkv",
    "jet_sv1_n2t",
    "jet_jf_n2t",
    "jet_jf_nvtx",
    "jet_jf_nvtx1t"
};

float _float_range[_num_float_types][2] = {
    {0, 1e7},         //jet_pt
    {-10, 10},      //jet_eta
    {0, 100},         //jet_ip2d_pb
    {0, 100},      //jet_ip2d_pc
    {0, 100},       //jet_ip2d_pu
    {0, 100},         //jet_ip3d_pb
    {0, 100},      //jet_ip3d_pc
    {0, 100},    //jet_ip3d_pu
    {0, 1e4},         //jet_sv1_m
    {-10, 10},      //jet_sv1_efc
    {-1e3, 1e3},        //jet_sv1_Lxy
    {-1e3, 1e3},         //jet_sv1_L3d
    {0, 1e3},         //jet_sv1_sig3d
    {0, 100},    //jet_sv1_dR
    {0, 2e4},        //jet_jf_m
    {0, 10},      //jet_jf_efc
    {-100, 100},      //jet_jf_deta
    {-1e3, 1e3},      //jet_jf_dphi
    {0, 1e3},      //jet_jf_sig3d
    {0, 100}       //jet_jf_ntrkAtVx
};

int _int_range[_num_int_types][2] = {
    {-100, 100},         //jet_sv1_ntrkv
    {-100, 100},      //jet_sv1_n2t
    {0, 100},         //jet_jf_n2t
    {0, 100},       //jet_jf_nvtx
    {0, 100}          //jet_jf_nvtx1t
};


vector< vector<TH1*>* >* make_histograms(string label) {
    vector< vector<TH1*>* >* histogram_vector_list = new vector< vector<TH1*>* >();
    for (int jettype_index = 0; jettype_index < 3; jettype_index++) {
        vector<TH1*>* histogram_vector = new vector<TH1*>();
        for (int float_index = 0; float_index < _num_float_types; float_index++) {
            float xmin = _float_range[float_index][0];
            float xmax = _float_range[float_index][1];
            int num_bins = 1e6;

            string name = label+"_"+_float_value_name[float_index]+"_"+to_string(jettype_index);
            TH1F* new_hist = new TH1F( name.c_str(), name.c_str(), num_bins, xmin, xmax );
            histogram_vector->push_back(new_hist);
        }

        for (int int_index = 0; int_index < _num_int_types; int_index++) {
            int xmin = _int_range[int_index][0];
            int xmax = _int_range[int_index][1];
            int num_bins = 1e4;

            string name = label+"_"+_int_value_name[int_index]+"_"+to_string(jettype_index);
            TH1I* new_hist = new TH1I( name.c_str(), name.c_str(), num_bins, xmin, xmax );
            histogram_vector->push_back(new_hist);
        }

        histogram_vector_list->push_back(histogram_vector);
    }

    return histogram_vector_list;
}


void fill_histograms(TFile& data_file, vector< vector<TH1*>* >* histogram_vector_list) {
    TTreeReader tree_reader("bTag_TriggerJets", &data_file);
    TTreeReaderValue< vector<int> > coneID_vector_reader(tree_reader, "jet_truthflav");

    vector<  TTreeReaderValue< vector<float> >  > float_reader_vector;
    vector<  TTreeReaderValue< vector<int> >  > int_reader_vector;

    for ( int float_plot_index = 0; float_plot_index < _num_float_types; float_plot_index++ ) {
        TTreeReaderValue< vector<float> > float_reader( tree_reader, _float_value_name[float_plot_index].c_str() );
        float_reader_vector.push_back(float_reader);
    }
    for ( int int_plot_index = 0; int_plot_index < _num_int_types ; int_plot_index++) {
        TTreeReaderValue< vector<int> > int_reader( tree_reader, _int_value_name[int_plot_index].c_str() );
        int_reader_vector.push_back(int_reader);
    }

    int event_number = 0;
    while ( tree_reader.Next() ) {
        vector<int> coneID_vector = *coneID_vector_reader;
        int jettype_index;
        for (int jet_index = 0; jet_index < coneID_vector.size(); jet_index++) {
            switch (coneID_vector[jet_index]) {
                case 5: jettype_index=0; break;
                case 4: jettype_index=1; break;
                default: jettype_index=2; break;
            }

            for ( int float_plot_index = 0; float_plot_index < _num_float_types; float_plot_index++ ) {
                TTreeReaderValue< vector<float> >& float_reader = float_reader_vector[float_plot_index];
                float parameter = (*float_reader)[jet_index];
                histogram_vector_list->at(jettype_index)->at(float_plot_index)->Fill(parameter);
            }

            for ( int int_plot_index = 0; int_plot_index < _num_int_types ; int_plot_index++) {
                TTreeReaderValue< vector<int> >& int_reader = int_reader_vector[int_plot_index];
                int parameter = (*int_reader)[jet_index];
                histogram_vector_list->at(jettype_index)->at(_num_float_types+int_plot_index)->Fill(parameter);
            }
        }
        //if (event_number++ > 10) break;
    }
}


void save_histograms(vector< vector<TH1*>* >* histogram_vector_list, string label) {
    TFile root_file( ("extracted_"+label+".root").c_str(), "recreate");
    for (int jettype_index = 0; jettype_index < 3; jettype_index++) {
        for (int float_index = 0; float_index < _num_float_types; float_index++) {
            string name = label+"_"+_float_value_name[float_index]+"_"+to_string(jettype_index);
            histogram_vector_list->at(jettype_index)->at(float_index)->Write();
        }

        for (int int_index = 0; int_index < _num_int_types; int_index++) {
            string name = label+"_"+_int_value_name[int_index]+"_"+to_string(jettype_index);
            histogram_vector_list->at(jettype_index)->at(int_index+_num_float_types)->Write();
        }
    }
}


void record_flavntuple( string flavntuple_name, string label) {
    cout << "Initializing histograms..." << endl;
    vector< vector<TH1*>* >* histogram_vector_list = make_histograms(label);
    cout << "Reading " << flavntuple_name << "..." << endl;
    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    cout << "Filling Histograms..." << endl;
    fill_histograms(flavntuple_file, histogram_vector_list);
    cout << "Saving Histograms..." << endl;
    save_histograms(histogram_vector_list, label);
}


void record_inputs() {
    //record_flavntuple("/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/manual_tests/track_test/flavntuple_htl.root", "hlt_test");
    record_flavntuple(_slurm_arrays+"slurm_20190601_hlt_ttbar_410470_step4_step4/merged_flavntuple.root", "hlt");
    record_flavntuple(_slurm_arrays+"slurm_20190601_ftk_ttbar_410470_step4_step4/merged_flavntuple.root", "ftk");
}
