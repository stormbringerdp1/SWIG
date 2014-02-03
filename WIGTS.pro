#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T14:01:01
#
#-------------------------------------------------

CONFIG += static

QT       += core gui

QT += opengl
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WIGTS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MSyntaxHighlighterParamsTest.cpp \
    MReadiness.cpp \
    MTelemetry.cpp \
    funcs.cpp \
    MTelemetryTabChannel.cpp \
    MPlot.cpp \
    MEkranoplan.cpp \
    MGyrohorizon.cpp \
    MEkranoplanGL.cpp \
    MReadinessTestChannel.cpp \
    MArduino.cpp \
    MTelemetryTabWidgetStates.cpp \
    MTelemetryTabBarStates.cpp \
    MTelemetryTabReport.cpp \
    MLabelCloseTab.cpp \
    MTelemetryTabBarChannels.cpp \
    MTelemetryTabWidgetChannels.cpp

HEADERS  += mainwindow.h \
    MSyntaxHighlighterParamsTest.h \
    MReadiness.h \
    MTelemetry.h \
    funcs.h \
    MTelemetryTabChannel.h \
    MPlot.h \
    MEkranoplan.h \
    MGyrohorizon.h \
    MEkranoplanGL.h \
    MReadinessTestChannel.h \
    MArduino.h \
    MTelemetryTabWidgetStates.h \
    MTelemetryTabBarStates.h \
    MTelemetryTabReport.h \
    MLabelCloseTab.h \
    MTelemetryTabBarChannels.h \
    MTelemetryTabWidgetChannels.h \
    constants.h

RESOURCES += \
    Shaders.qrc \
    Texture.qrc \
    3dsMax_Ekranoplan.qrc \
    Pictures.qrc

FORMS    += mainwindow.ui

OTHER_FILES +=
