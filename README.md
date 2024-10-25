<h1 align="center">SkillBox SearchEngine ver. 0.1</h1>
<h2 align="center">
<img src="https://badges.frapsoft.com/os/v1/open-source.svg?v=103" >
<img src="https://badgen.net/badge/icon/windows?icon=windows&label">
<img src="https://img.shields.io/badge/--181717?logo=github&logoColor=ffffff">

<p align="center">
<img src="https://media.giphy.com/media/v2xIous7mnEYg/giphy.gif" width="80%"></p>

## Description
- [About the program](About...)
- [Princeps](#princeps)
- [CONFIGJ.SON](#Configjson)
- [REQUESTS.JSON](#Requestsjson)
- [ANSWERS.JSON](#Answersjson)
- [Organization](#Organization)
- [Relative](#relative)

## About...
Программа SkillBoxSearchEngine представляет из себя консольное приложение,
осуществляющее поиск иформации (текстовые файлы TXT) и имеющее возможность настройки через файлы формата JSON. Приложение написно на C++
(GCC 13.2.0 x86_64-w64-mingw32 Windows 10, Visaul Studio Code 1.94.2).

## Princeps
Принципы работы поискового движка.
В конфигурационном файле [CONFIG.JSON](#Configjson) перед запуском приложения задаются названия файлов, по которым движок будет осуществлять поиск.
Файлы расположены в папке проекта (skill_project\resources). Названия файлов имеют вид fileXXX.txt XXX-000, 001, 002 и т.д. При обходе
файлов движок индексирует их таким образом, чтобы находить наиболее релевантные документы.
Пользователь задаёт запрос через файл requests.txt. Запрос — это набор слов, по которым нужно найти документы.  
Запрос трансформируется в список слов, JSON-файл [REQUESTS.JSON](#Requestsjson). В индексе ищутся те документы (папка skill_project\resources), в которых встречаются эти слова.
Результаты поиска ранжируются, сортируются и отдаются пользователю [ANSWERS.JSON](#Answersjson), максимальное количество возможных документов в ответе задаётся в
конфигурационном файле.

## Configjson
Файл конфигурации config.json.
Без него запуск приложения невозможен. Он содержит название "name" поискового движка, его версию "version", максимальное количество вариантов в ответе "max_responses" (если не указано,
то значение выбирается равным пяти).
Формат файла:
```cpp
      jConfJSON = {
      {"config",{
        {"name","SkillboxSearchEngine"},
        {"version","0.1"},
        {"max_responses",respFiles}
      },
      "files",{strRespFiles}
      }};
```

## Requestsjson
Содержит запросы, которые необходимо обработать поисковому движку. Запросы для удобства пользователя записываются в текстовом файле. Требования к сазпросам, английские слова строчными буквами, масимальная
длина слова запроса 100 символов, не более 1000 строк в запросе. Если в запросе встречаются слова длиной больше 100 символов, русские буквы или символы не отвечающие требованиям a-z, они игнорируются.
Формат файла:
```cpp
  jRequestsJSON = {
    {"requests",{
    }
    }
  };
```

## Answersjson
В него записываются результаты работы поискового движка.
Формат файла:
```cpp
{"answers":["requestNNN",["result",true/false],{"relevance":[
{"doc_id": ,"rank":},
{"doc_id":,"rank":},
{"doc_id":,"rank":},
{"doc_id":,"rank":},
{"doc_id":,"rank":}
...
]}]}
```

## Organization
Основной код работы программы происходит в методе Run() класса class Server.
```cpp
void Server::Run(){
///...
case 104 : {
if(!prepare){
///...подготовительная часть
}
while(true){
///основной цикл

if(!ready){
///поиск полсе первого старта программы при подготовленных входных данных 
}else{
///поиск по событиям, изменили файл ресурса с документом или изменили посиковый запрос
}
}
break;
}
}
```
Программа тематически разбита на основные классы,  class [InvertedIndex](#class_InvertedIndex),  Проихзводит обработку входных документов, расположенных в папке
skill_project\resources. 

## Relative

## Class_InvertedIndex
Краткое описание класса InvertedIndex.
Класс принимает текстовые блоки и формирует из них инвертированный индекс (хранит и индексирует слова).
Основной метод void UpdateDocumentBaseThreads() формирует потоки, равные числу файлов с ресурсами, в которых 

```cpp
  for(size_t i = 0; i < countThreads; ++i){//(int i = 0; i < countThreads; ++i)
    vecThDocBase.emplace_back(thread(DocBaseThreadNew,this,ref(fieldDocs)/*freq_dictionaryTh, ref(docs)*/));
  }
```
метод DocBaseThreadNew(size_t &numDocs) производит заполнение частотного словаря map<string, vector<EntryThreads>> freq_dictionaryTh.
EntryThreads структура данных. Заполняется в DocBaseThreadNew и используется в последующем для поиска по текстам.
```cpp
struct EntryThreads{
  size_t doc_id, count;
  void operator=(const EntryThreads& other){
    count = other.count;
    doc_id = other.doc_id;
  }
};
```
 doc_id - номер документа, count - сколько раз слово встретилось в документе.
