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
QT += core \
    gui \
    svg \
    xml

symbian:TARGET.UID3 = 0xE6A388CF

unix {
    DATADIR = $$PREFIX/share
    PKGDATADIR = $$DATADIR/glst
    DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"
}

OTHER_FILES += \
    android/res/drawable-mdpi/icon.png \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl \
    android/AndroidManifest.xml
