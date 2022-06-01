void plotHeepCoin(){

  //read the input file
  //TFile *f = new TFile(Form("mkROOTfiles/hms_replay_matrixopt_%i_-1.root",nrun));
  //TFile *f = new TFile("myROOTfiles/data_heep_low.root");
  TFile *f = new TFile("/volatile/hallc/spring17/holly/shmsoptics/coin_replay_production_7830_-1.root");

  TTree *tt = (TTree*)f->Get("T");

  TFile *f1 = new TFile("/w/hallc-scifs17exp/e1206107/holly/simc_gfortran/worksim/h1_sidis_40c.root");
  TTree *ts = (TTree*)f1->Get("h666");

  int nentries = ts->GetEntries();

  //here's the cut
  //TCut cut = "H.gtr.dp<8&&H.gtr.dp>-8&&H.kin.primary.W>0.8&&H.kin.primary.W<1.1&&P.cal.etracknorm>0.8&&abs(P.kin.secondary.emiss)<0.2";
  TCut cut = "";//H.cal.etracknorm>0.8";

  //make the output file
  TCanvas *canvas = new TCanvas("canvas","plots",800,800);
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetBorderSize(0);
  canvas->SetFrameFillColor(0);
  canvas->SetFrameBorderMode(0);
  std::string pdf_file_name= Form("output_heep/output_heep_coin_7830.pdf");
  gROOT->SetBatch(true);
  gStyle->SetOptStat(0);
  canvas->SetGridx();
  canvas->SetGridy();
  TFile *fout = new TFile("output_heep/output_heep_coin_7830.root","RECREATE");


  //make plots
  //data
  TH1F *h_delta = new TH1F("h_delta","HMS delta",100,-12,12);
  TH1F *h_xptar = new TH1F("h_xptar","HMS xptar",100,-0.1,0.1);
  TH1F *h_yptar = new TH1F("h_yptar","HMS yptar",100,-0.06,0.06);
  TH1F *h_ytar = new TH1F("h_ytar","HMS ytar",100,-12,12);
  TH1F *p_delta = new TH1F("p_delta","SHMS delta",100,-20,30);
  TH1F *p_xptar = new TH1F("p_xptar","SHMS xptar",100,-0.1,0.1);
  TH1F *p_yptar = new TH1F("p_yptar","SHMS yptar",100,-0.06,0.06);
  TH1F *p_ytar = new TH1F("p_ytar","SHMS ytar",100,-12,12);
  TH1F *h_W = new TH1F("h_W", "W [GeV]",100,0.4,1.6);
  TH1F *h_Emiss = new TH1F("h_Emiss", "Emiss [GeV]",100,-0.1,0.15);
  TH1F *h_Pmiss = new TH1F("h_Pmiss", "Pmiss [GeV]",100,0.0,0.25);
  TH1F *h_PmissZ = new TH1F("h_PmissZ", "Pmiss_z [GeV]",100,-0.4,0.4);

  //simc
  TH1F *h_simc_delta = new TH1F("h_simc_delta","HMS delta",100,-12,12);
  TH1F *h_simc_xptar = new TH1F("h_simc_xptar","HMS xptar",100,-0.1,0.1);
  TH1F *h_simc_yptar = new TH1F("h_simc_yptar","HMS yptar",100,-0.06,0.06);
  TH1F *h_simc_ytar = new TH1F("h_simc_ytar","HMS ytar",100,-12,12);
  TH1F *p_simc_delta = new TH1F("p_simc_delta","SHMS delta",100,-20,30);
  TH1F *p_simc_xptar = new TH1F("p_simc_xptar","SHMS xptar",100,-0.1,0.1);
  TH1F *p_simc_yptar = new TH1F("p_simc_yptar","SHMS yptar",100,-0.06,0.06);
  TH1F *p_simc_ytar = new TH1F("p_simc_ytar","SHMS ytar",100,-12,12);
  TH1F *h_simc_W = new TH1F("h_simc_W", "W [GeV]",100,0.4,1.6);
  TH1F *h_simc_Emiss = new TH1F("h_simc_Emiss", "Emiss [GeV]",100,-0.1,0.15);
  TH1F *h_simc_Pmiss = new TH1F("h_simc_Pmiss", "Pmiss [GeV]",100,0.0,0.25);
  TH1F *h_simc_PmissZ = new TH1F("h_simc_PmissZ", "Pmiss_z [GeV]",100,-0.4,0.4);

  //plot this stuff
  tt->Draw("H.gtr.dp>>h_delta",cut);
  tt->Draw("H.gtr.th>>h_xptar",cut);
  tt->Draw("H.gtr.ph>>h_yptar",cut);
  tt->Draw("H.gtr.y>>h_ytar",cut);
  tt->Draw("H.kin.primary.W>>h_W",cut );

  tt->Draw("P.gtr.dp>>p_delta",cut);
  tt->Draw("P.gtr.th>>p_xptar",cut);
  tt->Draw("P.gtr.ph>>p_yptar",cut);
  tt->Draw("P.gtr.y>>p_ytar",cut);
  tt->Draw("P.kin.secondary.emiss>>h_Emiss",cut);
  tt->Draw("P.kin.secondary.pmiss>>h_Pmiss",cut);
  tt->Draw("P.kin.secondary.pmiss_z>>h_PmissZ",cut);

  for (int ii=0; ii<nentries; ii++){
    ts->GetEntry(ii);

    TLeaf *hsdeltaL = ts->GetLeaf("hsdelta");
    TLeaf *hsxptarL = ts->GetLeaf("hsxptar");
    TLeaf *hsyptarL = ts->GetLeaf("hsyptar");
    TLeaf *hsytarL = ts->GetLeaf("hsytar");
    TLeaf *psdeltaL = ts->GetLeaf("ssdelta");
    TLeaf *psxptarL = ts->GetLeaf("ssxptar");
    TLeaf *psyptarL = ts->GetLeaf("ssyptar");
    TLeaf *psytarL = ts->GetLeaf("ssytar");
    TLeaf *hsWL = ts->GetLeaf("W");
    TLeaf *hWeightL = ts->GetLeaf("Weight");
    TLeaf *hEmL = ts->GetLeaf("Em");
    TLeaf *hPmL = ts->GetLeaf("Pm");
    TLeaf *hPmzL = ts->GetLeaf("Pmz");

    double hsdeltaV = hsdeltaL->GetValue();
    double hsxptarV = hsxptarL->GetValue();
    double hsyptarV = hsyptarL->GetValue();
    double hsytarV = hsytarL->GetValue();
    double psdeltaV = psdeltaL->GetValue();
    double psxptarV = psxptarL->GetValue();
    double psyptarV = psyptarL->GetValue();
    double psytarV = psytarL->GetValue();
    double hsWV = hsWL->GetValue();
    double hWeightV = hWeightL->GetValue();
    double hEmV = hEmL->GetValue();
    double hPmV = hPmL->GetValue();
    double hPmzV = hPmzL->GetValue();

    if (hsWV>0.8 && hsWV<1.1 && abs(hsdeltaV)<8.0){
      h_simc_delta->Fill(hsdeltaV,hWeightV);
      h_simc_xptar->Fill(hsxptarV,hWeightV);
      h_simc_yptar->Fill(hsyptarV,hWeightV);
      h_simc_ytar->Fill(hsytarV,hWeightV);
      p_simc_delta->Fill(psdeltaV,hWeightV);
      p_simc_xptar->Fill(psxptarV,hWeightV);
      p_simc_yptar->Fill(psyptarV,hWeightV);
      p_simc_ytar->Fill(psytarV,hWeightV);
      h_simc_W->Fill(hsWV,hWeightV);
      h_simc_Emiss->Fill(hEmV,hWeightV);
      h_simc_Pmiss->Fill(hPmV,hWeightV);
      h_simc_PmissZ->Fill(hPmzV,hWeightV);

    }
  }


  //save plots
  gPad->Clear();
  canvas->Divide(2,2);
  canvas->Update();
  //gPad->Clear();

  canvas->cd(1);
  h_delta->SetLineColor(kRed);
  h_delta->SetLineWidth(2);
  h_delta->Scale(1./h_delta->Integral());
  h_simc_delta->SetLineColor(kBlue);
  h_simc_delta->SetLineWidth(2);
  h_simc_delta->Scale(1./h_simc_delta->Integral());
  h_simc_delta->Draw("HIST");
  h_delta->Draw("histsame");
  //canvas->Print((pdf_file_name +"(").c_str());

  canvas->cd(2);
  h_xptar->SetLineColor(kRed);
  h_xptar->SetLineWidth(2);
  h_xptar->Scale(1./h_xptar->Integral());
  h_simc_xptar->SetLineColor(kBlue);
  h_simc_xptar->SetLineWidth(2);
  h_simc_xptar->Scale(1./h_simc_xptar->Integral());
  h_simc_xptar->Draw("HIST");
  h_xptar->Draw("histsame");
  //canvas->Print((pdf_file_name +"(").c_str());

  canvas->cd(3);
  h_yptar->SetLineColor(kRed);
  h_yptar->SetLineWidth(2);
  h_yptar->Scale(1./h_yptar->Integral());
  h_simc_yptar->SetLineColor(kBlue);
  h_simc_yptar->SetLineWidth(2);
  h_simc_yptar->Scale(1./h_simc_yptar->Integral());
  h_simc_yptar->Draw("HIST");
  h_yptar->Draw("histsame");
  //canvas->Print((pdf_file_name +"(").c_str());

  canvas->cd(4);
  h_ytar->SetLineColor(kRed);
  h_ytar->SetLineWidth(2);
  h_ytar->Scale(1./h_ytar->Integral());
  h_simc_ytar->SetLineColor(kBlue);
  h_simc_ytar->SetLineWidth(2);
  h_simc_ytar->Scale(1./h_simc_ytar->Integral());
  h_simc_ytar->Draw("HIST");
  h_ytar->Draw("histsame");
  canvas->Print((pdf_file_name +"(").c_str());

  canvas->cd(1);
  p_delta->SetLineColor(kRed);
  p_delta->SetLineWidth(2);
  p_delta->Scale(1./p_delta->Integral());
  p_simc_delta->SetLineColor(kBlue);
  p_simc_delta->SetLineWidth(2);
  p_simc_delta->Scale(1./p_simc_delta->Integral());
  p_simc_delta->Draw("HIST");
  p_delta->Draw("histsame");
  //canvas->Print((pdf_file_name +"(").c_str());

  canvas->cd(2);
  p_xptar->SetLineColor(kRed);
  p_xptar->SetLineWidth(2);
  p_xptar->Scale(1./p_xptar->Integral());
  p_simc_xptar->SetLineColor(kBlue);
  p_simc_xptar->SetLineWidth(2);
  p_simc_xptar->Scale(1./p_simc_xptar->Integral());
  p_simc_xptar->Draw("HIST");
  p_xptar->Draw("histsame");
  //canvas->Print((pdf_file_name +"(").c_str());

  canvas->cd(3);
  p_yptar->SetLineColor(kRed);
  p_yptar->SetLineWidth(2);
  p_yptar->Scale(1./p_yptar->Integral());
  p_simc_yptar->SetLineColor(kBlue);
  p_simc_yptar->SetLineWidth(2);
  p_simc_yptar->Scale(1./p_simc_yptar->Integral());
  p_simc_yptar->Draw("HIST");
  p_yptar->Draw("histsame");
  //canvas->Print((pdf_file_name +"(").c_str());

  canvas->cd(4);
  p_ytar->SetLineColor(kRed);
  p_ytar->SetLineWidth(2);
  p_ytar->Scale(1./p_ytar->Integral());
  p_simc_ytar->SetLineColor(kBlue);
  p_simc_ytar->SetLineWidth(2);
  p_simc_ytar->Scale(1./p_simc_ytar->Integral());
  p_simc_ytar->Draw("HIST");
  p_ytar->Draw("histsame");
  canvas->Print((pdf_file_name +"(").c_str());


  canvas->cd(1);
  h_W->SetLineColor(kRed);
  h_W->SetLineWidth(2);
  h_W->Scale(1./h_W->Integral());
  h_simc_W->SetLineColor(kBlue);
  h_simc_W->SetLineWidth(2);
  h_simc_W->Scale(1./h_simc_W->Integral());
  h_simc_W->Draw("HIST");
  h_W->Draw("histsame");
  //canvas->Print((pdf_file_name +"(").c_str());
  
  canvas->cd(2);
  h_Emiss->SetLineColor(kRed);
  h_Emiss->SetLineWidth(2);
  h_Emiss->Scale(1./h_Emiss->Integral());
  h_simc_Emiss->SetLineColor(kBlue);
  h_simc_Emiss->SetLineWidth(2);
  h_simc_Emiss->Scale(1./h_simc_Emiss->Integral());
  h_simc_Emiss->Draw("HIST");
  h_Emiss->Draw("histsame");

  canvas->cd(3);
  h_Pmiss->SetLineColor(kRed);
  h_Pmiss->SetLineWidth(2);
  h_Pmiss->Scale(1./h_Pmiss->Integral());
  h_simc_Pmiss->SetLineColor(kBlue);
  h_simc_Pmiss->SetLineWidth(2);
  h_simc_Pmiss->Scale(1./h_simc_Pmiss->Integral());
  h_simc_Pmiss->Draw("HIST");
  h_Pmiss->Draw("histsame");


  canvas->cd(4);
  h_PmissZ->SetLineColor(kRed);
  h_PmissZ->SetLineWidth(2);
  h_PmissZ->Scale(1./h_PmissZ->Integral());
  h_simc_PmissZ->SetLineColor(kBlue);
  h_simc_PmissZ->SetLineWidth(2);
  h_simc_PmissZ->Scale(1./h_simc_PmissZ->Integral());
  h_simc_PmissZ->Draw("HIST");
  h_PmissZ->Draw("histsame");

  canvas->Print((pdf_file_name +")").c_str());

  fout->Write();
  fout->Close();

}
