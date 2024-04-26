/**
 * @file      tests/ManyTables.C
 * @copyright Christian Holm Christensen
 * @brief     Part of the GraphSysErr test suite
 */
//
// This test reads in a number of tables from an input file,
// and then draws them 
//
#ifdef __CLING__
# include "GraphSysErr.C"
#endif

void
ManyTables(const char* fileName="inputs/arxiv_1412.6828.input",
	   Bool_t fix=true)
{
  if ((gROOT->GetVersionCode() >> 16) < 6)
    gROOT->Macro("tests/Load.C");

  TSeqCollection* l = GraphSysErr::Import(fileName);

  TList        tables;
  TIter        next(l);
  GraphSysErr* gse = 0;
  while ((gse = static_cast<GraphSysErr*>(next()))) {
    TString nme(gse->GetName());
    nme.Remove(0,3);
    TObjArray*  tokens = nme.Tokenize("_");
    TObjString* sIdx   = static_cast<TObjString*>(tokens->At(0));
    TObjString* sSub   = static_cast<TObjString*>(tokens->At(1));
    Int_t       idx    = sIdx->String().Atoi();
    Int_t       sub    = sSub->String().Atoi();
    delete tokens;
    
    TList* table = static_cast<TList*>(tables.At(idx));
    if (!table) {
      tables.AddAt(table = new TList, idx);
      table->SetName(Form("table_%02d", idx));
      // table->SetTitle(gse->GetTitle());
    }
    table->AddAt(gse, sub);
    gse->SetMarkerColor(sub+1);
    if (!fix) continue;
    TString   qual  = gse->GetQualifier(gse->GetXTitle());
    TString   ytit  = gse->GetYTitle();
    // Int_t     colon = qual.Index(":");
    // if (colon != kNPOS) qual.Remove(0, colon+1);
    gse->SetYTitle(qual);
    gse->AddQualifier("centrality", ytit);
    gse->RemoveQualifier(gse->GetXTitle());
  }
  // tables.ls();

  TString again(fileName);
  again.ReplaceAll(".input", "_again.input");
  std::ofstream out(again.Data());
  TIter nextL(&tables);
  TList* table = 0;
  Bool_t first = true;
  while ((table = static_cast<TList*>(nextL()))) {
    TCanvas* c = new TCanvas(table->GetName(), "");
    TIter nextG(table);
    GraphSysErr* gse = 0;
    Bool_t one = true;
    while ((gse = static_cast<GraphSysErr*>(nextG()))) {
      TString opt("STACK STAT QUAD SPLIT");
      if (one) opt.Append(" AXIS");
      gse->Draw(opt);
      TString ytit(gse->GetYTitle());
      if (one) {
	gse->GetMulti()->GetHistogram()->SetMinimum(0);
	gse->GetMulti()->GetHistogram()->SetMaximum(ytit[0] == 'Q' ? 2 : 65);
      }
      one = false;
      // std::ofstream s(gse->GetName());
      // gse->Export(false, s);
      gse->Save(Form("%s.C", gse->GetName()));
    }
    TString opt(first ? "h" : "");
    GraphSysErr::Export(table, out, opt);
    first = false;
  }
  out.close();
}
      
    
