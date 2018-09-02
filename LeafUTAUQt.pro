#-------------------------------------------------
#
# Project created by QtCreator 2018-08-24T14:58:05
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = LeafUTAUQt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
        editorwindow.cpp \
    VoiceBankUtils/voicebankmanagerwindow.cpp \
    VoiceBankUtils/voicebankreadmeinformationdialog.cpp \
    VoiceBankUtils/voicebank.cpp \
    VoiceBankUtils/voicebankhandler.cpp \
    GUIUtils/nofocusdelegate.cpp \
    VoiceBankUtils/monitorfolderssettingdialog.cpp \
    VoiceBankUtils/monitorfoldersadddialog.cpp \
    VoiceBankUtils/textcodecsettingdialog.cpp \
    VoiceBankUtils/availabletextcodecdialog.cpp \
    ../LeafPublicQtClasses/leaflogger.cpp

HEADERS += \
        editorwindow.h \
    VoiceBankUtils/voicebankmanagerwindow.h \
    VoiceBankUtils/voicebankreadmeinformationdialog.h \
    VoiceBankUtils/voicebank.h \
    VoiceBankUtils/voicebankhandler.h \
    GUIUtils/nofocusdelegate.h \
    VoiceBankUtils/monitorfolderssettingdialog.h \
    VoiceBankUtils/monitorfoldersadddialog.h \
    VoiceBankUtils/textcodecsettingdialog.h \
    VoiceBankUtils/availabletextcodecdialog.h \
    ../LeafPublicQtClasses/leaflogger.h

FORMS += \
        editorwindow.ui \
    VoiceBankUtils/voicebankmanagerwindow.ui \
    VoiceBankUtils/voicebankreadmeinformationdialog.ui \
    VoiceBankUtils/monitorfolderssettingdialog.ui \
    VoiceBankUtils/monitorfoldersadddialog.ui \
    VoiceBankUtils/textcodecsettingdialog.ui \
    VoiceBankUtils/availabletextcodecdialog.ui
win32-msvc{
QMAKE_CXXFLAGS += /std:c++17
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
