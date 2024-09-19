#include"search.h"
using namespace std;

// void SearchServer::SetObjServ(shared_ptr<Service> _shrdPtrServ){
//   shrdPtrServ = _shrdPtrServ;  
// }

string SearchServer::makeRegExpSpace(){
  string ret;
  ret =  "(\\b(?! )\\w+)";
  return ret;
}

void SearchServer::SetObjInvInd(InvertedIndex* _shrdPtrInvInd){
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

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& queries_input){
  unordered_map<std::string, int> filterWords;//уникальные слова получаемые из запроса
  MyMapTh::iterator itMapIdx = uMapIdx.get()->begin();
  MyMapTh::iterator itMapIdxEnd = uMapIdx.get()->end();
  MyVectorTh value;
  vector<string>queries;
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
  cout << t << endl;
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
  vector<pair<string,size_t>>uniqueWords;
  vector<string>vecUncnownWord;
  size_t doc_id;
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
  vector<pair<string,size_t>>::iterator itVecUW;//iterator uniqueWords
#if(do_this == do_not)
      for(itVecUW = uniqueWords.begin(); itVecUW != uniqueWords.end(); ++itVecUW){
        std::cout << itVecUW->first << " ";
        std::cout << itVecUW->second << '\n';
    }
#endif

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
  cout << "size vec docs is " << uDocsIdx.get()->size() << endl;//два раза где-то повторяется

  //новый вариант расчета
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
    for(auto &v : itvPhr->second){//число документов для расчета релевантностей
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
  queries.clear();
  vecRabs.clear();
  uniqueWords.clear();
  filterWords.clear();//очищаем уникальные слова
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
  Answers();
  return vecRelIdx;
}

void SearchServer::Answers(){

jAnswJSON = {{"answers",{}}};
  json::iterator it = jAnswJSON.begin();
  size_t ind = 0;
  size_t vecInd = 0;//для формирования ответов из результатов vecRelIdx
  json value;
  json j;
      vector<pair<size_t,double>>vec2j;
      vector<string>vec2jstr;
      pair<size_t,double>jp;

  for(auto &vec : vResult){
    vector<RelativeIndex>& tempV = vecRelIdx[vecInd];
    for(size_t i = 0; i < vec.size(); ++i){
    string field = "request";
    json jfield;
   ++ind;
    field += [ind](){
      string temp;
      temp = to_string(ind);
      if(temp.length() == 1){
        temp.clear();temp += "00";temp += to_string(ind);
      }else if(temp.length() == 2){
        temp.clear();temp += "0";temp += to_string(ind);
      }else if(temp.length() == 3){
        temp.clear();temp += to_string(ind);}
      return temp;
    }();
    it.value().push_back(field);
    jfield[field] = it.value();

      if(vec[i]){
      json jb = { "result" , true };
      it.value().push_back(jb);
      
    json jr;
    json::iterator itRel = jr.begin();
    size_t i = 0;

#if(do_this == execute)
  for(auto &v : tempV){
    j[i] = {{"doc_id",v.doc_id},{"rank",[v](){
      double t;//floor(v.rank * 1e+4) / 1e+4
      if(v.rank < 1){
        t = floor(v.rank * 1e+3) / 1e+3;}else{
          t = v.rank;
        }
      return t;
    }()}};
    ++i;
    jr["relevance"] = j;
  }
#endif

#if(do_this == do_not)
    for(auto &vec:vecRelIdx){
      for(auto &v:vec){
    j[i] = {{"doc_id",v.doc_id},{"rank",v.rank}};
    jr["relevance"] = j;
    ++i;
    }
    }
#endif

    it.value().push_back(jr);

      }else{
     json jb = { "result" , false };
      it.value().push_back(jb);
      }
    }
    ++vecInd;
  }
  cout << jAnswJSON << endl;
  }

void SearchServer::Answers1(){
jAnswJSON = {
  {
    "answers",{

    }    
  }
};
  json::iterator it = jAnswJSON.begin();
  // pair<string,bool>jp;
  size_t ind = 0;string field = "request";
  json value;
  json j;
      vector<pair<size_t,double>>vec2j;
      vector<string>vec2jstr;
      pair<size_t,double>jp;

  for(auto &v : vecRelIdx){
    if(result[ind]){
    ++ind;
    field += [ind](){
      string temp;
      temp = to_string(ind);
      if(temp.length() == 1){
        temp.clear();temp += "00";temp += to_string(ind);
      }else if(temp.length() == 2){
        temp.clear();temp += "0";temp += to_string(ind);
      }else if(temp.length() == 3){
        temp.clear();temp += to_string(ind);}
      return temp;
    }();

    it.value().push_back(field);
    // j = it.value();
    // value = it.value();
      json jb = { "result" , true };
      it.value().push_back(jb);
      
    json jr;
    // json jparse,jdoc,jrel;
    json::iterator itRel = jr.begin();
    size_t i = 0;
    for(auto &vec:vecRelIdx){
      for(auto &v:vec){
    j[i] = {{"doc_id",v.doc_id},{"rank",v.rank}};
    jr["relevance"] = j;
    ++i;
    }
    }
    it.value().push_back(jr);
    }else{
      json jb = { "result" , false };
      it.value().push_back(jb);
    }
  }
  cout << jAnswJSON << endl;
}

//можно обращаться к коллекции и через обычный указатель
void SearchServer::search1(){
  map<string, vector<EntryThreads>>& mapInvInd = ptrInvInd->GetMap();
  MyMapTh::iterator itK = mapInvInd.begin();
  string strSrch = "milk";
  // try{
  //   itK = mapInvInd->find(strSrch);
  // }catch(exception &ex){
  //   cout << "can't find in object map\n" << ex.what() << endl;
  // }
  cout << "key " << itK->first << "\nvalue ";
  // cout << "size map is " << editM.MapSize(*uMapIdx);//выдает неверный результат - отказаться!!!
  cout << "size value is " << itK->second.size() << endl;
  MyVectorTh value;
  value = itK->second;
    for(int i = 0; i < value.size(); i++){
      cout << "{";
      cout << value[i].doc_id << "," << value[i].count << "}";
    }  

  // json j = shrdPtrServ->GetRequests();
  // cout << "request is " << j << endl;
  json::iterator it = j.begin();
  cout << "key " << it.key() << " value ";
  size_t jsize = it.value().size();
  for(size_t ind = 0; ind < jsize; ++ind){
    cout << it.value()[ind] << " ";
  }
  cout << endl;
}

void SearchServer::GetInvIndMap(){
    map<string, vector<EntryThreads>>& mapInvInd = ptrInvInd->GetMap();
    // size_t sizeMap;
  // try{
    // sizeMap = mapInvInd.size();
    uMapIdx = make_unique< map<string, vector<EntryThreads>> >(mapInvInd);
    size_t sizeMap = uMapIdx.get()->size();
    cout << "size map is " << sizeMap << endl;
    // }catch(exception &ex){
      // cout << "can't do this!" << ex.what() << endl;
  // }
}

void SearchServer::GetInvIndDocs(){
  // vector<string>& vDocsInvInd = ptrInvInd->GetDocs();
  // uDocsIdx = make_unique< vector<string> >(vDocsInvInd);
  size_t sizeDocs = uDocsIdx.get()->size();
  cout << "size vec is " << sizeDocs << endl;
}

/*
        try{
         filExist(temp);
      } catch (exception &ex){
          cout << "file " << temp << ". " << ex.what() << "!\n";
      }
*/

void SearchServer::ReadRequests(){
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