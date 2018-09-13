#include "editorwindow.h"
#include "VoiceBankUtils/voicebankmanagerwindow.h"
#include <QApplication>
#include <QTranslator>
#include <../LeafPublicQtClasses/leaflogger.h>
#include <QLibraryInfo>
#define VOICEBANK_MANAGER_ONLY
#define NO_EDITOR

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Leaf UTAU Qt Developer Team");
    QCoreApplication::setOrganizationDomain("shine5402.top");
    QCoreApplication::setApplicationName("Leaf UTAU Qt");
    LeafLogger::LogInit();
    QTranslator translatorsys;
    translatorsys.load(":/translations/qt_zh_CN.qm");
    a.installTranslator(&translatorsys);
    QTranslator qtTranslator;
#ifndef NO_EDITOR
    EditorWindow w;
    w.show();
#endif
//TODO: Log看起来不能正常保存
#ifdef VOICEBANK_MANAGER_ONLY
    VoiceBankManagerWindow v;
    v.show();
#endif
    return a.exec();
}
