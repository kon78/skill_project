#include"convjson.h"
#include"myexception.h"

void ConverterJSON::ReadJsonfile(const char* fname){
  // MyException myexcep;
  assert(pExcep != nullptr);
  assert(fname != nullptr);
  try{
    pExcep->SetFName(fname);
    ifstream f(fname);
    pExcep->filExist();
    jData = json::parse(f);
  }catch(char const * error){
    cout << pExcep->errors();
    exit(0);//по условиям задания
  }
}

void ConverterJSON::SetObjEvent(MyEvent* ptr){
  assert(ptr != nullptr);
  pEvent = ptr;
}

void ConverterJSON::SetObjExcep(MyException* ptr){
  assert(ptr != nullptr);
  pExcep = ptr;
}

void ConverterJSON::SetObjServ(Server* ptr){
  assert(ptr != nullptr);
  pServ = ptr;
}

void ConverterJSON::ClearAnswers(){
  jAnswJSON.clear();
}

void ConverterJSON::ReadTextfile(const char* fname){
  // MyException myexcep;
  bool res;
  pExcep->SetObjEvent(pEvent);
  assert(fname != nullptr);
  try{
    ifstream f(fname);
    res = pExcep->filExist();
  }catch(char const * error){
    
    cout << pExcep->errors();
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

void ConverterJSON::ClearRequest(){
  jRequestsJSON.clear();
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
  bool fexist=true;
  bool bEnglWrds=false;
  string key = "requests";
  assert(fname != nullptr);
  try{
    fexist = pExcep->readjson(fname);
  }catch(char const * error){
    cout << pExcep->errors();
  }
  if(!fexist){
    json::iterator itReq;
    fstream fp;
    string temp;
    fp.open(fname, ios::in);
    if(fp.is_open()){
      itReq = jRequestsJSON.find(key);
      assert(itReq != jRequestsJSON.end());
      while(!fp.eof()){
        getline(fp,temp);
        try{
          bEnglWrds = pExcep->ReadRequests(temp);
          if(!bEnglWrds)
            itReq.value().push_back(temp);
        }catch(const char* error){
          cout << pExcep->errors();
        }
      }
      temp.clear();
      SaveJSON(jRequestsJSON, "requests.json");
    }
    else{
      cout << "file not open!\n";
    }
  }
}

vector<string>& ConverterJSON::GetRequest(){
  const char* fname = "requests.json";
  ReadJsonfile(fname);

  string key = "requests";
  json::iterator itReq;
  
  if(vReq.size() > 0)
    vReq.clear();

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
  // size_t vecInd = 0;//для формирования ответов из результатов vecRelIdx
  //число ответов
  // size_t i, ind;
  size_t ind;
  // size_t ind=0;
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
      // assert(pServ != nullptr);
      size_t maxRespFls = (pServ->GetResponse() - 1);
      size_t i = 0;
      for(auto &r : vec){  
    j[i] = {{"doc_id",r.doc_id},{"rank",r.rank}};
    jr["relevance"] = j;
    ++i;

    if(i > maxRespFls){
      break;
    }else if(vec.size() < maxRespFls){
      continue;
    }else{
      continue;
    }
    
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