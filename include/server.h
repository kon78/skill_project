#pragma once
#ifndef SERVER_H
#define SERVER_H

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
#include<regex>
#include<vector>
#include<filesystem>
#include"invertindex.h"
#include"myexception.h"
#include"convjson.h"
#include"search.h"


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

struct Entry;
struct EntryThreads;
class InvertedIndex;
class SearchService;
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
void SetObj(InvertedIndex* ptr);
shared_ptr< map< string, vector<EntryThreads> >> GetMap();//freq_dictionaryTh
shared_ptr< map< string, vector<EntryThreads> >> GetMapTst();//freq_dictionaryTh
shared_ptr< map< string, vector<Entry> >> GetMap1();//freq_dictionary
shared_ptr< map<string,vector<Entry>> > GetMap1Tst();
// shared_ptr<InvertedIndex> GetObjectInvInd();
vector<string>& GetDocs();
string& ViewValue(json::iterator itValue, string& key);
string& ViewValueFiles(json::iterator itValue, string& key);
string makeRegExp();
size_t numbFiles;
// bool filExist(string f);


private:
  // shared_ptr<InvertedIndex> sPtrInvInd;
  int argumc;
  ConverterJSON* clConvJSON=nullptr;
  InvertedIndex* clInvInd=nullptr;
  SearchService* clSearchServ=nullptr;
  InvertedIndex* clInvIndTst=nullptr;//TEST
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
  shared_ptr< map< string, vector<EntryThreads> >> refMapTh;
  shared_ptr< map< string, vector<EntryThreads> >> refMapThTst;
  shared_ptr< map< string, vector<Entry> >> refMap;
  shared_ptr< map< string, vector<Entry> >>refMapTst;
};
#endif