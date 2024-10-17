#include"search.h"
using namespace std;

string SearchService::makeRegExpSpace(){
  string ret;
  ret =  "(\\b(?! )\\w+)";
  return ret;
}

void SearchService::SetObjInvInd(InvertedIndex* _shrdPtrInvInd){
  ptrInvInd = _shrdPtrInvInd;
}

void SearchService::go(){
  std::unique_lock<std::mutex> lck(global);
  ready = true;
  cv.notify_all();
}

vector<vector<RelativeIndex>> SearchService::searchTh(const vector<string>& queries_input){
  vector<thread>vecThSearchBase;
  size_t countThreads = queries_input.size();
  size_t fieldQueries = 1;//start index
  for(size_t i = 0; i < countThreads; ++i)
    vecThSearchBase.emplace_back(thread(CalculateRelative,this,ref(fieldQueries),ref(queries_input),ref(vecUncnownWord)));
  
  go();

  for (auto& t: vecThSearchBase) {
    t.join();
    }

  return vecRelIdx;
}

void SearchService::CalculateRelative(size_t& fieldQueries, const vector<string>& queries_input, vector<string>& vecUncnownWord){
unique_lock<std::mutex> lck(global);
unordered_map<std::string, int> filterWords;
string t;
MyMapTh::iterator itMapIdx = uMapIdx.get()->begin();
MyMapTh::iterator itMapIdxEnd = uMapIdx.get()->end();
MyVectorTh value;

  ++fieldQueries;

  t = queries_input[fieldQueries-2];

  vector<string>queries;
  const regex rgxSpaces(makeRegExpSpace());
  std::ptrdiff_t const match_count(distance(sregex_iterator(t.begin(), t.end(), rgxSpaces),sregex_iterator()));
    for( sregex_iterator itrgx(t.begin(), t.end(), rgxSpaces), it_end; itrgx != it_end; ++itrgx ){
      size_t v;//любое значение 
      filterWords[itrgx->str()] = v;
      queries.push_back(itrgx->str());//этот вектор необходим для дальнейшей работы!!!
    }

  vector<pair<string,size_t>>uniqueWords;
  for(auto& m : filterWords){
    itMapIdx = uMapIdx.get()->find(m.first);
    if(itMapIdx == itMapIdxEnd){
      vecUncnownWord.push_back(m.first);//неизвестные слова
      continue;}    

    value = itMapIdx->second;
    uniqueWords.push_back(make_pair(m.first,[value](){
    size_t count = 0;
      for(auto &v : value)
        count += v.count;
        return count;
}() ));
  }

//сортировка слов от меньшего к бльшему (по числу упоминаний)
  sort(
    uniqueWords.begin(),
    uniqueWords.end(),
    [](const auto& p1, const auto& p2){
      return tie(p2.second, p1.first) > tie(p1.second, p2.first);
    }
  );

  vector<pair<string,vector<size_t>>>uniqueWordsDocID;
  vector<size_t> vdoc;
  pair<string,vector<size_t>>vecUDOCID;
  for(auto &k : uniqueWords){
    itMapIdx = uMapIdx.get()->find(k.first);
    vecUDOCID = make_pair(k.first,vdoc);
    vecUDOCID.first=k.first;
    value = itMapIdx->second;
    for(auto &v : value){
      vdoc.push_back(
      //lambda
      [v](){
        size_t doc = v.doc_id;
        return doc;
      }());
      vecUDOCID.second=vdoc;
    }
      uniqueWordsDocID.push_back(vecUDOCID);
      vdoc.clear();
  }

  vecView.push_back(uniqueWordsDocID);//этот веткор для просмотра работы потоков

size_t Rabs = 0;
double maxRabs = 0;
vector<pair<string,vector<size_t>>>::iterator itvPhr;
vector<size_t>vCalcRel;
pair<size_t,size_t>prVecRabs;
RelativeIndex relIndx;
vector<pair<size_t,size_t>>vecRabs;//вектор посчитанных релевантностей для документов
vector<RelativeIndex>vecRel;
vector<pair<vector<string>,vector<RelativeIndex>>>vecLinks;//связи запроса с релевантностями
pair<vector<string>,vector<RelativeIndex>>prLinks;
vector<RelativeIndex>vRelIndx;

  for(itvPhr = uniqueWordsDocID.begin(); itvPhr != uniqueWordsDocID.end(); ++itvPhr){
    for(auto &v : itvPhr->second){//число документов для расчета релевантностей
      if(! [v,vCalcRel](){
        bool wasCalc = false;
        for(auto &vec : vCalcRel){
          if(v == vec)
            wasCalc = true;
        }
        return wasCalc;
      }() ){
      prVecRabs.first = v;
      relIndx.doc_id = v;//номер документа в струтуру ответа
      string s = uDocsIdx.get()->at(v);
      //считаем Rabs для полученного документа
      SearchSubStrng schSubStrng(s,"");
      vector<string>vecWordsDoc = schSubStrng.GetVec();//возврат по ссылке
          Rabs = 0;
      for(auto &s :vecWordsDoc){
        // cout << s << " ";
        itMapIdx = uMapIdx.get()->find(s);
        if(itMapIdx == itMapIdxEnd){
          continue;
        }else{        
          value = itMapIdx->second;
          // prLinks.first = queries;//запрос для пары связи запроса и ветора релевантностей
          for(auto &d : value){
            if(d.doc_id == v && [queries,itMapIdx](){
              bool compare = false;
              for(auto &s : queries){//queries не очищается
                // cout << s << " ";
                if(s == itMapIdx->first)
                  compare = true;            
                  }
                return compare;  
            }() ){
              if(d.count == 1)
                Rabs += d.count;
              else
                Rabs += (d.count / d.count);
                vCalcRel.push_back(v);//уже посчитанные ранее значения
            // break;
            }
            }        
        }
      }
          prVecRabs.second = Rabs;
          vecRabs.push_back(prVecRabs);
          relIndx.rank = Rabs;
          vecRel.push_back(relIndx);
          (Rabs > maxRabs)?maxRabs = Rabs:maxRabs = maxRabs;
}
  prLinks.second = vecRel;
  vecLinks.push_back(prLinks);
    }
  }

  RelativeIndex rind;
  for(auto &v : vecRabs){
    rind.doc_id = v.first;
    rind.rank = v.second / maxRabs;
    vRelIndx.push_back(rind);
  }
  vecRelIdx.push_back(vRelIndx);
}

void SearchService::ClearVecRelIdx(){
  vecRelIdx.clear();
}

void SearchService::SaveVector(){
  const char* fname = "vrelidx.txt";
  shared_ptr<ofstream> fout;
  fout = make_shared<ofstream>(fname,ios::out);
  string svec;
  string ent="\n";

  for(auto &v : vecRelIdx){
    for(auto &d : v){
      svec = to_string(d.doc_id) + " " + to_string(d.rank) + " ";
      fout.get()->write(svec.c_str(),svec.length());
    }
    fout.get()->write(ent.c_str(),ent.length());
  }
  fout.get()->close();
  fout.reset();
}

void SearchService::GetInvIndMap(){
    uMapIdx = make_unique< map<string, vector<EntryThreads>> >(ptrInvInd->GetMap());//для связи метода SearchService::search()
}

void SearchService::GetInvIndDocs(){
  uDocsIdx = make_unique< vector<string> >(ptrInvInd->GetDocs());
  size_t sizeDocs = uDocsIdx.get()->size();
}
