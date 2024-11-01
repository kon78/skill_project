#include<iostream>
#include<chrono>
#include<iomanip>
#include "convjson.h"
#include "invertindex.h"
#include "server.h"
#include "event.h"
#include "myexception.h"

namespace fs = filesystem;
using namespace std;

char Bunner[] = "Usage: SkillboxSearchEngine [keys /r]";
char keys[] = "\n/r run\n \n/h help\n \n/s service\n /e erase\n";

int main(int argc, char *argv[]){

MyEvent* myevent = new MyEvent;
MyException* myexcep = new MyException;

  if(argc < 2){
    cout << Bunner << keys;
  }else{
    Server* clServ = new Server(argc,argv);
    clServ->SetObjEvent(myevent);
    clServ->SetExcep(myexcep);
    myexcep->SetObjEvent(myevent);
    myevent->SetObjServ(clServ);

    if(clServ->Ready()){
      while(true)
        clServ->Run();  
  }
    //end;
    delete clServ;
  }

  delete myevent;
  delete myexcep;

  return 0;
}