#ifndef __readMasterFile__HH__
#define __readMasterFile__HH__
#include <fstream>
#include <map>
#include <vector>
class MasterFile{

public:
  MasterFile()= default;
  std::map<std::string, std::string> leerArchivo(std::string file);
  std::vector<std::string> quitarCaracteres(std::string line);
};
#include "readMasterFile.hxx"
#endif
