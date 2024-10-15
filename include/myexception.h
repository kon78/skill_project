#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include<string>
#include<iostream>
#include<fstream>
#include<exception>
#include<memory>
#include<cassert>
#include"server.h"
#include"event.h"

using namespace std;

class Myevent;
class Server;
class MyException : public exception{
private:
    string fname;
    string fileWrong,filenone;
    char * error;
    bool bfex;//bool file exist
    bool bwfn;//bool wrong file name
    bool bfnr;//bool file name request
    bool bfdoc;//bool files docs folder skill_project\\resources
    bool bfwn;//bool files wrong name
    bool bwcf;//bool was changed file
    bool bwcfr;//bool was changed file requests
    Server* pServObj = nullptr;
    MyEvent* pEvent = nullptr;
public:
    MyException(){}
    const char* nonefiles();
    string& GetWrongName();
    void SetObjServ(Server* ptrObj);
    void SetObjEvent(MyEvent* ptr);
    // shared_ptr<Server*> spObj;
    // MyException();
    char * errors();
    bool filExist();
    bool SetFName(string fn);
    bool fDocsExist(string fn);
    void fDocsNames(string fn);
    bool ReadDocument(const string& doc);
    bool readjson(const char* fname);
    string& GetWrongNames();
    void ChangedFiles(const time_t& difftime);
    void ChangedFile(const time_t& difftime);
    const char* what() const noexcept override;
};
#endif