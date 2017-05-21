#ifndef __MASTERFILE__HXX__
#define __MASTERFILE__HXX__

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
    std::map<std::string, std::string> leerArchivo(std::string file);
    std::vector<std::string> quitarCaracteres(std::string line);
  };
}
#include "readMasterFile.hxx"
#endif
