#include"header.h"

void Service::examination(char* fname){
      string temp(fname);
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

void Service::ArgumSet(char* argv[]){
      for(int i = 0; i < argumc; i++){
        argumv += argv[i];
        if(i != (argumc-1))
          argumv += " ";
        }
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
        serviceKey = true; serviceKeyError = false;
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
        codeKey = int('r');
      }else if(argumv[pos] == 'h'){
        // cout << "finded /h" << endl;
        serviceKey = true; serviceKeyError = false;
        codeKey = int('h');
      }else{
        serviceKeyError = true;
        cout << "error usage key!\n";
      }
      // if( argumv.find("/") )      
      // cout << "argc=" << argumc << " argv=" << argumv << endl;
    }
      }
    
  }

  if(!start && stop && fileConfError && !serviceKey){
    // cout << "exit" << endl;
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
      }else if(codeKey == int('r')){
        cout << "Run!" << endl;
        GetObject();
        sptrClConvJSON->GetTextDocuments();
      }
    }
}

void Service::GetObject(){
  sptrClConvJSON = make_shared<ConverterJSON>();
}

void Service::TouchFile(char* fname){
  fout = make_shared<ofstream>(fname,ios::out);
}

void Service::GetArgumInfo(){
  cout << "numbers arguments is " << argumc << endl;
  cout << argumv << endl;
}

void Service::filExist(string f){
  bool bFileExist;
  // cout << "file is " << f << endl;
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

void Service::setRespFiles(int resp){
  while(resp != 0){

    --resp;
  }
}

int Service::numbRespFiles(){
int ret;
  QDir sourceDir("/resources");
  auto files = sourceDir.entryList(QStringList() << "*.txt", QDir::Files);

  for(auto &filename : files){
    cout << filename.toStdString() << " ";
  }
  cout << endl;
  return ret;
}

void Service::prepareConfFile(){
  cout << "Prepare file Config.json!\n";
  cout << "Maximum responses files :";
  cin >> respFiles;
  if(respFiles == 0)
    respFiles = 5;

  // setRespFiles(respFiles);
  numbRespFiles();

  jConfJSON = {
    {"config",{
      {"name","SkillboxSearchEngine"},
      {"version","0.1"},
      {"max_responses",respFiles}
    },
    "files",{}
    }};
}