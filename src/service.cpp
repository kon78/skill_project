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
    filErr = true;
    while(!fp.eof()){
      getline(fp,temp);
      dataFile.push_back(temp);
    }
  }else{
    cout << "Can't read file " << f << "!\n";
  }
}

vector<string> Service::GetDataFile(){
  return dataFile;
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
