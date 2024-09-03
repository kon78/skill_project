#pragma once
#ifndef SEARCH_H
#define SEARCH_H
#include<vector>
#include<cassert>
#include<memory>
#include<cassert>
#include<cmath>
#include<algorithm>
#include<unordered_map>
#include "header.h"
#include "service.h"
#include "invertindex.h"

struct RelativeIndex{
size_t doc_id;
float rank;
bool operator ==(const RelativeIndex& other) const {
return (doc_id == other.doc_id && rank == other.rank);
}
};

struct Frequency{
  int count;
  string word;
  size_t _hash;
};

class SearchServer{
public:
  SearchServer(){}
  // template<class M> SearchServer(M&){
  //   map<string, vector<EntryThreads>>& mapInvInd = M&;
  // }
  ~SearchServer(){}
  void SetObjServ(shared_ptr<Service> _shrdPtrServ);
  void SetObjInvInd(InvertedIndex* _shrdPtrInvInd);
  void ReadRequests();
  void GetInvIndMap();
  vector<vector<RelativeIndex>> search(const vector<string>& queries_input);
  void search1();
  template <class T> void sorting(vector<T> &t);
  // template<class T> void SetAddrObj(T* _shared);//{ptrInvInd = _shared;}
  
private:
  shared_ptr<Service>shrdPtrServ;
  shared_ptr<InvertedIndex>shrdInvInd;
  InvertedIndex* ptrInvInd = nullptr;
  vector<string>vRequests;
  vector<vector<size_t>>document;
  json requests;
  unordered_map<size_t,string> uniqueWords;
  hash<string>hashStr;
  vector<string>vecUncnownWord;
  unique_ptr<map<string,vector<EntryThreads>>> uMapIdx;
  // map<string, vector<EntryThreads>>& mapInvInd;
};

//bubblesorting
template <class T> void SearchServer::sorting(vector<T> &t) {
  T value, value1, _swap;
  typename vector<T>::iterator it = t.begin();
  size_t size = t.size();
  size_t pos, pos1;
  bool b = true;
  while (b) {
    b = false;
    for (int i = 0; i < size - 1; ++i) {
      value = t[i];
      value1 = t[i + 1];
      if (t[i].count < t[i + 1].count) {
        it = t.begin();
        advance(it, i);
        pos = distance(t.begin(), it);
        pos1 = pos + 1;
        _swap = value; //запоминаем значение перед изменением
        value = value1;
        value1 = _swap;
        t[pos1] = value1;
        t[pos] = value;
        b = true;
      }
    }
  }
}

// template<class T> void SearchServer::SetAddrObj(T* _shared){
//   try{
//     ptrInvInd = _shared;
//   }catch(exception &ex){
//     cout << "error with pointer!" << ex.what() <<endl;
//     ptrInvInd = nullptr;
//   }
// }
#endif
