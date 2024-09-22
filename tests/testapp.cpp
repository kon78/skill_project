// #include <multiply/multiply.h>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
// #include "multiply.h"
// #include "service.h"
// #include "invertindex.h"
// #include "appparam.h"
// #include "appparam.h"
#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>
#include<memory>
#include "server.h"
#include "myexception.h"
#include "convjson.h"

using namespace std;

#define run_test_cin 0
#define do_this 1

using namespace nlohmann::json_abi_v3_11_3;

// std::ostream& operator <<(std::ostream &os, const Entry &c){
//     os << "(document-->" << c.doc_id << ", count repeat-->" << c.count << ")\n";
//     return os;
// }

// std::ostream& operator <<(std::ostream &os, const EntryThreads &c){
//     os << "(document-->" << c.doc_id << ", count repeat-->" << c.count << ")\n";
//     return os;
// }
// TEST(MultiplyTests, TestIntegerOne_One)
// {
//     const auto expected = 1;
//     const auto actual = multiply(1, 1);
//     ASSERT_EQ(expected, actual);
// }


// TEST(MultiplyTests, TestIntegerZero_Zero)
// {
//     const auto expected = 0;
//     const auto actual = multiply(0, 0);
//     ASSERT_EQ(expected, actual);
// }

// TEST(MultiplyTests, TestIntegerZero_One)
// {
//     const auto expected = 0;
//     const auto actual = multiply(0, 1);
//     ASSERT_EQ(actual, expected);
// }

// TEST(TestApplication, TestSerializaton){
//     json jString = "this is a simple test";
//     std::string cppString = jString.dump();
//     EXPECT_EQ(bool(cppString == std::string(jString.dump())), true);
// }

// TEST(TestApplication, TestEqualMap){
//     Service serv;
//     serv.readFile("freq_dictionary.map");
//     vector<string> vec1 = serv.GetDataFile();
//     serv.clearVec();
    
//     serv.readFile("freq_dictionaryTh.map");
//     vector<string> vec2 = serv.GetDataFile();
//     ASSERT_EQ(vec1, vec2);    
// }

// TEST(TestApplication, TestException){
//     int argc = 3; char* argv[] = {" this ", "is ", "test"};
//     char* fname = "config.json";
//     Server serv(argc, argv);

//     serv.examination(fname);
// }
// TEST(MultiplyTests, ClearVector){
// Service serv;
// serv.readFile("config.json");
// int sizeVec = serv.SizeVector();
// EXPECT_EQ(sizeVec > 0, true);
// serv.clearVec();
// sizeVec = serv.SizeVector();
// EXPECT_EQ(sizeVec == 0, true);
// }

// TEST(MultiplyTests, ClearVec1){
//   Service serv;
//   vector<string>vec{"one", "two", "three"};
//   serv.clearVec1(vec);
//   vector<string>vec1;
//   ASSERT_EQ(vec, vec1);
// }

// TEST(MultiplyTests, readFileJSON){
//   Service serv;
//   json j = {
//     {"requests",{
//       "milk water","sugar solt","index"
//     }
//     }
//   };
//   /*файл должен наодиться в папке skill_project\build, если его там, значит его там нет или 
//   он находится в папке skill_project, тогда к имени файла надо добавлять ..\\fname.xyz*/
//   //пока выключил этих механизмы в классе Service
//   // serv.readjson("..\\requests.json");
//   // json t = serv.GetJSON();
//   // cout << "TEST " << t << endl;
//   std::ifstream f("..\\requests.json");
//   json data = json::parse(f);
//   ASSERT_EQ(j, data);
// }

#if(do_this == run_test_cin)
typedef vector<char> symb;
symb s{'a','y','[','(','.','n'};
istream& operator>>(istream& in, symb& other){
  char ch;
  for(auto &c : other){
    ch = c;
    in.get(ch);
    return in;
  }
}
#endif

string makeRegExp(){
  string ret;
  ret = "\\w+\\.\\w+";
  return ret;
}

TEST(TestApplication, CinTest){
  istringstream isch("ay[fje\n#(.n");
  int good = 0;
  char ch;
  int cnt = 0;
  while(!isch.eof()){
    ch = isch.get();
    ++cnt;
    if((cin.fail() || cin.peek() != '\n') && (ch == 'y' || ch == 'n')){
      ++good;
    }
    }
    ASSERT_EQ(good, 2);
    ASSERT_EQ(cnt, 12);
}

TEST(TestApplication, JSONVIEW){
  ConverterJSON* clConvJSON = new ConverterJSON();
  string fConfJSON = "C:\\develop\\skill_project\\config.json";//в тесте не может увидеть имя файла, только весь путь???
  clConvJSON->TestRead(fConfJSON.c_str());
  json jConf = clConvJSON->GetJSON();
  json::iterator it=jConf.begin();
  Server* clServ = new Server;
  string key = "files";
  string answer;
  answer = clServ->ViewValueFiles(it,key);
    const regex findRegCntWord(makeRegExp());
    ptrdiff_t const countWord(distance(sregex_iterator(answer.begin(), answer.end(), findRegCntWord), sregex_iterator()));
    int cntWrd = (int)countWord;//количество слов в строке

  ASSERT_EQ(22,cntWrd);
  // cout << answer << endl;
}

TEST(TestApplication, JSONQUERIES){
  ConverterJSON* clConvJSON = new ConverterJSON();
  clConvJSON->prepareReqFile();
  vector<string>ref;
  const vector<string> except = {"moscow is the capital of russia","bern is the capital of switzerland","tallinn is the capital of estonia",
  "alice in wonderland","moscow never sleeps","paris is the capital of france","now you understand that moscow is behind us and we have nowhere to retreat"};
  const char* fname="C:\\develop\\skill_project\\requests.txt";
  clConvJSON->PrepareQueries(fname);
  ref = clConvJSON->GetRequest();
  size_t err = 100;
  bool equal;
  size_t step = except.size();
  size_t ind = 0;
  if(except.size() == ref.size()){
    err = 0;
    while(step!=0){
      (except[ind] == ref[ind])?equal=true:equal=false;
      if(!equal)++err;
      --step;
    }
  }
  ASSERT_EQ(err,0);
}

TEST(TestApplication, EQUAL_MAP){
  //file config.json должен находиться в папке C:\develop\skill_project\build\tests
  int argc=2; char* argv[] = {"SkillboxSearchEngine", "/r"};
  bool equalMap;
  vector<string>vKey;
  Server* clServ = new Server(argc,argv);
  cout << boolalpha << clServ->Ready() << endl;
  SearchService* clSearchServ = new SearchService();
  InvertedIndex* clInvInd = new InvertedIndex();
  clServ->SetObj(clInvInd);//TEST


  clInvInd->PrepareDocs(clServ);
  clInvInd->UpdateDocumentBase1();//запускается для тестов, записываются файлы freq_dictionary.map freq_dictionaryTh.map для проверки!!!
  clInvInd->UpdateDocumentBaseThreads();
  
  shared_ptr< map< string, vector<EntryThreads> >>shrdMapThrd = clServ->GetMapTst();
  shared_ptr< map< string, vector<Entry> >>shrdMap = clServ->GetMap1Tst();

  ASSERT_EQ(shrdMapThrd.get()->size(),shrdMap.get()->size());
  MyMapTh::iterator it;
    EditMyMapTh edMyMapTh(*shrdMapThrd.get());
    EditMyMap edMyPap(*shrdMap.get());
    for(auto &k : *shrdMapThrd.get()){
      vKey.push_back(k.first);
    }

      int err=100;
      int key = 0; int val = 0;
    for(auto &s : vKey){
      MyVectorTh value = edMyMapTh.GetMapValue(*shrdMapThrd.get(),s);
      MyVector value1 = edMyPap.GetMapValue(*shrdMap.get(),s);
      bool equal; 
      key++;

    if(value.size() == value1.size()){
      err = 0;
      for(size_t sz = 0; sz < value.size(); ++sz){
        val++;
        (value[sz] == value1[sz])?equal=true:equal=false;
        if(!equal)++err;
      }
  }  
}
        ASSERT_EQ(err,0);

///////TEST search
  const vector<vector<RelativeIndex>> expected = { {{7,1.0},{14,1.0}} };
  clSearchServ->SetObjInvInd(clInvInd);
  clSearchServ->GetInvIndDocs();
  clSearchServ->GetInvIndMap();
  vector<string>queries={"moscow is the capital of russia"};
  vector<vector<RelativeIndex>>result;
  result = clSearchServ->search(queries);
  size_t ind = 0;
  typedef RelativeIndex value;
  typedef RelativeIndex valueC;
  valueC vC;
  for(auto &v : result){
    vC = expected[0][ind];
    ASSERT_EQ(vC , v[ind]);
    ind++;
  }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}