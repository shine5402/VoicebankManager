#include "voicebankmanagerwindow.h"
#include "ui_voicebankmanagerwindow.h"

VoiceBankManagerWindow::VoiceBankManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VoiceBankManagerWindow)
{
    ui->setupUi(this);
#ifndef NDEBUG
   QAction* debugFunctionAction = new QAction(u8"执行Debug测试函数",this);
   ui->menubar->addAction(debugFunctionAction);
   connect(debugFunctionAction,SIGNAL(triggered(bool)),this,SLOT(debugFunction()));
#endif
}

VoiceBankManagerWindow::~VoiceBankManagerWindow()
{
    delete ui;
}

QStringList VoiceBankManagerWindow::getMonitorFolders() const
{
    return monitorFolders;
}

void VoiceBankManagerWindow::setMonitorFolders(const QStringList &value)
{
    monitorFolders = value;
}
#ifndef NDEBUG
void VoiceBankManagerWindow::debugFunction()
{
    auto voiceBank = voiceBankhandler->addVoiceBank(QString(u8R"(E:\UTAU\voice\Akatsuka Youichi_CVVCHN Act.2\)"));
    connect(voiceBank,SIGNAL(readDone(VoiceBank*)),this,SLOT(debug_voiceBank_readDone_Slot(VoiceBank*)));
}
void VoiceBankManagerWindow::debug_voiceBank_readDone_Slot(VoiceBank *voiceBank){
    qDebug() << voiceBank->getName() << voiceBank->getReadme();
    ui->voicebankNameLabel->setText(voiceBank->getName());
    ui->voicebankImage->setPixmap(voiceBank->getImage());
    ui->voicebankReadmeTextBrowser->setText(voiceBank->getReadme());

}
#endif
