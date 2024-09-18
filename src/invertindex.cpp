#include"invertindex.h"

void InvertedIndex::PrepareData(int index){
  // mutex* pRefClInvIndThrd = new mutex;
  pStThread = new stThread();
  pStThread->id = to_string(index);
  pStThread->status = threadRunTask;//выставляем флаг, что задачу можно выполнять
  pStThread->milliseconds = 0;//start time

}

int InvertedIndex::GetNumbTest(){
  return idThread;
}

void InvertedIndex::ThreadSleep(){
  Th.join();
  Th.~thread();
}

void InvertedIndex::ThreadRoutine(){
  for(int i = 0; i < 4; ++i){
  PrepareData(i);

    testers.emplace_back(pStThread,pMutex,&idThread,&docs,InnerHelloWorld);//помещаем в функцию потока данные
  }
  // _sleep(10);
  // this_thread::sleep_for(50ms);
  ThreadSleep();
}

string InvertedIndex::makeRegExp(const string &word){
  string ret;
  // string ret;ret = "(\\b(?!(?!";ret += word;ret += "))\\w+)";
  // ret = "(\\b(?!(?!milk))\\w+)";
  //\b(?!(?!thread))\w+
  ret = "(\\b(?!(?!";
  ret += word;
  ret += "))\\w+)";
  // cout << ret << endl;
  return ret;
}

string InvertedIndex::_makeRegExp(const string &word){
  string ret;
  // string ret;ret = "(\\b(?!";ret += word;ret += ")\\w+)";
  ret = "(\\b(?!";
  ret += word;
  ret += ")\\w+)";
  return ret;
}

void InnerHelloWorld(stThread* strucTh, mutex* m, int* numb, vector<string>* pVecDocs)
{
  // if(strucTh != nullptr){
    // std::lock_guard<std::mutex> guard(*m);
  m->lock();
  for(int i = 0; i < 25; ++i){
    ++(*numb);
  }
  // if(strucTh->status == threadRunTask){
    // while(true){
      cout << "Thread id=" << strucTh->id << "numb is " << *(numb) << endl;

    // }
  // }
  m->unlock();
  // }else{
    // cout << "somthing wrong!\n";
  // }
    
}

// void InvertedIndex::ResetStruct(stThread* pStrucThread){
//   *pStrucThread = {};
// }

// int InvertedIndex::ThreadRoutine(){
//   // stThread* pStrucThread;

//     /*
//     итераторы по map freq_dictionary через них выгружаем адрес структуры, где встречаются
//     и сама строка с содержимым слов
//     */
//     for(int i = 0 ; i < 4 ; i++){
//     pStThread = new stThread();
//     pStThread->id = to_string(i);
//     pStThread->status = threadRunTask;//выставляем флаг, что задачу можно выполнять
//     pStThread->milliseconds = 0;//start time
    
//     /*здесь выставляем адрес структуры Entry, который получаем из map freq_dictionary*/
//     // pStThread->SetAddress();
//     testers.emplace_back(pStThread,InnerHelloWorld);    
//     }    
//   _sleep(10);
//   return 0;
// }

// void InvertedIndex::UpdateDocumentBaseThread(vector<string> input_docs){
//   map<string, vector<Entry>>::iterator iterMapFreqDict;
//   int index = 0; Entry stEntry; smatch m; vector<Entry>v;
//   string path = "C:\\develop\\skill_project\\resources\\";
//   string str, fStrName, strCopy;
//   string::size_type posB;
//   int i = 0;

//   iCntRespFiles = shrdPtrServ.get()->numbRespFiles();
//   str = shrdPtrServ.get()->prepareNameFiles();
//   while(iCntRespFiles != 0){
//     fStrName = path;
//     posB = str.find(" ");
//     if(posB < str.length()){
//       fStrName += str.substr(0,posB);
//       str.erase(0,posB+1);
//       shrdPtrServ.get()->readFile(fStrName);
//       docs = shrdPtrServ.get()->GetDataFile();
//       fStrName.erase();
//       input_docs.push_back(docs[i]);
//       ++i;
//     }

//   --iCntRespFiles;
//   }
// }

std::ostream& operator <<(std::ostream &os, const Entry &c){
    os << "(document-->" << c.doc_id << ", count repeat-->" << c.count << ")\n";
    return os;
}

std::ostream& operator <<(std::ostream &os, const EntryThreads &c){
    os << "(document-->" << c.doc_id << ", count repeat-->" << c.count << ")\n";
    return os;
}

bool operator==(const Entry& ls, const Entry& rs){
  return((ls.doc_id == rs.doc_id) && 
    (ls.count == rs.count)
    );
}

bool operator==(const EntryThreads& ls, const EntryThreads& rs){
  return((ls.doc_id == rs.doc_id) && 
    (ls.count == rs.count)
    );
}

bool operator==(const MyVector& ls, const MyVectorTh& rs){
bool ret = true;
  for(auto &l : ls){
    for(auto &r : rs){
      if(l.doc_id == r.doc_id && l.count == r.count){
        continue;
      }else{
      ret = false; break;
      }
    }
    if(!ret)break;
  }
  return ret;
}
#if(switch == switch_off)

void InvertedIndex::UpdateDocumentBaseThreads(){
  vector<thread>vecThDocBase;
  map<string, vector<Entry>>::iterator iterMapFreqDict;
  int index = 0; Entry stEntry; smatch m; vector<Entry>v;
  string path = "C:\\develop\\skill_project\\resources\\";
  string str, fStrName, strCopy;
  string::size_type posB;
  int i = 0;
  //повторное фомирование не нужно!!!
  // PrepareDocs();
  size_t countThreads = shrdPtrServ.get()->numbRespFiles();
  size_t fieldDocs = -1;//start index
  if(countThreads % 10 > 1)
  pVecDocs = &shrdPtrServ.get()->prepareNameFilesVec();
  cout << "size vector docs is " << docs.size() << endl;
  for(size_t i = 0; i < countThreads; ++i){//(int i = 0; i < countThreads; ++i)
    // vecThDocBase.push_back(thread(DocBaseThread,this,i));
    // vecThDocBase.emplace_back(thread(DocBaseThread,this,i));
    vecThDocBase.emplace_back(thread(DocBaseThreadNew,this,ref(fieldDocs),/*freq_dictionaryTh*/ref(docs)));
  }
  //run threads

  ThreadSleep();
  go();

  for (auto& t: vecThDocBase) {
    t.join();
    }

#if(do_this == do_not)
  int th = 0;
  const int ten = 10;
  if(countThreads % 10 > 1){
    int cntVectorsTens = countThreads % 10;
    int remaindVec = cntVectorsTens - ((countThreads % 10) * 10);
    for(int i = 0; i < cntVectorsTens; ++i){
      for(int j = 0; j < ten; ++j){
        vecThDocBase[th].join();
        ++th;
      }
    }
    for(int k = 0; k < remaindVec; ++ k){
      vecThDocBase[th].join();
      ++th;
    }
  }else{
  for (auto& t: vecThDocBase) {
    t.join();
    }
  }
#endif

  
  // cout << "after working " << countThreads << " threads count is " << idThread << endl;
  // cout << "result----------\n";
  cout << "size freq_dictionaryTh is " << freq_dictionaryTh.size() << endl;

//здесь определяем число повторений в map freq_dictionaryTh
  vector<string> vDubl;
  // vector<EntryThreads> vStructEnt;
  for(auto it = freq_dictionaryTh.cbegin(); it != freq_dictionaryTh.cend(); ++it){
    if(it->second.size() > 1){
      vDubl.push_back(it->first);
    }    
  }
  cout << "count repeats words is " << vDubl.size() << endl;
  // for(auto &s : vDubl){
  //   cout << s << endl;
  // }
//вывод на экран содержимого map freq_dictionaryTh - рабочий вариант
#if(do_this == do_not)
    vector<EntryThreads>vTempEntry;
    string strIndexTemp;

  for(auto &fd : freq_dictionaryTh){
    strIndexTemp = fd.first;
    vTempEntry = fd.second;
    int sizeStruct = vTempEntry.size();
    cout << "\nindex<" << strIndexTemp << ">=";
    for(int i = 0; i < sizeStruct; i++){
      cout << "{";
      cout << vTempEntry[i].doc_id << "," << vTempEntry[i].count << "}";
    }
    vTempEntry.clear();
  }
#endif

  SaveMap(freq_dictionaryTh,"freq_dictionaryTh.map");

  cout << "\nmap compare is " << boolalpha << map_compare() << endl;
}
#endif

size_t SearchSubStrng::GetMatch() { 
  //  std::lock_guard<std::mutex> guard(clMutex);
  return match; }

void SearchSubStrng::Search() {
  // std::lock_guard<std::mutex> guard(clMutex);
  for (auto &r : result) {
    if (r == subStr)
      ++match;
  }
}

void SearchSubStrng::GetVector() {
  // std::lock_guard<std::mutex> guard(clMutex);
  while (copyStr.length() > 0) {
    posB = copyStr.find(" ");
    if (posB > copyStr.length()) {
      result.push_back(copyStr);
      break;
    }
    subCopy = copyStr.substr(0, posB);
    copyStr.erase(0, posB + 1);
    result.push_back(subCopy);
  }
#if(do_this == do_not)
    for(auto &s : result){
      cout << s << " ";
    cout << endl;
    }
    std::getchar();
#endif
}

string& SearchSubStrng::GetString(){
  return copyStr;
}

void InvertedIndex::DocBaseThreadNew1(size_t& numDocs, const vector<string> &docs){
// mutex global;
// lock_guard<mutex>guard(global);
unique_lock<std::mutex> lck(global);
while (!ready) cv.wait(lck);
++numDocs;
  cout << "thread say " << docs[numDocs] << endl;
  // cout << "thread say " << numDocs << endl;
}

void InvertedIndex::go() {
  std::unique_lock<std::mutex> lck(global);
  ready = true;
  cv.notify_all();
}

#if(switch == switch_off)
void InvertedIndex::DocBaseThreadNew(size_t &numDocs, 
                                    // map<string, vector<EntryThreads>> freq_dictionaryTh, 
                                    const vector<string> &docs

){
// mutex global;
// lock_guard<mutex>guard(global);
unique_lock<std::mutex> lck(global);
string str,key, reg,strCopy, strC;
string::size_type posB;
string::size_type posF;
EntryThreads stEntryTh;
MyVectorTh value;
map<string, vector<EntryThreads>>::iterator iterSearchTh;
EditMyMapTh editMyMap(freq_dictionaryTh);

while (!ready) cv.wait(lck);
++numDocs;

  str = docs[numDocs];//своемоу потоку своя строка
  strC = str;
  const regex findRegCntWord(_makeRegExp("%"));
  ptrdiff_t const countWord(distance(sregex_iterator(str.begin(), str.end(), findRegCntWord), sregex_iterator()));
  size_t cntWrd = (size_t)countWord;//количество слов в строке
  stEntryTh.doc_id = numDocs; /*stEntryTh.str = str;*/
    while(cntWrd != 0){
      if(str.length() > 0){
        posB = str.find(" ");
        key = str.substr(0,posB);//слово для поиска
        str.erase(0,posB+1);        
        SearchSubStrng clSrchSubStr(strC,key);//мой класс для посика слова в строке
        stEntryTh.count = clSrchSubStr.GetMatch();//match
        if(!freq_dictionaryTh.empty()){
          iterSearchTh = freq_dictionaryTh.find(key);//ищем по ключу
          if(iterSearchTh->first == key){//есть ли такой ключ в колкции
            size_t pos = editMyMap.FindValue(freq_dictionaryTh,stEntryTh, key);//есть ли такой элемент в векторе
            if(pos == 1000000){
//               //элемента в векторе нет
              value = iterSearchTh->second;
              value.push_back(stEntryTh);
              editMyMap.AddedValue(freq_dictionaryTh, key, value);//добавдяем вектор
              //printing result
              iterSearchTh = freq_dictionaryTh.find(key);
              // value = iterSearchTh->second;
              // for(auto &v : value){
              //   cout << v;
              // }
//               cout << endl;
            }

          }else{
            // нет такого ключа, добавляем
            freq_dictionaryTh[key];//добавляем ключ
            iterSearchTh = freq_dictionaryTh.find(key);
            value = iterSearchTh->second;
            value.push_back(stEntryTh);
            editMyMap.AddedValue(freq_dictionaryTh, key, value);//добавдяем вектор
          }
        }else{
          freq_dictionaryTh = editMyMap.InitMap(key,value,stEntryTh);//изначально пустая коллекция
        }
          
//         }
      }
      --cntWrd;
    }//while
//         // vEntTh.clear();
//здесь удаляем dataFile в классе Service
  shrdPtrServ.get()->clearVec();
}
#endif

void InvertedIndex::DocBaseThread(int numDocs){
  vector<EntryThreads>v;//из метода UpdateDocumentBase
  string::size_type posB;//из метода UpdateDocumentBase
  string str, fStrName, strCopy;//из метода UpdateDocumentBase
  mutex mDocBase,mNumDocs,mFreqDict,mWrdSave,mFunc,mMatchCount;
  map<string, vector<EntryThreads>>::iterator iterMapFreqDict;
  // Entry stEntryTh;

  mNumDocs.lock();
  int index = numDocs;
  mNumDocs.unlock();

  mDocBase.lock();
#if(do_this == do_not)  
  TestPutToString(shrdPtrServ.get()->GetFName(idThread));//кладет в вектор имена файлов
#endif
/*
получаем строку, здесь docs в перспективе надо заменить на input_docs
docs и input_docs вектора freq_dictionaryTh
*/
  mNumDocs.lock();
  str = docs[index];
  mNumDocs.unlock();
  // mWrdSave.lock();
  // bool wrdSave = false;
  // mWrdSave.unlock();
  mFunc.lock();
  const regex findRegCntWord(_makeRegExp("%"));
  mFunc.unlock();
  ptrdiff_t const countWord(distance(sregex_iterator(str.begin(), str.end(), findRegCntWord), sregex_iterator()));
  int cntWrd = (int)countWord;//количество слов в строке
    //stEntryTh.cntWrd = (int)countWord;;
    mNumDocs.lock();
    ++index;
    mNumDocs.unlock();
    while(cntWrd != 0){
    if(str.length() > 0){
      // stEntry.count=0;stEntry.doc_id=0;
      mNumDocs.lock();
    stEntryTh.doc_id = index;//index увеличиваем на 1 после прохождения цикла
      mNumDocs.unlock();
      // ++cntWord;
      posB = str.find(" ");
        strCopy = str.substr(0,posB);
        str.erase(0,posB+1);
        mFunc.lock();
        // string ret;ret = "(\\b(?!(?!";ret += strCopy;ret += "))\\w+)";
        // const regex findRegExpWord(ret);
        const regex findRegExpWord(makeRegExp(strCopy));
        this_thread::sleep_for(5ms);
        mFunc.unlock();
        mMatchCount.lock();
        ptrdiff_t const matchCount(distance(
          sregex_iterator(str.begin(), str.end(), findRegExpWord), sregex_iterator()));
        this_thread::sleep_for(5ms);
//начинает правильно заполнять словарь через раз
        // std::cout << "index-->" << index << " " << strCopy << " count --> " << matchCount << endl;
        // cout << matchCount << index;
        stEntryTh.count = (int)matchCount;//+1???
        //stEntryTh.str = strCopy;
        mMatchCount.unlock();
        // this_thread::sleep_for(1ms);
        // cout << ".";
        mNumDocs.lock();
        stEntryTh.doc_id = index;//повторяемся, если так удалить эту строку
        mNumDocs.unlock();
        mFreqDict.lock();
        if(freq_dictionaryTh.size() != 0){
          iterMapFreqDict = freq_dictionaryTh.find(strCopy);//поиск по ключу
            // mWrdSave.lock();
            if(iterMapFreqDict->first == strCopy/* && !wrdSave*/){
              (iterMapFreqDict->second).push_back(stEntryTh);
              // wrdSave = true;//сюда больше не заходим в этом документе index
        }else{
          v.clear();
          v.push_back(stEntryTh);
          freq_dictionaryTh.insert(pair<string,vector<EntryThreads>>(strCopy, v));
        }
        // mWrdSave.unlock();
        }else{
          v.push_back(stEntryTh);
          freq_dictionaryTh.insert(pair<string,vector<EntryThreads>>(strCopy, v));
          v.clear();
        }
        mFreqDict.unlock();
    }
    --cntWrd;
    }//while
    // ++index;
    v.clear();
  ++idThread;
  mDocBase.unlock();  
  // this_thread::sleep_for(1ms);//спорно!!!
}

void InvertedIndex::TestPutToString(string str){
  forTest.push_back(str);
}

#if(switch == switch_on)
void InvertedIndex::PrepareDocs(){
  string path = "C:\\develop\\skill_project\\resources\\";
  string str, fStrName; 
  string::size_type posB;
  int i = 0;
  // iCntRespFiles = shrdPtrServ.get()->numbRespFiles();
  // iCntRespFiles = Server::numbFiles;
  // Server s = Server();
  // s.GetNumbFiles(s);
  // str = shrdPtrServ.get()->prepareNameFiles();
  // cout << str << endl;
  while(iCntRespFiles != 0){
    fStrName = path;
    posB = str.find(" ");
    if(posB < str.length()){
      fStrName += str.substr(0,posB);
      str.erase(0,posB+1);
      // shrdPtrServ.get()->readFile(fStrName);
      // docs = shrdPtrServ.get()->GetDataFile();
      // shrdPtrServ.get()->clearVec();//помоему не стоит тут так делать!!!
      // cout << "file " << fStrName << endl;
      fStrName.erase();
      // input_docs.push_back(docs[i]);
      ++i;
    }

  --iCntRespFiles;
  }

}
#endif

vector<string>& InvertedIndex::GetDocs(){
  return docs;
}

bool my_equal(const Entry &entl, const EntryThreads &entr) {
  bool ret;
  ret = ((entl.doc_id+1 == entr.doc_id) && (entl.count == entr.count));
  return ret;
}

template <typename VecL, typename vecR>
void InvertedIndex::vec_compare(VecL const &lhs, vecR const &rhs) {
  bVecAreEqual = true;
  if (lhs.size() == rhs.size()) {
    cout << "size are equal\n";
    for (int i = 0; i < lhs.size(); ++i) {
      cout << lhs[i] << " " << rhs[i] << endl;
      bVecAreEqual = my_equal(lhs[i], rhs[i]);
      CountEqualDocuments();
      if(!bVecAreEqual)break;
      ++i;
    }
  }
}

void InvertedIndex::EqualFreqDictionary2(){
  // map<string, vector<Entry>>::iterator iterMapFreqDict;
  map<string, vector<EntryThreads>>::iterator iterMapFreqDictTh;
  string str;
  if(freq_dictionary.size() == freq_dictionaryTh.size()){
    for(auto it = freq_dictionary.cbegin(); it != freq_dictionary.cend(); ++it){
      str = it->first;
      iterMapFreqDictTh = freq_dictionaryTh.find(str);
      cout << "---------------------------------------------\n";
      cout << "index-->" << str << " index-->" << iterMapFreqDictTh->first << "\n";
      if(str == iterMapFreqDictTh->first){//strings are equal
        cout << "s=" << (it->second).size() << " s=" << (iterMapFreqDictTh->second).size() << "\n";
        // cout << it->second << " " << iterMapFreqDictTh->second << "\n";
        vec_compare(it->second, iterMapFreqDictTh->second);
        if(bVecAreEqual)cout << boolalpha << true << " " << endl; else cout << false << " " << endl;
      }
    }
  }
    cout << endl;

    cout << "count equal documents is " << cntEqualDoc << endl;
    cout << "count not equal documents is " << freq_dictionary.size()-cntEqualDoc << endl;
}
//пока оставим как есть
void InvertedIndex::EqualFreqDictionary(){

// #if(do_this == do_not)
  map<string, vector<Entry>>::iterator iterDocBase;
  map<string, vector<EntryThreads>>::iterator iterDocBaseTh;
  // vector<Entry>::iterator iterEntry;
  // vector<Entry> vEntry;
  size_t doc_id, count;
// map<string, vector<Entry>>::iterator iterMapFreqDict,iterMapFreqDictTh;
  cout << "size freq_dictionary is " << freq_dictionary.size() << "size freq_dictionaryTh is " <<
      " " << freq_dictionaryTh.size() << endl;
int i;
for(auto it = freq_dictionary.cbegin(); it != freq_dictionary.cend(); ++it){
  i = 0;
  string str = it->first;
  iterDocBaseTh = freq_dictionaryTh.find(str);
  if(str == iterDocBaseTh->first){
    int sizeVecEntry = (it->second).size();
    int sizeVecEntryTh = (iterDocBaseTh->second).size();
    if(sizeVecEntry == sizeVecEntryTh){
      auto iterFreqDictVecEntry = it->second;
      auto iterFreqDictVecEntryTh = iterDocBaseTh->second;
      for(auto itVec = iterFreqDictVecEntry.cbegin(); itVec != iterFreqDictVecEntry.cend(); ++itVec){
        auto itVecTh = iterDocBaseTh->second;
        if(itVec->count == itVecTh[i].count && itVec->doc_id+1 == itVecTh[i].doc_id){
        cout << boolalpha << true << " ";
        }else{
          cout << boolalpha << false << " ";
        }
        ++i;
      }
      //itStrucEntry
      // for(auto itTh = freq_dictionaryTh.cbegin(); itTh != freq_dictionaryTh.cend(); ++itTh){
      //   // (iterDocBaseTh->second == *itStrucEntry)
      //   auto iterEntryTh = itTh->second;
      //   int i = 0;
      //   // if(itStrucEntry == iterEntryTh)
      //   // cout << str << " " << itTh->second << " " << iterDocBaseTh->first << iterEntryTh[i] << endl;
      //   if(itStrucEntry->count == iterEntryTh[i].count && 
      //   itStrucEntry->doc_id+1 == iterEntryTh[i].doc_id){
      //     ++i;
      //     cout << boolalpha << true << " ";
      //   }else{
      //     cout << boolalpha << false << " ";
      //   }        
      // }
      cout << endl;
    }
  }
  // for(auto itTh = freq_dictionaryTh.cbegin(); itTh != freq_dictionaryTh.cend(); ++itTh){
  //   string str = (it->first); string strTh = (itTh->first);
  //   if(str == strTh){
  //     for(auto itStrucEntry = it->second.cbegin(); itStrucEntry != it->second.cend(); ++itStrucEntry){
  //       for(auto itStrucEntryTh = it->second.cbegin(); itStrucEntry != it->second.cend(); ++itStrucEntry){
  //   //itStrucEntry - vector Entry
  //       if(str == strTh && itStrucEntry == itStrucEntryTh){
  //         cout << boolalpha << true << " ";
  //         continue;}
  //       else{ 
  //         cout << boolalpha << false << " ";
  //         break;}
  //         // if((itTh->second).size() > 1)
  //         // ++itStrucEntryTh;
  //     }
  //   }
  //   cout << endl;
  //   }
  // }
    // itStrucEntry
  // iterEntry = it->second;
}
// #endif
  
}

// template <typename Map>
// bool InvertedIndex::map_compare (/*Map const &lhs, Map const &rhs*/){
//  return freq_dictionary.size() == freq_dictionaryTh.size();
        // && std::equal(freq_dictionary.begin(), freq_dictionary.end(),
                      // freq_dictionaryTh.begin());
// }



bool InvertedIndex::map_compare (/*Map const &lhs, Map const &rhs*/){
  bool ret = false;
  MyMap::iterator it;
  MyMapTh::iterator itTh;
  MyVector vec;
  MyVectorTh vecTh;

  if(freq_dictionary.size() == freq_dictionaryTh.size()){
    for(it = freq_dictionary.begin(); it != freq_dictionary.end(); ++it){
      for(itTh = freq_dictionaryTh.begin(); itTh != freq_dictionaryTh.end(); ++itTh){
        if(it->first == itTh->first){
          if(it->second == itTh->second){
            ret = true;
          }
          else{ ret = false; break;}
        }
      }

    }
  }
    return ret;
}

//without threads routine

void InvertedIndex::UpdateDocumentBase1(){
  map<string, vector<Entry>>::iterator itSearch;
  EditMyMap editMyMap(freq_dictionary);
  int index = 0;//отсчет файлов
  MyVector value;
  string str, key;
  string::size_type posB;
  PrepareDocs();
  for(auto &d : docs){
    str = d;//получаем строку
    const regex findRegCntWord(_makeRegExp("%"));
    ptrdiff_t const countWord(distance(sregex_iterator(d.begin(), d.end(), findRegCntWord), sregex_iterator()));
    int cntWrd = (int)countWord;//количество слов в строке
    while(cntWrd != 0){
      if(str.length() > 0){
        posB = str.find(" ");
        key = str.substr(0,posB);
        str.erase(0,posB+1);
        const regex findRegExpWord(makeRegExp(key));
        ptrdiff_t const matchCount(distance(sregex_iterator(d.begin(), d.end(), findRegExpWord), sregex_iterator()));
        stEntry.count = (int)matchCount;
        stEntry.doc_id = index;//повторяемся, если так удалить эту строку
        // cout << "size map is " << editMyMap.MapSize(freq_dictionary) << endl;
        if(!freq_dictionary.empty()){
          itSearch = freq_dictionary.find(key);//ищем по ключу
          if(itSearch->first == key){//есть ли такой ключ в колкции
            size_t pos = editMyMap.FindValue(freq_dictionary,stEntry, key);//есть ли такой элемент в векторе
            if(pos == 1000000){
              //элемента в векторе нет
              value = itSearch->second;
              value.push_back(stEntry);
              editMyMap.AddedValue(freq_dictionary, key, value);//добавдяем вектор
              //printing result
              itSearch = freq_dictionary.find(key);
              value = itSearch->second;
#if(do_this == do_not)              
              for(auto &v : value){
                cout << v;
              }
              cout << endl;
#endif              
            }

          }else{
            //нет такого ключа, добавляем
            freq_dictionary[key];//добавляем ключ
            itSearch = freq_dictionary.find(key);
            value = itSearch->second;
            value.push_back(stEntry);
            editMyMap.AddedValue(freq_dictionary, key, value);//добавдяем вектор
          }
        }else{
          freq_dictionary = editMyMap.InitMap(key,value,stEntry);//изначально пустая коллекция
        }
    }
    --cntWrd;
    }//while 
    ++index;//index увеличиваем на 1 после прохождения цикла  
  }//for
#if(do_this == do_not)
    vector<Entry>vTempEntry;
    string strIndexTemp;
    cout << "-----------------------------\n";
  for(auto &fd : freq_dictionary){
    strIndexTemp = fd.first;
    vTempEntry = fd.second;
    int sizeStruct = vTempEntry.size();
    cout << "\nindex[" << strIndexTemp << "]=";
    for(int i = 0; i < sizeStruct; i++){
      cout << "{";
      cout << vTempEntry[i].doc_id << "," << vTempEntry[i].count << "}";
    }
    vTempEntry.clear();
  }
#endif

//save map to file
  SaveMap(freq_dictionary,"freq_dictionary.map");
}

void InvertedIndex::UpdateDocumentBase(/*vector<string> input_docs*/){
  map<string, vector<Entry>>::iterator itSearch;
  int index = 0;//отсчет файлов
  Entry stEntry;
  // smatch m; 
  vector<Entry>v;
  string path = "C:\\develop\\skill_project\\resources\\";
  // vector<string> temp;
  string str, fStrName;
  string strCopy;
  string::size_type posB;
  int i = 0;
  // string::size_type posE;

#if(do_this == do_not)
  cout << "class InvertedIndex.UpdateDocumentBase() run!\n";
  for(auto &v : input_docs){
    cout << v;
  }
  cout << endl;
#endif
  /*file1 milk sugar solt
    file2 milk a milk b milk c milk d
  */
  PrepareDocs();
#if(do_this == do_not)
  iCntRespFiles = shrdPtrServ.get()->numbRespFiles();
  str = shrdPtrServ.get()->prepareNameFiles();
  // cout << str << endl;
  while(iCntRespFiles != 0){
    fStrName = path;
    posB = str.find(" ");
    if(posB < str.length()){
      fStrName += str.substr(0,posB);
      str.erase(0,posB+1);
      shrdPtrServ.get()->readFile(fStrName);
      docs = shrdPtrServ.get()->GetDataFile();
      // cout << "file " << fStrName << endl;
      fStrName.erase();
      // input_docs.push_back(docs[i]);
      ++i;
    }

  --iCntRespFiles;
  }
#endif

#if(do_this == do_not)
  for(auto &v : docs){
    cout << v << endl;
  }
#endif

#if(do_this == execute)
  typedef vector<string>Word;
  Word matchWord;//совпадения в документе
  bool compare;
  for(auto &d : docs){
    str = d;//получаем строку
    // bool wrdSave = false;
    // const regex findRegCntWord(_makeRegExp("%"));
    string ret;ret = "(\\b(?!";ret += "%";ret += ")\\w+)";
    const regex findRegCntWord(ret);
    ptrdiff_t const countWord(distance(sregex_iterator(d.begin(), d.end(), findRegCntWord), sregex_iterator()));
    int cntWrd = (int)countWord;//количество слов в строке

//--------------------------------------------------------------------------------------------------
    while(cntWrd != 0){
    if(str.length() > 0){
    // stEntry.doc_id = index+1;
      // ++cntWord;
      posB = str.find(" ");
        strCopy = str.substr(0,posB);
        str.erase(0,posB+1);
          const regex findRegExpWord(makeRegExp(strCopy));
          ptrdiff_t const matchCount(distance(sregex_iterator(d.begin(), d.end(), findRegExpWord), sregex_iterator()));
        if(matchCount > 1){matchWord.push_back(strCopy);}
        std::cout << strCopy << " count --> " << matchCount << endl;
        // for(auto &mW : matchWord){
        //   if(mW == strCopy)compare = true;
        // }
        // if(!compare){
        // }
        stEntry.count = (int)matchCount;
        stEntry.doc_id = index;//повторяемся, если так удалить эту строку
        // if(freq_dictionary.size() != 0){
        if(!freq_dictionary.empty()){
          itSearch = freq_dictionary.find(strCopy);//поиск по ключу
          if(itSearch->first != strCopy){
            v.push_back(stEntry);
            freq_dictionary.insert(pair<string,vector<Entry>>(strCopy, v));
            v.clear();
          }
            if(
                itSearch->first == strCopy 
                && 
                [itSearch,index]()->decltype(compare){
              for(auto &vE : itSearch->second){
                cout << vE.doc_id << " " << index << endl;
                // if(vE.doc_id == index+1)return false;/*compare = false;*/
                return (vE.doc_id == index && vE.count > 1);
                // return (vE.count > 1);
              }
              }()==true
              ){

                compare = true;
            // itSearch->second[0].doc_id == index+1/*&& !wrdSave*/
              // wrdSave = true;//сюда больше не заходим в этом документе index
        }
        // else{
        //       (itSearch->second).push_back(stEntry);
        //   v.clear();
        //   v.push_back(stEntry);
        //   freq_dictionary.insert(pair<string,vector<Entry>>(strCopy, v));
        //   v.clear();
        //   v.push_back(stEntry);
        //   freq_dictionary.insert(pair<string,vector<Entry>>(strCopy, v));
        // }
        }else{//если документ пустой изначально
          v.push_back(stEntry);
          freq_dictionary.insert(pair<string,vector<Entry>>(strCopy, v));
          v.clear();
        }
    }
    --cntWrd;
    cout << "----------------------\n";

//вывод содержимого на экран - рабочий вариант
#if(do_this == do_not)
        vector<Entry>vTempEntry;
    string strIndexTemp;

  for(auto &fd : freq_dictionary){
    strIndexTemp = fd.first;
    vTempEntry = fd.second;
    int sizeStruct = vTempEntry.size();
    cout << "\nindex<" << strIndexTemp << ">=";
    for(int i = 0; i < sizeStruct; i++){
      cout << "{";
      cout << vTempEntry[i].doc_id << "," << vTempEntry[i].count << "}";
    }
    vTempEntry.clear();
  }
  cout << endl;
#endif

    }//while
//------------------------------------------------------------------------------------------------    
    ++index;//index увеличиваем на 1 после прохождения цикла
    v.clear();
  }//for

#if(do_this == do_not)
    vector<Entry>vTempEntry;
    string strIndexTemp;
    cout << "-----------------------------\n";
  for(auto &fd : freq_dictionary){
    strIndexTemp = fd.first;
    vTempEntry = fd.second;
    int sizeStruct = vTempEntry.size();
    cout << "\nindex[" << strIndexTemp << "]=";
    for(int i = 0; i < sizeStruct; i++){
      cout << "{";
      cout << vTempEntry[i].doc_id << "," << vTempEntry[i].count << "}";
    }
    vTempEntry.clear();
  }
#endif


#endif
  return;
}

#if(switch == switch_off)
void InvertedIndex::SetObjServ(shared_ptr<Service> _shrdPtrServ){
  shrdPtrServ = _shrdPtrServ;
}
#endif

int InvertedIndex::GetNumbFiles(){
  return iCntRespFiles;
}

void EditMyMap::remove(MyVector& vec, size_t pos)
{
  MyVector::iterator it = vec.begin();
  cout << "pos=" << pos << endl;
  if(!vec.empty()){
    advance(it, pos);
    vec.erase(it);
  }
}

void EditMyMapTh::remove(MyVectorTh& vec, size_t pos)
{
  MyVectorTh::iterator it = vec.begin();
  cout << "pos=" << pos << endl;
  if(!vec.empty()){
    advance(it, pos);
    vec.erase(it);
  }
}

bool EditMyMap::DeleteValue(MyMap& map, const string& key, const int& elem){
  bool ret = false;
  MyMap::iterator it = map.begin();
  MyVector vec;
  int sizeBefDel, sizeAftDel;
  it = map.find(key);

  if(it->first == key){
    vec = it->second;
    sizeBefDel = vec.size();
    assert(!(elem > (vec.size()-1) ));//message
    if(elem <= vec.size()){
      remove(vec, elem);
    }
    map[it->first] = vec;
    sizeAftDel = (it->second).size();
    // assert(sizeBefDel == sizeAftDel);
    if((sizeBefDel - sizeAftDel) == 1)ret = true;
  }
  return ret;
}

bool EditMyMapTh::DeleteValue(MyMapTh& map, const string& key, const int& elem){
  bool ret = false;
  MyMapTh::iterator it = map.begin();
  MyVectorTh vec;
  int sizeBefDel, sizeAftDel;
  it = map.find(key);

  if(it->first == key){
    vec = it->second;
    sizeBefDel = vec.size();
    assert(!(elem > (vec.size()-1) ));//message
    if(elem <= vec.size()){
      remove(vec, elem);
    }
    map[it->first] = vec;
    sizeAftDel = (it->second).size();
    // assert(sizeBefDel == sizeAftDel);
    if((sizeBefDel - sizeAftDel) == 1)ret = true;
  }
  return ret;
}

bool EditMyMap::AddedValue(MyMap& map, const string& key, const MyVector& value){
  MyMap::iterator it = map.begin();
  MyVector vec;
  bool ret = false;

  it = map.find(key);
  
  if(it->second.size() != 0){
    map[it->first] = value;
    int i = it->second.size();
    if(it->second[i-1] == value[i-1])ret = true;
  }else{
    map[it->first] = value;
    if(
      (it->second[0] == value[0])
      ){
      ret = true;}
    else{ ret = false;}
  }
  return ret;
}

bool EditMyMapTh::AddedValue(MyMapTh& map, const string& key, const MyVectorTh& value){
  MyMapTh::iterator it = map.begin();
  MyVectorTh vec;
  bool ret = false;

  it = map.find(key);
  
  if(it->second.size() != 0){
    map[it->first] = value;
    int i = it->second.size();
    if(it->second[i-1] == value[i-1])ret = true;
  }else{
    map[it->first] = value;
    if(
      (it->second[0] == value[0])
      ){
      ret = true;}
    else{ ret = false;}
  }
  return ret;
}

MyVector EditMyMap::GetMapValue(MyMap& map, const string& key){
  MyVector ret;
  MyMap::iterator it = map.begin();  
  it = map.find(key);
  if(it->first == key){
    ret = it->second;
  }else{
    assert(it->first != key);
  }
  return ret;
}

MyVectorTh EditMyMapTh::GetMapValue(MyMapTh& map, const string& key){
  MyVectorTh ret;
  MyMapTh::iterator it = map.begin();  
  it = map.find(key);
  if(it->first == key){
    ret = it->second;
  }else{
    assert(it->first != key);
  }
  return ret;
}

size_t EditMyMap::MapSize(MyMap& map){
size_t ret;
  MyMap::iterator it = map.begin();
  ret = it->second.size();
  return ret;
}

size_t EditMyMapTh::MapSize(MyMapTh& map){
size_t ret;
  MyMapTh::iterator it = map.begin();
  ret = it->second.size();
  return ret;
}

MyMap EditMyMap::InitMap(const string& key, MyVector& value, Entry& ent){
  // assert(!(value.size() != 0));
  value.push_back(ent);
  map.insert(make_pair(key,value));
  return map;
}

MyMapTh EditMyMapTh::InitMap(const string& key, MyVectorTh& value, EntryThreads& ent){
  // assert(!(value.size() != 0));
  value.push_back(ent);
  map.insert(make_pair(key,value));
  return map;
}

size_t EditMyMap::FindValue(MyMap& map, Entry& ent, const string& key){
  size_t pos; MyVector vec;
  MyMap::iterator it;
  it = map.find(key);
  if(it->first == key){
  vec = it->second;
  pos = 1000000;
  for(size_t i = 0; i < vec.size(); i++){
    if(vec[i] == ent){pos = i; break;}
  }  
  }
  return pos;
}

size_t EditMyMapTh::FindValue(MyMapTh& map, EntryThreads& ent, const string& key){
  size_t pos; MyVectorTh vec;
  MyMapTh::iterator it;
  it = map.find(key);
  if(it->first == key){
  vec = it->second;
  pos = 1000000;
  for(size_t i = 0; i < vec.size(); i++){
    if(vec[i] == ent){pos = i; break;}
  }  
  }
  return pos;
}

//не очень хорошая идея
map<string, vector<EntryThreads>>& InvertedIndex::GetMap(){
  // static map<string, vector<EntryThreads>> ret(freq_dictionaryTh);
  // map<string, vector<EntryThreads>>::iterator it;
  // MyVector value;
  // for(it=freq_dictionaryTh.begin(); it != freq_dictionaryTh.end(); ++it){
    
  // }
  // map<string, vector<EntryThreads>>& ret = freq_dictionaryTh;
  // assert(ret.size() == 0);
  // cout << "InvertedIndex::GetMap()" << " size map is " << ret.size() << endl;
  // map<string, vector<EntryThreads>>& ret = freq_dictionaryTh;
  return freq_dictionaryTh;
}

    string InvertedIndex::MapGetKey(const string& key ){
      MyMapTh::iterator it;
      MyMapTh::iterator itE = freq_dictionaryTh.end();
      it = freq_dictionaryTh.find(key);
      if(it == itE)return "";
      cout << it->first << endl;
      string ret;
      ret  = it->first;
      return ret;
    }
    MyVectorTh InvertedIndex::MapGetValue(const string& key){
      MyMapTh::iterator it;
      it = freq_dictionaryTh.find(key);
      return it->second;
    }