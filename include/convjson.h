#pragma once
#ifndef CONVJSON_H
#define CONVJSON_H
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<nlohmann/json.hpp>

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
    // vector<string> GetTextDocuments();
  void ReadJsonfile(const char* fname);
  void TestRead(const char* fname);
    json GetJSON();
    // ConverterJSON(){}
    void ParamApp();
    // void SetObjServ(shared_ptr<Service> _shrdPtrServ);


    int GetResponsesLimit(){return 0;}
    // vector<string> GetRequests(){}
    void putAnswers(vector<vector<pair<int, float>>>answers){}
  
  private:
    json jData;
    // Service* pService = nullptr;
    // shared_ptr<Service>shrdPtrServ;
};
#endif