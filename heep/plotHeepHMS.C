void plotHeepHMS(){

  //read the input file
  //TFile *f = new TFile(Form("mkROOTfiles/hms_replay_matrixopt_%i_-1.root",nrun));
  //TFile *f = new TFile("myROOTfiles/data_heep_low.root");
  TFile *f = new TFile("/home/cdaq/holly/hallc_replay_kaonlt/ROOTfiles/hms_coin_replay_production_all_6610_500000.root");

  TTree *tt = (TTree*)f->Get("T");

  TFile *f1 = new TFile("heep_simc/h1_hms_30_2p478.root");
  TTree *ts = (TTree*)f1->Get("h666");

  int nentries = ts->GetEntries();

  //here's the cut
  TCut cut = "H.gtr.dp<8&&H.gtr.dp>-8&&H.cal.etracknorm>0.8&&H.cer.npeSum>2&&H.kin.W>0.8&&H.kin.W<1.1";

  //make the output file
  TCanvas *canvas = new TCanvas("canvas","plots",800,800);
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetBorderSize(0);
  canvas->SetFrameFillColor(0);
  canvas->SetFrameBorderMode(0);
  std::string pdf_file_name= Form("output_heep/output_heep_hms_30_2p478.pdf");
  gROOT->SetBatch(true);
  gStyle->SetOptStat(0);
  canvas->SetGridx();
  canvas->SetGridy();
  TFile *fout = new TFile("output_heep/output_heep_hms_30_2p478.root","RECREATE");


  //make plots
  //data
  TH1F *h_delta = new TH1F("h_delta","HMS delta",100,-12,12);
  TH1F *h_xptar = new TH1F("h_xptar","HMS xptar",100,-0.1,0.1);
  TH1F *h_yptar = new TH1F("h_yptar","HMS yptar",100,-0.06,0.06);
  TH1F *h_ytar = new TH1F("h_ytar","HMS ytar",100,-12,12);
  TH1F *h_W = new TH1F("h_W", "W [GeV]",100,0.8,1.3);

  //simc
  TH1F *h_simc_delta = new TH1F("h_simc_delta","HMS delta",100,-12,12);
  TH1F *h_simc_xptar = new TH1F("h_simc_xptar","HMS xptar",100,-0.1,0.1);
  TH1F *h_simc_yptar = new TH1F("h_simc_yptar","HMS yptar",100,-0.06,0.06);
  TH1F *h_simc_ytar = new TH1F("h_simc_ytar","HMS ytar",100,-12,12);
  TH1F *h_simc_W = new TH1F("h_simc_W", "W [GeV]",100,0.8,1.3);

  //plot this stuff
  tt->Draw("H.gtr.dp>>h_delta",cut);
  tt->Draw("H.gtr.th>>h_xptar",cut);
  tt->Draw("H.gtr.ph>>h_yptar",cut);
  tt->Draw("H.gtr.y>>h_ytar",cut);
  tt->Draw("H.kin.W>>h_W",cut );

  for (int ii=0; ii<nentries; ii++){
    ts->GetEntry(ii);

    TLeaf *hsdeltaL = ts->GetLeaf("hsdelta");
    TLeaf *hsxptarL = ts->GetLeaf("hsxptar");
    TLeaf *hsyptarL = ts->GetLeaf("hsyptar");
    TLeaf *hsytarL = ts->GetLeaf("hsytar");
    TLeaf *hsWL = ts->GetLeaf("W");
    TLeaf *hWeight = ts->GetLeaf("Weight");
    double hsdeltaV = hsdeltaL->GetValue();
    double  hsxptarV = hsxptarL->GetValue();
    double hsyptarV = hsyptarL->GetValue();
    double hsytarV = hsytarL->GetValue();
    double hsWV = hsWL->GetValue();
    double hWeightV = hWeight->GetValue();

    if (hsWV>0.85 && hsWV<1.1 && abs(hsdeltaV)<8.0){
      h_simc_delta->Fill(hsdeltaV,hWeightV);
      h_simc_xptar->Fill(hsxptarV,hWeightV);
      h_simc_yptar->Fill(hsyptarV,hWeightV);
      h_simc_ytar->Fill(hsytarV,hWeightV);
      h_simc_W->Fill(hsWV,hWeightV);
    }
  }


  //save plots
  canvas->Update();

  h_delta->SetLineColor(kRed);
  h_delta->SetLineWidth(2);
  h_delta->Scale(1./h_delta->Integral());
  h_simc_delta->SetLineColor(kBlue);
  h_simc_delta->SetLineWidth(2);
  h_simc_delta->Scale(1./h_simc_delta->Integral());
  h_delta->Draw("HIST");
  h_simc_delta->Draw("histsame");
  canvas->Print((pdf_file_name +"(").c_str());

  h_xptar->SetLineColor(kRed);
  h_xptar->SetLineWidth(2);
  h_xptar->Scale(1./h_xptar->Integral());
  h_simc_xptar->SetLineColor(kBlue);
  h_simc_xptar->SetLineWidth(2);
  h_simc_xptar->Scale(1./h_simc_xptar->Integral());
  h_xptar->Draw("HIST");
  h_simc_xptar->Draw("histsame");
  canvas->Print((pdf_file_name +"(").c_str());

  h_yptar->SetLineColor(kRed);
  h_yptar->SetLineWidth(2);
  h_yptar->Scale(1./h_yptar->Integral());
  h_simc_yptar->SetLineColor(kBlue);
  h_simc_yptar->SetLineWidth(2);
  h_simc_yptar->Scale(1./h_simc_yptar->Integral());
  h_yptar->Draw("HIST");
  h_simc_yptar->Draw("histsame");
  canvas->Print((pdf_file_name +"(").c_str());

  h_ytar->SetLineColor(kRed);
  h_ytar->SetLineWidth(2);
  h_ytar->Scale(1./h_ytar->Integral());
  h_simc_ytar->SetLineColor(kBlue);
  h_simc_ytar->SetLineWidth(2);
  h_simc_ytar->Scale(1./h_simc_ytar->Integral());
  h_ytar->Draw("HIST");
  h_simc_ytar->Draw("histsame");
  canvas->Print((pdf_file_name +"(").c_str());

  h_W->SetLineColor(kRed);
  h_W->SetLineWidth(2);
  h_W->Scale(1./h_W->Integral());
  h_simc_W->SetLineColor(kBlue);
  h_simc_W->SetLineWidth(2);
  h_simc_W->Scale(1./h_simc_W->Integral());
  h_W->Draw("HIST");
  h_simc_W->Draw("histsame");
  canvas->Print((pdf_file_name +")").c_str());


  fout->Write();
  fout->Close();

}
