QT += core
QT -= gui

CONFIG += c++11

TARGET = itransition-task
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src/main.cpp \
    src/Adler32Generator.cpp \
    src/DownloaderFile.cpp \
    src/DownloaderParallel.cpp \
    src/DownloaderString.cpp \
    src/HTMLParser.cpp \
    src/URI.cpp \
    src/TextColor.cpp

HEADERS += \
    src/Adler32Generator.h \
    src/DownloaderFile.h \
    src/DownloaderParallel.h \
    src/DownloaderString.h \
    src/Gumbo.hpp \
    src/HTMLParser.h \
    src/ICurlEasyDownloader.h \
    src/URI.h \
    src/TextColorCode.h \
    src/TextColor.h
