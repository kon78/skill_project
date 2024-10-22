#pragma once
#ifndef SERVER_H
#define SERVER_H

#include<vector>
#include<cassert>
#include<memory>
#include<cmath>
#include<algorithm>
#include<unordered_map>
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
  size_t responses;
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
Server(int argc, char* argv[]):argumc(argc),start(false),startfName(false),stop(true),
                            run(false),eventException(0),srvEvent(0),ready(false),
                            prepare(false),brfwc(false),readyThResFls(false){
  fConfJSON = "config.json"; fRequestsJSON = "requests.json"; fTestFile = "text.txt";
  ArgumSet(argv);
  // examination(fConfJSON);
}
~Server(){
  delete clConvJSON;
}
string makeRegExpKey();
void MainPath();
string& GetMainPath();
// void go();
// void wait();
void ArgumSet(char* argv[]);
void examination(const string& fname);
void TouchFile(const char* fname);
void GetResourcesInfo();
void ViewFolder(string& fname);
void ReadInfoRequest();
void ReadInfoResourcesFiles();
void EventChangedFiles();
void EventChangedNumbersFiles();
void EventChangedRequest();
void ChangedResourcesFiles();
void ReadyTest();
bool Ready();
void Run();
void KeyApplication();
void GetConfig();
size_t& GetResponse();
void Service();
void SaveFile(const int& respFiles);
void PrepareNameFilesVec();
void SetObj(InvertedIndex* ptr);
void SetObjEvent(MyEvent* ptr);
void Signal(size_t& event);
void SetExcep(MyException* ptr);
void MyWaitTh();
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
  size_t number_of_files_in_directory(filesystem::path path);
// bool filExist(string f);

private:
  // shared_ptr<InvertedIndex> sPtrInvInd;
  int argumc;
  string mainPath;
  size_t docNumbChanged;
  size_t eventException;
  size_t srvEvent;
  string mssg;
  string timeReq;
  time_t tmReqFile;
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
  bool brfwc;//bool requests file was changed
  string fConfJSON;
  string fTestFile;
  string fRequestsJSON;
  shared_ptr<ifstream> fin;
  shared_ptr<ofstream> fout;
  shared_ptr< map< string, vector<EntryThreads> >> refMapTh;
  shared_ptr< map< string, vector<EntryThreads> >> refMapThTst;
  shared_ptr< map< string, vector<Entry> >> refMap;
  shared_ptr< map< string, vector<Entry> >>refMapTst;
  bool ready,readyThResFls;
  mutex global1,globalRes,globalReq,globalFiles;
  condition_variable cvResFiles;
  // thread* Th=nullptr;
  thread* ThChange=nullptr;
  thread* ThCnangeRq=nullptr;
  thread* ThNumbFilesFolder=nullptr;
  vector<pair<string,time_t>>vecFiles;//resources
  vector<string>vecFold;
  vector<string>vecFoldLast;
  vector<pair<string,time_t>>vecReq;//requests
  vector<string>vecChangedFiles;//was changed files folder resources
  vector<size_t>vecChngFlsNumb;
  size_t NumbFlsChngd;
};
#endif