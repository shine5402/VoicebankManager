#-------------------------------------------------
#
# Project created by QtCreator 2018-08-24T14:58:05
#
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = LeafOpenUTAUQt
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
    VoiceBankUtils/voicebank.cpp \
    VoiceBankUtils/voicebankhandler.cpp \
    VoiceBankUtils/textcodecsettingdialog.cpp \
    VoiceBankUtils/voicebanktablemodel.cpp \
    EngineUtils/moresamplerconfigreader.cpp \
    EngineUtils/moresamplerconfig.cpp \
    EngineUtils/moresamplerconfigsmodel.cpp \
    EngineUtils/moresamplerconfigsdialog.cpp \
    EngineUtils/moresamplerconfigsdelegate.cpp \
    EngineUtils/moresamplerconfigaddnewdialog.cpp \
    EngineUtils/moresamplerconfigsaddnewmodel.cpp \
    VoiceBankUtils/voicebankiconcropdialog.cpp \
    VoiceBankUtils/categoriesandlabelslistwidget.cpp \
    VoiceBankUtils/categoriesmodel.cpp \
    VoiceBankUtils/labelsmodel.cpp \
    VoiceBankUtils/folderssettingdialog.cpp \
    VoiceBankUtils/foldersadddialog.cpp \
    CommonUtils/showhtmldialog.cpp \
    VoiceBankUtils/monitorfoldersscanner.cpp \
    CommonUtils/messagelistwidget.cpp \
    CommonUtils/messagewidget.cpp

HEADERS += \
        editorwindow.h \
    VoiceBankUtils/voicebankmanagerwindow.h \
    VoiceBankUtils/voicebank.h \
    VoiceBankUtils/voicebankhandler.h \
    VoiceBankUtils/textcodecsettingdialog.h \
    public_defines.h \
    VoiceBankUtils/voicebanktablemodel.h \
    EngineUtils/moresamplerconfigreader.h \
    EngineUtils/moresamplerconfig.h \
    EngineUtils/moresamplerconfigsmodel.h \
    EngineUtils/moresamplerconfigsdialog.h \
    EngineUtils/moresamplerconfigsdelegate.h \
    EngineUtils/moresamplerconfigaddnewdialog.h \
    EngineUtils/moresamplerconfigsaddnewmodel.h \
    VoiceBankUtils/voicebankiconcropdialog.h \
    VoiceBankUtils/categoriesandlabelslistwidget.h \
    VoiceBankUtils/categoriesmodel.h \
    VoiceBankUtils/labelsmodel.h \
    VoiceBankUtils/folderssettingdialog.h \
    VoiceBankUtils/foldersadddialog.h \
    CommonUtils/showhtmldialog.h \
    VoiceBankUtils/monitorfoldersscanner.h \
    CommonUtils/messagelistwidget.h \
    CommonUtils/messagewidget.h

FORMS += \
        editorwindow.ui \
    VoiceBankUtils/voicebankmanagerwindow.ui \
    VoiceBankUtils/textcodecsettingdialog.ui \
    EngineUtils/moresamplerconfigsdialog.ui \
    EngineUtils/moresamplerconfigaddnewdialog.ui \
    VoiceBankUtils/voicebankiconcropdialog.ui \
    ../ImageCropper/src/imagecroppercontainer.ui \
    VoiceBankUtils/categoriesandlabelslistwidget.ui \
    VoiceBankUtils/folderssettingdialog.ui \
    VoiceBankUtils/foldersadddialog.ui \
    CommonUtils/showhtmldialog.ui \
    CommonUtils/messagelistwidget.ui \
    CommonUtils/messagewidget.ui
win32-msvc{
QMAKE_CXXFLAGS += /std:c++17
}
win32-g++{
QMAKE_CXXFLAGS += -std=c++1z
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
TRANSLATIONS = LeafOpenUTAUQt_en.ts
!exists($$PWD/outsideLibrarys.pri){
    error("outsideLibrarys.pri not exist, please write one. The outsideLibrarys.template.pri could help.")
}
DISTFILES += \
    outsideLibrarys.pri \
    module.pri
include(outsideLibrarys.pri)
include(module.pri)
