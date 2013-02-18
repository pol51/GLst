TEMPLATE = app
TARGET = GLst
DEPENDPATH += src \
    .
INCLUDEPATH += src \
    .
HEADERS += src/winBook.h \
    src/winFilm.h \
    src/widgetListe.h \
    src/winListe.h \
    src/winListeMenu.h \
    src/winOptions.h \
    src/winZik.h \
    src/gestion/Acces.h \
    src/gestion/Acces_HTML.h \
    src/gestion/Book.h \
    src/gestion/Collection.h \
    src/gestion/Film.h \
    src/gestion/Media.h \
    src/gestion/Options.h \
    src/gestion/Utils.h \
    src/gestion/Zik.h
FORMS += ui/Book.ui \
    ui/Film.ui \
    ui/Liste.ui \
    ui/Options.ui \
    ui/Zik.ui
SOURCES += src/main.cpp \
    src/winBook.cpp \
    src/winFilm.cpp \
    src/widgetListe.cpp \
    src/winListe.cpp \
    src/winListeMenu.cpp \
    src/winOptions.cpp \
    src/winZik.cpp \
    src/gestion/Acces.cpp \
    src/gestion/Acces_HTML.cpp \
    src/gestion/Book.cpp \
    src/gestion/Collection.cpp \
    src/gestion/Film.cpp \
    src/gestion/Media.cpp \
    src/gestion/Options.cpp \
    src/gestion/Utils.cpp \
    src/gestion/Zik.cpp
CONFIG += warn_on  qt
RESOURCES += res/res.qrc
DESTDIR = bin
MOC_DIR = build/moc
UI_DIR = build/uic
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
RC_FILE += GLst.rc
CONFIG += c++11
QT += core \
    gui \
    widgets \
    xml
