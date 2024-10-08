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
  // pServObj->Signal();
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
    bfex = true;
    error = "Config file is missing.\n";
    // throw "Config file is missing.\n";
    pServObj->SetExcep();
    pEvent->SetEvent(0);//wrong name
    pEvent->Signal();
    throw errors();
    // errors();
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
    // errors();
  }
  return bfdoc;
}

bool MyException::ReadDocument(const string& doc){
  vector<string> englwords;
  bool longWord = false;//good < 100
  bool countWord = false;//good < 1000
  error = "";
  const regex findRegCntWord("([a-zA-Z\\'\\&\\-\\@]+|![а-я]+|![0-9]+)");
  std::ptrdiff_t const match_count(distance(sregex_iterator(doc.begin(), doc.end(), findRegCntWord),sregex_iterator()));
    for( sregex_iterator itrgx(doc.begin(), doc.end(), findRegCntWord), it_end; itrgx != it_end; ++itrgx ){
      if(itrgx->str().length() > 100){
        error = "No more than 100 characters per word are allowed.";
        countWord = true;
        throw errors();
        }
      englwords.push_back(itrgx->str());
    }
  if(englwords.size() > 1000){
    error = "No more than 1000 words allowed.";
    longWord = true;
    throw errors();
    }
  return (longWord || countWord);
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