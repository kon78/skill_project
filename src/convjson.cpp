#include"convjson.h"
#include"myexception.h"

void ConverterJSON::ReadJsonfile(const char* fname){
  MyException myexcep;
  assert(fname != nullptr);
  myexcep.SetFName(fname);
  try{
    ifstream f(fname);
    myexcep.filExist();
    jData = json::parse(f);
  }catch(char const * error){
    cout << myexcep.errors();
    exit(0);
  }
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
  for(size_t ind = 0; ind < itReq.value().size(); ++ind){
    vReq.push_back(itReq.value()[ind]);

  }
  return vReq;
}

void ConverterJSON::ParamApp(){
  // shrdPtrServ.get()->Start();
  // shrdPtrServ.get()->AppReady();
}

// void ConverterJSON::SetObjServ(shared_ptr<Service> _shrdPtrServ){
  // shrdPtrServ = _shrdPtrServ;
// }