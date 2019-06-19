#include "../util/titles.hh"


const int _num_plot_types = 6;
const int _num_jettypes = 1;

string _jet_titles[3] = { "B-Jets", "C-Jets", "Light-Jets"};

string _value_name[_num_plot_types] = {
    "numPixelHits",
    "numSCTHits",
    "numPixelDeadSensors",
    "numSCTDeadSensors",
    "numPixelHoles",
    "numSCTHoles"
};


string _param_titles[_num_plot_types] = {
    "numPixelHits",
    "numSCTHits",
    "numPixelDeadSensors",
    "numSCTDeadSensors",
    "numPixelHoles",
    "numSCTHoles"
};

string _param_units[_num_plot_types] = {
    "",
    "",
    "",
    "",
    "",
    ""
};

//1 is lowest; larger means courser binning
//i.e. 20 means 20 bins are averaged into 1
int _rebin_level[_num_plot_types] = {
    100,
    100,
    100,
    100,
    100,
    100
};

int _plot_ylog[_num_plot_types] = { 
    0, 
    0, 
    0, 
    0, 
    0, 
    0 };

float _plot_range[_num_plot_types][2] = {
/*numPixelHits*/           {0, 20},
/*numSCTHits*/             {0, 20},
/*numPixelDeadSensors*/    {0, 20},
/*numSCTDeadSensors*/      {0, 20},
/*numPixelHoles*/          {0, 20},
/*numSCTHoles*/            {0, 20}
};


vector< vector<TH1I*>* >* get_hists(string label, string title, int line_color, int line_width, int line_style) {
    TFile* extraction_file = new TFile( ("extracted_"+label+".root").c_str() );

    vector< vector<TH1I*>* >* histogram_vector_list = new vector< vector<TH1I*>* >();
    for (int jettype_index = 0; jettype_index < _num_jettypes; jettype_index++) {
        vector<TH1I*>* histogram_vector = new vector<TH1I*>();
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            TH1I* retrieved_hist;
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



void draw_histograms( vector< vector< vector<TH1I*>* >*  > hist_container ) {
    double width = 1400;
    double height = 1000;
    float axis_offset = 1.5;

    for (int jettype_index = 0; jettype_index < _num_jettypes; jettype_index++) {
        for (int plot_index = 0; plot_index < _num_plot_types; plot_index++) {
            TCanvas* canvas = new TCanvas("c1", "canvas", width, height);

            string label = _value_name[plot_index]+"_"+to_string(jettype_index);
            string title = _param_titles[plot_index];
            //uncomment below to split jettypes, and set _num_jettypes=3
            //title += " for " + _jet_titles[jettype_index];
            THStack* multihist = new THStack( label.c_str(), title.c_str() );
            for ( vector< vector<TH1I*>* >* hist_list : hist_container ) {
                TH1I* hist = hist_list->at(jettype_index)->at(plot_index);
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

    vector< vector< vector<TH1I*>* >*  > hist_container;
    //hist_container.push_back( get_hists("test", "TEST", kRed, 5, solid_line) );
    hist_container.push_back( get_hists("hlt", "HLT", kBlue, 5, solid_line) );
    hist_container.push_back( get_hists("ftk_idtrig", "FTK IDTrig", kRed, 5, solid_line) );
    hist_container.push_back( get_hists("ftkRefit_idtrig", "FTKRefit IDTrig", kOrange+1, 3, dashed_line) );

    draw_histograms(hist_container);
}
