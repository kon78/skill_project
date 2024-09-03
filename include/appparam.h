#include<string>
#include<vector>
#include<regex>
#include<nlohmann/json.hpp>
using namespace nlohmann::json_abi_v3_11_3;
using namespace std;

enum status{YES = 1,NO = 0};

struct MethodsAppStat{
  string methods;
  bool stat;
};

struct MethodPassingInfo{
  string message;
  string methods;
};

typedef vector<MethodsAppStat> MyVectorNamesMethods, MyVectorNamesPassing;
typedef MethodsAppStat MyStructNames;
typedef MethodPassingInfo MyStructPassing;

class Parameters{
  public:
  Parameters():fName("param.txt"),fNameTxt("message.txt"){
    ReadSettings();
    names = "Hello UpdateDocumentBase1 UpdateDocumentBaseThreads";//via spaces names of the methods class InvertedIndex
    Prepare(names);
  }
  ~Parameters(){}
  void SetInvertIndex();
  void Prepare(const string& methodName);//vector
  void ReadSettings();
  void ReadTextInfo();
  string GetDataParam(){return invertind;}
  string makeRegExp(const string &word);
  string makeRegExpSpace();
  private:
  string fName,fNameTxt;
  string invertind;
  string names;
  string passNames;
  vector<string>dataFile;
  MyVectorNamesMethods vecNames;
  MyVectorNamesPassing vecPassing;
  MyStructNames structNames;
  MethodPassingInfo structPassing;
};