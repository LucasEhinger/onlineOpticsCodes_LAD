void plotOptics(const std::string& runfile, int nrun) {

  //read the input file
  TFile *f = new TFile(runfile.c_str());
  TTree *tt = (TTree*)f->Get("T");

  //here's the cut
  TCut cut = "P.gtr.dp<20&&P.gtr.dp>-15&&P.cal.etracknorm>0.8&&P.ngcer.npeSum>5";
 TCut cutCentral = "abs(P.gtr.x+P.gtr.th*253.0)<1&&abs((-0.019*P.gtr.dp+0.00019*P.gtr.dp*P.gtr.dp+(138.0+75.0)*P.gtr.ph+P.gtr.y) + 40.0*(-0.00052*P.gtr.dp+0.0000052*pow(P.gtr.dp,2)+P.gtr.ph))<1";

  //make the output file
  TCanvas *canvas = new TCanvas("canvas","plots",800,800);
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetBorderSize(0);
  canvas->SetFrameFillColor(0);
  canvas->SetFrameBorderMode(0);
  std::string pdf_file_name= Form("shms_output_plots_%i_sieve0.pdf",nrun);
  gROOT->SetBatch(true);
  gStyle->SetOptStat(0);
  canvas->SetGridx();
  canvas->SetGridy();
  TFile *fout = new TFile(Form("shms_output_plots_%i_sieve0.root",nrun),"RECREATE");


  //make plots
  TH1F *h_z = new TH1F("h_z",";P.react.z [cm]",100,-14,14);
  TH2F *h2_ypVy = new TH2F("h2_ypVy",";yTar [cm];ypTar",100,-5,5,100,-0.05,0.05);
  TH2F *h2_yfpVxfp = new TH2F("h2_yfpVxfp",";xfp [cm];yfp [cm]",100,0,8,100,-10,10);
  TH2F *h2_dpVz = new TH2F("h2_dpVz",";zVertex [cm];delta",100,-14,14,100,-15,20);
  TH2F *h2_ypVz = new TH2F("h2_ypVz",";zVertex [cm];ypTar",100,-14,14,100,-0.05,0.05);
  TH2F *h2_sieve = new TH2F("h2_sieve",";ySieve [cm];xSieve[cm]",200,-7.0,7.0,200,-12.0,12.0);
  TH2F *h2_xpVd = new TH2F("h2_xpVd",";delta;xpfp",100,-10,20,100,-0.15,0.15);
  
  //plots with central hole only
  TH1F *h_z_c = new TH1F("h_z_c","central sieve hole;P.react.z [cm]",100,-14,14);
  TH2F *h2_ypVy_c = new TH2F("h2_ypVy_c","central sieve hole;yTar [cm];ypTar",100,-5,5,100,-0.05,0.05);
  TH2F *h2_yfpVxfp_c = new TH2F("h2_yfpVxfp_c","central sieve hole;yfp [cm];yfp [cm]",100,0,8,100,-10,10);
  TH2F *h2_dpVz_c = new TH2F("h2_dpVz_c","central sieve hole;zVertex [cm];delta",100,-14,14,100,-10,20);
  TH2F *h2_ypVz_c = new TH2F("h2_ypVz_c","central sieve hole;zVertex [cm];ypTar",100,-14,14,100,-0.05,0.05);
  TH2F *h2_sieve_c = new TH2F("h2_sieve_c","central sieve hole;ySieve [cm];xSieve[cm]",200,-7.0,7.0,200,-12.0,12.0);
  TH2F *h2_xpVd_c = new TH2F("h2_xpVd_c","central sieve hole;delta;xpfp",100,-15,20,100,-0.15,0.15);

  TH2F *h2_ypVzSlice[8];


  //plot this stuff
  tt->Draw("P.gtr.ph:P.react.z>>h2_ypVz",cut);
  tt->Draw("P.dc.y_fp:P.dc.x_fp>>h2_yfpVxfp",cut);
  tt->Draw("P.gtr.ph:P.gtr.y>>h2_ypVy",cut);
  tt->Draw("P.react.z>>h_z",cut);
  tt->Draw("P.gtr.dp:P.react.z>>h2_dpVz",cut);
  tt->Draw("P.gtr.x+P.gtr.th*253.0:(-0.019*P.gtr.dp+0.00019*P.gtr.dp*P.gtr.dp+(138.0+75.0)*P.gtr.ph+P.gtr.y) + 40.0*(-0.00052*P.gtr.dp+0.0000052*pow(P.gtr.dp,2)+P.gtr.ph)>>h2_sieve",cut);
  tt->Draw("P.dc.xp_fp:P.gtr.dp>>h2_xpVd",cut);

  tt->Draw("P.gtr.ph:P.react.z>>h2_ypVz_c",cut && cutCentral);
  tt->Draw("P.dc.y_fp:P.dc.x_fp>>h2_yfpVxfp_c",cut && cutCentral);
  tt->Draw("P.gtr.ph:P.gtr.y>>h2_ypVy_c",cut && cutCentral);
  tt->Draw("P.react.z>>h_z_c",cut && cutCentral);
  tt->Draw("P.gtr.dp:P.react.z>>h2_dpVz_c",cut && cutCentral);
  tt->Draw("P.gtr.x+P.gtr.th*253.0:(-0.019*P.gtr.dp+0.00019*P.gtr.dp*P.gtr.dp+(138.0+75.0)*P.gtr.ph+P.gtr.y) + 40.0*(-0.00052*P.gtr.dp+0.0000052*pow(P.gtr.dp,2)+P.gtr.ph)>>h2_sieve_c",cut && cutCentral);
  tt->Draw("P.dc.xp_fp:P.gtr.dp>>h2_xpVd_c",cut && cutCentral);

  for (int ii=0; ii<8; ii++){
    h2_ypVzSlice[ii] = new TH2F(Form("h2_ypVzSlice_%i",ii),Form("xfp=%i cm +/- 0.5cm;zVertex [cm]; ypTar",ii+1),100,-15,15,100,-0.05,0.05);
    TCut slice = Form("abs(P.dc.x_fp - (%i+1))<0.5",ii);
    tt->Draw(Form("P.gtr.ph:P.react.z>>h2_ypVzSlice_%i",ii),cut && slice);
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
