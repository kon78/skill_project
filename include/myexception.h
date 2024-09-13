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
    char * error;
    bool bfex;//bool file exist
    bool bwfn;//bool wrong file name
public:
    MyException(){}
    // MyException();
    char * errors();
    bool filExist();
    bool SetFName(string fn);
    const char* what() const noexcept override;
};
#endif