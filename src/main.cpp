// #pragma once
#include<iostream>
#include<chrono>
#include<iomanip>
// #include <thread>
// #include <chrono> 
// #include "service.h"
#include "convjson.h"
#include "invertindex.h"
// #include "search.h"
#include "server.h"
#include "event.h"
#include "myexception.h"

#define Application 1
#define TestApplication 1
#define Editing 1
#define do_this 1
#define do_not 0

using namespace std;
using namespace std::chrono_literals;

char Bunner[] = "Usage: SkillboxSearchEngine [keys /r]";
char keys[] = "\n/r run\n \n/h help\n \n/s service\n";

// void pause_thread(int n)
// {
//   std::this_thread::sleep_for (std::chrono::microseconds(n));
//   std::cout << "pause of " << n << " seconds ended\n";
// }
void AnalysesInfoFiles(const vector<pair<string,time_t>>& vecFiles){
  time_t difftime;
  filesystem::file_time_type ftime;
  string path = "C:\\develop\\skill_project\\resexample";
  while(true){
  for(auto &v : vecFiles){
  
    for(auto &p : fs::directory_iterator(path)){
      if(v.first == p.path().filename().generic_string()){
        ftime = std::filesystem::last_write_time(p);
        auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));

        difftime = cftime - v.second;
        if(difftime > 0)
          cout << v.first << endl;
      }
    }
  }
  }
}

vector<pair<string,time_t>>& SetDataInfoFiles(vector<pair<string,time_t>>&vecRes){
  // vector<pair<string,time_t>>vecRes;
  //read from folder
  fstream fp;
  string fname = "C:\\develop\\skill_project\\resexample\\resfiles.inf";
  pair<string,time_t>prFileDate;
    string temp;
    string fn;
    fp.open(fname.c_str(), ios::in);
    if(fp.is_open()){
      while(!fp.eof()){
        getline(fp,temp);
        // cout << temp << endl;
        string::size_type pos;
        pos = temp.find(".txt");
        if(pos > temp.length()){
          continue;}
        else{
          prFileDate.first = temp.substr(0,pos+4);
          temp.erase(0,pos+4);
          prFileDate.second = stol(temp);
          vecRes.push_back(prFileDate);
        }
      }
    }
  return vecRes;
}

void Folder(shared_ptr<ofstream>& fout){
  cout << "folder\n";
  filesystem::file_time_type ftime;
  vector<string>vecFold;
  vector<pair<string,time_t>>vecFilesInfoTime;
  pair<string,time_t>prFileDate;
  string fdata;

  string path = "C:\\develop\\skill_project\\resexample";
  
  while(true){
  for(auto &p : fs::directory_iterator(path)){

    vecFold.push_back(p.path().filename().generic_string());
    prFileDate.first = p.path().filename().generic_string();
    ftime = std::filesystem::last_write_time(p);
    auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
    prFileDate.second = cftime;

    vecFilesInfoTime.push_back(prFileDate);
    
    // cout << p.last_write_time() << endl;

    // vecFilesInfoTime.push_back(std::filesystem::last_write_time(p));
//  std::cout << "File " <<  p << " write time is " << std::asctime(std::localtime(&cftime)) << '\n';

    // vecFilesInfoTime.push_back(pair(p,cftime));
  }
  if(vecFold.size()>0)break;
  }
  size_t ind = 0;
  for(auto &d : vecFold){
    // cout << d << " ";
    // if(vecFilesInfoTime[ind].first == d){
    //   auto cftime = vecFilesInfoTime[ind].second;
    //   cout << std::asctime(std::localtime(&cftime)) << endl;
    // }
    auto cftime = vecFilesInfoTime[ind].second;

    fdata += d + " ";
    // fdata += asctime(std::localtime(&cftime));
    fdata += to_string(cftime) + "\n";
    fout.get()->write(fdata.c_str(),fdata.length());
    ++ind;
    fdata.clear();
  }
  fout.get()->close();
}

int main(int argc, char *argv[]){
vector<pair<string,time_t>>vecFiles;
// MyException myexcep;

#if(Application == do_not)
MyEvent* myevent = new MyEvent;
MyException* myexcep = new MyException;

  if(argc < 2){
    cout << Bunner << keys;
  }else{
    Server* clServ = new Server(argc,argv);
    clServ->SetObjEvent(myevent);
    clServ->SetExcep(myexcep);
    myevent->SetObjServ(clServ);

    if(clServ->Ready()){
      clServ->Run();  
  }
  }

#endif

#if(TestApplication == do_this)
MyEvent* myevent = new MyEvent;
MyException* myexcep = new MyException;

  if(argc < 2){
    cout << Bunner << keys;
  }else{
    Server* clServ = new Server(argc,argv);
    clServ->SetObjEvent(myevent);
    clServ->SetExcep(myexcep);
    myevent->SetObjServ(clServ);

    if(clServ->Ready()){
      while(true)
        clServ->Run();  
      // clServ->ReadyTest();
  }
  }

#endif

#if(Editing == do_not)

  shared_ptr<ofstream> fout;
  string fname = "C:\\develop\\skill_project\\resources\\resfiles.inf";
  fout = make_shared<ofstream>(fname.c_str(),ios::out);

  thread tfldr(Folder,ref(fout));
  tfldr.join();

  vecFiles = SetDataInfoFiles(vecFiles);

  // for(auto &s : vecFiles)
  //   cout << s.first << " " << s.second << endl;
  
  thread tanls(AnalysesInfoFiles,ref(vecFiles));
  tanls.join();
  
#endif

  return 0;
}