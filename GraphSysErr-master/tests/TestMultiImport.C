/**
 * @file   tests/TestMultiImport.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:20:49 2017
 * 
 * @brief  Test of multple imports from a single file
 */
#ifdef __CLING__
# include "GraphSysErr.C"
#endif
#include <fstream>

/** 
 * Test of importing multiple data sets from a single file. 
 * 
 * @param file 
 */
void
TestMultiImport(const char* file="inputs/sample.input")
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C");

  TString base = file;
  base.ReplaceAll(".input", "");
  base.ReplaceAll(".txt",   "");
  TString nam = gSystem->BaseName(base);

  TFile*        out  = TFile::Open(Form("%s.root",base.Data()), "RECREATE");
  std::ifstream in(file);
  GraphSysErr*  g = 0;
  
  std::ofstream again(Form("%s_again.input", base.Data()));
  Bool_t        first = true;

  Int_t id  = 0;
  do { 
    TCanvas* c = 0;
    Int_t sub = 1;
    do { 
      int cur = in.tellg();
      if (!(g = GraphSysErr::Import(in, sub))) break;
      
      in.seekg(cur, in.beg);

      if (!c) 
	c = new TCanvas(Form("c%d", id++), 
		    Form("Dataset %d", id),
		    1200, 900);
      if (sub == 1) g->Draw("axis stack common stat");
      else          g->Draw("stack common stat same");
      
      g->SetName(Form("%s%02d_%02d",nam.Data(),id, sub)); 
      g->Write();
      g->Export(again, first ? "H" : "");
      first = false;

      sub++;
    } while (true);
  } while (!in.eof());
  // g->Export();
  out->Write();
  out->Close();

  again.close();
}
// 
// EOF
// 


