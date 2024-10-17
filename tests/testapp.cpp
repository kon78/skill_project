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
  // cout << answer << endl;
}

//для проверки работы метода ConverterJSON::PrepareQueries(...)
//для успешного прохождения содержимое векторов должно быть одинаковым
TEST(TestApplication, JSONQUERIES){
  MyEvent* myevent = new MyEvent;
  MyException* myexcep = new MyException;

  int argc=2; char* argv[] = {"SkillboxSearchEngine", "/r"};
  Server* clServ = new Server(argc,argv);
  SearchService* clSearchServ = new SearchService();
  InvertedIndex* clInvInd = new InvertedIndex();
    clServ->SetObjEvent(myevent);
    clServ->SetExcep(myexcep);
    myevent->SetObjServ(clServ);

  ConverterJSON* clConvJSON = new ConverterJSON();
  clConvJSON->SetObjEvent(myevent);
  clConvJSON->SetObjExcep(myexcep);
  clConvJSON->prepareReqFile();//jRequestsJSON null
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
    myevent->SetObjServ(clServ);

  cout << boolalpha << clServ->Ready() << endl;
  // clServ->SetObjEvent(myevent);
  // clServ->SetExcep(myexcep);
  clServ->SetObj(clInvInd);//TEST
  clInvInd->SetObjEvent(myevent);
  clServ->MyWaitTh();//ожидает изменения в документах на диске
  clInvInd->SetObjEvent(myevent);
  clInvInd->SetObjExcep(myexcep);
  clInvInd->PrepareDocs(clServ);
  clInvInd->UpdateDocumentBase1();//запускается для тестов, записываются файлы freq_dictionary.map freq_dictionaryTh.map для проверки!!!

  clInvInd->UpdateDocumentBaseThreads();//рабочий метод - поточный

  shared_ptr< map< string, vector<EntryThreads> >>shrdMapThrd = clServ->GetMapTst();
  shared_ptr< map< string, vector<Entry> >>shrdMap = clServ->GetMap1Tst();
  // cout << shrdMapThrd.get()->size() << " " << shrdMap.get()->size() << endl;
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
  // result = clSearchServ->search(queries);
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

//1000 words + 100 symbols
TEST(TestApplication, FilesDocs){
  size_t allSymb;
  vector<string> englwords, rusWords, digit;
  fstream fp;
  string temp, temp1, d;
  string fn = "C:\\develop\\skill_project\\build\\tests\\";
  const vector<string>vecWords{"this","is","simple","test","this","is","longest","words","supercalifragilisticexpialidocious",
  "onomatopoeia","hospitable","facilitate","prejudice","pronunciation","prioritising","^^//","3423","dfew","sdfvvvfddc","dfghjytg","hereditary", 
  "particularly","February","regularly","aluminium","это","фраза","на","русском","языке","and","it","shouldn't","be","in","the","line","simple-test","harlay&davidson",
"boss&hoss"};
  d = "files001.txt";
  fn += d;
  fp.open(fn, ios::in);
  if(fp.is_open()){
    // cout << "open" << endl;
    while(!fp.eof()){
      getline(fp,temp);
      temp1 += temp + " ";
    }
  // temp.erase(temp.length()-1);//delete last space
  }
  temp.clear();
  // string::size_type pos;
  vector<string>uncnWords;
  const regex findRegCntWordpnt(".");
  ptrdiff_t const countWord(distance(sregex_iterator(temp1.begin(), temp1.end(), findRegCntWordpnt), sregex_iterator()));
  // cout << "all symbols is " << countWord << endl;

  const regex findRegCntWord(makeRegExpFiltEnglSymb());
  string str;
  std::ptrdiff_t const match_count(distance(sregex_iterator(temp1.begin(), temp1.end(), findRegCntWord),sregex_iterator()));
    for( sregex_iterator itrgx(temp1.begin(), temp1.end(), findRegCntWord), it_end; itrgx != it_end; ++itrgx ){
      str = itrgx->str();
      if([vecWords,str](){
        bool compare = false;
        for(auto &s : vecWords)
          if(str == s)
            compare = true; 
          return compare;
      }())
      englwords.push_back(itrgx->str());
      else
        uncnWords.push_back(str);
    }

size_t len = 0;
for(auto &s : englwords){
  len += s.length();}

#if(do_this == do_not)
  const regex findRegCntWord1(makeRegExpFiltRus());
  std::ptrdiff_t const match_count1(distance(sregex_iterator(temp1.begin(), temp1.end(), findRegCntWord1),sregex_iterator()));
    for( sregex_iterator itrgx(temp1.begin(), temp1.end(), findRegCntWord1), it_end; itrgx != it_end; ++itrgx ){
      rusWords.push_back(itrgx->str());
    }

  for (auto &s : rusWords){
    cout << s << " ";
  }
  cout << endl;
#endif

  const regex findRegCntWord2(makeRegExpFiltDig());
  std::ptrdiff_t const match_count2(distance(sregex_iterator(temp1.begin(), temp1.end(), findRegCntWord2),sregex_iterator()));
    for( sregex_iterator itrgx(temp1.begin(), temp1.end(), findRegCntWord2), it_end; itrgx != it_end; ++itrgx ){
      digit.push_back(itrgx->str());
    }

  size_t dlen = 0;
for(auto &s : digit){
  dlen += s.length();}

  size_t w1 = 0;
  size_t w2 = 0;
  size_t ost = temp1.length();
  // cout << "ost=" << ost << endl;
  for(auto &s : englwords){
    size_t l = s.length();
    w1 += l;
    string::size_type pos = temp1.find(s);
    if(pos > temp1.length())continue;
    temp1.erase(pos,pos+l);
  }
  ost -= w1;
  // cout << "ost=" << ost << endl;

  for(auto &s : digit){
    size_t l = s.length();
    w2 += l;
    string::size_type pos = temp1.find(s);
    temp1.erase(pos,pos+l);
  }
  ost -= w2;

  // cout << "ost=" << ost << endl;

  // cout << temp1 << endl;

// for(auto &s : uncnWords){
//   cout << s << " ";
// }
// cout << endl;
size_t allSymbols = 0;

int cntStr = 0;
int cntEng = 0;
int cntRus = 0;
int Space = 0;
vector<string>vecRus={"электроэнергия"};
vector<char>vecCodeRus;
cout << "size vecRus is " << vecRus.size() << endl;
cout << "size rus is " << vecRus[0].length() << endl;
int t = 0;
for(auto &str : vecWords){
  ++t;
bool view = false;
bool RusSymbols = false;
++cntStr;//счетчик всех символов
  for(auto &c : str){
    ++allSymbols;
    if(ispunct(static_cast<unsigned char>(c)) != 0){
      cout << c;
      view = true;
    }

    if(c == ' ')
      ++Space;

    if(isalpha(static_cast<unsigned char>(c)) != 0){
      ++cntEng;
    }

    if(
      (!isalpha(static_cast<unsigned char>(c)) != 0)            
    ){
      if(!ispunct(static_cast<unsigned char>(c)) != 0){
        if(!isdigit(static_cast<unsigned char>(c)) != 0){
          // size_t ch = static_cast<unsigned char>(c);
          vecCodeRus.push_back((c));
      ++cntRus;
          // continue;
        }
      }
    }
  }
    if(view)
      cout << endl;
    else
      continue;
}
setlocale(LC_ALL, "Russian");
cout << "all symbols is " << allSymbols << endl;
cout << "english characters is " << cntEng << endl;
cout << "russian characters is " << cntRus / 2 << endl;
cout << "space symbols is " << Space << endl;
for(auto &s : vecCodeRus){
  // cout << ((unsigned int)s - 4294967000) << " ";
  cout << ((unsigned int)s * (-1)) << "-" << (unsigned char)s << " ";
}
cout << endl;
// cout << "size vec is " << uncnWords.size() << endl;
  ASSERT_EQ(englwords.size(),33);
  // ASSERT_EQ(rusWords.size(),5);
  ASSERT_EQ(digit.size(),1);


      // cout << temp1 << endl;
  // cout << "long " << temp.length() << endl;
}

TEST(TestApplication, ReadDocument){
  MyEvent* myevent = new MyEvent;
  MyException* myexcep = new MyException;
  
  int argc=2; char* argv[] = {"SkillboxSearchEngine", "/r"};
  Server* clServ = new Server(argc,argv);
    clServ->SetObjEvent(myevent);
    clServ->SetExcep(myexcep);
    myevent->SetObjServ(clServ);
    if(clServ->Ready()){
      clServ->Run();    
  }

  ASSERT_EQ(1,1);
}

//проверка работы оповещения об ошибках в server
TEST(TestApplication, MyEvent_Exception){
MyEvent* myevent = new MyEvent;
MyException* myexcep = new MyException;

  int argc=2; char* argv[] = {"SkillboxSearchEngine", "/r"};
    Server* clServ = new Server(argc,argv);
    clServ->SetObjEvent(myevent);
    clServ->SetExcep(myexcep);
    myevent->SetObjServ(clServ);
    while(true){
      clServ->ReadyTest();

      if(!clServ->GetException())
        break;
    };
    ASSERT_EQ(clServ->GetException(),0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}