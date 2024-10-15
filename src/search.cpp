#include"search.h"
using namespace std;

// void SearchService::SetObjServ(shared_ptr<Service> _shrdPtrServ){
//   shrdPtrServ = _shrdPtrServ;  
// }

string SearchService::makeRegExpSpace(){
  string ret;
  ret =  "(\\b(?! )\\w+)";
  return ret;
}

void SearchService::PrepareMap(InvertedIndex* pInvIndObj){
assert(pInvIndObj != nullptr);//проверка на нулевой указатель
refMapTh = pInvIndObj->GetMap();
cout << "Hello! SearchService\n";
}

void SearchService::Hello(){
  cout << "Hello from SearchService!\n";
}

void SearchService::SetObjInvInd(InvertedIndex* _shrdPtrInvInd){
  ptrInvInd = _shrdPtrInvInd;
}

  void CalcRel::printElem(size_t elem){
    // pairKey prKey;
    vCalcRel vecElem = vecRel[elem];
    for(auto &key : vecElem){
      cout << "doc_id " << key.first << " ";
      cout << "word " << key.second.first << " count " << key.second.second << endl;
    }
  }

  string CalcRel::GetWord(size_t elem){
    vCalcRel vecElem = vecRel[elem];
        for(auto &key : vecElem)
    return key.second.first;        
  }


  size_t CalcRel::GetDocid(size_t elem){
     vCalcRel vecElem = vecRel[elem];
        for(auto &key : vecElem)
    return key.first;    
  }

  auto CalcRel::GetData(size_t elem){
vCalcRel vecElem = vecRel[elem];
        for(auto &key : vecElem){
          return make_tuple(key.first,key.second.first,key.second.second);
        }    
  }
//pair<size_t beg, size_t end>
  vector<pair<size_t,size_t>> CalcRel::calculate(const size_t& beg, const size_t& elem){
    cout << "begin " << beg << " elem " << elem << endl;
    // pairKey key;
    // vCalcRel vecElem = vecRel[elem];

    // size_t elem = vecRel.size();
    //ищем одинаковые слова в этом промежутке
    pairKey prKey;
    vector<size_t>vecalg;
    // vCalcRel vecElem = vecRel[beg];
    for(size_t ind = beg; ind < (beg+elem); ++ind){
      // printElem(ind);
      vecalg.push_back(GetDocid(ind));
    }
    // cout << endl;

    for(auto &s : vecalg){
      cout << s <<" ";
    }
    cout << endl;

    sort(vecalg.begin(),vecalg.end());

    for(auto &s : vecalg){
      cout << s <<" ";
    }
    cout << endl;

    vector<size_t>cop;
    cop.clear();
    //получили вектор с одинаковыми документами, то есть в них есть искомые слова
    std::copy_if(vecalg.begin(), vecalg.end(),
                 std::back_inserter(cop),
                 [vecalg](size_t x) { return x == vecalg[0]; });

    for(auto &s : cop){
      cout << s <<" ";
    }
              //doc_id rabs
    vector<pair<size_t,size_t>>vecRabs;
    pair<size_t,size_t>C;
    // pair<int,double>R;
    size_t Rabs=0; double Rrel=0;
    //расчет Rabs для одинаковых документов (на основе векотра vector cop)
    if(!cop.empty() && cop.size() > 1){
      cout << "calculate Rabs!\n";
      size_t docSearch = cop[0];
      cop.clear();
      // for(auto &v : cop){
        //пока нет информации об элементе, придется перебирать все документы из этой подчасти структуры
        vector<size_t>memcalc;//здесь уже посчитанные документы
        bool saveData = false;
        for(size_t ind = beg; ind < (beg+elem); ++ind){
        auto d = GetData(ind);
        Rabs=0;
        if(!saveData){
          vecRabs.push_back(make_pair(0,0));
          saveData = true;}
        if(get<0>(d) == docSearch){
          Rabs = vecRabs[0].second;//выгружаем прежнее значение
          Rabs += get<2>(d);
          C.first = get<0>(d);//doc_id
          C.second = Rabs;
          cout << "doc_id " << C.first << "Rabs " << C.second << endl;
          vecRabs[0] = make_pair(get<0>(d),Rabs);

          // vecRabs.push_back(C);
          memcalc.push_back(get<0>(d));//кладем посчитанные документы
        }else if(get<0>(d) != docSearch){
          Rabs += get<2>(d);
          C.first = get<0>(d);//doc_id
          C.second = Rabs;
          cout << "doc_id " << C.first << "Rabs " << C.second << endl;
          memcalc.push_back(get<0>(d));//кладем посчитанные документы
      vecRabs.push_back(C);
        }
        }
      // }
    }

    cout << "Relevant \n";
    for(auto &r : vecRabs){
      cout << "doc_id " << r.first << " Rabs = " << r.second << endl;
    }

    cout << endl;
    vCalcRel vecElem = vecRel[elem];
    for(auto &key : vecElem){
      Rabs += key.second.second;//Rabs
    Rrel = ((double)Rabs);
    }
    // return make_pair(Rabs,Rrel);
    return vecRabs;
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
  // cout << "size vector queries is " << queries_input.size() << endl;
  for(size_t i = 0; i < countThreads; ++i){
    // cout << queries_input[i] << endl;
    vecThSearchBase.emplace_back(thread(CalculateRelative,this,ref(fieldQueries),ref(queries_input),ref(vecUncnownWord)));
  }

  go();

  for (auto& t: vecThSearchBase) {
    t.join();
    }

  // cout << "size vector threads is " << vecThSearchBase.size() << " " << "fieldQueries is " << fieldQueries << endl;
  // cout << "size map filterWords is " << filterWords.size() << endl;
  #if(do_this == do_not)
  for(auto &m : filterWords){
    cout << m.first << " ";
  }
  cout << endl;
  #endif

#if(do_this == do_not)
  for(auto &v : vecUncnownWord){
    cout << v << " ";
  }
  cout << endl;
#endif

  // cout << "size vector vecView is " << vecView.size() << endl;
#if(do_this == do_not)
  typedef pair<string,vector<size_t>> value;
  value val;
  for(auto & vec : vecView){
    for(auto &v : vec){
      val = v;
      cout << val.first << " ";
      for(auto &d : val.second){
        cout << d << " ";
      }
      cout << endl;
    }
  }
#endif

  // cout << "size vector vRelIndx is " << vecRelIdx.size() << endl;
  #if(do_this == do_not)
  size_t sizeAnswer = 5;
  size_t ind = 0;
  for(auto &vec : vecRelIdx){
    for(auto &v : vec){
      cout << "doc_id " << v.doc_id << " " << v.rank << " ";
      ++ind;
      // if(ind == sizeAnswer)break;
    }
    cout << "\n-------------------------------------------------------" << endl;
    ind = 0;
  }
  #endif
  return vecRelIdx;
}

void SearchService::CalculateRelative(size_t& fieldQueries, const vector<string>& queries_input, vector<string>& vecUncnownWord){
unique_lock<std::mutex> lck(global);
unordered_map<std::string, int> filterWords;
string t;
MyMapTh::iterator itMapIdx = uMapIdx.get()->begin();
MyMapTh::iterator itMapIdxEnd = uMapIdx.get()->end();
MyVectorTh value;
// vector<string>vecUncnownWord;

// while (!ready) cv.wait(lck);
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
    // uniqueWords.push_back(make_pair(m.first,value[1].count));
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

#if(do_this == do_not)
  vector<pair<string,size_t>>::iterator itVecUW;//iterator uniqueWords
cout << "-------------sorting----------------";
      for(itVecUW = uniqueWords.begin(); itVecUW != uniqueWords.end(); ++itVecUW){
        std::cout << itVecUW->first << " ";
        std::cout << itVecUW->second << '\n';
    }
cout << "-------------------------------------\n";
exit(0);
#endif

  vector<pair<string,vector<size_t>>>uniqueWordsDocID;
  vector<size_t> vdoc;
  pair<string,vector<size_t>>vecUDOCID;
  // cout << "size vec is " << uniqueWords.size() << endl;
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
      // cout << endl;
      // vecWordsDoc.clear();
          // cout << " " << Rabs << endl;
          prVecRabs.second = Rabs;
          vecRabs.push_back(prVecRabs);
          relIndx.rank = Rabs;
          vecRel.push_back(relIndx);
          (Rabs > maxRabs)?maxRabs = Rabs:maxRabs = maxRabs;
}
  // vecRelIdx.push_back(vecRel);
  prLinks.second = vecRel;
  vecLinks.push_back(prLinks);
    }
    // cout << endl;
  }

  // vector<RelativeIndex>vRelIndx;
  RelativeIndex rind;
  for(auto &v : vecRabs){
    rind.doc_id = v.first;
    rind.rank = v.second / maxRabs;
    vRelIndx.push_back(rind);
  }
  vecRelIdx.push_back(vRelIndx);

}

vector<vector<RelativeIndex>> SearchService::search(const vector<string>& queries_input){
  // unordered_map<std::string, int> filterWords;//уникальные слова получаемые из запроса
  MyMapTh::iterator itMapIdx = uMapIdx.get()->begin();
  MyMapTh::iterator itMapIdxEnd = uMapIdx.get()->end();
  MyVectorTh value;
    vector<string>vecUncnownWord;
  // vector<string>queries;
  vector<bool>res;//этот вектор в конце положить в вектор vResult для Answers()
//начитка строки из вектора в лямбде
size_t sizeQ = queries_input.size();//для проверки
// vector<string>vecT;
// size_t pos;
  string mem;
  size_t pos=0;size_t pos1=0;

string t;
for(auto &vT : queries_input){
        mem = vT;
        pos = mem.length();
        if(!t.empty()){
          mem.erase(0,pos1);
          pos1 = mem.length();          
          }
        // temp += mem + " ";
        t = mem;
        mem.clear();
        pos1=pos;

        // temp.erase(temp.length()-1);
  // cout << t << endl;
// }
// while(sizeQ != 0){

  // size_t indT = 0;
#if(do_this == do_not)
  {
  t = [vecT](){
  string temp, mem;
  size_t pos=0;size_t pos1=0;
      for(auto &s : vecT){
        mem = s;
        pos = mem.length();
        if(!temp.empty()){
          mem.erase(0,pos1);
          pos1 = mem.length();          
          }
        temp += mem + " ";
        mem.clear();
        pos1=pos;
      }
        temp.erase(temp.length()-1);
      return temp;
}();
  }
#endif

#if(do_this == do_not)
t = [queries_input](){
  string temp, mem;
  size_t pos=0;size_t pos1=0;
      for(auto &s : queries_input){
        mem = s;
        pos = mem.length();
        if(!temp.empty()){
          mem.erase(0,pos1);
          pos1 = mem.length();          
          }
        temp += mem + " ";
        mem.clear();
        pos1=pos;
      }
        temp.erase(temp.length()-1);
      return temp;
}();
cout << t << endl;
#endif
// string t;

// for(auto &t : queries_input){

//уникальные слова получаются из строки string t
vector<string>queries;
unordered_map<std::string, int> filterWords;//уникальные слова получаемые из запроса
const regex rgxSpaces(makeRegExpSpace());
    std::ptrdiff_t const match_count(distance(sregex_iterator(t.begin(), t.end(), rgxSpaces),sregex_iterator()));
    for( sregex_iterator itrgx(t.begin(), t.end(), rgxSpaces), it_end; itrgx != it_end; ++itrgx ){
    size_t v;//любое значение 
      filterWords[itrgx->str()] = v;
      queries.push_back(itrgx->str());//этот вектор необходим для дальнейшей работы!!!
    }
    // t.clear();
//}
  //вывод на экран уникальных слов
      // for(auto &s:filterWords){
      //   cout << s.first << " ";
      // }
      // cout << endl;
  
  unordered_map<std::string, int>::iterator itFiltWrd;
  unordered_map<std::string, int>::iterator itFiltWrdE = filterWords.end();
  
  //vector уникальных слов pair<word,count> количество слов по всем документам
  // vector<string>vecUncnownWord;
  size_t doc_id;
  vector<pair<string,size_t>>uniqueWords;
  for(auto& m : filterWords){
    itMapIdx = uMapIdx.get()->find(m.first);
    if(itMapIdx == itMapIdxEnd){
      vecUncnownWord.push_back(m.first);//неизвестные слова
      continue;}    

    value = itMapIdx->second;
    // uniqueWords.push_back(make_pair(m.first,value[1].count));
    uniqueWords.push_back(make_pair(m.first,[value](){
    size_t count = 0;
      for(auto &v : value)
        count += v.count;
        return count;
}() ));
  }

  if( uniqueWords.size() == 0 ){
    result.push_back(false);
    res.push_back(false);
    }else{
    result.push_back(true);
    res.push_back(true);
    }
//сортировка слов от меньшего к бльшему (по числу упоминаний)
  sort(
    uniqueWords.begin(),
    uniqueWords.end(),
    [](const auto& p1, const auto& p2){
      return tie(p2.second, p1.first) > tie(p1.second, p2.first);
    }
  );

//вывод содержимого вектора на экран
#if(do_this == do_not)
cout << "-------------sorting----------------";
  vector<pair<string,size_t>>::iterator itVecUW;//iterator uniqueWords
      for(itVecUW = uniqueWords.begin(); itVecUW != uniqueWords.end(); ++itVecUW){
        std::cout << itVecUW->first << " ";
        std::cout << itVecUW->second << '\n';
    }
cout << "-------------------------------------\n";
#endif



//}//vector queries 


//(база) вектор слов запроса по всем документам
  vector<pair<string,vector<size_t>>>uniqueWordsDocID;
  vector<size_t> vdoc;
  pair<string,vector<size_t>>vecUDOCID;
  cout << "size vec is " << uniqueWords.size() << endl;
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

//вывод содержимого на экран
#if(do_this == do_not)
  vector<pair<string,vector<size_t>>>::iterator itUWDID;
  for(itUWDID = uniqueWordsDocID.begin(); itUWDID != uniqueWordsDocID.end(); ++itUWDID){
    cout << itUWDID->first << " ";
    for(auto &v : itUWDID->second){
        cout << v << " ";
    }
      cout << endl;
  }
#endif
// exit(0);
  //число документов
  // int cntDoc = shrdPtrServ->numbRespFiles();
  // cout << "size vec docs is " << uDocsIdx.get()->size() << endl;//два раза где-то повторяется

  vdoc.clear();
  vector<pair<string,vector<size_t>>>vecPhrase;
  pair<string,vector<size_t>>prDataInVec;
  for(auto &w : uniqueWords){
    itMapIdx = uMapIdx.get()->find(w.first);
    if(itMapIdx == itMapIdxEnd){
      continue;}
    else{
      value = itMapIdx->second;
      prDataInVec.first = w.first;
      for(auto &v : value){
        vdoc.push_back(v.doc_id);
      }
      prDataInVec.second = vdoc;
      vecPhrase.push_back(prDataInVec);
      vdoc.clear();
    }
  }

  //новый вариант расчета
  size_t Rabs = 0;
  double maxRabs = 0;
  vector<size_t>vCalcRel;
  RelativeIndex relIndx;
  vector<RelativeIndex>vecRel;
  vector<pair<string,vector<size_t>>>::iterator itvPhr;
  vector<pair<size_t,size_t>>vecRabs;//вектор посчитанных релевантностей для документов
  pair<size_t,size_t>prVecRabs;
  vector<pair<vector<string>,vector<RelativeIndex>>>vecLinks;//связи запроса с релевантностями
  pair<vector<string>,vector<RelativeIndex>>prLinks;

  for(itvPhr = uniqueWordsDocID.begin(); itvPhr != uniqueWordsDocID.end(); ++itvPhr){
    cout << itvPhr->first << " ";
    for(auto &v : itvPhr->second){//число документов для расчета релевантностей
      cout << v << " ";
      if(! [v,vCalcRel](){
        bool wasCalc = false;
        for(auto &vec : vCalcRel){
          if(v == vec)
            wasCalc = true;
        }
        return wasCalc;
      }() ){
      // cout << "document " << v << " " << uDocsIdx.get()->at(v);
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
      // cout << endl;
      // vecWordsDoc.clear();
          // cout << " " << Rabs << endl;
          prVecRabs.second = Rabs;
          vecRabs.push_back(prVecRabs);
          relIndx.rank = Rabs;
          vecRel.push_back(relIndx);
          (Rabs > maxRabs)?maxRabs=Rabs:maxRabs=maxRabs;
}
  // vecRelIdx.push_back(vecRel);
  prLinks.second = vecRel;
  vecLinks.push_back(prLinks);
    }
    cout << endl;
  }



//вывод содержимого на экран вектора ответов
#if(do_this == do_not)
for(auto &v : vecRabs){
  cout << "document " << v.first << " Rabs=" << v.second << " Rrel=" << ((double)v.second / maxRabs) << endl;
}
#endif  

//подготовка вектора ответов

#if(do_this == do_not)
//вывод содержимого на экран
typedef pair<vector<string>,vector<RelativeIndex>> prValueLnk;
typedef vector<string>lhpVecLink;//левая часть пары
typedef vector<RelativeIndex>rhpVecLinks;//правая часть пары
 vector<pair<vector<string>,vector<RelativeIndex>>>::iterator itLinks;

size_t sizeVec = vecLinks.size();
for(itLinks = vecLinks.begin(); itLinks != vecLinks.end(); ++itLinks){
  lhpVecLink lhp = itLinks->first;
  rhpVecLinks rhp = itLinks->second;
  while(sizeVec != 0){
    cout << [lhp](){
      string temp;
      for(auto &s : lhp){
        temp += s + " ";
      }
      return temp;
    }();

    pair<size_t,size_t>p;
    for(auto &v : rhp){
      cout << [v](){
              string answ;
              RelativeIndex ri;
              ri = v;              
              answ = to_string(ri.doc_id) + to_string(ri.rank);
              return answ;
      }();
    }

    --sizeVec;
  }
}



//вывод содержимого на экран
  // vector<pair<string,vector<size_t>>>::iterator itvPhr;
  for(itvPhr = uniqueWordsDocID.begin(); itvPhr != uniqueWordsDocID.end(); ++itvPhr){
    cout << itvPhr->first << " ";
    for(auto &v : itvPhr->second){
        cout << v << " ";
    }
      cout << endl;
  }
#endif

//окончательный вывод ответов в виде чисел структуры RelativeIndex
#if(do_this == do_not)
cout << "size vector vecRelIdx is " << vecRelIdx.size() << endl;
cout << "size subvectors is " << vecRelIdx[0].size() << endl;
cout << "all size is " << (vecRelIdx.size() * vecRelIdx[0].size()) << endl;
cout << "  doc_id  " << " relative " << endl;
for(auto & vec:vecRelIdx){
  for(auto &v:vec){
    cout << v.doc_id << "   " << v.rank << endl;
  }
}
#endif
  vector<RelativeIndex>vRelIndx;
  RelativeIndex rind;
  for(auto &v : vecRabs){
    rind.doc_id = v.first;
    rind.rank = v.second / maxRabs;
    vRelIndx.push_back(rind);
  }
  vecRelIdx.push_back(vRelIndx);
  vResult.push_back(res);//сохраняем в векторе вектор ответов bool
  res.clear();//очищаем вектор перед новым проходом
  vRelIndx.clear();
  // queries.clear();
  vecRabs.clear();
  // uniqueWords.clear();
  // filterWords.clear();//очищаем уникальные слова
  vdoc.clear();
  maxRabs = 0;
  --sizeQ;//если все правильно 0
}//

#if(do_this == do_not)
  for(auto &vec:vecRelIdx){
    for(auto &v:vec){
      cout << v.doc_id << " " << v.rank << endl;
    }
  }
#endif

  cout << "result is " << result.size() << " vecRelIdx is " << vecRelIdx.size() << endl;
  cout << "logic is " << res.size() << " vResult is " << vResult.size() << endl;
  assert(result.size() == vecRelIdx.size());//число ответов не совпадает!!!
  // Answers1();
  // Answers();
  return vecRelIdx;
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
    // map<string, vector<EntryThreads>>& mapInvInd = ptrInvInd->GetMap();//выполняется
    uMapIdx = make_unique< map<string, vector<EntryThreads>> >(ptrInvInd->GetMap());//для связи метода SearchService::search()
    // size_t sizeMap = uMapIdx.get()->size();
    // cout << "size map is " << sizeMap << endl;
}

void SearchService::GetInvIndDocs(){
  // vector<string>& vDocsInvInd = ptrInvInd->GetDocs();
  uDocsIdx = make_unique< vector<string> >(ptrInvInd->GetDocs());
  size_t sizeDocs = uDocsIdx.get()->size();
  // cout << "size vec is " << sizeDocs << endl;
}

/*
        try{
         filExist(temp);
      } catch (exception &ex){
          cout << "file " << temp << ". " << ex.what() << "!\n";
      }
*/

void SearchService::ReadRequests(){
#if(do_this == do_not)
  shared_ptr<ifstream> fin;
  char buff[255];
  fin = make_shared<ifstream>("..\\requests.json",ios::in);
  fin.get()->read(buff, sizeof(buff));
  string strData(buff);
  cout << strData << endl;
  //out to console --> pck
  exit(0);

  //zavis
  std::ifstream f("..\\requests.json");
  f.clear();
  f.seekg(0,ios::beg);
  char buff[255];
  while(!f.eof()){
  f.getline(buff,sizeof(buff));
  }
  string str(buff);
  cout << str << endl;
#endif

  // json data = json::parse(fin.get()->read(buff, sizeof(buff)));


  try{
    ifstream f("c:\\skill_project\\build\\requests.json");
    // requests = json::parse(f);

    }catch(exception &ex){
      cout << "can't read or find file " << "requests.json" << endl;
  string ret;
  string path = "C:\\develop\\skill_project";
  for(auto &p : fs::directory_iterator(path)){
    ret += p.path().filename().generic_string();
    ret += " ";
  }
  cout << ret << endl;

  }
  // if(f.is_open()){
  // }else{
  // }
  json data;
  json::iterator it = data.begin();

  try{
    string strTRY = it.key();
  }catch(exception &ex){
    cout << "problems withs json-object requests!\n";
    exit(0);
  }

    cout << "key " << it.key() << " | value: ";
  for(size_t ind = 0; ind < data.size(); ++ind){
    cout << it.value() << " ";
  }
}