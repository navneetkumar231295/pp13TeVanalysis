/**
 * @file   tests/TestLargeImport.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:13:35 2017
 * 
 * @brief  Test import of a large Durham input file 
 * 
 * 
 */
#ifdef __CLING__
# include "GraphSysErr.C"
# include <fstream>
#endif

/** 
 * Test import of a large Durham input file 
 * 
 */
void
TestLargeImport()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C");
  TSeqCollection* c = GraphSysErr::Import("inputs/large.input");
  c->ls();

  std::ofstream out("inputs/large_again.input");
  GraphSysErr::Export(c, out);
  out.close();
}
//
// EOF
//
