#include"appparam.h"
using namespace std;
string Parameters::makeRegExp(const string &word){
  string ret;
  ret = "(\\b(?!(?!";
  ret += word;
  ret += "))\\w+)";
  return ret;
}

string Parameters::makeRegExpSpace(){
  string ret;
  ret =  "(\\b(?! )\\w+)";
  return ret;
}

void Parameters::SetInvertIndex(){
  string d;
  string question;
  for(auto &d : dataFile){
    const regex findRegExpWord(makeRegExp(question));
    ptrdiff_t const matchCount(distance(sregex_iterator(d.begin(), d.end(), findRegExpWord), sregex_iterator()));
    
  }
}

void Parameters::Prepare(const string& methodName){
  const regex rgxNames (makeRegExpSpace());
  if(methodName == names){
    for( sregex_iterator it(methodName.begin(), methodName.end(), rgxNames), it_end; it != it_end; ++it )
      {
      // cout << (*it)[0] << "\n";
        structNames.methods = (it->str());
        structNames.stat = NO;
        vecNames.push_back(structNames);
      }
  }else if(methodName == passNames){
    for( sregex_iterator it(methodName.begin(), methodName.end(), rgxNames), it_end; it != it_end; ++it )
      {
      // cout << (*it)[0] << "\n";
        structPassing.methods = (it->str());
        vecPassing.push_back(structNames);
      }
  }
}

void Parameters::ReadSettings(){
  fstream fp;
  string temp;
  fp.open(fName, ios::in);
  if(fp.is_open()){
    while(!fp.eof()){
      getline(fp,temp);
      dataFile.push_back(temp);
    }
  // json jConfigApp = {{
  //   "execute",{names},
  //   "passing",{passNames}
  // }};
  }else{
    cout << "Can't read file " << fName << "!\n";
  }
}

void Parameters::ReadTextInfo(){
  fstream fp;
  string temp;
  fp.open(fNameTxt, ios::in);
  if(fp.is_open()){
    while(!fp.eof()){
      getline(fp,temp);
      dataFile.push_back(temp);
    }
  // json jConfigApp = {{
  //   "execute",{names},
  //   "passing",{passNames}
  // }};
  }else{
    cout << "Can't read file " << fNameTxt << "!\n";
  }
}