################################
#    libqxt configuration      #
################################




#where to install qxt(default is /opt/qxt on unix , C:\libqxt on windows ,  and /Library/Frameworks on mac)

#QXTINSTALLDIR=/opt/qxt

#QXTUNIXPREFIX=/usr


#modules  (core kit gui network sql media)

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




