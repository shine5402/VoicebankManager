#include "voicebankmanagerwindow.h"
#include "ui_voicebankmanagerwindow.h"
//TODO:重构 将Dialog完成后的代码迁移至继承的accept和reject。
VoiceBankManagerWindow::VoiceBankManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VoiceBankManagerWindow)
{
    ui->setupUi(this);
#ifndef NDEBUG
    QAction* debugFunctionAction = new QAction("执行Debug测试函数",this);
    ui->menubar->addAction(debugFunctionAction);
    connect(debugFunctionAction,SIGNAL(triggered(bool)),this,SLOT(debugFunction()));
#endif
    loadMonitorFoldersSettings();
    createVoiceBanksTableMenu();
    connect(voiceBankHandler,SIGNAL(aVoiceBankReadDone(VoiceBank*)),this,SLOT(voiceBankReadDoneSlot(VoiceBank*)));
    ui->voiceBankBriefInfomationWidget->setVisible(false);
    ui->voiceBankBriefInfomationWidget->setTitleBarWidget(new QWidget(this));
    auto readmeTextBroswerPattle = ui->voicebankReadmeTextBrowser->palette();
    readmeTextBroswerPattle.setBrush(QPalette::Base,readmeTextBroswerPattle.window());
    ui->voicebankReadmeTextBrowser->setPalette(readmeTextBroswerPattle);
    voiceBankTableModel = new VoiceBankTableModel(voiceBankHandler);
    ui->voiceBanksTableView->setModel(voiceBankTableModel);
    ui->voiceBanksTableView->horizontalHeader()->setSortIndicator(VoiceBankTableModel::TableColumns::Name,Qt::SortOrder::AscendingOrder);
    connect(ui->voiceBanksTableView->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),this,SLOT(onVoiceBankViewCurrentChanged(const QModelIndex &, const QModelIndex &)));
    connect(voiceBankHandler,SIGNAL(backupImageFileBecauseExists(VoiceBank*)),this,SLOT(onBackupImageFileBecauseExists(VoiceBank *)));
    connect(voiceBankHandler,SIGNAL(cannotBackupImageFile(VoiceBank*)),this,SLOT(onCannotBackupImageFile(VoiceBank*)));
}

void VoiceBankManagerWindow::loadVoiceBanksList()
{
    voiceBankHandler->clear();
    voiceBankTableModel->clearEmitter();
    voiceBankReadDoneCount = 0;
    ui->voiceBanksTableView->setEnabled(false);
    ui->voicebankCountLabel->setText(tr("加载中"));
    readVoiceBanks();
}

VoiceBankManagerWindow::~VoiceBankManagerWindow()
{
    delete ui;
    saveMonitorFoldersSettings();
}
void VoiceBankManagerWindow::loadMonitorFoldersSettings(){
    QSettings settings;
    if (settings.contains("MonitorFolders"))
    {
        auto value = settings.value("MonitorFolders");
        monitorFolders = value.toStringList();
    }
}
void VoiceBankManagerWindow::saveMonitorFoldersSettings()
{
    QSettings settings;
    settings.setValue("MonitorFolders",monitorFolders);
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
            folderList.append(monitorDir.absolutePath() + "/" + path);
        }
    }
    return folderList;
}

void VoiceBankManagerWindow::setVoiceBankInfomation(VoiceBank *voiceBank)
{
    if (!ui->voiceBankBriefInfomationWidget->isVisible())
        ui->voiceBankBriefInfomationWidget->setVisible(true);
    ui->voicebankNameLabel->setText(voiceBank->getName());
    ui->voicebankImage->setPixmap(QPixmap::fromImage(voiceBank->getImage().scaled(100,100)));
    ui->voicebankReadmeTextBrowser->clear();
    auto errors = voiceBank->getErrorStates();
    if (!errors.isEmpty()){
        for (auto state : errors){
            ui->voicebankReadmeTextBrowser->append(state->getErrorHTMLString());
        }
    }
    ui->voicebankReadmeTextBrowser->append(QString("<p><pre style=\"color:black\">%1</pre></p>").arg(voiceBank->getReadme()));
    ui->voicebankReadmeTextBrowser->moveCursor(QTextCursor::Start);
}
void VoiceBankManagerWindow::readVoiceBanks(){
    auto pathList = getFoldersInMonitorFolders();
    voiceBankPathsCount = pathList.count();
    LeafLogger::LogMessage(QString("准备读取音源库。共有%1个文件夹待读取。").arg(pathList.count()));
    if (voiceBankPathsCount == 0)
        setUIAfterVoiceBanksReadDone();
    else{
        voiceBankHandler->addVoiceBanks(pathList);
    }
    
}
void VoiceBankManagerWindow::setUIAfterVoiceBanksReadDone()
{
    ui->voiceBanksTableView->setEnabled(true);
    if (voiceBankHandler->count() != 0){
        ui->voicebankCountLabel->setText(tr("共 %1 个").arg(voiceBankHandler->count()));
        voiceBankTableModel->sort(VoiceBankTableModel::TableColumns::Name,Qt::SortOrder::AscendingOrder);}
    else
        ui->voicebankCountLabel->setText(tr("没有音源。"));
    ui->voiceBankBriefInfomationWidget->setVisible(false);
}

void VoiceBankManagerWindow::voiceBankReadDoneSlot(VoiceBank *voiceBank){
    if (voiceBank->isFirstRead())
        if (++voiceBankReadDoneCount == voiceBankPathsCount){
            setUIAfterVoiceBanksReadDone();
        }
    auto name  = voiceBank->getName();
    if (!name.isEmpty())
        ui->statusbar->showMessage(tr("音源“%1”读取完毕").arg(name));
    else
        ui->statusbar->showMessage(tr("音源“%1”读取完毕").arg(voiceBank->getPath()));
    LeafLogger::LogMessage(QString("读取完成数为%1个，共需要读取%2个。").arg(voiceBankReadDoneCount).arg(voiceBankPathsCount));
}
#ifndef NDEBUG
void VoiceBankManagerWindow::debugFunction()
{
    //    auto voicebank = getSelectedVoiceBank();
    //    auto dialog = new VoiceBankIconCropDialog(voicebank);
    //    dialog->exec();
}


void VoiceBankManagerWindow::debug_voiceBank_readDone_Slot(VoiceBank *){
    
}
#endif

void VoiceBankManagerWindow::createVoiceBanksTableMenu()
{
    auto openSubMenu = new QMenu(tr("打开..."),this);

    auto openPathAction = new QAction(tr("打开音源文件夹"),this);
    connect(openPathAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankPathInExplorer()));
    openPathAction->setStatusTip(tr("在资源管理器中打开该音源的文件夹。"));
    openSubMenu->addAction(openPathAction);

    auto openCharacterAction = new QAction(tr("打开character.txt"),this);
    connect(openCharacterAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankCharacterFileByOS()));
    openCharacterAction->setStatusTip(tr("在系统关联的文本编辑器中打开该音源的character.txt。"));
    openSubMenu->addAction(openCharacterAction);

    auto openReadmeAction = new QAction(tr("打开readme.txt"),this);
    connect(openReadmeAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankReadmeFileByOS()));
    openReadmeAction->setStatusTip(tr("在系统关联的文本编辑器中打开该音源的readme.txt。"));
    openSubMenu->addAction(openReadmeAction);

    voiceBanksTableWidgetMenu->addMenu(openSubMenu);

    auto copySubMenu = new QMenu(tr("复制...路径"),this);

    auto copyPathAction = new QAction(tr("复制音源路径"),this);
    connect(copyPathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankPathtoClipboard()));
    copyPathAction->setStatusTip(tr("复制该音源的文件夹路径到剪贴板。"));
    copySubMenu->addAction(copyPathAction);

    auto copyCharacterPathAction = new QAction(tr("复制character.txt的文件路径"),this);
    connect(copyCharacterPathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankCharacterFilePathtoClipboard()));
    copyCharacterPathAction->setStatusTip(tr("复制该音源的character.txt的路径到剪贴板。"));
    copySubMenu->addAction(copyCharacterPathAction);

    auto copyReadmePathAction = new QAction(tr("复制readme.txt的文件路径"),this);
    connect(copyReadmePathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankReadmeFilePathtoClipboard()));
    copyReadmePathAction->setStatusTip(tr("复制该音源的readme.txt路径到剪贴板。"));
    copySubMenu->addAction(copyReadmePathAction);

    voiceBanksTableWidgetMenu->addMenu(copySubMenu);

    auto modifySubMenu = new QMenu(tr("修改..."));

    auto modifyNameAction = new QAction(tr("修改音源的名称..."));
    connect(modifyNameAction,SIGNAL(triggered(bool)),this,SLOT(modifyNameActionSlot()));
    modifyNameAction->setStatusTip(tr("为该音源指定一个新名称。"));
    modifySubMenu->addAction(modifyNameAction);

    auto modifyIconAction = new QAction(tr("修改音源的图标..."));
    connect(modifyIconAction,SIGNAL(triggered(bool)),this,SLOT(modifyIconActionSlot()));
    modifyIconAction->setStatusTip(tr("为该音源指定一个新图标。"));
    modifySubMenu->addAction(modifyIconAction);


    voiceBanksTableWidgetMenu->addMenu(modifySubMenu);

    auto codecSubMenu = new QMenu(tr("编码相关"),this);

    auto setCodecAction = new QAction(tr("为该音源单独设置文本编码..."),this);
    connect(setCodecAction,SIGNAL(triggered(bool)),this,SLOT(setCodecForVoiceBankActionSlot()));
    setCodecAction->setStatusTip(tr("为该音源设置读取用文本编码。注意，这仅在本软件中有效。"));
    codecSubMenu->addAction(setCodecAction);

    codecSubMenu->addSeparator();

    auto convertCharacterCodecAction = new QAction(tr("对character.txt进行编码转换..."),this);
    connect(convertCharacterCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertCharacterCodecActionSlot()));
    convertCharacterCodecAction->setStatusTip(tr("在文件编码转换器中转换该音源character.txt的编码。"));
    codecSubMenu->addAction(convertCharacterCodecAction);

    auto convertReadmeCodecAction = new QAction(tr("对readme.txt进行编码转换..."),this);
    connect(convertReadmeCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertReadmeCodecActionSlot()));
    convertReadmeCodecAction->setStatusTip(tr("在文件编码转换器中转换该音源readme.txt的编码。"));
    codecSubMenu->addAction(convertReadmeCodecAction);

    auto convertWavFileNameCodecAction = new QAction(tr("对WAV文件名进行编码转换..."),this);
    connect(convertWavFileNameCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertWavFileNameCodecActionSlot()));
    convertWavFileNameCodecAction->setStatusTip(tr("在文件编码转换器中转换该音源的WAV文件名的编码。"));
    codecSubMenu->addAction(convertWavFileNameCodecAction);

    voiceBanksTableWidgetMenu->addMenu(codecSubMenu);

    auto engineMenu = new QMenu(tr("引擎相关"),this);

    auto moresamplerConfigEditAction = new QAction(tr("编辑该音源的Moresampler声库配置..."),this);
    connect(moresamplerConfigEditAction,SIGNAL(triggered(bool)),this,SLOT(moresamplerConfigEditActionSlot()));
    moresamplerConfigEditAction->setStatusTip(tr("编辑该声库的Moresampler声库配置。只有在您使用Moresampler时起效。"));
    engineMenu->addAction(moresamplerConfigEditAction);

    voiceBanksTableWidgetMenu->addMenu(engineMenu);

    auto reloadAction = new QAction(tr("重载此音源"),this);
    connect(reloadAction,SIGNAL(triggered(bool)),this,SLOT(reloadVoiceBankActionSlot()));
    reloadAction->setStatusTip(tr("重新从硬盘加载此音源。"));
    voiceBanksTableWidgetMenu->addAction(reloadAction);

}
VoiceBank* VoiceBankManagerWindow::getSelectedVoiceBank()
{
    return getSelectedVoiceBank(ui->voiceBanksTableView->currentIndex());
}

VoiceBank *VoiceBankManagerWindow::getSelectedVoiceBank(const QModelIndex &current)
{
    return voiceBankHandler->getVoiceBank(current.row());
}

void VoiceBankManagerWindow::openVoiceBankPathInExplorer()
{
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        auto url = QUrl("file:" + voiceBank->getPath());
        QDesktopServices::openUrl(url);}
    
}
void VoiceBankManagerWindow::openVoiceBankCharacterFileByOS(){
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        auto url = QUrl("file:" + voiceBank->getPath() + "character.txt");
        if (!QDesktopServices::openUrl(url)){
            if (!QFileInfo(voiceBank->getPath() + "character.txt").exists())
            {
                auto id = QMessageBox::information(this,"文件不存在","看起来该音源的character.txt不存在。是否需要程序创建一个？",QMessageBox::Ok | QMessageBox::Abort,QMessageBox::Ok);
                if (id == QMessageBox::Ok)
                {
                    modifyNameActionSlot();
                    openVoiceBankCharacterFileByOS();
                    return;
                }
            }
            QMessageBox::warning(this,tr("打开失败"),tr("无法打开%1。").arg(url.url()));
        };}
}
void VoiceBankManagerWindow::openVoiceBankReadmeFileByOS(){
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        auto url = QUrl("file:" + voiceBank->getPath() + "readme.txt");
        if(!QDesktopServices::openUrl(url)){
            if (!QFileInfo(voiceBank->getPath() + "readme.txt").exists())
            {
                auto id = QMessageBox::information(this,"文件不存在","看起来该音源的readme.txt不存在。是否需要程序创建一个？",QMessageBox::Ok | QMessageBox::Abort,QMessageBox::Ok);
                if (id == QMessageBox::Ok)
                {
                    QFile file(voiceBank->getPath() + "readme.txt");
                    file.open(QIODevice::WriteOnly);
                    file.close();
                    openVoiceBankReadmeFileByOS();
                    return;
                }
            }
            QMessageBox::warning(this,tr("打开失败"),tr("无法打开%1。").arg(url.url()));
        };
    }
}
void VoiceBankManagerWindow::copyVoiceBankPathtoClipboard()
{
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(QDir::toNativeSeparators(voiceBank->getPath()));}
}
void VoiceBankManagerWindow::copyVoiceBankCharacterFilePathtoClipboard(){
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        if (!QFileInfo(voiceBank->getPath() + "character.txt").exists())
        {
            auto id = QMessageBox::information(this,"文件不存在","看起来该音源的character.txt不存在。是否需要程序创建一个？",QMessageBox::Ok | QMessageBox::Abort,QMessageBox::Ok);
            if (id == QMessageBox::Ok)
            {
                modifyNameActionSlot();
            }
            else
                QMessageBox::information(this,tr("剪贴板仍会被更改"),tr("即使您没有要求程序创建character.txt，程序也将把路径复制到剪贴板。但还是请您注意，这个路径并没有指向有效的文件。"));
        }
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(QDir::toNativeSeparators(voiceBank->getPath() + "character.txt"));}
}
void VoiceBankManagerWindow::copyVoiceBankReadmeFilePathtoClipboard(){
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        if (!QFileInfo(voiceBank->getPath() + "readme.txt").exists())
        {
            auto id = QMessageBox::information(this,"文件不存在","看起来该音源的readme.txt不存在。是否需要程序创建一个？",QMessageBox::Ok | QMessageBox::Abort,QMessageBox::Ok);
            if (id == QMessageBox::Ok)
            {
                QFile file(voiceBank->getPath() + "readme.txt");
                file.open(QIODevice::WriteOnly);
                file.close();
            }
            else
                QMessageBox::information(this,tr("剪贴板仍会被更改"),tr("即使您没有要求程序创建readme.txt，程序也将把路径复制到剪贴板。但还是请您注意，这个路径并没有指向有效的文件。"));
        }
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(QDir::toNativeSeparators(voiceBank->getPath() + "readme.txt"));}
}
void VoiceBankManagerWindow::setCodecForVoiceBankActionSlot(){
    auto voiceBank = getSelectedVoiceBank();
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
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        auto path = voiceBank->getPath() + "character.txt";
        if (!QFileInfo(path).exists())
        {
            QMessageBox::warning(this,tr("character.txt不存在"),tr("您选定的音源不存在character.txt。所以无法进行转换操作。"));
            return;
        }
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
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        auto path = voiceBank->getPath() + "readme.txt";
        if (!QFileInfo(path).exists())
        {
            QMessageBox::warning(this,tr("readme.txt不存在"),tr("您选定的音源不存在readme.txt。所以无法进行转换操作。"));
            return;
        }
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
    auto voiceBank = getSelectedVoiceBank();
    voiceBank->readWavFileName();
    if (voiceBank){
        auto showString = voiceBank->getWavFileNameRaw().join("\n");
        auto dialog = new TextCodecConvertDialog(tr("%1的WAV文件名").arg(voiceBank->getName()),showString,voiceBank->getWavFileNameTextCodec(),QTextCodec::codecForLocale(),true,this);
        auto dialogCode = dialog->exec();
        if (dialogCode == QDialog::Accepted){
            auto sourceCodec = dialog->getSourceCodec();
            auto targetCodec = dialog->getTargetCodec();
            QTextEncoder encoder(targetCodec);
            QTextDecoder decoder(sourceCodec);
            QTextDecoder decoderLocale(QTextCodec::codecForLocale());
            auto wavFilePath = voiceBank->getWavFilePath();
            auto it = wavFilePath.begin();
            QStringList unsucess;
            while (it != wavFilePath.end())
            {
                auto file = new QFile(*it);
                if (file->exists()) {
                    QFileInfo fileInfo(*it);
                    auto newName = decoderLocale.toUnicode(encoder.fromUnicode(decoder.toUnicode(fileInfo.fileName().toLocal8Bit())));
                    auto newPath = fileInfo.absolutePath() + "/" + newName;
                    if (newName != fileInfo.fileName())
                    {
                        if (!file->rename(newPath)) {
                            unsucess.append(tr("%1（%2）").arg(file->fileName()).arg(file->errorString()));
                            LeafLogger::LogMessage(QString("文件重命名时发生错误。QFile的错误信息为%1。").arg(file->errorString()));
                        }
                    }
                }
                file->deleteLater();
                ++it;
            }
            if (!unsucess.isEmpty()){
                QMessageBox::warning(this,tr("转换中出了些问题"),tr("<h3>程序在转换以下文件时出了些错误</h3><pre>%1</pre><p>这些文件应当都保持在原有的状态。您可以排查问题后重试。</p>").arg(unsucess.join("\n")));
            }
            else
            {
                voiceBank->clearWavFileReadStage();
                voiceBank->setWavFileNameTextCodec(targetCodec);
                QMessageBox::information(this,tr("转换成功完成"),tr("音源%1的WAV文件名均已从%2转换至%3。").arg(voiceBank->getName()).arg(QString::fromUtf8(sourceCodec->name())).arg(QString::fromUtf8(targetCodec->name())));
            }
        }
        dialog->deleteLater();
    }
}
QPair<bool,QTextCodec*> VoiceBankManagerWindow::processFileTextCodecConvert(const QString& path,QTextCodec* sourceCodec,QTextCodec* targetCodec){
    bool isDone = false;
    QFile* file = new QFile(path);
    if (!file->exists()){
        file->deleteLater();
        QMessageBox::warning(this,tr("文件不存在"),tr("文件%1不存在").arg(path));
        return QPair<bool,QTextCodec*>(false,nullptr);}
    QByteArray rawData;
    if (file->open(QIODevice::ReadOnly | QIODevice::Text)){
        rawData = file->readAll();
        file->close();}
    auto dialog = new TextCodecConvertDialog(path,rawData,sourceCodec,targetCodec,false,this);
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted){
        auto infoDialogCode = QMessageBox::information(this,tr("即将执行编码转换"),tr("<h3>程序即将对%1执行编码转换（%2 -> %3）</h3><p>在您单击确定后，程序将会把转换后的结果保存至%1。</p><p>但是，程序有必要提醒您编码转换的<b>风险</b>：由于源编码和目标编码间的可能的映射不对等关系，这种转换可能<b>不可逆</b>，并且可能使您<b>丢失数据</b>！</p><p>出于安全考虑，程序将保存一份源文件的备份副本（%1.bak），以便出现问题时您可以手动恢复。</p><p>确定要执行转换吗？</p>").arg(path).arg(QString::fromUtf8(dialog->getSourceCodec()->name())).arg(QString::fromUtf8(dialog->getTargetCodec()->name())),QMessageBox::Ok | QMessageBox::Cancel);
        if (infoDialogCode == QMessageBox::Ok){
            QFile bakFile(path + ".bak");
            if (bakFile.exists())
                bakFile.remove();
            if (file->copy(path + ".bak")){
                if (file->open(QIODevice::WriteOnly | QIODevice::Text)){
                    auto fileWriteCode = file->write(dialog->getEncodedTargetByteArray());
                    if (fileWriteCode == -1){
                        QMessageBox::critical(this,tr("转换失败"),tr("<h3>程序无法对%1进行写入</h3><p>在写入时出现错误。Qt提供的错误描述为%2。</p><p>文件应该没有被修改。</p>").arg(path).arg(file->errorString()));
                    }
                    else
                    {
                        QMessageBox::information(this,tr("转换成功"),tr("<h3>文件编码转换完成</h3><p>程序将自动修改该文件的读取用文本编码，之后将实施重载。</p>"));
                        isDone = true;
                    }
                    file->close();
                }
            }
            else
            {
                QMessageBox::critical(this,tr("无法备份%1").arg(path + ".bak"),tr("<h3>程序无法对%1进行备份</h3><p>在备份时出现错误。Qt提供的错误说明为：%2</p><p>你仍可以令程序继续转换，但是之前提到的<b>风险</b>仍然存在，且出现问题时您无法恢复。</p><p>确定要继续转换吗？</p>").arg(path).arg(file->errorString()));
            }
        }
    }
    if (file->isOpen())
        file->close();
    file->deleteLater();
    dialog->deleteLater();
    return QPair<bool,QTextCodec*>(isDone,dialog->getTargetCodec());
}
void VoiceBankManagerWindow::reloadVoiceBankActionSlot(){
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        voiceBank->readFromPath();
        voiceBankTableModel->dataChangedEmitter(voiceBank);
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
        auto clickedButton = QMessageBox::information(this,"监视文件夹列表被更改","您更改了监视文件夹列表，是否立即重载音源库列表？",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
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
        auto clickedButton = QMessageBox::information(this,"默认文本读取编码被更改","您更改了默认的读取用文本编码，是否立即重载音源库列表？",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksList();
    }
    dialog->deleteLater();
}

void VoiceBankManagerWindow::on_searchLineEdit_textChanged(const QString &text)
{
    int rowCount = voiceBankHandler->getVoiceBankCount();//获得行号
    if (text.isEmpty())//判断输入是否为空
    {
        for (int i = 0; i < rowCount; i++)
        {
            ui->voiceBanksTableView->setRowHidden(i, false);//显示所有行
        }
    }
    else
    {
        auto voiceBankIDs = voiceBankHandler->findIDByName(text);
        for (int i = 0; i < rowCount; i++)
        {
            ui->voiceBanksTableView->setRowHidden(i, true);//隐藏所有行
        }
        if (!voiceBankIDs.isEmpty())//不为空
        {
            for (auto i : voiceBankIDs)
                ui->voiceBanksTableView->setRowHidden(i,false);
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
    QMessageBox::about(this,tr("关于本程序"),tr("<h3>音源管理器</h3>"
                                             "<p>版本：%1 作者：shine_5402</p>"
                                             "<p>本程序以 Apache License Version 2.0 分发。</p>"
                                             "<p>“音源管理器”是为UTAU程序所用音源设计的本地信息管理器。</p>"
                                             "<p>本程序是 <a href=\"https://github.com/shine5402/LeafOpenUTAUQt\">Leaf OpenUTAU Qt Project</a> 的一部分</p>"
                                             "<p>UTAU是一款由饴屋/菖蒲（あめや・あやめ）氏开发的免费的歌声合成软件。</p>"
                                             "<p>本程序使用了以下开源项目：</p>"
                                             "<ul>"
                                             "<li>LeafPublicQtClasses by shine_5402 (Apache License Version 2.0)</li>"
                                             "<li>ImageCropper by dimkanovikov and shine_5402 (GNU LGPL v3)</li>"
                                             "</ul>").arg(voicebankManagerVersion));
}

void VoiceBankManagerWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,tr("关于 Qt"));
}

void VoiceBankManagerWindow::on_actionSet_Thread_Pool_Max_Count_triggered()
{
    bool ok = false;
    auto count = QInputDialog::getInt(this,tr("设定线程池的最大大小"),tr("（高级）该设置改变程序读取音源库时的最大线程数。请确保您在知道自己在做什么之后再更改此项设置。"),voiceBankHandler->getThreadPoolMaxThreadCount(),1,2147483647,1,&ok);
    if (ok){
        voiceBankHandler->setThreadPoolMaxThreadCount(count);
        ui->statusbar->showMessage(tr("线程池大小已经被设置为%1").arg(count));
    }
}

void VoiceBankManagerWindow::on_voiceBanksTableView_customContextMenuRequested(const QPoint &)
{
    voiceBanksTableWidgetMenu->exec(QCursor::pos());
}


void VoiceBankManagerWindow::onVoiceBankViewCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    auto voiceBank = getSelectedVoiceBank(current);
    if (voiceBank)
        setVoiceBankInfomation(voiceBank);
}

void VoiceBankManagerWindow::moresamplerConfigEditActionSlot()
{
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank)
    {
        QDir dir(voiceBank->getPath());
        auto subDirs = dir.entryList(QDir::Dirs | QDir::NoDotDot);
        if (subDirs == QStringList({"."}))
        {
            auto dialog = new MoresamplerConfigsDialog(voiceBank->getPath() + "moreconfig.txt",MoresamplerConfigReader::VoiceBank,this,voiceBank->getName());
            dialog->exec();
        }
        else
        {
            bool ok = false;
            auto choice = QInputDialog::getItem(this,tr("选择一个子文件夹"),tr("您选择的音源有子文件夹。Moresampler的配置文件只对一个同文件夹内的wav文件起效。请选择一个子文件夹来编辑配置："),subDirs,0,true,&ok);
            if (ok)
            {
                auto dialog = new MoresamplerConfigsDialog(QDir::cleanPath(dir.absoluteFilePath(choice)) + "/" + "moreconfig.txt",MoresamplerConfigReader::VoiceBank,this,voiceBank->getName());
                dialog->exec();
            }
        }
    }
}

void VoiceBankManagerWindow::on_actionEdit_Global_MoresamplerConfig_triggered()
{
    QStringList configFilePaths;
    for (auto path : monitorFolders)
    {
        QDir dir(path);
        if (dir.cdUp()){
            if (QFileInfo(dir.absoluteFilePath("moreconfig.txt")).exists())
                configFilePaths.append(QDir::cleanPath(dir.absoluteFilePath("moreconfig.txt")));
        }
    }
    if (!configFilePaths.isEmpty())
    {
        bool ok = false;
        auto item = QInputDialog::getItem(this,tr("检测到可能的全局配置"),tr("在监视文件夹的父文件夹中发现了以下可能的Moresampler配置文件。您可以选择其中的一个打开，或者取消来进行浏览。"),configFilePaths,0,false,&ok);
        if (ok)
        {
            auto dialog = new MoresamplerConfigsDialog(item,MoresamplerConfigReader::Global,this);
            dialog->exec();
            return;
        }
    }
    if (auto filePath = QFileDialog::getOpenFileName(this,tr("打开一个Moresampler全局配置文件"),QString(),tr("Moresampler 配置文件 (moreconfig.txt)"));!filePath.isEmpty()){
        auto dialog = new MoresamplerConfigsDialog(filePath,MoresamplerConfigReader::Global,this);
        dialog->exec();
    };
}

void VoiceBankManagerWindow::modifyNameActionSlot()
{
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank)
    {
        bool ok = false;
        auto name = QInputDialog::getText(this,tr("为音源指定一个新名称"),tr("为路径为%1的音源指定一个新名称（程序会自动转换编码）：").arg(voiceBank->getPath()),QLineEdit::Normal,voiceBank->getName(),&ok);
        if (ok)
        {
            try{voiceBank->rename(name);
                ui->statusbar->showMessage(tr("已将路径为%1的音源的名称设置为%2。").arg(voiceBank->getPath()).arg(voiceBank->getName()));
                setVoiceBankInfomation(voiceBank);}
            catch(VoiceBank::FileCanNotOpen& e){
                QMessageBox::critical(this,tr("文件无法被打开"),tr("有一个文件无法被打开。Qt提供的错误字符串为%1").arg(e.QFileError()));
            }
            catch(VoiceBank::FileNotExists&){
                setVoiceBankInfomation(voiceBank);
                ui->statusbar->showMessage(tr("路径为%1的音源的character.txt不存在。程序已经自动创建并将名称设置为%1。").arg(voiceBank->getName()));
            }
        }
    }
}

void VoiceBankManagerWindow::modifyIconActionSlot()
{
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank)
    {
        QByteArrayList supportedList = QImageReader::supportedImageFormats();
        QString supportedListJoinedString;
        for (auto i : supportedList)
        {
            supportedListJoinedString.append("*." + QString::fromUtf8(i) + " ");
        }
        auto supportedFilterString = tr("图像文件 (%1)").arg(supportedListJoinedString.trimmed());
        auto rawImageFilePath = QFileDialog::getOpenFileName(this,tr("选择要设定为图标的新图片"),voiceBank->getPath(),supportedFilterString);
        if (!rawImageFilePath.isEmpty())
        {
            auto dialog = new VoiceBankIconCropDialog(voiceBank,rawImageFilePath,this);
            auto id = dialog->exec();
            if (id == QDialog::Accepted)
            {
                reloadVoiceBankActionSlot();
            }
        }
    }
}

void VoiceBankManagerWindow::on_actionchoose_a_voicebank_randomly_triggered()
{
    if (voiceBankHandler->count() == 0)
    {
        QMessageBox::warning(this,tr("没有音源"),tr("没有音源，无法随机选择音源。"));
        return;
    }
    QList<int> unHidden;
    for (int i = 0;i < voiceBankHandler->count();++i)
    {
        if (!ui->voiceBanksTableView->isRowHidden(i))
            unHidden.append(i);
    }
    int random = QRandomGenerator::global()->bounded(0,unHidden.count());
    ui->voiceBanksTableView->setCurrentIndex(voiceBankTableModel->index(unHidden.at(random),0));
}

void VoiceBankManagerWindow::onBackupImageFileBecauseExists(VoiceBank *voicebank)
{
    ui->statusbar->showMessage(tr("备份了%1原先的图标，因为目标文件名已存在。").arg(voicebank->getName()));
}

void VoiceBankManagerWindow::onCannotBackupImageFile(VoiceBank *voicebank)
{
    QMessageBox::critical(this,tr("无法备份"),tr("因为重名，程序尝试备份%1原先的图标，但是遇到错误无法完成，操作终止。").arg(voicebank->getName()));
}

void VoiceBankManagerWindow::on_playSamplebutton_clicked()
{
    samplePlayer->stop();
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank)
    {
        //FIXME:没有sample的音源的读取出错
        auto sample = voiceBank->getSample();
        if (sample.isEmpty())
        {
            voiceBank->readWavFileName();
            auto wavfileList = voiceBank->getWavFilePath();
            if (wavfileList.isEmpty())
            {
                QMessageBox::critical(this,tr("没有可供播放的样例"),tr("程序无法找到可供播放的样例文件。"));
                return;
            }
            for (auto i : wavfileList)
            {
                if (!i.isEmpty())
                {
                    if (i.contains("br"))
                        continue;
                    sample = i;
                    break;
                }
            }
        }
        else
            sample = voiceBank->getPath() + sample + ".wav";
        qDebug() << sample;
        samplePlayer->setAudioRole(QAudio::Role::MusicRole);
        samplePlayer->setMedia(QUrl::fromLocalFile(sample));
        if (samplePlayerProgress)
        samplePlayerProgress->setMinimum(0);
        samplePlayerProgress->setMaximum(INT_MAX);
        samplePlayerProgress->setTextVisible(false);
        connect(samplePlayer,SIGNAL(positionChanged(qint64)),this,SLOT(onSamplePlayerPositionChange(qint64)));
        connect(samplePlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(onSamplePlayerStateChanged(QMediaPlayer::State)));
        ui->statusbar->addPermanentWidget(samplePlayerProgress);
        samplePlayerProgress->show();
        samplePlayer->play();
        ui->statusbar->showMessage(tr("正在播放%1的声音样例").arg(voiceBank->getName()));
    }
}
void VoiceBankManagerWindow::onSamplePlayerPositionChange(qint64 position)
{
    auto sampleDuration = samplePlayer->duration();
    qreal positionRate = static_cast<double>(position) / ((sampleDuration == 0)?INT_MAX:sampleDuration);
    samplePlayerProgress->setValue(static_cast<int>(INT_MAX * positionRate));
}
void VoiceBankManagerWindow::onSamplePlayerStateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::State::StoppedState){
        ui->statusbar->removeWidget(samplePlayerProgress);
        ui->statusbar->clearMessage();
        samplePlayer->setMedia(QMediaContent());
    }
}
