/**
 * @file   tests/TestFWHM.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:11:15 2017
 * 
 * @brief  Test to calculate full-width-at-half-maximum (FWHM)
 */
#ifdef __CLING__
# include "GraphSysErr.C"
# include "TestMaker.C"
#endif

/** 
 * Test to calculate full-width-at-half-maximum (FWHM)
 * 
 */
void
TestFWHM()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C(1,0)");
  gRandom->SetSeed(12345);

  GraphSysErr* g1 = TestMaker::MakeGaus("g1", 0,
					.001, .01.
					.05, .03);

  g1->Print("all");
  g1->Draw("axis quad combine");
 
  Double_t ymin, ymax, xmin, xmax;
  Int_t imin, imax;
  g1->GetMinMax("quad", ymin, ymax, xmin, xmax, imin, imax);
  Printf("min=(%3d:%f,%f) max=(%3d:%f,%f)",
	 imin, xmin, ymin, imax, xmax, ymax);
  
  Double_t fl, fh, xl, xh;
  Double_t fwhm = g1->FWHM(fl, fh, xl, xh);
  Printf("fwhm=%f -%f +%f [%f,%f]", fwhm, fl, fh, xl, xh);
  
  TGraphAsymmErrors* w = new TGraphAsymmErrors(2);
  w->SetPoint(0, xl, ymax/2);
  w->SetPoint(1, xh, ymax/2);
  w->SetPointError(0, fl, 0, 0, 0);
  w->SetPointError(1, 0, fh, 0, 0);
  w->Draw("l");
}
//
// EOF
//
