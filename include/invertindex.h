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

void print(stThread _thread);

//M.A.R.T.I.N.
class InvertedIndex{
  public:
    InvertedIndex(){}
    ~InvertedIndex(){}
    int ThreadRoutine(vector<string> input_docs);
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
    mutex threadAccess;
};

#endif