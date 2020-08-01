QT += core gui sql 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += src/wordinserter.cpp \
           src/main.cpp \
           src/wordsdialog.cpp \
           src/db_wrapper.cpp

FORMS += \
    forms/wordinserter.ui \
    forms/wordsdialog.ui

HEADERS += include/wordinserter.hpp \
    include/wordsdialog.hpp \
    include/db_wrapper.hpp

TRANSLATIONS += lang/wordinserter_pl.ts
