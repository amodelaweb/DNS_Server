#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;
vector<string> quitarCaracteres(string line){
  vector<string> v;
  string s="";
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
void leerArchivo(ifstream &myfile){
  string line;
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
      vector<string> data=quitarCaracteres(line);
      for(int i=0;i<data.size();i++){
        cout<<data[i]<<endl;
      }
    }
  }
}
int main ()
{
  ifstream myfile("ip.txt");
  if(myfile.is_open()==true){
    leerArchivo(myfile);
  }
  return 0;
}
