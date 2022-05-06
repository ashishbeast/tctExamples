{
  ////////////////////////////////////////////////////////////////////////////
  // This is a demonstrator for getting the measured waveforms from         //
  // simulated waveforms taking into account the transfer function          //
  // The comparisson between measured and simulated curves are shown        //
  //////////////////////////////////////////////////////////////////////////// 
  gSystem->Load("SupportFuntions.C");


 PSTCT stct("NTypeDiode-300um_R.rtct", 11.5,2);
  stct.CorrectBaseLine();   // Baseline correction 
  stct.PrintInfo();         // Information about the read data 
  // group a set of votlages into a MeasureWF structure
  // basically this can be done for any set x,y,z,U1 and U2 parameters
  MeasureWF *wf= stct.Projection(0,3,0,0,0,0,0, stct.NU1); //get measurements

  //Simulation of the current drift;
  TF1 *neff=new TF1("neff","[0]+x[0]*0",0,1000);
  neff->SetParameter(0,0.2);
  TGraph *gr[10];
  TH1F *Is[10],*Im[10];

  TCTConv *jj=new TCTConv(2000,0.1);      //init class
  jj->Load("TestTransferFunc-1500.dat");  //load transfer functions

for(Int_t i=0;i<6;i++) 
{
  KPad *det=new KPad(50,300);     //simulated currents for different voltages
  det->Neff=neff;
  det->Voltage=50+i*20;
  det->SetUpVolume(1);
  det->SetUpElectrodes();
  det->SetEntryPoint(25,299.5,0.5);
  det->SetExitPoint(25,287.5,0.5);
  det->Temperature=300;
  det->SStep=1;
  det->diff=1;
  det->average=1;
  det->SStep=0.25;
  det->MipIR(200,3.3);
  Is[i]=RebinHistoX(det->sum,1e9);
  //  det->ShowMipIR(100,1);

 
  gr[i]=jj->Convolute(Is[i],true); 
  ShiftGraph(gr[i],0,-11.5);  // shift graphs so that the WF are aligned
  gr[i]->SetLineColor(i);
  ScaleGraph(gr[i],-0.0005);  // normalize graphs
  if(i==0) gr[i]->Draw("AL"); else  gr[i]->Draw("L"); 

  Im[i]=wf->GetHA(10+i*4);
  Im[i]->Scale(-1);
  Im[i]->SetLineColor(i);
  Im[i]->SetLineStyle(2);
  Im[i]->Draw("SAME");
 }

 

}
