TEMPLATE = subdirs
SUBDIRS += bind fifo json job modelserializer pipe sharedprivate slotmapper 
SUBDIRS += filelock #permfail

test.CONFIG += recursive
QMAKE_EXTRA_TARGETS += test
