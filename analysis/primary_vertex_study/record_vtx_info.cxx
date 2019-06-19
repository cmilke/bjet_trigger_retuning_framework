#include "../util/titles.hh"

const int _num_plot_types = 3;
const string _slurm_arrays = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/";

string _value_name[_num_plot_types] = { "x_pos", "y_pos", "z_pos" };

float _plot_range[_num_plot_types][2] = { {-10, 10}, {-10,10}, {-200, 200} };


void make_histograms(string label, vector<TH1F>& histogram_vector) {
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            float xmin = _plot_range[plot_index][0];
            float xmax = _plot_range[plot_index][1];
            int num_bins = 1e4;

            string name = label+"_"+_value_name[plot_index];
            TH1F new_hist( name.c_str(), name.c_str(), num_bins, xmin, xmax );
            histogram_vector.push_back(new_hist);
        }
}


void fill_histograms(TFile& data_file, vector<TH1F>& histogram_vector) {
    TTreeReader tree_reader("bTag_TriggerJets", &data_file);
    TTreeReaderValue< vector<float> > primVtx_vector_reader(tree_reader, "primary_vertex_location");

    while ( tree_reader.Next() ) {
        vector<float> primVtx_vector = *primVtx_vector_reader;
        if (primVtx_vector.size() == 0) continue;
        for (int plot_index=0; plot_index < _num_plot_types; plot_index++) {
            histogram_vector[plot_index].Fill( primVtx_vector[plot_index] );
        }
    }
}


void save_histograms(vector<TH1F>& histogram_vector, string label) {
    TFile root_file( ("extracted_"+label+".root").c_str(), "recreate");
    for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
        histogram_vector[plot_index].Write();
    }
}


void record_flavntuple( string flavntuple_name, string label) {
    cout << "Initializing histograms..." << endl;
    vector<TH1F> histogram_vector;
    make_histograms(label, histogram_vector);

    cout << "Reading " << flavntuple_name << "..." << endl;
    TFile flavntuple_file( flavntuple_name.c_str(), "read" );

    cout << "Filling Histograms..." << endl;
    fill_histograms(flavntuple_file, histogram_vector);

    cout << "Saving Histograms..." << endl;
    save_histograms(histogram_vector, label);
    cout << endl;
}


void record_vtx_info() {
    record_flavntuple(_slurm_arrays+"slurm_20190425_hlt_dRtest_ttbar_41000valid1_full_step2/merged_flavntuple.root", "offline");
    record_flavntuple(_slurm_arrays+"slurm_20190501_hlt_ttbar_41000valid1_full_step1/merged_flavntuple.root", "hlt");
    record_flavntuple(_slurm_arrays+"slurm_20190501_ftkVtx_ttbar_41000valid1_full_step1/merged_flavntuple.root", "ftkVtx");
    //record_flavntuple("/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/manual_tests/pv_test/flavntuple_htl.root", "test_hlt");
}
