#include"convjson.h"
#include"myexception.h"
// using namespace std;
//void ReadJsonfile(char* fname)
void ConverterJSON::ReadJsonfile(const char* fname){
  MyException myexcep;
  assert(fname != nullptr);
  myexcep.SetFName(fname);
  ifstream f(fname);
  jData = json::parse(f);
  // cout << data << endl;
}

void ConverterJSON::TestRead(const char* fname){
  assert(fname != nullptr);
  ifstream f(fname);
  jData = json::parse(f);
}

json ConverterJSON::GetJSON(){
  return jData;
}

// vector<string> ConverterJSON::GetTextDocuments(){
//   vector<string> ret;
//   string temp;
//   char result[256]{};
//   string::size_type pos;

  // int iCntRespFiles = shrdPtrServ.get()->numbRespFiles();

  // cout << "class ConverterJSON->GetTextDocuments()\n";
  // cout << "count files is " << iCntRespFiles << endl;
  // temp = shrdPtrServ.get()->prepareNameFiles();
  // cout << temp << endl;
  // while(iCntRespFiles != 0){
  //   pos = temp.find(" ");
  //   if(pos < temp.length()){
  //     temp.copy(result,pos);
  //     temp.erase(0,pos+1);      
  //     ret.push_back(string(result));
  //     result[0] = '\0';
  //   }
  //   --iCntRespFiles;
  // }

  //printing filenames string
  // for(auto p:ret){
  //   cout << p << " ";
  // }
  // cout << endl;

// return ret;
// }

void ConverterJSON::ParamApp(){
  // shrdPtrServ.get()->Start();
  // shrdPtrServ.get()->AppReady();
}

// void ConverterJSON::SetObjServ(shared_ptr<Service> _shrdPtrServ){
  // shrdPtrServ = _shrdPtrServ;
// }