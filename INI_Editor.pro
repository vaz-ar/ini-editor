#-------------------------------------------------
#
#                   INI Editor
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = INI_Editor
TEMPLATE = app

CONFIG += c++11

SOURCES +=  \
            INI_Editor.cpp \
    main_INI_Editor.cpp

HEADERS  += INI_Editor.h

OBJECTS_DIR =   obj
MOC_DIR =       obj
RCC_DIR =       obj
UI_DIR =        obj
