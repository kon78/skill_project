#pragma once
#ifndef CONVJSON_H
#define CONVJSON_H
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<nlohmann/json.hpp>
// #include"event.h"
// #include"search.h"
// #include"invertindex.h"

// #include<memory>
// #include"service.h"
using namespace std;
using namespace nlohmann::json_abi_v3_11_3;

#define do_this 1
#define do_not 0
#define execute 1

struct RelativeIndex;
class MyEvent;
class Server;
class ConverterJSON{
  public:
    ConverterJSON() = default;// ConverterJSON(){}
    ~ConverterJSON(){}
  void ReadJsonfile(const char* fname);
  void ReadTextfile(const char* fname);
  void TestRead(const char* fname);
  void prepareReqFile();
  json GetJSON();
  void ParamApp();
  void PrepareQueries(const char* fname);
  // void Hello();
  void ViewJSON();
  void TouchFile(const char* fname);
  vector<string>& GetRequest();
  void SaveJSON(json& j2f, const char* fname);
  void Answers(vector<vector<RelativeIndex>>& ridx);
  int GetResponsesLimit(){return 0;}
  // vector<string> GetRequests(){}
  void putAnswers(vector<vector<pair<int, float>>>answers){}
  void SetObjEvent(MyEvent* ptr);
  void SetObjServ(Server* ptr);
  
  private:
    json jData;
    json jRequestsJSON;
    json jAnswJSON;
    vector<string> vReq;
    shared_ptr<ofstream> fout;
    MyEvent* pEvent=nullptr;
    Server* pServ=nullptr;
    // Service* pService = nullptr;
    // shared_ptr<Service>shrdPtrServ;
};
#endif