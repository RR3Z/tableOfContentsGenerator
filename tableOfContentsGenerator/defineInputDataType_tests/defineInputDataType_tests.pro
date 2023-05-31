QT += testlib
QT += network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_defineinputdatatype_tests.cpp \
            ../tableOfContentsGenerator_main/tableOfContentsGenerator.cpp

HEADER += ../tableOfContentsGenerator_main/tableOfContentsGenerator.h
