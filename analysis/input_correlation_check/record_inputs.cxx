#include "../util/titles.hh"

const int _num_float_types = 20;
const int _num_int_types = 5;
const string _slurm_arrays = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/";

string _float_value_name[_num_float_types] = {
/*1*/    "jet_pt",
/*2*/    "jet_eta",
/*3*/    "jet_ip2d_pb",
/*4*/    "jet_ip2d_pc",
/*5*/    "jet_ip2d_pu",
/*6*/    "jet_ip3d_pb",
/*7*/    "jet_ip3d_pc",
/*8*/    "jet_ip3d_pu",
/*9*/    "jet_sv1_m",
/*10*/    "jet_sv1_efc",
/*11*/    "jet_sv1_Lxy",
/*12*/    "jet_sv1_L3d",
/*13*/    "jet_sv1_sig3d",
/*14*/    "jet_sv1_dR",
/*15*/    "jet_jf_m",
/*16*/    "jet_jf_efc",
/*17*/    "jet_jf_deta",
/*18*/    "jet_jf_dphi",
/*19*/    "jet_jf_sig3d",
/*20*/    "jet_jf_ntrkAtVx"
};


string _int_value_name[_num_int_types] = {
/*1*/    "jet_sv1_ntrkv",
/*2*/    "jet_sv1_n2t",
/*3*/    "jet_jf_n2t",
/*4*/    "jet_jf_nvtx",
/*5*/    "jet_jf_nvtx1t"
};

float _float_range[_num_float_types][2] = {
    {0, 1e6},         //jet_pt
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
    {-10, 20},         //jet_sv1_ntrkv
    {-100, 100},      //jet_sv1_n2t
    {0, 100},         //jet_jf_n2t
    {0, 100},       //jet_jf_nvtx
    {0, 100}          //jet_jf_nvtx1t
};


void record_flavntuple( string flavntuple_name, string label) {
    int value1_index = 0; //pt
    int value2_index = 0; //sv1_ntrkv ... for int array
    TH2F pt_vs_sv1ntrk("pt_vs_sv1ntrk","Correlation Between #P_t and SV1_ntrkv", 
            1e3, _float_range[value1_index][0], _float_range[value1_index][1], 
            1e3, _int_range[value2_index][0], _int_range[value2_index][1]);

    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    TTreeReader tree_reader("bTag_TriggerJets", &flavntuple_file);
    TTreeReaderValue< vector<float> > value1_vector_reader( tree_reader, _float_value_name[value1_index].c_str() );
    TTreeReaderValue< vector<int> > value2_vector_reader( tree_reader, _int_value_name[value2_index].c_str() );
    while ( tree_reader.Next() ) {
        vector<float> value1_vector = *value1_vector_reader;
        vector<int> value2_vector = *value2_vector_reader;
        for (int jet_index = 0; jet_index < value1_vector.size(); jet_index++) {
            double value1 = value1_vector[jet_index];
            double value2 = (float) value2_vector[jet_index];
            pt_vs_sv1ntrk.Fill(value1, value2);
        }
    }

    //save th2d
    TFile root_file( ("extracted_"+label+".root").c_str(), "recreate");
    pt_vs_sv1ntrk.Write();
}


void record_inputs() {
    //record_flavntuple("/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/manual_tests/track_test/flavntuple_htl.root", "hlt_test");
    record_flavntuple(_slurm_arrays+"slurm_20190420_hlt_ttbar_41000valid1_full_step2/merged_flavntuple.root", "hlt");
    record_flavntuple(_slurm_arrays+"slurm_20190420_ftkVtx_ttbar_41000valid1_full_step2/merged_flavntuple.root", "ftkVtx");
    //record_flavntuple(_slurm_arrays+"slurm_20190420_ftk_ttbar_41000valid1_full_step2/merged_flavntuple.root", "ftk");
    //record_flavntuple(_slurm_arrays+"slurm_20190420_ftkRefit_ttbar_41000valid1_full_step2/merged_flavntuple.root", "ftkRefit");
}
