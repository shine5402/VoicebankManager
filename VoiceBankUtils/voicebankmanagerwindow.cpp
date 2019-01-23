#include "voicebankmanagerwindow.h"
#include "ui_voicebankmanagerwindow.h"
//TODO:重构 将Dialog完成后的代码迁移至继承的accept和reject。

VoiceBankManagerWindow::VoiceBankManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VoiceBankManagerWindow)
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
    //确保readmeTextBroswer的背景与父统一
    auto readmeTextBroswerPattle = ui->voicebankReadmeTextBrowser->palette();
    readmeTextBroswerPattle.setBrush(QPalette::Base,readmeTextBroswerPattle.window());
    ui->voicebankReadmeTextBrowser->setPalette(readmeTextBroswerPattle);

    //设置TableView
    voiceBankTableModel = new VoiceBankTableModel(voiceBankHandler);
    ui->voiceBanksTableView->setModel(voiceBankTableModel);
    ui->voiceBanksTableView->horizontalHeader()->setSortIndicator(VoiceBankTableModel::TableColumns::Name,Qt::SortOrder::AscendingOrder);
    connect(ui->voiceBanksTableView->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),this,SLOT(onVoiceBankViewCurrentChanged(const QModelIndex &, const QModelIndex &)));

    //连接Handler和主窗口的信号与槽
    connect(voiceBankHandler,SIGNAL(backupImageFileBecauseExists(VoiceBank*)),this,SLOT(onBackupImageFileBecauseExists(VoiceBank *)));
    connect(voiceBankHandler,SIGNAL(cannotBackupImageFile(VoiceBank*)),this,SLOT(onCannotBackupImageFile(VoiceBank*)));
    //connect(voiceBankHandler,SIGNAL(aVoiceBankReadDone(VoiceBank*)),this,SLOT(voiceBankReadDoneSlot(VoiceBank*)));
    connect(voiceBankHandler,SIGNAL(voiceBanksReadDone()),this,SLOT(setUIAfterVoiceBanksReadDone()));
    connect(voiceBankHandler,SIGNAL(useOldFolderScanChanged()),this,SLOT(onUseOldFolderScanChanged()));

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

    loadWindowStatus();

    //连接分类和标签相关信号与handler
    connect(voiceBankHandler,SIGNAL(categoriesChanged()),categoriesAndLabelsListWidget,SLOT(readCategoriesFromVoicebankHandler()));
    connect(categoriesAndLabelsListWidget,SIGNAL(categoriesChanged()),this,SLOT(createVoiceBanksCategoriesSubMenu()));
    connect(voiceBankHandler,SIGNAL(labelsChanged()),categoriesAndLabelsListWidget,SLOT(readLabelsFromVoiceBankHandler()));
    connect(categoriesAndLabelsListWidget,SIGNAL(labelsChanged()),this,SLOT(createVoiceBanksLabelsSubMenu()));
    connect(categoriesAndLabelsListWidget,SIGNAL(currentCategoriesChanged(QStringList)),this,SLOT(onCurrentCategoriesChanged(const QStringList&)));
    connect(categoriesAndLabelsListWidget,SIGNAL(currentLabelsChanged(QStringList)),this,SLOT(onCurrentLabelsChanged(const QStringList&)));
    connect(categoriesAndLabelsListWidget,SIGNAL(labelSelectionStrategyChanged()),this,SLOT(dealFilters()));

    showMoreInformationInTotalCountLabel = settings.value("VoiceBankManager/showMoreInformationInTotalCountLabel",true).toBool();
    ui->actionshow_more_infomation_in_total_count_label->setChecked(showMoreInformationInTotalCountLabel);

}


void VoiceBankManagerWindow::loadVoiceBanksAndTable()
{
    /*!
      加载音源库列表，并填充窗口中的表格。\n
       VoiceBankManagerWindow 会自动处理相关的UI变化，所以在合适的时机调用该函数即可。\n
      如果您不是在 VoiceBankManagerWindow 打开之时加载音源库，您可以直接使用 VoiceBankHandler::readVoiceBanksFromMonitorFolders() 。
    */
    voiceBankTableModel->clearEmitter();
    voiceBankHandler->clear();
    //ui->voiceBanksTableView->setEnabled(false);
    ui->categoryAndLabelsAndListSplitter->setEnabled(false);
    ui->searchLineEdit->setEnabled(false);
    ui->voicebankCountLabel->setText(tr("加载中"));
    voiceBankHandler->readVoiceBanksFromMonitorFolders();
}

void VoiceBankManagerWindow::dealLanguageMenuAutoAndDontStates(){
    if (ui->actionAuto_detect->isChecked())
    {
        autoDetectTranslate();
    }
    else if (ui->actionDon_t_translate->isChecked())
    {
        removeAllTranslators();
    }
}
void VoiceBankManagerWindow::dealLanguageMenuLoadFile(){
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
void VoiceBankManagerWindow::autoDetectTranslate(){
    removeAllTranslators();
    auto translator = new QTranslator(this);
    auto success = translator->load(QLocale(),"LeafOpenUTAUQt",".","./translations",".qm");
    LeafLogger::LogMessage(QString("QLocale detected:%1").arg(QLocale::system().name()));
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
void VoiceBankManagerWindow::removeAllTranslators(){
    LeafLogger::LogMessage("删除所有翻译。");
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


VoiceBankManagerWindow::~VoiceBankManagerWindow()
{
    /*!
       VoiceBankManagerWindow 的析构函数。它将自动保存窗口状态，监视文件夹等设置。
     */
    saveWindowStatus();
    delete ui;

    QSettings settings;
    settings.setValue("VoiceBankManager/showMoreInformationInTotalCountLabel",showMoreInformationInTotalCountLabel);
}

void VoiceBankManagerWindow::loadWindowStatus()
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
        //ui->categoryAndLabelsAndListSplitter->insertWidget(0,categoriesAndLabelsListWidget);
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

void VoiceBankManagerWindow::saveWindowStatus()
{
    QSettings settings;
    settings.setValue("VoiceBankManager/WindowGeometry",saveGeometry());
    settings.setValue("VoiceBankManager/categoryAndLabelsAndListSplitterState",ui->categoryAndLabelsAndListSplitter->saveState());
    settings.setValue("VoiceBankManager/informationAndListSplitterState",ui->informationAndListSplitter->saveState());
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
    if (voiceBank->hasTextCodecAutoDetected())
    {
        ui->voicebankReadmeTextBrowser->append(tr("<p style=\"color:blue\">自动探测后程序使用的文本编码：character.txt：%1。readme.txt：%2</p>").arg(QString::fromUtf8(voiceBank->getCharacterTextCodec()->name())).arg(QString::fromUtf8(voiceBank->getReadmeTextCodec()->name())));
    }
    ui->voicebankReadmeTextBrowser->append(QString("<p><pre style=\"color:black\">%1</pre></p>").arg(voiceBank->getReadme()));
    ui->voicebankReadmeTextBrowser->moveCursor(QTextCursor::Start);
}

void VoiceBankManagerWindow::updateVoiceBankCountLabel()
{

    if (voiceBankHandler->count() != 0){
        if (!showMoreInformationInTotalCountLabel)
            ui->voicebankCountLabel->setText(tr("共 %1 个").arg(voiceBankHandler->count()));
        else if (!MonitorFoldersScanner::getMonitorFoldersScanner()->isUseOldFolderScan())
            ui->voicebankCountLabel->setText(tr("共 %1 个（忽略 %2 个，不是音源文件夹的 %3 个，子文件夹递归得到 %4 个）").arg(voiceBankHandler->count()).arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getIgnoredVoiceBankFolders().count()).arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getNotVoiceBankPaths().count()).arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getScannedSubFolders().count()));
        else
            ui->voicebankCountLabel->setText(tr("共 %1 个（忽略 %2 个）").arg(voiceBankHandler->count()).arg(MonitorFoldersScanner::getMonitorFoldersScanner()->getIgnoredVoiceBankFolders().count()));
        voiceBankTableModel->sort(VoiceBankTableModel::TableColumns::Name,Qt::SortOrder::AscendingOrder);}
    else
        ui->voicebankCountLabel->setText(tr("没有音源。"));
}

void VoiceBankManagerWindow::setUIAfterVoiceBanksReadDone()
{
    // ui->voiceBanksTableView->setEnabled(true);
    ui->categoryAndLabelsAndListSplitter->setEnabled(true);
    ui->searchLineEdit->setEnabled(true);
    updateVoiceBankCountLabel();
    ui->voiceBankBriefInfomationWidget->setVisible(false);
    categoriesAndLabelsListWidget->readCategoriesFromVoicebankHandler();
    categoriesAndLabelsListWidget->readLabelsFromVoiceBankHandler();

}

void VoiceBankManagerWindow::onUseOldFolderScanChanged()
{

}

#ifndef NDEBUG
void VoiceBankManagerWindow::debugFunction()
{

}


#endif

void VoiceBankManagerWindow::createVoiceBanksTableMenu()
{
    voiceBankCategoriesSubMenu = new QMenu(tr("分类"),this);
    voiceBankLabelsSubMenu = new QMenu(tr("标签"),this);
    voiceBanksTableWidgetMenu->clear();

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

    createVoiceBanksCategoriesSubMenu();
    createVoiceBanksLabelsSubMenu();

    voiceBanksTableWidgetMenu->addSeparator();
    voiceBanksTableWidgetMenu->addMenu(voiceBankCategoriesSubMenu);
    voiceBanksTableWidgetMenu->addMenu(voiceBankLabelsSubMenu);
    voiceBanksTableWidgetMenu->addSeparator();

    auto ignoreAction = new QAction(tr("忽略该文件夹"),this);
    connect(ignoreAction,SIGNAL(triggered(bool)),this,SLOT(ignoreActionSlot()));
    ignoreAction->setStatusTip(tr("将该文件夹加入忽略文件夹列表。"));
    voiceBanksTableWidgetMenu->addAction(ignoreAction);

    auto reloadAction = new QAction(tr("重载此音源"),this);
    connect(reloadAction,SIGNAL(triggered(bool)),this,SLOT(reloadVoiceBankActionSlot()));
    reloadAction->setStatusTip(tr("重新从硬盘加载此音源。"));
    voiceBanksTableWidgetMenu->addAction(reloadAction);

}

void VoiceBankManagerWindow::createVoiceBanksCategoriesSubMenu(){
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

void VoiceBankManagerWindow::createVoiceBanksLabelsSubMenu(){
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

void VoiceBankManagerWindow::ignoreActionSlot(){
    auto voiceBank = getSelectedVoiceBank();
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

void VoiceBankManagerWindow::addNewLabelActionSlot(){
    auto newLabel = QInputDialog::getText(this,tr("输入新标签的名称"),tr("输入新标签的名称："));
    newLabel = newLabel.trimmed();
    if (!newLabel.isEmpty())
    {
        categoriesAndLabelsListWidget->addLabel(newLabel);
    }
    else
        return;
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank)
    {
        voiceBank->appendLabel(newLabel);
    }
}
void VoiceBankManagerWindow::setLabelActionSlot(QAction* action){
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank)
    {
        voiceBank->toggleLabelStatus(action->text());
    }
}
void VoiceBankManagerWindow::setCategoryActionsSlot(QAction* action){
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank)
    {
        if (action->text() != tr("未分类"))
            voiceBank->setCategory(action->text());
        else
            voiceBank->setCategory("");
    }
}
void VoiceBankManagerWindow::addNewCategoryActionSlot(){
    auto newCategory = QInputDialog::getText(this,tr("输入新分类的名称"),tr("输入新分类的名称："));
    newCategory = newCategory.trimmed();
    if (!newCategory.isEmpty())
    {
        categoriesAndLabelsListWidget->addCategory(newCategory);
    }
    else
        return;
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank)
    {
        voiceBank->setCategory(newCategory);
    }
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
            voiceBank->setTextCodecFollowDefault(dialog->getIsFollowDefaultCodec());
            voiceBank->setCharacterTextCodec(dialog->getCharacterTextCodec());
            voiceBank->setReadmeTextCodec(dialog->getReadmeTextCodec());
            voiceBank->setTextCodecAutoDetect(dialog->getIsAutoDetect());
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
        auto sourceCodec = voiceBank->getCharacterTextCodec();
        auto targetCodec = VoiceBank::getDefaultCharacterTextCodec();
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
void VoiceBankManagerWindow::convertReadmeCodecActionSlot(){
    auto voiceBank = getSelectedVoiceBank();
    if (voiceBank){
        auto path = voiceBank->getPath() + "readme.txt";
        if (!QFileInfo(path).exists())
        {
            QMessageBox::warning(this,tr("readme.txt不存在"),tr("您选定的音源不存在readme.txt。所以无法进行转换操作。"));
            return;
        }
        auto sourceCodec = voiceBank->getReadmeTextCodec();
        auto targetCodec = VoiceBank::getDefaultReadmeTextCodec();
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

void VoiceBankManagerWindow::convertWavFileNameCodecActionSlot(){
    auto voiceBank = getSelectedVoiceBank();
    //voiceBank->readWavFileName();
    if (voiceBank){
        auto sourceCodec = voiceBank->getWavFileNameTextCodec();
        auto targetCodec = QTextCodec::codecForLocale();
        auto a = voiceBank->getWavFileNameRaw();
        auto b = voiceBank->getWavFilePath();
        auto c = tr("%1的WAV文件名").arg(voiceBank->getName());
        if (TextConvertHelper::processFileNameConvert(voiceBank->getWavFileNameRaw(),voiceBank->getWavFilePath(),tr("%1的WAV文件名").arg(voiceBank->getName()),sourceCodec,targetCodec,this))
        {
            voiceBank->clearWavFileReadStage();
            voiceBank->setWavFileNameTextCodec(targetCodec);
            QMessageBox::information(this,tr("转换成功完成"),tr("音源%1的WAV文件名均已从%2转换至%3。").arg(voiceBank->getName()).arg(QString::fromUtf8(sourceCodec->name())).arg(QString::fromUtf8(targetCodec->name())));
        }
    }
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
    letUserModifyFolder(&MonitorFoldersScanner::getMonitorFolders,&MonitorFoldersScanner::setMonitorFolders,tr("监视文件夹列表"),{"./voice"});
}

void VoiceBankManagerWindow::on_actionRefresh_triggered()
{
    loadVoiceBanksAndTable();
}

void VoiceBankManagerWindow::on_actionDefault_TextCodec_triggered()
{
    auto dialog = new TextCodecSettingDialog(this);
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted){
        VoiceBank::setDefaultCharacterTextCodec(dialog->getCharacterTextCodec());
        VoiceBank::setDefaultReadmeTextCodec(dialog->getReadmeTextCodec());
        VoiceBank::setDefalutTextCodecAutoDetect(dialog->getIsAutoDetect());
        auto clickedButton = QMessageBox::information(this,tr("默认文本读取编码被更改"),tr("您更改了默认的读取用文本编码，是否立即重载音源库列表？"),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksAndTable();
    }
    dialog->deleteLater();
}

void VoiceBankManagerWindow::showVoiceBanksRows(const QList<int> &voiceBankIDs)
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

void VoiceBankManagerWindow::dealFilters()
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

void VoiceBankManagerWindow::on_searchLineEdit_textChanged(const QString &)
{
    dealFilters();
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
                                           "<li>libchardet by JoungKyun.Kim (MPL 1.1 or LGPL 2.1)</li>"
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

void VoiceBankManagerWindow::refreshCategoryAndLabelsActionsChecked()
{
    auto voiceBank = getSelectedVoiceBank();
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
        voiceBanksTableWidgetMenu->exec(QCursor::pos());
    }
}

void VoiceBankManagerWindow::on_voiceBanksTableView_customContextMenuRequested(const QPoint &)
{
    refreshCategoryAndLabelsActionsChecked();
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

void VoiceBankManagerWindow::modifyNameActionSlot()
{
    auto voiceBank = getSelectedVoiceBank();
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
        auto sample = voiceBank->getSampleFileName();
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

void VoiceBankManagerWindow::changeEvent(QEvent *e)
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

void VoiceBankManagerWindow::on_actionFor_text_file_triggered()
{
    auto path = QFileDialog::getOpenFileName(this,tr("打开一个文本文件"));
    if (path.isEmpty())
        return;
    auto sourceCodec = QTextCodec::codecForLocale();
    auto targetCodec = QTextCodec::codecForLocale();
    TextConvertHelper::processFileTextCodecConvert(path,sourceCodec,targetCodec,this);
}

void VoiceBankManagerWindow::on_actionFor_File_Name_triggered()
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

void VoiceBankManagerWindow::on_voicebankImage_customContextMenuRequested(const QPoint &)
{
    auto menu = new QMenu(this);
    auto modifyIconAction = new QAction(tr("修改音源的图标..."),menu);
    connect(modifyIconAction,SIGNAL(triggered(bool)),this,SLOT(modifyIconActionSlot()));
    modifyIconAction->setStatusTip(tr("为该音源指定一个新图标。"));
    menu->addAction(modifyIconAction);
    menu->popup(QCursor::pos());
}

void VoiceBankManagerWindow::onCurrentCategoriesChanged(const QStringList &current)
{
    currentCategoriesFilter = current;
    dealFilters();
}

void VoiceBankManagerWindow::onCurrentLabelsChanged(const QStringList &current)
{
    currentLabelFilter = current;
    dealFilters();
}

void VoiceBankManagerWindow::on_actionuse_old_watched_folder_scan_strategy_toggled(bool checked)
{
    MonitorFoldersScanner::getMonitorFoldersScanner()->setUseOldFolderScan(checked);
}

void VoiceBankManagerWindow::on_actionshow_more_infomation_in_total_count_label_toggled(bool checked)
{
    showMoreInformationInTotalCountLabel = checked;
    updateVoiceBankCountLabel();
}

void VoiceBankManagerWindow::letUserModifyFolder(std::function<QStringList(MonitorFoldersScanner*)>getFunc,std::function<void(MonitorFoldersScanner*,const QStringList&)>setFunc,const QString& name,const QStringList& defaultList)
{
    auto dialog = new FoldersSettingDialog(getFunc(MonitorFoldersScanner::getMonitorFoldersScanner()),tr("设定%1：").arg(name),tr("%1设定").arg(name),this,defaultList);
    auto dialogCode = dialog->exec();
    if (dialogCode == 1 && getFunc(MonitorFoldersScanner::getMonitorFoldersScanner()) != dialog->getFolders()){
        setFunc(MonitorFoldersScanner::getMonitorFoldersScanner(),dialog->getFolders());
        auto clickedButton = QMessageBox::information(this,tr("%1被更改").arg(name),tr("您更改了%1，是否立即重载音源库列表？").arg(name),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
        if (clickedButton == QMessageBox::Ok)
            loadVoiceBanksAndTable();
    }
    dialog->deleteLater();
}

void VoiceBankManagerWindow::on_actionOutside_VoiceBanks_triggered()
{
    letUserModifyFolder(std::mem_fn(&MonitorFoldersScanner::getOutsideVoiceBankFolders),std::mem_fn(&MonitorFoldersScanner::setOutsideVoiceBankFolders),tr("外部音源文件夹列表"));
}

void VoiceBankManagerWindow::on_actionIgnored_folders_triggered()
{
    letUserModifyFolder(std::mem_fn(&MonitorFoldersScanner::getIgnoreVoiceBankFolders),std::mem_fn(&MonitorFoldersScanner::setIgnoreVoiceBankFolders),tr("忽略文件夹列表"));
}

void VoiceBankManagerWindow::on_actionView_scan_details_triggered()
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
