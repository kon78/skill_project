#include<iostream>
#include<chrono>
#include<iomanip>
#include "convjson.h"
#include "invertindex.h"
#include "server.h"
#include "event.h"
#include "myexception.h"

#define do_this 1
#define do_not 0
#define execute 1

namespace fs = filesystem;
using namespace std;

// size_t number_of_files_in_directory(filesystem::path path){
//   return (size_t)distance(filesystem::directory_iterator{path},filesystem::directory_iterator{});
// }

// void EventChangedNumbersFiles(){
//   string path = "C:\\develop\\skill_project\\resources";  
//   size_t numbFilesResources = 0;
//   size_t memNumbFiles;
//   vector<string>vecFilesChanged;
//   bool trigNumbFiles = true;

//   numbFilesResources = number_of_files_in_directory(path);

//   cout << numbFilesResources << endl;
// }

char Bunner[] = "Usage: SkillboxSearchEngine [keys /r]";
char keys[] = "\n/r run\n \n/h help\n \n/s service\n";

int main(int argc, char *argv[]){
  // EventChangedNumbersFiles();
#if(do_this == execute)
MyEvent* myevent = new MyEvent;
MyException* myexcep = new MyException;

  if(argc < 2){
    cout << Bunner << keys;
  }else{
    Server* clServ = new Server(argc,argv);
    clServ->SetObjEvent(myevent);
    clServ->SetExcep(myexcep);
    myevent->SetObjServ(clServ);

    if(clServ->Ready()){
      while(true)
        clServ->Run();  
  }
  }
#endif

  return 0;
}