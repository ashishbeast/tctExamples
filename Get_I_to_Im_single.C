{

  ////////////////////////////////////////////////////////////////////////////
  // This is a demonstrator for getting the measured waveform from          //
  // simulated waveform taking into account the transfer function           //
  // ///////////////////////////////////////////////////////////////////////// 
  gSystem->Load("SupportFuntions.C"); 

 //Simulation of the current drift;
  TF1 *neff=new TF1("neff","[0]+x[0]*0",0,1000);
  neff->SetParameter(0,0.2);
  TGraph *gr;

  KPad det(50,300);          // pad detector of 50um width, of 300 um thickness
  det->Neff=neff;            // define detector parameters
  det->Voltage=100;          // voltage
  det->SetUpVolume(1);       // initialize volume
  det->SetUpElectrodes();    // initialize electrodes
  det->SetEntryPoint(25,299.5,0.5); // entry point
  det->SetExitPoint(25,287.5,0.5);  // exit point
  det->Temperature=300;      // temperature [K]
  det->diff=1;               // diffusion is on
  det->average=1;            // averaging = 1
  det->SStep=0.25;           // simulation step size 0.25 um
  //  det->ShowMipIR(100,1); 
   det->MipIR(200,3.3);   // exponential depostion of 3.3 um 
  mama=RebinHistoX(det.sum,1e9); 

  
  TCTConv *jj=new TCTConv(2000,0.1); //2000 points, 100 ps between them
  jj->Load("TestTransferFunc-1500.dat"); //load transfer function
  gr=jj->Convolute(mama,true);          // convolution
  gr->Draw("AL");                       // draw convoluted response
}
