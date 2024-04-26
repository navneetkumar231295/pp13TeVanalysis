/**
 * @file   tests/TestLine.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:15:09 2017
 * 
 * @brief  Test with a simple line 
 */
#ifdef __CLING__
# include "GraphSysErr.C"
# include "TestMaker.C"
#endif

/** 
 * Test with a simple line 
 * 
 */
void
TestLine()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C(1,0)");
  gRandom->SetSeed(12345);

  GraphSysErr* g1 = TestMaker::MakeLine("g1", 1,2);
  g1->Print("xy sum sys");

  for (Int_t i = 0; i < g1->GetN(); i++) {
    Double_t eyl, eyh, wyl, wyh;
    Double_t y = g1->GetYandError(i, false,false,true,false,
				  eyl, eyh, wyl, wyh);
    Double_t peyl = g1->GetSysErrorYDown(3, i);
    Double_t peyh = g1->GetSysErrorYUp(3, i);
    
    Double_t x = g1->GetX(i);
    Printf("%d: %10.7f -> %10.7f +%10.7f -%10.7f [+%10.7f -%10.7f]",
	   i, x, y, eyl, eyh, peyl, peyh);
  }
}
//
// EOF
//


