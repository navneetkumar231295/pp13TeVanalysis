/**
 * @file      tests/TestJSON.C
 * @copyright Christian Holm Christensen
 * @brief     Part of the GraphSysErr test suite
 */
GraphSysErr* TestJSON(const char* file="inputs/kstar_pt.input"
		      //"inputs/dndeta_pa.input"
		      ,
		      Int_t idx=0
		      )
{
  TSeqCollection* c = GraphSysErr::Import(file);
  GraphSysErr*    g = static_cast<GraphSysErr*>(c->At(idx));

  std::ofstream out("foo.json");
  g->ToJSON(out);
  out.close();

  g->Print("all");
  g->ToJSON(std::cout);
  return g;
}
