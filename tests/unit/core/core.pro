TEMPLATE = subdirs
SUBDIRS += bind fifo json job modelserializer pipe sharedprivate slotmapper tempdir
SUBDIRS += filelock #permfail

test.CONFIG += recursive
QMAKE_EXTRA_TARGETS += test
