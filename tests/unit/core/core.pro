TEMPLATE = subdirs
SUBDIRS += bind fifo filelock job modelserializer pipe sharedprivate slotmapper

test.CONFIG += recursive
QMAKE_EXTRA_TARGETS += test
