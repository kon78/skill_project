#pragma once
#ifndef INVERTINDEX_H
#define INVERTINDEX_H
#include <map>
#include <regex>
#include <thread>
#include <mutex>
#include <chrono>
#include <cassert>
#include <condition_variable>
#include <fstream>
#include<iostream>
// #include<server.h>
// #include "service.h"

#define do_this 1
#define do_not 0
#define execute 1

#define switch_off 0
#define switch_on 1
#define switch 1

using namespace std;
enum {threadRunTask=100, threadStopTask=101, threadError=99, threadEndedTask=1}enumState;

struct Entry {
  size_t doc_id, count;
  int GetDocId(){return (int)doc_id;}
};


struct EntryThreads{
  size_t doc_id, count;
  // string str,reg, word;
  // size_t cntWrd;
  // ptrdiff_t number;
  //добавил метод для записи в файл
  void operator=(const EntryThreads& other){
    count = other.count;
    doc_id = other.doc_id;
  }
};

typedef map<string,vector<Entry>> MyMap;
typedef vector<Entry> MyVector;
typedef map<string,vector<EntryThreads>> MyMapTh;
typedef vector<EntryThreads> MyVectorTh;


struct stThread{
  string id;
  int milliseconds;
  int status;

  Entry* pAddrrEntry = nullptr;
  void SetAddress(Entry* pntr){
    if(pntr != nullptr)
      pAddrrEntry = pntr;
  }
};

class SearchSubStrng {
public:
  SearchSubStrng(const string &str, const string &Str1) : match(0),copyStr(str),subStr(Str1) {
    GetVector();
    Search();
  }
  SearchSubStrng(const vector<string>& vecStr,const string &Str1){
    strV = ([vecStr](){
      string ret;
      for(auto &s : vecStr){
        ret += s;
        ret += " ";
      }
      ret.erase(ret.length()-1);
      return ret;
    }());
    copyStr = strV;
    GetVector();
    Search();
  }
  string& GetString();
  void GetVector();
  size_t GetMatch();
  void Search();
  size_t GetSize(){
    return strV.length();
  }
  vector<string>& GetVec(){
    return result;
  }

private:
  vector<string> result;
  // mutex clMutex;
  string copyStr;
  string subStr;
  size_t match;
  string subCopy;
  string::size_type posB;
  string strV;
};


//еще один вариант запуска потоков
#if(do_this == do_not)
class Tester{
  public:
  Tester(){};
    void MakeThreads()
    {
        for (int i = 0; i < 5; ++i)
            vecThreads.push_back(std::thread(&Tester::func, this));
        for (auto& t: vecThreads) t.join();
    }  
  private:
  stThread* pStrucTh;
  void func();
   std::vector<std::thread> vecThreads;
  std::thread th;
};
#endif

  void InnerHelloWorld(stThread* strucTh, mutex* m, int* numb, vector<string>* pVecDocs);

#if(do_this == execute)
class Tester
{
  public:
  #if(do_this == do_not)
  Tester(){
    th(InnerHelloWorld());
  }//working
  #endif
  
#if(do_this == execute)
  Tester(
    stThread* strucTh,
    mutex* m,
    int* numb,
    vector<string>* pVecDocs, 
    function<void(stThread*,mutex*,int*,vector<string>*)> func) : th(
      func,//
      strucTh,//struct 
      m,//mutex pointer class InvertIndex
      numb,//for testing
      pVecDocs//vector pointer docs
      ){}//working
  // Tester(stThread strucTh,std::function<void(stThread)> func) : th(func,strucTh){}
  #endif

  #if(do_this == do_not)
  Tester(){
    std::function<void(Tester)> func = &Tester::hello;    
  }
  #endif
  // void hello(){cout << "hello from class Tester\n";}
  // static void GetAddressStruct(stThread* pAdress);
  ~Tester()
  {
    if(th.joinable())
        th.join();
  }

  Tester(Tester&&) = default;
  private:
  // stThread* pStrucTh;
  // mutex mutexStThread;

  std::thread th;
};
#endif

class EditMyMap{
public:
  EditMyMap(MyMap& EditMap):map(EditMap){}
  ~EditMyMap(){}
  MyMap InitMap(const string& key, MyVector& value, Entry& ent);
  void remove(MyVector& vec, size_t pos);
  bool DeleteValue(MyMap& map, const string& key, const int& elem);
  bool AddedValue(MyMap& map, const string& key, const MyVector& value);
  MyVector GetMapValue(MyMap& map, const string& key);
  size_t MapSize(MyMap& map);
  size_t FindValue(MyMap& map, Entry& ent, const string& key);
private:
  MyMap map;
};

class EditMyMapTh{
public:
  EditMyMapTh(MyMapTh& EditMap):map(EditMap){}
  ~EditMyMapTh(){}
  MyMapTh InitMap(const string& key, MyVectorTh& value, EntryThreads& ent);
  void remove(MyVectorTh& vec, size_t pos);
  bool DeleteValue(MyMapTh& map, const string& key, const int& elem);
  bool AddedValue(MyMapTh& map, const string& key, const MyVectorTh& value);
  MyVectorTh GetMapValue(MyMapTh& map, const string& key);
  size_t MapSize(MyMapTh& map);
  size_t FindValue(MyMapTh& map, EntryThreads& ent, const string& key);
private:
  MyMapTh map;
};


//M.A.R.T.I.N.
class InvertedIndex{
  public:
    InvertedIndex():cntEqualDoc(0),pMutex(new mutex),idThread(0),Th(Sleep, this),ready(false)/**/{}
    ~InvertedIndex(){}
    // void SetObjServ(shared_ptr<Service> _shrdPtrServ);
    void PrepareDocs();
    void UpdateDocumentBase(/*vector<string> input_docs*/);
    void UpdateDocumentBase1();
    void UpdateDocumentBaseThreads();
    void EqualFreqDictionary();
    void EqualFreqDictionary2();
    void CountEqualDocuments(){if(bVecAreEqual)++cntEqualDoc;};
    template <typename VecL, typename vecR>void vec_compare(VecL const &lhs, vecR const &rhs);
    // template <typename Map>
    bool map_compare (/*Map const &lhs, Map const &rhs*/);
    void ThreadRoutine();
    void ThreadSleep();
    void DocBaseThread(int numDocs);
    void DocBaseThreadNew(size_t &numDocs, 
                          // map<string, vector<EntryThreads>> freq_dictionaryTh,
                          const vector<string> &docs
    );
    void DocBaseThreadNew1(size_t& numDocs, 
                          // map<string, vector<EntryThreads>> freq_dictionaryTh,
                          const vector<string> &docs);
    void TestPutToString(string str);
    void Sleep(){this_thread::sleep_for(10ms);}
    void PrepareData(int index);
    void Hello(){cout << "SkillSearchEngine! Hello!\n";}
    string makeRegExp(const string &word);
    string _makeRegExp(const string &word);
    // int GetNumbFiles();
    int GetNumbTest();
    map<string, vector<EntryThreads>>& GetMap();
    string MapGetKey(const string& key );
    MyVectorTh MapGetValue(const string& key);
    template <class K, class V, class N> void SaveMap(map<K, V>& m, N fn);
    template <class x_Object> size_t GetNumbDocs(x_Object &obj);
    int GetNumbFiles();
    vector<string>& GetDocs();
    void go();
  private:
    Entry stEntry;
    EntryThreads stEntryTh;
    // Parameters clParamApp;
    int cntEqualDoc;
    bool bVecAreEqual;
    // map<string, vector<Entry>>::iterator iterMapFreqDict;
    // string str, fStrName, strCopy;//из метода UpdateDocumentBase
    // string::size_type posB;//из метода UpdateDocumentBase
    // vector<Entry>v;//из метода UpdateDocumentBase
    // int index;//из метода UpdateDocumentBase
    stThread* pStThread = nullptr;
    vector<string>::iterator itVecDocs;
    vector<EntryThreads> vRepeatWords;
    mutex* pMutex = nullptr;
    std::condition_variable cv;
bool ready;
mutex global;
    int idThread;//for test
    // mutex global;
    vector<string> docs;
    int iCntRespFiles;//for testing
    map<string, vector<Entry>> freq_dictionary;
    map<string, vector<EntryThreads>> freq_dictionaryTh;
    // shared_ptr<Service>shrdPtrServ;
    vector<Tester> testers;
    vector<string>* pVecDocs;//указатель на список файлов в папке /resource
    thread Th;
    vector<string> forTest;//для проверки работы потоков класса
    // MyMapTh::iterator it;
};


    template <class K, class V, class N> void InvertedIndex::SaveMap(map<K, V>& this_map, N fn){
      ofstream mStream(fn);
      V value;
      for(auto &m : this_map){
        mStream << "[" << m.first << "]";
        value = m.second;
        for(auto &v : value){
          mStream << "{" << v.doc_id << "," << v.count << "}";
        }
        }
        mStream << endl;
      mStream.close();
    }

template <class x_Object> size_t GetServerInfo(x_Object &obj){
  size_t ret = obj.GetNumbFiles();
  return ret;
}
#endif