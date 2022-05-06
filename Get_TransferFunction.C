{
  ////////////////////////////////////////////////////////////////////////////
  // This is a demonstrator for obtaining the transfer function from the    // 
  // measured and simulated wafeform (see a link to the theory)             //
  // ///////////////////////////////////////////////////////////////////////// 
  gSystem->Load("SupportFuntions.C");


  ////////////////////////////////////
  //Simulation of the current drift //
  ////////////////////////////////////

  TF1 *neff=new TF1("neff","[0]+x[0]*0",0,1000);  // neff function
  neff->SetParameter(0,0.2);                      
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
  det->MipIR(200,3.3);       // exponential depostion of 3.3 um 
                             // penetration depth

  ////////////////////////////////////
  //Measurement of the current drift //
  ////////////////////////////////////

  PSTCT stct("NTypeDiode-300um_R.rtct", 11.5,2);
  stct.CorrectBaseLine();   // Baseline correction 
  stct.PrintInfo();         // Information about the read data 

  // group a set of votlages into a MeasureWF structure
  // basically this can be done for any set x,y,z,U1 and U2 parameters
  MeasureWF *wf= stct->Projection(0,3,0,0,0,0,0, stct->NU1); 
  TH1F *hism=wf->GetHA(20);  // get histogram
  hiss= RebinHistoX(det.sum,1e9); // rebin to have x-axis in [ns]

  TCTConv *jj=new TCTConv(2000,0.1);  // initialize class
  jj->GetTransferFuntion(hism,hiss, 0, 1500); // get tranfer function
  jj->Save("TestTransferFunc-1500.dat"); // save it to disk

}
