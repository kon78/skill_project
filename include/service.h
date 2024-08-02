#pragma once
#ifndef SERVICE_H
#define SERVICE_H
#include<nlohmann/json.hpp>
#include<vector>

using namespace std;

using namespace nlohmann::json_abi_v3_11_3;

class Service{
  public:
    //for testing
    Service(){}
    Service(int argc, char* argv[]):start(false),stop(true),run(false),argumc(argc),fileConfError(false),serviceKey(false),codeKey(0),serviceKeyError(false)/*,ptrArgv(argv)*/{
      start = true; stop = false;
      fConfJSON = "config.json";
      ArgumSet(argv);
      // examination(fConfJSON);
      examination1(fConfJSON);
      // fin = make_shared<ifstream>("config.json",ios::app);
    }
    ~Service(){fin.reset();fout.reset();}
    void examination(char* fname);
    void examination1(char *fname);
    string GetInfo();
    string GetArgumInfo();
    vector<string> GetDataFile();
    void filExist(string f);
    void readFile(string f);
    void Start();
    void prepareConfFile();
    void TouchFile(char* fname);
    void setRespFiles(int resp);
    int numbRespFiles();
    string nameRespFiles();
    bool AppReady();
    string prepareNameFiles();
    // void GetObject();
    void ArgumSet(char* argv[]);
    Service* getAddr(){
      return this;
    }

  private:
    string argumv;
    int argumc;
    bool start;
    bool stop;
    bool run;
    bool filErr;
    vector<string>dataFile;
    // char** ptrArgv = nullptr;
    shared_ptr<ifstream> fin;
    shared_ptr<ofstream> fout;
    // shared_ptr<ConverterJSON> sptrClConvJSON;
    char* projectName = nullptr;
    char* fConfJSON = nullptr;
    int codeKey;
    bool fileConfError;
    bool serviceKey;
    bool serviceKeyError;
    json jConfJSON;
    string json2strTemp;
    int respFiles;
    string strRespFiles;
    // ConverterJSON* clConvJson = nullptr;
};
#endif
