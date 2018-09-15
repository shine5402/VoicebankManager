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
    loadMonitorFoldersSettings();
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
                if (errors_it.value()) {
                    if (voiceBank->getImage().isNull())
                        ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：character.txt中设定的图片文件没有正常读取。是不是图片格式与后缀名不符？亦或是文件损坏？</p>)"));
                    else
                        ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：character.txt中设定的图片文件（%1*%2）不符合UTAU的图标要求（100*100）。在音源使用过程中将音源区域图片可能显示不正确，或者无法显示。</p>)").arg(voiceBank->getImage().width()).arg(voiceBank->getImage().height()));
                }
                break;
            case VoiceBank::ProbablyErrors::ReadmeFileNotExists:
                if (errors_it.value())
                    ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：找不到readme.txt。音源的README将无法显示。</p>)"));
                break;
            case VoiceBank::ProbablyErrors::PixmapReadException:
                if (errors_it.value())
                    ui->voicebankReadmeTextBrowser->append(tr(u8R"(<p style="color:red">错误：在读取音源图片时发生了一个异常。或许重载此音源能解决这个问题。</p>)"));
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
    if (voiceBankPathsCount == 0)
        setUIAfterVoiceBanksReadDone();
    else{
        for (auto path : pathList){
            voiceBankHandler->addVoiceBank(path);
        }
    }
    
}
void VoiceBankManagerWindow::setUIAfterVoiceBanksReadDone()
{
    ui->voiceBanksTableWidget->setEnabled(true);
    if (voiceBankHandler->count() != 0)
        ui->voicebankCountLabel->setText(tr(u8"共 %1 个").arg(voiceBankHandler->count()));
    else
        ui->voicebankCountLabel->setText(tr(u8"没有音源。"));
    ui->voiceBankBriefInfomationWidget->setVisible(false);
}

void VoiceBankManagerWindow::voiceBankReadDoneSlot(VoiceBank *voiceBank){
    addVoiceBankRowInTableWidget(voiceBank);
    if (++voiceBankReadDoneCount == voiceBankPathsCount){
        setUIAfterVoiceBanksReadDone();
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
    if (dialogCode == 1){
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
    QMessageBox::about(this,tr(u8"关于本程序"),tr(u8R"(<h3>音源管理器</h3><p>版本：%1 作者：shine_5402</p><p>本程序以 Apache 2.0 License 分发。</p><p>“音源管理器”是为UTAU程序所用音源设计的本地信息管理器。</p><p>本程序是 <a href="https://github.com/shine5402/LeafOpenUTAUQt">Leaf OpenUTAU Qt Project</a> 的一部分</p><p>UTAU是一款由饴屋/菖蒲（あめや・あやめ）氏开发的免费的歌声合成软件。</p>)").arg(version));
}
const QString VoiceBankManagerWindow::version = "0.1.1";

void VoiceBankManagerWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,tr(u8"关于 Qt"));
}
