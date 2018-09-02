#include "editorwindow.h"
#include "VoiceBankUtils/voicebankmanagerwindow.h"
#include <QApplication>
#include <../LeafPublicQtClasses/leaflogger.h>
#define DEBUG_TEST

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Leaf UTAU Qt Developer Team");
    QCoreApplication::setOrganizationDomain("shine5402.top");
    QCoreApplication::setApplicationName("Leaf UTAU Qt");
    LeafLogger::LogInit();

#ifndef DEBUG_TEST
    EditorWindow w;
    w.show();
#endif

#ifdef DEBUG_TEST
    VoiceBankManagerWindow v;
    v.show();
#endif
    return a.exec();
}
