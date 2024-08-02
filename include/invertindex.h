#pragma once
#ifndef INVERTINDEX_H
#define INVERTINDEX_H
#include "header.h"
#include"service.h"
#include <map>
#include <regex>

struct Entry {
  size_t doc_id, count;
};

//M.A.R.T.I.N.
class InvertedIndex{
  public:
    InvertedIndex(){}
    ~InvertedIndex(){}
    void UpdateDocumentBase(vector<string> input_docs);
    void SetObjServ(shared_ptr<Service> _shrdPtrServ);
    string makeRegExp(const string &word);
    string _makeRegExp(const string &word);
    int GetNumbFiles();
  private:
    vector<string> docs;
    int iCntRespFiles;//for testing
    map<string, vector<Entry>> freq_dictionary;
    shared_ptr<Service>shrdPtrServ;
    
};

#endif