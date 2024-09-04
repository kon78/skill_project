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
#include <iomanip>
// #include<tuple>
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

typedef pair<size_t,pair<string,size_t>>pairKey;
typedef pair<string,size_t>pairValue;
typedef vector<pair<size_t,pair<string,size_t>>> vCalcRel;


struct CalcRel{
  json phrase;
  //table Relative
  vector < 
          vector < 
                  pair <
                        /*doc_id*/
                        size_t, 
                            pair <
                                /*word from phrase*/
                                string, 
                                /*rel count*/
                                size_t> 
          > >>vecRel;
  vector< pair< string,size_t > >vRelWords;

  void NullElem(const string& word){
    pairValue prValue;
    pairKey prKey;
    prValue.first=word,prValue.second=0;
    // pp.first=0;pp.second=(make_pair("",0));
    prKey.first=1000000;prKey.second=prValue;
    vCalcRel v;
    v.push_back(prKey);
    vecRel.push_back(v);
  }
  void push_elem(const string& word, const size_t& doc_id, const size_t& count){
    pairValue prValue(make_pair(word,count));
    pairKey prKey(make_pair(doc_id,prValue));
    vCalcRel v;
    v.push_back(prKey);
    vecRel.push_back(v);
  }
  void printElem(size_t elem){
    pairKey prKey;
    vCalcRel vecElem = vecRel[elem];
    for(auto &key : vecElem){
      cout << "doc_id " << key.first << " ";
      cout << "word " << key.second.first << " count " << key.second.second << endl;
    }
  }

  size_t size(){
    size_t ret = vecRel.size();
    return ret;
  }

  pair<int,double> calculate(size_t elem){
    pair<int,double>R;
    size_t Rabs=0; double Rrel=0;
    // pairKey prKey;
    // pair<int,double>R;
    vCalcRel vecElem = vecRel[elem];
    for(auto &key : vecElem){
      Rabs += key.second.second;//Rabs
    // assert(!(Rabs > 10));
    Rrel = ((double)Rabs);
    // cout << "Rref->" << fixed << setprecision(4) << "[" << R.first << "/10 =" << (double)(4 / 10) << "]" << endl;
    // std::setprecision (std::numeric_limits<double>::digits10 + 1)
        // cout << "Rref->" << "[" << Rabs << "/10 =" << Rrel << "]" << endl;
    }

    return make_pair(Rabs,Rrel);
  }

  // void operator=(CalcRel other){
  //   other.phrase = phrase;
  //   other.vecRel
  //   other.vRelWords = vRelWords;
  // }
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
  void GetInvIndDocs();
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
  unique_ptr<vector<string>> uDocsIdx;
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
