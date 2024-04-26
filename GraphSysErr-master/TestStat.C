/**
 * @file   tests/TestStat.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Mar 16 12:30:18 2017
 * 
 * @brief  Run tests on statistics
 */
#ifdef __CLING__
# include "GraphSysErr.C"
#endif

/** 
 * Test of stats
 * 
 * @param func Function expression
 * @param r    The return graph
 * @param h    The return histogram
 */
void Make(const TString& func,
	  TObject*&      r,
	  TH1*&          h)
{
  Double_t xMin=0, xMax=1;
  Int_t    n=20;
  if      (func.BeginsWith("gaus"))   { xMin = -3; xMax = +3; n = 10; }
  else if (func.BeginsWith("landau")) { xMin = 0;  xMax = 10; n = 100; }
  h = new TH1D(Form("h%s", func.Data()), Form("Hist. of %s", func.Data()),
	       n, xMin, xMax);
  h->Sumw2();
  h->SetStats(0);
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.2);
  h->SetLineWidth(3);
  h->SetMarkerColor(kRed+2);
  h->SetLineColor(kRed+2);
  h->SetDirectory(0);
  h->FillRandom(func);
  // Stats(h);
  
  GraphSysErr* g = new GraphSysErr(Form("h%s", func.Data()),
				   Form("Graph of %s", func.Data()));
  Int_t sys = g->DeclarePoint2Point("Syst.uncerr.",false,
				    GraphSysErr::kBox);
  // g->DefineCommon("Common",true,.05,GraphSysErr::kBox);
  g->SetSumOption(GraphSysErr::kBox);
  g->SetDataOption(GraphSysErr::kNoTick);
  g->SetMarkerStyle(24);
  g->SetMarkerSize(1.4);
  g->SetMarkerColor(kBlue+2);
  g->SetLineColor(kBlue+2);
  g->SetSumLineColor(kBlue+2);
  for (Int_t i = 0; i < n; i++) {
    Double_t x = h->GetXaxis()->GetBinCenter (i+1);
    Double_t w = h->GetXaxis()->GetBinWidth  (i+1);
    Double_t y = h->            GetBinContent(i+1);
    Double_t e = h->            GetBinError  (i+1);

    g->SetPoint     (i, x, y);
    g->SetPointError(i, w/2);
    g->SetStatError (i, 0);
    g->SetSysError  (sys, i, 0, e);
  }
  r = g;
}

/** 
 * Get the stats
 * 
 * @param h Histogram
 */
void
Stats(TH1* h)
{
  if (!TString(h->GetName()).Contains("gaus")) return;
  h->ResetStats();
  Double_t stats[10];
  h->GetStats(stats);
  Printf("                                          "
	 "hist n=%f  sumY=%7.1f  sumXY=%7.1f  sumXXY=%7.1f  sumE2=%7.2f",
	 TMath::Sqrt(h->GetEffectiveEntries()), 
	 stats[0], stats[2], stats[3], stats[1]);
  Double_t sumY=0, sumXY=0, sumXXY=0, sumE2=0;
  for (Int_t i = 0; i < h->GetNbinsX(); i++) {
    Double_t x = h->GetXaxis()->GetBinCenter (i+1);
    Double_t y = h->            GetBinContent(i+1);
    Double_t e = h->            GetBinError  (i+1);
    sumY   += y;
    sumXY  += x*y;
    sumXXY += x*x*y;
    sumE2  += e*e;
    Printf("             %3d (x,y)=(%6.3f,%6.1f)+/-(%6.1f)        -> "
	   "sumY=%7.1f  sumXY=%7.1f  sumXXY=%7.1f  sumE2=%7.2f",
	   i, x, y, e, sumY, sumXY, sumXXY, sumE2);
  }
}

/** 
 * Draw test
 * 
 * @param p Pad
 * @param o Graph
 * @param h Histogram
 */
void
Draw(TVirtualPad* p, TObject* o, TH1* h)
{
  GraphSysErr* g = static_cast<GraphSysErr*>(o);

  p->cd();
  p->SetTicks();

  h->SetMaximum(1.2*h->GetMaximum());
  h->Draw();
  g->Draw("stat quad combine xbase=2");

  h->ResetStats();
  Double_t hMean  = h->GetMean();
  Double_t hEMean = h->GetMeanError();
  Double_t hRMS   = h->GetRMS();
  Double_t hERMS  = h->GetRMSError();
  Double_t gEMean = 0;
  Double_t gMean  = g->MeanX(gEMean);
  Double_t gERMS  = 0;
  Double_t gRMS   = g->StandardDeviationX(gERMS);
  Double_t rMean  = gMean / hMean;
  Double_t rEMean = rMean * TMath::Sqrt(TMath::Power(hEMean/hMean,2) +
					TMath::Power(gEMean/gMean,2));
  Double_t rRMS   = gRMS  / hRMS;
  Double_t rERMS  = rRMS * TMath::Sqrt(TMath::Power(hERMS/hRMS,2) +
				       TMath::Power(gERMS/gRMS,2));
  

  Int_t   width = 5;
  Int_t   prec  = 3;
  TString ifmt;  ifmt.Form("%d.%df", width, prec);
  TString fmt("%10s: ");
  for (Int_t i = 0; i < 6; i++)
    fmt.Append(Form("%%%s+/-%%%s  ", ifmt.Data(), ifmt.Data()));
  Printf(fmt.Data(), 
	 h->GetName(),
	 hMean, hEMean, gMean, gEMean, rMean, rEMean,
	 hRMS,  hERMS,  gRMS,  gERMS,  rRMS,  rERMS);
#if 0
  Printf("%10s: "
	 "%6.3f +/- %6.3f  %6.3f +/- %6.3f  "
	 "%6.3f +/- %6.3f  %6.3f +/- %6.3f",
	 h->GetName(),
	 hMean, hEMean, gMean, gEMean, hRMS, hERMS, gRMS, gERMS);
#endif 
}

/** 
 * Do a test
 * 
 * @param func Function
 * @param p    Pad
 */
void
Do(const TString& func, TVirtualPad* p)
{
  TObject* o;
  TH1*     h;
  Make(func, o, h);
  Draw(p, o, h);
}
       
/** 
 * Run the test
 * 
 */
void
TestStat()
{
  TH1::StatOverflows(false);
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->LoadMacro("../GraphSysErr.C+g");
  gStyle->SetOptFit(11111);
  
  TCanvas* c = new TCanvas("c","c");
  c->Divide(2,3);
  Printf("%10s: %13s  %13s  %13s  %13s  %13s  %13s",
	 "Name",
	 "Hist. mean", "Graph mean", "Mean ratio", 
	 "Hist. RMS",  "Graph RMS",  "RMS ratio");
  const char* bar = "-------------";
  Printf("%10s+--%13s+-%13s+-%13s+-%13s+-%13s+-%13s",
	 "----------", bar, bar, bar, bar, bar, bar);
  Do("gaus", c->cd(1));
  Do("expo", c->cd(2));
  TF1* f = static_cast<TF1*>(gROOT->GetFunction("expo"));
  f->SetParameter(1,-f->GetParameter(1));
  Do("expo", c->cd(3));
  f = static_cast<TF1*>(gROOT->GetFunction("landau"));
  f->SetParameter(1,1);
  Do("landau", c->cd(4));
  Do("pol1", c->cd(5));
  Do("cheb2", c->cd(6));
}
//
// EOF
//
