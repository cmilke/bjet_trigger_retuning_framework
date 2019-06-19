#include "../util/titles.hh"


void generate_plots(string event, string level) {
    string level_title = get_level_title(level);
    string event_title = get_event_title(event);

    TFile bjet_file( ("mv2c10_"+event+"_"+level+"_bjet_discriminants.root").c_str() );
    TFile cjet_file( ("mv2c10_"+event+"_"+level+"_cjet_discriminants.root").c_str() );
    TFile ljet_file( ("mv2c10_"+event+"_"+level+"_ljet_discriminants.root").c_str() );
    TH1D* bjet_discriminant_histogram;
    TH1D* cjet_discriminant_histogram;
    TH1D* ljet_discriminant_histogram;
    bjet_file.GetObject("bjet_discriminant", bjet_discriminant_histogram);
    cjet_file.GetObject("cjet_discriminant", cjet_discriminant_histogram);
    ljet_file.GetObject("ljet_discriminant", ljet_discriminant_histogram);

    //1 is lowest; larger means courser binning
    //i.e. 20 means 20 bins are averaged into 1
    int rebin_level = 10;
    bjet_discriminant_histogram->Rebin(rebin_level);
    cjet_discriminant_histogram->Rebin(rebin_level);
    ljet_discriminant_histogram->Rebin(rebin_level);

    THStack* overlaid_c10_discriminant = new THStack( "all_c10_discriminants", (level_title+" MV2c10 Discriminants for "+event_title+" Events (Stacked)").c_str() );
    overlaid_c10_discriminant->Add(ljet_discriminant_histogram);
    overlaid_c10_discriminant->Add(cjet_discriminant_histogram);
    overlaid_c10_discriminant->Add(bjet_discriminant_histogram);


    //Pretty everything up
    double width = 1400;
    double height = 1000;
    TCanvas* canvas = new TCanvas("c1", "canvas", width, height);
    bjet_discriminant_histogram->SetLineColor(kBlue);
    cjet_discriminant_histogram->SetLineColor(kGreen);
    ljet_discriminant_histogram->SetLineColor(kRed);

    int histogram_line_width = 3;
    int histogram_line_style = (level == "offline") ? 1 : 9;
    float y_axis_offset = 1.5;

    bjet_discriminant_histogram->SetLineWidth(histogram_line_width);
    cjet_discriminant_histogram->SetLineWidth(histogram_line_width);
    ljet_discriminant_histogram->SetLineWidth(histogram_line_width);
    bjet_discriminant_histogram->SetLineStyle(histogram_line_style);
    cjet_discriminant_histogram->SetLineStyle(histogram_line_style);
    ljet_discriminant_histogram->SetLineStyle(histogram_line_style);

    gStyle->SetStatX(0.5);
    gStyle->SetStatY(0.8);

    bjet_discriminant_histogram->Draw("hist");
    bjet_discriminant_histogram->GetXaxis()->SetTitle("MV2c10 Discriminant");
    bjet_discriminant_histogram->GetYaxis()->SetTitle("Frequency Discriminant is Assigned by Tagger");
    bjet_discriminant_histogram->GetXaxis()->CenterTitle();
    bjet_discriminant_histogram->GetYaxis()->CenterTitle();
    bjet_discriminant_histogram->GetYaxis()->SetTitleOffset(y_axis_offset);
    canvas->SaveAs( ("mv2c10_"+event+"_"+level+"_bjet_discriminants.png").c_str() );

    cjet_discriminant_histogram->Draw("hist");
    cjet_discriminant_histogram->GetXaxis()->SetTitle("MV2c10 Discriminant");
    cjet_discriminant_histogram->GetYaxis()->SetTitle("Frequency Discriminant is Assigned by Tagger");
    cjet_discriminant_histogram->GetXaxis()->CenterTitle();
    cjet_discriminant_histogram->GetYaxis()->CenterTitle();
    cjet_discriminant_histogram->GetYaxis()->SetTitleOffset(y_axis_offset);
    canvas->SaveAs( ("mv2c10_"+event+"_"+level+"_cjet_discriminants.png").c_str() );

    ljet_discriminant_histogram->Draw("hist");
    ljet_discriminant_histogram->GetXaxis()->SetTitle("MV2c10 Discriminant");
    ljet_discriminant_histogram->GetYaxis()->SetTitle("Frequency Discriminant is Assigned by Tagger");
    ljet_discriminant_histogram->GetXaxis()->CenterTitle();
    ljet_discriminant_histogram->GetYaxis()->CenterTitle();
    ljet_discriminant_histogram->GetYaxis()->SetTitleOffset(y_axis_offset);
    canvas->SaveAs( ("mv2c10_"+event+"_"+level+"_ljet_discriminants.png").c_str() );
    
    
    overlaid_c10_discriminant->Draw("hist");
    canvas->SetLogy();
    overlaid_c10_discriminant->SetMinimum(1E2);
    overlaid_c10_discriminant->SetMaximum(1E7);

    bjet_discriminant_histogram->SetTitle("B-Jets");
    cjet_discriminant_histogram->SetTitle("C-Jets");
    ljet_discriminant_histogram->SetTitle("Light-Jets");
    overlaid_c10_discriminant->GetXaxis()->SetTitle("Mv2c10 Discriminant");
    overlaid_c10_discriminant->GetYaxis()->SetTitle("Frequency Discriminant is Assigned by Tagger");
    overlaid_c10_discriminant->GetXaxis()->CenterTitle();
    overlaid_c10_discriminant->GetYaxis()->CenterTitle();
    overlaid_c10_discriminant->GetYaxis()->SetTitleOffset(y_axis_offset);
    canvas->BuildLegend(0.5, 0.65, 0.7, 0.85);
    canvas->SaveAs( ("mv2c10_"+event+"_"+level+"_all_discriminants_stack_log.png").c_str() );
    
    //Normalize the plots with respect to THEIR entries
    //(not the global number of entries)
    canvas->SetLogy(0);
    bjet_discriminant_histogram->Scale( 1.0 / bjet_discriminant_histogram->Integral() );
    cjet_discriminant_histogram->Scale( 1.0 / cjet_discriminant_histogram->Integral() );
    ljet_discriminant_histogram->Scale( 1.0 / ljet_discriminant_histogram->Integral() );

    overlaid_c10_discriminant->SetTitle( (level_title+" MV2c10 Discriminants for "+event_title+" Events").c_str() );
    overlaid_c10_discriminant->Draw("nostack hist");
    overlaid_c10_discriminant->SetMinimum(0);
    overlaid_c10_discriminant->SetMaximum(0.7);

    canvas->BuildLegend(0.3, 0.65, 0.5, 0.85);
    canvas->SaveAs( ("mv2c10_"+event+"_"+level+"_all_discriminants.png").c_str() );
}
