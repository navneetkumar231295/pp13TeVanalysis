/**
 * @file   tests/WriteTests.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:31:01 2017
 * 
 * @brief  Tests of writing
 * 
 * 
 */
#ifdef __CLING__
# include "GraphSysErr.C"
#endif

struct GraphSysErr;

// forward declarations
void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
/** 
 * Write the tests 
 * 
 */
void WriteTests()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C");
  
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
}

/** 
 * Make a gausian graphs
 * 
 * @param g Graph to modify 
 */
void MakeGaus(GraphSysErr* g)
{
  g->SetXTitle("X");
  g->SetYTitle("Gaus");
  
  TH1*  h = new TH1D("hist", "hist", 30, -3, 3);
  h->FillRandom("gaus");
  Bool_t rel=g->IsStatRelative();
  for (Int_t i = 1; i <= h->GetNbinsX(); i++) {
    Double_t x  = h->GetXaxis()->GetBinCenter(i);
    Double_t y  = h->GetBinContent(i);
    Double_t ex = h->GetXaxis()->GetBinWidth(i)/2;
    Double_t ey = h->GetBinError(i);
    if (rel) ey *= (y == 0 ? 0 : 1./y);
    g->SetPoint(i-1, x, y);
    g->SetPointError(i-1, ex);
    g->SetStatError(i-1, ey);
  }
  delete h;
}
/** 
 * Make an error value 
 * 
 * @param relative If true, then as a relative error 
 * 
 * @return Error
 */
Double_t MakeError(Bool_t relative)
{
  return (relative ? gRandom->Uniform(0.1,0.2) : gRandom->Uniform(1, 10));
}
/** 
 * Add common systematic error
 * 
 * @param g         graph
 * @param relative  if true, relative value
 * @param asym      if true, make asymmetric 
 * 
 * @return Identifier of uncertainty 
 */
UInt_t AddCommon(GraphSysErr* g, Bool_t relative=false, Bool_t asym=false)
{
  TUUID uid;
  Double_t eyl = MakeError(relative);
  Double_t eyh = (asym ? MakeError(relative) : eyl);
  return g->DefineCommon(uid.AsString(), relative, eyl, eyh);
}
/** 
 * Export to a file 
 * 
 * @param g        Graph
 * @param filename Where to export to 
 */
void Export(GraphSysErr* g, const char* filename)
{
  std::ofstream out(filename);
  g->Export(out, "H");
  out.close();
}
/** 
 * Import from a file 
 * 
 * @param filename File to read from 
 * 
 * @return read graph
 */
GraphSysErr* Import(const char* filename)
{
  std::ifstream in(filename);
  GraphSysErr* ret = GraphSysErr::Import(in, 1);
  in.close();
  return ret;
}
/** 
 * Compare for I/O of graphs
 * 
 * @param g Graph
 * @param i Index
 * 
 * @return 
 */
Bool_t Diff(GraphSysErr* g, Int_t i)
{
  TString out   = Form("test%02d.input", i);
  TString check = Form("check%02d.input", i);
  Export(g, out);
  GraphSysErr* g1 = Import(out);
  if (!g1) { 
    Error("Diff", "Failed to import from %s", out.Data());
    return false;
  }
  g1->SetMarkerColor(kRed+1);
  g1->SetMarkerStyle(21);
  g1->Draw("stat same");
  Export(g1, check);
  Int_t ret = gSystem->Exec(Form("diff -u -w %s %s", out.Data(), check.Data()));
  if (ret != 0) Warning("Diff", "Test # %d failed", i);
  return ret == 0;
}

/** 
 * Draw a graph
 * 
 * @param g Graph 
 * @param i Index
 */
void Draw(GraphSysErr* g, Int_t i, Option_t* options="axis stat")
{
  TCanvas* c = new TCanvas(Form("c%02d", i), Form("Test # %d", i));
  g->Draw(options);
}

/** 
 * Run test 1
 */
void Test1()
{
  GraphSysErr* g = new GraphSysErr("simple", "Simple data");
  MakeGaus(g);

  Draw(g, 1);
  Diff(g, 1);
}

/** 
 * Run test 2
 */
void Test2()
{
  GraphSysErr* g = new GraphSysErr("simple", "Simple data");
  g->SetStatRelative(true);
  MakeGaus(g);

  Draw(g, 2);
  Diff(g, 2);
}

/** 
 * Run test 3
 */
void Test3()
{
  GraphSysErr* g = new GraphSysErr("simple", "Simple data");
  g->SetKey("reference", "archive : year");
  g->SetKey("reference", "journal : year");
  g->SetKey("reackey", "Reaction 1");
  g->SetKey("reackey", "Reaction 2");
  g->SetKey("obskey", "Observation 1");
  g->SetKey("obskey", "Observation 2");
  g->SetKey("qual", "Qualifier 1");
  g->SetKey("qual", "Qualifier 2");
  MakeGaus(g);

  Draw(g, 3);
  Diff(g, 3);
}


/** 
 * Run test 4
 */
void Test4()
{
  GraphSysErr* g = new GraphSysErr("simple", "Simple data");
  MakeGaus(g);
  UInt_t id = AddCommon(g);
  g->SetSysLineColor(id, kGreen+2);
  g->SetSysFillColor(id, kGreen+2);
  
  Draw(g, 4, "stat split axis");
  Diff(g, 4);
}

/** 
 * Run test 5
 */
void Test5()
{
  GraphSysErr* g = new GraphSysErr("simple", "Simple data");
  MakeGaus(g);
  UInt_t id = AddCommon(g, true, true);
  g->SetSysLineColor(id, kGreen+2);
  g->SetSysFillColor(id, kGreen+2);

  Draw(g, 5, "stack stat common axis");
  Diff(g, 5);
}
//
// EOF
//
