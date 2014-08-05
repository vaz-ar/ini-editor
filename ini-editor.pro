#-------------------------------------------------
#
#                   Ini Editor
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ini-editor
TEMPLATE = app

CONFIG += c++11

SOURCES +=  main.cpp \
            dialog.cpp

HEADERS  += dialog.h

OBJECTS_DIR = obj
MOC_DIR = obj
RCC_DIR = obj
UI_DIR = obj
