#include"header.h"
using namespace std;

class Service{
  public:
    Service():start(false),stop(true),fileConfError(false),fConfJSON("config.json"){
      cout << "Service start." << endl;
      start = true; stop = false;
      // fin = make_shared<ifstream>("config.json",ios::app);
      examination(fConfJSON);
    }
    ~Service(){fin.reset();}
    void examination(char* fname);
    string GetInfo();
    void filExist(string f);
    void prepareConfFile();

  private:
    bool start;
    bool stop;
    shared_ptr<ifstream> fin;
    char* projectName = nullptr;
    char* fConfJSON = nullptr;
    bool fileConfError;
};
