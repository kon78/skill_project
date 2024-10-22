#pragma once
#ifndef INVERTINDEX_H
#define INVERTINDEX_H
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<cassert>
#include<server.h>
#include<thread>
#include<mutex>
#include<condition_variable>
#include"myexception.h"
#include"event.h"

using namespace std;

#define do_this 1
#define do_not 0
#define execute 1


struct Entry {
  size_t doc_id, count;
  int GetDocId(){return (int)doc_id;}
};

struct EntryThreads{
  size_t doc_id, count;
  void operator=(const EntryThreads& other){
    count = other.count;
    doc_id = other.doc_id;
  }
};

typedef map<string,vector<Entry>> MyMap;
typedef map<string,vector<EntryThreads>> MyMapTh;
typedef vector<Entry> MyVector;
typedef vector<EntryThreads> MyVectorTh;

std::ostream& operator <<(std::ostream &os, const EntryThreads &c);
std::ostream& operator <<(std::ostream &os, const Entry &c);
bool operator==(const Entry& ls, const Entry& rs);
bool operator==(const EntryThreads& ls, const EntryThreads& rs);
bool operator==(const MyVector& ls, const MyVectorTh& rs);
bool operator==(const EntryThreads& ls, const Entry& rs);

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

class Server;
class MyEvent;
class MyException;
//tactical communication
class InvertedIndex{
  public:
    InvertedIndex(){}
    ~InvertedIndex(){}
    void UpdateDocumentBase1();
    void UpdateDocumentBaseThreads();
    string makeRegExp(const string &word);
    string _makeRegExp(const string &word);
    // bool ReadDocument(const string& doc);
    void ClearDocs();
    void PrepareDocs(Server* pServObj);//vector с именами документов в классе Server
    map<string,vector<EntryThreads>>& GetMap();
    map<string,vector<Entry>>& GetMap1();
    template <class K, class V, class N> void SaveMap(map<K, V>& m, N fn);
    void DocBaseThreadNew(size_t &numDocs
                                    // map<string, vector<EntryThreads>> freq_dictionaryTh, 
                                    /*const vector<string> &docs*/);
    void ThreadSleep();
    void SetPath(const string& path);
    void go();
    // void Hello();
    bool MapIsEqual();
    vector<string>& GetDocs();
    void SetObjExcep(MyException* ptr);
    void SetObjEvent(MyEvent* ptr);

  private:
  vector<string> vecFNames;
  string mainPath;
  vector<string>docs;
  map<string, vector<Entry>> freq_dictionary;
  map<string, vector<EntryThreads>> freq_dictionaryTh;
  Entry stEntry;
  condition_variable cv;
  bool ready;
  mutex global;
  thread Th;
  MyEvent* pEvent=nullptr;
  MyException* pExcep=nullptr;
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


#endif