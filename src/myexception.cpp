#include "myexception.h"

// MyException::MyException() {
//     error = "";
// }
// MyException::MyException() {
//         //  filExist(temp);
// }

bool MyException::SetFName(string fn){
  if(fn == ""){
    error = "no file name\n";
    bwfn = true;//error
    throw "no file name\n";

  }else if(!(fn == "config.json" || fn == "requests.json" || fn == "answers.json")){
    error = "wrong filename\n";
    bwfn = true;//error
    throw errors();
  }
    (*this).fname = fn;
    error = "";
    bwfn = false;
return bwfn;
}
 
bool MyException::filExist(){
  fstream fp;
  fp.open(fname, ios::in);
  if(!fp.is_open()){    
    error = "Config file is missing.\n";
    bfex = false;
    // throw "Config file is missing.\n";
    throw errors();
  }else{
    error = "";
    bfex = true;
  }
  return bfex;
}

char * MyException::errors() {
    return error;
}

const char* MyException::what() const noexcept{
  return error;
}