#-------------------------------------------------
#
# Project created by QtCreator 2019-07-08T16:21:19
#
#-------------------------------------------------

QT       += widgets

TARGET = BlokInterfaces
TEMPLATE = lib

DEFINES += BLOKINTERFACES_LIBRARY

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
        ibackground.cpp \
        iblock.cpp \
        iblockbuilder.cpp \
        icore.cpp \
        iground.cpp \
        iplugin.cpp \
        iplugincontroller.cpp \
        isimulator.cpp \
        iskinfactory.cpp \
        iuicontroller.cpp

HEADERS += \
        ibackground.h \
        iblock.h \
        iblockbuilder.h \
        icore.h \
        blokinterfaces_global.h  \
        iground.h \
        iplugin.h \
        iplugincontroller.h \
        isimulator.h \
        iskinfactory.h \
        iuicontroller.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
