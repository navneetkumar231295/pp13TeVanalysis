/**
 * @file      tests/ToJson.C
 * @copyright Christian Holm Christensen
 * @brief     Part of the GraphSysErr test suite
 */
#include <iostream>
#include <TCollection.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TKey.h>
#include "GraphSysErr.C"
#include <iostream>
#include <string>

bool Sub(std::ostream& out, TDirectory* d, const std::string& ind);
bool Sub(std::ostream& out, TCollection* d, const std::string& ind);

bool Obj(std::ostream& out, TObject* o, const std::string& ind, bool comma)
{
  if (o->IsA() == GraphSysErr::Class()) {
    if (comma) out << ",";

    out << "\n";
    GraphSysErr* g = static_cast<GraphSysErr*>(o);
    g->ToJSON(out, false, ind.c_str());

    return true;
  }
  if (o->InheritsFrom(TCollection::Class())) {
    out << "\n" << ind << "\"" << o->GetName() << "\": ";
    return Sub(out,static_cast<TCollection*>(o), ind);
  }
  else if (o->InheritsFrom(TDirectory::Class())) {
    out << "\n" << ind << "\"" << o->GetName() << "\": ";
    return Sub(out,static_cast<TDirectory*>(o), ind);
  }
  return false;
}

bool Sub(std::ostream& out, TDirectory* d, const std::string& ind)
{
  std::string sub = ind + "  ";
  out << ind << "{";
  bool comma = false;
  
  TList* keys = d->GetListOfKeys();
  keys->Sort();
  
  for (auto ok : *keys) {
    TKey*    k  = static_cast<TKey*>(ok);
    TObject* ov = k->ReadObj();

    if (Obj(out, ov, sub, comma))
      comma = true;
  }
  out << "\n" << ind << "}";
  return comma;
}

bool Sub(std::ostream& out, TCollection* d, const std::string& ind)
{
  std::string sub = ind + "  ";
  out << ind << "{";
  bool comma = false;
  
  for (auto ov : *d) {
    if (Obj(out, ov, sub, comma))
      comma = true;
  }
  out << "\n" << ind << "}";
  return comma;
}

void ToJson(const char* filename)
{
  TFile*          file = TFile::Open(filename,"READ");

  Sub(std::cout, file, "");

  std::cout << std::endl;
}


#ifdef MAIN
int main(int argc, char** argv)
{
  ToJson(argv[1]);

  return 0;
}

#endif
//
// EOF
//
