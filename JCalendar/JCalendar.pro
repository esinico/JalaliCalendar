#-------------------------------------------------
#
# Project created by QtCreator 2014-09-25T13:08:46
#
#-------------------------------------------------

QT       += widgets

TARGET = jcalendar
TEMPLATE = lib
CONFIG += staticlib

SOURCES += JCalendar.cpp \
    JCalendarButton.cpp

HEADERS += JCalendar.h \
    JCalendarButton.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    JCalendar.ui

CONFIG(release, debug|release): DESTDIR = release
else: DESTDIR = debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
