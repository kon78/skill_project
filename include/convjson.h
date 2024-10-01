#pragma once
#ifndef CONVJSON_H
#define CONVJSON_H
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<nlohmann/json.hpp>
// #include"invertindex.h"

// #include<memory>
// #include"service.h"
using namespace std;
using namespace nlohmann::json_abi_v3_11_3;

#define do_this 1
#define do_not 0
#define execute 1

class ConverterJSON{
  public:
    ConverterJSON() = default;// ConverterJSON(){}
    ~ConverterJSON(){}
  void ReadJsonfile(const char* fname);
  void TestRead(const char* fname);
  void prepareReqFile();
  json GetJSON();
  void ParamApp();
  void PrepareQueries(const char* fname);
  void Hello();
  void ViewJSON();
  void TouchFile(const char* fname);
  vector<string>& GetRequest();
  void SaveJSON(json& j2f, const char* fname);

  int GetResponsesLimit(){return 0;}
  // vector<string> GetRequests(){}
  void putAnswers(vector<vector<pair<int, float>>>answers){}
  
  private:
    json jData;
    json jRequestsJSON;
    vector<string> vReq;
    shared_ptr<ofstream> fout;
    // Service* pService = nullptr;
    // shared_ptr<Service>shrdPtrServ;
};
#endif