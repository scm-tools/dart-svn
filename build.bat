@ECHO OFF
set DART_SDK=D:\CI\tools\Building\dart-sdk
rem set SVN_DEV=..\svn-win32-1.7.6
rem set SVN_DEV=..\svn-win32-1.6.17
set SVN_DEV=..\svn-win32-1.7.6

IF "%1"=="doc" GOTO DOC
IF "%1"=="test" GOTO TEST
IF "%1"=="install" GOTO INSTALL

:BUILD
cl /nologo /Ox /W3 /GS- /DNDEBUG -DWIN32 /DDART_SHARED_LIB /D_USRDLL /D_WINDLL /I%SVN_DEV%\include\apr /I%SVN_DEV%\include\arp-util /I%SVN_DEV%\include\arp-iconv /I%SVN_DEV%\include /I%DART_SDK%\include src\dart_svn.cc /link dart.lib /LIBPATH:%DART_SDK%\bin /DLL /OUT:lib/dart_svn.dll
GOTO END

:DOC
%DART_SDK%\bin\dart %DART_SDK%\lib\dartdoc\dartdoc.dart --mode=static lib\svn.dart
GOTO END

:TEST

%DART_SDK%\bin\dart test\test.dart
GOTO END

:INSTALL
%DART_SDK%\bin\pub.bat install
GOTO END

:END
