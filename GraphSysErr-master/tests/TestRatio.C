/**
 * @file   tests/TestRatio.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:21:26 2017
 * 
 * @brief  Test taking ratios 
 */
#ifdef __CLING__
# include "GraphSysErr.C"
# include "TestMaker.C"
#endif
class GraphSysErr;
class TestMaker;

/**
 * Test taking ratios 
 * 
 */
void
TestRatio()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C(1,0)");
  gRandom->SetSeed(12345);

  GraphSysErr* num = TestMaker::MakeGaus("num", 0);
  // num->RemoveSysError(3);
  // num->Print("xy p2p");
  
  GraphSysErr* den = TestMaker::MakeGaus("den", 0);
  // den->RemoveSysError(3);
  // den->Print("xy p2p");

  GraphSysErr* r  = GraphSysErr::Ratio(num,den);
  r->Print("xy p2p");

  TCanvas* c = new TCanvas("c","C", 900, 600);
  c->Divide(1,3,0,0);

  c->cd(1); num->Draw("axis stack split");
  c->cd(2); den->Draw("axis stack split");
  c->cd(3); r ->Draw("axis stack split");

}
//
// EOF
//

  
