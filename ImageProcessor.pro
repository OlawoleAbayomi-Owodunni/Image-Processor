QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += "C:/Dev/vcpkg/installed/x64-windows/include"
INCLUDEPATH += "C:/Dev/vcpkg/installed/x64-windows/share/halide/tools"
LIBS += -L"C:/Dev/vcpkg/installed/x64-windows/bin" -lHalide
LIBS += -L"C:/Dev/vcpkg/installed/x64-windows/bin" -llibpng16
LIBS += -L"C:/Dev/vcpkg/installed/x64-windows/bin" -ljpeg

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    halideFunctions.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
