#pragma once
#ifndef SEARCH_H
#define SEARCH_H
#include<vector>
#include<cassert>
#include<memory>
#include<cmath>
#include<algorithm>
#include<unordered_map>
#include<filesystem>
#include<thread>
#include<mutex>
#include<condition_variable>
#include "invertindex.h"
#include"server.h"
#include"convjson.h"

using namespace std;
namespace fs = filesystem;

struct RelativeIndex{
size_t doc_id;
float rank;
bool operator ==(const RelativeIndex& other) const {
return (doc_id == other.doc_id && rank == other.rank);
}
};

typedef pair<size_t,pair<string,size_t>>pairKey;
typedef pair<string,size_t>pairValue;
typedef vector<pair<size_t,pair<string,size_t>>> vCalcRel;

struct EntryThreads;
class Server;
class InvertedIndex;
class SearchService{
public:
  SearchService(){}
  ~SearchService(){}
  void SetObjInvInd(InvertedIndex* _shrdPtrInvInd);
  void GetInvIndMap();
  void GetInvIndDocs();
  vector<vector<RelativeIndex>> searchTh(const vector<string>& queries_input);
  void CalculateRelative(size_t& fieldQueries, const vector<string>& queries_input, vector<string>& vecUncnownWord);
  string makeRegExpSpace();
  void SaveVector();
  void go();
  void ClearVecRelIdx();
  
private:
vector<string>vecUncnownWord;
vector< vector< pair<string,vector<size_t> >> >vecView;
  shared_ptr<InvertedIndex>shrdInvInd;
  unordered_map<std::string, int> filterWords;//уникальные слова получаемые из запроса
  InvertedIndex* ptrInvInd = nullptr;
  vector<string>vRequests;
  vector<vector<size_t>>document;
  json requests;
  unique_ptr<map<string,vector<EntryThreads>>> uMapIdx;
  unique_ptr<vector<string>> uDocsIdx;
  vector<vector<pair<size_t,size_t>>>vecAnswerRabs;
  vector<vector<RelativeIndex>>vecRelIdx;
  vector<vector<bool>>vResult;//для файла answers.json результат найденного ответа true-ответы есть false-ответов нет
  vector<bool>result;//этот вектор для метода Answers1()
  map<string,vector<EntryThreads>> refMapTh;
  mutex global;
  condition_variable cv;
  bool ready;
};

#endif
