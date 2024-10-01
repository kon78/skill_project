#include<iostream>
// #include "service.h"
#include "convjson.h"
#include "invertindex.h"
// #include "search.h"
#include "server.h"
#include "event.h"
// #include "myexception.h"

#define Application 1
#define Editing 0
#define do_this 1
#define do_not 0

using namespace std;

char Bunner[] = "Usage: SkillboxSearchEngine [keys /r]";
char keys[] = "\n/r run\n \n/h help\n \n/s service\n";

int main(int argc, char *argv[]){
// MyException myexcep;

MyEvent* myevent = new MyEvent;

#if(Application == do_this)
  if(argc < 2){
    cout << Bunner << keys;
  }else{
    Server* clServ = new Server(argc,argv);
    clServ->SetObjEvent(myevent);
    if(clServ->Ready()){
      clServ->Run();    
  }
  }

#endif

#if(Editing == do_this)
  Service* service = nullptr;
  if(argc < 2){
    cout << Bunner << keys;
    delete service;
    exit(0);
  }else{

  shared_ptr<Service>_shrdPtrServ = make_shared<Service>(argc, argv); 
  ConverterJSON* clConvJSON = new ConverterJSON();
  InvertedIndex* clInvInd = new InvertedIndex();
  SearchServer* clSearchServ = new SearchServer();
  clConvJSON->SetObjServ(_shrdPtrServ);//передача
  clInvInd->SetObjServ(_shrdPtrServ);
  clSearchServ->SetObjServ(_shrdPtrServ);
  clSearchServ->SetObjInvInd(clInvInd);

  clConvJSON->ParamApp();
  if( _shrdPtrServ->AppReady() ){
    //двигаемся дальше - получаем вектор с содержимым файлов-запросов

    clInvInd->UpdateDocumentBase1();
    clInvInd->UpdateDocumentBaseThreads();
    _shrdPtrServ->SetRequests();
    _shrdPtrServ->PrepareQueries();
    clSearchServ->GetInvIndMap();
    clSearchServ->GetInvIndDocs();
    clSearchServ->search(_shrdPtrServ->GetQueries());
  
  }else{
    cout << "Wrong! AppReady() - false!\n";
  }
  }
#endif

  return 0;
}