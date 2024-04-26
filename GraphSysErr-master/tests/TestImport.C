/**
 * @file   tests/TestImport.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:12:27 2017
 * 
 * @brief  Test of importing Durham database input files
 */

#include <fstream>
#include "GraphSysErr.C"
/** 
 * Import a Durham databae file 
 * 
 * @param input 
 */
struct GraphSysErr;

void
TestImport(const char* input="dndeta_pa.input", Bool_t check=true)
{
  // gROOT->Macro("tests/Load.C");

  TString base(input);
  base.ReplaceAll(".txt", "");
  base.ReplaceAll(".input", "");
  
  std::ifstream in(input);
  GraphSysErr* g = GraphSysErr::Import(in);
  
  gStyle->SetErrorX(.2);
 
  TCanvas* c = new TCanvas("imported", "Imported data");
  g->Draw("AXIS STACK STAT QUAD SPLIT");
  c->BuildLegend();

  c->Print(Form("%s.png", gSystem->BaseName(base)));
  
  if (check) {
    TString output(Form("%s_again.input", base.Data()));

    std::ofstream again(output.Data());
    g->Export(again, "",3);
    again.close();

    TString tmp[2];
    TString files[2];
    files[0] = input;
    files[1] = output.Data();
    for (Int_t i = 0; i < 2; i++) {
      tmp[i] = gSystem->BaseName(files[i].Data());
      gSystem->TempFileName(tmp[i]);
      TString cmd(Form("cat %s | grep -v \"^#\" | "
		       "sed 's/\\(DSYS=[^:]*\\):[^,)]*/\\1/g' |"
		       "sed 's/\\([0-9]\\)\\.*0*\\([[:space:];]\\)/\\1\\2/g' "
		       "> %s",
		       files[i].Data(), tmp[i].Data()));
      // Info("", cmd.Data());
      gSystem->Exec(cmd);
    }
    Int_t ret = gSystem->Exec(Form("diff -u -w %s %s",
				   tmp[0].Data(), tmp[1].Data()));
  }
}
//
// EOF
//
