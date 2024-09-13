#pragma once
#ifndef SEVER_H
#define SEVER_H

#include<vector>
#include<cassert>
#include<memory>
#include<cmath>
#include<algorithm>
#include<unordered_map>
#include <iomanip>
#include<fstream>
#include<string>
#include "invertindex.h"

#define do_this 1
#define do_not 0
#define execute 1

using namespace std;

class Server{
public:
Server(int argc, char* argv[]):argumc(argc),start(false),startfName(false),stop(true),run(false){
  fConfJSON = "config.json"; fRequestsJSON = "requests.json";
  ArgumSet(argv);
  examination(fConfJSON);
}
~Server(){}
string makeRegExpKey();
void ArgumSet(char* argv[]);
void examination(const string& fname);
void TouchFile(char* fname);
bool Ready();
void Run(const string& appname);
void KeyApplication();

// bool filExist(string f);


private:
  int argumc;
  size_t keyApp;
  string argumv;
  bool start;//общий старт
  bool startfName;//проверка имен файлов
  bool stop;//общий стоп
  bool run;//разрешение на запуск
  string fConfJSON;
  string fRequestsJSON;
  shared_ptr<ifstream> fin;
  shared_ptr<ofstream> fout;

};
#endif