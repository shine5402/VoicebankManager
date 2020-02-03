#include "voicebankmanagerwindow.h"
#include "ui_voicebankmanagerwindow.h"
//TODO:重构 将Dialog完成后的代码迁移至继承的accept和reject。

#ifndef NDEBUG
#include "voicebankcategoryeditormodel.h"
#include "voicebankcategorylabeleditdialog.h"
void VoicebankManagerWindow::debugFunction()
{
    auto model = new VoicebankCategoryEditorModel(getCurrentVoiceBank(), categoriesAndLabelsListWidget, this);
    auto dialog = new VoicebankCategoryLabelEditDialog(model,this);
    dialog->exec();
}
#endif

void VoicebankManagerWindow::connectWithVoiceBankHandler()
{
    connect(voiceBankHandler,SIGNAL(backupImageFileBecauseExists(Voicebank*)),this,SLOT(onBackupImageFileBecauseExists(Voicebank *)));
    connect(voiceBankHandler,SIGNAL(cannotBackupImageFile(Voicebank*)),this,SLOT(onCannotBackupImageFile(Voicebank*)));
    connect(voiceBankHandler,SIGNAL(voiceBanksReadDone()),this,SLOT(setUIAfterVoiceBanksReadDone()));
    connect(voiceBankHandler,SIGNAL(aVoiceBankReloadDone(Voicebank *)),this,SLOT(onVoiceBankReloadDone(Voicebank *)));
    connect(voiceBankHandler,SIGNAL(useOldFolderScanChanged()),this,SLOT(onUseOldFolderScanChanged()));

    connect(voiceBankHandler,SIGNAL(categoriesChanged()),categoriesAndLabelsListWidget,SLOT(readCategoriesFromVoicebankHandler()));
    connect(categoriesAndLabelsListWidget,SIGNAL(categoriesChanged()),this,SLOT(createVoiceBanksCategoriesSubMenu()));
    connect(voiceBankHandler,SIGNAL(labelsChanged()),categoriesAndLabelsListWidget,SLOT(readLabelsFromVoiceBankHandler()));
    connect(categoriesAndLabelsListWidget,SIGNAL(labelsChanged()),this,SLOT(createVoiceBanksLabelsSubMenu()));
    connect(categoriesAndLabelsListWidget,SIGNAL(currentCategoriesChanged(QStringList)),this,SLOT(onCurrentCategoriesChanged(const QStringList&)));
    connect(categoriesAndLabelsListWidget,SIGNAL(currentLabelsChanged(QStringList)),this,SLOT(onCurrentLabelsChanged(const QStringList&)));
    connect(categoriesAndLabelsListWidget,SIGNAL(labelSelectionStrategyChanged()),this,SLOT(dealFilters()));
}

VoicebankManagerWindow::VoicebankManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VoicebankManagerWindow)
{
    /*!
      VoiceBankManagerWindow 的构造函数。它将会自动加载相关设置，但不会加载音源库。因为那是 VoiceBankHandler 的工作。 \n
      VoiceBankManagerWindow 会自动获取 VoiceBankHandler 的实例。您只需要调用 VoiceBankManagerWindow::loadVoiceBanksAndTable() 即可让 VoiceBankManager 加载音源库。
     */
    ui->setupUi(this);
#ifndef NDEBUG
    //创建Debug用菜单项
    QAction* debugFunctionAction = new QAction("执行Debug测试函数",this);
    ui->menubar->addAction(debugFunctionAction);
    connect(debugFunctionAction,SIGNAL(triggered(bool)),this,SLOT(debugFunction()));
#endif

    //设置音源信息显示区域
    ui->voiceBankBriefInfomationWidget->setVisible(false);

    //设置TableView
    voiceBankTableModel = new VoicebankTableModel(voiceBankHandler);
    ui->voiceBanksTableView->setModel(voiceBankTableModel);
    ui->voiceBanksTableView->horizontalHeader()->setSortIndicator(VoicebankTableModel::TableColumns::Name,Qt::SortOrder::AscendingOrder);
    connect(ui->voiceBanksTableView->selectionModel(),SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),this,SLOT(onVoiceBankViewSelectionChanged(const QItemSelection &, const QItemSelection &)));
    connect(voiceBankTableModel,&VoicebankTableModel::sortDone,this,&VoicebankManagerWindow::dealFilters);

    //分组语言菜单的action
    auto languageActionGroup = new QActionGroup(this);
    languageActionGroup->addAction(ui->actionAuto_detect);
    languageActionGroup->addAction(ui->actionDon_t_translate);
    languageActionGroup->addAction(ui->actionLoad_a_translation_file);

    //加载语言文件
    QSettings settings;
    ui->actionAuto_detect->setChecked(settings.value("Translation/Auto",true).toBool());
    if (settings.value("Translation/Auto",true).toBool())
    {
        autoDetectTranslate();
        ui->actionAuto_detect->setChecked(true);
        ui->actionDon_t_translate->setChecked(false);
        ui->actionLoad_a_translation_file->setChecked(false);
    }
    else if (settings.value("Translation/isLoadOwnTranslationFile",false).toBool())
    {
        auto translator = new QTranslator(this);
        auto success = translator->load(settings.value("Translation/OwnTranslationFile").toString());
        if (success)
        {
            qApp->installTranslator(translator);
            translators.append(translator);
            ui->actionAuto_detect->setChecked(false);
            ui->actionDon_t_translate->setChecked(false);
            ui->actionLoad_a_translation_file->setChecked(true);
        }
    }
    else if (settings.value("Translation/NoTranslation",false).toBool())
    {
        ui->actionAuto_detect->setChecked(false);
        ui->actionDon_t_translate->setChecked(true);
        ui->actionLoad_a_translation_file->setChecked(false);
    }
    //连接语言菜单的槽
    connect(ui->actionAuto_detect,SIGNAL(triggered(bool)),this,SLOT(dealLanguageMenuAutoAndDontStates()));
    connect(ui->actionLoad_a_translation_file,SIGNAL(triggered(bool)),this,SLOT(dealLanguageMenuLoadFile()));
    connect(ui->actionDon_t_translate,SIGNAL(triggered(bool)),this,SLOT(dealLanguageMenuAutoAndDontStates()));

    createVoiceBanksTableMenu();

    //在分类器里加入分类和标签
    ui->categoryAndLabelsAndListSplitter->insertWidget(0,categoriesAndLabelsListWidget);
    showMoreInformationInTotalCountLabel = settings.value("VoiceBankManager/showMoreInformationInTotalCountLabel",true).toBool();
    ui->actionshow_more_infomation_in_total_count_label->setChecked(showMoreInformationInTotalCountLabel);

    loadWindowStatus();
    connectWithVoiceBankHandler();
}


void VoicebankManagerWindow::loadVoiceBanksAndTable()
{
    /*!
      加载音源库列表，并填充窗口中的表格。\n
       VoiceBankManagerWindow 会自动处理相关的UI变化，所以在合适的时机调用该函数即可。\n
      如果您不是在 VoiceBankManagerWindow 打开之时加载音源库，您可以直接使用 VoiceBankHandler::readVoiceBanksFromMonitorFolders() 。
    */
    voiceBankTableModel->clearEmitter();
    voiceBankHandler->clear();
    ui->categoryAndLabelsAndListSplitter->setEnabled(false);
    ui->searchLineEdit->setEnabled(false);
    ui->voicebankCountLabel->setText(tr("加载中"));
    voiceBankHandler->readVoiceBanksFromMonitorFolders();
    ui->searchLineEdit->clear();
}

void VoicebankManagerWindow::dealLanguageMenuAutoAndDontStates(){
    if (ui->actionAuto_detect->isChecked())
    {
        autoDetectTranslate();
    }
    else if (ui->actionDon_t_translate->isChecked())
    {
        removeAllTranslators();
    }
}
void VoicebankManagerWindow::dealLanguageMenuLoadFile(){
    if (ui->actionLoad_a_translation_file->isChecked()){
        auto fileName = QFileDialog::getOpenFileName(this,tr("载入一个翻译文件（Load a translation file...）"),QString(),"Qt 语言文件 (*.qm)");
        if (!fileName.isEmpty()){
            auto translator = new QTranslator(this);
            auto success = translator->load(fileName);
            if (success)
            {
                qApp->installTranslator(translator);
                translators.append(translator);
                QSettings settings;
                settings.setValue("Translation/Auto",false);
                settings.setValue("Translation/NoTranslation",false);
                settings.setValue("Translation/isLoadOwnTranslationFile",true);
                settings.setValue("Translation/OwnTranslationFile",fileName);
            }
            else
            {
                ui->statusbar->showMessage(tr("无法加载语言文件%1。等同于自动推断。(Can't load language file %1. Equal to auto-detect.)").arg(fileName));
                autoDetectTranslate();
                ui->actionAuto_detect->setChecked(true);
                ui->actionDon_t_translate->setChecked(false);
                ui->actionLoad_a_translation_file->setChecked(false);
            }
        }
        else
        {
            ui->statusbar->showMessage(tr("没有指定语言文件。等同于自动推断。(No language file is selected. Equal to auto-detect.)"));
            autoDetectTranslate();
            ui->actionAuto_detect->setChecked(true);
            ui->actionDon_t_translate->setChecked(false);
            ui->actionLoad_a_translation_file->setChecked(false);
            return;
        }
    }
}
void VoicebankManagerWindow::autoDetectTranslate(){
    removeAllTranslators();
    auto translator = new QTranslator(this);
    auto success = translator->load(QLocale(),"LeafOpenUTAUQt",".","./translations",".qm");
    if ((!success) && QLocale::system().name() != QLocale(QLocale::Chinese).name())
    {
        translator->load("./translations/LeafOpenUTAUQt_en.qm");
    }
    qApp->installTranslator(translator);
    translators.append(translator);
    QSettings settings;
    settings.setValue("Translation/Auto",true);
    settings.setValue("Translation/NoTranslation",false);
    settings.setValue("Translation/isLoadOwnTranslationFile",false);
}
void VoicebankManagerWindow::removeAllTranslators(){
    for (auto translator : translators)
    {
        qApp->removeTranslator(translator);
    }
    //ui->retranslateUi(this);
    translators.clear();
    QSettings settings;
    settings.setValue("Translation/Auto",false);
    settings.setValue("Translation/NoTranslation",true);
    settings.setValue("Translation/isLoadOwnTranslationFile",false);
}


VoicebankManagerWindow::~VoicebankManagerWindow()
{
    /*!
       VoiceBankManagerWindow 的析构函数。它将自动保存窗口状态，监视文件夹等设置。
     */
    saveWindowStatus();
    delete ui;

    QSettings settings;
    settings.setValue("VoiceBankManager/showMoreInformationInTotalCountLabel",showMoreInformationInTotalCountLabel);
}

void VoicebankManagerWindow::loadWindowStatus()
{
    QSettings settings;
    if (settings.contains("VoiceBankManager/WindowGeometry"))
        restoreGeometry(settings.value("VoiceBankManager/WindowGeometry").toByteArray());
    if (settings.contains("VoiceBankManager/categoryAndLabelsAndListSplitterState"))
    {
        bool a = ui->categoryAndLabelsAndListSplitter->restoreState(settings.value("VoiceBankManager/categoryAndLabelsAndListSplitterState").toByteArray());
        qDebug() << a;
    }
    else
    {
        //处理分裂器布局
        //横向
        QWidget *hWidget0 = ui->categoryAndLabelsAndListSplitter->widget(0);
        auto sizePolicy0 = hWidget0->sizePolicy();
        sizePolicy0.setHorizontalStretch(1);
        hWidget0->setSizePolicy(sizePolicy0);
        QWidget *hWidget1 = ui->categoryAndLabelsAndListSplitter->widget(1);
        auto sizePolicy1 = hWidget1->sizePolicy();
        sizePolicy1.setHorizontalStretch(5);
        hWidget1->setSizePolicy(sizePolicy1);

    }
    if (settings.contains("VoiceBankManager/informationAndListSplitterState"))
        ui->informationAndListSplitter->restoreState(settings.value("VoiceBankManager/informationAndListSplitterState").toByteArray());
    else
    {
        //纵向
        ui->informationAndListSplitter->setStretchFactor(0,2);
        ui->informationAndListSplitter->setStretchFactor(1,1);
    }
}

void VoicebankManagerWindow::saveWindowStatus()
{
    QSettings settings;
    settings.setValue("VoiceBankManager/WindowGeometry",saveGeometry());
    settings.setValue("VoiceBankManager/categoryAndLabelsAndListSplitterState",ui->categoryAndLabelsAndListSplitter->saveState());
    settings.setValue("VoiceBankManager/informationAndListSplitterState",ui->informationAndListSplitter->saveState());
}

void VoicebankManagerWindow::fillVoicebankInformationTextBrower(Voicebank* voiceBank)
{
    if (!voiceBank)
        return;
    ui->voicebankInformationTextBrowser->clear();
    if (voiceBank->askFileInfo())
    {
        ui->voicebankInformationTextBrowser->append(generateFileInfoString(voiceBank->getfileInfoStruct()));
    }
    else {
        ui->voicebankInformationTextBrowser->append(tr("<p>文件信息统计中……</p>"));
        connect(voiceBank,&Voicebank::fileInfoReadComplete,this,&VoicebankManagerWindow::handleFileInfoReadComplete,static_cast<Qt::ConnectionType>(Qt::ConnectionType::AutoConnection | Qt::ConnectionType::DirectConnection));
    }
    if (!voiceBank->getAuthor().isEmpty())
        ui->voicebankInformationTextBrowser->append(tr("<p>作者：%1</p>").arg(voiceBank->getAuthor()));
    auto errors = voiceBank->getErrorStates();
    ui->voicebankInformationTextBrowser->append(tr("<h4><span style=\"color:red\">错误</span>与<span style=\"color:orange\">警告</span>：</h4>"));
    if (!errors.isEmpty()){
        for (auto state : errors){
            ui->voicebankInformationTextBrowser->append(state->getErrorHTMLString());
        }
    }
    else {
        ui->voicebankInformationTextBrowser->append(tr("<p style=\"color:green\">读取该声库时没有错误。</p>"));
    }

    ui->voicebankInformationTextBrowser->append(tr("<h4 style=\"color:blue\">文件编码：</h4>"));
    if (voiceBank->hasTextCodecAutoDetected())
    {
        ui->voicebankInformationTextBrowser->append(tr("<p style=\"color:blue\">自动探测后程序读取时使用的文本编码：character.txt：%1；readme.txt：%2。</p>").arg(QString::fromUtf8(voiceBank->getCharacterTextCodec()->name())).arg(QString::fromUtf8(voiceBank->getReadmeTextCodec()->name())));
    }
    else {
        ui->voicebankInformationTextBrowser->append(tr("<p style=\"color:blue\">程序读取时使用的文本编码：character.txt：%1；readme.txt：%2。</p>").arg(QString::fromUtf8(voiceBank->getCharacterTextCodec()->name())).arg(QString::fromUtf8(voiceBank->getReadmeTextCodec()->name())));
    }
}

void VoicebankManagerWindow::setVoiceBankInfomation(Voicebank *voiceBank)
{
    if (!ui->voiceBankBriefInfomationWidget->isVisible())
        ui->voiceBankBriefInfomationWidget->setVisible(true);

    if(auto name = voiceBank->getName();!name.isEmpty())
        ui->voicebankNameLabel->setText(voiceBank->getName());
    else
        ui->voicebankNameLabel->setText(voiceBank->getPath());

    ui->voicebankImage->clear();
    if (voiceBank->getImage().isNull())
    {
        if (!voiceBank->getImagePath().isEmpty()){
            QFileInfo info(voiceBank->getImagePath());
            if (info.exists())
                ui->voicebankImage->setText(tr("（读取出错）"));
            else {
                ui->voicebankImage->setText(tr("（文件不存在）"));
            }
        }
        else {
            ui->voicebankImage->setText(tr("（字段未设定）"));
        }
    }
    else
        ui->voicebankImage->setPixmap(QPixmap::fromImage(voiceBank->getImage().scaled(100,100)));


    fillVoicebankInformationTextBrower(voiceBank);

    ui->voicebankReadmeTextBrowser->clear();
    if(!voiceBank->getReadme().isEmpty())
        ui->voicebankReadmeTextBrowser->append(QString("<p><pre style=\"color:black\">%1</pre></p>").arg(voiceBank->getReadme()));
    else {
        ui->voicebankReadmeTextBrowser->append(tr("<p>该声库没有自述文件。</p>"));
    }

    ui->voicebankReadmeTextBrowser->moveCursor(QTextCursor::Start);
    ui->voicebankInformationTextBrowser->moveCursor(QTextCursor::Start);
}

QString VoicebankManagerWindow::generateFileInfoString(const Voicebank::FileInfoStruct& fileInfoStruct) const
{
    return tr("<h4>文件信息</h4><p>文件总数：%1 个（其中有 %2 个文件夹）<br/>文件总大小：%3 字节</p>").arg(fileInfoStruct.fileCount).arg(fileInfoStruct.dirCount).arg(fileInfoStruct.fileTotalSize);
}

void VoicebankManagerWindow::updateVoiceBankCountLabel()
{

    if (voiceBankHandler->count() != 0){
        if (!showMoreInformationInTotalCountLabel)
            ui->voicebankCountLabel->setText(tr("共 %1 个").arg(voiceBankHandler->count()));
        else if (!MonitorFoldersScanner::getMonitorFoldersScanner()->isUseOldFolderScan())
            ui->voicebankCountLabel->setText(tr("共 %1 个（忽略 %2 个，不是音源文件夹的 %3 个，子文件夹递归得到 %4 个）").arg(voiceBankHandler->count()).arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getIgnoredVoiceBankFolders().count()).arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getNotVoiceBankPaths().count()).arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getScannedSubFolders().count()));
        else
            ui->voicebankCountLabel->setText(tr("共 %1 个（忽略 %2 个）").arg(voiceBankHandler->count()).arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getIgnoredVoiceBankFolders().count()));
        voiceBankTableModel->sort(VoicebankTableModel::TableColumns::Name,Qt::SortOrder::AscendingOrder);}
    else
        ui->voicebankCountLabel->setText(tr("没有音源。"));
}

void VoicebankManagerWindow::setUIAfterVoiceBanksReadDone()
{
    ui->categoryAndLabelsAndListSplitter->setEnabled(true);
    ui->searchLineEdit->setEnabled(true);
    updateVoiceBankCountLabel();
    ui->voiceBankBriefInfomationWidget->setVisible(false);
    categoriesAndLabelsListWidget->readCategoriesFromVoicebankHandler();
    categoriesAndLabelsListWidget->readLabelsFromVoiceBankHandler();
    categoriesAndLabelsListWidget->resetCurrentAndSelection();
}

void VoicebankManagerWindow::onUseOldFolderScanChanged()
{

}

void VoicebankManagerWindow::onVoiceBankReloadDone(Voicebank *voiceBank)
{
    if (voiceBank == getCurrentVoiceBank())
        setVoiceBankInfomation(voiceBank);
}


void VoicebankManagerWindow::handleFileInfoReadComplete(Voicebank* voiceBank)
{
    if (voiceBank == getCurrentVoiceBank())
        fillVoicebankInformationTextBrower(voiceBank);
}




void VoicebankManagerWindow::createVoiceBanksTableMenu()
{
    //生成单选菜单
    voiceBankCategoriesSubMenu = new QMenu(tr("分类"),this);
    voiceBankLabelsSubMenu = new QMenu(tr("标签"),this);
    singleVoiceBankTableWidgetMenu->clear();

    auto openSubMenu = new QMenu(tr("打开..."),singleVoiceBankTableWidgetMenu);

    auto openPathAction = new QAction(tr("打开音源文件夹"),openSubMenu);
    connect(openPathAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankPathInExplorer()));
    openPathAction->setStatusTip(tr("在资源管理器中打开该音源的文件夹。"));
    openSubMenu->addAction(openPathAction);

    auto openCharacterAction = new QAction(tr("打开character.txt"),openSubMenu);
    connect(openCharacterAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankCharacterFileByOS()));
    openCharacterAction->setStatusTip(tr("在系统关联的文本编辑器中打开该音源的character.txt。"));
    openSubMenu->addAction(openCharacterAction);

    auto openReadmeAction = new QAction(tr("打开readme.txt"),openSubMenu);
    connect(openReadmeAction,SIGNAL(triggered(bool)),this,SLOT(openVoiceBankReadmeFileByOS()));
    openReadmeAction->setStatusTip(tr("在系统关联的文本编辑器中打开该音源的readme.txt。"));
    openSubMenu->addAction(openReadmeAction);

    singleVoiceBankTableWidgetMenu->addMenu(openSubMenu);

    auto copySubMenu = new QMenu(tr("复制...路径"),singleVoiceBankTableWidgetMenu);

    auto copyPathAction = new QAction(tr("复制音源路径"),copySubMenu);
    connect(copyPathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankPathtoClipboard()));
    copyPathAction->setStatusTip(tr("复制选中音源的文件夹路径到剪贴板。"));
    copySubMenu->addAction(copyPathAction);

    auto copyCharacterPathAction = new QAction(tr("复制character.txt的文件路径"),copySubMenu);
    connect(copyCharacterPathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankCharacterFilePathtoClipboard()));
    copyCharacterPathAction->setStatusTip(tr("复制选中音源的character.txt的路径到剪贴板。"));
    copySubMenu->addAction(copyCharacterPathAction);

    auto copyReadmePathAction = new QAction(tr("复制readme.txt的文件路径"),copySubMenu);
    connect(copyReadmePathAction,SIGNAL(triggered(bool)),this,SLOT(copyVoiceBankReadmeFilePathtoClipboard()));
    copyReadmePathAction->setStatusTip(tr("复制选中音源的readme.txt路径到剪贴板。"));
    copySubMenu->addAction(copyReadmePathAction);

    singleVoiceBankTableWidgetMenu->addMenu(copySubMenu);

    auto modifySubMenu = new QMenu(tr("修改..."));

    auto modifyNameAction = new QAction(tr("修改音源的名称..."),modifySubMenu);
    connect(modifyNameAction,SIGNAL(triggered(bool)),this,SLOT(modifyNameActionSlot()));
    modifyNameAction->setStatusTip(tr("为该音源指定一个新名称。"));
    modifySubMenu->addAction(modifyNameAction);

    auto modifyIconAction = new QAction(tr("修改音源的图标..."),modifySubMenu);
    connect(modifyIconAction,SIGNAL(triggered(bool)),this,SLOT(modifyIconActionSlot()));
    modifyIconAction->setStatusTip(tr("为该音源指定一个新图标。"));
    modifySubMenu->addAction(modifyIconAction);


    singleVoiceBankTableWidgetMenu->addMenu(modifySubMenu);

    auto codecSubMenu = new QMenu(tr("编码相关"),singleVoiceBankTableWidgetMenu);

    auto setCodecAction = new QAction(tr("为选中音源单独设置文本编码..."),codecSubMenu);
    connect(setCodecAction,SIGNAL(triggered(bool)),this,SLOT(setCodecForVoiceBankActionSlot()));
    setCodecAction->setStatusTip(tr("为选中音源设置读取用文本编码。注意，这仅在本软件中有效。"));
    codecSubMenu->addAction(setCodecAction);

    codecSubMenu->addSeparator();

    auto convertCharacterCodecAction = new QAction(tr("对character.txt进行编码转换..."),codecSubMenu);
    connect(convertCharacterCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertCharacterCodecActionSlot()));
    convertCharacterCodecAction->setStatusTip(tr("在文件编码转换器中转换选中音源character.txt的编码。"));
    codecSubMenu->addAction(convertCharacterCodecAction);

    auto convertReadmeCodecAction = new QAction(tr("对readme.txt进行编码转换..."),codecSubMenu);
    connect(convertReadmeCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertReadmeCodecActionSlot()));
    convertReadmeCodecAction->setStatusTip(tr("在文件编码转换器中转换选中音源readme.txt的编码。"));
    codecSubMenu->addAction(convertReadmeCodecAction);

    auto convertWavFileNameCodecAction = new QAction(tr("对WAV文件名进行编码转换..."),codecSubMenu);
    connect(convertWavFileNameCodecAction,SIGNAL(triggered(bool)),this,SLOT(convertWavFileNameCodecActionSlot()));
    convertWavFileNameCodecAction->setStatusTip(tr("在文件编码转换器中转换选中音源的WAV文件名的编码。"));
    codecSubMenu->addAction(convertWavFileNameCodecAction);

    singleVoiceBankTableWidgetMenu->addMenu(codecSubMenu);

    auto engineMenu = new QMenu(tr("引擎相关"),singleVoiceBankTableWidgetMenu);

    auto moresamplerConfigEditAction = new QAction(tr("编辑该音源的Moresampler声库配置..."),engineMenu);
    connect(moresamplerConfigEditAction,SIGNAL(triggered(bool)),this,SLOT(moresamplerConfigEditActionSlot()));
    moresamplerConfigEditAction->setStatusTip(tr("编辑该声库的Moresampler声库配置。这些设置只有在您使用Moresampler时起效。"));
    engineMenu->addAction(moresamplerConfigEditAction);

    singleVoiceBankTableWidgetMenu->addMenu(engineMenu);

    createVoiceBanksCategoriesSubMenu();
    createVoiceBanksLabelsSubMenu();

    singleVoiceBankTableWidgetMenu->addSeparator();
    singleVoiceBankTableWidgetMenu->addMenu(voiceBankCategoriesSubMenu);
    singleVoiceBankTableWidgetMenu->addMenu(voiceBankLabelsSubMenu);
    singleVoiceBankTableWidgetMenu->addSeparator();

    auto ignoreAction = new QAction(tr("忽略选中的文件夹"),singleVoiceBankTableWidgetMenu);
    connect(ignoreAction,SIGNAL(triggered(bool)),this,SLOT(ignoreActionSlot()));
    ignoreAction->setStatusTip(tr("将选中的文件夹加入忽略文件夹列表。"));
    singleVoiceBankTableWidgetMenu->addAction(ignoreAction);

    auto reloadAction = new QAction(tr("重载选中音源"),singleVoiceBankTableWidgetMenu);
    connect(reloadAction,SIGNAL(triggered(bool)),this,SLOT(reloadVoiceBankActionSlot()));
    reloadAction->setStatusTip(tr("重新从硬盘加载选中音源。"));
    singleVoiceBankTableWidgetMenu->addAction(reloadAction);

    //生成多选菜单
    multipleVoiceBankTableWidgetMenu->clear();

    multipleVoiceBankTableWidgetMenu->addMenu(copySubMenu);
    multipleVoiceBankTableWidgetMenu->addMenu(codecSubMenu);
    multipleVoiceBankTableWidgetMenu->addSeparator();
    multipleVoiceBankTableWidgetMenu->addMenu(voiceBankCategoriesSubMenu);
    multipleVoiceBankTableWidgetMenu->addMenu(voiceBankLabelsSubMenu);
    multipleVoiceBankTableWidgetMenu->addAction(ignoreAction);
    multipleVoiceBankTableWidgetMenu->addAction(reloadAction);

}

void VoicebankManagerWindow::createVoiceBanksCategoriesSubMenu(){
    voiceBankCategoriesSubMenu->clear();
    voiceBankCategoriesActionGroup->deleteLater();
    voiceBankCategoriesActionGroup = new QActionGroup(this);

    auto addNewCategoryAction = new QAction(tr("新建一个分类..."),this);
    connect(addNewCategoryAction,SIGNAL(triggered(bool)),this,SLOT(addNewCategoryActionSlot()));
    voiceBankCategoriesSubMenu->addAction(addNewCategoryAction);

    voiceBankCategoriesSubMenu->addSeparator();
    auto noAction = new QAction(tr("未分类"),voiceBankCategoriesActionGroup);
    noAction->setCheckable(true);
    for (auto i : categoriesAndLabelsListWidget->getCategories())
    {
        auto action = new QAction(i,voiceBankCategoriesActionGroup);
        action->setCheckable(true);
    }
    connect(voiceBankCategoriesActionGroup,SIGNAL(triggered(QAction *)),this,SLOT(setCategoryActionsSlot(QAction*)));
    voiceBankCategoriesSubMenu->addActions(voiceBankCategoriesActionGroup->actions());
}

void VoicebankManagerWindow::createVoiceBanksLabelsSubMenu(){
    voiceBankLabelsSubMenu->clear();
    voiceBankLabelsActionGroup->deleteLater();
    voiceBankLabelsActionGroup = new QActionGroup(this);
    voiceBankLabelsActionGroup->setExclusive(false);

    auto addNewLabelAction = new QAction(tr("新建一个标签..."),this);
    connect(addNewLabelAction,SIGNAL(triggered(bool)),this,SLOT(addNewLabelActionSlot()));
    voiceBankLabelsSubMenu->addAction(addNewLabelAction);

    voiceBankLabelsSubMenu->addSeparator();

    for (auto i : categoriesAndLabelsListWidget->getLabels())
    {
        auto action = new QAction(i,voiceBankLabelsActionGroup);
        action->setCheckable(true);
    }
    connect(voiceBankLabelsActionGroup,SIGNAL(triggered(QAction *)),this,SLOT(setLabelActionSlot(QAction*)));
    voiceBankLabelsSubMenu->addActions(voiceBankLabelsActionGroup->actions());

}

void VoicebankManagerWindow::refreshCategoryAndLabelsActionsChecked()
{
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank)
    {
        for (auto i : voiceBankCategoriesActionGroup->actions())
        {
            i->setChecked(i->text() == voiceBank->getCategory());
            if (voiceBank->getCategory().isEmpty() && i->text() == tr("未分类"))
            {
                i->setChecked(true);
            }
        }
        for (auto i : voiceBankLabelsActionGroup->actions())
        {
            i->setChecked(voiceBank->getLabels().contains(i->text()));
        }
    }
}

void VoicebankManagerWindow::ignoreActionSlot(){
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank)
    {
        auto button = QMessageBox::warning(this,tr("确定？"),tr("确定要把该文件夹中加入忽略列表吗？"),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
        if (button == QMessageBox::Ok)
            MonitorFoldersScanner::getMonitorFoldersScanner()->addIgnoreVoiceBankFolder(voiceBank->getPath());
        auto clickedButton = QMessageBox::information(this,tr("忽略文件夹列表被更改"),tr("您更改了忽略文件夹列表，是否立即重载音源库列表？"),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksAndTable();
    }
}

void VoicebankManagerWindow::addNewLabelActionSlot(){
    auto newLabel = QInputDialog::getText(this,tr("输入新标签的名称"),tr("输入新标签的名称："));
    newLabel = newLabel.trimmed();
    if (!newLabel.isEmpty())
    {
        categoriesAndLabelsListWidget->addLabel(newLabel);
    }
    else
        return;
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank)
    {
        voiceBank->addLabel(newLabel);
    }
}
void VoicebankManagerWindow::setLabelActionSlot(QAction* action){
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank)
    {
        voiceBank->toggleLabelStatus(action->text());
    }
}
void VoicebankManagerWindow::setCategoryActionsSlot(QAction* action){
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank)
    {
        if (action->text() != tr("未分类"))
            voiceBank->setCategory(action->text());
        else
            voiceBank->setCategory("");
    }
}
void VoicebankManagerWindow::addNewCategoryActionSlot(){
    auto newCategory = QInputDialog::getText(this,tr("输入新分类的名称"),tr("输入新分类的名称："));
    newCategory = newCategory.trimmed();
    if (!newCategory.isEmpty())
    {
        categoriesAndLabelsListWidget->addCategory(newCategory);
    }
    else
        return;
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank)
    {
        voiceBank->setCategory(newCategory);
    }
}

Voicebank* VoicebankManagerWindow::getCurrentVoiceBank()
{
    return getCurrentVoiceBank(ui->voiceBanksTableView->currentIndex());
}

QList<Voicebank *> VoicebankManagerWindow::getSelectedVoiceBanks()
{
    auto selections = ui->voiceBanksTableView->selectionModel()->selectedRows();
    QList<Voicebank *> result;
    for (auto selection : selections)
    {
        result.append(getCurrentVoiceBank(selection));
    }
    return result;
}

Voicebank *VoicebankManagerWindow::getCurrentVoiceBank(const QModelIndex &current)
{
    return voiceBankHandler->getVoiceBank(current.row());
}

void VoicebankManagerWindow::openVoiceBankPathInExplorer()
{
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank){
        auto url = QUrl("file:" + voiceBank->getPath());
        QDesktopServices::openUrl(url);}

}
void VoicebankManagerWindow::openVoiceBankCharacterFileByOS(){
    auto voiceBank = getCurrentVoiceBank();
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
void VoicebankManagerWindow::openVoiceBankReadmeFileByOS(){
    auto voiceBank = getCurrentVoiceBank();
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
void VoicebankManagerWindow::copyVoiceBankPathtoClipboard()
{
    auto voiceBanks = getSelectedVoiceBanks();
    QStringList pathList{};
    for (auto voiceBank : voiceBanks)
    {
        pathList.append(QDir::toNativeSeparators(voiceBank->getPath()));
    }
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(pathList.join("\n"));
}
void VoicebankManagerWindow::copyVoiceBankCharacterFilePathtoClipboard(){
    auto voiceBanks = getSelectedVoiceBanks();
    for (auto voiceBank : voiceBanks){
        if (voiceBank)
        {
            if (!QFileInfo(voiceBank->getPath() + "character.txt").exists())
            {
                auto id = QMessageBox::information(this,tr("文件不存在"),tr("看起来音源“%1”的character.txt不存在。是否需要程序创建一个？").arg(voiceBank->getPath()),QMessageBox::Ok | QMessageBox::Abort,QMessageBox::Ok);
                if (id == QMessageBox::Ok)
                {
                    modifyVoiceBankName(voiceBank);
                }
                else
                    QMessageBox::information(this,tr("剪贴板仍会被更改"),tr("即使您没有要求程序创建character.txt，程序也将把该文件的路径复制到剪贴板。但是请注意，这个路径并没有指向有效的文件。"));
            }
        }
    }
    QStringList pathList{};
    for (auto voiceBank : voiceBanks)
    {
        pathList.append(QDir::toNativeSeparators(voiceBank->getPath() + "character.txt"));
    }
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(pathList.join("\n"));
}
void VoicebankManagerWindow::copyVoiceBankReadmeFilePathtoClipboard(){
    auto voiceBanks = getSelectedVoiceBanks();
    for (auto voiceBank : voiceBanks){
        if (voiceBank)
        {
            if (!QFileInfo(voiceBank->getPath() + "readme.txt").exists())
            {
                auto id = QMessageBox::information(this,tr("文件不存在"),tr("看起来音源“%1”的readme.txt不存在。是否需要程序创建一个？").arg(voiceBank->getPath()),QMessageBox::Ok | QMessageBox::Abort,QMessageBox::Ok);
                if (id == QMessageBox::Ok)
                {
                    QFile file(voiceBank->getPath() + "readme.txt");
                    file.open(QIODevice::WriteOnly);
                    file.close();
                }
                else
                    QMessageBox::information(this,tr("剪贴板仍会被更改"),tr("即使您没有要求程序创建readme.txt，程序也将把该文件的路径复制到剪贴板。但是请注意，这个路径并没有指向有效的文件。"));
            }
        }
    }
    QStringList pathList{};
    for (auto voiceBank : voiceBanks)
    {
        pathList.append(QDir::toNativeSeparators(voiceBank->getPath() + "character.txt"));
    }
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(pathList.join("\n"));
}
void VoicebankManagerWindow::setCodecForVoiceBankActionSlot(){
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank){
        auto dialog = new TextCodecSettingDialog(this,voiceBank);
        auto dialogCode = dialog->exec();
        if (dialogCode == 1){
            voiceBank->setTextCodecFollowDefault(dialog->getIsFollowDefaultCodec());
            voiceBank->setCharacterTextCodec(dialog->getCharacterTextCodec());
            voiceBank->setReadmeTextCodec(dialog->getReadmeTextCodec());
            voiceBank->setTextCodecAutoDetect(dialog->getIsAutoDetect());
            voiceBank->saveSettings();
            reloadVoiceBankActionSlot();
        }
    }
}
void VoicebankManagerWindow::convertCharacterCodecActionSlot(){
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank){
        auto path = voiceBank->getPath() + "character.txt";
        if (!QFileInfo(path).exists())
        {
            QMessageBox::warning(this,tr("character.txt不存在"),tr("您选定的音源不存在character.txt。所以无法进行转换操作。"));
            return;
        }
        auto sourceCodec = voiceBank->getCharacterTextCodec();
        auto targetCodec = Voicebank::getDefaultCharacterTextCodec();
        auto isDone = TextConvertHelper::processFileTextCodecConvert(path,sourceCodec,targetCodec,this);
        if (isDone)
        {
            voiceBank->setTextCodecFollowDefault(false);
            voiceBank->setCharacterTextCodec(targetCodec);
            voiceBank->saveSettings();
            reloadVoiceBankActionSlot();
        }
    }
}
void VoicebankManagerWindow::convertReadmeCodecActionSlot(){
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank){
        auto path = voiceBank->getPath() + "readme.txt";
        if (!QFileInfo(path).exists())
        {
            QMessageBox::warning(this,tr("readme.txt不存在"),tr("您选定的音源不存在readme.txt。所以无法进行转换操作。"));
            return;
        }
        auto sourceCodec = voiceBank->getReadmeTextCodec();
        auto targetCodec = Voicebank::getDefaultReadmeTextCodec();
        auto isDone = TextConvertHelper::processFileTextCodecConvert(path,sourceCodec,targetCodec,this);
        if (isDone)
        {
            voiceBank->setTextCodecFollowDefault(false);
            voiceBank->setReadmeTextCodec(targetCodec);
            voiceBank->saveSettings();
            reloadVoiceBankActionSlot();
        }
    }
}

void VoicebankManagerWindow::convertWavFileNameCodecActionSlot(){
    auto voiceBank = getCurrentVoiceBank();
    //voiceBank->readWavFileName();
    if (voiceBank){
        auto sourceCodec = voiceBank->getWavFileNameTextCodec();
        auto targetCodec = QTextCodec::codecForLocale();
        if (TextConvertHelper::processFileNameConvert(voiceBank->getWavFileNameRaw(),voiceBank->getWavFilePath(),tr("%1的WAV文件名").arg(voiceBank->getName()),sourceCodec,targetCodec,this))
        {
            voiceBank->clearWavFileReadStage();
            voiceBank->setWavFileNameTextCodec(targetCodec);
            QMessageBox::information(this,tr("转换成功完成"),tr("音源%1的WAV文件名均已从%2转换至%3。").arg(voiceBank->getName()).arg(QString::fromUtf8(sourceCodec->name())).arg(QString::fromUtf8(targetCodec->name())));
        }
    }
}

void VoicebankManagerWindow::reloadVoiceBankActionSlot(){
    auto voiceBank = getCurrentVoiceBank();
    if (voiceBank){
        voiceBank->reload();
        setVoiceBankInfomation(voiceBank);
    }
}

void VoicebankManagerWindow::on_actionMonitor_Folders_triggered()
{
    letUserModifyFolder(&MonitorFoldersScanner::getMonitorFolders,&MonitorFoldersScanner::setMonitorFolders,tr("监视文件夹列表"),{"./voice"});
}

void VoicebankManagerWindow::on_actionRefresh_triggered()
{
    loadVoiceBanksAndTable();
}

void VoicebankManagerWindow::on_actionDefault_TextCodec_triggered()
{
    auto dialog = new TextCodecSettingDialog(this);
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted){
        Voicebank::setDefaultCharacterTextCodec(dialog->getCharacterTextCodec());
        Voicebank::setDefaultReadmeTextCodec(dialog->getReadmeTextCodec());
        Voicebank::setDefalutTextCodecAutoDetect(dialog->getIsAutoDetect());
        auto clickedButton = QMessageBox::information(this,tr("默认文本读取编码被更改"),tr("您更改了默认的读取用文本编码，是否立即重载音源库列表？"),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksAndTable();
    }
    dialog->deleteLater();
}

void VoicebankManagerWindow::showVoiceBanksRows(const QList<int> &voiceBankIDs)
{
    int rowCount = voiceBankHandler->count();//获得行号
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

void VoicebankManagerWindow::dealFilters()
{
    auto byName = voiceBankHandler->findIDByNameOrPath(ui->searchLineEdit->text());
    QList<int> byCategory;
    if (currentCategoriesFilter.count() == 1)
        byCategory.append(voiceBankHandler->findIDByCategory(currentCategoriesFilter.at(0)));
    else if (currentCategoriesFilter.isEmpty())
        byCategory.append(voiceBankHandler->findIDByCategory(""));
    else
    {
        for (auto i : currentCategoriesFilter){
            byCategory = SetOperations::getUnion<int>({byCategory,voiceBankHandler->findIDByCategory(i)});
        }
    }
    QList<int> byLabel;
    if (currentLabelFilter.count() == 1)
        byLabel.append(voiceBankHandler->findIDByLabel(currentLabelFilter.at(0)));
    else if (currentLabelFilter.isEmpty())
        byLabel.append(voiceBankHandler->findIDByLabel(""));
    else
    {
        if (categoriesAndLabelsListWidget->getSelectionStrategy() == CategoriesAndLabelsListWidget::Intersection)
            byLabel.append(voiceBankHandler->findIDByLabel(""));
        for (auto i : currentLabelFilter){
            auto byLabeli = voiceBankHandler->findIDByLabel(i);
            switch (categoriesAndLabelsListWidget->getSelectionStrategy()){
            case CategoriesAndLabelsListWidget::Intersection:
                byLabel = SetOperations::getIntersection<int>({byLabel,byLabeli});
                break;
            case CategoriesAndLabelsListWidget::Union:
                byLabel = SetOperations::getUnion<int>({byLabel,byLabeli});
            }
        }
    }
    auto result = SetOperations::getIntersection<int>({byName,byCategory,byLabel});
    showVoiceBanksRows(result);
}

void VoicebankManagerWindow::on_searchLineEdit_textChanged(const QString &)
{
    dealFilters();
}

void VoicebankManagerWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void VoicebankManagerWindow::on_actionAbout_triggered()
{
    auto dialog = new AboutDialog(tr("音源管理器 v%1").arg(voicebankManagerVersion),QImage(),
                                  //关于
                                  tr("<p>为管理适用于UTAU歌声合成应用程序的声音资料库写的一个辅助工具。</p>"
                                     "<p>版权所有 2018-2019 shine_5402</p>"
                                     "<p>本程序是 Leaf Open UTAU Project 的一部分。</p>"
                                     "<p>Github项目页：<a href=\"https://github.com/shine5402/LeafOpenUTAUQt\">Leaf OpenUTAU Qt Project</a></p>"),
                                  //作者
                                  tr("<h4>主要维护者</h4>"
                                     "<p>shine_5402</p>"
                                     "<h4>联系方式</h4>"
                                     "<p>邮箱：shine_5402@126.com/shine_5402@live.cn/shine5402@gmail.com/shine_5402@qq.com</p>"
                                     "<p>QQ：1952784042</p>"
                                     "<p>微博/Twitter @shine_5402</p>"
                                     "<p>Github @shine5402</p>"
                                     "<b>如果需要反馈程序的BUG，或者想要提出对新特性的请求，请直接在Github项目页提交issue。</b>"),
                                  //致谢
                                  tr("<p>首先先是感谢在UTAU坑里遇到的所有朋友，特别是哈鲁鲁的UTAU群里第一时间使用的大家，没有你们我不可能坚持写出这个工具。名单太长，这里就不列举了。</p>"
                                     "<p>然后是感谢译者（当然也是亲友）隋卞帮忙做英文翻译，我的英语真的很烂……</p>"
                                     "<p>接着要感谢在第三方代码那页里提到的所有第三方作者，没有他们我肯定要花上更多功夫，甚至无法完成。</p>"
                                     "<p>当然最后，还有使用这个软件的你。感谢您的使用！</p>"),
                                  //译者
                                  tr("<h4>本程序译者</h4>"
                                     "<ul>"
                                     "<li>English（英文）：隋卞</li>"
                                     "</ul>"
                                     "<p>如果你想要（当然，有能力最好）为本程序增加你的语言版本，请联系我！</p>"),
                                  //许可
                                  tr("<h4>简述</h4>"
                                     "<p>本程序大体上是以<a href=\"https://www.apache.org/licenses/LICENSE-2.0\">Apache License, Version 2.0</a>分发的，除了某些文件因其代码来源的原因使用了<a href=\"http://www.gnu.org/licenses/gpl-3.0.html\">GNU 通用公共许可证 版本3</a>。<br/>"
                                     "你可以直接通过上述链接（需要Internet）查看这些许可，也可继续向下翻阅。<br/>"
                                     "你可以通过源文件中的说明来辨别文件使用的许可。</p>"
                                     "<h4>Apache License, Version 2.0</h4>"
                                     "<pre>%1</pre>"
                                     "<h4>GNU General Public License, Version 3</h4>"
                                     "<pre>%2</pre>")
                                  .arg([] () -> QString {
                                           QFile file(":/license/apachev2");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }())
                                  .arg([] () -> QString {
                                           QFile file(":/license/gplv3");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }()
                                       ),
                                  tr("<i>你可以直接通过库后所附许可的链接查看每个库的对应许可（需要Internet），也可继续向下翻阅。</i>"
                                     "<h4>本程序使用了以下第三方程序库：</h4>"
                                     "<ul>"
                                     "<li>Qt，版本 %1，作者：The Qt Company Ltd.(<a href=\"http://www.gnu.org/licenses/lgpl-3.0.html\">GNU LGPL v3</a>)</li>"
                                     "<li>LeafLogger，作者：shine_5402 (<a href=\"https://www.apache.org/licenses/LICENSE-2.0\">Apache License, Version 2.0</a>)</li>"
                                     "<li>TextCodecUtils，作者：shine_5402 (<a href=\"https://www.apache.org/licenses/LICENSE-2.0\">Apache License, Version 2.0</a>)</li>"
                                     "<li>ImageCropper，作者：dimkanovikov 与 shine_5402 (<a href=\"http://www.gnu.org/licenses/lgpl-3.0.html\">GNU LGPL v3</a>)</li>"
                                     "<li>libchardet，版本 %2，作者：JoungKyun.Kim (<a href=\"https://www.mozilla.org/en-US/MPL/1.1/\">MPL 1.1</a> or <a href=\"http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html\">LGPL 2.1</a>)</li>"
                                     "</ul>"
                                     "<h4>本程序参考、借用了以下项目的部分源代码</h4>"
                                     "<ul>"
                                     "<li>qBittorrent，作者：qBittorrent Project (<a href=\"http://www.gnu.org/licenses/old-licenses/gpl-2.0.html\">GNU GPL v2</a> with some special exception)"
                                     "</ul>"
                                     "<h4>Apache License, Version 2.0</h4>"
                                     "<pre>%3</pre>"
                                     "<h4>GNU General Public License, Version 3</h4>"
                                     "<pre>%4</pre>"
                                     "<h4>GNU Lesser General Public License, Version 3</h4>"
                                     "<pre>%5</pre>"
                                     "<h4>MOZILLA PUBLIC LICENSE, Version 1.1</h4>"
                                     "<pre>%6</pre>"
                                     "<h4>GNU Lesser General Public License, Version 2.1</h4>"
                                     "<pre>%7</pre>"
                                     "<h4>GNU General Public License, Version 2</h4>"
                                     "<pre>%8</pre>"
                                     "<h4>qBittorrent special exception</h4>"
                                     "<pre>%9</pre>").arg(QT_VERSION_STR).arg(QChardet::libchardetVersion())
                                  .arg([] () -> QString {
                                           QFile file(":/license/apachev2");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }())
                                  .arg([] () -> QString {
                                           QFile file(":/license/gplv3");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }()
                                       )
                                  .arg([] () -> QString {
                                           QFile file(":/license/lgplv3");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }())
                                  .arg([] () -> QString {
                                           QFile file(":/license/mplv1.1");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }())
                                  .arg([] () -> QString {
                                           QFile file(":/license/lgplv2.1");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }())
                                  .arg([] () -> QString {
                                           QFile file(":/license/gplv2");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }())
                                  .arg([] () -> QString {
                                           QFile file(":/license/qse");
                                           file.open(QFile::ReadOnly);
                                           return QString::fromUtf8(file.readAll());
                                       }())
                                  ,this
                                  );
    dialog->exec();
}

void VoicebankManagerWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,tr("关于 Qt"));
}

void VoicebankManagerWindow::on_actionSet_Thread_Pool_Max_Count_triggered()
{
    bool ok = false;
    auto count = QInputDialog::getInt(this,tr("设定线程池的最大大小"),tr("（高级）该设置改变程序读取音源库时的最大线程数。请确保您在知道自己在做什么之后再更改此项设置。"),Voicebank::getThreadPoolMaxThreadCount(),1,2147483647,1,&ok);
    if (ok){
        Voicebank::setThreadPoolMaxThreadCount(count);
        ui->statusbar->showMessage(tr("线程池大小已经被设置为%1").arg(count));
    }
}



void VoicebankManagerWindow::on_voiceBanksTableView_customContextMenuRequested(const QPoint &)
{
    refreshCategoryAndLabelsActionsChecked();
    auto voicebanks = getSelectedVoiceBanks();
    if (voicebanks.count() == 1) {
        if (voicebanks.at(0))
            singleVoiceBankTableWidgetMenu->exec(QCursor::pos());
    }
    else
    {
        multipleVoiceBankTableWidgetMenu->exec(QCursor::pos());
    }
}


void VoicebankManagerWindow::resetSamplePlayer()
{
    samplePlayer->stop();
    samplePlayer->setMedia(QMediaContent());
    ui->playSamplebutton->setText(tr("播放样例"));
}

void VoicebankManagerWindow::onVoiceBankViewSelectionChanged(const QItemSelection &, const QItemSelection &)
{
    auto voiceBanks = getSelectedVoiceBanks();
    Voicebank* voiceBank = nullptr;
    if (voiceBanks.count() == 0)
        voiceBank = getCurrentVoiceBank();
    else if (voiceBanks.count() == 1)
        voiceBank = voiceBanks.at(0);
    else {
        ui->voiceBankBriefInfomationWidget->setVisible(false);
    }
    if (voiceBank){
        setVoiceBankInfomation(voiceBank);
        resetSamplePlayer();

    }
}

void VoicebankManagerWindow::moresamplerConfigEditActionSlot()
{
    auto voiceBank = getCurrentVoiceBank();
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

void VoicebankManagerWindow::on_actionEdit_Global_MoresamplerConfig_triggered()
{
    QStringList configFilePaths;
    for (auto path : MonitorFoldersScanner::getMonitorFoldersScanner()->getMonitorFolders())
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
    auto dialog = new QFileDialog(this);
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setWindowTitle(tr("打开一个Moresampler全局配置文件"));
    dialog->setNameFilter(tr("Moresampler 配置文件 (moreconfig.txt)"));
    QString filePath;
    if (dialog->exec())
        filePath = dialog->selectedFiles().at(0);
    if (!filePath.isEmpty()){
        auto dialog = new MoresamplerConfigsDialog(filePath,MoresamplerConfigReader::Global,this);
        dialog->exec();
    };
}

void VoicebankManagerWindow::modifyVoiceBankName(Voicebank * voiceBank)
{
    if (voiceBank)
    {
        bool ok = false;
        auto name = QInputDialog::getText(this,tr("为音源指定一个新名称"),tr("为路径为%1的音源指定一个新名称（程序会自动转换编码）：").arg(voiceBank->getPath()),QLineEdit::Normal,voiceBank->getName(),&ok);
        if (ok)
        {
            try{
                voiceBank->setName(name);
                ui->statusbar->showMessage(tr("已将路径为%1的音源的名称设置为%2。").arg(voiceBank->getPath()).arg(voiceBank->getName()));
                setVoiceBankInfomation(voiceBank);
            }
            catch(Voicebank::FileCanNotOpen& e){
                QMessageBox::critical(this,tr("文件无法被打开"),tr("有一个文件无法被打开。Qt提供的错误字符串为%1").arg(e.QFileError()));
            }
            catch(FileIOWithCodecHelper::FileNotExists&){
                setVoiceBankInfomation(voiceBank);
                auto a = voiceBank->getName();
                ui->statusbar->showMessage(tr("路径为%1的音源的character.txt不存在。程序已经自动创建并将名称设置为%1。").arg(voiceBank->getName()));
            }
        }
    }
}

void VoicebankManagerWindow::modifyNameActionSlot()
{
    auto voiceBank = getCurrentVoiceBank();
    modifyVoiceBankName(voiceBank);
}

void VoicebankManagerWindow::modifyIconActionSlot()
{
    auto voiceBank = getCurrentVoiceBank();
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
            auto dialog = new VoicebankIconCropDialog(voiceBank,rawImageFilePath,this);
            auto id = dialog->exec();
            if (id == QDialog::Accepted)
            {
                reloadVoiceBankActionSlot();
            }
        }
    }
}

void VoicebankManagerWindow::on_actionchoose_a_voicebank_randomly_triggered()
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

void VoicebankManagerWindow::onBackupImageFileBecauseExists(Voicebank *voicebank)
{
    ui->statusbar->showMessage(tr("备份了%1原先的图标，因为目标文件名已存在。").arg(voicebank->getName()));
}

void VoicebankManagerWindow::onCannotBackupImageFile(Voicebank *voicebank)
{
    QMessageBox::critical(this,tr("无法备份"),tr("因为重名，程序尝试备份%1原先的图标，但是遇到错误无法完成，操作终止。").arg(voicebank->getName()));
}

void VoicebankManagerWindow::on_playSamplebutton_clicked()
{
    if (!(samplePlayer->state() == QMediaPlayer::State::PlayingState)){
        samplePlayer->stop();
        auto voiceBank = getCurrentVoiceBank();
        if (voiceBank)
        {
            auto sample = voiceBank->getSampleFileName();
            if (auto fileInfo = QFileInfo(sample);!fileInfo.exists())
            {
                QMessageBox::critical(this,tr("找不到示例音频"),tr("找不到可用的示例音频文件。"));
            }
            samplePlayer->setAudioRole(QAudio::Role::MusicRole);\
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
            ui->playSamplebutton->setText(tr("停止"));
        }
    }
    else {
        resetSamplePlayer();
    }
}
void VoicebankManagerWindow::onSamplePlayerPositionChange(qint64 position)
{
    auto sampleDuration = samplePlayer->duration();
    qreal positionRate = static_cast<double>(position) / ((sampleDuration == 0)?INT_MAX:sampleDuration);
    samplePlayerProgress->setValue(static_cast<int>(INT_MAX * positionRate));
}
void VoicebankManagerWindow::onSamplePlayerStateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::State::StoppedState){
        ui->statusbar->removeWidget(samplePlayerProgress);
        ui->statusbar->clearMessage();
        resetSamplePlayer();
    }
}

void VoicebankManagerWindow::changeEvent(QEvent *e)
{
    /*!
      继承自 QWidget 的 QWidget::changeEvent(QEvent *e) 。\n
      此函数用于处理语言变化后的相关操作。
    */
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        createVoiceBanksTableMenu();
        break;
    default:
        break;
    }
}

void VoicebankManagerWindow::on_actionFor_text_file_triggered()
{
    auto path = QFileDialog::getOpenFileName(this,tr("打开一个文本文件"));
    if (path.isEmpty())
        return;
    auto sourceCodec = QTextCodec::codecForLocale();
    auto targetCodec = QTextCodec::codecForLocale();
    TextConvertHelper::processFileTextCodecConvert(path,sourceCodec,targetCodec,this);
}

void VoicebankManagerWindow::on_actionFor_File_Name_triggered()
{
    auto path = QFileDialog::getExistingDirectory(this,tr("打开一个文件夹"));
    if (path.isEmpty())
        return;
    QStringList fileNames;
    QStringList filePath;
    QByteArrayList fileNameRaw;
    QDir dir(path);
    fileNames.append(dir.entryList(QDir::Dirs | QDir::Files|QDir::NoDotAndDotDot));
    for (auto fileName : fileNames)
    {
        filePath.append(path + "/" + fileName);
    }
    QTextEncoder encoder(QTextCodec::codecForLocale());
    for (auto name : fileNames)
    {
        auto raw = encoder.fromUnicode(name);
        fileNameRaw.append(raw);
    }
    auto sourceCodec = QTextCodec::codecForLocale();
    auto targetCodec = QTextCodec::codecForLocale();
    if (TextConvertHelper::processFileNameConvert(fileNameRaw,filePath,tr("转换%1下的文件名").arg(path),sourceCodec,targetCodec,this))
        QMessageBox::information(this,tr("转换成功"),tr("对%1下的文件名的从%2到%3的转换成功完成。").arg(path).arg(QString::fromUtf8(sourceCodec->name())).arg(QString::fromUtf8(targetCodec->name())));
}

void VoicebankManagerWindow::on_voicebankImage_customContextMenuRequested(const QPoint &)
{
    auto menu = new QMenu(this);
    auto modifyIconAction = new QAction(tr("修改音源的图标..."),menu);
    connect(modifyIconAction,SIGNAL(triggered(bool)),this,SLOT(modifyIconActionSlot()));
    modifyIconAction->setStatusTip(tr("为该音源指定一个新图标。"));
    menu->addAction(modifyIconAction);
    menu->popup(QCursor::pos());
}

void VoicebankManagerWindow::onCurrentCategoriesChanged(const QStringList &current)
{
    currentCategoriesFilter = current;
    dealFilters();
}

void VoicebankManagerWindow::onCurrentLabelsChanged(const QStringList &current)
{
    currentLabelFilter = current;
    dealFilters();
}

void VoicebankManagerWindow::on_actionuse_old_watched_folder_scan_strategy_toggled(bool checked)
{
    MonitorFoldersScanner::getMonitorFoldersScanner()->setUseOldFolderScan(checked);
}

void VoicebankManagerWindow::on_actionshow_more_infomation_in_total_count_label_toggled(bool checked)
{
    showMoreInformationInTotalCountLabel = checked;
    updateVoiceBankCountLabel();
}

void VoicebankManagerWindow::letUserModifyFolder(std::function<QStringList(MonitorFoldersScanner*)>getFunc, std::function<void(MonitorFoldersScanner*,const QStringList&)>setFunc, const QString& name, const QStringList& defaultList, const QList<FoldersSettingDialog::AllowedPrefix>& allowedPrefix)
{
    auto dialog = new FoldersSettingDialog(getFunc(MonitorFoldersScanner::getMonitorFoldersScanner()),tr("设定%1：").arg(name),tr("%1设定").arg(name),this,defaultList,allowedPrefix);
    auto dialogCode = dialog->exec();
    if (dialogCode == 1 && getFunc(MonitorFoldersScanner::getMonitorFoldersScanner()) != dialog->getFolders()){
        setFunc(MonitorFoldersScanner::getMonitorFoldersScanner(),dialog->getFolders());
        auto clickedButton = QMessageBox::information(this,tr("%1被更改").arg(name),tr("您更改了%1，是否立即重载音源库列表？").arg(name),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksAndTable();
    }
    dialog->deleteLater();
}

void VoicebankManagerWindow::on_actionOutside_VoiceBanks_triggered()
{
    letUserModifyFolder(std::mem_fn(&MonitorFoldersScanner::getOutsideVoiceBankFolders),std::mem_fn(&MonitorFoldersScanner::setOutsideVoiceBankFolders),tr("外部音源文件夹列表"));
}

void VoicebankManagerWindow::on_actionIgnored_folders_triggered()
{
    letUserModifyFolder(std::mem_fn(&MonitorFoldersScanner::getIgnoreVoiceBankFolders),std::mem_fn(&MonitorFoldersScanner::setIgnoreVoiceBankFolders),tr("忽略文件夹列表"),QStringList(),{{"*",tr("子文件夹不包括"),tr("在路径前使用“*”前缀会使VoiceBankManager在扫描时同时忽略其子文件夹。")}});
}

void VoicebankManagerWindow::on_actionView_scan_details_triggered()
{
    auto html = tr("<h4>已忽略的文件夹</h4>"
                   "<pre>%1</pre>"
                   "<h4>不是音源的文件夹</h4>"
                   "<pre>%2</pre>"
                   "<h4>手动添加的音源文件夹</h4>"
                   "<pre>%3</pre>"
                   "<h4>子文件夹递归确定得到的声库文件夹</h4>"
                   "<pre>%4</pre>")
            .arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getIgnoredVoiceBankFolders().join("\n"))
            .arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getNotVoiceBankPaths().join("\n"))
            .arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getOutsideVoiceBankFolders().join("\n"))
            .arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getScannedSubFolders().join("\n"));
    auto dialog = new ShowHTMLDialog(html,tr("音源文件夹扫描详情"),this);
    dialog->exec();
}
