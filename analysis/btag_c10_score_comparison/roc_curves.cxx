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

    vector<Double_t> bjet_efficiency;
    vector<Double_t> ljet_rejection;
    int num_bins = bjet_discriminant_histogram->GetNbinsX();
    Double_t bjet_total = bjet_discriminant_histogram->Integral();
    Double_t ljet_total = ljet_discriminant_histogram->Integral();
    for (int bin = 1; bin <= num_bins; bin++) {
        Double_t bjets_accepted = bjet_discriminant_histogram->Integral(bin, num_bins);
        Double_t ljets_accepted = ljet_discriminant_histogram->Integral(bin, num_bins);
        Double_t efficiency = bjets_accepted / bjet_total;
        if ( ljets_accepted == 0 ) continue;
        bjet_efficiency.push_back(efficiency);
        ljet_rejection.push_back(ljet_total / ljets_accepted);
    }

    int num_graph_points = bjet_efficiency.size();
    Double_t* graph_x = new Double_t[num_graph_points];
    Double_t* graph_y = new Double_t[num_graph_points];
    for (int bin = 0; bin < num_graph_points; bin++) {
        graph_x[bin] = bjet_efficiency[bin];
        graph_y[bin] = ljet_rejection[bin];
    }

    TGraph* graph = new TGraph(num_bins, graph_x, graph_y);
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

    TMultiGraph* multigraph = new TMultiGraph( "mgraph", ("MV2c10 ROC Curves for "
                                                           + cevent + " Events With "
                                                           "Jet p_{T} > 55 GeV and "
                                                           "|#eta| < 2.5").c_str() );
    for (TGraph* graph : roc_vector) {multigraph->Add(graph);}

    multigraph->Draw("AC");
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
    canvas->SaveAs( ("mv2c10_roc_"+event+".pdf").c_str() );
    delete(canvas);
}


void roc_curves(string event) {
    int line_width = 3;
    int solid_line = 1;
    int dot_dash_line = 4;
    int dashed_line = 9;

    vector<TGraph*> roc_vector;
    roc_vector.push_back( generate_roc(event, "retune_hlt", "Retuned HLT", kBlue, line_width, solid_line) );
    roc_vector.push_back( generate_roc(event, "retune_ftk_idtrig", "Retuned FTK-IDTrig", kRed, line_width, solid_line) );
    roc_vector.push_back( generate_roc(event, "retune_ftkRefit_idtrig", "Retuned FTKRefit-IDTrig", kOrange+1, line_width, dashed_line) );
    roc_vector.push_back( generate_roc(event, "defaultHLT", "TrigBTagCalibRUN12-08-14", kBlack, line_width, dashed_line) );

    draw_roc(event, roc_vector);
}
