void ShiftGraph(TGraph *gr,Int_t axis, Float_t offset)
{
  Int_t i;
  for(i=0;i<gr->GetN();i++)
    {
      if(axis==0)
	gr->GetX()[i]+=offset;
      else
	gr->GetY()[i]+=offset;
    }

}

TH1F *RebinHistoX(TH1F *his,Float_t scale)
{
  Int_t numBin=his->GetXaxis()->GetNbins();
  Float_t binup=his->GetXaxis()->GetBinUpEdge(numBin);
  Float_t binlow=his->GetXaxis()->GetBinLowEdge(1);
  
  TH1F *hisN=new TH1F("hisN",his->GetTitle(),numBin,binlow*scale,binup*scale);
  
  for(int i=0;i<=his->GetXaxis()->GetNbins();i++)
    {
      hisN->SetBinContent(i,his->GetBinContent(i));
    }
  return hisN;
}
