TEMPLATE = subdirs
SUBDIRS += other unit

test.depends += sub-unit
test.recurse += unit
test.CONFIG += recursive
QMAKE_EXTRA_TARGETS += test
