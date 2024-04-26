/**
 * @file   tests/DrawStyles.C
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Aug 14 13:52:24 2014
 * 
 * @brief  An (X,Y) graph with configurable errors - Tests
 * 
 * Copyright (c) 2014 Christian Holm Christensen. 
 *
 * Licensed under the LGPL- 3
 */
//=== A Test =========================================================
#ifndef DRAWSTYLES_C
#define DRAWSTYLES_C
#ifndef __CINT__
# include <TRandom.h>
# include <TH1.h>
# include <TCanvas.h>
# include <TLegend.h>
#endif
#ifdef __CLING__
# include "GraphSysErr.C"
# include "TestMaker.C"
#endif
class GraphSysErr;
class TestMaker;

/**
 * A test of GraphSysErr
 * 
 * @image html GraphSysErr.png
 */
struct Drawer
{
  Drawer(GraphSysErr* g)
    : gse(g)
  {
  }
  /** 
   * Make a canvas
   * 
   * @param n Name of canvas
   * @param t Title of canvas 
   * 
   * @return Pointer to canvas 
   */
  TVirtualPad* MakeCanvas(const char* n, const char* t)
  {
    TCanvas* c = new TCanvas(n, t, 1200, 900);
    c->SetTopMargin(0.02);
    c->SetRightMargin(0.02);
    c->cd();

    return c;
  } //EndMakeCanvas
  /** 
   * Draw our data 
   * 
   * @param p Pad to drawn in 
   * @param option Draw option
   * @param fit if true, fit a gaus
   */
  void DrawIt(TVirtualPad* p, Option_t* option, Bool_t fit=false) 
  {
    p->SetTopMargin(0.02);
    p->SetRightMargin(0.02);
    gStyle->SetOptTitle(0);
    Sizes();

    // If we're to fit, do so, otherwise just draw
    // Note that the same drawing options are used 
    TFitResultPtr r;
    if (!fit) 
      gse->Draw(option);
    else 
      r = gse->Fit("gaus", "SQ", option, -3, 3);
    gse->GetMulti()->GetXaxis()->SetTitle("X");
    gse->GetMulti()->GetYaxis()->SetTitle("P(X)");

    // Make a legend from canvas content 
    TLegend* l = p->BuildLegend(.12, .7, .4, .97);
    l->SetFillColor(0);
    l->SetFillStyle(0);
    l->SetBorderSize(0);

    // Show our drawing options 
    TLatex* ltx = new TLatex(.02,.02,option);
    ltx->SetTextAlign(11);
    ltx->SetTextFont(42);
    ltx->SetTextSize(0.03);
    ltx->SetNDC();
    ltx->Draw();

    // Check have a fit, and put stuff on canvas 
    if (fit) {
      Double_t y  = .97;
      Double_t x1 = .6;
      Double_t x2 = .75;
      Double_t x3 = .76;
      TLatex* name = new TLatex(x1, y, "#chi^{2}/#nu");
      name->SetTextAlign(13);
      name->SetTextFont(62);
      name->SetTextSize(0.02);
      name->SetNDC();
      name->Draw();
      TLatex* value = new TLatex(x2, y, "");
      value->SetTextAlign(33);
      value->SetTextFont(42);
      value->SetTextSize(0.02);
      value->SetNDC();
      value->Draw();
      TLatex* error = new TLatex(x2, y, Form("%7.4f", r->Chi2()/r->Ndf()));
      error->SetTextAlign(13);
      error->SetTextFont(42);
      error->SetTextSize(0.02);
      error->SetNDC();
      error->Draw();
      y -= error->GetTextSize() + .01;
      
      for (Int_t i = 0; i < r->NPar(); i++) {
	name->DrawLatex(x1,y,r->ParName(i).c_str());
	value->DrawLatex(x2,y,Form("%7.4f",r->Parameter(i)));
	error->DrawLatex(x3,y,Form("#pm %8.5f",r->ParError(i)));
	y -= error->GetTextSize() + .01;
      }
    }
    // Make sure the canvas is updated 
    p->Modified();
    p->Update();
    p->cd();
  } // EndDrawIt
  /** 
   * Set the default sizes of the error along X (if not specified) and
   * the tick sizes using the global TStyle
   */
  void Sizes()
  {
    // Adjust size along X of common errors 
    gStyle->SetErrorX(.2);
    // Adjust size of hat, cap, ...
    gStyle->SetEndErrorSize(6);
  } //EndSizes
  /** 
   * Draw all examples
   * 
   */
  void DrawAll()
  {
    TVirtualPad* p = MakeCanvas("all", "All Tests");
    p->Divide(3,2);
    
    TVirtualPad* q = 0;

    // Draw our data in various ways 
    q = p->cd(1); DrawCombined(q);
    q = p->cd(2); DrawStack(q);
    q = p->cd(3); DrawCombinedCommonStat(q);
    q = p->cd(4); DrawStackCommonStat(q);
    q = p->cd(5); DrawStackStat(q);
    q = p->cd(6);

    // Put a description 
    TPaveText* txt = new TPaveText(0.02,0.02,.95,.95,"NB NDC");
    txt->SetFillColor(0);
    txt->SetFillStyle(0);
    txt->SetTextFont(42);
    txt->SetTextAlign(11);
    txt->SetBorderSize(0);
    txt->AddText("#bf{GraphSysErr}");
    txt->AddText("A TGraph-like object with separate statistical");
    txt->AddText("and systematic errors.  Many options for drawing");
    txt->AddText("the data, and full configurability of styles.");
    txt->AddText("Data can be exported to a file suitabile for");
    txt->AddText("upload to the Durham database with minimal editting");
    txt->AddText("");
    txt->AddText("#it{Christian Holm Christensen}");
    
    txt->Draw();
    
    
    p->Print("DrawStyles.png");
  } //EndDrawAll
  /** 
   * Fit and Draw the data with options 
   *
   * - COMBINED - all selected errors are added up in quadrature 
   * - axis     - Draw axis 
   * - quad     - Add errors in quadrature (rather then directly)
   * - max      - Common errors are show near maximum of graph 
   */
  void DrawCombined(TVirtualPad* p=0)
  {
    if (!p) p = MakeCanvas("combined", "Combined");
    else    p->SetTitle("Combined");
    
    DrawIt(p, "COMBINE axis quad max", true);;
  } // EndDrawCombined
  /** 
   * Draw the data with options 
   *
   * - STACK    - Cumulative display of selected errors 
   * - axis     - Draw axis 
   * - quad     - Add errors in quadrature (rather then directly)
   * - min      - Common errors are show near minimum of graph 
   * - west     - Common errors are drawn to the west 
   */
  void DrawStack(TVirtualPad* p=0)
  {
    Sizes();
    if (!p) p = MakeCanvas("stack","Stack");
    else    p->SetTitle("Stack");

    DrawIt(p, "STACK axis quad split min west");
  } // EndDrawStack
  /** 
   * Draw the data with options 
   *
   * - COMBINED - all selected errors are added up in quadrature 
   * - COMMON   - Add common errors to points
   * - STAT     - Add statistical errors to systematic errors
   * - axis     - Draw axis 
   * - quad     - Add errors in quadrature (rather then directly)
   *
   * We also change the draw option of combined errors from a hat to
   * boxes.
   */
  void DrawCombinedCommonStat(TVirtualPad* p=0)
  {
    if (!p) p = MakeCanvas("combinedCommonStat","Combined,Common,Stat");
    else    p->SetTitle("Combined,Common,Stat");

    gse->SetSumFillColor(kPink+2);
    gse->SetSumFillStyle(3002);
    gse->SetSumOption(GraphSysErr::kBox);

    DrawIt(p, "COMBINED COMMON STAT axis quad");
  } // EndDrawCombinedCommonStat
  /** 
   * Fit and Draw the data with options 
   *
   * - STACK    - Cumulative display of selected errors 
   * - COMMON   - Add common errors to points
   * - STAT     - Add statistical errors to systematic errors
   * - axis     - Draw axis 
   * - quad     - Add errors in quadrature (rather then directly)
   */
  void DrawStackCommonStat(TVirtualPad* p=0)
  {
    if (!p) p = MakeCanvas("stackCommonStat","Stack, Common, Stat");
    else    p->SetTitle("Stack, Common, Stat");

    DrawIt(p, "STACK COMMON STAT axis quad", true);;
  } // EndDrawStackCommonStat
  /** 
   * Fit & Draw the data with options 
   *
   * - STACK    - Cumulative display of selected errors 
   * - STAT     - Add statistical errors to systematic errors
   * - axis     - Draw axis 
   * - quad     - Add errors in quadrature (rather then directly)
   * - split    - Common errors shown individually (rather than cumulative)
   * - max      - Common errors shown nead graph maximum
   */
  void DrawStackStat(TVirtualPad* p=0)
  {
    if (!p) p = MakeCanvas("stackStat","Stack,Stat");
    else    p->SetTitle("Stack,Stat");

    DrawIt(p, "STACK STAT axis quad split max", true);;
  } // EndDrawStackStat
    
  // Our data
  GraphSysErr* gse;
};
#endif

void 
DrawStyles()
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C(1,0)");

  Drawer t(TestMaker::MakeGaus());
  t.DrawAll();
} // EndDrawStyles
// 
// EOF
// 
