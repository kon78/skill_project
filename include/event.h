#pragma once
#ifndef EVENT_H
#define EVENT_H
#include<iostream>
#include<cassert>
#include<vector>
#include<cassert>
#include"myexception.h"
#include"server.h"

using namespace std;

class Server;
class MyException;
class MyEvent{
  public:
    MyEvent():evCode(0){}
    ~MyEvent(){}
    void Exceptions(MyException* pObjExcep);
    void SetEvent(const size_t ev);
    void SetObjServ(Server* ptr);
    void Signal();
    vector<string>& GetWrongNames();
  private:
    size_t evCode;
    MyException* pMyExcep=nullptr;
    vector<string>wrongName;
    Server* pServ=nullptr;
    string msg;
};
#endif