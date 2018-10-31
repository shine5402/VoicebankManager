#-------------------------------------------------
#
# Project created by QtCreator 2018-08-24T14:58:05
#
#-------------------------------------------------

QT       += core gui widgets

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
    VoiceBankUtils/voicebankreadmeinformationdialog.cpp \
    VoiceBankUtils/voicebank.cpp \
    VoiceBankUtils/voicebankhandler.cpp \
    VoiceBankUtils/monitorfolderssettingdialog.cpp \
    VoiceBankUtils/monitorfoldersadddialog.cpp \
    VoiceBankUtils/textcodecsettingdialog.cpp \
    ../LeafPublicQtClasses/leaflogger.cpp \
    TextCodecUtils/availabletextcodecdialog.cpp \
    TextCodecUtils/textcodecconvertdialog.cpp \
    VoiceBankUtils/voicebanktablemodel.cpp \
    EngineUtils/moresamplerconfigreader.cpp \
    EngineUtils/moresamplerconfig.cpp \
    EngineUtils/moresamplerconfigsmodel.cpp \
    EngineUtils/moresamplerconfigsdialog.cpp \
    EngineUtils/moresamplerconfigsdelegate.cpp \
    EngineUtils/moresamplerconfigaddnewdialog.cpp \
    EngineUtils/moresamplerconfigsaddnewmodel.cpp \
    ../ImageCropper/src/imagecropper.cpp \
    VoiceBankUtils/voicebankiconcropdialog.cpp \
    ../ImageCropper/src/imagecroppercontainer.cpp

HEADERS += \
        editorwindow.h \
    VoiceBankUtils/voicebankmanagerwindow.h \
    VoiceBankUtils/voicebankreadmeinformationdialog.h \
    VoiceBankUtils/voicebank.h \
    VoiceBankUtils/voicebankhandler.h \
    VoiceBankUtils/monitorfolderssettingdialog.h \
    VoiceBankUtils/monitorfoldersadddialog.h \
    VoiceBankUtils/textcodecsettingdialog.h \
    ../LeafPublicQtClasses/leaflogger.h \
    TextCodecUtils/availabletextcodecdialog.h \
    TextCodecUtils/textcodecconvertdialog.h \
    public_defines.h \
    VoiceBankUtils/voicebanktablemodel.h \
    EngineUtils/moresamplerconfigreader.h \
    EngineUtils/moresamplerconfig.h \
    EngineUtils/moresamplerconfigsmodel.h \
    EngineUtils/moresamplerconfigsdialog.h \
    EngineUtils/moresamplerconfigsdelegate.h \
    EngineUtils/moresamplerconfigaddnewdialog.h \
    EngineUtils/moresamplerconfigsaddnewmodel.h \
    ../ImageCropper/src/imagecropper.h \
    ../ImageCropper/src/imagecropper_e.h \
    ../ImageCropper/src/imagecropper_p.h \
    VoiceBankUtils/voicebankiconcropdialog.h \
    ../ImageCropper/src/imagecroppercontainer.h

FORMS += \
        editorwindow.ui \
    VoiceBankUtils/voicebankmanagerwindow.ui \
    VoiceBankUtils/voicebankreadmeinformationdialog.ui \
    VoiceBankUtils/monitorfolderssettingdialog.ui \
    VoiceBankUtils/monitorfoldersadddialog.ui \
    VoiceBankUtils/textcodecsettingdialog.ui \
    TextCodecUtils/availabletextcodecdialog.ui \
    TextCodecUtils/textcodecconvertdialog.ui \
    EngineUtils/moresamplerconfigsdialog.ui \
    EngineUtils/moresamplerconfigaddnewdialog.ui \
    VoiceBankUtils/voicebankiconcropdialog.ui \
    ../ImageCropper/src/imagecroppercontainer.ui
win32-msvc{
QMAKE_CXXFLAGS += /std:c++17
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
