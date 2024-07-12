#include "header.h"
// #include "service.h"

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

  service = new Service(argc, argv);
  ConverterJSON* clConvJSON = new ConverterJSON();
  clConvJSON->ParamApp(service);
  if( service->AppReady() ){
    //двигаемся дальше - получаем вектор с содержимым файлов-запросов
    clConvJSON->GetTextDocuments();
  }else{
    cout << "Wrong! AppReady() - false!\n";
  }
  }
  return 0;
}