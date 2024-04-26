void absf()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Dec 22 12:41:29 2023) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "c1",72,64,700,502);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c1->Range(-5.917567,-0.04347826,33.99084,0.2270531);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.1482787);
   c1->SetBottomMargin(0.1607143);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH2F *h1__1 = new TH2F("h1__1","h1 title",1000,0,30,1000,0,0.2);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__1->SetLineColor(ci);
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetTitleOffset(1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("");
   
   Double_t Graph0_fx1001[10] = {
   2.55,
   4.5,
   6.32,
   7.95,
   10.02,
   12.04,
   13.77,
   16.17,
   20.02,
   26.02};
   Double_t Graph0_fy1001[10] = {
   0.1200199,
   0.126896,
   0.1304168,
   0.1313776,
   0.1329592,
   0.1338662,
   0.1344974,
   0.1355358,
   0.1368562,
   0.1300969};
   Double_t Graph0_fex1001[10] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[10] = {
   9.797998e-05,
   0.0001051413,
   0.0001274588,
   0.0001200479,
   0.0001141222,
   0.0001382931,
   0.0001346156,
   0.0001285481,
   0.0001303951,
   0.0001948344};
   TGraphErrors *gre = new TGraphErrors(10,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(40);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(40);
   gre->SetMarkerStyle(27);
   gre->SetMarkerSize(1.4);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","Graph",100,0.203,28.367);
   Graph_Graph01001->SetMinimum(0.1182155);
   Graph_Graph01001->SetMaximum(0.1386931);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("ps");
   
   TPaveText *pt = new TPaveText(0.4348424,0.94,0.5651576,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetLineWidth(2);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("h1 title");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
