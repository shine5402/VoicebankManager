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
    monitorFolders.append(u8R"(E:\UTAU\voice)");
#endif
    ui->voiceBanksTableWidget->setItemDelegate(new NoFocusDelegate());
    loadVoiceBanksList();
    createVoiceBanksTableMenu();
    connect(voiceBankHandler,SIGNAL(aVoiceBankReadDone(VoiceBank*)),this,SLOT(voiceBankReadDoneSlot(VoiceBank*)));
    ui->voiceBankBriefInfomationWidget->setVisible(false);
}

void VoiceBankManagerWindow::loadVoiceBanksList()
{
    ui->voiceBanksTableWidget->clearContents();
    ui->voiceBanksTableWidget->setRowCount(0);
    voiceBankHandler->clear();
    voiceBankByTableItemFinder.clear();
    voiceBankReadDoneCount = 0;
    ui->voiceBanksTableWidget->setEnabled(false);
    ui->voicebankCountLabel->setText(tr(u8"加载中……"));
    readVoiceBanks();

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
QStringList VoiceBankManagerWindow::getFoldersInMonitorFolders() const{
    QStringList folderList{};
    for (auto monitorFolder : monitorFolders){
        QDir monitorDir(monitorFolder);
        auto entrys = monitorDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (auto path : entrys){
            folderList.append(monitorDir.absolutePath() + u8"/" + path);
        }
    }
    return folderList;
}
void VoiceBankManagerWindow::addVoiceBankRowInTableWidget(VoiceBank *voiceBank)
{
    ui->voiceBanksTableWidget->insertRow(ui->voiceBanksTableWidget->rowCount());
    QTableWidgetItem *newNameItem = new QTableWidgetItem(voiceBank->getName());
    newNameItem->setIcon(voiceBank->getPixmap());
    ui->voiceBanksTableWidget->setItem(ui->voiceBanksTableWidget->rowCount()-1,TableColumn::Name,newNameItem);
    voiceBankByTableItemFinder.insert(newNameItem,voiceBank);
    QTableWidgetItem *newPathItem = new QTableWidgetItem(voiceBank->getPath());
    ui->voiceBanksTableWidget->setItem(ui->voiceBanksTableWidget->rowCount()-1,TableColumn::Path,newPathItem);
    voiceBankByTableItemFinder.insert(newPathItem,voiceBank);
}

void VoiceBankManagerWindow::setVoiceBankInfomation(VoiceBank *voiceBank)
{
    if (!ui->voiceBankBriefInfomationWidget->isVisible())
        ui->voiceBankBriefInfomationWidget->setVisible(true);
    ui->voicebankNameLabel->setText(voiceBank->getName());
    ui->voicebankImage->setPixmap(voiceBank->getPixmap());
    //ui->voicebankReadmeTextBrowser->setText();
    ui->voicebankReadmeTextBrowser->clear();
    if (!voiceBank->getErrors().isEmpty()){
        auto errors = voiceBank->getErrors();
        auto errors_it = errors.begin();
        while (errors_it != errors.end()){
            switch (errors_it.key()){
            case VoiceBank::ProbablyErrors::CharacterFileNotExists:
                if (errors_it.value())
                    ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：没有为此音源库找到character.txt。在音源使用过程中将无法查看音源名称、图像等信息。</p>)"));
                break;
            case VoiceBank::ProbablyErrors::NameNotSet:
                if (errors_it.value())
                    ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：character.txt中的name字段没有被设定。在音源使用过程中音源区域将显示文件夹名称。</p>)"));
                break;
            case VoiceBank::ProbablyErrors::ImageFileNotSet:
                if (errors_it.value())
                    ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：character.txt中的image字段没有被设定。在音源使用过程中音源区域将不显示图片。</p>)"));
                break;
            case VoiceBank::ProbablyErrors::ImageFileNotExists:
                if (errors_it.value())
                    ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：找不到character.txt中设定的图片文件（%1）。在音源使用过程中将音源区域将不显示图片。</p>)").arg(voiceBank->getPixmapPath()));
                break;
            case VoiceBank::ProbablyErrors::ImageFileNotFit:
                if (errors_it.value())
                    ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：character.txt中设定的图片文件（%1*%2）不符合UTAU的图标要求（100*100）。在音源使用过程中将音源区域图片可能显示不正确，或者无法显示。</p>)").arg(voiceBank->getPixmap().width()).arg(voiceBank->getPixmap().height()));
                break;
            case VoiceBank::ProbablyErrors::ReadmeFileNotExists:
                if (errors_it.value())
                    ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：找不到readme.txt。音源的README将无法显示。</p>)"));
                break;
            }
            ++errors_it;
        }
    }
    ui->voicebankReadmeTextBrowser->append(QString(u8R"(<p><pre style="color:black">%1</pre></p>)").arg(voiceBank->getReadme()));
    ui->voicebankReadmeTextBrowser->moveCursor(QTextCursor::Start);
}
void VoiceBankManagerWindow::readVoiceBanks(){
    auto pathList = getFoldersInMonitorFolders();
    voiceBankPathsCount = pathList.count();
    for (auto path : pathList){
        voiceBankHandler->addVoiceBank(path);
    }

}
void VoiceBankManagerWindow::voiceBankReadDoneSlot(VoiceBank *voiceBank){
    addVoiceBankRowInTableWidget(voiceBank);
    if (++voiceBankReadDoneCount == voiceBankPathsCount){
        ui->voiceBanksTableWidget->setEnabled(true);
        ui->voicebankCountLabel->setText(tr(u8"共 %1 个").arg(voiceBankHandler->count()));
        ui->voiceBankBriefInfomationWidget->setVisible(false);
    }
}
#ifndef NDEBUG
void VoiceBankManagerWindow::debugFunction()
{
    qDebug() << "debug";
}

void VoiceBankManagerWindow::debug_voiceBank_readDone_Slot(VoiceBank *voiceBank){

}
#endif

void VoiceBankManagerWindow::on_voiceBanksTableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *)
{
    auto voiceBank = voiceBankByTableItemFinder.value(current);
    if (voiceBank)
        setVoiceBankInfomation(voiceBank);
}

void VoiceBankManagerWindow::on_voiceBanksTableWidget_customContextMenuRequested(const QPoint &)
{
    voiceBanksTableWidgetMenu->exec(QCursor::pos());
}
void VoiceBankManagerWindow::createVoiceBanksTableMenu()
{
    auto openPathAction = new QAction(tr(u8"打开音源文件夹"),voiceBanksTableWidgetMenu);
    connect(openPathAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankPathInExplorer()));
    voiceBanksTableWidgetMenu->addAction(openPathAction);
    auto openCharacterAction = new QAction(tr(u8"打开character.txt"),voiceBanksTableWidgetMenu);
    connect(openCharacterAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankCharacterFileByOS()));
    voiceBanksTableWidgetMenu->addAction(openCharacterAction);
    auto openReadmeAction = new QAction(tr(u8"打开readme.txt"),voiceBanksTableWidgetMenu);
    connect(openReadmeAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankReadmeFileByOS()));
    voiceBanksTableWidgetMenu->addAction(openReadmeAction);
    voiceBanksTableWidgetMenu->addSeparator();
    auto copyPathAction = new QAction(tr(u8"复制音源路径"),voiceBanksTableWidgetMenu);
    connect(copyPathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankPathtoClipboard()));
    voiceBanksTableWidgetMenu->addAction(copyPathAction);
    auto copyCharacterPathAction = new QAction(tr(u8"复制character.txt的文件路径"),voiceBanksTableWidgetMenu);
    connect(copyCharacterPathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankCharacterFilePathtoClipboard()));
    voiceBanksTableWidgetMenu->addAction(copyCharacterPathAction);
    auto copyReadmePathAction = new QAction(tr(u8"复制readme.txt的文件路径"),voiceBanksTableWidgetMenu);
    connect(copyReadmePathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankReadmeFilePathtoClipboard()));
    voiceBanksTableWidgetMenu->addAction(copyReadmePathAction);
    voiceBanksTableWidgetMenu->addSeparator();
    auto setCodecAction = new QAction(tr(u8"为该音源单独设置文本编码"),voiceBanksTableWidgetMenu);
    connect(setCodecAction,SIGNAL(triggered(bool)),this,SLOT(setCodecForVoiceBankActionSlot()));
    voiceBanksTableWidgetMenu->addAction(setCodecAction);
    voiceBanksTableWidgetMenu->addSeparator();
    auto reloadAction = new QAction(tr(u8"重载此音源"),voiceBanksTableWidgetMenu);
    connect(reloadAction,SIGNAL(triggered(bool)),this,SLOT(reloadVoiceBankActionSlot()));
    voiceBanksTableWidgetMenu->addAction(reloadAction);
}
void VoiceBankManagerWindow::openVoiceBankPathInExplorer()
{
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
    auto url = QUrl(u8"file:" + voiceBank->getPath());
    QDesktopServices::openUrl(url);}

}
void VoiceBankManagerWindow::openVoiceBankCharacterFileByOS(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
    auto url = QUrl(u8"file:" + voiceBank->getPath() + u8"character.txt");
    QDesktopServices::openUrl(url);}
}
void VoiceBankManagerWindow::openVoiceBankReadmeFileByOS(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
    auto url = QUrl(u8"file:" + voiceBank->getPath() + u8"readme.txt");
    QDesktopServices::openUrl(url);
    }
}
void VoiceBankManagerWindow::copyVoiceBankPathtoClipboard()
{
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(QDir::toNativeSeparators(voiceBank->getPath()));}
}
void VoiceBankManagerWindow::copyVoiceBankCharacterFilePathtoClipboard(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(QDir::toNativeSeparators(voiceBank->getPath() + u8"character.txt"));}
}
void VoiceBankManagerWindow::copyVoiceBankReadmeFilePathtoClipboard(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(QDir::toNativeSeparators(voiceBank->getPath() + u8"readme.txt"));}
}
void VoiceBankManagerWindow::setCodecForVoiceBankActionSlot(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
        auto dialog = new TextCodecSettingDialog(this,voiceBank);
        auto dialogCode = dialog->exec();
        if (dialogCode == 1){
            voiceBank->setIsFollowDefault(dialog->getIsFollowDefaultCodec());
            voiceBank->setCharacterTextCodec(dialog->getCharacterTextCodec());
            voiceBank->setReadmeTextCodec(dialog->getReadmeTextCodec());
            voiceBank->saveSettings();
            reloadVoiceBankActionSlot();
        }
    }
}
void VoiceBankManagerWindow::reloadVoiceBankActionSlot(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
        voiceBank->readFromPathWithoutEmit();
        auto row = ui->voiceBanksTableWidget->currentRow();
        ui->voiceBanksTableWidget->item(row,TableColumn::Name)->setText(voiceBank->getName());
        ui->voiceBanksTableWidget->item(row,TableColumn::Name)->setIcon(voiceBank->getPixmap());
        ui->voiceBanksTableWidget->item(row,TableColumn::Path)->setText(voiceBank->getPath());
        setVoiceBankInfomation(voiceBank);
    }
}

void VoiceBankManagerWindow::on_actionMonitor_Folders_triggered()
{
    auto dialog = new MonitorFoldersSettingDialog(this);
    dialog->setMonitorFolders(monitorFolders);
    auto dialogCode = dialog->exec();
    if (dialogCode == 1 && monitorFolders == dialog->getMonitorFolders()){
        monitorFolders = dialog->getMonitorFolders();
        auto clickedButton = QMessageBox::information(this,u8"监视文件夹列表被更改",u8"您更改了监视文件夹列表，是否立即重载音源库列表？",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksList();
    }
    dialog->deleteLater();
}

void VoiceBankManagerWindow::on_actionRefresh_triggered()
{
    loadVoiceBanksList();
}

void VoiceBankManagerWindow::on_actionDefault_TextCodec_triggered()
{
    auto dialog = new TextCodecSettingDialog(this);
    auto dialogCode = dialog->exec();
    if (dialogCode == 1){
        VoiceBank::setDefaultCharacterTextCodec(dialog->getCharacterTextCodec());
        VoiceBank::setDefaultReadmeTextCodec(dialog->getReadmeTextCodec());
        auto clickedButton = QMessageBox::information(this,u8"默认文本读取编码被更改",u8"您更改了默认的读取用文本编码，是否立即重载音源库列表？",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksList();
    }
    dialog->deleteLater();
}
