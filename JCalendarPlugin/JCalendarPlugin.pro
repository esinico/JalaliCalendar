CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(JalaliCalendarPlugin)
TEMPLATE    = lib

HEADERS     = jcalendarplugin.h jcalendarbuttonplugin.h JalaliCalendar.h
SOURCES     = jcalendarplugin.cpp jcalendarbuttonplugin.cpp JalaliCalendar.cpp
RESOURCES   = icons.qrc
LIBS        += -L. -ljcalendar

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target


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
