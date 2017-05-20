#ifndef __readMasterFile__HH__
#define __readMasterFile__HH__
#include <fstream>
#include <map>
class masterFile{
protected:
  ifstream file;
public:
  void leerArchivo(std::string file);
  std::vector<std::string> quitarCaracteres(std::string line);
};
#include "readMasterFile.hxx"
#endif
