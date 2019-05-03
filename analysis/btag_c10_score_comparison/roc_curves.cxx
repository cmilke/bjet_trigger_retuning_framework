#include "../util/titles.hh"


TGraph* generate_roc(string event, string label, string graph_title, int line_color, int line_width, int line_style) {
    TFile* bjet_file = new TFile( ("mv2c10_"+event+"_"+label+"_bjet_discriminants.root").c_str() );
    TFile* cjet_file = new TFile( ("mv2c10_"+event+"_"+label+"_cjet_discriminants.root").c_str() );
    TFile* ljet_file = new TFile( ("mv2c10_"+event+"_"+label+"_ljet_discriminants.root").c_str() );

    TH1D* bjet_discriminant_histogram = nullptr;
    TH1D* cjet_discriminant_histogram = nullptr;
    TH1D* ljet_discriminant_histogram = nullptr;
    bjet_file->GetObject("bjet_discriminant", bjet_discriminant_histogram);
    cjet_file->GetObject("cjet_discriminant", cjet_discriminant_histogram);
    ljet_file->GetObject("ljet_discriminant", ljet_discriminant_histogram);

    int num_bins = bjet_discriminant_histogram->GetNbinsX();
    Double_t* efficiency = new Double_t[num_bins];
    Double_t* rejection = new Double_t[num_bins];
    Double_t bjet_total = bjet_discriminant_histogram->Integral();
    Double_t ljet_total = ljet_discriminant_histogram->Integral();
    for (int bin = 1; bin <= num_bins; bin++) {
        Double_t bjets_accepted = bjet_discriminant_histogram->Integral(bin, num_bins);
        Double_t ljets_accepted = ljet_discriminant_histogram->Integral(bin, num_bins);
        if (ljets_accepted == 0) continue;
        efficiency[bin-1] = bjets_accepted / bjet_total;
        rejection[bin-1]  = 1.0 / (ljets_accepted / ljet_total);
    }

    TGraph* graph = new TGraph(num_bins, efficiency, rejection);
    graph->SetTitle( graph_title.c_str() );
    graph->SetLineColor(line_color);
    graph->SetFillColor(0);
    graph->SetLineWidth(line_width);
    graph->SetLineStyle(line_style);
    return graph;
}


void draw_roc(string event, const vector<TGraph*>& roc_vector) { 
    string cevent = get_event_title(event);

    double width = 1400;
    double height = 1000;
    float y_axis_offset = 1.5;
    TCanvas* canvas = new TCanvas("c1", "canvas", width, height);

    TMultiGraph* multigraph = new TMultiGraph( "mgraph", ("Online vs Offline ROC Curves for "
                                                           + cevent + " Events With "
                                                           "Jet p_{T} > 55 GeV and "
                                                           "|#eta| < 2.5").c_str() );
    for (TGraph* graph : roc_vector) {multigraph->Add(graph);}

    multigraph->Draw("A");
    multigraph->GetXaxis()->SetTitle("B-Jet Efficiency");
    multigraph->GetYaxis()->SetTitle("Light-Jet Rejection");
    multigraph->GetYaxis()->SetTitleOffset(y_axis_offset);
    multigraph->GetXaxis()->SetLimits(0.5,1.02);
    multigraph->SetMinimum(0.6);
    multigraph->SetMaximum(6E4);
    canvas->SetLogy();
    canvas->SetGrid();
    float xstart = 0.5;
    float xend = 0.9;
    float ystart = 0.6;
    float yend = 0.8;
    canvas->BuildLegend(xstart, ystart, xend, yend)->SetTextSize(0.03);
    canvas->SaveAs( ("performance_roc_"+event+".png").c_str() );
    delete(canvas);
}


void roc_curves(string event) {
    int line_width = 3;
    int solid_line = 1;
    int dot_dash_line = 4;
    int dashed_line = 9;

    vector<TGraph*> roc_vector;
    //roc_vector.push_back( generate_roc(event, "retune_ftkVtx_wrong", "t#bar{t} Retune w/ FTK-VTK Tracks Wrong", kMagenta, line_width, dashed_line) );
    //roc_vector.push_back( generate_roc(event, "retune_hlt_alt", "t#bar{t} Retune w/ HLT Tracks Alt", kGreen, line_width, dashed_line) );
    //roc_vector.push_back( generate_roc(event, "retune_ftkVtx_alt", "t#bar{t} Retune w/ FTK-VTK Tracks Alt", kBlue, line_width, dashed_line) );
    roc_vector.push_back( generate_roc(event, "retune_hlt", "t#bar{t} Retune w/ HLT Tracks", kBlack, line_width, solid_line) );
    roc_vector.push_back( generate_roc(event, "retune_ftkVtx", "t#bar{t} Retune w/ FTKVtx Tracks", kRed, line_width, solid_line) );
    roc_vector.push_back( generate_roc(event, "retune_hlt_gutted2", "t#bar{t} Retune w/ HLT Tracks-LI2", kBlue, line_width, dashed_line) );
    roc_vector.push_back( generate_roc(event, "retune_ftkVtx_gutted2", "t#bar{t} Retune w/ FTKVtx Tracks-LI2", kOrange, line_width, dashed_line) );
    //roc_vector.push_back( generate_roc(event, "retune_ftk", "t#bar{t} Retune w/ FTK IDTrig Tracks", kBlue, line_width, solid_line) );
    //roc_vector.push_back( generate_roc(event, "retune_ftkRefit", "t#bar{t} Retune w/ FTK-Refit Tracks", kGreen, line_width, solid_line) );
    //roc_vector.push_back( generate_roc(event, "retune_hlt_gutted", "t#bar{t} Retune w/ HLT Tracks, LI", kBlue, line_width, solid_line) );
    //roc_vector.push_back( generate_roc(event, "retune_ftkVtx_gutted", "t#bar{t} Retune w/ FTKVtx Tracks, LI", kOrange, line_width, solid_line) );

    draw_roc(event, roc_vector);
}
