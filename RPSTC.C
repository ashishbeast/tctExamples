{
  PSTCT stct("NTypeDiode-300um-FocusFind-IR.rtct", 28.6,2);
  stct.CorrectBaseLine();   // Baseline correction 
  stct.PrintInfo();         // Information about the read data 

  TCanvas res("results","results",1200,800);
  res.Divide(1,2);

  res.cd(1);
  stct.GetHA(0,20,0,0,0,0)->Draw();

  TH1F *histo=stct.GetHA(0,0,0,0,0,0);
  histo->SetLineColor(2);
  histo->DrawCopy("SAME");

  res.cd(2);
  stct.Draw(0,1,0,0,0,0,0,20)->Draw("COLZ");
 
}
