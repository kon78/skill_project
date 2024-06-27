#include "header.h"
// #include "service.h"

char Bunner[] = "Usage: SkillboxSearchEngine [keys /c/i/s/r/h] <config.json | requests.json | answers.json>";
// char appName[] = "SkillboxSearchEngine";
// char JSONfNameConfig[] = "config.json";

int main(int argc, char *argv[]){
string argumentV;
  if(argc < 2){
    cout << Bunner << "\n/c clear\n/i info\n/s service\n/r run\n/h help\n";
    exit(0);
  }else{
      for(int i = 0; i < argc; i++){
        
        argumentV += argv[i];
        if(i != (argc-1))
          argumentV += " ";
        }

      cout << "argument is " << argumentV << endl;
      
      Service* service = new Service(argc, argv);
    service->Start();
    // service->numbRespFiles();
    // service->GetArgumInfo();
    delete service;
  }
  return 0;
}