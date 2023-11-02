# YAPOS

YAPOS is a recreation of the UI on [https://plaza.one](https://plaza.one) that is built with Qt 4.1 as the only external dependency, meaning it can run on Windows 98/Me/2000/XP, Mac OS 10.2.8, Solaris 9, IRIX 6.5, AIX 5.1, and [any other platforms listed on this page](http://web.archive.org/web/20060126211419/http://www.trolltech.com/developer/platforms/)

# Building

## Windows XP

Note that you should have Linux on standby because Windows was even worse for C/C++ development then then it is now (and also you won't be able to git push from Windows XP due to Github using a newer, unsupported SSL standard).

- Install [mingw-get-setup.exe](https://zenlayer.dl.sourceforge.net/project/mingw/Installer/mingw-get-setup.exe)
- Install [qt-win-opensource-4.1.0-mingw.exe](https://download.qt.io/archive/qt/4.1/qt-win-opensource-4.1.0-mingw.exe)
- You will most likely need to open up the Qt4.1 prompt from the Start Menu and do `configure.exe && make.exe` because the pre-built packages that the installer installs were built with a previous version of MinGW that's undocumented (and probably no longer avaliable anyways)
- `cd` to wherever the installer is from cmd and do `build.bat`. The batch file will automatically launch the executable.

## Linux

- Install qt4 from your distro's package manager (and qt4-devel if your distro does that).
- Do ./build.sh
