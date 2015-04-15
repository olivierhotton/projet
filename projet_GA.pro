TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Geojson.cpp \
    Gpx.cpp \
    Arete.cpp \
    Graphe.cpp \
    Lieu.cpp \
    Noeud.cpp \
    Portion.cpp \
    Algorithme.cpp \
    Manipulateur.cpp \
    chemin.cpp \
    Parcours.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Gpx.h \
    Geojson.h \
    Arete.h \
    Graphe.h \
    Interface_Quantifiable.h \
    Lieu.h \
    Manipulateur.h \
    Noeud.h \
    Portion.h \
    Algorithme.h \
    chemin.h \
    Parcours.h

OTHER_FILES +=

