@echo off
set QMAKEBIN=qmake
set MSVCMODE=
echo QXT_stability += unknown > config.in

:top
if "%1" == "" goto finish
if "%1" == "-qmake-bin" goto qmakebin
if "%1" == "-nomake" goto nomake
if "%1" == "-prefix" goto prefix
if "%1" == "-libdir" goto libdir
if "%1" == "-docdir" goto docdir
if "%1" == "-headerdir" goto headerdir
if "%1" == "-bindir" goto bindir
if "%1" == "-ignore-stability" goto ignorestability
if "%1" == "-static" goto static
if "%1" == "-debug" goto debug
if "%1" == "-release" goto release
if "%1" == "-no-stability-unknown" goto nounknown
if "%1" == "-no-openssl" goto nossl
if "%1" == "-msvc" goto msvc
if "%1" == "-help" goto help
if "%1" == "--help" goto help
if "%1" == "/help" goto help
if "%1" == "/?" goto help

echo Unrecognized configure option: %1
del config.in
goto end

:bottom2
shift
:bottom
shift
goto top

:qmakebin
    set QMAKEBIN=%2
    goto bottom2

:nomake
    echo QXT_BUILD -= %2 >> config.in
    goto bottom2

:prefix
    echo QXTINSTALLDIR = %2 >> config.in
    goto bottom2

:libdir
    echo target.path = %2 >> config.in
    goto bottom2

:docdir
    echo docs.path = %2 >> config.in
    goto bottom2

:headerdir
    echo include.path = %2 >> config.in
    goto bottom2

:bindir
    echo bin.path = %2 >> config.in
    goto bottom2

:ignorestability
    echo QXT_ignore_stability += %2 >> config.in
    goto bottom2

:static
    echo CONFIG += static staticlib >> config.in
    goto bottom

:debug
    echo CONFIG += debug >> config.in
    goto bottom

:release
    echo CONFIG += release >> config.in
    goto bottom

:nounknown
    echo QXT_stability -= unknown >> config.in
    goto bottom

:nossl
    echo QXT_LIBS -= openssl >> config.in
    goto bottom

:msvc
<<<<<<< .mine
    set MSVCMODE=-tp vc
    echo TEMPLATE = vcsubdirs  >> config.in
=======
    echo TEMPLATE = vclib  >> config.in
>>>>>>> .r331
    goto bottom

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
    echo -static ............. Compile Qxt as a static library
    echo -debug .............. Build Qxt with debugging symbols
    echo -release ............ Build Qxt without debugging support
    echo -no-stability-unknown Do not build untested classes
    echo -no-openssl ......... Do not link to OpenSSL
    echo -nomake (module) .... Do not compile the specified module
    echo                       options: kit network gui sql media curses web
    echo -msvc ............... Configure Qxt to use Microsoft Visual Studio

    del config.in
    goto end

:finish
copy config.pri config.pri.bak
copy config.in config.pri
del config.in

%QMAKEBIN% %MSVCMODE% -recursive

:end
