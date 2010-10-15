@ECHO off

@rem -- defaults
set QMAKE_BIN=qmake
set MAKE_BIN=
set STATIC=0
set DEBUG_OR_RELEASE=0
set MSVCMODE=
set DB=1
set ZEROCONF=1
set QXT_MODULES=docs core gui network sql web designer berkeley zeroconf

@rem -- initialize
set QXT_INSTALL_PREFIX=
set QXT_INSTALL_LIBS=
set QXT_INSTALL_BINS=
set QXT_INSTALL_HEADERS=
set QXT_INSTALL_FEATURES=
set QXT_INSTALL_DOCS=

@rem -- working directories
set QXT_BUILD_TREE=%CD%
cd "%0\..\"
SET QXT_SOURCE_TREE=%CD%
cd %QXT_BUILD_TREE%
if not exist %QXT_BUILD_TREE%\examples mkdir %QXT_BUILD_TREE%\examples 2>&1 >NUL 2>&1
if not exist %QXT_BUILD_TREE%\tests mkdir %QXT_BUILD_TREE%\tests 2>&1 >NUL 2>&1

@rem -- output files
set CONFIG_LOG=%QXT_BUILD_TREE%\config.log
set QMAKE_CACHE=%QXT_BUILD_TREE%\.qmake.cache
set QXT_VARS=%QXT_BUILD_TREE%\qxtvars.prf
if exist %CONFIG_LOG% move %CONFIG_LOG% %CONFIG_LOG%.bak >NUL 2>&1
if exist %QMAKE_CACHE% move %QMAKE_CACHE% %QMAKE_CACHE%.bak >NUL 2>&1
if exist %QXT_VARS% move %QXT_VARS% %QXT_VARS%.bak 2>&1 >NUL 2>&1

@rem -- defaults
echo CONFIG += silent > %QMAKE_CACHE%
echo QXT_MODULES = %QXT_MODULES% >> %QMAKE_CACHE%
echo QXT_MODULES = %QXT_MODULES% > %QXT_VARS%

shift
:top
if "%0" == ""                   goto finish
if "%0" == "-qmake-bin"         goto setqmake
if "%0" == "-make-bin"          goto setmake
if "%0" == "-I"                 goto addinclude 
if "%0" == "-L"                 goto addlibpath
if "%0" == "-l"                 goto addlib
if "%0" == "-nomake"            goto nomake
if "%0" == "-prefix"            goto prefix
if "%0" == "-libdir"            goto libdir 
if "%0" == "-docdir"            goto docdir
if "%0" == "-headerdir"         goto headerdir
if "%0" == "-bindir"            goto bindir
if "%0" == "-featuredir"        goto featuredir
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
del %QMAKE_CACHE%
del %QXT_VARS%
goto end

:setqmake
set QMAKE_BIN=%1
goto bottom2

:setmake
set MAKE_BIN=%1
goto bottom2

:addinclude
set QXT_INCPATH=%1
set QXT_INCPATH=%QXT_INCPATH:\=/%
echo INCLUDEPATH += %QXT_INCPATH% >> %QMAKE_CACHE%
goto bottom2

:addlibpath
set QXT_LIBPATH=%1
set QXT_LIBPATH=%QXT_LIBPATH:\=/%
echo LIBS += -L%QXT_LIBPATH% >> %QMAKE_CACHE%
goto bottom2

:addlib
echo LIBS += -l%1 >> %QMAKE_CACHE%
goto bottom2

:nomake
if "%1"=="db" set DB=0
if "%1"=="zeroconf" set ZEROCONF=0
echo QXT_MODULES -= %1 >> %QMAKE_CACHE%
echo QXT_MODULES -= %1 >> %QXT_VARS%
goto bottom2

:prefix
echo hmm
set QXT_INSTALL_PREFIX=%1
goto bottom2

:libdir
set QXT_INSTALL_LIBS=%1
goto bottom2

:docdir
set QXT_INSTALL_DOCS=%1
goto bottom2

:headerdir
set QXT_INSTALL_HEADERS=%1
goto bottom2

:bindir
set QXT_INSTALL_BINS=%1
goto bottom2

:featuredir
set QXT_INSTALL_FEATURES=%1
goto bottom2

:static
set STATIC=1
echo CONFIG += static staticlib >> %QMAKE_CACHE%
echo DEFINES += QXT_STATIC >> %QXT_VARS%
goto bottom    

:debug
set DEBUG_OR_RELEASE=1
echo CONFIG += debug >> %QMAKE_CACHE%
goto bottom

:release
set DEBUG_OR_RELEASE=1
echo CONFIG += release >> %QMAKE_CACHE%
goto bottom

:debug_and_release
set DEBUG_OR_RELEASE=1
echo CONFIG += debug_and_release build_all >> %QMAKE_CACHE%
goto bottom

:nodb
set DB=0
echo DEFINES -= HAVE_DB >> %QMAKE_CACHE%
goto bottom

:nozeroconf
set ZEROCONF=0
echo DEFINES -= HAVE_ZEROCONF >> %QMAKE_CACHE%
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
    echo        [-make-bin (path)] [-nomake (module)] [-debug] [-release]
    echo        [-static]
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
    echo -make-bin (path) .... Specifies the path to the make executable
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

    del %QMAKE_CACHE%
    goto end

:finish
echo    Testing for qmake...
%QMAKE_BIN% -v >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto qmakeERR
goto qmakeOK
:qmakeERR
echo    You don't seem to have 'qmake' in your PATH.
echo    Cannot proceed.
goto end

:qmakeOK
if not "%MAKE_BIN%" == "" goto detectTools_end_test_make
if "%QMAKESPEC%" == "win32-msvc"     goto testnmake
if "%QMAKESPEC%" == "win32-msvc.net" goto testnmake
if "%QMAKESPEC%" == "win32-msvc2005" goto testnmake
if "%QMAKESPEC%" == "win32-msvc2008" goto testnmake

:testmingw
echo    Testing for mingw32-make...
call mingw32-make -v >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto testnmake
echo        Using mingw32-make. 
SET MAKE_BIN=mingw32-make
GOTO detectTools_end_test_make     

:testnmake
if "%QMAKESPEC%" == "win32-g++"     goto testgmake
echo    Testing for nmake...
nmake /? >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto testgmake
echo        Using nmake.
SET MAKE_BIN=nmake
GOTO detectTools_end_test_make

:testgmake
echo    Testing for GNU make...
call make -v >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto missingmake
echo        Using GNU make.
SET MAKE_BIN=make
GOTO detectTools_end_test_make
 
:missingmake
echo    You don't seem to have 'mingw32-make', 'nmake' or 'make' in your PATH. 
echo    Cannot proceed.
goto end

:detectTools_end_test_make
if not "%QXT_INSTALL_PREFIX%" == "" goto skipdefaultprefix
    set QXT_INSTALL_PREFIX=C:\Qxt
:skipdefaultprefix
if not "%QXT_INSTALL_LIBS%" == "" goto skipdefaultlibs
    set QXT_INSTALL_LIBS=%QXT_INSTALL_PREFIX%\lib
:skipdefaultlibs
if not "%QXT_INSTALL_DOCS%" == "" goto skipdefaultdocs
    set QXT_INSTALL_DOCS=%QXT_INSTALL_PREFIX%\doc
:skipdefaultdocs
if not "%QXT_INSTALL_HEADERS%" == "" goto skipdefaultheaders
    set QXT_INSTALL_HEADERS=%QXT_INSTALL_PREFIX%\include
:skipdefaultheaders
if not "%QXT_INSTALL_BINS%" == "" goto skipdefaultbins
    set QXT_INSTALL_BINS=%QXT_INSTALL_PREFIX%\bin
:skipdefaultbins
if not "%QXT_INSTALL_FEATURES%" == "" goto skipdefaultfeatures
    %QMAKE_BIN% -query QMAKE_MKSPECS > %QXT_BUILD_TREE%\mkspecs.tmp
    set /p QXT_INSTALL_FEATURES=<%QXT_BUILD_TREE%\mkspecs.tmp
    set QXT_INSTALL_FEATURES=%QXT_INSTALL_FEATURES%\features
    del %QXT_BUILD_TREE%\mkspecs.tmp
:skipdefaultfeatures

echo QXT_INSTALL_PREFIX = %QXT_INSTALL_PREFIX:\=/% >> %QMAKE_CACHE%
echo QXT_INSTALL_PREFIX = %QXT_INSTALL_PREFIX:\=/% >> %QXT_VARS%
echo QXT_INSTALL_LIBS = %QXT_INSTALL_LIBS:\=/% >> %QMAKE_CACHE%
echo QXT_INSTALL_LIBS = %QXT_INSTALL_LIBS:\=/% >> %QXT_VARS%
echo QXT_INSTALL_BINS = %QXT_INSTALL_BINS:\=/% >> %QMAKE_CACHE%
echo QXT_INSTALL_BINS = %QXT_INSTALL_BINS:\=/% >> %QXT_VARS%
echo QXT_INSTALL_HEADERS = %QXT_INSTALL_HEADERS:\=/% >> %QMAKE_CACHE%
echo QXT_INSTALL_HEADERS = %QXT_INSTALL_HEADERS:\=/% >> %QXT_VARS%
echo QXT_INSTALL_FEATURES = %QXT_INSTALL_FEATURES:\=/% >> %QMAKE_CACHE%
echo QXT_INSTALL_FEATURES = %QXT_INSTALL_FEATURES:\=/% >> %QXT_VARS%
echo QXT_INSTALL_DOCS = %QXT_INSTALL_DOCS:\=/% >> %QMAKE_CACHE%
echo QXT_INSTALL_DOCS = %QXT_INSTALL_DOCS:\=/% >> %QXT_VARS%
echo QXT_SOURCE_TREE = %QXT_SOURCE_TREE:\=/% >> %QMAKE_CACHE%
echo QXT_BUILD_TREE = %QXT_BUILD_TREE:\=/% >> %QMAKE_CACHE%

echo    Testing for optional external libraries.
echo    If tests fail, some features will not be available.

:detectdb
if "%DB%"=="0" goto detectzeroconf
echo    Testing for Berkeley DB...
echo BDB... >> %CONFIG_LOG%
if not exist %QXT_BUILD_TREE%\config.tests\db mkdir %QXT_BUILD_TREE%\config.tests\db
cd %QXT_BUILD_TREE%\config.tests\db
%QMAKE_BIN% %QXT_SOURCE_TREE%\config.tests\db\db.pro >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto dbfailed
call %MAKE_BIN% clean >> %CONFIG_LOG% 2>&1
call %MAKE_BIN% >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto dbfailed
set DB=1
echo DEFINES += HAVE_DB >> %QMAKE_CACHE%
echo        Berkeley DB enabled.
goto detectzeroconf

:dbfailed
set DB=0
echo DEFINES -= HAVE_DB >> %QMAKE_CACHE%
echo        Berkeley DB disabled.

:detectzeroconf
if "%ZEROCONF%"=="0" goto alltestsok
echo    Testing for Zero Conf...
echo ZEROCONF... >> %CONFIG_LOG%
if not exist %QXT_BUILD_TREE%\config.tests\zeroconf mkdir %QXT_BUILD_TREE%\config.tests\zeroconf
cd %QXT_BUILD_TREE%\config.tests\zeroconf
%QMAKE_BIN% %QXT_SOURCE_TREE%\config.tests\zeroconf\zeroconf.pro >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto zeroconffailed
call %MAKE_BIN% clean >> %CONFIG_LOG% 2>&1
call %MAKE_BIN% >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto zeroconffailed
set ZEROCONF=1
echo DEFINES += HAVE_ZEROCONF >> %QMAKE_CACHE%
echo        Zero Conf enabled.
goto alltestsok

:zeroconffailed
set ZEROCONF=0
echo DEFINES -= HAVE_ZEROCONF >> %QMAKE_CACHE%
echo        Zero Conf disabled.

:alltestsok
if "%DEBUG_OR_RELEASE%"=="1" goto skiprelease
echo CONFIG += release >> %QMAKE_CACHE%
:skiprelease

echo    Configuration successful.
echo    Generating makefiles...
cd %QXT_BUILD_TREE%
%QMAKE_BIN% %MSVCMODE% -recursive %QXT_SOURCE_TREE%\libqxt.pro
if errorlevel 1 goto mainqmakeERR

if not "%MSVCMODE%" == "" goto skipmakeannounce
echo    Makefiles generated. Run %MAKE% now.
goto end
:skipmakeannounce
echo    Visual Studio solution generated. Open libqxt.sln in Visual Studio.
goto end

:mainqmakeERR
echo    Error running qmake. Cannot proceed.
goto end

:end 
