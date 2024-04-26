/**
 * @file      tests/SplitInput.C
 * @copyright Christian Holm Christensen
 * @brief     Part of the GraphSysErr test suite
 */
#include <fstream>
#include <TError.h>
#include <TString.h>

/** 
 * Split a Durham formatted Input file into several files - one for
 * each dataset in the input.  The header is copied to each file. 
 * 
 * @param file File to split 
 */
void
SplitInput(const char* file, 
	   Bool_t includeHeader=true,
	   Bool_t preserveComments=false)
{
  TString base(file);
  base.ReplaceAll(".input", "");
  base.ReplaceAll(".txt",   "");

  std::ifstream in(file);
  if (!in) { 
    Error("SplitInput", "Failed to open %s", file);
    return;
  }

  Int_t          cnt      = 0;
  TString        header   = "";
  std::ofstream* cur      = 0;
  TString        curName  = "";
  do { 
    TString line;
    line.ReadLine(in);
    if (!preserveComments && line[0] == '#') continue; // Kill comment lines 
    if (line.BeginsWith("*dataset:")) {
      if (!cur) { 
	curName = Form("%s_%03d.input", base.Data(), cnt);
	cnt++;
	cur = new ofstream(curName.Data());
	if (!cur) { 
	  Error("SplitIput", "Failed to open %s", curName.Data());
	  return;
	}
      }
      if (includeHeader) *cur << header << std::endl;
      *cur << line << std::endl;
      continue;
    }
    else if (line.BeginsWith("*dataend:")) { 
      if (!cur) { 
	Error("SplitInput", "No current file");
	return;
      }
      *cur << line << std::endl;
      cur->close();
      delete cur;
      cur = 0;
      continue;
    }
    if (cur) 	
      *cur << line << std::endl;
    else {
      if (!header.IsNull()) header.Append("\n");
      header.Append(line);
    }
  } while (!in.eof());
  Info("SplitInput", "Wrote %d files", cnt);
}
// 
// EOF
// 
