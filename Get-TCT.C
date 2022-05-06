{
  Int_t k=0;
  // see Get-Scanning-TCT.C for information about the next 3 program lines
  PSTCT stct("NTypeDiode-300um_R.rtct", 11.5,2);
  stct.CorrectBaseLine();   // Baseline correction 
  stct.PrintInfo();         // Information about the read data 
  // group a set of votlages into a MeasureWF structure
  // basically this can be done for any set x,y,z,U1 and U2 parameters
  MeasureWF* wf= stct.Projection(0,3,0,0,0,0,0, stct.NU1); 
  wf->SetTemperatures(300);

 TCanvas res("results","results",1200,800);
 wf->DrawMode=true;
 res.Divide(1,2);
 res.cd(1);
 wf->DrawMulti(-5,80,1, stct.NU1-1,3); //plot waveforms from -5 to 80 ns from voltage index 1 to 20 in steps of 3
 res.cd(2);
 wf->CCE(0,80); //plot current integral - charge integrated from 0 - 80 ns
 
}
