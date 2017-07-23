#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T10:39:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TEMS20
TEMPLATE = app


SOURCES += main.cpp\
        tems.cpp \
    aperture.cpp \
    editpic.cpp \
    opticalscreen.cpp \
    resultpic.cpp \
    SelectAndResult.cpp \
    myLabel.cpp \
    CameraOperate.cpp

HEADERS  += tems.h \
    aperture.h \
    editpic.h \
    opticalscreen.h \
    resultpic.h \
    SelectAndResult.h \
    myLabel.h \
    CameraOperate.h

INCLUDEPATH += E:\software\opencv\opencv_QT\include\opencv2\
    E:\software\opencv\opencv_QT\include\opencv\
    E:\software\opencv\opencv_QT\include

LIBS += -L E:/software/opencv/opencv_QT/lib/libopencv_*310.dll.a

RC_FILE += \
    tems.rc

RESOURCES += \
    tems.qrc
