QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_findseperateclosetagheaders_tests.cpp \
            ../tableOfContentsGenerator_main/findHeaders.cpp

HEADERS += ../tableOfContentsGenerator_main/findHeaders.h
