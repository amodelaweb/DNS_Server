#ifndef __readMasterFile__HXX__
#define __readMasterFile__HXX__
#include "readMasterFile.h"
void masterFile::leerArchivo(std::string file){
  ifstream myfile(file);
  if(myfile.is_open()==true){
    std::string line;
    while(getline(myfile,line)){
      int x=0;
      bool pasar=false;
      for(int i=0;i<line.size();i++){
        if(line[i]=='#'){
          pasar=true;
          break;
        }else{
          if(line[i]!=' '){
            //cout<<"->"<<line[i]<<endl;
            break;
          }
        }
      }
      if(pasar){
        continue;
      }else{
        std::vector<std::string> data=quitarCaracteres(line);
        for(int i=0;i<data.size();i++){
          cout<<data[i]<<endl;
        }
      }
    }
  }
}
std::vector<std::string> masterFile::quitarCaracteres(std::string line){
  std::vector<std::string> v;
  std::string s="";
  for(int i=0;i<line.size();i++){
    if(line[i]==' ' || line[i]==9){
      if(s!=""){
        v.push_back(s);
        s="";
      }
    }else{
      if(line[i]!='#'){
        s=s+line[i];
      }else{
        break;
      }
    }
    if(i==line.size()-1){
      v.push_back(s);
    }
  }
  return v;
}

#endif
