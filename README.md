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
Программа SkillBoxSearchEngine представляет из себя консольное приложение, осуществляющее поиск иформации (текстовые файлы TXT) и имеющее возможность настройки через файлы формата JSON. 
Приложение написно на C++ (GCC 13.2.0 x86_64-w64-mingw32 Windows 10, Visaul Studio Code 1.94.2).

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
requestNNN - идентификатор запроса, с автоматическим порядковым номером, 1-1000, 

result - true / false,

docid - идентификатор документа из папки  /resorces/fileXXX.txt и т.д.

## Organization
Программа тематически разбита на основные классы.

- [InvertedIndex](#class_InvertedIndex)
- [ConverterJSON](#class_ConverterJSON)
- [SearchService](#class_SearchService)
- [Server](#class_Server)
- [MyException](#class_MyException)
- [MyEvent](#class_MyEvent)

Приложение запускается при проверке готовности на наличие файла config.json. Если такого нет, то запуск приложения невозможен. Файл config.json можно создать командой
SkillboxSearchEngine.exe /s, при условии, что есть папка resources, если папки нет, то приложение также не запустится, о чем будет выдано сообщение. Проверки этих условий
происходят в классах MyException и MyEvent.

Если все условия выполнены, то приложение начинает работать.

Основной код работы программы происходит в методе класса Server::Run(). 
При старте приложения для поиска по базе документов используется ключ [key](#Key_Application) /r, анализ командной строки из консоли происходит в методе Server::KeyApplication().
Поиск по заданию начинается с подготовки документов в методе [InvertedIndex](#class_InvertedIndex)::PrepareDocs(this) и в случае успешного прохождения условий (1000 строк, 100 слов, строчные английские, не цифры и
не спецсимволы) заполняется вектор vector<string>docs, где элемент вектора, файл в ../resources/.

После успешного заполнения вектора документов, то по нему можно осуществлять поиск. В этом случае поисковый движок считывает запросы из файла requests.json и после начинает расчет релевантности для каждого слова
из запроса.

Расчет релевантносте выполняется в методе класса vector<vector<RelativeIndex>> [SearchService](#class_SearchService)::searchTh(const vector<string>& queries_input).


После выдачи результатов приложение переходит в режим ожидания. При изменении содержимого папки ../resources/, удалении или добавления файла, а также его редактировании и последующем сохранении
приложение переходит в работу и очередной поиск по заданию. При изменении файла задания requests.txt приложение также производит новый поиск. 

## Relative

## Class_InvertedIndex
Краткое описание класса InvertedIndex.

Класс принимает текстовые блоки vector< string >docs и формирует из них инвертированный индекс (хранит и индексирует слова). 
Инвертированный индекс (inverted index) — структура данных. В ней для каждого слова коллекции документов в соответствующем списке
перечислены все документы, в которых оно встретилось. Инвертированный индекс используется для поиска по текстам.

Инвертированный индекс организован на контейнере (карте) map<string, vector<EntryThreads>> freq_dictionaryTh.
EntryThreads структура.
```cpp
struct EntryThreads{
  size_t doc_id, count;
  void operator=(const EntryThreads& other){
    count = other.count;
    doc_id = other.doc_id;
  }
};
```
doc_id — номер элемента в векторе docs, по которому хранится текст

count — число, которое обозначает, сколько раз ключевое слово встретилось в документе doc_id.

Основной метод void UpdateDocumentBaseThreads() формирует потоки, равные числу файлов с ресурсами, в которых 

```cpp
  for(size_t i = 0; i < countThreads; ++i){//(int i = 0; i < countThreads; ++i)
    vecThDocBase.emplace_back(thread(DocBaseThreadNew,this,ref(fieldDocs)/*freq_dictionaryTh, ref(docs)*/));
  }
```
метод DocBaseThreadNew(size_t &numDocs) производит заполнение частотного словаря map<string, vector<EntryThreads>> freq_dictionaryTh.

EntryThreads заполняется в DocBaseThreadNew и используется в последующем для поиска по текстам.

doc_id - номер документа, count - сколько раз слово встретилось в документе.

## class_ConverterJSON

## class_SearchService
Краткое описание класса SearchService.

Для своей работы класс принимает подготовленные данные от классов [InvertedIndex](#class_InvertedIndex) и [ConverterJSON](#class_ConverterJSON).

Полученные данные обрабатываются в поточном методе void CalculateRelative(size_t& fieldQueries, const vector<string>& queries_input, vector<string>& vecUncnownWord)

## class_Server

## Key_Application
- SkillboxSearchEngine.exe /r - поиск документов по запросу.
- SkillboxSearchEngine.exe /s - сервис, подготовка [CONFIG.JSON](#Configjson)
- SkillboxSearchEngine.exe /e - удалить файлы из папки resources/
- SkillboxSearchEngine.exe /h - краткая справка по приложению

## class_MyException

## class_MyEvent
