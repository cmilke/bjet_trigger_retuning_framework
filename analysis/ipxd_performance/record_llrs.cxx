#include "../util/titles.hh"

using _mv2c10_type = double;
//using _mv2c10_type = float;

int _num_bins = 60;
float _pt_min_cutoff = 55*1000; //= 55 GeV
float _eta_min_cutoff = 2.5; //= 55 GeV


vector<TH1D*>* make_histograms(string event, string label, string ipx) {
    string label_title = get_level_title(label);
    string event_title = get_event_title(event);
 
    vector<TH1D*>* histogram_list = new vector<TH1D*>();
    int xmin = -20;
    int xmax =  40;
    string title_prefix = label_title+" IP"+ipx+"D Log Likelihood Ratio for "+event_title;
    histogram_list->push_back( new TH1D("bjet_llr", (title_prefix+" B-Jets").c_str(), _num_bins, xmin, xmax) );
    histogram_list->push_back( new TH1D("cjet_llr", (title_prefix+" C-Jets").c_str(), _num_bins, xmin, xmax) );
    histogram_list->push_back( new TH1D("ljet_llr", (title_prefix+" Light-Jets").c_str(), _num_bins, xmin, xmax) );

    return histogram_list;
}


void fill_histograms(TFile& data_file, vector<TH1D*>* histogram_list, string tree_name, string coneID_name, string ipx) {
    string ipxd_branch_name = "jet_ip"+ipx+"d_llr";
    TTreeReader tree_reader(tree_name.c_str(), &data_file);
    TTreeReaderValue< vector<float> > pt_reader(tree_reader, "Offjet_pt");
    TTreeReaderValue< vector<float> > eta_reader(tree_reader, "Offjet_Eta");
    TTreeReaderValue< vector<int> > coneID_vector_reader(tree_reader, coneID_name.c_str());
    TTreeReaderValue< vector<float> > ipxd_llr_vector_reader(tree_reader, ipxd_branch_name.c_str());

    int event_number = 0;
    while ( tree_reader.Next() ) {
        vector<float> pt_vector = *pt_reader;
        vector<float> eta_vector = *eta_reader;
        vector<int> coneID_vector = *coneID_vector_reader;
        auto ipxd_llr_vector = *ipxd_llr_vector_reader;
        for (int vector_index = 0; vector_index < coneID_vector.size(); vector_index++) {
            float pt = pt_vector[vector_index];
            float eta = eta_vector[vector_index];
            if (pt < _pt_min_cutoff or abs(eta) > _eta_min_cutoff) continue;
            int coneID = coneID_vector[vector_index];
            double ipxd_llr = ipxd_llr_vector[vector_index];

            switch (coneID) {
                case 5: histogram_list->at(0)->Fill(ipxd_llr); break;
                case 4: histogram_list->at(1)->Fill(ipxd_llr); break;
                default: histogram_list->at(2)->Fill(ipxd_llr); break;
            }
        }
        //if (event_number++ > 100) break;
    }
}


void save_and_delete_histograms(vector<TH1D*>* histogram_list, string event, string label, string ipx) {
    string filename_prefix = "ip"+ipx+"d_"+event+"_"+label;
    histogram_list->at(0)->SaveAs( (filename_prefix+"_bjet_llr.root").c_str() );
    histogram_list->at(1)->SaveAs( (filename_prefix+"_cjet_llr.root").c_str() );
    histogram_list->at(2)->SaveAs( (filename_prefix+"_ljet_llr.root").c_str() );

    delete histogram_list->at(0);
    delete histogram_list->at(1);
    delete histogram_list->at(2);
    delete histogram_list;
}


void record_flavntuple( string flavntuple_name, string event, string label, string ipx) {
    vector<TH1D*>* histogram_list = make_histograms(event, label, ipx);
    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    fill_histograms(flavntuple_file, histogram_list, "bTag_TriggerJets", "jet_truthflav", ipx);
    save_and_delete_histograms(histogram_list, event, label, ipx);
}


void record_ipxd_llr( string flavntuple_name, string event, string label) {
    record_flavntuple(flavntuple_name, event, label, "2");
    record_flavntuple(flavntuple_name, event, label, "3");
}


void record_llrs() {
    record_ipxd_llr(_slurm_arrays+"slurm_20190601_hlt_ttbar_410470_step23_step2/merged_flavntuple.root", "ttbar", "retune_hlt");
    record_ipxd_llr(_slurm_arrays+"slurm_20190613_ftk_IDTrig_ttbar_410470_step23_step2/merged_flavntuple.root", "ttbar", "retune_ftk_idtrig");
    record_ipxd_llr(_slurm_arrays+"slurm_20190613_ftkRefit_IDTrig_ttbar_410470_step23_step2/merged_flavntuple.root", "ttbar", "retune_ftkRefit_idtrig");
    record_ipxd_llr(_slurm_arrays+"slurm_20190601_defaultHLT_ttbar_410470_step1_step1/merged_flavntuple.root", "ttbar", "defaultHLT");



    //record_ipxd_llr(_archived_arrays+"slurm_20190420_ftk_ttbar_41000valid1_full_step2/merged_flavntuple.root", "ttbar", "retune_ftk");
}
