#include "../util/titles.hh"


const int _num_plot_types = 25;

string _jet_titles[3] = { "B-Jets", "C-Jets", "Light-Jets"};

string _value_name[_num_plot_types] = {
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
    "jet_jf_ntrkAtVx",
    "jet_sv1_ntrkv",
    "jet_sv1_n2t",
    "jet_jf_n2t",
    "jet_jf_nvtx",
    "jet_jf_nvtx1t"
};

//string _param_titles[_num_plot_types] = {
//     "Pt",
//     "d0", "d0 Error", "d0 Significance",
//     "z0", "z0 Error", "z0 Significance",
//     "#phi 0", "#phi 0 Error", "#phi 0 Significance",
//     "#theta", "#theta Error", "#theta Significance",
//     "q/P", "q/P Error", "q/P Significance"
//};

//string _param_units[_num_plot_types] = {
//     "(MeV)",
//     "(?)", "(?)", "",
//     "(?)", "(?)", "",
//     "(radians)", "(radians)", "",
//     "(radians)", "(radians)", "",
//     "(C/MeV)", "(C/MeV)", ""
//};

//1 is lowest; larger means courser binning
//i.e. 20 means 20 bins are averaged into 1
int _rebin_level[_num_plot_types] = {
     1000,   //jet_pt
     10000,   //jet_eta
     1000,   //jet_ip2d_pb
     1000,   //jet_ip2d_pc
     1000,   //jet_ip2d_pu
     1000,   //jet_ip3d_pb
     1000,   //jet_ip3d_pc
     1000,   //jet_ip3d_pu
     10000,   //jet_sv1_m
     1000,   //jet_sv1_efc
     1000,   //jet_sv1_Lxy
     1000,   //jet_sv1_L3d
     10000,   //jet_sv1_sig3d
     1000,   //jet_sv1_dR
     10000,   //jet_jf_m
     1000,   //jet_jf_efc
     100,   //jet_jf_deta
     10,   //jet_jf_dphi
     10000,   //jet_jf_sig3d
     10000,   //jet_jf_ntrkAtVx //start ints...
     100,   //jet_sv1_ntrkv
     100,   //jet_sv1_n2t
     100,   //jet_jf_n2t
     100,   //jet_jf_nvtx
     100    //jet_jf_nvtx1t
};



int _plot_ylog[_num_plot_types] = {
     1,   //jet_pt
     0,   //jet_eta
     1,   //jet_ip2d_pb
     1,   //jet_ip2d_pc
     1,   //jet_ip2d_pu
     1,   //jet_ip3d_pb
     1,   //jet_ip3d_pc
     1,   //jet_ip3d_pu
     1,   //jet_sv1_m
     1,   //jet_sv1_efc
     1,   //jet_sv1_Lxy
     1,   //jet_sv1_L3d
     1,   //jet_sv1_sig3d
     1,   //jet_sv1_dR
     1,   //jet_jf_m
     1,   //jet_jf_efc
     0,   //jet_jf_deta
     0,   //jet_jf_dphi
     1,   //jet_jf_sig3d
     1,   //jet_jf_ntrkAtVx //start int
     1,   //jet_sv1_ntrkv
     1,   //jet_sv1_n2t
     1,   //jet_jf_n2t
     1,   //jet_jf_nvtx
     1    //jet_jf_nvtx1t
};


vector< vector<float> > _plot_range_list_array[_num_plot_types] = {
/*jet_pt*/          { {0, 1e6} },
/*jet_eta*/         { {-4, 4} },
/*jet_ip2d_pb*/     { {0, 1.1} },
/*jet_ip2d_pc*/     { {0, 1.1} },
/*jet_ip2d_pu*/     { {0, 1.1} },
/*jet_ip3d_pb*/     { {0, 1.1} },
/*jet_ip3d_pc*/     { {0, 1.1} },
/*jet_ip3d_pu*/     { {0, 1.1} },
/*jet_sv1_m*/       { {0, 6.2e3} },
/*jet_sv1_efc*/     { {-1, 1.1} },
/*jet_sv1_Lxy*/     { {0, 150} },
/*jet_sv1_L3d*/     { {0, 200} },
/*jet_sv1_sig3d*/   { {0, 500} },
/*jet_sv1_dR*/      { {0, 6} },
/*jet_jf_m*/        { {0, 1.1e4} },
/*jet_jf_efc*/      { {0, 1.1} },
/*jet_jf_deta*/     { {-11, 1}, {-10.5, -9.5}, {-0.5, 0.5} },
/*jet_jf_dphi*/     { {-11, 2}, {-10.5, -9.5}, {-0.5, 0.5} },
/*jet_jf_sig3d*/    { {0, 100} },
/*jet_jf_ntrkAtVx*/ { {0, 20} },
/*jet_sv1_ntrkv*/   { {-5, 17} },
/*jet_sv1_n2t*/     { {0, 70} },
/*jet_jf_n2t*/      { {0, 100} },
/*jet_jf_nvtx*/     { {0, 5} },
/*jet_jf_nvtx1t*/   { {0, 5} }
};


vector< vector<TH1*>* >* get_hists(string label, string title, int line_color, int line_width, int line_style) {
    TFile* extraction_file = new TFile( ("extracted_"+label+".root").c_str() );

    vector< vector<TH1*>* >* histogram_vector_list = new vector< vector<TH1*>* >();
    for (int jettype_index = 0; jettype_index < 3; jettype_index++) {
        vector<TH1*>* histogram_vector = new vector<TH1*>();
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            TH1* retrieved_hist;
            string name = label+"_"+_value_name[plot_index]+"_"+to_string(jettype_index);
            extraction_file->GetObject(name.c_str(), retrieved_hist);
            retrieved_hist->Rebin( _rebin_level[plot_index] );
            retrieved_hist->SetTitle( title.c_str() );
            retrieved_hist->SetLineColor(line_color);
            retrieved_hist->SetFillColor(0);
            retrieved_hist->SetLineWidth(line_width);
            retrieved_hist->SetLineStyle(line_style);

            histogram_vector->push_back(retrieved_hist);
        }
        histogram_vector_list->push_back(histogram_vector);
    }

    return histogram_vector_list;
}



void draw_histograms( vector< vector< vector<TH1*>* >*  > hist_container ) {
    double width = 1400;
    double height = 1000;
    float axis_offset = 1.25;

    for (int jettype_index = 0; jettype_index < 3; jettype_index++) {
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            TCanvas* canvas = new TCanvas("c1", "canvas", width, height);

            string label = _value_name[plot_index]+"_"+to_string(jettype_index);
            //string title = _param_titles[plot_index] + " for " + _jet_titles[jettype_index];
            string title = _value_name[plot_index] + " for " + _jet_titles[jettype_index];
            THStack* multihist = new THStack( label.c_str(), title.c_str() );
            for ( vector< vector<TH1*>* >* hist_list : hist_container ) {
                TH1* hist = hist_list->at(jettype_index)->at(plot_index);
                multihist->Add(hist);
            }
            multihist->Draw("nostack hist");
            canvas->SetLogy(_plot_ylog[plot_index]);
            canvas->SetGrid();
            float xstart = 0.80;
            float ystart = 0.9;
            float xsize = 0.15;
            float ysize = 0.1;
            canvas->BuildLegend(xstart, ystart, xstart+xsize, ystart+ysize)->SetTextSize(0.03);

            gStyle->SetTitleAlign(13);
            gStyle->SetTitleX(0.0);
            string axis_title = _value_name[plot_index];
            //string axis_title = _param_titles[plot_index] + _param_units[plot_index];
            multihist->GetXaxis()->SetTitle( axis_title.c_str() );
            multihist->GetXaxis()->SetTitleOffset(axis_offset);

            int range_suffix = 0;
            for ( vector<float> plot_range : _plot_range_list_array[plot_index] ) {
                multihist->GetXaxis()->SetRangeUser(plot_range[0], plot_range[1]);
                canvas->SaveAs( ("image_"+label+"-"+to_string(range_suffix++)+".png").c_str() );
            }

            delete(canvas);
        }
    }
}


void draw_inputs() {
    int line_width = 4;
    int solid_line = 1;
    int dot_dash_line = 4;
    int dashed_line = 9;

    //int online_official_color = kBlue;

    vector< vector< vector<TH1*>* >*  > hist_container;
    hist_container.push_back( get_hists("hlt", "HLT", kBlack, 7, solid_line) );
    hist_container.push_back( get_hists("ftkVtx", "FTK-HLT", kRed, 4, dashed_line) );
    //hist_container.push_back( get_hists("ftk", "FTK IDTrig", kBlue, 7, solid_line) );
    //hist_container.push_back( get_hists("ftkRefit", "FTK Refit", kGreen, 4, dashed_line) );

    draw_histograms(hist_container);
}
