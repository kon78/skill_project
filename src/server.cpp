#include"server.h"
#include"myexception.h"
#include"convjson.h"

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
  cout << ret << endl;
  return ret;
}
void Server::KeyApplication(){
  cout << argumv << endl;
    const regex findRegCntWord(makeRegExpKey());
    std::ptrdiff_t const countWord(distance(sregex_iterator(argumv.begin(), argumv.end(), findRegCntWord),sregex_iterator()));
  sregex_iterator itrgx(argumv.begin(), argumv.end(), findRegCntWord);

    if(countWord != 0 && itrgx->str() == "/e"){
      // cout << "finded key " << "/e" << endl;
      keyApp = 101;
    }else if(countWord != 0 && itrgx->str() == "/i"){
      // cout << "finded key " << "/i" << endl;
      keyApp = 102;
    }else if(countWord != 0 && itrgx->str() == "/s"){
      // cout << "finded key " << "/s" << endl;
      keyApp = 103;
    }else if(countWord != 0 && itrgx->str() == "/r"){
      // cout << "finded key " << "/r" << endl;
      keyApp = 104;
    }else if(countWord != 0 && itrgx->str() == "/h"){
      // cout << "finded key " << "/h" << endl;
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
  if(!stop && start && !startfName){
    run = true;
  }
  return run;
}

void Server::Run(const string& appname){
  ConverterJSON* clConvJSON = new ConverterJSON();
  const char* fName = fConfJSON.c_str();
  clConvJSON->ReadJsonfile(fName);

  KeyApplication();
  
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
      break;
    }
    case (104):{
      cout << "finded key " << "/r" << endl;

      break;
    }
    case (105):{
      cout << "finded key " << "/h" << endl;
    }
    default:{cout << "wrong key!" << endl;
    break;
    }
  }
  

  // clConvJSON->JfileRead();
  // if(appName != nullptr){
    // string s;s.assign(appname,(sizeof(appname)/sizeof(char*)));
    // string s;s.assign(appname,(sizeof(*appname)));
  cout << "Application " << appname << endl;

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