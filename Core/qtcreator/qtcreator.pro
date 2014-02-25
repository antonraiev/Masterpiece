#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T22:35:20
#
#-------------------------------------------------

QT       -= gui

TARGET = Core
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../include

SOURCES += \
    ../src/Actuator.cpp \
    ../src/ActuatorCircle.cpp \
    ../src/ActuatorCooperation.cpp \
    ../src/EffectorMemory.cpp \
    ../src/FuzzyOperations.cpp \
    ../src/Granule.cpp \
    ../src/Sensor.cpp \
    ../src/SensorMemory.cpp

HEADERS += \
    ../include/Actuator.h \
    ../include/ActuatorCircle.h \
    ../include/ActuatorCooperation.h \
    ../include/EffectorMemory.h \
    ../include/EffectorMemoryImpl.h \
    ../include/FuzzyOperations.h \
    ../include/Granule.h \
    ../include/IControlMediator.h \
    ../include/Sensor.h \
    ../include/SensorMemory.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += -std=c++11
