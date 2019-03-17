TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    shape.cpp \
    triangle.cpp \
    main.cpp \
    righttriangle.cpp \
    ellipse.cpp

HEADERS += \
    shape.h \
    triangle.h \
    righttriangle.h \
    ellipse.h
