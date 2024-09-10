#include"header.h"
#include"service.h"
void Service::examination(char* fname){
      string temp(fname);
      cout << "filename is " << temp << endl;
      // if( argumc > 1 && (argumv.find("/")) < argumv.length() ){
        // string::size_type pos;
        // pos = argumv.find("/");
        // pos += 1;
        while(start && !fileConfError){
        try{
         filExist(temp);
      } catch (exception &ex){
          cout << "file " << temp << ". " << ex.what() << "!\n";
      }
      }
      // }
}

// string Service::makeRegExpSpace(){
//   string ret;
//   ret =  "(\\b(?! )\\w+)";
//   return ret;
// }

vector<string>* Service::FilterWordsSpaces(const string& words){
vector<string>* ptrRet = &ret;
  const regex rgxSpaces (makeRegExpSpace());
  ret.clear();
  for( sregex_iterator it(words.begin(), words.end(), rgxSpaces), it_end; it != it_end; ++it ){
    ret.push_back(it->str());
}
return ptrRet;
}

void Service::examination1(char* fname){
  fstream fp;
  fp.open(fname, ios::in);
  if(!fp.is_open()){
    TouchFile(fname);
    fileConfError = true;
  }else{
    fileConfError = true;//file exist
  }
}

bool Service::AppReady(){
  return run;
}

void Service::ArgumSet(char* argv[]){
      for(int i = 0; i < argumc; i++){
        argumv += argv[i];
        if(i != (argumc-1))
          argumv += " ";
        }
  cout << "Constructor argumentV is " << argumv << endl;
}

string Service::GetInfo(){
  // string ret((int)start + " " + (int)stop + " " + (int)fileConfError);
  string ret;
  ret = ((start)?"true ":"false ");
  ret +=((stop)?"true ":"false ");
  ret +=((fileConfError)?"true ":"false ");

  // ret = start + " " + stop + " " + fileConfError;
  return ret;
}

void Service::Start(){
  // cout << "Start " << endl;
  while(start){
    // cout << "Start while!" << endl;
    if(fileConfError){
      start = false; stop = true;
      // break;

    if( argumc > 1 && (argumv.find("/")) < argumv.length() ){
      string::size_type pos;
      pos = argumv.find("/");
      pos += 1;
      if(argumv[pos] == 's'){
        // cout << "finded /s" << endl;
        pos = argumv.find(fConfJSON);
        if(pos < argumv.length() ){
          // cout << "json file exist!\n";
          serviceKey = true;  
        }else{
          serviceKey = false;  
        }
        // serviceKey = true; 
        serviceKeyError = false;
        codeKey = int('s');
      }else if(argumv[pos] == 'c'){
        // cout << "finded /c" << endl;
        serviceKey = true; serviceKeyError = false;
        codeKey = int('c');
      }else if(argumv[pos] == 'i'){
        // cout << "finded /i" << endl;
        serviceKey = true; serviceKeyError = false;
        codeKey = int('i');
      }else if(argumv[pos] == 'r'){
        // cout << "finded /r" << endl;
        serviceKey = false; serviceKeyError = false;
        fileConfError = false;
        codeKey = int('r');
      }else if(argumv[pos] == 'h'){
        // cout << "finded /h" << endl;
        serviceKey = true; serviceKeyError = false;
        codeKey = int('h');
      }else{
        serviceKeyError = true;
      }
      // if( argumv.find("/") )      
      // cout << "argc=" << argumc << " argv=" << argumv << endl;
    }
      }
    
  }

  if(!start && stop && fileConfError && !serviceKey){
    cout << "exit Service::Start()" << endl;
    cout << "error usage key!\n";
    exit(0);
    }else{
      //service file <*target*>.json
      if(codeKey == int('s')){
        cout << "Service! Create file config.json!" << endl;        
        TouchFile(fConfJSON);
        prepareConfFile();
        json2strTemp = jConfJSON.dump();
        const char* str = json2strTemp.c_str();

        fout.get()->write(str,json2strTemp.length());
        fout.get()->close();

        json2strTemp.clear();
        fout.reset();      
      }else if(codeKey == int('r') ){//здесь стоит детально проверить условия запуска
        cout << "Run!" << endl;
        run = true;
        // GetObject();
        // sptrClConvJSON->GetTextDocuments();
      }
    }
}

// void Service::GetObject(){
//   sptrClConvJSON = make_shared<ConverterJSON>();
// }

void Service::TouchFile(char* fname){
  fout = make_shared<ofstream>(fname,ios::out);
}

string Service::GetArgumInfo(){
  // cout << "numbers arguments is " << argumc << endl;
  // cout << argumv << endl;
  return argumv;
}

//для проверки, существует ли файл config.json
void Service::filExist(string f){
  cout << "file is " << f << endl;
  fstream fp;
  fp.open(f, ios::in);
  if(fp.is_open()){    
    fileConfError = true;
    throw runtime_error("Config file is missing");
  }
  else{
    //здесь проверить, есть ли в файле поле config наверно в методе ConverterJSON::GetTextDocuments()
    
  }
}

void Service::readFile(string f){
  fstream fp;
  string temp;
  filErr = false;
  fp.open(f, ios::in);
  if(fp.is_open()){
    while(!fp.eof()){
      getline(fp,temp);
      dataFile.push_back(temp);
    }
    filErr = true;
  }else{
    cout << "Can't read file " << f << "!\n";
  }
}

vector<string> Service::GetDataFile(){
  return dataFile;
}

//шаблон не может быть виртуалным
//шаблон лучше прописывать в header файле
// template<class T>
// void Service::clearVec1(vector<T>& TVector){
//   typename vector<T>::iterator it;
//   for(it = TVector.begin(); it != TVector.end(); ++it){
//     it = TVector.erase(it);
//   }
// }

//пока откажусь от механизма чтения и перудачи через класс Service
#if(do_this == do_not)
bool Service::readjson(const string& fName){
  // std::ifstream f("..\\requests.json");
  // json data = json::parse(f);

  ifstream f(fName);
  if(f.is_open()){
    data = json::parse(f);
  }else{
    cout << "file " << fName << " not exist or located any folder!\n";
  }
  cout << "readjson() " << data << endl;
}

json Service::GetJSON(){
  cout << "GetJSON() " << data << endl;
  return data;
}
#endif

void Service::clearVec(){
for(vector<string>::iterator it = dataFile.begin(); it != dataFile.end();){
  it = dataFile.erase(it);
}
}

size_t Service::SizeVector(){
  return dataFile.size();
}

void Service::setRespFiles(int resp){
  while(resp != 0){

    --resp;
  }
}

int Service::numbRespFiles(){
int ret;
#if(do_this == do_not)
qsizetype qres;
  QDir sourceDir("C:\\develop\\skill_project\\resources");
  auto files = sourceDir.entryList(QStringList() << "*.txt", QDir::Files);
  qres = sourceDir.count();
  ret = static_cast<int>(qres);

  if(ret >= 2)
    ret -= 2;

  int i = 0;
  for(auto &filename : files){
    i += 1;
    strRespFiles += filename.toStdString();
    if(i != (ret-1))
      strRespFiles += " ";

    // cout << filename.toStdString() << " ";
  }
  cout << endl;
#endif

  string path = "C:\\develop\\skill_project\\resources";
  ret = 0;
  for (auto & p : fs::directory_iterator(path)){
    ++ret;
        }

  return ret;
}

string Service::nameRespFiles(){
  string ret;
  string path = "C:\\develop\\skill_project\\resources";
  for (auto & p : fs::directory_iterator(path)){
    cout << p.path() << " ";    
  }
  cout << endl;
  return ret;
}

//имена всех файлов в папке resource
string Service::prepareNameFiles(){
  string ret;
  string path = "C:\\develop\\skill_project\\resources";
  for(auto &p : fs::directory_iterator(path)){
    ret += p.path().filename().generic_string();
    ret += " ";
  }
  return ret;
}

vector<string>& Service::prepareNameFilesVec(){
  vector<string> &ref = FNamesFoldResource;
  string path = "C:\\develop\\skill_project\\resources";
  for(auto &p : fs::directory_iterator(path)){
    ref.push_back(p.path().filename().generic_string());
  }
  return ref;
}

string Service::GetFName(int index){
  string ret;
  const int vecSize = FNamesFoldResource.size();
  if(index > vecSize || index < 0){
    cout << "error index vector!";
  }else{
    ret = FNamesFoldResource[index];
  }
  return ret;
}

void Service::prepareConfFile(){
  respFiles = numbRespFiles();
  cout << "Prepare file Config.json!\n";
  // cout << "Maximum responses files :";

  if(respFiles == 0)
    respFiles = 5;

  cout << "response files count is " << respFiles << endl;
  // setRespFiles(respFiles);

  jConfJSON = {
    {"config",{
      {"name","SkillboxSearchEngine"},
      {"version","0.1"},
      {"max_responses",respFiles}
    },
    "files",{strRespFiles}
    }};
}

void Service::prepareReqFile(){
  // vector<string>vecstr;
  // vecstr.push_back("some_words...");
  // vecstr.push_back("some_words...");
  // vecstr.push_back("some_words...");
  cout << "Prepare file requests.json!\n";
  jRequestsJSON = {
    {"requests",{
    }
    }
  };

  json::iterator it=jRequestsJSON.begin();
  // for(auto &s : req){
  //   it.value() = s;
  //   ++it;
  // }

  int i = 0;
  while(true){
    if(i == req.size())break;
    it.value().push_back(req[i]);
    ++i;
  }
  // --it;
  int size_vec = req.size();
  int size_json = it.value().size();
  cout << "size req is " << size_vec << " size json is " << size_json << endl;
}

string Service::makeRegExpSpace(){
  string ret;
  ret =  "(\\b(?! )\\w+)";
  return ret;
}

void Service::FilterWords(){
  const regex rgxSpaces (makeRegExpSpace());
  for(auto &d : dataFile){
    for( sregex_iterator it(d.begin(), d.end(), rgxSpaces), it_end; it != it_end; ++it ){
        strRequests += it->str();
        strRequests += " ";
        }
  size_t pos = strRequests.length();
  strRequests.erase(pos-1, pos);//delete last space
  req.push_back(strRequests);
  strRequests.erase();
  }
}


void Service::SetRequests(){
  clearVec();//clear vector dataFile
  readFile("requests.txt");//data to vector
  FilterWords();
  clearVec();
  prepareReqFile();
  //save
  char* fName = "requests.json";
  TouchFile(fName);
  json2strTemp.clear();
  json2strTemp = jRequestsJSON.dump();
  const char* str = json2strTemp.c_str();
  fout.get()->write(str,json2strTemp.length());
  fout.get()->close();
  fout.reset();
}

json Service::GetRequests(){
  return jRequestsJSON;
}

void Service::PrepareQueries(){
  json::iterator it = jRequestsJSON.begin();
  string key = it.key();
  vector<string>value;
  size_t jsize = it.value().size();
  for(size_t ind = 0; ind < jsize; ++ind){
    value.push_back(it.value()[ind]);
    cout << it.value()[ind] << endl;
  }

  assert(value.size() == it.value().size());//if error

#if(do_this == execute)
  const regex rgxSpaces (makeRegExpSpace());
  string temp;
  for(auto &d : value){
    for( sregex_iterator it(d.begin(), d.end(), rgxSpaces), it_end; it != it_end; ++it ){
      temp += it->str() + " ";
      temp.erase(temp.length()-1);//удаляем последний пробел
      queries.push_back(temp);
  }
}
#endif

#if(do_this == do_not)
  const regex rgxSpaces (makeRegExpSpace());
  for(auto &d : value){
    for( sregex_iterator it(d.begin(), d.end(), rgxSpaces), it_end; it != it_end; ++it ){
      queries.push_back(it->str());
  }
  }
#endif
}

vector<string>& Service::GetQueries(){
  return queries;
}