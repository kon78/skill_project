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

    if(countWord != 0 && itrgx->str() == "/e"){
      keyApp = 101;
    }else if(countWord != 0 && itrgx->str() == "/i"){
      keyApp = 102;
    }else if(countWord != 0 && itrgx->str() == "/s"){
      keyApp = 103;
    }else if(countWord != 0 && itrgx->str() == "/r"){
      keyApp = 104;
    }else if(countWord != 0 && itrgx->str() == "/h"){
      keyApp = 105;
    }
    else{
      cout << "wrong key! uses only /e /i /s /r /h\n";
    }
}

void Server::examination(const string& fname){
      MyException myexcep;
        try{
  cout << "examination file " << fname << ". ";
          startfName = myexcep.SetFName(fname);
          start = myexcep.filExist();
          start ? stop = false:stop = true;
          start ? cout << boolalpha << start << " file exist!\n":cout << endl;
      } catch (char const * error){
          cout << myexcep.errors();
      }
}

void Server::TouchFile(char* fname){
  assert(fname != nullptr);
  fout = make_shared<ofstream>(fname,ios::out);
}

bool Server::Ready(){
    clConvJSON = new ConverterJSON();
    KeyApplication();
  if(!startfName){
    clConvJSON->ReadJsonfile(fConfJSON.c_str());
    jConf = clConvJSON->GetJSON();
    GetConfig();
  }else if(keyApp == 103){
    Service();
  }

  if(!stop && start && !startfName){
    run = true;
  }
  delete clConvJSON;
  return run;
}

void Server::Service(){
  int respFiles, nf;
  string strRespFiles;
  char q;
  // cout << "Creat config.json file? (y/n) :";
/*
while(std::cout << "Small Pizza Price: " && not(std::cin >> small)) {
        // if(std::cin.eof() || std::cin.bad()) {    or:
        if(std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
            std::cout << "aborted\n";
            return 1;
        }
        std::cout << "please enter a valid price\n";
        std::cin.clear();                            // clear the fail state
        // remove any lingering characters in the istream:
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }*/
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
  if(data.length() == 0){
  const regex rgxSpaces (makeRegExp());
  std::ptrdiff_t const match_count(distance(sregex_iterator(data.begin(), data.end(), rgxSpaces),sregex_iterator()));
    for( sregex_iterator itrgx(data.begin(), data.end(), rgxSpaces), it_end; itrgx != it_end; ++itrgx ){
      vecFNamesFoldResource.push_back(itrgx->str());//имена файлов в вектор
    }
  data.clear();//стоку можно очистить
  numbFiles = vecFNamesFoldResource.size();//для метода void InvertedIndex::PrepareDocs()
  }else{

  }
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
      // sPtrInvInd = make_shared<InvertedIndex>(clInvInd);//подклюяаем другой объект
        clSearchServ = new SearchService();
        clInvInd = new InvertedIndex();
        clConvJSON = new ConverterJSON();
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

      cout << confApp.appName << " version " << confApp.version << " run!" << endl;
      // clInvInd = new InvertedIndex();
      // sPtrInvInd = make_shared<InvertedIndex*>(clInvInd);//подклюяаем другой объект
      clInvInd->PrepareDocs(this);
        // clSearchServ->PrepareMap(clInvInd);
      while(true){
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
      result = clSearchServ->searchTh(queries);
      exit(0);

      clSearchServ->SaveVector();
      //запись ответов в файл
      const char* fname = "answers.json";
      clConvJSON->TouchFile(fname);
      clConvJSON->SaveJSON(clSearchServ->GetJson(),fname);
    }
        // refMap = GetMap1();
        
        cout << "size map freq_dictionaryTh is " << refMapTh.get()->size() << endl;
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