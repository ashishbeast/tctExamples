{
  ////////////////////////////////////////////////////////////////////////////
  // This is a demonstrator for getting the induced current  waveforms from //    // measured waveforms taking into account the transfer function           //
  //////////////////////////////////////////////////////////////////////////// 

  PSTCT stct("NTypeDiode-300um_R.rtct", 11.5,2);
  stct.CorrectBaseLine();   // Baseline correction 
  stct.PrintInfo();         // Information about the read data 
  // group a set of votlages into a MeasureWF structure
  // basically this can be done for any set x,y,z,U1 and U2 parameters
  MeasureWF *wf= stct.Projection(0,3,0,0,0,0,0, stct.NU1); 

  TGraph *gr[10];

  TCTConv *jj=new TCTConv(2000,0.1);      // initialize class
  jj->Load("TestTransferFunc-1500.dat");  // load transfer function

  for(Int_t i=0;i<5;i++)                  //
   {
     TH1F *hism= wf->GetHA(12+i*4);             // get measured WF
     jj->GetIndCur(hism,0,1500);          // get induced current from WF
     gr[i]=jj->Draw(1);                   // get induced curent 
     gr[i]->SetLineColor(i);      // set color    
     if(i==0) gr[i]->Draw("AL"); else  gr[i]->Draw("L"); //draw

   }
}
