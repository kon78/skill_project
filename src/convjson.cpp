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

void ConverterJSON::Hello(){
  cout << "Hello from class ConverterJSON!\n";
}

void ConverterJSON::prepareReqFile(){
  cout << "Prepare file requests.json!\n";
  jRequestsJSON = {
    {"requests",{
    }
    }
  };
}

void ConverterJSON::ViewJSON(){
  cout << jRequestsJSON << endl;
}

void ConverterJSON::TouchFile(const char* fname){
  assert(fname != nullptr);
  fout = make_shared<ofstream>(fname,ios::out);
}

void ConverterJSON::SaveJSON(json& j2f, const char* fname){
  assert(fname != nullptr);
  TouchFile(fname);
  string temp = j2f.dump();
  const char* str = temp.c_str();
  fout.get()->write(str,temp.length());
  fout.get()->close();
}

void ConverterJSON::PrepareQueries(const char* fname){
  MyException myexcep;
  bool fexist;
  string key = "requests";
  assert(fname != nullptr);
  try{
    fexist = myexcep.readjson(fname);//bool MyException::readjson();
  }catch(char const * error){
    cout << myexcep.errors();
  }
  if(!fexist){
    json::iterator itReq;
    fstream fp;
    string temp;
    // string path = "..\\skill_project\\";
    // path += fname;
    fp.open(fname, ios::in);
    if(fp.is_open()){
      itReq = jRequestsJSON.find(key);
      assert(itReq != jRequestsJSON.end());
      while(!fp.eof()){
        getline(fp,temp);
        cout << temp << endl;
        itReq.value().push_back(temp);
      }
    }
    else{
      cout << "file not open!\n";
    }
  }
}

vector<string>& ConverterJSON::GetRequest(){
  string key = "requests";
  json::iterator itReq;
  itReq = jRequestsJSON.find(key);
  assert(itReq != jRequestsJSON.end());
  // string valueS;
  for(size_t ind = 0; ind < itReq.value().size(); ++ind){
    // valueS = itReq.value()[ind];
    vReq.push_back(itReq.value()[ind]);

  }
  // string valueS = itReq.value();
  // SearchSubStrng clSubStr(s,"");

  // for(auto &s : clSubStr.GetVec())

  return vReq;
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