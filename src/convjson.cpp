#include"header.h"
#include"convjson.h"

vector<string> ConverterJSON::GetTextDocuments(){
  vector<string> ret;
  string temp;
  char result[256]{};
  string::size_type pos;

  int iCntRespFiles = shrdPtrServ.get()->numbRespFiles();

  cout << "class ConverterJSON->GetTextDocuments()\n";
  cout << "count files is " << iCntRespFiles << endl;
  temp = shrdPtrServ.get()->prepareNameFiles();
  // cout << temp << endl;
  while(iCntRespFiles != 0){
    pos = temp.find(" ");
    if(pos < temp.length()){
      temp.copy(result,pos);
      temp.erase(0,pos+1);      
      ret.push_back(string(result));
      result[0] = '\0';
    }
    --iCntRespFiles;
  }

  //printing filenames string
  // for(auto p:ret){
  //   cout << p << " ";
  // }
  // cout << endl;

return ret;
}

void ConverterJSON::ParamApp(){
  // shrdPtrServ.get()->getAddr();
  
  shrdPtrServ.get()->Start();
  shrdPtrServ.get()->AppReady();
  // pService->Start();
  // pService->AppReady();
  // pService = new Service();
}

void ConverterJSON::SetObjServ(shared_ptr<Service> _shrdPtrServ){
  shrdPtrServ = _shrdPtrServ;
}