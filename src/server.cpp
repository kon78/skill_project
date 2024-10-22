#include"server.h"

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

void Server::ChangedResourcesFiles(){
  // unique_lock<std::mutex> lck(global);
  filesystem::file_time_type ftime;
  cout << "ChangedResourcesFiles()\n";
  string fileNumb;
  size_t numb;
  for(auto &f : vecChangedFiles){
    fileNumb = f;
    string::size_type pos = fileNumb.find(".txt");
    fileNumb.erase(pos,fileNumb.length());
    fileNumb.erase(0,4);
    cout << fileNumb << endl;
    if(fileNumb.length() == 3){
      //good
      numb = stoi(fileNumb);//перевод в число
      cout << vecFiles[numb-1].first << " this file was changed!\n";
      auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
      vecFiles[numb-1].second = cftime;//здесь обовляем время
      vecChngFlsNumb.push_back(numb-1);//вместо имени файла его номер
    }
    else{
      cout << "error!" << endl;
    }
  }
}


void Server::GetResourcesInfo(){
  string fname = "C:\\develop\\skill_project\\resfiles.inf";
  TouchFile(fname.c_str());
  ViewFolder(fname);
  string fNameReq = "C:\\develop\\skill_project\\requests.inf";
  TouchFile(fNameReq.c_str());
  ReadInfoRequest();
}

void Server::ReadInfoRequest(){
  filesystem::file_time_type ftime;
  string path = "C:\\develop\\skill_project";
  string fName = "requests.txt";
  // string fName = "requests.json";
  string fdata;
  pair<string,time_t>prFileDate;
  for(auto &p : fs::directory_iterator(path)){
    if(p.path().filename().generic_string() == fName){
      prFileDate.first = p.path().filename().generic_string();
      ftime = std::filesystem::last_write_time(p);
      auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
      prFileDate.second = cftime;
      tmReqFile = cftime;
      break;
    }else{
      continue;
    }
  }
  fdata = prFileDate.first + " " + to_string(prFileDate.second);
  timeReq = fdata;
  fout.get()->write(fdata.c_str(),fdata.length());
  fout.get()->close();
  fout.reset();
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
  fout.reset();
}

void Server::ReadInfoResourcesFiles(){
  fstream fp;
  string fname = "C:\\develop\\skill_project\\resfiles.inf";
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
    cout << "size vecFiles is " << vecFiles.size() << endl;
}

void Server::EventChangedRequest(){
  unique_lock<std::mutex> lck(globalReq);
  string pathReq = "C:\\develop\\skill_project\\requests.txt";
  // string pathReq = "C:\\develop\\skill_project\\requests.json";
  time_t difftime;
  filesystem::file_time_type ftime;
  while(true){
    ftime = std::filesystem::last_write_time(pathReq);
    auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
    try{
      difftime = cftime - tmReqFile;
      pExcep->ChangedFile(difftime);//bool was changed file requests.txt
    }catch(char const * error){
      brfwc = true;
      auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
      tmReqFile = cftime;//обновляем время после закрытия
      cout << pExcep->errors();
    }
  }
}

size_t Server::number_of_files_in_directory(filesystem::path path){
  return (size_t)distance(filesystem::directory_iterator{path},filesystem::directory_iterator{});
}

void Server::EventChangedNumbersFiles(){
  // cout << "EventChangedNumbersFiles() - run!\n";
  unique_lock<std::mutex> lck(globalFiles);
  string path = "C:\\develop\\skill_project\\resources";
  size_t numbFilesResources;
  // size_t memNumbFiles = number_of_files_in_directory(path);
  size_t memNumbFiles;
  // vector<string>vecFilesChanged;
  bool trigNumbFiles = true;
  while(true){
    numbFilesResources = distance(filesystem::directory_iterator{path},filesystem::directory_iterator{});
    // for(auto &p : fs::directory_iterator(path)){
    //   // if(trigNumbFiles){
    //     ++numbFilesResources;
    //     vecFilesChanged.push_back(p.path().filename().generic_string());
    //   // }
    // }

    if(trigNumbFiles)
        memNumbFiles = numbFilesResources;
    trigNumbFiles = false;

    try{

      pExcep->DiffFilesresources(numbFilesResources,memNumbFiles);
      // pExcep->DiffFilesresources(1,2);
      // numbFilesResources = 0;
      // vecFilesChanged.clear();
    }catch(char const * error){
      trigNumbFiles = true;
      // memNumbFiles = number_of_files_in_directory(path);
      cout << "was changed number files!\n";
    }
  }
  this_thread::sleep_for(10ms);
}

void Server::EventChangedFiles(){
  unique_lock<std::mutex> lckEvntChngFls(globalRes);
  time_t difftime;
  filesystem::file_time_type ftime;
  string path = "C:\\develop\\skill_project\\resources";
  string fileNumb;
  size_t numb;
  string fNameLambda;
  // size_t numbFilesResources = 0;
  // size_t memNumbFiles;
  // bool trigNumbFiles = true;

  while (!readyThResFls) cvResFiles.wait(lckEvntChngFls);

  while(true){    
  for(auto &v : vecFiles){
  
    for(auto &p : fs::directory_iterator(path)){
      // ++numbFilesResources;//считаем файлы
      if(v.first == p.path().filename().generic_string()){
        ftime = std::filesystem::last_write_time(p);
        auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
        fNameLambda = p.path().filename().generic_string();

        (numb = [&fNameLambda](){
          string fNmb;
          size_t nf;
          fNmb = fNameLambda;
          string::size_type pos = fNmb.find(".txt");
          fNmb.erase(pos,fNmb.length());
          fNmb.erase(0,4);
          if(fNmb.length() == 3)
            nf = stoi(fNmb);
          else
            nf = 1000000;//error
          return nf;
        }());

          try{
            difftime = cftime - v.second;
            pExcep->ChangedFiles(difftime,numb);//bool was changed file
            // pExcep->DiffFilesresources(numbFilesResources,memNumbFiles);//DiffFilesresources(const size_t& numb1,const size_t& numb2);
          }catch(char const * error){
            vecChangedFiles.push_back(v.first);//если попался, то сюда
            // ChangedResourcesFiles();

  for(auto &f : vecChangedFiles){
    fileNumb = f;
    string::size_type pos = fileNumb.find(".txt");
    fileNumb.erase(pos,fileNumb.length());
    fileNumb.erase(0,4);
    // cout << fileNumb << endl;
    if(fileNumb.length() == 3){
      //good
      numb = stoi(fileNumb);//перевод в число
      cout << vecFiles[numb-1].first << " this file was changed!\n";
      auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
      vecFiles[numb-1].second = cftime;//здесь обовляем время
      vecChngFlsNumb.push_back(numb-1);//вместо имени файла его номер
    }
    else{
      cout << "error!" << endl;
    }
  }
            cout << pExcep->errors();
          }
      }
    }
    //запоминаем и сюда больше не заходим
    // if(trigNumbFiles)
    //   memNumbFiles = numbFilesResources;

    // numbFilesResources = 0;//обнуляем
  }
  // trigNumbFiles = false;
  }}

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
    clConvJSON = new ConverterJSON();
    clInvInd = new InvertedIndex();
    // clConvJSON->prepareReqFile();
    // const char* fname1 = "requests.txt";
    // clConvJSON->PrepareQueries(fname1);

  if(!start && keyApp == 103){
      Service();
  }
  else if(!start && !stop && !startfName){
    clConvJSON->SetObjExcep(pExcep);
    clInvInd->SetObjEvent(pEvent);
    pExcep->SetObjEvent(pEvent);
    // const char* fname1 = "requests.txt";
    // clConvJSON->PrepareQueries(fname1);
    clConvJSON->ReadJsonfile(fConfJSON.c_str());
    jConf = clConvJSON->GetJSON();
    GetConfig();
    run = true;
  }
  delete clConvJSON;
    MyWaitTh();
  return run;
}

size_t& Server::GetException(){
  return eventException;
}

void Server::MyWaitTh(){
  ThChange = new thread(EventChangedFiles,this);
  ThCnangeRq = new thread(EventChangedRequest,this);
  ThNumbFilesFolder = new thread(EventChangedNumbersFiles,this);
}

void Server::go(){
  std::unique_lock<std::mutex> lck1(global1);
  readyThResFls = true;
  cvResFiles.notify_all();
}

void Server::wait(){
  std::unique_lock<std::mutex> lck2(global1);
  readyThResFls = false;
  cvResFiles.notify_all();
}

void Server::SetExcep(MyException* ptr){
  assert(ptr != nullptr);
  pExcep = ptr;
}

void Server::Signal(size_t& event){
  cout << "event " << event << endl;
  srvEvent = event;

  if(srvEvent == 1010){
    pEvent->Exceptions(pExcep);
    // ThChange->detach();
  }else if(srvEvent == 100){
    pEvent->Exceptions(pExcep);//wrong names
  }else if(srvEvent == 1011){
    pEvent->Exceptions(pExcep);//wrong names
  }else if(srvEvent == 1012){
    pEvent->Exceptions(pExcep);//wrong names
  }else{
    srvEvent = 0;
  }
  ++eventException;
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
  confApp.responses = (size_t)stoi(ViewValue(it,key));
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
}

size_t& Server::GetResponse(){
  return confApp.responses;
}

vector<string>& Server::GetDocs(){
  return vecFNamesFoldResource;
}

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
      if(!prepare){
        cout << confApp.appName << " version " << confApp.version << " run!" << endl;
        clInvInd->SetObjEvent(pEvent);
        clInvInd->SetObjExcep(pExcep);
        clConvJSON->SetObjEvent(pEvent);
        clConvJSON->SetObjExcep(pExcep);
        clConvJSON->prepareReqFile();
        const char* fname1 = "requests.txt";
        clConvJSON->PrepareQueries(fname1);
        clConvJSON->SetObjServ(this);
        clInvInd->PrepareDocs(this);

//здесь запускаем поток и разблокируем его
        ThChange->detach();
        go();

        ThCnangeRq->detach();
        ThNumbFilesFolder->detach();
        prepare = true;
      }
      vector<string>queries;
      while(true){

        if(!ready){

        clInvInd->UpdateDocumentBase1();//запускается для тестов, записываются файлы freq_dictionary.map freq_dictionaryTh.map для проверки!!!
        clInvInd->UpdateDocumentBaseThreads();
        refMapTh = GetMap();//работаем с reference map полученной от работы потоков
        if(refMapTh.get()->size() > 0){

          clSearchServ->SetObjInvInd(clInvInd);
          clSearchServ->GetInvIndDocs();
          clSearchServ->GetInvIndMap();//

          queries = clConvJSON->GetRequest();
   
      vector<vector<RelativeIndex>>result;//вектор ответов
      result = clSearchServ->searchTh(queries);//поточный метод

      cout << "size vector result is " << result.size() << endl;
      clSearchServ->SaveVector();//для проверки глазами
      clConvJSON->Answers(result);//запись ответов в файл answers.json      
    }
        ready = true;//останавливаемся и ждем событий
        }else{
          //здесь смотрим что изменилось - файлы, задания и т.д. и принимаем решение о выполнении нового расчета
          if(srvEvent == 1010){
            bool bChange = true;
            
            vector<size_t>vecHistoryRequests;
            //работаем над измененным файлом
            string fTmpBefore, fTmpAfter;
            vector<string>LastDocs = clInvInd->GetDocs();//тексты!!! предидущие документы, чтобы посмотреть что изменилось

            while(vecChngFlsNumb.size() == 0);//ждем ответа от обработсика события

            // wait();

            size_t ind;
            ind = vecChngFlsNumb.size();

            // for(auto &v : vecChngFlsNumb)
            //   cout << v << " ";
            // cout << endl;
            size_t fNmb;
            if(vecChngFlsNumb.size() > 0)
              fNmb = pExcep->GetDiffNumbFile()-1;
              // docNumbChanged = NumbFlsChngd;//из потока
            // for(auto &f : vecChngFlsNumb){
            //   fTmpBefore = LastDocs[f];//получаем предыдущий файл           
            // }
              // fTmpBefore = LastDocs[vecChngFlsNumb[ind-1]];

              // fTmpBefore = LastDocs[vecChngFlsNumb[0]];//error!!!
              fTmpBefore = LastDocs[fNmb];
            
            
            LastDocs.clear();
            clInvInd->ClearDocs();
            clInvInd->PrepareDocs(this);//получаем документы и смотрим файл который изменился

            LastDocs = clInvInd->GetDocs();//смотрим что после прочтения документов
            
            if(vecChngFlsNumb.size() > 0)
              // fTmpAfter = LastDocs[vecChngFlsNumb[0]];//error!!!
              fTmpAfter = LastDocs[fNmb];
              // fTmpAfter = LastDocs[vecChngFlsNumb[ind-1]];//получаем новый файл  
            
            vecHistoryRequests.push_back(docNumbChanged);

            // fTmpAfter = LastDocs.back();//берем последний элемент сверху
            if(fTmpBefore == fTmpAfter){
              cout << fTmpBefore << " " << fTmpAfter << endl;
              //есть изменения в содержании
              ready = true;//ничего не делаем
              cout << "no changes!\n";
            }else{
              cout << fTmpBefore << " " << fTmpAfter << endl;
              ready = false;//начинаем новый расчет
              bChange = false;//когда все закончится
              clSearchServ->ClearVecRelIdx();
              cout << "was changes!\n";
            }

            // go();

            fTmpBefore.clear();
            fTmpAfter.clear();
            // cout << "vector vecChngFlsNumb size is " << vecChngFlsNumb.size() << endl;
            // vecChngFlsNumb.clear();
            // srvEvent = 0;//clear event

          }else if(srvEvent == 1011/*|| srvEvent == 1012*/){
            // bool bQueries = false;
            clConvJSON->ClearRequest();
            clConvJSON->prepareReqFile();
            const char* fname1 = "requests.txt";
            clConvJSON->PrepareQueries(fname1);
            vector<string>newQueries = clConvJSON->GetRequest();

            size_t sizeQueries = ([queries](){
              size_t szq=0;
              for(auto &s : queries){
                szq += s.length();
              }
              return szq;
            }());

            size_t sizeNewQueries = ([newQueries](){
              size_t sznq=0;
              for(auto &s : newQueries){
                sznq += s.length();
              }
              return sznq;
            }());

            if(sizeQueries == sizeNewQueries && queries.size() == newQueries.size() && ([queries,newQueries](){
              bool res = false;
              size_t ind=0;
              size_t sz = queries.size();
              while(sz != 0){
                if(queries[ind] == newQueries[ind]){
                  res = true;
                  ++ind;
                }else{
                  break;
                }
                --sz;
              }
              return res;
            }())){
              cout << "no changes!\n";
              srvEvent = 0;//clear event
              ready = true;//ничего не делаем
            }else{          
            cout << "was changes!\n";
            clInvInd->ClearDocs();
            clInvInd->PrepareDocs(this);//получаем документы и смотрим файл который изменился
            clSearchServ->ClearVecRelIdx();
            srvEvent = 0;//clear event
            ready = false;//начинаем пересчет
            }
          }else if(srvEvent == 1012){
            cout << "changed space folder /resources\n";
            ready = true;
            srvEvent = 0;//clear event
          }
          
          // else{
          //   cout << "Waiting for tasks...\n";
          //   // ready = true;
          //   while(srvEvent != 0);
          //   // for(;;);
          // }
        }
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
  
}
