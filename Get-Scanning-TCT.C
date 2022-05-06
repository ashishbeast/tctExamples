{ 
  gSystem->Load("TCTAnalyse.sl"); // load the dll library
  PSTCT stct("NTypeDiode-300um-FocusFind-IR.rtct",28.6,2); // measurement file
  // 1st parameter : file_name is the name of the file
  // 2nd parameter : set the scale such that signal start at t=0; 
  // 3rd parameter : Byte order (little/big endian), default  =2 
  stct.CorrectBaseLine();   // Correction for the DC offset, uses the data before t=0
  stct.PrintInfo();           // Information about the read data 

  TCanvas res("Example","Example",1200,800);
  res.Divide(1,2);
 
  res.cd(1); 
  stct.GetHA(0,20,0,0,0,0)->Draw(); // plot the first waveform taken
  // parameters ch, x, y, z, U1, U2 - all indexes
  histo=stct.GetHA(0,0,0,0,0,0);
  histo->SetLineColor(2); 
  histo->DrawCopy("SAME");             // plot the first waveform with x index =0

  res.cd(2);
  stct.Draw(0,1,0,0,0,0,0,20)->Draw("COLZ");// Draw 2D plot of integral X,Z
  // X=direction of metalization crossing during focus find 
  // Z=distance of the laser to the sample 
  // note the sharp transition when crossing the metal is where the focus is the best

  
}


