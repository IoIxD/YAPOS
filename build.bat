cls  
for /r %%i in (.\src\*.hpp) do moc -p . %%i > %%i.moc
qmake YAPOP.pro
make && .\debug\YAPOP.exe > output.txt