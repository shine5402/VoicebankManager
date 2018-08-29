#include "editorwindow.h"
#include "VoiceBankUtils/voicebankmanagerwindow.h"
#include <QApplication>
#define DEBUG_TEST

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
