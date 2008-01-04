;--------------------------------

;LibQxt Installation

;--------------------------------
;Includes

  !include "MUI.nsh"
  !include "InstallOptions.nsh"

;--------------------------------
;General

  ;Name and file
  Name "LibQxt 0.3.0"
  OutFile "libqxt-0.3.0.exe"

  ;Default installation folder
  InstallDir "C:\libqxt-0.3.0"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\$(^Name)" ""

  ;Vista redirects $SMPROGRAMS to all users without this
  RequestExecutionLevel admin

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Variables

  Var MUI_TEMP
  Var STARTMENU_FOLDER

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "..\..\cpl1.0.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  
  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\$(^Name)" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER
  
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section QxtBerkeley SecQxtBerkeley
  SetOutPath "$INSTDIR\lib"
  File "..\..\deploy\libs\QxtBerkeley.dll"
  File "..\..\deploy\libs\QxtBerkeley.lib"
  
  SetOutPath "$INSTDIR\include\Qxt\QxtBerkeley"
  File /r /x .svn "..\..\deploy\include\QxtBerkeley\*"
  File /r /x .svn "..\..\src\berkeley\*.h"
SectionEnd

Section QxtCore SecQxtCore

  SectionIn RO ; Mandatory section (appears disabled)
  
  SetOutPath "$INSTDIR\lib"
  File "..\..\deploy\libs\QxtCore.dll"
  File "..\..\deploy\libs\QxtCore.lib"
  
  SetOutPath "$INSTDIR\include\Qxt\QxtCore"
  File /r /x .svn "..\..\deploy\include\QxtCore\*"
  File /r /x .svn "..\..\src\core\*.h"
  
  ;Store installation folder
  WriteRegStr HKCU "Software\$(^Name)" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\uninstall.exe"
  
  ;Create shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\uninstall.lnk" "$INSTDIR\uninstall.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
  
SectionEnd

Section QxtCrypto SecQxtCrypto
  SetOutPath "$INSTDIR\lib"
  File "..\..\deploy\libs\QxtCrypto.dll"
  File "..\..\deploy\libs\QxtCrypto.lib"
  
  SetOutPath "$INSTDIR\include\Qxt\QxtCrypto"
  File /r /x .svn "..\..\deploy\include\QxtCrypto\*"
  File /r /x .svn /x thirdparty "..\..\src\crypto\*.h"
SectionEnd

Section QxtGui SecQxtGui
  SetOutPath "$INSTDIR\lib"
  File "..\..\deploy\libs\QxtGui.dll"
  File "..\..\deploy\libs\QxtGui.lib"
  
  SetOutPath "$INSTDIR\include\Qxt\QxtGui"
  File /r /x .svn "..\..\deploy\include\QxtGui\*"
  File /r /x .svn "..\..\src\gui\*.h"
SectionEnd

Section QxtDesignerPlugins SecDesignerPlugins
SectionEnd

Section QxtNetwork SecQxtNetwork
  SetOutPath "$INSTDIR\lib"
  File "..\..\deploy\libs\QxtNetwork.dll"
  File "..\..\deploy\libs\QxtNetwork.lib"
  
  SetOutPath "$INSTDIR\include\Qxt\QxtNetwork"
  File /r /x .svn "..\..\deploy\include\QxtNetwork\*"
  File /r /x .svn "..\..\src\network\*.h"
SectionEnd

Section QxtSql SecQxtSql
  SetOutPath "$INSTDIR\lib"
  File "..\..\deploy\libs\QxtSql.dll"
  File "..\..\deploy\libs\QxtSql.lib"
  
  SetOutPath "$INSTDIR\include\Qxt\QxtSql"
  File /r /x .svn "..\..\deploy\include\QxtSql\*"
  File /r /x .svn "..\..\src\sql\*.h"
SectionEnd

Section QxtWeb SecQxtWeb
  SetOutPath "$INSTDIR\lib"
  File "..\..\deploy\libs\QxtWeb.dll"
  File "..\..\deploy\libs\QxtWeb.lib"
  
  SetOutPath "$INSTDIR\include\Qxt\QxtWeb"
  File /r /x .svn "..\..\deploy\include\QxtWeb\*"
  File /r /x .svn "..\..\src\web\*.h"
SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecQxtBerkeley ${LANG_ENGLISH} "The QxtBerkeley module provides a persistent storage."
  LangString DESC_SecQxtCore ${LANG_ENGLISH} "The QxtCore module extends QtCore and contains core non-GUI functionality."
  LangString DESC_SecQxtCrypto ${LANG_ENGLISH} "The QxtCrypto module provides tools for encryption and hashing."
  LangString DESC_SecQxtGui ${LANG_ENGLISH} "The QxtGui module extends QtGui."
  LangString DESC_SecQxtDesignerPlugins ${LANG_ENGLISH} "The QxtDesignerPlugins module provides designer plugins for QxtGui widgets."
  LangString DESC_SecQxtNetwork ${LANG_ENGLISH} "The QxtNetwork module extends QtNetwork with RPC functionality."
  LangString DESC_SecQxtSql ${LANG_ENGLISH} "The QxtSql module extends QtSql with serializable queries."
  LangString DESC_SecQxtWeb ${LANG_ENGLISH} "The QxtWeb module provides Qt like Web Developement tools."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecQxtBerkeley} $(DESC_SecQxtBerkeley)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecQxtCore} $(DESC_SecQxtCore)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecQxtCrypto} $(DESC_SecQxtCrypto)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecQxtGui} $(DESC_SecQxtGui)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDesignerPlugins} $(DESC_SecQxtDesignerPlugins)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecQxtNetwork} $(DESC_SecQxtNetwork)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecQxtSql} $(DESC_SecQxtSql)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecQxtWeb} $(DESC_SecQxtWeb)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\uninstall.exe"

  RMDir /r "$INSTDIR"
  
  !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
    
  Delete "$SMPROGRAMS\$MUI_TEMP\uninstall.lnk"
  
  ;Delete empty start menu parent diretories
  StrCpy $MUI_TEMP "$SMPROGRAMS\$MUI_TEMP"
 
  startMenuDeleteLoop:
	ClearErrors
    RMDir $MUI_TEMP
    GetFullPathName $MUI_TEMP "$MUI_TEMP\.."
    
    IfErrors startMenuDeleteLoopDone
  
    StrCmp $MUI_TEMP $SMPROGRAMS startMenuDeleteLoopDone startMenuDeleteLoop
  startMenuDeleteLoopDone:

  DeleteRegKey /ifempty HKCU "Software\$(^Name)"

SectionEnd
