#-------------------------------------------------
#
# Project created by QtCreator 2014-09-25T13:25:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JCalendarTest
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../JCalendar/release/ -ljcalendar
else: LIBS += -L$$OUT_PWD/../JCalendar/debug/ -ljcalendar

INCLUDEPATH += $$PWD/../JCalendar
DEPENDPATH += $$PWD/../JCalendar

CONFIG(release, debug|release): DESTDIR = release
else: DESTDIR = debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
