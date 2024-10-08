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
#include<iomanip>
#include<filesystem>
#include<thread>
#include<mutex>
#include<condition_variable>

// #include<tuple>
// #include "service.h"
#include "invertindex.h"
#include"server.h"
#include"convjson.h"

#define do_this 1
#define do_not 0
#define execute 1

using namespace std;
namespace fs = filesystem;

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

  size_t size(){
    size_t ret = vecRel.size();
    return ret;
  }
void printElem(size_t elem);
 string GetWord(size_t elem);
 size_t GetDocid(size_t elem);
    auto GetData(size_t elem);
// pair<int,double> calculate(const size_t& beg, const size_t& elem);
vector<pair<size_t,size_t>> calculate(const size_t& beg, const size_t& elem);
  // void operator=(CalcRel other){
  //   other.phrase = phrase;
  //   other.vecRel
  //   other.vRelWords = vRelWords;
  // }
};

// class SearchServer{
struct EntryThreads;
class Server;
class InvertedIndex;
class SearchService{
public:
  SearchService(){}
  // template<class M> SearchServer(M&){
  //   map<string, vector<EntryThreads>>& mapInvInd = M&;
  // }
  ~SearchService(){}
  // void SetObjServ(shared_ptr<Service> _shrdPtrServ);
  void SetObjInvInd(InvertedIndex* _shrdPtrInvInd);
  void PrepareMap(InvertedIndex* pInvIndObj);
  void ReadRequests();
  void GetInvIndMap();
  void GetInvIndDocs();
  vector<vector<RelativeIndex>> searchTh(const vector<string>& queries_input);
  vector<vector<RelativeIndex>> search(const vector<string>& queries_input);
  void CalculateRelative(size_t& fieldQueries, const vector<string>& queries_input, vector<string>& vecUncnownWord);
  // void search1();
  void Answers1();//выдает ответ только для одного запроса
  void Answers();
  void AnswersJSON();
  string makeRegExpSpace();
  void Hello();
  json& GetJson();
  void SaveVector();
  template <class T> void sorting(vector<T> &t);
  void go();
  // template<class T> void SetAddrObj(T* _shared);//{ptrInvInd = _shared;}
  
private:
// vector<RelativeIndex>vRelIndx;//ответ для релевантностей
vector<string>vecUncnownWord;
vector< vector< pair<string,vector<size_t> >> >vecView;
vector<pair<string,size_t>>uniqueWords;
  // shared_ptr<Service>shrdPtrServ;
  shared_ptr<InvertedIndex>shrdInvInd;
  unordered_map<std::string, int> filterWords;//уникальные слова получаемые из запроса
  InvertedIndex* ptrInvInd = nullptr;
  vector<string>vRequests;
  vector<vector<size_t>>document;
  json requests;
  // unordered_map<size_t,string> uniqueWords;
  // hash<string>hashStr;
  // vector<string>vecUncnownWord;
  unique_ptr<map<string,vector<EntryThreads>>> uMapIdx;
  unique_ptr<vector<string>> uDocsIdx;
  vector<vector<pair<size_t,size_t>>>vecAnswerRabs;
  vector<vector<RelativeIndex>>vecRelIdx;
  json jAnswJSON;
  vector<vector<bool>>vResult;//для файла answers.json результат найденного ответа true-ответы есть false-ответов нет
  vector<bool>result;//этот вектор для метода Answers1()
  map<string,vector<EntryThreads>> refMapTh;
  mutex global;
  condition_variable cv;
  bool ready;

  // map<string, vector<EntryThreads>>& mapInvInd;
};

//bubblesorting
template <class T> void SearchService::sorting(vector<T> &t) {
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
