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
    std::multimap<std::string, std::string>  r ;
  public:
    MasterFile()= default;
    bool ReadFile(std::string file);
    std::vector<std::string> EraseCharacters(std::string line);
    std::multimap<std::string, std::string> getRecords();
  };
}
#include "MasterFile.hxx"
#endif
