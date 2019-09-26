#include "moresamplerconfigsdialog.h"
#include "ui_moresamplerconfigsdialog.h"

MoresamplerConfigsDialog::MoresamplerConfigsDialog(const QString &path, const MoresamplerConfigReader::ConfigFileType configFileType,QWidget *parent,QString voiceBankName) :
    QDialog(parent),
    ui(new Ui::MoresamplerConfigsDialog),path(path)
{
    ui->setupUi(this);
    reader = new MoresamplerConfigReader(path,configFileType,this);
    model = new MoresamplerConfigsModel(reader);
    connect(model,SIGNAL(ValueToSetIsNotValid(int, QVariant)),this,SLOT(onInvalidValue(int, QVariant)));
    ui->configTableView->setModel(model);
    ui->configTableView->resizeColumnsToContents();
    ui->configTableView->setItemDelegate(new MoresamplerConfigsDelegate(reader,this));
    if (configFileType == MoresamplerConfigReader::ConfigFileType::VoiceBank)
    {
        if (!voiceBankName.isEmpty())
            setWindowTitle(tr("编辑“%1”的Moresampler配置").arg(voiceBankName));
        else
            setWindowTitle(tr("编辑名称未知的音源的Moresampler配置"));
    }
    else{
        setWindowTitle(tr("编辑全局Moresampler配置"));
        ui->deleteFilesCheckBoxs->hide();
    }
    ui->whatIsEditingLabel->setText(tr("当前正在编辑：%1").arg(path));

}

MoresamplerConfigsDialog::~MoresamplerConfigsDialog()
{
    delete ui;
}

void MoresamplerConfigsDialog::on_deleteButton_clicked()
{
    if (reader->count() > 0)
    {
        model->removeConfig(ui->configTableView->currentIndex().row());
        ui->configTableView->resizeColumnsToContents();
    }
    else
        QMessageBox::warning(this,tr("没有可删除的项"),tr("当前配置文件的配置项目数为0，所以无法删除项目。"));
}

void MoresamplerConfigsDialog::on_addButton_clicked()
{
    auto dialog = new MoresamplerConfigAddNewDialog(reader,this);
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted)
    {
        auto name = dialog->getCurrentEntryName();
        if (name == tr("（空行）"))
            name = QString();
        else if (name == tr("（注释）"))
            name = "#";
        else if (name == tr("（元标记）"))
        {
            bool ok = false;
            auto num = QInputDialog::getInt(this,tr("指定元标记的序数"),tr("在下面的输入框中输入一个数字。该数字将作为调用元标记时应当使用的序数。比如，您想要使用M1，就在下框中输入1."),1,1,100,1,&ok);
            if (ok)
            {
                name = QString("meta-flag-%1").arg(num);
            }
            else
                return;
        }
        model->addConfig(name);
        ui->configTableView->resizeColumnsToContents();
    }
}

void MoresamplerConfigsDialog::accept()
{
    QString error;
    for (int i = 0;i < reader->count();++i)
    {
        auto config = reader->getConfig(i);
        if (!config->isValidValue())
            error.append(tr("您设置的值“%1”无法应用于第%2行。请修改后重试。\n").arg(config->getValueString()).arg(i));
    }
    if (!error.isEmpty()){
        QMessageBox::warning(this,tr("设置的值无效"),error.trimmed());
        return;
    }
    reader->saveConfigs();
    auto deleteFile = [&](const QString& path, const QStringList& filter){
        auto dir = QFileInfo(path).dir();
        auto llsmInfoList = dir.entryInfoList(filter,QDir::Files | QDir::NoDotAndDotDot);
        QList<QPair<QString,QString>> errorFiles;
        for (auto i : llsmInfoList)
        {
            QFile file(i.canonicalFilePath());
            if (!file.remove())
            {
                qCritical() << tr("删除文件%1时出现错误%2。").arg(file.fileName()).arg(file.errorString());
                errorFiles.append(qMakePair(file.fileName(),file.errorString()));
            }
        }
        if (!errorFiles.isEmpty())
        {
            QString errorString{tr("<h3>以下文件无法删除。</h3><ul>")};
            for (auto i : errorFiles)
            {
                errorString.append(tr("<li>%1（%2）</li>"));
            }
            errorString.append(tr("</ul>"));
            QMessageBox::critical(this,tr("删除某些文件时出错"),errorString);
        }
    };
    if (ui->deleteLLSMCheckBox->isChecked())
    {
        deleteFile(path,{"*.llsm"});
    }
    if (ui->deleteDESCMRQCheckBox->isChecked())
    {
        deleteFile(path,{"desc.mrq"});
    }
    QDialog::accept();
}

void MoresamplerConfigsDialog::onInvalidValue(int row, QVariant data)
{
    QMessageBox::warning(this,tr("设置的值无效"),tr("您设置的值“%1”无法应用于第%2行。请修改后重试。").arg(data.toString()).arg(row));
}
