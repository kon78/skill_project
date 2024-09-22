#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include<string>
#include<iostream>
#include<fstream>
#include<exception>

using namespace std;

class MyException : public exception{
private:
    string fname;
    string filenone;
    char * error;
    bool bfex;//bool file exist
    bool bwfn;//bool wrong file name
    bool bfnr;//bool file name request
    bool bfdoc;
public:
    MyException(){}
    const char* nonefiles();
    // MyException();
    char * errors();
    bool filExist();
    bool SetFName(string fn);
    bool fDocsExist(string fn);
    bool readjson(const char* fname);
    const char* what() const noexcept override;
};
#endif