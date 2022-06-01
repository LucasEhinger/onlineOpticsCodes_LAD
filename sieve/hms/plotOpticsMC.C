void plotOpticsMC(){

  //read the input file
  TFile *f = new TFile("~hszumila/hallc/mc-single-arm-FORK/worksim/hms_carbon_Q3p5_6gev.root");
  TTree *tt = (TTree*)f->Get("h1");

  //here's the cut
  TCut cut = "hsdelta<9&&hsdelta>-9";
  TCut cutCentral = "abs(hsyptar)<0.005&&abs(hsytar)<1";

  //make the output file
  TCanvas *canvas = new TCanvas("canvas","plots",800,800);
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetBorderSize(0);
  canvas->SetFrameFillColor(0);
  canvas->SetFrameBorderMode(0);
  std::string pdf_file_name= "output_plots_MC_Q3p5.pdf";
  gROOT->SetBatch(true);
  gStyle->SetOptStat(0);
  canvas->SetGridx();
  canvas->SetGridy();
  TFile *fout = new TFile("output_plots_MC_Q3p5.root","RECREATE");


  //make plots
  TH1F *h_z = new TH1F("h_z",";H.react.z [cm]",100,-14,14);
  TH2F *h2_ypVy = new TH2F("h2_ypVy",";yTar [cm];ypTar",100,-5,5,100,-0.05,0.05);
  TH2F *h2_yfpVxfp = new TH2F("h2_yfpVxfp",";xfp [cm];yfp [cm]",100,-5,5,100,-10,10);
  TH2F *h2_dpVz = new TH2F("h2_dpVz",";zVertex [cm];delta",100,-14,14,100,-15,20);
  TH2F *h2_ypVz = new TH2F("h2_ypVz",";zVertex [cm];ypTar",100,-14,14,100,-0.05,0.05);
  TH2F *h2_sieve = new TH2F("h2_sieve",";ySieve [cm];xSieve[cm]",200,-0.04,0.04,200,-0.06,0.06);
  TH2F *h2_xpVd = new TH2F("h2_xpVd",";delta;xpfp",100,-10,20,100,-0.15,0.15);
  
  //plots with central hole only
  TH1F *h_z_c = new TH1F("h_z_c","central sieve hole;H.react.z [cm]",100,-14,14);
  TH2F *h2_ypVy_c = new TH2F("h2_ypVy_c","central sieve hole;yTar [cm];ypTar",100,-5,5,100,-0.05,0.05);
  TH2F *h2_yfpVxfp_c = new TH2F("h2_yfpVxfp_c","central sieve hole;xfp [cm];yfp [cm]",100,-5,5,100,-10,10);
  TH2F *h2_dpVz_c = new TH2F("h2_dpVz_c","central sieve hole;zVertex [cm];delta",100,-14,14,100,-10,20);
  TH2F *h2_ypVz_c = new TH2F("h2_ypVz_c","central sieve hole;zVertex [cm];ypTar",100,-14,14,100,-0.05,0.05);
  TH2F *h2_sieve_c = new TH2F("h2_sieve_c","central sieve hole;ySieve [cm];xSieve[cm]",200,-0.04,0.04,200,-0.06,0.06);
  TH2F *h2_xpVd_c = new TH2F("h2_xpVd_c","central sieve hole;delta;xpfp",100,-15,20,100,-0.15,0.15);

  TH2F *h2_ypVzSlice[8];

  //sieve at 166.032
  //plot this stuff
  tt->Draw("hsyptar:ztar>>h2_ypVz",cut);
  tt->Draw("hsyfp:hsxfp>>h2_yfpVxfp",cut);
  tt->Draw("hsyptar:hsytar>>h2_ypVy",cut);
  tt->Draw("ztar>>h_z",cut);
  tt->Draw("hsdelta:ztar>>h2_dpVz",cut);
  tt->Draw("hsxptar:hsyptar>>h2_sieve",cut);
  tt->Draw("hsxpfp:hsdelta>>h2_xpVd",cut);

  tt->Draw("hsyptar:ztar>>h2_ypVz_c",cut && cutCentral);
  tt->Draw("hsyfp:hsxfp>>h2_yfpVxfp_c",cut && cutCentral);
  tt->Draw("hsyptar:hsytar>>h2_ypVy_c",cut && cutCentral);
  tt->Draw("ztar>>h_z_c",cut && cutCentral);
  tt->Draw("hsdelta:ztar>>h2_dpVz_c",cut && cutCentral);
  tt->Draw("hsxptar:hsyptar>>h2_sieve_c",cut && cutCentral);
  tt->Draw("hsxpfp:hsdelta>>h2_xpVd_c",cut && cutCentral);

  for (int ii=0; ii<8; ii++){
    h2_ypVzSlice[ii] = new TH2F(Form("h2_ypVzSlice_%i",ii),Form("xfp=%i cm +/- 0.5cm;zVertex [cm]; ypTar",ii-4),100,-15,15,100,-0.05,0.05);
    TCut slice = Form("abs(hsxfp - (%i+1))<0.5",ii-4);
    tt->Draw(Form("hsyptar:ztar>>h2_ypVzSlice_%i",ii),cut && slice);
  }

  //save plots
  canvas->Update();

  h_z->SetLineWidth(2);
  h_z->Draw();
  canvas->Print((pdf_file_name +"(").c_str());

  h2_ypVz->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_dpVz->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_ypVy->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_yfpVxfp->Draw("colz");  
  canvas->Print((pdf_file_name +"(").c_str());

  h2_sieve->Draw("colz");  
  canvas->Print((pdf_file_name +"(").c_str());

  h2_xpVd->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h_z_c->SetLineWidth(2);
  h_z_c->Draw();
  canvas->Print((pdf_file_name +"(").c_str());

  h2_ypVz_c->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_dpVz_c->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_ypVy_c->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_yfpVxfp_c->Draw("colz");  
  canvas->Print((pdf_file_name +"(").c_str());

  h2_sieve_c->Draw("colz");  
  canvas->Print((pdf_file_name +"(").c_str());

  h2_xpVd_c->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  for (int jj=0;jj<8; jj++){
    h2_ypVzSlice[jj]->Draw("colz");
    canvas->Print((pdf_file_name +"(").c_str());
  }
  h2_xpVd_c->Draw("colz");
  canvas->Print((pdf_file_name +")").c_str());

  fout->Write();
  fout->Close();

}
