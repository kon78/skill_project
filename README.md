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
- [ANSWERS.JSON](#Answers.json)
- [Relative](#relative)
- 
## About...
Приложение SkillBoxSearchEngine представляет из себя консольное приложение, (исполняемый файл запускаемый на компьютере),
осуществляющее поиск и имеющее возможность настройки через файлы формата JSON и текстовый файл TXT. Приложение написно на C++
(GCC 13.2.0 x86_64-w64-mingw32 Windows 10, Visaul Studio Code 1.94.2).

## Princeps
Принципы работы поискового движка.
В конфигурационном файле [CONFIG.JSON](#Configjson) перед запуском приложения задаются названия файлов, по которым движок будет осуществлять поиск.
Файлы расположены в папке проекта (skill_project\resources). Названия файлов имеют вид fileXXX.txt XXX-000, 001, 002 и т.д. При обходе
файлов движок индексирует их таким образом, чтобы находить наиболее релевантные документы.
Пользователь задаёт запрос через JSON-файл [REQUESTS.JSON]. Запрос — это набор слов, по которым нужно найти документы.  
Запрос трансформируется в список слов. В индексе ищутся те документы (папка skill_project\resources), в которых встречаются эти слова.
6. Результаты поиска ранжируются, сортируются и отдаются пользователю, максимальное количество возможных документов в ответе задаётся в
конфигурационном файле. В конце программа формирует файл [ANSWERS.JSON], в который записывает результаты поиска.

## Configjson
## Requestsjson
## Answersjson
## Relative
