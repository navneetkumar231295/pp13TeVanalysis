/**
 * @file      tests/Load.C
 * @copyright Christian Holm Christensen
 * @brief     Part of the GraphSysErr test suite
 */
void
Load(bool maker=false, bool dbg=false)
{
  gDebug = dbg ? 7 : 0;

  // TString mkLib = gSystem->GetMakeSharedLib();
  // mkLib.ReplaceAll("-std=c++14", "-std=c++98");
  // mkLib.Append("-ffpe-trap=invalid,zero,overflow,underflow,inexact");
  // mkLib.ReplaceAll("-pthread", "-include sstream -pthread");
  // Printf("%s",mkLib.Data());
  // gSystem->SetMakeSharedLib(mkLib);

  if (!gROOT->GetClass("GraphSysErr",false,true)) {
    Info("Load", "Loading the graph class");
    gROOT->LoadMacro("GraphSysErr.C+g");
  }

  if (maker && !gROOT->GetClass("TestMaker",false,true)) {
    Info("Load", "Loading the maker class");
    gROOT->LoadMacro("tests/TestMaker.C");
  }
  gDebug = false;
}

