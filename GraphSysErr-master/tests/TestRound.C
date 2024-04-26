/**
 * @file   tests/TestRound.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:24:23 2017
 * 
 * @brief  Test rounding
 */
#ifdef __CLING__
# include "GraphSysErr.C"
#endif

/** 
 * Test round a single number @a v to @a n significant digits 
 * 
 * @param v Value 
 * @param n Number of significant digits 
 */
void TestOne(Double_t v, Int_t n)
{
  Int_t     e = 0;
  Double_t  r = GraphSysErr::Round(v, n, e);
  Double_t  w = r*TMath::Power(10,e);
  Printf("%12f (using %2d) -> %12f (with %2d) -> %12f",
	 v, n, r, e, w);
}
/** 
 * Test a set of value all rounded some number of significant
 * digits. The least value dictates how the others should be rounded.
 * 
 * @param pv Array of values 
 * @param nv Number of values 
 * @param n  Number of significant digits
 */
void TestSet(Double_t* pv, Int_t nv, Int_t n)
{
  Int_t  e  = 9999;
  Int_t* te = new Int_t[nv];
  for (Int_t i = 0; i < nv; i++) {
    Double_t re = GraphSysErr::Round(pv[i], n, te[i]);
    e           = TMath::Min(e, te[i]);
    Printf("%2d: %12.6f (using %2d) -> exponent %3d [%3d] %f",
	   i, n, pv[i], te[i], e, re*TMath::Power(10,te[i]));
  }
  for (Int_t i = 0; i < nv; i++) {
    Int_t    expo = Int_t(TMath::Log10(pv[i]));
    Int_t    ntmp = expo-e, le;
    if (expo >= 0) ntmp++;
    Double_t w    = GraphSysErr::Round(pv[i], ntmp, le);
    Double_t y    = w*TMath::Power(10, le);
    Printf ("%2d: %12.6f (expo: %2d, using %2d/%2d) -> %f %12.6f",
	    i, pv[i], expo, n, ntmp, w, y);
  }
}

/** 
 * Run the test
 * 
 */
void
TestRound()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C(0,0)");

  TestOne(1234.56789, 2);
  TestOne(1234.56789, 4);
  TestOne(1234.56789, 5);
  TestOne(1234.56789, 7);
  TestOne(5432.1,     2);

  {
    Double_t pv[] = { 100.123456, 0.231234, 0.0115, 0.0146, 1.00052, 10.00054 };
    TestSet(pv, 6, 2);
  }
}
//
// EOF
//

    
    
  
