#include "../util/titles.hh"


TGraph* generate_roc(string event, string level, string graph_title,
            int line_color, int line_width, int line_style) {
    TFile* bjet_file = new TFile( ("mv2c10_"+event+"_"+level+"_bjet_discriminants.root").c_str() );
    TFile* cjet_file = new TFile( ("mv2c10_"+event+"_"+level+"_cjet_discriminants.root").c_str() );
    TFile* ljet_file = new TFile( ("mv2c10_"+event+"_"+level+"_ljet_discriminants.root").c_str() );

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

    multigraph->Draw("AC");
    multigraph->GetXaxis()->SetTitle("B-Jet Efficiency");
    multigraph->GetYaxis()->SetTitle("Light-Jet Rejection");
    multigraph->GetYaxis()->SetTitleOffset(y_axis_offset);
    multigraph->GetXaxis()->SetLimits(0.38,1.02);
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

    //int online_official_color = kBlue;


    vector<TGraph*> roc_vector {
        generate_roc(event, "offline",                        "MV2c10 Offline",                    kBlack,    line_width, solid_line),
        //generate_roc(event, "online_official_tune",           "Online Official Tune RUN12-08-14",  kRed,      line_width, solid_line),

        //generate_roc(event, "online_hybrid_retune_med_test",  "My Hybrid Tune, 200K New Events",   kCyan,     line_width, solid_line),
        //generate_roc(event, "online_hybrid_retune_large",     "My Hybrid Tune, 90-10 Split",       kMagenta,  line_width, solid_line),
        //generate_roc(event, "online_hybrid_retune_full",      "My Hybrid Tune, 5M Same Events",    kGreen,    line_width, solid_line)
        //generate_roc(event, "online_hybrid_retune", "My Online Hybrid Retune",           kGreen,   line_width, solid_line),
        //generate_roc(event, "online_hybrid_retune_alt", "My Online Hybrid Retune (alt)"  kGreen+4, line_width, solid_line),
        generate_roc(event, "online_retune_med", "My Online t#bar{t} Retune",            kBlue,    line_width, solid_line),
        //generate_roc(event, "online_retune_med_alt", "My Online t#bar{t} Retune (alt)",      kCyan,    line_width, solid_line),
        //generate_roc(event, "online_retune_large", "My Online t#bar{t} Retune (large)",  kMagenta, line_width, solid_line)

        //generate_roc(event, "online_ttbar_retune_1234",   "My Online t#bar{t} Retune, 1-4 500K",     kBlue,    line_width, solid_line),
        //generate_roc(event, "online_ttbar_retune_1234_med",   "My Online t#bar{t} Retune, 1-4 200K", kMagenta, line_width, solid_line),
        //generate_roc(event, "online_ttbar_retune_123_4",  "My Online t#bar{t} Retune, 1-3,4 500K",   kCyan,    line_width, solid_line),
        //generate_roc(event, "online_ttbar_retune_1_23_4", "My Online t#bar{t} Retune, 1,2-3,4 500K", kGreen,    line_width, solid_line)
    };

    draw_roc(event, roc_vector);
}
