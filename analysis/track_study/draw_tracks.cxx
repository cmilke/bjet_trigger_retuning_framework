#include "../util/titles.hh"


const int _num_plot_types = 17;

string _jet_titles[3] = { "B-Jets", "C-Jets", "Light-Jets"};

string _value_name[_num_plot_types] = {
     "pt",
     "d0", "d0_err", "d0_sig",
     "z0", "z0_err", "z0_sig",
     "phi0", "phi0_err", "phi0_sig",
     "theta", "theta_err", "theta_sig",
     "qOverP", "qOverP_err", "qOverP_sig",
     "eta"
};


string _param_titles[_num_plot_types] = {
     "Pt",
     "d0", "d0 Error", "d0 Significance",
     "z0", "z0 Error", "z0 Significance",
     "#phi 0", "#phi 0 Error", "#phi 0 Significance",
     "#theta", "#theta Error", "#theta Significance",
     "q/P", "q/P Error", "q/P Significance",
     "#eta"
};

string _param_units[_num_plot_types] = {
     "(MeV)",
     "(mm)", "(mm)", "",
     "(mm)", "(mm)", "",
     "(radians)", "(radians)", "",
     "(radians)", "(radians)", "",
     "(C/MeV)", "(C/MeV)", "",
     ""
};

//1 is lowest; larger means courser binning
//i.e. 20 means 20 bins are averaged into 1
int _rebin_level[_num_plot_types] = {
     1000,
     200, 100, 100,
     10000, 100, 1000,
     10000, 1000, 1000,
     10000, 1000, 100,
     1000, 1000, 1000,
     10000
};

int _plot_ylog[_num_plot_types] = {
     0,
     1, 1, 1,
     0, 0, 0,
     0, 0, 0,
     0, 0, 0,
     0, 0, 0,
     0
};

float _plot_range[_num_plot_types][2] = {
     {0, 1e4},                              //pt
     {-5, 5}, {0, 0.3}, {-20, 20},    //d0
     {-100,100}, {0, 1}, {-1e3, 1e3},     //z0
     {-M_PI, M_PI}, {0, 0.01}, {-5e3, 5e3},  //phi0
     {0, M_PI}, {0, 5e-3}, {0, 5e3},         //theta
     {-1e-3, 1e-3}, {0, 1e-4}, {-1e2, 1e2},  //qOverP
     {-3, 3}                              //eta
};


vector< vector<TH1F*>* >* get_hists(string label, string title, int line_color, int line_width, int line_style) {
    TFile* extraction_file = new TFile( ("extracted_"+label+".root").c_str() );

    vector< vector<TH1F*>* >* histogram_vector_list = new vector< vector<TH1F*>* >();
    for (int jettype_index = 0; jettype_index < 3; jettype_index++) {
        vector<TH1F*>* histogram_vector = new vector<TH1F*>();
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            TH1F* retrieved_hist;
            string name = label+"_"+_value_name[plot_index]+"_"+to_string(jettype_index);
            extraction_file->GetObject(name.c_str(), retrieved_hist);
            retrieved_hist->Rebin( _rebin_level[plot_index] );
            retrieved_hist->SetTitle( title.c_str() );
            retrieved_hist->SetLineColor(line_color);
            retrieved_hist->SetFillColor(0);
            retrieved_hist->SetLineWidth(line_width);
            retrieved_hist->SetLineStyle(line_style);
            //Uncomment below line to scale each plot to 1
            retrieved_hist->Scale( 1.0 / retrieved_hist->Integral() );

            histogram_vector->push_back(retrieved_hist);
        }
        histogram_vector_list->push_back(histogram_vector);
    }

    return histogram_vector_list;
}



void draw_histograms( vector< vector< vector<TH1F*>* >*  > hist_container ) {
    double width = 1400;
    double height = 1000;
    float axis_offset = 1.5;

    for (int jettype_index = 0; jettype_index < 3; jettype_index++) {
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            TCanvas* canvas = new TCanvas("c1", "canvas", width, height);

            string label = _value_name[plot_index]+"_"+to_string(jettype_index);
            string title = _param_titles[plot_index] + " for " + _jet_titles[jettype_index];
            THStack* multihist = new THStack( label.c_str(), title.c_str() );
            for ( vector< vector<TH1F*>* >* hist_list : hist_container ) {
                TH1F* hist = hist_list->at(jettype_index)->at(plot_index);
                multihist->Add(hist);
            }


            multihist->Draw("nostack hist");
            string axis_title = _param_titles[plot_index] + _param_units[plot_index];
            multihist->GetXaxis()->SetTitle( axis_title.c_str() );
            multihist->GetXaxis()->SetTitleOffset(axis_offset);
            multihist->GetXaxis()->SetRangeUser(_plot_range[plot_index][0], _plot_range[plot_index][1]);
            canvas->SetLogy(_plot_ylog[plot_index]);
            canvas->SetGrid();
            float xstart = 0.70;
            float xend = 0.90;
            float ystart = 0.65;
            float yend = 0.85;
            canvas->BuildLegend(xstart, ystart, xend, yend)->SetTextSize(0.03);
            canvas->SaveAs( ("plot_"+label+".pdf").c_str() );
            delete(canvas);
        }
    }
}


void draw_tracks() {
    int line_width = 4;
    int solid_line = 1;
    int dot_dash_line = 4;
    int dashed_line = 9;

    //int online_official_color = kBlue;

    vector< vector< vector<TH1F*>* >*  > hist_container;
    hist_container.push_back( get_hists("hlt", "HLT", kBlue, 5, solid_line) );
    //hist_container.push_back( get_hists("ftkVtx", "FTK-Vtx", kRed, 3, dashed_line) );
    hist_container.push_back( get_hists("ftk_idtrig", "FTK IDTrig", kRed, 5, solid_line) );
    hist_container.push_back( get_hists("ftkRefit_idtrig", "FTKRefit IDTrig", kOrange+1, 3, dashed_line) );
    //hist_container.push_back( get_hists("ftk", "FTK", kBlue, line_width, solid_line) );
    //hist_container.push_back( get_hists("ftkRefit", "FTK-Refit", kCyan, line_width, solid_line) );

    draw_histograms(hist_container);
}
