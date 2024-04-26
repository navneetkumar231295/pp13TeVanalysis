/**
 * @file   tests/TestMaker.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:15:58 2017
 * 
 * @brief  A class to make tests 
 * 
 * 
 */
#ifndef TESTMAKER_C
#define TESTMAKER_C
#ifdef __CLING__
# include "GraphSysErr.C"
#endif
class GraphSysErr;

/**
 * A structure to make various tests
 * 
 */
struct TestMaker
{
  /** 
   * Fill in keys 
   * 
   * @param gse Graph
   */
  static void FillKeys(GraphSysErr* gse)
  {
    // Draw data with-out ticks 
    gse->SetDataOption(GraphSysErr::kNoTick);
    gse->SetXTitle("X");
    gse->SetYTitle("Y");
    // Set some key/value pairs 
    gse->SetKey("laboratory", "The Center");
    gse->SetKey("accelerator", "Mega Collider");
    gse->SetKey("detector", "Huge Experiment");
    gse->SetKey("author", "Christensen");
    gse->SetKey("reference","Jour.All.Things A1,999");
    gse->SetKey("doi","9999-9999-9999-9999");
    gse->SetKey("abstract", "The data");
    gse->SetKey("location", "In the paper");
    gse->SetKey("reackey", "graviton -> tachyons");
    gse->SetKey("obskey", "GUT");
    gse->SetKey("qual", "Life, universe, and everything");

    // Set options on summed errors (in case of option COMBINED)
    gse->SetSumLineColor(kRed+2);
    gse->SetSumLineWidth(2);
    gse->SetSumTitle("All errors");
    gse->SetSumOption(GraphSysErr::kHat);
  }
  /** 
   * Make a commen systematic uncertainty 
   * 
   * @param gse Graph
   * @param rel Relative if this is true
   * @param val Value 
   * 
   * @return Identifier of systematic uncertainty
   */
  static Int_t MakeCommon(GraphSysErr* gse, Bool_t rel, Double_t val)
  {
    if (val < 0) return -1;
    TString title;
    if (rel) title.Form("Common %4.1f%%", val*100);
    else     title.Form("Common %f", val);
    UInt_t id = gse->DefineCommon(title, rel, val);
    Color_t c = (!rel ? kRed : kCyan)+2;    
    gse->SetSysFillColor(id, c);
    gse->SetSysFillStyle(id, 3001);
    gse->SetSysLineColor(id, c);
    gse->SetSysOption(id, GraphSysErr::kBox);
    return id;
  }
  /** 
   * Make a point-to-point systematic uncertainty.  The values will be
   * sampled from a flat distribution between @a min and @a max
   * 
   * @param gse Graph
   * @param rel Relative if this is true
   * @param min Least value
   * @param max Largest value
   * 
   * @return Identifier of systematic uncertainty
   */
  static Int_t MakeP2P(GraphSysErr* gse, Bool_t rel, Double_t min, Double_t max)
  {
    if (min < 0) return -1;
    TString title;
    if (rel) title.Form("Point-to-point %f-%f%%", min*100, max*100);
    else     title.Form("Point-to-point %f-%f", min, max);
    UInt_t id = gse->DeclarePoint2Point(title, rel);
    Color_t c = (rel ? kBlue : kGreen)+2;

    gse->SetSysLineColor(id, c);
    gse->SetSysLineWidth(id, (rel ? 2 : 3));
    if (!rel) 
      gse->SetSysOption(id, GraphSysErr::kHat);
    else
      gse->SetSysOption(id, GraphSysErr::kBar);
    return id;
  }
  /**
   * Make our test data. The points are drawn from a Gaussian
   * distribution, while common errors are fixed and point-to-point
   * errors are drawn from uniform distributions.
   * 
   * @param name    Name of graph
   * @param off     Offset 
   * @param cmnFix  Fixed common uncertainty value
   * @param cmnRel  Relative common uncertainty value
   * @param p2pFix  Fixed point-to-point uncertainty mean
   * @param p2pRel  Relative point-to-point uncertainty mean
   * 
   * @return Graph
   */
  static GraphSysErr* MakeGaus(const char* name="foo",
			       Double_t off=0,
			       Double_t cmnFix=.05,
			       Double_t cmnRel=.10,
			       Double_t p2pFix=.10,
			       Double_t p2pRel=.05)
  {
    GraphSysErr* gse = new GraphSysErr(name, "Gaussian");
    FillKeys(gse);

    // Two sources of common errors, one relative, one absolute
    // MakeCommon(gse, false,  cmnFix);
    MakeCommon(gse, true,   cmnRel);

    // Two sources of point-to-point errors, one relative, one absolute
    UInt_t pp1 = MakeP2P(gse, false, p2pFix, 2*p2pFix);
    UInt_t pp2 = MakeP2P(gse, true,  p2pRel, 2*p2pRel);
    
    // Fill a histogram with a Guassian random deviate 
    TH1* h = new TH1F("h", "h", 30, -3, 3);
    h->Sumw2();
    h->SetDirectory(0);
    h->FillRandom("gaus",10000);
    h->Scale(1./10000, "width");

    for (Int_t i = 0, j = 0; i < h->GetNbinsX(); i++) { 
      Int_t    bin = i+1;
      Double_t x   = h->GetXaxis()->GetBinCenter(bin);
      Double_t y   = h->GetBinContent(bin);
      Double_t sta = h->GetBinError(bin);
      if (TMath::Abs(off) > 1e-9) y += off;
      if (sta < 1e-6) continue;
      if (y < 1e-6) continue;
      
      // Set data 
      gse->SetPoint(j, x, y);
      gse->SetStatError(j, sta);
      // gse->SetPointError(j, h->GetXaxis()->GetBinWidth(i)/2);

      Double_t abs = gRandom->Uniform(p2pFix, 2*p2pFix);
      Double_t rl  = gRandom->Uniform(p2pRel, 2*p2pRel);
      Double_t rh  = gRandom->Uniform(p2pRel, 2*p2pRel);
      // Info("", "Point %2d abs=%f rl=%f rh=%f", abs, rl, rh);
      // Set point-to-point errors
      if (pp1 > 0) gse->SetSysError(pp1, j, 0., abs);
      if (pp2 > 0) gse->SetSysError(pp2, j, 0., 0., rl, rh);
      j++;
    }
    delete h;
    return gse;
  } //EndTest1
  /** 
   * Make a straigh line graph 
   * 
   * @param name Name 
   * @param a    First value 
   * @param b    Second value 
   * 
   * @return The graph
   */
  static GraphSysErr* MakeLine(const char* name, Double_t a, Double_t b)
  {
    GraphSysErr* gse = new GraphSysErr(name, "Line");
    FillKeys(gse);

    // Two sources of common errors, one relative, one absolute
    MakeCommon(gse, false,  0.05);
    MakeCommon(gse, true,   0.10);

    // Two sources of point-to-point errors, one relative, one absolute
    // UInt_t pp1 = MakeP2P(gse, false, 0.1, 0.2);
    UInt_t pp2 = MakeP2P(gse, true,  0.10, 0.10);

    Int_t n = 10;
    for (Int_t i = 0; i < n; i++) {
      Double_t y = a*i+b;
      gse->SetPoint(i, i, y);
      gse->SetPointError(i, .5, .5);
      gse->SetStatError(i, TMath::Sqrt(y));
      
      Double_t abs = 0.1;  // gRandom->Uniform(0.1, 0.2);
      Double_t rl  = 0.05; // gRandom->Uniform(0.05, 0.1);
      Double_t rh  = 0.10; // gRandom->Uniform(0.05, 0.1);
      // Info("", "Point %2d abs=%f rl=%f rh=%f", abs, rl, rh);
      // Set point-to-point errors 
      // gse->SetSysError(pp1, i, 0., abs);
      gse->SetSysError(pp2, i, 0., 0., rl, rh);
    }
    return gse;
  }
};
#endif
// EOF

