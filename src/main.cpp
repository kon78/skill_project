// #include<nlohmann/json.hpp>
#include "header.h"
#include "service.h"
#include "convjson.h"
#include "invertindex.h"
#include "search.h"
// #include "service.h"

// using namespace nlohmann::json_abi_v3_11_3;
using namespace std;

char Bunner[] = "Usage: SkillboxSearchEngine [keys /c/i/s/r/h] <config.json | requests.json | answers.json>";
char keys[] = "\n/c clear\n/i info\n/s service\n/r run\n/h help\n";
char appName[] = "SkillboxSearchEngine";

int main(int argc, char *argv[]){
// string argumentV;
  Service* service = nullptr;
  if(argc < 2){
    cout << Bunner << keys;
    delete service;
    exit(0);
  }else{

#if(do_this == do_not)
      Service* service = new Service(argc, argv);
    service->Start();

    delete service;
#endif

  shared_ptr<Service>_shrdPtrServ = make_shared<Service>(argc, argv); 
  // service = new Service(argc, argv);
  ConverterJSON* clConvJSON = new ConverterJSON();
  InvertedIndex* clInvInd = new InvertedIndex();
  SearchServer* clSearchServ = new SearchServer();
  // SearchServer clSearchServ;
  // InvertedIndex clInvInd;
  clConvJSON->SetObjServ(_shrdPtrServ);//передача
  clInvInd->SetObjServ(_shrdPtrServ);
  clSearchServ->SetObjServ(_shrdPtrServ);
  clSearchServ->SetObjInvInd(clInvInd);

  clConvJSON->ParamApp();
  if( _shrdPtrServ->AppReady() ){
    //двигаемся дальше - получаем вектор с содержимым файлов-запросов
    // clConvJSON->GetTextDocuments();
  #if(do_this == execute)

    clInvInd->UpdateDocumentBase1();
    // clInvInd.UpdateDocumentBase1();

    clInvInd->UpdateDocumentBaseThreads();
    // clInvInd.UpdateDocumentBaseThreads();

    _shrdPtrServ->SetRequests();
    _shrdPtrServ->PrepareQueries();
    // clSearchServ->ReadRequests();//временно выключил!!!
    // clSearchServ->search1();
    clSearchServ->GetInvIndMap();
    clSearchServ->GetInvIndDocs();
    clSearchServ->search(_shrdPtrServ->GetQueries());
    // clInvInd->EqualFreqDictionary();
    // cout << boolalpha << clInvInd->map_compare();
    // clInvInd->EqualFreqDictionary2();
    // clInvInd->PrepareDocs();//перенес в метод InvertedIndex::UpdateDocumentBaseThreads(...)
    // clInvInd->UpdateDocumentBaseThreads(clConvJSON->GetTextDocuments());
  #endif
  #if(do_this == do_not)
    cout << "before threads work numb is " << clInvInd->GetNumbTest() << endl; 
    clInvInd->ThreadRoutine();
    cout << "after threads work numb is " << clInvInd->GetNumbTest() << endl;
  #endif
  
  }else{
    cout << "Wrong! AppReady() - false!\n";
  }
  }
  return 0;
}