cls  
for /r %%i in (.\src\*.hpp) do moc -p . %%i > %%i.moc
qmake YAPOS.pro
make && .\debug\YAPOS.exe > output.txt