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
  // cout << ret << endl;
  return ret;
}

void InvertedIndex::UpdateDocumentBase(vector<string> input_docs){
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

  //docs --> freq_dictionary;
  // cout << "size docs is " << docs.size() << endl;
  for(auto &d : docs){
    str = d;//получаем строку
    int cntWord = 0;
    // while(cntWrd != 0){
    // cout << "length string " << str << " is " << str.length() << endl;
    //\b(?!%)\w+
    const regex findRegCntWord(_makeRegExp("%"));
    ptrdiff_t const countWord(distance(sregex_iterator(d.begin(), d.end(), findRegCntWord), sregex_iterator()));
    int cntWrd = countWord;
    cout << "count word at string " << str << " is " << cntWrd << endl;
    while(cntWrd != 0){
    if(str.length() > 0){
      stEntry.doc_id = index;//index увеличиваем на 1 после прохождения цикла
      cout << str << endl;
      //делаем обход строки
      ++cntWord;
      posB = str.find(" ");
      if(posB < str.length()){
        strCopy = str.substr(0,posB);
        str.erase(0,posB+1);
        
        // cout << "length string is " << str.length() << endl;
        //здесь лучше подключить regexp, чтобы искать count вхождений в строке strCopy
        // string findStr(strCopy);
        const regex findRegExpWord(makeRegExp(strCopy));
        // regex_search(d,m,findRegExpWord);//обычный поиск

        //поиска совпадений
        ptrdiff_t const matchCount(distance(sregex_iterator(d.begin(), d.end(), findRegExpWord), sregex_iterator()));
        cout << strCopy << " count --> " << matchCount << endl;
        stEntry.count = matchCount;
      }
      else{
        const regex findRegExpWord(makeRegExp(str));
        ptrdiff_t const matchCount(distance(sregex_iterator(d.begin(), d.end(), findRegExpWord), sregex_iterator()));
        cout << str << " count --> " << matchCount << endl;
        stEntry.count = matchCount;
      }
    }
    --cntWrd;
    }//while
    cout << "count word at string " << str << " is " << cntWord << endl;
    ++index;

    v.push_back(stEntry);
    freq_dictionary.insert(pair<string,vector<Entry>>(strCopy, v));

  }//for
  //map<string, vector<Entry>> freq_dictionary

  for(auto &fd : freq_dictionary){
    cout << "index[" << fd.first << "]=" << fd.second.size() << endl;
  }
  return;
}

void InvertedIndex::SetObjServ(shared_ptr<Service> _shrdPtrServ){
  shrdPtrServ = _shrdPtrServ;
}

int InvertedIndex::GetNumbFiles(){
  return iCntRespFiles;
}