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
    exit(0);//по условиям задания
  }
}

void ConverterJSON::SetObjEvent(MyEvent* ptr){
  assert(ptr != nullptr);
  pEvent = ptr;
}

void ConverterJSON::SetObjServ(Server* ptr){
  assert(ptr != nullptr);
  pServ = ptr;
}

void ConverterJSON::ReadTextfile(const char* fname){
  MyException myexcep;
  myexcep.SetObjEvent(pEvent);
  assert(fname != nullptr);
  try{
    ifstream f(fname);
    myexcep.filExist();
  }catch(char const * error){
    
    cout << myexcep.errors();
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

// void ConverterJSON::Hello(){
//   cout << "Hello from class ConverterJSON!\n";
// }

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
        // cout << temp << endl;
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

void ConverterJSON::Answers(vector<vector<RelativeIndex>>& ridx){
  const char* fname = "answers.json";
  TouchFile(fname);

  jAnswJSON = {{"answers",{}}};
  json jfield;
  json::iterator it = jAnswJSON.begin();
  size_t vecInd = 0;//для формирования ответов из результатов vecRelIdx
  //число ответов
  size_t i, ind;
  ind = 1;
  for(auto &vec : ridx){
  string field = "request";
    //request001 request 002 ... lambda
        field += [ind](){
      string temp;
      temp = to_string(ind);
      if(temp.length() == 1){
        temp.clear();temp += "00";temp += to_string(ind);
      }else if(temp.length() == 2){
        temp.clear();temp += "0";temp += to_string(ind);
      }else if(temp.length() == 3){
        temp.clear();temp += to_string(ind);}
      return temp;
    }();
    it.value().push_back(field);
    jfield[field] = it.value();
    field.clear();

    if(vec.size() > 0){    
        json jb = { "result" , true };
      it.value().push_back(jb);

      json j;
      json jr;
      json::iterator itRel = jr.begin();
      size_t i = 0;

      for(auto &r : vec){  
    j[i] = {{"doc_id",r.doc_id},{"rank",r.rank}};
    jr["relevance"] = j;
    ++i;
    }
    it.value().push_back(jr);
    }else{
     json jb = { "result" , false };
      it.value().push_back(jb);

    }
    ++ind;
  }

  SaveJSON(jAnswJSON,fname);
}

void ConverterJSON::ParamApp(){
  // shrdPtrServ.get()->Start();
  // shrdPtrServ.get()->AppReady();
}

// void ConverterJSON::SetObjServ(shared_ptr<Service> _shrdPtrServ){
  // shrdPtrServ = _shrdPtrServ;
// }