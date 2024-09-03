#include"search.h"

void SearchServer::SetObjServ(shared_ptr<Service> _shrdPtrServ){
  shrdPtrServ = _shrdPtrServ;  
}

void SearchServer::SetObjInvInd(InvertedIndex* _shrdPtrInvInd){
  ptrInvInd = _shrdPtrInvInd;
}

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& queries_input){
  vector<vector<RelativeIndex>> ret;
  unordered_map<std::string, int> filterWords;
  MyMapTh::iterator itMapIdx = uMapIdx.get()->begin();
  MyMapTh::iterator itMapIdxEnd = uMapIdx.get()->end();
  MyVectorTh value;
    for(auto &qi : queries_input)
      filterWords[qi] = qi.length();//нужны только уникальные ключи
  
  
  //vector уникальных слов pair<word,count>
  vector<pair<string,size_t>>uniqueWords;
  vector<string>vecUncnownWord;
  size_t doc_id;
  for(auto& m : filterWords){
    itMapIdx = uMapIdx.get()->find(m.first);
    if(itMapIdx == itMapIdxEnd){
      vecUncnownWord.push_back(m.first);//неизвестные слова
      continue;}    

    value = itMapIdx->second;
    // uniqueWords.push_back(make_pair(m.first,value[1].count));
    uniqueWords.push_back(make_pair(m.first,[value](){
    size_t count = 0;
      for(auto &v : value)
        count += v.count;
        return count;
}() ));
  }

  sort(
    uniqueWords.begin(),
    uniqueWords.end(),
    [](const auto& p1, const auto& p2){
      return tie(p2.second, p1.first) > tie(p1.second, p2.first);
    }
  );

//вывод содержимого вектора на экран
#if(do_this == execute)
  vector<pair<string,size_t>>::iterator itVecUW;
      for(itVecUW = uniqueWords.begin(); itVecUW != uniqueWords.end(); ++itVecUW){
        std::cout << itVecUW->first << " ";
        std::cout << itVecUW->second << '\n';
    }
#endif

  vector<pair<string,vector<vector<size_t>>>>uniqueWordsDocID;
  cout << "size vec is " << uniqueWords.size() << endl;
  for(auto &v : uniqueWords){
    itMapIdx = uMapIdx.get()->find(v.first);
    value = itMapIdx->second;
    uniqueWordsDocID.push_back(make_pair(v.first,[value](){
      vector<vector<size_t>>vec;
      vector<size_t>vecInner;
      for(auto& v : value){
        vecInner.push_back(v.doc_id);
      }
      vec.push_back(vecInner);
      vecInner.clear();
      return vec;
    }() ));
  }

  vector<pair<string,vector<vector<size_t>>>>::iterator itUWDID;
  for(itUWDID = uniqueWordsDocID.begin(); itUWDID != uniqueWordsDocID.end(); ++itUWDID){
    cout << itUWDID->first << " ";
    for(auto &v : itUWDID->second){
      for(auto &vIn : v){
        cout << vIn << " ";
      }
      cout << endl;
    }
  }



  return ret;
}


//можно обращаться к коллекции и через обычный указатель
void SearchServer::search1(){
  map<string, vector<EntryThreads>>& mapInvInd = ptrInvInd->GetMap();
  MyMapTh::iterator itK = mapInvInd.begin();
  string strSrch = "milk";
  // try{
  //   itK = mapInvInd->find(strSrch);
  // }catch(exception &ex){
  //   cout << "can't find in object map\n" << ex.what() << endl;
  // }
  cout << "key " << itK->first << "\nvalue ";
  // cout << "size map is " << editM.MapSize(*uMapIdx);//выдает неверный результат - отказаться!!!
  cout << "size value is " << itK->second.size() << endl;
  MyVectorTh value;
  value = itK->second;
    for(int i = 0; i < value.size(); i++){
      cout << "{";
      cout << value[i].doc_id << "," << value[i].count << "}";
    }  

  json j = shrdPtrServ->GetRequests();
  // cout << "request is " << j << endl;
  json::iterator it = j.begin();
  cout << "key " << it.key() << " value ";
  size_t jsize = it.value().size();
  for(size_t ind = 0; ind < jsize; ++ind){
    cout << it.value()[ind] << " ";
  }
  cout << endl;
}

void SearchServer::GetInvIndMap(){
    map<string, vector<EntryThreads>>& mapInvInd = ptrInvInd->GetMap();
    // size_t sizeMap;
  // try{
    // sizeMap = mapInvInd.size();
    uMapIdx = make_unique< map<string, vector<EntryThreads>> >(mapInvInd);
    size_t sizeMap = uMapIdx.get()->size();
    cout << "size map is " << sizeMap << endl;
    // }catch(exception &ex){
      // cout << "can't do this!" << ex.what() << endl;
  // }
}

/*
        try{
         filExist(temp);
      } catch (exception &ex){
          cout << "file " << temp << ". " << ex.what() << "!\n";
      }
*/

void SearchServer::ReadRequests(){
#if(do_this == do_not)
  shared_ptr<ifstream> fin;
  char buff[255];
  fin = make_shared<ifstream>("..\\requests.json",ios::in);
  fin.get()->read(buff, sizeof(buff));
  string strData(buff);
  cout << strData << endl;
  //out to console --> pck
  exit(0);

  //zavis
  std::ifstream f("..\\requests.json");
  f.clear();
  f.seekg(0,ios::beg);
  char buff[255];
  while(!f.eof()){
  f.getline(buff,sizeof(buff));
  }
  string str(buff);
  cout << str << endl;
#endif

  // json data = json::parse(fin.get()->read(buff, sizeof(buff)));


  try{
    ifstream f("c:\\skill_project\\build\\requests.json");
    // requests = json::parse(f);

    }catch(exception &ex){
      cout << "can't read or find file " << "requests.json" << endl;
  string ret;
  string path = "C:\\develop\\skill_project";
  for(auto &p : fs::directory_iterator(path)){
    ret += p.path().filename().generic_string();
    ret += " ";
  }
  cout << ret << endl;

  }
  // if(f.is_open()){
  // }else{
  // }
  json data;
  json::iterator it = data.begin();

  try{
    string strTRY = it.key();
  }catch(exception &ex){
    cout << "problems withs json-object requests!\n";
    exit(0);
  }

    cout << "key " << it.key() << " | value: ";
  for(size_t ind = 0; ind < data.size(); ++ind){
    cout << it.value() << " ";
  }
}