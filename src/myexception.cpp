#include "myexception.h"

bool MyException::SetFName(string fn){
  if(fn == ""){
    error = "no file name\n";
    bwfn = true;//error
    throw "no file name\n";

  }else if(!(fn == "config.json" || fn == "requests.json" || fn == "answers.json")){
    error = "wrong file name\n";
    bwfn = true;//error
    throw errors();
  }
    (*this).fname = fn;
    error = "";
    bwfn = false;//
return bwfn;
}

void MyException::SetObjServ(Server* ptrObj){
  assert(ptrObj != nullptr);
  pServObj = ptrObj;
  pServObj->Signal();
}

string& MyException::GetWrongNames(){
  return fileWrong;
}

string& MyException::GetWrongName(){
  return fileWrong;
}

void MyException::SetObjEvent(MyEvent* ptr){
  assert(ptr != nullptr);
  pEvent = ptr;
}

bool MyException::fDocsNames(string fn){
  string name,extension;
  string::size_type posPnt;
  // MyEvent* myevent = new MyEvent;
  bfwn = false;
  posPnt = fn.find(".");
  name = fn.substr(0,posPnt);
  extension = fn.substr(posPnt+1,fn.length());
  if(fn == ""){
    error = "no file name\n";
    bfwn = true;//error
    throw "no file name\n";
  }else if(!(extension == "txt")){
    error = "wrong file name\n";
    bfwn = true;//error
    fileWrong += fn + " ";
    // myevent->Exceptions(this);
    pEvent->SetEvent(100);//wrong name
    throw errors();
  }

  return bfwn;
}

bool MyException::filExist(){
  fstream fp;
  fp.open(fname, ios::in);
  if(!fp.is_open()){    
    error = "Config file is missing.\n";
    bfex = true;
    // throw "Config file is missing.\n";
    throw errors();
  }else{
    error = "";
    bfex = false;
    fp.close();//закрываем после провекри
  }
  return bfex;
}


bool MyException::fDocsExist(string fn){
  string path = "C:\\develop\\skill_project\\resources\\";
  if(filenone.length() == 0) filenone.clear();
  fstream fp;
  fn += path;
  fp.open(fn, ios::in);
  if(!fp.is_open()){    
    error = "";
    bfdoc = true;
    fp.close();//закрываем после провекри
  }else{
    error = "File is missing.\n";
    bfdoc = false;
    filenone += fn + " ";//отсутствующие файлы по условиям задания
    throw errors();
  }
  return bfdoc;
}

bool MyException::readjson(const char* fname){
  string fn;
  fn = fname;
  if(!(fn == "requests.txt" || fn == "config.json")){
    error = "wrong filename\n";
    bfnr = true;//error
    throw errors();
  }else{
    (*this).fname = fn;
    error = "";
    bfnr = false;
  }
  return bfnr;
}

const char* MyException::nonefiles(){
  return filenone.c_str();
}

char * MyException::errors() {
    return error;
}

const char* MyException::what() const noexcept{
  return error;
}