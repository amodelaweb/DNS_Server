#ifndef __MASTERFILE__HXX__
#define __MASTERFILE__HXX__

#include "readMasterFile.h"

/*=============================================================================================================================*/
std::map<std::string, std::string> DNS::MasterFile::ReadFile(std::string file){
  std::ifstream myfile(file);
  std::map<std::string, std::string> r;
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
        std::vector<std::string> data=EraseCharacters(line);
        for(int i=0;i<data.size();i++){
          if(data[i+1][data[i+1].size()-1] == 13){
            data[i+1].erase(data[i+1].size() - 1, data[i+1].size());
          }
          r.insert(std::pair<std::string,std::string>(data[i],data[i+1]));
          i++;
        }
      }
    }
  }
  else{
    return r;
  }
  return r;
}
/*=============================================================================================================================*/
std::vector<std::string> DNS::MasterFile::EraseCharacters(std::string line){
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
/*=============================================================================================================================*/
#endif
