{
  Int_t k=0;
  // see Get-TCT.C for information about the next 6 program lines
  PSTCT stctIR("NTypeDiode-300um_IR.rtct", 81,2);
  PSTCT stctR("NTypeDiode-300um_R.rtct", 11.5,2);
  stctIR.CorrectBaseLine();   // Baseline correction 
  stctR.CorrectBaseLine();    // Baseline correction
  stctIR.PrintInfo();         // Information about the read data 
  stctR.PrintInfo();          // Information about the read data 


  stctR.RefC=-0.1276;  //Switch on the reflection correction by 
                       //setting the reflection amplitude -0.1276 e.g. means
                       //0.1276 of the main pulse with opposite polarity
  stctR.RefTs=0;       //time interval of the non-distorted region
  stctR.RefTe=26.2;
  // group a set of votlages into a MeasureWF structure
  // basically this can be done for any set x,y,z,U1 and U2 parameters
  MeasureWF *corR= stctR.Projection(0,3,0,0,0,0,0, stctR.NU1);
  stctR.RefC=-1;       // Switching off the reflection correction
  MeasureWF *ncorR= stctR.Projection(0,3,0,0,0,0,0, stctR.NU1);


  stctIR.RefC=-0.1276; 
  stctIR.RefTs=0;
  stctIR.RefTe=26.2;
  MeasureWF *corIR= stctIR.Projection(0,3,0,0,0,0,0, stctIR.NU1);
  stctIR.RefC=-1; // Switching of the reflection correction
  MeasureWF *ncorIR= stctIR.Projection(0,3,0,0,0,0,0, stctIR.NU1);


 TCanvas res("results","results",1200,800);
 //wf.DrawMode=true;
 res.Divide(2,2);

 res.cd(1);
 corR->DrawMulti(-5,80,2,stctR.NU1-1,6); //plot waveforms from -5 to 80 ns from voltage index 1 to 20 in steps of 3
 res.cd(2);
 ncorR->DrawMulti(-5,80,2,stctR.NU1-1,6); //plot current integral - charge integrated from 0 - 80 ns
 
 res.cd(3);
 corIR->DrawMulti(-5,80,1,stctIR.NU1-1,3); //plot waveforms from -5 to 80 ns from voltage index 1 to 20 in steps of 3
 res.cd(4);
 ncorIR->DrawMulti(-5,80,1,stctIR.NU1-1,3); //plot current integral - charge integrated from 0 - 80 ns
 

}
