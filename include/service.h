#pragma once
#ifndef SERVICE_H
#define SERVICE_H
#include<nlohmann/json.hpp>
#include<vector>
#include<cassert>
#include<regex>
#include<fstream>

using namespace std;

using namespace nlohmann::json_abi_v3_11_3;

class Service{
  public:
    //for testing
    Service(){}
    Service(int argc, char* argv[]):start(false),stop(true),run(false),argumc(argc),fileConfError(false),serviceKey(false),codeKey(0),serviceKeyError(false)/*,ptrArgv(argv)*/{
      start = true; stop = false;
      fConfJSON = "config.json";
      fRequestsJSON = "requests.json";

      ArgumSet(argv);
      // examination(fConfJSON);
      examination1(fConfJSON);
      examination1(fRequestsJSON);
      // fin = make_shared<ifstream>("config.json",ios::app);
    }
    ~Service(){fin.reset();fout.reset();}
    void examination(char* fname);
    void examination1(char *fname);
    string GetInfo();
    string GetArgumInfo();
    vector<string> GetDataFile();
    size_t SizeVector();
    void filExist(string f);
    void readFile(string f);
    // bool readjson(const string& fName);//пока выключил эти мехагизмы
    // json GetJSON();
    void clearVec();
    template<class T> void clearVec1(vector<T>& TVector);
    void Start();
    void prepareConfFile();
    void prepareReqFile();
    void SetRequests();
    void TouchFile(char* fname);
    void setRespFiles(int resp);
    int numbRespFiles();
    string GetFName(int index);
    string nameRespFiles();
    string makeRegExpSpace();
    vector<string>* FilterWordsSpaces(const string& words);
    bool AppReady();
    string prepareNameFiles();
    vector<string>& prepareNameFilesVec();//возвращает vector имен файлов в папке /resource
    void FilterWords();
    // string makeRegExpSpace();
    // void GetObject();
    void ArgumSet(char* argv[]);
    Service* getAddr(){
      return this;
    }
    json GetRequests();
    void PrepareQueries();
    vector<string>& GetQueries();

  private:
    vector<string> FNamesFoldResource;
    string argumv;
    int argumc;
    bool start;
    bool stop;
    bool run;
    bool filErr;
    vector<string>dataFile;
    vector<string>req;
    vector<string> ret;
    // char** ptrArgv = nullptr;
    shared_ptr<ifstream> fin;
    shared_ptr<ofstream> fout;
    // shared_ptr<ConverterJSON> sptrClConvJSON;
    char* projectName = nullptr;
    char* fConfJSON = nullptr;
    char* fRequestsJSON = nullptr;
    int codeKey;
    bool fileConfError;
    bool serviceKey;
    bool serviceKeyError;
    json jConfJSON;
    json jRequestsJSON;
    json data;
    string json2strTemp;
    int respFiles;
    string strRespFiles;
    string strRequests;
    vector<string>queries;
    // ConverterJSON* clConvJson = nullptr;
};

template<class T> void Service::clearVec1(vector<T>& TVector){
  typename vector<T>::iterator it = TVector.begin();
  size_t pos = 0;
  size_t size = TVector.size();
  while(!TVector.empty()){
    advance(it, pos);
    TVector.erase(it);
    ++pos;
}
}
#endif
