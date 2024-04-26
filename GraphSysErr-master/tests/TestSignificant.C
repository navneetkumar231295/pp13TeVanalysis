/**
 * @file   tests/TestSignificant.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:28:12 2017
 * 
 * @brief  Test round of numbers
 */
#ifdef __CLING__
# include "GraphSysErr.C"
#endif

/** 
 * Test of rounding value @a v to @a n significant digits
 * 
 * @param v Value 
 * @param n Number of significant digits
 */
void
Test(Double_t v, Int_t n)
{
  std::cout << v << " [" << n << "] -> " << std::flush;
  Int_t    e = 0;
  Double_t m = GraphSysErr::Round(v, n, e);
  Double_t w = m*TMath::Power(10,e);
  Int_t    sp = std::cout.precision();
  std::cout.precision(n);
  std::cout << w << std::endl;
  std::cout.precision(sp);
}

/** 
 * Round a value and an error to a number of significant digits.  The
 * smaller of the two dictates the actual rounding
 * 
 * @param v Value 
 * @param e Error
 * @param n Number of significant digitis 
 */
void
TestV(Double_t v, Double_t e, Int_t n)
{
  std::cout << v << " +/-" << e << " [" << n << "] -> " << std::flush;
  Int_t    sp = std::cout.precision();
  Int_t    ee = 0;
  Double_t me = GraphSysErr::Round(e, n, ee);
  Double_t re = me*TMath::Power(10,ee);
  Int_t    nV = TMath::Ceil(TMath::Log10(TMath::Abs(v)))-ee; 
  std::cout << std::setprecision(nV) << v  << " +/- "
	    << std::setprecision(n) << re << std::endl;
  std::cout.precision(sp);
}
/** 
 * Round a value and an error to a number of significant digits.  The
 * smaller of the two dictates the actual rounding
 * 
 * @param v  Value 
 * @param el lower error
 * @param eh higher error
 * @param n  Number of significant digitis 
 */
void
TestW(Double_t v, Double_t el, Double_t eh, Int_t n)
{
  std::cout << v << " -" << el << " +" << eh << " [" << n << "] -> "
	    << std::flush;
  Int_t    sp = std::cout.precision();
  Int_t    pl, ph;
  Double_t ml = GraphSysErr::Round(el, n, pl);
  Double_t mh = GraphSysErr::Round(eh, n, ph);
  Double_t rl = ml*TMath::Power(10,pl);
  Double_t rh = mh*TMath::Power(10,ph);
  Int_t    ep = TMath::Min(pl,ph);
  Int_t    nV = TMath::Ceil(TMath::Log10(TMath::Abs(v)))-ep;
  std::cout << std::setprecision(nV) << v << " -"
	    << std::setprecision(n) << rl << " +"
	    << std::setprecision(n) << rh << std::endl;
  std::cout.precision(sp);
}

/** 
 * Test exoprt
 * 
 * @param n Number of significant digits
 */
void
TestG(Int_t n=2)
{
  GraphSysErr* g = new GraphSysErr("g","g");
  Int_t c1 = g->DefineCommon("c1", false, 1.2345);
  Int_t c2 = g->DefineCommon("c2", true, 0.12345);
  Int_t p1 = g->DeclarePoint2Point("p1",false);
  Int_t p2 = g->DeclarePoint2Point("p2",false);
  Int_t p3 = g->DeclarePoint2Point("p3",false);

  g->SetPoint(0, 1234.567890, 123.456789012345);
  g->SetPointError(0, 1.2345, 0.12345);
  g->SetStatError(0, 4.321, 5.4321);
  g->SetSysError(p1, 0, 0, 0, 5.6789, 9.8765);
  g->SetSysError(p2, 0, 0, 0, 12.33456, 123.456);
  g->SetSysError(p3, 0, 0, 0, 0.065432, 0.01534);

  g->SetPoint(1, 1213, 123);
  g->SetPointError(1,0,0);
  g->SetSysError(p1, 1, 0, 0, 10, 20);
  g->SetSysError(p2, 1, 0, 0, 10, 20);
  g->SetSysError(p3, 1, 0, 0, 10, 20);

  g->SetPoint(2, 1.213, 123);
  g->SetPointError(2,0.300,0.300);
  g->SetSysError(p1, 2, 0, 0, 11, 10);
  g->SetSysError(p2, 2, 0, 0, 12, 13);
  g->SetSysError(p3, 2, 0, 0, 14, 15);
  
  g->Export(std::cout,"",n,n);
}

/** 
 * Run the test
 * 
 */
void
TestSignificant()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C");
  Test(TMath::Pi(), 4);
  Test(123.4567, 2);
  Test(123.4567, 3);
  Test(123.4567, 4);
  Test(0.001234567, 1);
  Test(0.00234567, 1);
  Test(1.25, 2);
  Test(1.35, 2);
  Test(-1.251, 2);  
  TestV(1234.4567, 1.2345, 2);
  TestV(1234.4567, 123, 2);
  TestV(0.512, 1.21, 2);
  TestV(0.512, 1.21, -1);
  TestV(1234, 0, 2);

  TestW(123.456789, 1.2345, 12.34567, 4);

  TestG(2);
}
//
// EOF
//
