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
    size_t fNumbDiff;
    // char * error;
    string error;
    bool bfex;//bool file exist
    bool bwfn;//bool wrong file name
    bool bfnr;//bool file name request
    bool bfdoc;//bool files docs folder skill_project\\resources
    bool bfwn;//bool files wrong name
    bool bwcf;//bool was changed file
    bool bwcfr;//bool was changed file requests
    bool bnfc;//bool number files changed
    Server* pServObj = nullptr;
    MyEvent* pEvent = nullptr;
public:
    MyException(){}
    const char* nonefiles();
    string& GetWrongName();
    void SetObjServ(Server* ptrObj);
    void SetObjEvent(MyEvent* ptr);
    const char * errors();
    bool filExist();
    bool SetFName(string fn);
    bool fDocsExist(string fn);
    void fDocsNames(string fn);
    bool ReadRequests(const string& req);
    bool ReadDocument(const string& doc);
    bool readjson(const char* fname);
    string& GetWrongNames();
    size_t& GetDiffNumbFile();
    void ChangedFiles(const time_t& difftime,const size_t& fnumb);
    void DiffFilesresources(const size_t& numb1,const size_t& numb2);
    void ChangedFile(const time_t& difftime);
    const char* what() const noexcept override;
};
#endif