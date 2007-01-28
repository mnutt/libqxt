echo "==========test============="
qmake

make || { echo "aborted" ;  exit; }
echo "=========clean=============="
make clean
rm *.so
rm Makefile
rm Makefile.*
rm ../bin/libqx.so*

echo "=======packing========"

cd ..
cd ..
tar -cvjf libqxt-$(date -I).tar.bz2 qxt/*
cd libqxt/src

echo "=======uploading pack========"
echo "
user anonymous
pass bla@invalid.com
binary
send ../../libqxt-$(date -I).tar.bz2 /incoming/libqxt-$(date -I).tar.bz2
bye
" | ftp -i -v -n  ftp.sourceforge.net

echo "=======building========"
make
echo "=======doxing========"
doxygen doxygen.conf 
echo "=======uploading dox========"
scp deploy/docs/* xparanoidj@shell.sourceforge.net:/home/groups/l/li/libqxt/htdocs

echo "finished"

