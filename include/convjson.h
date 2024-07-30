#pragma once
#include"header.h"
#include"service.h"

class ConverterJSON{
  public:
    vector<string> GetTextDocuments();

    ConverterJSON() = default;// ConverterJSON(){}
    // ConverterJSON(){}
    void ParamApp();
    void SetObjServ(shared_ptr<Service> _shrdPtrServ);

    int GetResponsesLimit();
    vector<string> GetRequests();
    void putAnswers(vector<vector<pair<int, float>>>answers);
  
  private:
    // Service* pService = nullptr;
    shared_ptr<Service>shrdPtrServ;
};
