QT += widgets

TARGET = calculator2
CONFIG += console
CONFIG -= app_bundle

HEADERS += \
    CalculatorEngine.h \
    CalculatorWindow.h \
    MatrixDialog.h \
    QuadraticDialog.h \
    SimultaneousDialog.h \
    CRTDialog.h \
    NthRootDialog.h

SOURCES += \
    CalculatorEngine.cpp \
    CalculatorWindow.cpp \
    main_qt.cpp \
    MatrixDialog.cpp \
    QuadraticDialog.cpp \
    SimultaneousDialog.cpp \
    CRTDialog.cpp \
    NthRootDialog.cpp

# Optionally, specify C++ standard
QMAKE_CXXFLAGS += -std=c++17