@ECHO off
SET QMAKE=qmake
SET MAKE=nmake
SET PROJECT_ROOT=%CD%
SET TESTDIR=%PROJECT_ROOT%\config.tests
SET CONFIG_LOG=config.log
SET LAST_FUNC_RET=0
SET STATIC=0
SET DEBUG_OR_RELEASE=0

if exist %PROJECT_ROOT%\config.in   del %PROJECT_ROOT%\config.in
if exist %PROJECT_ROOT%\config.log  del %PROJECT_ROOT%\config.log
if exist %PROJECT_ROOT%\depends.pri del %PROJECT_ROOT%\depends.pri

echo #depends.pri > %PROJECT_ROOT%\depends.pri
    
shift
set QMAKEBIN=qmake
set MSVCMODE=
set FCGI=1
set DB=1
set ZEROCONF=1
echo include(depends.pri) > %PROJECT_ROOT%\config.in
echo QXT_stability += unknown >> %PROJECT_ROOT%\config.in

:top
if "%0" == ""                   goto finish
if "%0" == "-qmake-bin"         goto setqmake
if "%0" == "-I"                 goto addinclude 
if "%0" == "-L"                 goto addlibpath
if "%0" == "-l"                 goto addlib
if "%0" == "-nomake"            goto nomake
if "%0" == "-prefix"            goto prefix
if "%0" == "-libdir"            goto libdir 
if "%0" == "-docdir"            goto docdir
if "%0" == "-headerdir"         goto headerdir
if "%0" == "-bindir"            goto bindir
if "%0" == "-static"            goto static
if "%0" == "-debug"             goto debug
if "%0" == "-release"           goto release
if "%0" == "-debug_and_release" goto debug_and_release
if "%0" == "-no-db"             goto nodb
if "%0" == "-msvc"              goto msvc
if "%0" == "/help"              goto help
if "%0" == "-help"              goto help
if "%0" == "--help"             goto help
if "%0" == "/?"                 goto help

echo Unrecognized configure option: %0
del %PROJECT_ROOT%\config.in
goto end

:setqmake
set QMAKEBIN=%1
goto bottom2

:addinclude
echo INCLUDEPATH += "%1" >> %PROJECT_ROOT%\depends.pri
goto bottom2	

:addlibpath
echo LIBS += -L"%1" >> %PROJECT_ROOT%\depends.pri
goto bottom2

:addlib
echo LIBS += -l"%1" >> %PROJECT_ROOT%\depends.pri
goto bottom2

:nomake
if "%1"=="fcgi" set FCGI=0
if "%1"=="db" set DB=0
if "%1"=="zeroconf" set ZEROCONF=0
echo QXT_BUILD -= %1 >> %PROJECT_ROOT%\config.in
goto bottom2

:prefix
echo QXTINSTALLDIR = %1 >> %PROJECT_ROOT%\config.in
goto bottom2

:libdir
echo target.path = %1 >> %PROJECT_ROOT%\config.in
goto bottom2

:docdir
echo docs.path = %1 >> %PROJECT_ROOT%\config.in
goto bottom2

:headerdir
echo include.path = %1 >> %PROJECT_ROOT%\config.in
goto bottom2

:bindir
echo bin.path = %1 >> %PROJECT_ROOT%\config.in
goto bottom2

:static
set STATIC=1
echo CONFIG += static staticlib >> %PROJECT_ROOT%\config.in
goto bottom    

:debug
set DEBUG_OR_RELEASE=1
echo CONFIG += debug >> %PROJECT_ROOT%\config.in
goto bottom

:release
set DEBUG_OR_RELEASE=1
echo CONFIG += release >> %PROJECT_ROOT%\config.in
goto bottom

:debug_and_release
set DEBUG_OR_RELEASE=1
echo CONFIG += debug_and_release >> %PROJECT_ROOT%\config.in
goto bottom

:nodb
set DB=0
echo DEFINES -= HAVE_DB >> %PROJECT_ROOT%\config.in
goto bottom

:nozeroconf
set ZEROCONF=0
echo DEFINES -= HAVE_ZEROCONF >> %PROJECT_ROOT%\config.in
goto bottom

:msvc
set MSVCMODE=-tp vc
goto bottom

:bottom2
    shift
:bottom
    shift
goto top
    
:help
    echo Usage: configure [-prefix (dir)] [-libdir (dir)] [-docdir (dir)]
    echo        [-bindir (dir)] [-headerdir (dir)] [-qmake-bin (path)]
    echo        [-static] [-debug] [-release] [-no-stability-unknown]
    echo        [-nomake (module)] [-msvc]
    echo.
    echo Installation options:
    echo.
    echo -prefix (dir) ....... This will install everything relative to (dir)
    echo                       default: C:\libqxt
    echo -libdir (dir) ....... Libraries will be installed to (dir)
    echo                       default: PREFIX/lib
    echo -docdir (dir) ....... Documentation will be installed to (dir)
    echo                       default: PREFIX/share/doc
    echo -bindir (dir) ....... Executables will be installed to (dir)
    echo                       default: PREFIX/bin
    echo -headerdir (dir) .... Include files will be installed to (dir)
    echo                       default: PREFIX/include
    echo -qmake-bin (path) ... Specifies the path to the qmake executable
    echo                       default: search the system path
    echo -L (path)............ Specifies the a additional library search path
    echo -I (path)............ Specifies the a additional include search path
    echo -l (path)............ Add a custom library
    echo -static ............. Compile Qxt as a static library
    echo -debug .............. Build Qxt with debugging symbols
    echo -release ............ Build Qxt without debugging support
    echo -debug_and_release .. Build Qxt with and without debugging support
    echo -no-db .............. Do not link to Berkeley DB
    echo -nomake (module) .... Do not compile the specified module
    echo                       options: berkeley designer gui network sql web zeroconf
    echo -msvc ............... Configure Qxt to use Microsoft Visual Studio

    del %PROJECT_ROOT%\config.in
    goto end

:finish
echo    Testing for qmake...
qmake -v >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto qmakeERR
goto qmakeOK
:qmakeERR
echo    You don't seem to have 'qmake' in your PATH.
echo    Cannot proceed.
goto end

:qmakeOK
if "%QMAKESPEC%" == "win32-msvc"     goto testnmake
if "%QMAKESPEC%" == "win32-msvc.net" goto testnmake
if "%QMAKESPEC%" == "win32-msvc2005" goto testnmake
if "%QMAKESPEC%" == "win32-msvc2008" goto testnmake

:testmingw
echo    Testing for mingw32-make...
call mingw32-make -v >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto testnmake
echo        Using mingw32-make. 
SET MAKE=mingw32-make
GOTO detectTools_end_test_make     

:testnmake
if "%QMAKESPEC%" == "win32-g++"     goto testgmake
echo    Testing for nmake...
nmake /? >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto testgmake
echo        Using nmake.
SET MAKE=nmake
GOTO detectTools_end_test_make

:testgmake
echo    Testing for GNU make...
call make -v >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto missingmake
echo        Using GNU make.
SET MAKE=make
GOTO detectTools_end_test_make
 
:missingmake
echo    You don't seem to have 'mingw32-make', 'nmake' or 'make' in your PATH. 
echo    Cannot proceed.
goto end

:detectTools_end_test_make
echo    Testing for optional external libraries.
echo    If a test fails, some features will not be available.

:detectdb
if "%DB%"=="0" goto detectzeroconf
echo    Testing for Berkeley DB...
echo BDB... >> %PROJECT_ROOT%\%CONFIG_LOG%
cd %TESTDIR%\db
%QMAKE% >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto dbfailed
call %MAKE% clean >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
call %MAKE% >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto dbfailed
set DB=1
echo DEFINES += HAVE_DB >> %PROJECT_ROOT%\config.in
echo        Berkeley DB enabled.
goto detectzeroconf

:dbfailed
set DB=0
echo DEFINES -= HAVE_DB >> %PROJECT_ROOT%\config.in
echo        Berkeley DB disabled.

:detectzeroconf
if "%ZEROCONF%"=="0" goto detectfcgi
echo    Testing for Zero Conf...
echo ZEROCONF... >> %PROJECT_ROOT%\%CONFIG_LOG%
cd %TESTDIR%\zeroconf
%QMAKE% >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto zeroconffailed
call %MAKE% clean >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
call %MAKE% >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto zeroconffailed
set ZEROCONF=1
echo DEFINES += HAVE_ZEROCONF >> %PROJECT_ROOT%\config.in
echo        Zero Conf enabled.
goto detectfcgi

:zeroconffailed
set ZEROCONF=0
echo DEFINES -= HAVE_ZEROCONF >> %PROJECT_ROOT%\config.in
echo        Zero Conf disabled.

:detectfcgi
rem if "%FCGI%"=="0" goto skipfcgitest
rem echo    Testing for FastCGI...
rem echo fcgi... >> %PROJECT_ROOT%\%CONFIG_LOG%
rem cd %TESTDIR%\fcgi
rem %QMAKE% >> %PROJECT_ROOT%\%CONFIG_LOG%
rem if errorlevel 1 goto fcgifailed
rem call %MAKE% clean >> %PROJECT_ROOT%\%CONFIG_LOG%
rem call %MAKE% >> %PROJECT_ROOT%\%CONFIG_LOG%
rem if errorlevel 1 goto fcgifailed
rem set FCGI=1
rem echo DEFINES += HAVE_FCGI >> %PROJECT_ROOT%\config.in
rem echo        FastCGI enabled.
rem goto alltestsok

:fcgifailed
set FCGI=0
echo DEFINES -= HAVE_FCGI >> %PROJECT_ROOT%\config.in
rem echo        FastCGI disabled.

:skipfcgitest
:alltestsok
if "%DEBUG_OR_RELEASE%"=="1" goto skiprelease
echo CONFIG += release >> %PROJECT_ROOT%\config.in
:skiprelease
cd %PROJECT_ROOT%

echo    Configuration successful.
echo    Generating makefiles...
copy %PROJECT_ROOT%\config.pri %PROJECT_ROOT%\config.pri.bak >> %PROJECT_ROOT%\%CONFIG_LOG%
copy %PROJECT_ROOT%\config.in %PROJECT_ROOT%\config.pri >> %PROJECT_ROOT%\%CONFIG_LOG%
del %PROJECT_ROOT%\config.in >> %PROJECT_ROOT%\%CONFIG_LOG%
echo #define QXT_SHARED > %PROJECT_ROOT%\src\core\qxtconfig.h
if "%STATIC%"=="0" goto skipstatic
echo #define QXT_STATIC > %PROJECT_ROOT%\src\core\qxtconfig.h
:skipstatic
%QMAKE% %MSVCMODE% -recursive
if errorlevel 1 goto mainqmakeERR

echo    Makefiles generated. Run %MAKE% now.
goto end

:mainqmakeERR
echo    Error running qmake. Cannot proceed.
goto end

:end 
