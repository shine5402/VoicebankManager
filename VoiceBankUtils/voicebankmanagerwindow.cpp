﻿#include "voicebankmanagerwindow.h"
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
    ui->voiceBanksTableWidget->setItemDelegate(new NoFocusDelegate());
    loadMonitorFoldersSettings();
    createVoiceBanksTableMenu();
    connect(voiceBankHandler,SIGNAL(aVoiceBankReadDone(VoiceBank*)),this,SLOT(voiceBankReadDoneSlot(VoiceBank*)));
    ui->voiceBankBriefInfomationWidget->setVisible(false);
    auto readmeTextBroswerPattle = ui->voicebankReadmeTextBrowser->palette();
    readmeTextBroswerPattle.setBrush(QPalette::Base,readmeTextBroswerPattle.window());
    ui->voicebankReadmeTextBrowser->setPalette(readmeTextBroswerPattle);
    //loadVoiceBanksList();
}

void VoiceBankManagerWindow::loadVoiceBanksList()
{
    ui->voiceBanksTableWidget->clearContents();
    ui->voiceBanksTableWidget->setRowCount(0);
    voiceBankHandler->clear();
    voiceBankByTableItemFinder.clear();
    voiceBankReadDoneCount = 0;
    ui->voiceBanksTableWidget->setEnabled(false);
    ui->voicebankCountLabel->setText(tr(u8"加载中"));
    ui->voiceBanksTableWidget->setSortingEnabled(false);
    readVoiceBanks();
    
}

VoiceBankManagerWindow::~VoiceBankManagerWindow()
{
    delete ui;
    saveMonitorFoldersSettings();
}
void VoiceBankManagerWindow::loadMonitorFoldersSettings(){
    QSettings settings;
    if (settings.contains(u8"MonitorFolders"))
    {
        auto value = settings.value(u8"MonitorFolders");
        monitorFolders = value.toStringList();
    }
}
void VoiceBankManagerWindow::saveMonitorFoldersSettings()
{
    QSettings settings;
    settings.setValue(u8"MonitorFolders",monitorFolders);
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
    newNameItem->setIcon(QPixmap::fromImage(voiceBank->getImage()));
    ui->voiceBanksTableWidget->setItem(ui->voiceBanksTableWidget->rowCount()-1,TableColumn::Name,newNameItem);
    voiceBankByTableItemFinder.insert(newNameItem,voiceBank);
    QTableWidgetItem *newPathItem = new QTableWidgetItem(voiceBank->getPath());
    ui->voiceBanksTableWidget->setItem(ui->voiceBanksTableWidget->rowCount()-1,TableColumn::Path,newPathItem);
    LeafLogger::LogMessage(QString(u8"设置后的路径Item项的内容为%1").arg(ui->voiceBanksTableWidget->item(ui->voiceBanksTableWidget->rowCount()-1,TableColumn::Path)->text()));
    voiceBankByTableItemFinder.insert(newPathItem,voiceBank);
}

void VoiceBankManagerWindow::setVoiceBankInfomation(VoiceBank *voiceBank)
{
    if (!ui->voiceBankBriefInfomationWidget->isVisible())
        ui->voiceBankBriefInfomationWidget->setVisible(true);
    ui->voicebankNameLabel->setText(voiceBank->getName());
    ui->voicebankImage->setPixmap(QPixmap::fromImage(voiceBank->getImage()));
    //ui->voicebankReadmeTextBrowser->setText();
    ui->voicebankReadmeTextBrowser->clear();
    auto errors = voiceBank->getErrorStates();
    if (!errors.isEmpty()){
        for (auto state : errors){
            ui->voicebankReadmeTextBrowser->append(state->getErrorHTMLString());
        }
    }
    ui->voicebankReadmeTextBrowser->append(QString(u8R"(<p><pre style="color:black">%1</pre></p>)").arg(voiceBank->getReadme()));
    ui->voicebankReadmeTextBrowser->moveCursor(QTextCursor::Start);
}
void VoiceBankManagerWindow::readVoiceBanks(){
    auto pathList = getFoldersInMonitorFolders();
    voiceBankPathsCount = pathList.count();
    LeafLogger::LogMessage(QString(u8"准备读取音源库。共有%1个文件夹待读取。").arg(pathList.count()));
    if (voiceBankPathsCount == 0)
        setUIAfterVoiceBanksReadDone();
    else{
        for (auto path : pathList){
            LeafLogger::LogMessage(QString(u8"添加%1到音源Handler。").arg(path));
            voiceBankHandler->addVoiceBank(path);
        }
    }
    
}
void VoiceBankManagerWindow::setUIAfterVoiceBanksReadDone()
{
    ui->voiceBanksTableWidget->setEnabled(true);
    if (voiceBankHandler->count() != 0){
        ui->voicebankCountLabel->setText(tr(u8"共 %1 个").arg(voiceBankHandler->count()));
        ui->voiceBanksTableWidget->setSortingEnabled(true);
        ui->voiceBanksTableWidget->sortItems(TableColumn::Name);}
    else
        ui->voicebankCountLabel->setText(tr(u8"没有音源。"));
    ui->voiceBankBriefInfomationWidget->setVisible(false);
    ui->voiceBanksTableWidget->repaint();
}

void VoiceBankManagerWindow::voiceBankReadDoneSlot(VoiceBank *voiceBank){
    addVoiceBankRowInTableWidget(voiceBank);
    if (++voiceBankReadDoneCount == voiceBankPathsCount){
        setUIAfterVoiceBanksReadDone();
    }
    //    else
    //    {
    //       ui->voicebankCountLabel->setText(tr(u8"已完成%1个/共%2个").arg(voiceBankReadDoneCount).arg(voiceBankPathsCount));
    //        ui->voicebankCountLabel->repaint();
    //    }
    LeafLogger::LogMessage(QString(u8"读取完成数为%1个，共需要读取%2个。").arg(voiceBankReadDoneCount).arg(voiceBankPathsCount));
}
#ifndef NDEBUG
void VoiceBankManagerWindow::debugFunction()
{
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
        voiceBank->readWavFileName();
        qDebug() << "Read Done.";
    }
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
    auto openPathAction = new QAction(tr(u8"打开音源文件夹"),this);
    connect(openPathAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankPathInExplorer()));
    openPathAction->setStatusTip(tr(u8"在资源管理器中打开该音源的文件夹。"));
    voiceBanksTableWidgetMenu->addAction(openPathAction);

    auto openCharacterAction = new QAction(tr(u8"打开character.txt"),this);
    connect(openCharacterAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankCharacterFileByOS()));
    openCharacterAction->setStatusTip(tr(u8"在系统关联的文本编辑器中打开该音源的character.txt。"));
    voiceBanksTableWidgetMenu->addAction(openCharacterAction);

    auto openReadmeAction = new QAction(tr(u8"打开readme.txt"),this);
    connect(openReadmeAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankReadmeFileByOS()));
    openReadmeAction->setStatusTip(tr(u8"在系统关联的文本编辑器中打开该音源的readme.txt。"));
    voiceBanksTableWidgetMenu->addAction(openReadmeAction);

    voiceBanksTableWidgetMenu->addSeparator();

    auto copyPathAction = new QAction(tr(u8"复制音源路径"),this);
    connect(copyPathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankPathtoClipboard()));
    copyPathAction->setStatusTip(tr(u8"复制该音源的文件夹路径到剪贴板。"));
    voiceBanksTableWidgetMenu->addAction(copyPathAction);

    auto copyCharacterPathAction = new QAction(tr(u8"复制character.txt的文件路径"),this);
    connect(copyCharacterPathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankCharacterFilePathtoClipboard()));
    copyPathAction->setStatusTip(tr(u8"复制该音源的character.txt的路径到剪贴板。"));
    voiceBanksTableWidgetMenu->addAction(copyCharacterPathAction);

    auto copyReadmePathAction = new QAction(tr(u8"复制readme.txt的文件路径"),this);
    connect(copyReadmePathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankReadmeFilePathtoClipboard()));
    copyReadmePathAction->setStatusTip(tr(u8"复制该音源的readme.txt路径到剪贴板。"));
    voiceBanksTableWidgetMenu->addAction(copyReadmePathAction);

    voiceBanksTableWidgetMenu->addSeparator();

    auto setCodecAction = new QAction(tr(u8"为该音源单独设置文本编码"),this);
    connect(setCodecAction,SIGNAL(triggered(bool)),this,SLOT(setCodecForVoiceBankActionSlot()));
    setCodecAction->setStatusTip(tr(u8"为该音源设置读取用文本编码。注意，这仅在本软件中有效。"));
    voiceBanksTableWidgetMenu->addAction(setCodecAction);

    auto convertCharacterCodecAction = new QAction(tr(u8"对character.txt进行编码转换"),this);
    connect(convertCharacterCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertCharacterCodecActionSlot()));
    convertCharacterCodecAction->setStatusTip(tr(u8"在文件编码转换器中转换该音源character.txt的编码。"));
    voiceBanksTableWidgetMenu->addAction(convertCharacterCodecAction);

    auto convertReadmeCodecAction = new QAction(tr(u8"对readme.txt进行编码转换"),this);
    connect(convertReadmeCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertReadmeCodecActionSlot()));
    convertReadmeCodecAction->setStatusTip(tr(u8"在文件编码转换器中转换该音源readme.txt的编码。"));
    voiceBanksTableWidgetMenu->addAction(convertReadmeCodecAction);

    auto convertWavFileNameCodecAction = new QAction(tr(u8"对WAV文件名进行编码转换"),this);
    connect(convertWavFileNameCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertWavFileNameCodecActionSlot()));
    convertWavFileNameCodecAction->setStatusTip(tr(u8"在文件编码转换器中转换该音源的WAV文件名的编码。"));
    voiceBanksTableWidgetMenu->addAction(convertWavFileNameCodecAction);

    voiceBanksTableWidgetMenu->addSeparator();

    auto reloadAction = new QAction(tr(u8"重载此音源"),this);
    connect(reloadAction,SIGNAL(triggered(bool)),this,SLOT(reloadVoiceBankActionSlot()));
    reloadAction->setStatusTip(tr(u8"重新从硬盘加载此音源。"));
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
void VoiceBankManagerWindow::convertCharacterCodecActionSlot(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
        auto path = voiceBank->getPath() + u8"character.txt";
        auto isDone = processFileTextCodecConvert(path,voiceBank->getCharacterTextCodec(),VoiceBank::getDefaultCharacterTextCodec());
        if (isDone.first)
        {
            voiceBank->setIsFollowDefault(false);
            voiceBank->setCharacterTextCodec(isDone.second);
            voiceBank->saveSettings();
            reloadVoiceBankActionSlot();
        }
    }
}
void VoiceBankManagerWindow::convertReadmeCodecActionSlot(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
        auto path = voiceBank->getPath() + u8"readme.txt";
        auto isDone = processFileTextCodecConvert(path,voiceBank->getReadmeTextCodec(),VoiceBank::getDefaultReadmeTextCodec());
        if (isDone.first)
        {
            voiceBank->setIsFollowDefault(false);
            voiceBank->setReadmeTextCodec(isDone.second);
            voiceBank->saveSettings();
            reloadVoiceBankActionSlot();
        }
    }
}
void VoiceBankManagerWindow::convertWavFileNameCodecActionSlot(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    voiceBank->readWavFileName();
    if (voiceBank){
        auto showString = voiceBank->getWavFileNameRaw().join("\n");
        auto dialog = new TextCodecConvertDialog(tr(u8"%1的WAV文件名").arg(voiceBank->getName()),showString,voiceBank->getWavFileNameTextCodec(),QTextCodec::codecForLocale(),true,this);
        auto dialogCode = dialog->exec();
        if (dialogCode == QDialog::Accepted){
            auto sourceCodec = dialog->getSourceCodec();
            auto targetCodec = dialog->getTargetCodec();
            QTextEncoder encoder(targetCodec);
            QTextDecoder decoder(sourceCodec);
            QTextDecoder decoderLocale(QTextCodec::codecForLocale());
            //auto wavFileNameReDecoded = voiceBank->getWavFileNameReDecoded();
            auto wavFilePath = voiceBank->getWavFilePath();
            auto it = wavFilePath.begin();
            QStringList unsucess;
            while (it != wavFilePath.end())
            {
                auto file = new QFile(*it);
                if (file->exists()) {
                    QFileInfo fileInfo(*it);
                    auto newName = decoderLocale.toUnicode(encoder.fromUnicode(decoder.toUnicode(fileInfo.fileName().toLocal8Bit())));
                    auto newPath = fileInfo.absolutePath() + u8"/" + newName;
                    if (newName != fileInfo.fileName())
                    {
                        if (!file->rename(newPath)) {
                            unsucess.append(tr(u8"%1（%2）").arg(file->fileName()).arg(file->errorString()));
                            LeafLogger::LogMessage(QString(u8"文件重命名时发生错误。QFile的错误信息为%1。").arg(file->errorString()));
                        }
                    }
                }
                file->deleteLater();
                ++it;
            }
            if (!unsucess.isEmpty()){
                QMessageBox::warning(this,tr(u8"转换中出了些问题"),tr(u8"<h3>程序在转换以下文件时出了些错误</h3><pre>%1</pre><p>这些文件应当都保持在原有的状态。您可以排查问题后重试。</p>").arg(unsucess.join(u8"\n")));
            }
            else
            {
                voiceBank->clearWavFileReadStage();
                voiceBank->setWavFileNameTextCodec(targetCodec);
                QMessageBox::information(this,tr(u8"转换成功完成"),tr(u8"音源%1的WAV文件名均已从%2转换至%3。").arg(voiceBank->getName()).arg(QString::fromUtf8(sourceCodec->name())).arg(QString::fromUtf8(targetCodec->name())));
            }
        }
        dialog->deleteLater();
    }
}
QPair<bool,QTextCodec*> VoiceBankManagerWindow::processFileTextCodecConvert(const QString& path,QTextCodec* sourceCodec,QTextCodec* targetCodec){
    bool isDone = false;
    QFile* file = new QFile(path);
    if (!file->exists()){
        delete file;
        QMessageBox::warning(this,tr(u8"文件不存在"),tr(u8"文件%1不存在").arg(path));
        return QPair<bool,QTextCodec*>(false,nullptr);}
    QByteArray rawData;
    if (file->open(QIODevice::ReadOnly | QIODevice::Text)){
        rawData = file->readAll();
        file->close();}
    auto dialog = new TextCodecConvertDialog(path,rawData,sourceCodec,targetCodec,false,this);
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted){
        auto infoDialogCode = QMessageBox::information(this,tr(u8"即将执行编码转换"),tr(u8R"(<h3>程序即将对%1执行编码转换（%2 -> %3）</h3>
                                                                                <p>在您单击确定后，程序将会把转换后的结果保存至%1。</p>
                                                                                <p>但是，程序有必要提醒您编码转换的<b>风险</b>：由于源编码和目标编码间的可能的映射不对等关系，这种转换可能<b>不可逆</b>，并且可能使您<b>丢失数据</b>！</p>
                                                                                <p>出于安全考虑，程序将保存一份源文件的备份副本（%1.bak），以便出现问题时您可以手动恢复。</p>
                                                                                <p>确定要执行转换吗？</p>)").arg(path).arg(QString::fromUtf8(dialog->getSourceCodec()->name())).arg(QString::fromUtf8(dialog->getTargetCodec()->name())),QMessageBox::Ok | QMessageBox::Cancel);
        if (infoDialogCode == QMessageBox::Ok){
            QFile bakFile(path + u8".bak");
            if (bakFile.exists())
                bakFile.remove();
            if (file->copy(path + u8".bak")){
                if (file->open(QIODevice::WriteOnly | QIODevice::Text)){
                    auto fileWriteCode = file->write(dialog->getEncodedTargetByteArray());
                    if (fileWriteCode == -1){
                        QMessageBox::critical(this,tr(u8"转换失败"),tr(u8R"(<h3>程序无法对%1进行写入</h3>
                                                                   <p>在写入时出现错误。Qt提供的错误描述为%2。</p>
                                                                   <p>文件应该没有被修改。</p>)").arg(path).arg(file->errorString()));
                    }
                    else
                    {
                        QMessageBox::information(this,tr(u8"转换成功"),tr(u8R"(<h3>文件编码转换完成</h3>
                                                                      <p>程序将自动修改该文件的读取用文本编码，之后将实施重载。</p>)"));
                        isDone = true;
                    }
                    file->close();
                }
            }
            else
            {
                QMessageBox::critical(this,tr(u8"无法备份%1").arg(path + u8".bak"),tr(u8R"(<h3>程序无法对%1进行备份</h3>
                                                                                  <p>在备份时出现错误。Qt提供的错误说明为：%2</p>
                                                                                  <p>你仍可以令程序继续转换，但是之前提到的<b>风险</b>仍然存在，且出现问题时您无法恢复。</p>
                                                                                  <p>确定要继续转换吗？</p>)").arg(path).arg(file->errorString()));
            }
        }
    }
    if (file->isOpen())
        file->close();
    delete file;
    dialog->deleteLater();
    return QPair<bool,QTextCodec*>(isDone,dialog->getTargetCodec());
}
void VoiceBankManagerWindow::reloadVoiceBankActionSlot(){
    auto voiceBank = voiceBankByTableItemFinder.value(ui->voiceBanksTableWidget->currentItem());
    if (voiceBank){
        voiceBank->readFromPathWithoutEmit();
        auto row = ui->voiceBanksTableWidget->currentRow();
        ui->voiceBanksTableWidget->item(row,TableColumn::Name)->setText(voiceBank->getName());
        ui->voiceBanksTableWidget->item(row,TableColumn::Name)->setIcon(QPixmap::fromImage(voiceBank->getImage()));
        ui->voiceBanksTableWidget->item(row,TableColumn::Path)->setText(voiceBank->getPath());
        setVoiceBankInfomation(voiceBank);
    }
}

void VoiceBankManagerWindow::on_actionMonitor_Folders_triggered()
{
    auto dialog = new MonitorFoldersSettingDialog(this);
    dialog->setMonitorFolders(monitorFolders);
    auto dialogCode = dialog->exec();
    if (dialogCode == 1 && monitorFolders != dialog->getMonitorFolders()){
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
    if (dialogCode == QDialog::Accepted){
        VoiceBank::setDefaultCharacterTextCodec(dialog->getCharacterTextCodec());
        VoiceBank::setDefaultReadmeTextCodec(dialog->getReadmeTextCodec());
        auto clickedButton = QMessageBox::information(this,u8"默认文本读取编码被更改",u8"您更改了默认的读取用文本编码，是否立即重载音源库列表？",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksList();
    }
    dialog->deleteLater();
}

void VoiceBankManagerWindow::on_searchLineEdit_textChanged(const QString &arg1)
{
    int rC = ui->voiceBanksTableWidget->rowCount();//获得行号
    if (arg1.isEmpty())//判断输入是否为空
    {
        for (int i = 0; i < rC; i++)
        {
            ui->voiceBanksTableWidget->setRowHidden(i, false);//显示所有行
        }
    }
    else
    {
        //获取符合条件的cell索引
        QList <QTableWidgetItem *> item = ui->voiceBanksTableWidget->findItems(arg1, Qt::MatchContains);
        for (int i = 0; i < rC; i++)
        {
            ui->voiceBanksTableWidget->setRowHidden(i, true);//隐藏所有行
        }
        if (!item.isEmpty())//不为空
        {
            for (int i = 0; i < item.count(); i++)
            {
                ui->voiceBanksTableWidget->setRowHidden(item.at(i)->row(),false);
            }
        }
    }
    qApp->processEvents();
}

void VoiceBankManagerWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void VoiceBankManagerWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,tr(u8"关于本程序"),tr(u8R"(<h3>音源管理器</h3><p>版本：%1 作者：shine_5402</p><p>本程序以 Apache 2.0 License 分发。</p><p>“音源管理器”是为UTAU程序所用音源设计的本地信息管理器。</p><p>本程序是 <a href="https://github.com/shine5402/LeafOpenUTAUQt">Leaf OpenUTAU Qt Project</a> 的一部分</p><p>UTAU是一款由饴屋/菖蒲（あめや・あやめ）氏开发的免费的歌声合成软件。</p>)").arg(voicebankManagerVersion));
}

void VoiceBankManagerWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,tr(u8"关于 Qt"));
}

void VoiceBankManagerWindow::on_actionSet_Thread_Pool_Max_Count_triggered()
{
    bool ok = false;
    auto count = QInputDialog::getInt(this,tr(u8"设定线程池的最大大小"),tr(u8"该设置改变程序读取音源库时的最大线程数。请确保您在知道自己在做什么之后再更改此项设置。"),voiceBankHandler->getThreadPoolMaxThreadCount(),1,2147483647,1,&ok);
    if (ok)
        voiceBankHandler->setThreadPoolMaxThreadCount(count);
}
