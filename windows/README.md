# Необходимые действия
1. создать в скачанном проекте папки `build` и `bin`

2. установить `MinGW` с `SourceForge.net`
В окне установщика `MinGW` нужно выбрать все пакеты кроме `fortran`, `ada` и `objc`

3. прописать в переменную среды `Path` `C:\MinGW\bin\` **(у вас может быть свой путь)**

4. установить `cmake` с официального сайта

5. скачать релиз `SDL` с `github`. Нужен `SDL2`. Я использовал `SDL2-devel-2.26.5-mingw`.
В папке `i686-w64-mingw32` есть всё необходимое, чтобы добавить `SDL2` в `MinGW`. Я использую 32-ух битную версию для большей совместимости.
- из папки `i686-w64-mingw32\bin` нужно скопировать `sdl2.dll` в `cmakebin`. Файл `dll` должен лежать в одной папке с вашей программой, иначе она не запуститься. 
- из папки `i686-w64-mingw32\lib` нужно копировать все файлы **(кроме папок)** в `C:\MinGW\lib` **(ну или куда вы там mingw скачали)**
- из папки `i686-w64-mingw32\include` нужно копировать папку `SDL2` в папку `C:\MinGW\include`

Библиотеки `opengl32` и `glu32` по-умолчанию есть в `MinGW`. С ними ничего делать не нужно

6. дальше открыаем папку проекта в **Powershell**
7. запустите скрипт компиляции, прописав в консоль: `.\project_start.bat`
8. приложение должно скомпилироваться в папку `cmakebin`
