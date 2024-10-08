#include<invertindex.h>

bool operator==(const Entry& ls, const Entry& rs){
  return((ls.doc_id == rs.doc_id) && 
    (ls.count == rs.count)
    );
}

bool operator==(const EntryThreads& ls, const Entry& rs){
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

std::ostream& operator <<(std::ostream &os, const Entry &c){
    os << "(document-->" << c.doc_id << ", count repeat-->" << c.count << ")\n";
    return os;
}

std::ostream& operator <<(std::ostream &os, const EntryThreads &c){
    os << "(document-->" << c.doc_id << ", count repeat-->" << c.count << ")\n";
    return os;
}

size_t SearchSubStrng::GetMatch() { 
  return match; }

void SearchSubStrng::Search() {
  for (auto &r : result) {
    if (r == subStr)
      ++match;
  }
}

void SearchSubStrng::GetVector() {
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

string InvertedIndex::makeRegExp(const string &word){
  string ret;
  ret = "(\\b(?!(?!";
  ret += word;
  ret += "))\\w+)";
  return ret;
}

string InvertedIndex::_makeRegExp(const string &word){
  string ret;
  ret = "(\\b(?!";
  ret += word;
  ret += ")\\w+)";
  return ret;
}

void InvertedIndex::Hello(){
  std::cout << "Hello from class InvertedIndex!\n";
}

map<string,vector<EntryThreads>>& InvertedIndex::GetMap(){
  return freq_dictionaryTh;
}

map<string,vector<Entry>>& InvertedIndex::GetMap1(){
  return freq_dictionary;
}

void InvertedIndex::SetObjEvent(MyEvent* ptr){
  assert(ptr != nullptr);
  pEvent = ptr;
}

// bool InvertedIndex::ReadDocument(const string& doc){
//   vector<string> englwords;
//   bool longWord = false;//good < 100
//   bool countWord = false;//good < 1000
//   const regex findRegCntWord("([a-zA-Z\\'\\&\\-\\@]+|![а-я]+|![0-9]+)");
//   std::ptrdiff_t const match_count(distance(sregex_iterator(doc.begin(), doc.end(), findRegCntWord),sregex_iterator()));
//     for( sregex_iterator itrgx(doc.begin(), doc.end(), findRegCntWord), it_end; itrgx != it_end; ++itrgx ){
//       if(itrgx->str().length() > 100)
//         countWord = true;
//       englwords.push_back(itrgx->str());
//     }
//   if(englwords.size() > 1000)
//     longWord = true;
  
//   return (longWord || countWord);
// }

//1000 words 100 symbols
void InvertedIndex::PrepareDocs(Server* pServObj){
  assert(pServObj != nullptr);//проверка на нулевой указатель
  MyException myexcep;
  myexcep.SetObjEvent(pEvent);
  myexcep.SetObjServ(pServObj);
  bool bNone, bWrongName, bDocs;
  fstream fp;
  string temp,temp1;
  vecFNames = pServObj->GetDocs();
  size_t i = 0;

  for(auto &d : vecFNames){
    bWrongName = true;
    bNone = false;
    bDocs = false;
    try{
      bWrongName = myexcep.fDocsNames(d);
      bNone = myexcep.fDocsExist(d);
    }catch (char const * error){
      cout << myexcep.errors() << endl;
    }
      ++i;

  //читаем документы в вектор docs
    if(bNone){
      // for(auto &d : vecFNames){
        string fn = "C:\\develop\\skill_project\\resources\\";
        fn += d;

        fp.open(fn, ios::in);
          if(fp.is_open()){
//проходит условия 1000 слов 100 символов в слове 
//слова разделены пробелами (одно или несколько) и состоят из латинсских букв              
//файл может состоять из нескольких строк, для этого их надо объеденить в одну строку
            while(!fp.eof()){
              getline(fp,temp);
              temp1 += temp + " ";
            }
            try{
              bDocs = myexcep.ReadDocument(temp1);  //excep.ReadDocument(temp1);
              if(!bDocs)
                docs.push_back(temp1);
            }catch(char const * error){
              cout << myexcep.errors() << endl;
            }
    fp.close();
      }
      temp.clear();
      temp1.clear();
    // }
    }else{
      string none = myexcep.nonefiles();//отсутствующие файлы
      cout << "This files are none " << ((none!="")?none:"- empty") << endl;
}
    }

#if(do_this == do_not)
  for(auto &d : docs){
    cout << d << endl;
  }
  cout << endl;
#endif
}

vector<string>& InvertedIndex::GetDocs(){  
  return docs;
}

void InvertedIndex::DocBaseThreadNew(size_t &numDocs /*,const vector<string> &docs*/){
unique_lock<std::mutex> lck(global);
string str,key, strC;
string::size_type posB;
// string::size_type posF;
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
      }
      --cntWrd;
    }//while
}

void InvertedIndex::ThreadSleep(){
  Th.join();
  Th.~thread();
}

void InvertedIndex::go() {
  std::unique_lock<std::mutex> lck(global);
  ready = true;
  cv.notify_all();
}

void InvertedIndex::UpdateDocumentBaseThreads(){
  vector<thread>vecThDocBase;  
  string path = "C:\\develop\\skill_project\\resources\\";
  size_t countThreads = docs.size();
  size_t fieldDocs = -1;//start index
  
  for(size_t i = 0; i < countThreads; ++i){//(int i = 0; i < countThreads; ++i)
    vecThDocBase.emplace_back(thread(DocBaseThreadNew,this,ref(fieldDocs)/*freq_dictionaryTh, ref(docs)*/));
  }

  go();

  for (auto& t: vecThDocBase) {
    t.join();
    }
 
  // cout << "size freq_dictionaryTh is " << freq_dictionaryTh.size() << endl;

//здесь определяем число повторений в map freq_dictionaryTh
  vector<string> vDubl;
  // vector<EntryThreads> vStructEnt;
  for(auto it = freq_dictionaryTh.cbegin(); it != freq_dictionaryTh.cend(); ++it){
    if(it->second.size() > 1){
      vDubl.push_back(it->first);
    }    
  }
  SaveMap(freq_dictionaryTh,"freq_dictionaryTh.map");
}

void InvertedIndex::UpdateDocumentBase1(){
  map<string, vector<Entry>>::iterator itSearch;
  EditMyMap editMyMap(freq_dictionary);
  int index = 0;//отсчет файлов
  MyVector value;
  string str, key;
  string::size_type posB;
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
        if(!freq_dictionary.empty()){
          itSearch = freq_dictionary.find(key);//ищем по ключу
          if(itSearch == freq_dictionary.end()){
            //нет такого ключа, добавляем
            freq_dictionary[key];//добавляем ключ
            itSearch = freq_dictionary.find(key);
            value = itSearch->second;
            value.push_back(stEntry);
            editMyMap.AddedValue(freq_dictionary, key, value);//добавдяем вектор
          }else{
          if(itSearch->first == key){//есть ли такой ключ в колкции
            size_t pos = editMyMap.FindValue(freq_dictionary,stEntry, key);//есть ли такой элемент в векторе
            if(pos == 1000000){
              //элемента в векторе нет
              value = itSearch->second;
              value.push_back(stEntry);
              editMyMap.AddedValue(freq_dictionary, key, value);//добавдяем вектор
              itSearch = freq_dictionary.find(key);
              value = itSearch->second;
            }
          }
          }
        }else{
          freq_dictionary = editMyMap.InitMap(key,value,stEntry);//изначально пустая коллекция
        }
    }
    --cntWrd;
    }//while
    str.clear();//???
    ++index;//index увеличиваем на 1 после прохождения цикла  
  }//for
//save map to file
  SaveMap(freq_dictionary,"freq_dictionary.map");

}

bool InvertedIndex::MapIsEqual(){
  return (freq_dictionary.size() == freq_dictionaryTh.size() );
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
  
  if(it->second.size() != 0 && it != map.end()){
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
  if(it->first == key && it != map.end()){
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