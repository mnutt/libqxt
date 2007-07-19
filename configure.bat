@ECHO off
SET QMAKE=qmake
SET MAKE=nmake
SET PROJECT_ROOT=%CD%
SET TESTDIR=%PROJECT_ROOT%\config.tests
SET CONFIG_LOG=config.log
SET LAST_FUNC_RET=0

del %PROJECT_ROOT%\config.in >>Nul
del %PROJECT_ROOT%\config.log >>Nul
del %PROJECT_ROOT%\depends.pri >>Nul

echo #depends.pri > %PROJECT_ROOT%\depends.pri
    
shift
set QMAKEBIN=qmake
set MSVCMODE=
set OPENSSL=1
set CURSES=1
echo include(depends.pri) > %PROJECT_ROOT%\config.in
echo QXT_stability += unknown >> %PROJECT_ROOT%\config.in

:top
if "%0" == ""            goto finish
if "%0" == "-qmake-bin"  goto setqmake
if "%0" == "-I"          goto addinclude 
if "%0" == "-L"          goto addlibpath
if "%0" == "-l"          goto addlib
if "%0" == "-nomake"     goto nomake
if "%0" == "-prefix"     goto prefix
if "%0" == "-libdir"     goto libdir 
if "%0" == "-docdir"     goto docdir
if "%0" == "-headerdir"  goto headerdir
if "%0" == "-bindir"     goto bindir
if "%0" == "-static"     goto static
if "%0" == "-debug"      goto debug
if "%0" == "-release"    goto release
if "%0" == "-no-openssl" goto noopenssl
if "%0" == "-msvc"       goto msvc
if "%0" == "/help"       goto help
if "%0" == "-help"       goto help
if "%0" == "--help"      goto help
if "%0" == "/?"          goto help

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
if "%1"=="curses" set CURSES=0
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
echo CONFIG += static staticlib >> %PROJECT_ROOT%\config.in
goto bottom    

:debug
echo CONFIG += debug >> %PROJECT_ROOT%\config.in
goto bottom

:release
echo CONFIG += release >> %PROJECT_ROOT%\config.in
goto bottom

:noopenssl
set OPENSSL=0
echo QXT_LIBS -= openssl >> %PROJECT_ROOT%\config.in
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
    echo        [-no-openssl] [-nomake (module)] [-msvc]
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
    echo -no-openssl ......... Do not link to OpenSSL
    echo -nomake (module) .... Do not compile the specified module
    echo                       options: kit network gui sql media curses web
    echo -msvc ............... Configure Qxt to use Microsoft Visual Studio

    del %PROJECT_ROOT%\config.in
    goto end

:finish
echo    Testing for qmake...
qmake -v >> %PROJECT_ROOT%\%CONFIG_LOG%
if errorlevel 1 goto qmakeERR
goto qmakeOK
:qmakeERR
echo    You don't seem to have 'qmake' in your PATH.
echo    Cannot proceed.
goto end

:qmakeOK
echo    Testing for nmake...
nmake /? >> %PROJECT_ROOT%\%CONFIG_LOG%
if errorlevel 1 goto nmakeERR
echo    Using nmake.
SET MAKE=nmake
GOTO detectTools_end_test_make

:nmakeERR
echo    Testing for GNU make...
make -v >> %PROJECT_ROOT%\%CONFIG_LOG%
if errorlevel 1 goto gmakeERR
echo    Using GNU make.
SET MAKE=make
GOTO detectTools_end_test_make

:gmakeERR
echo    Testing for mingw32-make...
mingw32-make -v >> %PROJECT_ROOT%\%CONFIG_LOG%
if errorlevel 1 goto mingwmakeERR
echo    Using mingw32-make. 
SET MAKE=mingw32-make
GOTO detectTools_end_test_make     
 
:mingwmakeERR
echo    You don't seem to have 'make.' 'mingw32-make,' or 'nmake' in your PATH. 
echo    Cannot proceed.
goto end

:detectTools_end_test_make
if "%OPENSSL%"=="0" goto skipopenssltest
echo Testing for OpenSSL... 
echo OpenSSL... >> %PROJECT_ROOT%\%CONFIG_LOG%
cd %TESTDIR%\openssl
%QMAKE% >> %PROJECT_ROOT%\%CONFIG_LOG%
if errorlevel 1 goto testfailed
%MAKE% clean >> %PROJECT_ROOT%\%CONFIG_LOG%
%MAKE% >> %PROJECT_ROOT%\%CONFIG_LOG%
if errorlevel 1 goto testfailed

:skipopenssltest
if "%CURSES%"=="0" goto skipcursestest
echo Testing for curses... 
echo curses... >> %PROJECT_ROOT%\%CONFIG_LOG%
cd %TESTDIR%\curses
%QMAKE% >> %PROJECT_ROOT%\%CONFIG_LOG%
if errorlevel 1 goto testfailed
%MAKE% clean >> %PROJECT_ROOT%\%CONFIG_LOG%
%MAKE% >> %PROJECT_ROOT%\%CONFIG_LOG%
if errorlevel 1 goto testfailed

goto alltestsok

:testfailed
echo Test failed. Cannot proceed.
goto end

:skipcursestest
:alltestsok
cd %PROJECT_ROOT%

echo Configuration successful. Generating makefiles.
copy %PROJECT_ROOT%\config.pri %PROJECT_ROOT%\config.pri.bak >> %PROJECT_ROOT%\%CONFIG_LOG%
copy %PROJECT_ROOT%\config.in %PROJECT_ROOT%\config.pri >> %PROJECT_ROOT%\%CONFIG_LOG%
del %PROJECT_ROOT%\config.in >> %PROJECT_ROOT%\%CONFIG_LOG%
%QMAKE% %MSVCMODE% -recursive
if errorlevel 1 goto mainqmakeERR

echo Makefiles generated. Run %MAKE% now.
goto end

:mainqmakeERR
echo Error running qmake. Cannot proceed.
goto end

:end 
