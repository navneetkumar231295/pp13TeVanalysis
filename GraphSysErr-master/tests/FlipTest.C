/**
 * @file      tests/FlipTest.C
 * @copyright Christian Holm Christensen
 * @brief     Part of the GraphSysErr test suite
 */
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TMath.h>

void
FlipTest()
{
  Int_t n = 7;
  TGraphAsymmErrors* g[4] = { 0, 0 ,0, 0 };
  g[0] = new TGraphAsymmErrors(n);
  g[0]->SetMarkerStyle(20);
  g[0]->SetFillStyle(3001);
  g[0]->SetFillColor(kRed+2);
  g[0]->SetTitle("Graph # 0");
  for (Int_t j = 1; j < 4; j++) {
    g[j] = static_cast<TGraphAsymmErrors*>(g[0]->Clone());
    g[j]->SetTitle(Form("Graph # %d", j));
  }
  for (Int_t i = 0; i < n; i++) { 
    for (Int_t j = 0; j < 4; j++) 
      g[j]->SetPoint(i, i+1, i);
    Double_t exl = n-2*i;
    Double_t exh = i-.5*n;
    g[0]->SetPointError(i, 0.5, 0.5, exl, exh);
    g[1]->SetPointError(i, 0.5, 0.5, exh, exl);
    g[2]->SetPointError(i, 0.5, 0.5, TMath::Abs(exh), TMath::Abs(exl));
    g[3]->SetPointError(i, 0.5, 0.5, TMath::Abs(exl), TMath::Abs(exh));
  }
  
  TCanvas* c = new TCanvas("c", "C");
  c->Divide(2,2,0,0);

  for (Int_t j = 0; j < 4; j++) {
    c->cd(j+1);
    g[j]->Draw("alp 30");
    Printf(g[j]->GetTitle());
    g[j]->Print();
  }

}
