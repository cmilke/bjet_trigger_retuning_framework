int _rebin_level = 1;

TH1F* get_histogram(string label, string histogram_title,
            int line_color, int line_width, int line_style) {
    TFile* file = new TFile( (label+".root").c_str() );
    TH1F* histogram;
    file->GetObject(label.c_str(), histogram);

    histogram->SetTitle( histogram_title.c_str() );
    histogram->SetLineColor(line_color);
    histogram->SetFillColor(0);
    histogram->SetLineWidth(line_width);
    histogram->SetLineStyle(line_style);
    histogram->Rebin(_rebin_level);

    return histogram;
}

void draw_histogram(const vector<TH1F*>& hist_vector) { 
    THStack* overlaid_pt_histograms = new THStack( "pt_histograms", "Pt Distribution for Various Online Trigger Reconstructed Tracks");
    for (TH1F* hist : hist_vector) {overlaid_pt_histograms->Add(hist);}

    //Pretty everything up
    double width = 1400;
    double height = 1000;
    TCanvas* canvas = new TCanvas("c1", "canvas", width, height);
    float y_axis_offset = 1.5;

    //canvas->SetLogy();
    canvas->SetGrid();
    overlaid_pt_histograms->Draw("nostack hist");
    overlaid_pt_histograms->GetXaxis()->SetLimits(0, 200);
    overlaid_pt_histograms->GetXaxis()->SetTitle("Jet Pt (GeV)");
    overlaid_pt_histograms->GetXaxis()->CenterTitle();
    overlaid_pt_histograms->GetYaxis()->SetTitleOffset(y_axis_offset);
    canvas->BuildLegend(0.5, 0.65, 0.7, 0.85);
    canvas->SaveAs("pt_spectrum.png");
}

void generate_plots() {
    int line_width = 3;
    int solid_line = 1;
    int dot_dash_line = 4;
    int dashed_line = 9;

    vector<TH1F*> hist_vector {
        get_histogram("hlt_tracks", "HLT Tracks", kRed, line_width, solid_line),
        get_histogram("ftk_tracks", "FTK Tracks", kBlue, line_width, dashed_line),
        get_histogram("ftkRefit_tracks", "FTK-Refit Tracks", kCyan, line_width, dashed_line)
    };

    draw_histogram(hist_vector);
}
