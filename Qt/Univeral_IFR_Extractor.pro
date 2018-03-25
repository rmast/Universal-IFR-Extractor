#-------------------------------------------------
#
# Project created by QtCreator 2018-03-24T20:24:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Univeral IFR Extractor"
TEMPLATE = app
ICON = icns/Univeral_IFR_Extractor.icns
QMAKE_CXXFLAGS += -std=c++11

DEFINES += UNIVERSAL_IFR_EXTRACTOR

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        filemanager.cpp \
        moduleparser.cpp \
        ../OldWay/EFI.cpp \
        ../OldWay/UEFI.cpp

HEADERS += \
        mainwindow.h \
        filemanager.h \
        moduleparser.h \
        ../OldWay/EFI.h \
        ../OldWay/UEFI.h

FORMS += \
        mainwindow.ui
