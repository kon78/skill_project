#include"server.h"
// #include"invertindex.h"

namespace fs = filesystem;

void Server::ArgumSet(char* argv[]){
  for(int i = 0; i < argumc; i++){
    argumv += argv[i];
    if(i != (argumc-1))
      argumv += " ";
    }
}

string Server::makeRegExpKey(){
  string ret;
  ret = "(\\/\\w)";
  return ret;
}

void Server::KeyApplication(){
  // cout << argumv << endl;
    const regex findRegCntWord(makeRegExpKey());
    std::ptrdiff_t const countWord(distance(sregex_iterator(argumv.begin(), argumv.end(), findRegCntWord),sregex_iterator()));
  sregex_iterator itrgx(argumv.begin(), argumv.end(), findRegCntWord);

    if(countWord != 0 && itrgx->str() == "/s"){
      keyApp = 103;
    }
    else if(countWord != 0 && itrgx->str() == "/r"){
      keyApp = 104;
    }else if(countWord != 0 && itrgx->str() == "/h"){
      keyApp = 105;
    }else{
      cout << "wrong key! uses only /r /h /s\n";
    }
}

void Server::examination(const string& fname){
      MyException myexcep;
      // myexcep.SetObjServ(this);
        try{
  cout << "examination file " << fname << ". ";
          startfName = myexcep.SetFName(fname);
          start = myexcep.filExist();
          start ? stop = true:stop = false;
          start ? cout << boolalpha << start << " file exist!\n":cout << endl;
      } catch (char const * error){
          cout << myexcep.errors();
      }
}

void Server::TouchFile(const char* fname){
  assert(fname != nullptr);
  fout = make_shared<ofstream>(fname,ios::out);
}

void Server::GetResourcesInfo(){
  string fname = "C:\\develop\\skill_project\\resfiles.inf";
  TouchFile(fname.c_str());
  ViewFolder(fname);
}

void Server::ViewFolder(string& fname){
  filesystem::file_time_type ftime;
  vector<string>vecFold;
  vector<pair<string,time_t>>vecFilesInfoTime;
  pair<string,time_t>prFileDate;
  string fdata;

  string path = "C:\\develop\\skill_project\\resources";
    
  for(auto &p : fs::directory_iterator(path)){
    vecFold.push_back(p.path().filename().generic_string());
    prFileDate.first = p.path().filename().generic_string();
    ftime = std::filesystem::last_write_time(p);
    auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
    prFileDate.second = cftime;
    vecFilesInfoTime.push_back(prFileDate);
  }
  
  size_t ind = 0;
  for(auto &d : vecFold){
    auto cftime = vecFilesInfoTime[ind].second;

    fdata += d + " ";
    fdata += to_string(cftime) + "\n";
    fout.get()->write(fdata.c_str(),fdata.length());
    ++ind;
    fdata.clear();
  }
  fout.get()->close();
}

void Server::ReadInfoResourcesFiles(){
  fstream fp;
  string fname = "C:\\develop\\skill_project\\resexample\\resfiles.inf";
  pair<string,time_t>prFileDate;
    string temp;
    string fn;
    fp.open(fname.c_str(), ios::in);
    if(fp.is_open()){
      while(!fp.eof()){
        getline(fp,temp);
        string::size_type pos;
        pos = temp.find(".txt");
        if(pos > temp.length()){
          continue;}
        else{
          prFileDate.first = temp.substr(0,pos+4);
          temp.erase(0,pos+4);
          prFileDate.second = stol(temp);
          vecFiles.push_back(prFileDate);
        }
      }
    }
}

void Server::EventChangedFiles(){
  cout << "EventChangedFiles()\n";
  time_t difftime;
  bool bwcf;
  filesystem::file_time_type ftime;
  string path = "C:\\develop\\skill_project\\resexample";
  while(true){
  for(auto &v : vecFiles){
  
    for(auto &p : fs::directory_iterator(path)){
      if(v.first == p.path().filename().generic_string()){
        ftime = std::filesystem::last_write_time(p);
        auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));

          try{
            difftime = cftime - v.second;            
            bwcf = pExcep->ChangedFiles(difftime);//bool was changed file
          }catch(char const * error){
            cout << pExcep->errors();
          }
        if(bwcf)
          vecChangedFiles.push_back(v.first);//если попался, то сюда
      }
    }
  }
  }
}

void Server::ReadyTest(){
  MyWaitTh();
  ThChange->detach();
  clConvJSON = new ConverterJSON();
  clConvJSON->SetObjEvent(pEvent);
  clConvJSON->SetObjExcep(pExcep);
  clConvJSON->SetObjServ(this);
  clConvJSON->ReadTextfile(fTestFile.c_str());

  // pEvent->Exceptions(pExcep);
}

bool Server::Ready(){
    KeyApplication();
    GetResourcesInfo();//resfiles.inf - информация о файлах ресурсов files001.txt и т.д. датаи время создания
    ReadInfoResourcesFiles();//данные о файлах в вектор vecFiles
    MyWaitTh();
    clConvJSON = new ConverterJSON();
    clInvInd = new InvertedIndex();
  if(!start && keyApp == 103){
      Service();
  }
  else if(!start && !stop && !startfName){
    clConvJSON->SetObjExcep(pExcep);
    clInvInd->SetObjEvent(pEvent);
    clConvJSON->ReadJsonfile(fConfJSON.c_str());
    jConf = clConvJSON->GetJSON();
    // cout << eventException << endl;
    GetConfig();
    run = true;
  }
  delete clConvJSON;
  ThChange->detach();
  return run;
}

size_t& Server::GetException(){
  return eventException;
}

void Server::listening(size_t& eventException){
  unique_lock<std::mutex> lck(global);

  while (!ready) cv.wait(lck);

  if(eventException > 0){
    // return;
    cout << "listening - was signal!\n";
    --eventException;

    if(eventException < 0)
      eventException = 0;
    }
    ready=false;
}

void Server::MyWaitTh(){
  // thread Th(listening,this,ref(eventException));
  Th = new thread(listening,this,ref(eventException));
  ThChange = new thread(EventChangedFiles,this);
  // Th->detach();
}

void Server::go(){
  std::unique_lock<std::mutex> lck(global);
  ready = true;
  cv.notify_all();
}

void Server::SetExcep(MyException* ptr){
  assert(ptr != nullptr);
  pExcep = ptr;
}

void Server::Signal(size_t event){
  ++eventException;
  if(event == 1010){
    pEvent->Exceptions(pExcep);
    // ThChange->detach();
  }
  // cout << "Signal! Working now!\n";
  pEvent->Exceptions(pExcep);
  Th->detach();
  go();
}

void Server::Service(){
  int respFiles, nf;
  string strRespFiles;
  char q;
   cout << "Creat config.json file? (y/n) :";
  while(cin >> q){
    if(q == 'y' || q == 'n')break;
      cout << "Uses key (y / n). \nRepeat enter: ";
      cin.clear();
      cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
  }

  if(q == 'n'){
    cout << "Stop service!\n";
    exit(0);}
  
  while(cout << "Number of responses :" && cin >> nf){
    if(cin.good()){
    if(nf == 0){
      respFiles = 5;
      break;
    }else if(nf < 0){
      cout << "The number of files must be positive. Repeat enter.\n";
    }else if(nf > 0){
      respFiles = nf;
      break;}
    }else{
      cin.clear();
      cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
      cout << "aborted\n";
    }
  }
  PrepareNameFilesVec();
  SaveFile(respFiles);
}

void Server::PrepareNameFilesVec(){
  string path = "C:\\develop\\skill_project\\resources";
  for(auto &p : fs::directory_iterator(path)){
    vecFNamesFoldResource.push_back(p.path().filename().generic_string());
  }
}

void Server::SaveFile(const int& respFiles){
  string strRespFiles;
  for(auto &s : vecFNamesFoldResource){
    strRespFiles += s + " ";
    }
    strRespFiles.erase(strRespFiles.length()-1);

      jConfJSON = {
      {"config",{
        {"name","SkillboxSearchEngine"},
        {"version","0.1"},
        {"max_responses",respFiles}
      },
      "files",{strRespFiles}
      }};

  ofstream fout(fConfJSON.c_str(),ios::out);
  string json2strTemp = jConfJSON.dump();
        const char* str = json2strTemp.c_str();
  fout.write(str,json2strTemp.length());
  fout.close();
}

void Server::Help(){

}

string& Server::ViewValue(json::iterator itV, string& key){
    json::iterator itj, itsJ;
    json subJ;
    json j = itV.value();
    itj = j.begin();
    while(itj != j.end()){
      if(itj.value().size() == 3){
        subJ = itj.value();
        itsJ = subJ.find(key);
        if(itsJ != subJ.end()){
          (itsJ.value().is_string() == true)?
            dataTemp = itsJ.value() : (itsJ.value().is_number_float() == true)? 
            dataTemp = to_string(itsJ.value()) : dataTemp = to_string(itsJ.value());
        break;
        }
      }
      ++itj;
    }
  return dataTemp;
}

string Server::makeRegExp(){
  string ret;
  ret = "\\w+\\.\\w+";
  return ret;
}

string& Server::ViewValueFiles(json::iterator itV, string& key){
    json::iterator itj;
    json subJ;
    json j = itV.value();
    itj = j.begin();
    while(itj != j.end()){
      if(*itj == key){
        ++itj;//до списка имен файлов
        if(itj != j.end()){
          subJ = itj.value();//string
          dataTemp = subJ.dump();
        }
      }
      ++itj;
    }
  return dataTemp;
}

void Server::EditConfig(string& s){
  string data, key;
  json::iterator it=jConf.begin();
  key = "files";
  data = ViewValueFiles(it, key);
  string::size_type pos;
  pos = data.find(s);
  data.erase(pos,s.length());
  cout << data << endl;
}

void Server::GetConfig(){
  string data, key;
  json::iterator it=jConf.begin();
  key = "max_responses"; 
  confApp.responses = stoi(ViewValue(it,key));
  key = "name";
  confApp.appName = ViewValue(it,key);
  key = "version";
  confApp.version = stod(ViewValue(it,key));
  key = "files";
  data = ViewValueFiles(it, key);

  const regex rgxSpaces (makeRegExp());
  std::ptrdiff_t const match_count(distance(sregex_iterator(data.begin(), data.end(), rgxSpaces),sregex_iterator()));
    for( sregex_iterator itrgx(data.begin(), data.end(), rgxSpaces), it_end; itrgx != it_end; ++itrgx ){
      vecFNamesFoldResource.push_back(itrgx->str());//имена файлов в вектор
    }
  data.clear();//стоку можно очистить
  numbFiles = vecFNamesFoldResource.size();//для метода void InvertedIndex::PrepareDocs()
  #if(do_this == do_not)
  for(auto &s : vecFNamesFoldResource){
    cout << s << " ";
  }
  cout << endl;
  #endif
}

vector<string>& Server::GetDocs(){
  return vecFNamesFoldResource;
}

// shared_ptr<Service>_shrdPtrServ = make_shared<Service>(argc, argv); 

// shared_ptr<InvertedIndex> Server::GetObjectInvInd(){
//   return sPtrInvInd;
// }

//TEST
void Server::SetObj(InvertedIndex* ptr){
  assert(ptr != nullptr);
  clInvIndTst = ptr;
}

void Server::SetObjEvent(MyEvent* ptr){
  assert(ptr != nullptr);
  pEvent = ptr;
}

shared_ptr< map<string,vector<EntryThreads>> > Server::GetMap(){
  refMapTh = make_shared <map<string,vector<EntryThreads>>>(clInvInd->GetMap());
  return refMapTh;
}

shared_ptr< map<string,vector<EntryThreads>> > Server::GetMapTst(){
  refMapThTst = make_shared <map<string,vector<EntryThreads>>>(clInvIndTst->GetMap());
  return refMapThTst;
}

shared_ptr< map<string,vector<Entry>> > Server::GetMap1(){
  refMap = make_shared <map<string,vector<Entry>>>(clInvInd->GetMap1());
  return refMap;
}

shared_ptr< map<string,vector<Entry>> > Server::GetMap1Tst(){
  refMapTst = make_shared <map<string,vector<Entry>>>(clInvIndTst->GetMap1());
  return refMapTst;
}

void Server::Run(){
  clSearchServ = new SearchService();
  clConvJSON = new ConverterJSON();
  clInvInd->SetObjEvent(pEvent);
  switch(keyApp){
    case (101):{
      cout << "finded key " << "/e" << endl;
      break;
    }
    case (102):{
      cout << "finded key " << "/i" << endl;
      break;
    }
    case (103):{
      cout << "finded key " << "/s" << endl;
      Service();
      break;
    }
    case (104):{
      // MyWaitTh();//будет висеть программа
      // ThChange->join();
      cout << confApp.appName << " version " << confApp.version << " run!" << endl;
        // thread Th(listening,this,ref(eventException));
      // Th.join();
      // clInvInd = new InvertedIndex();
      // sPtrInvInd = make_shared<InvertedIndex*>(clInvInd);//подклюяаем другой объект
      clInvInd->SetObjEvent(pEvent);
      clInvInd->SetObjExcep(pExcep);
      clConvJSON->SetObjEvent(pEvent);
      clConvJSON->SetObjExcep(pExcep);

      clInvInd->PrepareDocs(this);
      
        // clSearchServ->PrepareMap(clInvInd);

      while(true){//!!!!!!!!!!!!!!!!!!!!!!!!!! FALSE - STOP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        clInvInd->Hello();//для проверки, можно убрать
        
        //start here main code
        clInvInd->UpdateDocumentBase1();//запускается для тестов, записываются файлы freq_dictionary.map freq_dictionaryTh.map для проверки!!!
        clInvInd->UpdateDocumentBaseThreads();
        // clSearchServ->PrepareMap(clInvInd);
        refMapTh = GetMap();//работаем с reference map полученной от работы потоков
        if(refMapTh.get()->size() > 0){
          //разрешаем работу SearchService
          //!!!!!!!!!!!!!!!!!!!!!!!!!!!

          clSearchServ->SetObjInvInd(clInvInd);
          clSearchServ->GetInvIndDocs();
          clSearchServ->GetInvIndMap();//

          vector<vector<RelativeIndex>>result;//вектор ответов
//одиночный поиск ответов на запрос 
          // vector<string>queries={"moscow is the capital of russia"};
          // result = clSearchServ->search(queries);//result - 

          //!!!!!!!!!!!!!!!!!!!!!!!!!!!
      clConvJSON->prepareReqFile();
      const char* fname1 = "requests.txt";
      clConvJSON->PrepareQueries(fname1);
      vector<string>queries = clConvJSON->GetRequest();

      //result = clSearchServ->search(queries);

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!      
      result = clSearchServ->searchTh(queries);//поточный метод!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// vector<string> vecUncnownWord;
// size_t fieldQueries=1;
// clSearchServ->CalculateRelative(fieldQueries,queries,vecUncnownWord);


      clSearchServ->SaveVector();//для проверки глазами
      // clSearchServ->AnswersJSON();
      clConvJSON->Answers(result);//запись ответов в файл answers.json
      
      // const char* fname = "answers.json";
      // clConvJSON->TouchFile(fname);
      // clConvJSON->SaveJSON(clSearchServ->GetJson(),fname);
    }
        // refMap = GetMap1();
        
        cout << "size map freq_dictionaryTh is " << refMapTh.get()->size() << endl;
        // ThChange->detach();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // ThChange->detach();
      for(;;);
        break;
      }
      break;
    }
    case (105):{
      cout << "finded key " << "/h" << endl;
    }
    default:{
      cout << "wrong key!" << endl;
      break;
    }
  }
  

  // clConvJSON->JfileRead();
  // if(appName != nullptr){
    // string s;s.assign(appname,(sizeof(appname)/sizeof(char*)));
    // string s;s.assign(appname,(sizeof(*appname)));
  // cout << "Application " << appname << endl;

  // }
}

// bool Server::filExist(string f){
//   fileConfError = false;
//   // cout << "file is " << f << endl;
//   fstream fp;
//   fp.open(f, ios::in);
//   if(!fp.is_open()){    
//     fileConfError = true;
//     // throw runtime_error("Config file is missing");
//   }
//   return fileConfError;
// }