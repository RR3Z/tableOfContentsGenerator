QT += testlib
QT += network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_islistempty_tests.cpp \
            ../tableOfContentsGenerator_main/tableOfContentsGenerator.cpp

HEADERS += ../tableOfContentsGenerator_main/tableOfContentsGenerator.h
