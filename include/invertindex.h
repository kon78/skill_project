#pragma once
#ifndef INVERTINDEX_H
#define INVERTINDEX_H
#include "header.h"
#include"service.h"
#include <map>
#include <regex>
#include <thread>
#include <mutex>
#include <chrono>
// #include <time.h>//?

enum {threadRunTask=100, threadStopTask=101, threadError=99, threadEndedTask=1}enumState;

struct Entry {
  size_t doc_id, count;
};

struct stThread{
  string id;
  int milliseconds;
  int status;
};

void InnerHelloWorld(stThread strucTh);

class Tester
{
  public:
  // Tester(){
  // std::function<void(void)> func;
  //   func = InnerHelloWorld;
  //   // RunTask();
  //   // th(func,0);
  //   // function<void(void)> f_object = strucTh;
  // }
  Tester(stThread strucTh,std::function<void(stThread)> func) : th(func,strucTh){
    // ResetStruct();

  }//working
  // Tester(std::function<void(int)> func1) : th(func1){}
  // void RunTask(){
  //   th(func);
  // }
  void GetAddressStruct(stThread* pStruct);
  ~Tester()
  {
    if(th.joinable())
        th.join();
  }

  Tester(Tester&&) = default;
  private:
  stThread strucTh;
  std::thread th;
};


// mutex dataAccess;

// void print(stThread _thread);

//M.A.R.T.I.N.
class InvertedIndex{
  public:
    InvertedIndex(){}
    ~InvertedIndex(){}
    int ThreadRoutine();
    void ResetStruct(stThread* pStrucThread);
    void UpdateDocumentBase(vector<string> input_docs);
    void UpdateDocumentBaseThread(vector<string> input_docs);
    void SetObjServ(shared_ptr<Service> _shrdPtrServ);
    string makeRegExp(const string &word);
    string _makeRegExp(const string &word);
    // thread makeThread(stThread _thread);
    // static void print(stThread _thread);

    int GetNumbFiles();
  private:
    vector<string> docs;
    vector<stThread> idThreadDocs;
    int iCntRespFiles;//for testing
    map<string, vector<Entry>> freq_dictionary;
    shared_ptr<Service>shrdPtrServ;
    vector<thread*> pVecThreadDocs;
    vector<stThread*> vecStructThreads;//вектор структур
    stThread* pStThread = nullptr;
    vector<Tester> testers;
};

#endif