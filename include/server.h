#pragma once
#ifndef SEVER_H
#define SEVER_H

#include<vector>
#include<cassert>
#include<memory>
#include<cmath>
#include<algorithm>
#include<unordered_map>
#include<iomanip>
#include<fstream>
#include<string>
#include<typeinfo>
#include <regex>
#include<filesystem>
// #include"invertindex.h"
#include"myexception.h"
#include"convjson.h"


#define do_this 1
#define do_not 0
#define execute 1

using namespace std;

struct ConfApp{
  int files;
  int responses;
  double version;
  string appName;
};

class Server{
public:
Server() = default;
Server(int argc, char* argv[]):argumc(argc),start(false),startfName(false),stop(true),run(false){
  fConfJSON = "config.json"; fRequestsJSON = "requests.json";
  ArgumSet(argv);
  examination(fConfJSON);
}
~Server(){
  delete clConvJSON;
}
string makeRegExpKey();
void ArgumSet(char* argv[]);
void examination(const string& fname);
void TouchFile(char* fname);
bool Ready();
void Run();
void KeyApplication();
void GetConfig();
void Service();
void SaveFile(const int& respFiles);
void PrepareNameFilesVec();
void Help();
size_t GetNumbFiles();
string& ViewValue(json::iterator itValue, string& key);
string& ViewValueFiles(json::iterator itValue, string& key);
string makeRegExp();
size_t numbFiles;
// bool filExist(string f);


private:
  int argumc;
  ConverterJSON* clConvJSON;
  string dataTemp;
  ConfApp confApp;
  json jConf,jConfJSON;//file config.json
  size_t keyApp;
  string argumv;
  vector<string>vecFNamesFoldResource;
  bool start;//общий старт
  bool startfName;//проверка имен файлов
  bool stop;//общий стоп
  bool run;//разрешение на запуск
  string fConfJSON;
  string fRequestsJSON;
  shared_ptr<ifstream> fin;
  shared_ptr<ofstream> fout;

};
#endif