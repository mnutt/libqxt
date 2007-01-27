################################
#    libqxt configuration      #
################################




#install prefix / dir
#
#on Windows qxt will be fully installed to that directory  (default is to C:\libqxt)
#on Unix qxt will be installed in  $QXTINSTALLDIR/lib/  $QXTINSTALLDIR/include  $QXTINSTALLDIR/doc/libqxt/  $QXTINSTALLDIR/bin/   (default is /usr)
#on mac the behaiviour is not tested (should install everyhting to /Library/Frameworks by default)

#QXTINSTALLDIR=/usr

#modules  (core kit gui network sql media mox)

#QXT -= media


#librarys libqxt will be linked to (openssl)
#exclude any librarys you dont want liqxt to be linked to
# note that excluding libs means loosing features

#QXT_LIBS-=openssl




#part stability (stable  broken unknown)
#note that this varys from platform to platform
#parts working on one OS maybe broken on a second

QXT_stability+= unknown


#you can ignore stability for parts. this will make it compile regardless how the deevloper flaged it (parts to be added here)

#QXT_ignore_stability += blowfish




