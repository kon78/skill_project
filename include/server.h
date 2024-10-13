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
#include<condition_variable>
#include"invertindex.h"
#include"myexception.h"
#include"convjson.h"
#include"search.h"
#include"event.h"


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
class MyEvent;
class MyException;
class Server{
public:
Server() = default;
Server(int argc, char* argv[]):argumc(argc),start(false),startfName(false),stop(true),run(false),eventException(0),srvEvent(0),ready(false),
                              prepare(false){
  fConfJSON = "config.json"; fRequestsJSON = "requests.json"; fTestFile = "text.txt";

  ArgumSet(argv);
  examination(fConfJSON);
}
~Server(){
  delete clConvJSON;
}
string makeRegExpKey();
void go();
void ArgumSet(char* argv[]);
void examination(const string& fname);
void TouchFile(const char* fname);
void GetResourcesInfo();
void ViewFolder(string& fname);
void ReadInfoResourcesFiles();
void EventChangedFiles();
void ChangedResourcesFiles();
void EventChangedFilesWithoutThrow();
void ReadyTest();
bool Ready();
void Run();
void KeyApplication();
void GetConfig();
void Service();
void SaveFile(const int& respFiles);
void PrepareNameFilesVec();
void Help();
void SetObj(InvertedIndex* ptr);
void SetObjEvent(MyEvent* ptr);
// void Signal(string& msg);
void Signal(size_t& event);
void SetExcep(MyException* ptr);
void MyWaitTh();
void listening(size_t& eventException, size_t& srvEvent);
shared_ptr< map< string, vector<EntryThreads> >> GetMap();//freq_dictionaryTh
shared_ptr< map< string, vector<EntryThreads> >> GetMapTst();//freq_dictionaryTh
shared_ptr< map< string, vector<Entry> >> GetMap1();//freq_dictionary
shared_ptr< map<string,vector<Entry>> > GetMap1Tst();
// shared_ptr<InvertedIndex> GetObjectInvInd();
vector<string>& GetDocs();
string& ViewValue(json::iterator itValue, string& key);
string& ViewValueFiles(json::iterator itValue, string& key);
void EditConfig(string& s);
string makeRegExp();
size_t& GetException();
size_t numbFiles;
// bool filExist(string f);


private:
  // shared_ptr<InvertedIndex> sPtrInvInd;
  int argumc;
  size_t eventException;
  size_t srvEvent;
  string mssg;
  ConverterJSON* clConvJSON=nullptr;
  InvertedIndex* clInvInd=nullptr;
  SearchService* clSearchServ=nullptr;
  InvertedIndex* clInvIndTst=nullptr;//TEST
  MyEvent* pEvent=nullptr;
  MyException* pExcep=nullptr;
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
  bool prepare;
  string fConfJSON;
  string fTestFile;
  string fRequestsJSON;
  shared_ptr<ifstream> fin;
  shared_ptr<ofstream> fout;
  shared_ptr< map< string, vector<EntryThreads> >> refMapTh;
  shared_ptr< map< string, vector<EntryThreads> >> refMapThTst;
  shared_ptr< map< string, vector<Entry> >> refMap;
  shared_ptr< map< string, vector<Entry> >>refMapTst;
  bool ready;
  mutex global;
  condition_variable cv;
  thread* Th=nullptr;
  thread* ThChange=nullptr;
  vector<pair<string,time_t>>vecFiles;//resources
  vector<string>vecChangedFiles;//was changed files folder resources

};
#endif