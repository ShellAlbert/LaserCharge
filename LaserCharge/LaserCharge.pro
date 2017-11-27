#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T10:09:55
#
#-------------------------------------------------

QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaserCharge
TEMPLATE = app

RC_ICONS = LaserCharge.ico

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
        mainui.cpp \
    resmanager.cpp \
    ztoolbar.cpp \
    zstatusbar.cpp \
    zpropertyeditor.cpp \
    zdialog.cpp \
    zprovincedata.cpp \
    zcinemadata.cpp \
    zcustomwidget.cpp \
    zcitydata.cpp \
    zrsamanager.cpp

HEADERS += \
        mainui.h \
    resmanager.h \
    sql.h \
    ztoolbar.h \
    zstatusbar.h \
    zpropertyeditor.h \
    zdialog.h \
    zprovincedata.h \
    zcinemadata.h \
    zcustomwidget.h \
    zcitydata.h \
    zrsamanager.h

RESOURCES += \
    imgrc.qrc

DISTFILES += \
    skins/lightYellow.qss

LIBS += -LC:/OpenSSL-Win32/lib/MinGW -llibeay32
LIBS += -LC:/OpenSSL-Win32/lib/MinGW -lssleay32


INCLUDEPATH += $$quote(C:/OpenSSL-Win32/include)
