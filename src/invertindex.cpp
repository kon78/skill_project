#include"invertindex.h"

string InvertedIndex::makeRegExp(const string &word){
  string ret;
  // ret = "(\\b(?!(?!milk))\\w+)";
  ret = "(\\b(?!(?!";
  ret += word;
  ret += "))\\w+)";
  // cout << ret << endl;
  return ret;
}

string InvertedIndex::_makeRegExp(const string &word){
  string ret;
  ret = "(\\b(?!";
  ret += word;
  ret += ")\\w+)";
  return ret;
}

void print(stThread stthread){
  if(stthread.status == threadStopTask){
  cout << "Martin thread " << stthread.id << " test!\n";
  stthread.status = threadEndedTask;
  }
}

int InvertedIndex::ThreadRoutine(vector<string> input_docs){
  // mutex threadAccess;
  string str, threadId("Thread_");
  int countElements;
  int index = 0;
  for(auto &d : input_docs){
    str = d;//получаем строку
    bool wrdSave = false;
    const regex findRegCntWord(_makeRegExp("%"));
    ptrdiff_t const countWord(distance(sregex_iterator(d.begin(), d.end(), findRegCntWord), sregex_iterator()));
    int cntWrd = (int)countWord;//количество слов в строке
    countElements = (int)countWord;
  while(cntWrd != 0){
    threadId += to_string(index);//подпись созданного потока
    pStThread = new stThread;
    pStThread->id = threadId;
    pStThread->status = threadStopTask;
    pStThread->milliseconds = 0;
    vecStructThreads.push_back(pStThread);

    --cntWrd;
  }
  ++index;//increment
  }
    cout << "size vector vecStructThreads is " << vecStructThreads.size() << endl;
    //create vectors threads
    for(int i = 0; i < vecStructThreads.size(); ++i){
      // pVecThreadDocs.push_back(new thread(print, (*pStThread)));
      cout << "thread " << i << endl;
      pVecThreadDocs.push_back( new thread( print, ( *vecStructThreads[i] ) ) );
    }

    //switch-on threads
    for(auto& t: pVecThreadDocs){
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        t->join();
    }

    //switch-off threads
    for(auto& t: pVecThreadDocs){
        // std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if(t->joinable())
          t->detach();
    }


  return threadError;
}

void InvertedIndex::UpdateDocumentBaseThread(vector<string> input_docs){
  map<string, vector<Entry>>::iterator iterMapFreqDict;
  int index = 0; Entry stEntry; smatch m; vector<Entry>v;
  string path = "C:\\develop\\skill_project\\resources\\";
  string str, fStrName, strCopy;
  string::size_type posB;
  int i = 0;

  iCntRespFiles = shrdPtrServ.get()->numbRespFiles();
  str = shrdPtrServ.get()->prepareNameFiles();
  while(iCntRespFiles != 0){
    fStrName = path;
    posB = str.find(" ");
    if(posB < str.length()){
      fStrName += str.substr(0,posB);
      str.erase(0,posB+1);
      shrdPtrServ.get()->readFile(fStrName);
      docs = shrdPtrServ.get()->GetDataFile();
      fStrName.erase();
      input_docs.push_back(docs[i]);
      ++i;
    }

  --iCntRespFiles;
  }


}

void InvertedIndex::UpdateDocumentBase(vector<string> input_docs){
  map<string, vector<Entry>>::iterator iterMapFreqDict;
  int index = 0; Entry stEntry; smatch m; vector<Entry>v;
  string path = "C:\\develop\\skill_project\\resources\\";
  // vector<string> temp;
  string str, fStrName, strCopy;
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
      input_docs.push_back(docs[i]);
      ++i;
    }

  --iCntRespFiles;
  }
#if(do_this == do_not)
  for(auto &v : docs){
    cout << v << endl;
  }
#endif

  for(auto &d : docs){
    str = d;//получаем строку
    bool wrdSave = false;
    const regex findRegCntWord(_makeRegExp("%"));
    ptrdiff_t const countWord(distance(sregex_iterator(d.begin(), d.end(), findRegCntWord), sregex_iterator()));
    int cntWrd = (int)countWord;//количество слов в строке
    while(cntWrd != 0){
    if(str.length() > 0){
    stEntry.doc_id = index;//index увеличиваем на 1 после прохождения цикла
      // ++cntWord;
      posB = str.find(" ");
        strCopy = str.substr(0,posB);
        str.erase(0,posB+1);
        const regex findRegExpWord(makeRegExp(strCopy));
        ptrdiff_t const matchCount(distance(sregex_iterator(d.begin(), d.end(), findRegExpWord), sregex_iterator()));
        cout << strCopy << " count --> " << matchCount << endl;
        stEntry.count = (int)matchCount;
        stEntry.doc_id = index;
        if(freq_dictionary.size() != 0){
          iterMapFreqDict = freq_dictionary.find(strCopy);//поиск по ключу
            if(iterMapFreqDict->first == strCopy && !wrdSave){
              (iterMapFreqDict->second).push_back(stEntry);
              wrdSave = true;//сюда больше не заходим в этом документе index
        }else{
          v.clear();
          v.push_back(stEntry);
          freq_dictionary.insert(pair<string,vector<Entry>>(strCopy, v));
        }
        }else{
          v.push_back(stEntry);
          freq_dictionary.insert(pair<string,vector<Entry>>(strCopy, v));
          v.clear();
        }
    }
    --cntWrd;
    }//while
    
    ++index;
    v.clear();
  }//for
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
  return;
}

void InvertedIndex::SetObjServ(shared_ptr<Service> _shrdPtrServ){
  shrdPtrServ = _shrdPtrServ;
}

int InvertedIndex::GetNumbFiles(){
  return iCntRespFiles;
}