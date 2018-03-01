QT += widgets

TARGET = Guibi
TEMPLATE = lib

DEFINES += \
    GUIBI_LIBRARY \
    QT_DEPRECATED_WARNINGS


SOURCES += \
    gbarretitre.cpp \
    gmessagebox.cpp

HEADERS += \
    guibi_global.h \
    gbarretitre.h \
    gmessagebox.h \
    guibi.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}

