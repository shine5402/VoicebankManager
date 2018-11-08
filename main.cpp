#include "editorwindow.h"
#include "VoiceBankUtils/voicebankmanagerwindow.h"
#include <QApplication>
#include <QTranslator>
#include <../LeafPublicQtClasses/leaflogger.h>
#include <QLibraryInfo>
#include <QTextCodec>
#define VOICEBANK_MANAGER_ONLY
#define NO_EDITOR
#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Leaf UTAU Qt Developer Team");
    QCoreApplication::setOrganizationDomain("shine5402.top");
    QCoreApplication::setApplicationName("Leaf UTAU Qt");
    LeafLogger::LogInit();
    QTranslator translator;
    auto success = translator.load(QLocale(),"LeafOpenUTAUQt",".","./translations",".qm");
    LeafLogger::LogMessage(QString("QLocale detected:%1").arg(QLocale::system().name()));
    if ((!success) && QLocale::system().name() != QLocale(QLocale::Chinese).name())
    {
        translator.load("./translations/LeafOpenUTAUQt_en.qm");
    }
        a.installTranslator(&translator);
#ifndef NO_EDITOR
    EditorWindow w;
    w.show();
#endif
#ifdef VOICEBANK_MANAGER_ONLY
    VoiceBankManagerWindow v;
    v.show();
    v.loadVoiceBanksList();
#endif
    return a.exec();
}
