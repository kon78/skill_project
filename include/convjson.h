#pragma once
#ifndef CONVJSON_H
#define CONVJSON_H
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<nlohmann/json.hpp>

using namespace std;
using namespace nlohmann::json_abi_v3_11_3;

struct RelativeIndex;
class MyEvent;
class MyException;
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
  void PrepareQueries(const char* fname);
  void ViewJSON();
  void TouchFile(const char* fname);
  vector<string>& GetRequest();
  void SaveJSON(json& j2f, const char* fname);
  void Answers(vector<vector<RelativeIndex>>& ridx);
  int GetResponsesLimit(){return 0;}
  void putAnswers(vector<vector<pair<int, float>>>answers){}
  void SetObjEvent(MyEvent* ptr);
  void SetObjExcep(MyException* ptr);
  void SetObjServ(Server* ptr);
  void ClearAnswers();
  void ClearRequest();
  
  private:
    json jData;
    json jRequestsJSON;
    json jAnswJSON;
    vector<string> vReq;
    shared_ptr<ofstream> fout;
    MyEvent* pEvent=nullptr;
    MyException* pExcep=nullptr;
    Server* pServ=nullptr;
};
#endif