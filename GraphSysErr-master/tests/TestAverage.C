/**
 * @file   tests/TestAverage.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:07:15 2017
 * 
 * @brief  Test of averaging 
 */
#ifdef __CLING__
# include "GraphSysErr.C"
#endif

/** 
 * Draw an object 
 * 
 * @param c 
 * @param no 
 * @param o 
 */
void
Draw(TVirtualPad* c, Int_t no, TObject* o)
{
  if (!o) return;
  TVirtualPad* p = c->cd(no);
  if (!p) return;
  p->SetGridx();
  p->SetGridy();
  p->SetTicks();
  p->SetRightMargin(0.01);
  o->Draw("axis stack stat split");
  // o->Draw("axis sum stat split");
}

/** 
 * Average objects in lust 
 * 
 * @param l    List of graphs 
 * @param sep  Separate uncertainties?
 * 
 * @return Average of all in @a l
 */
TObject* Average(TList* l, bool sep)
{
  if (!l) return 0;
  GraphSysErr* a  = new GraphSysErr("a", Form("Average (%s)",
					      sep ? "separate" : "sum"));
  a->Average(l, sep);
  a->Print("xy sys sum");
  if (!sep) {
    a->SetSysLineColor(3,kRed+2);
    a->SetSysFillColor(3,kRed+2);
    a->SetSysOption(3,GraphSysErr::kBox);
  }
  return a;
}
/** 
 * Run the test
 * 
 */  
void
TestAverage()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C(1,0)");
  gRandom->SetSeed(12345);

  // GraphSysErr* g1 = TestMaker::MakeGaus("g1", 0);
  // GraphSysErr* g2 = TestMaker::MakeGaus("g2", 0);
  GraphSysErr* g1 = TestMaker::MakeLine("g1", 1,2);
  GraphSysErr* g2 = TestMaker::MakeLine("g2", 2,3);
  g1->SetTitle("G1");
  g2->SetTitle("G2");
  g1->Print("xy sys sum");
  g2->Print("xy sys sum");
  TList* l = new TList;
  l->Add(g1);
  l->Add(g2);

  // return;
  TObject* a1 = Average(l, true);
  TObject* a2 = Average(l, false);
  
  TCanvas* c = new TCanvas("c","C", 900, 600);
  c->Divide(1,(a2 ? 4 : 3),0,0);

  Draw(c, 1, g1);
  Draw(c, 2, g2);
  Draw(c, 3, a1);
  Draw(c, 4, a2);

}  
//
// EOF
//
