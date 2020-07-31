QT += core gui sql 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += wordinserter.cpp \
           main.cpp \
           wordsdialog.cpp \
           db_wrapper.cpp

FORMS += \
    wordinserter.ui \
    wordsdialog.ui

HEADERS += wordinserter.hpp \
    wordsdialog.hpp \
    db_wrapper.hpp

TRANSLATIONS += lang/wordinserter_pl.ts
