#ifndef __MASTERFILE__H__
#define __MASTERFILE__H__

#include <fstream>
#include <map>
#include <vector>
/*
* Archivo de texto desde donde se obtiene los
* nombres de los sitios web.
*/
namespace DNS{
  class MasterFile{

  public:
    MasterFile()= default;
    std::multimap<std::string, std::string> ReadFile(std::string file);
    std::vector<std::string> EraseCharacters(std::string line);
  };
}
#include "readMasterFile.hxx"
#endif
