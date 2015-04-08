TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    gpx2son.cpp \
    Geojson.cpp \
    Gpx.cpp \
    lireGPX.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gpx2json.h \
    Gpx.h \
    Geojson.h \
    lireGPX.h

