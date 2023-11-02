clear
for f in src/*.hpp
do
    moc-qt4 $f > $f.moc
done
qmake-qt4 YAPOS.pro
make && ./YAPOS