/**
 * @file   tests/TestExport.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:10:09 2017
 * 
 * @brief  Test of exporting data to durham input files
 * 
 * 
 */
#ifdef __CLING__
# include "GraphSysErr.C"
#endif

/** 
 * Test of exporting data to durham input files
 * 
 */
void TestExport()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C(0,0)");

  GraphSysErr* g = new GraphSysErr("g", "g");
  Int_t p1 = g->DeclarePoint2Point("p1", false);
  Int_t p2 = g->DeclarePoint2Point("p2", false);

  g->SetPoint(0, 0, 1);
  g->SetStatError(0, .14, .14123);
  g->SetSysError(p1, 0, 0, 0, .012, .321876543);
  g->SetSysError(p2, 0, 0, 0, .12,  .21512356);

  g->SetPoint(1, 0, 1);
  g->SetStatError(1, 100, 100);
  g->SetSysError(p1, 1, 0, 0, 123, 876);
  g->SetSysError(p2, 1, 0, 0, 101, 807);

  g->SetPoint(2, 3.25, 1643.38040);
  g->SetStatError(2, 3, 3);
  g->SetSysError(p1, 2, 0, 0, 74.26, 74.26);
  g->SetSysError(p2, 2, 0, 0, 10,    10);
    

  std::cout.setf(std::ios::fixed);
  g->Export(std::cout, "", 2);
}
//
// EOF
//
