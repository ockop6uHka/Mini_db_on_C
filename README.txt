БД работает на базе шаблонного текстового файла, который находится 
в пути Database_on_C/src/db_logs

Для запуска скрипта находясь в src можно через Makefile make all/make build_db

Билд будет находиться в каталоге Database_on_C/builds
Если программа будет работать некорректно, т.е. не обрабатывать стандартные запросы 
SELECT INSERT И Т.П. Нужно будет перебилдить проект вручную

по типу: gcc -Wall -Werror -Wxtra -std=c11 modules_db.c status_events.c levels.c modules.c
или modules_db.c shared.c    (что-то из 2х вариантов должно сработать)