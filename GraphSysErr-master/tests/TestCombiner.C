/**
 * @file   tests/TestCombiner.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:09:06 2017
 * 
 * @brief  Test of combining measurements
 */
#ifdef __CLING__
# include "GraphSysErr.C"
#endif

void
TestCombiner()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C");

  GraphSysErr::LinearSigmaCombiner c;
  // c.Add(13.18033379,  0.37746449, 0.37626207);
  // c.Add(7.55818948,   0.24479109, 0.24390579);
  // 
  // c.Add(12.50000000,  0.38827359, 0.38827359);
  // c.Add(7.57000000,   0.27457892, 0.27457892);
  // 12.49856770  -0.19289140 +1.34511073   0.90
  // c.Add(8.34995000, 0.56761238, 0.54887823);
  // c.Add(2.83162000, 0.19248769, 0.18613460);
  // 3.18213600  -0.17182767 +0.16685073  67.89
  c.Add(10.34000000, 0.31137728, 0.31137728);
  c.Add(4.21000000, 0.12683815, 0.12683815);
  // 5.08239630  -0.11746638 +0.11746638  332.41
  c.Calculate();
  c.fResult->Print();
  c.Draw();
}
//
// EOF
//
