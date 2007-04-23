::/****************************************************************************
::**
::** Copyright (C) Qxt Foundation. Some rights reserved.
::**
::** This file is part of the Qxt build system of the Qt eXTension library
::**
::** This library is free software; you can redistribute it and/or
::** modify it under the terms of the GNU Lesser General Public
::** License as published by the Free Software Foundation; either
::** version 2.1 of the License, or any later version.
::**
::** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
::** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
::**
::** There is aditional information in the LICENSE file of libqxt.
::** If you did not receive a copy of the file try to download it or
::** contact the libqxt Management
::** 
::** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
::**
::****************************************************************************/

@ECHO off
::set our subroutine handlers
GOTO handle_subroutine

::please prefix all functions with func_ to avoid problems with normal labels
::do not use set errorlevel as you returnvalue cmd will not touch it after we set the errorlevel

:: ---------------------------------MAIN FUNCTION------------------------------------------------------
:func_main
    SET QMAKE=qmake
    SET MAKE=nmake
    SET PROJECT_ROOT=%CD%
    SET TESTDIR=%PROJECT_ROOT%\config.tests
    SET CONFIG_LOG=config.log
    SET LAST_FUNC_RET=0
    
    del %PROJECT_ROOT%\config.in >>Nul  2>&1
    del %PROJECT_ROOT%\config.log >>Nul  2>&1
    del %PROJECT_ROOT%\depends.pri >>Nul 2>&1

    echo #depends.pri > %PROJECT_ROOT%\depends.pri
    
    ::this is a workaround for supporting win9x
    ::win9x does not support passing all commandline params with %*
    :: %CALL_SUB% func_readArgs %*
    :: 
   
    shift
    
    GOTO lbl_func_readArgs
    :win9x_end_readArgs
    IF %LAST_FUNC_RET% == 1 goto RETURN
    
    %CALL_SUB% func_detectTools
    IF %LAST_FUNC_RET% == 1 goto RETURN
    
    %CALL_SUB% func_testLibs openssl OPENSSL network

    %CALL_SUB% func_testLibs ffmpeg FFMPEG media
    
    %CALL_SUB% func_testLibs sdl SDL media
    
    %CALL_SUB% func_testLibs curses CURSES curses
    
    echo autodetection finished running qmake
    cd %PROJECT_ROOT%
    %CALL_SUB% func_compile
    
    
GOTO RETURN
::--------------------------------End of main----------------------------------------------------------

:: ----func_test3rdParty Test for 3rdparty libs
:: param 0 name of lib
:: param 1 name param to add to project file
:: param 2 Qxt Package that needs this lib
::-----------------------------------------
:func_testLibs
echo func_testLibs
    echo %2
    echo testing for %0 
    echo %0 >>%PROJECT_ROOT%\%CONFIG_LOG%
    cd %TESTDIR%\%0
    %QMAKE% >>%PROJECT_ROOT%\%CONFIG_LOG% 2>&1
    IF NOT %ERRORLEVEL% == 0 (
        GOTO lbl_testLibs_error       
    )
    
    %MAKE% clean >>Nul 2>&1
    
    %MAKE% >>%PROJECT_ROOT%\%CONFIG_LOG% 2>&1
    IF %ERRORLEVEL% == 0 (
        echo DEFINES+=HAVE_%1% >>%PROJECT_ROOT%\config.in
        echo .....[SUCCESS]
        SET LAST_FUNC_RET=0
        GOTO lbl_testLibs_end       
    )

    :lbl_testLibs_error
    echo .....[FAILED]
    echo .....not creating %2
    echo QXT_BUILD -= %2 >> %PROJECT_ROOT%\config.in
    SET LAST_FUNC_RET=1
    
    :lbl_testLibs_end
    cd %PROJECT_ROOT%
        
GOTO RETURN

:: ----func_detectTools
:: looks for qmake and make
:func_detectTools
    echo autodetecting tools

    ::checking for Qmake
    echo    testing for qmake
    
    qmake -v >>%PROJECT_ROOT%\%CONFIG_LOG% 2>&1
    IF NOT %ERRORLEVEL% == 0 (
    echo    You don't seem to have 'qmake' in your PATH.
    echo    Cannot proceed.
    SET LAST_FUNC_RET=1
    GOTO RETURN
    )
    echo    qmake found
    
    echo testing for make

    :detectTools_test_make
    echo    testing for nmake
    nmake /? >>%PROJECT_ROOT%\%CONFIG_LOG% 2>&1
    IF NOT %ERRORLEVEL% == 0 (
        echo    testing for gnu make
        make -v >>%PROJECT_ROOT%\%CONFIG_LOG% 2>&1
        IF NOT %ERRORLEVEL% == 0 (
            echo    testing for mingw32-make
            mingw32-make  -v >>%PROJECT_ROOT%\%CONFIG_LOG% 2>&1
            IF NOT %ERRORLEVEL% == 0 (
                echo    You don't seem to have 'make' or 'nmake' in your PATH. 
                echo    Cannot proceed.
                SET LAST_FUNC_RET=1
                GOTO RETURN
            )
            echo    using mingw32-make
            SET MAKE=mingw32-make
            GOTO detectTools_end_test_make
        )
        echo    using make
        SET MAKE=make
        GOTO detectTools_end_test_make
        
    )
    echo    using nmake
    SET MAKE=nmake
    :detectTools_end_test_make
    SET LAST_FUNC_RET=0
GOTO RETURN

:: ----func_compile
:func_compile
    copy %PROJECT_ROOT%\config.pri %PROJECT_ROOT%\config.pri.bak >>Nul  2>&1
    copy %PROJECT_ROOT%\config.in %PROJECT_ROOT%\config.pri >>Nul  2>&1
    del %PROJECT_ROOT%\config.in >>Nul type conf 2>&1
    %QMAKE% %MSVCMODE% -recursive
GOTO RETURN

:: ----func_readArgs
:lbl_func_readArgs
    set QMAKEBIN=qmake
    set MSVCMODE=
    echo include(depends.pri) > %PROJECT_ROOT%\config.in
    echo QXT_stability += unknown >> %PROJECT_ROOT%\config.in
    
    :top
    if "%0" == "" goto finish
    if "%0" == "-qmake-bin" (
        set QMAKEBIN=%1
        goto bottom2
    )

    if "%0" == "-I" (
        echo INCLUDEPATH += "%1" >> %PROJECT_ROOT%\depends.pri
        goto bottom2	
    )
   
    if "%0" == "-L" (
        echo LIBS += -L"%1" >> %PROJECT_ROOT%\depends.pri
        goto bottom2
    )

    if "%0" == "-l" (
        echo LIBS += -l"%1" >> %PROJECT_ROOT%\depends.pri
        goto bottom2
    )
    
    if "%0" == "-nomake" (
        echo QXT_BUILD -= %1 >> %PROJECT_ROOT%\config.in
        goto bottom2
    )
    
    if "%0" == "-prefix" (
        echo QXTINSTALLDIR = %1 >> %PROJECT_ROOT%\config.in
        goto bottom2
    )
    
    if "%0" == "-libdir" (
        echo target.path = %1 >> %PROJECT_ROOT%\config.in
        goto bottom2
    )
    
    if "%0" == "-docdir" (
        echo docs.path = %1 >> %PROJECT_ROOT%\config.in
        goto bottom2
    )
    
    if "%0" == "-headerdir" (
        echo include.path = %1 >> %PROJECT_ROOT%\config.in
        goto bottom2
    )
    
    if "%0" == "-bindir" (
        echo bin.path = %1 >> %PROJECT_ROOT%\config.in
        goto bottom2
    )
    
    if "%0" == "-ignore-stability" (
        echo QXT_ignore_stability += %1 >> %PROJECT_ROOT%\config.in
        goto bottom2
    )
    
    if "%0" == "-static" (
        echo CONFIG += static staticlib >> %PROJECT_ROOT%\config.in
        goto bottom    
    )
    
    if "%0" == "-debug" (
        echo CONFIG += debug >> %PROJECT_ROOT%\config.in
        goto bottom
    )
    
    if "%0" == "-release" (
        echo CONFIG += release >> %PROJECT_ROOT%\config.in
        goto bottom
    )
    
    if "%0" == "-no-stability-unknown" (
        echo QXT_stability -= unknown >> %PROJECT_ROOT%\config.in
        goto bottom
    )
    
    if "%0" == "-no-openssl" (
        echo QXT_LIBS -= openssl >> %PROJECT_ROOT%\config.in
        goto bottom
    )

    if "%0" == "-msvc" (
        set MSVCMODE=-tp vc
        goto bottom
    )
    
    if "%0" == "/help" goto help
    if "%0" == "-help" goto help
    if "%0" == "--help" goto help
    if "%0" == "/?" goto help
    
    echo Unrecognized configure option: %0
    del %PROJECT_ROOT%\config.in
    SET LAST_FUNC_RET=1
    GOTO RETURN
    
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
        echo -no-stability-unknown Do not build untested classes
        echo -no-openssl ......... Do not link to OpenSSL
        echo -nomake (module) .... Do not compile the specified module
        echo                       options: kit network gui sql media curses web
        echo -msvc ............... Configure Qxt to use Microsoft Visual Studio
    
        del %PROJECT_ROOT%\config.in
        SET LAST_FUNC_RET=1
        GOTO RETURN
    
    :finish
    ::return with errorlevel 0
    SET LAST_FUNC_RET=0
GOTO win9x_end_readArgs

::-----------------------------------subroutine handler do not touch this---------------------------
:handle_subroutine
    :: if we are not in a subroutine call goto main
    IF (CALL_FNC)==(%1) (
        ::make %0 the first argument
        shift
        shift
        shift
        ::shift
        GOTO %2 ::this calls the subroutines in this file
    )
    SET ROOTDIR=%CD%
    set CALL_SUB=CALL %0 CALL_FNC
    GOTO func_main
    
    
:RETURN {End-of-code}
