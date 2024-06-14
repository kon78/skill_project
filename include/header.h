#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<exception>
#include<stdexcept>
#include<fstream>
#include<string>
#include<nlohmann/json.hpp>
#include<QtCore>

#define do_this 1
#define do_not 0
#define execute 1

using namespace nlohmann::json_abi_v3_11_3;
using namespace std;

class Service{
  public:
    Service(int argc, char* argv[]):start(false),stop(true),argumc(argc),fileConfError(false),serviceKey(false),codeKey(0),serviceKeyError(false){
      start = true; stop = false;
      fConfJSON = "config.json";
      examination(fConfJSON);

      for(int i = 0; i < argc; i++){
        argumv += argv[i];
        if(i != (argc-1))
          argumv += " ";
        }
      // fin = make_shared<ifstream>("config.json",ios::app);
    }
    ~Service(){fin.reset();fout.reset();}
    void examination(char* fname);
    string GetInfo();
    void GetArgumInfo();
    void filExist(string f);
    void Start();
    void prepareConfFile();
    void TouchFile(char* fname);
    void setRespFiles(int resp);
    int numbRespFiles();

  private:
    string argumv;
    int argumc;
    bool start;
    bool stop;
    shared_ptr<ifstream> fin;
    shared_ptr<ofstream> fout;
    char* projectName = nullptr;
    char* fConfJSON = nullptr;
    int codeKey;
    bool fileConfError;
    bool serviceKey;
    bool serviceKeyError;
    json jConfJSON;
    string json2strTemp;
    int respFiles;
};

class ConverterJSON{
  public:
    ConverterJSON() = default;// ConverterJSON(){}
    vector<string> GetTextDocuments();
    int GetResponsesLimit();
    vector<string> GetRequests();
    void putAnswers(vector<vector<pair<int, float>>>answers);
};
