#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>
#include<memory>
#include<regex>
#include<cctype>
#include "server.h"
#include "myexception.h"
#include "convjson.h"

using namespace std;

using namespace nlohmann::json_abi_v3_11_3;

std::ostream& operator <<(std::ostream &os, const RelativeIndex &c){
    os << "(document-->" << c.doc_id << ", rank-->" << c.rank << ")\n";
    return os;
}

string makeRegExp(){
  string ret;
  ret = "\\w+\\.\\w+";
  return ret;
}

string makeRegExpFiltRus(){
  string ret;
  ret = "\\!?[а-я]+";//\!?[а-я]+
  return ret;
}

string makeRegExpFiltEnglSymb(){
  string ret;
  ret = "([a-zA-Z\\'\\&\\-\\@]+|![а-я]+|![0-9]+)";
  return ret;
}

string makeRegExpFiltDig(){
  string ret;
  ret = "!?[(0-9)]+";
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

//количество файлов в папке resources должно быть равно константе
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

  ASSERT_EQ(24,cntWrd);
}

TEST(TestApplication, EQUAL_MAP){
  //file config.json должен находиться в папке C:/develop/skill_project/build/tests
  //папка /resources должна находиться в C:/develop/skill_project/build/tests/resources
  MyEvent* myevent = new MyEvent;
  MyException* myexcep = new MyException;
  bool equalMap;
  vector<string>vKey;
  int argc=2; char* argv[] = {"SkillboxSearchEngine", "/r"};
  Server* clServ = new Server(argc,argv);
  SearchService* clSearchServ = new SearchService();
  InvertedIndex* clInvInd = new InvertedIndex();
    clServ->SetObjEvent(myevent);
    clServ->SetExcep(myexcep);
    myexcep->SetObjEvent(myevent);
    myevent->SetObjServ(clServ);

  cout << boolalpha << clServ->Ready() << endl;
  clServ->SetObj(clInvInd);//TEST
  clInvInd->SetObjEvent(myevent);
  clServ->MyWaitTh();//можно не запускать
  clInvInd->SetObjEvent(myevent);
  clInvInd->SetObjExcep(myexcep);
  clInvInd->PrepareDocs(clServ);
  clInvInd->UpdateDocumentBase1();//запускается для тестов, записываются файлы freq_dictionary.map freq_dictionaryTh.map для проверки!!!

  clInvInd->UpdateDocumentBaseThreads();//рабочий метод - поточный

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

//TEST search (непоточный метод)
  const vector<vector<RelativeIndex>> expected = { {{7,1.0},{14,1.0}} };
  clSearchServ->SetObjInvInd(clInvInd);
  clSearchServ->GetInvIndDocs();
  clSearchServ->GetInvIndMap();
  vector<string>queries={"moscow is the capital of russia"};
  vector<vector<RelativeIndex>>result;
  result = clSearchServ->searchTh(queries);
  size_t ind = 0;
  typedef RelativeIndex value;
  typedef RelativeIndex valueC;
  valueC vC;
  size_t rErr = 0;
  for(auto &vec : result){
    for(auto &v : vec){
      vC = expected[0][ind];
      if(vC != v)++rErr;
      ASSERT_EQ(vC, v);

    ind++;
    if(ind == 2)break;
    }
  }
      ASSERT_EQ(rErr, 0);
}

TEST(TestApplication, Sample_Test){
  EXPECT_EQ(1 , 1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}