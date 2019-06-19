#include "../util/titles.hh"


const int _num_plot_types = 3;

string _value_name[_num_plot_types] = { "x_pos", "y_pos", "z_pos" };
string _param_titles[_num_plot_types] = { "X Position" , "Y Position", "Z Position" };

//1 is lowest; larger means courser binning
//i.e. 20 means 20 bins are averaged into 1
int _rebin_level[_num_plot_types] = {1,1,100};
int _plot_ylog[_num_plot_types] = {0,0,1};

float _plot_range[_num_plot_types][2] = { {-0.55, -0.45}, {-0.55,-0.45}, {-200, 200} };


vector<TH1F*>* get_hists(string label, string title, int line_color, int line_width, int line_style) {
    TFile* extraction_file = new TFile( ("extracted_"+label+".root").c_str() );

    vector<TH1F*>* histogram_vector = new vector<TH1F*>();
    for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
        TH1F* retrieved_hist;
        string name = label+"_"+_value_name[plot_index];
        extraction_file->GetObject(name.c_str(), retrieved_hist);
        retrieved_hist->Rebin( _rebin_level[plot_index] );
        retrieved_hist->SetTitle( title.c_str() );
        retrieved_hist->SetLineColor(line_color);
        retrieved_hist->SetFillColor(0);
        retrieved_hist->SetLineWidth(line_width);
        retrieved_hist->SetLineStyle(line_style);

        histogram_vector->push_back(retrieved_hist);
    }

    return histogram_vector;
}



void draw_histograms( vector< vector<TH1F*>* >& hist_container ) {
    double width = 1400;
    double height = 1000;
    float axis_offset = 1.5;

    for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
        gStyle->SetTitleAlign(13);
        gStyle->SetTitleX(0.0);
        TCanvas* canvas = new TCanvas("c1", "canvas", width, height);

        string label = _value_name[plot_index];
        string title = _param_titles[plot_index] + " of Primary Vertices Across Events";
        THStack* multihist = new THStack( label.c_str(), title.c_str() );
        for ( vector<TH1F*>* hist_list : hist_container ) {
            TH1F* hist = hist_list->at(plot_index);
            multihist->Add(hist);
        }


        multihist->Draw("nostack hist");
        multihist->GetXaxis()->SetTitle( "Position(mm)" );
        multihist->GetXaxis()->SetTitleOffset(axis_offset);
        multihist->GetXaxis()->SetRangeUser(_plot_range[plot_index][0], _plot_range[plot_index][1]);
        canvas->SetLogy(_plot_ylog[plot_index]);
        canvas->SetGrid();
        float xstart = 0.80;
        float ystart = 0.9;
        float xsize = 0.15;
        float ysize = 0.1;
        canvas->BuildLegend(xstart, ystart, xstart+xsize, ystart+ysize)->SetTextSize(0.03);
        canvas->SaveAs( ("image_"+label+".png").c_str() );
        delete(canvas);
    }
}


void draw_vtx_pos() {
    int line_width = 4;
    int solid_line = 1;
    int dot_dash_line = 4;
    int dashed_line = 9;

    //int online_official_color = kBlue;

    vector< vector<TH1F*>* > hist_container;
    hist_container.push_back( get_hists("offline", "Offline", kBlack, 5, solid_line) );
    hist_container.push_back( get_hists("hlt", "HLT", kBlue, 5, solid_line) );
    hist_container.push_back( get_hists("ftkVtx", "FTK-Vtx", kRed, 3, dashed_line) );

    draw_histograms(hist_container);
}
