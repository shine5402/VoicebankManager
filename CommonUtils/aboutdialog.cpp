/*
 *
 *  Copyright 2018-2019 shine_5402
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(const QString& applicationName,
                         const QIcon& applicationIcon,
                         const QString& aboutHtml,
                         const QString& authorHtml,
                         const QString& thanksHtml,
                         const QString& translatorsHtml,
                         const QString& licenseHtml,
                         const QString& thirdPartyLibraryHtml,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    if (applicationName.isEmpty())
    {
        setWindowTitle(tr("关于"));
        ui->headWidget->hide();
    }
    if (applicationIcon.isNull())
        ui->iconButton->hide();
    setWindowTitle(tr("关于 %1").arg(applicationName));
    ui->nameLabel->setText("<h1>" + applicationName + "</h1>");

    ui->iconButton->setIcon(applicationIcon);

    QList<QPair<int,QString>> tabTextList{};
    for (int i = 0; i < ui->tabWidget->count() ; ++i)
    {
        tabTextList.append(qMakePair(i,ui->tabWidget->tabText(i)));
    }
    for (const auto& i : tabTextList)
    {
        if (i.second == tr("关于"))
            setTab(i.first,ui->aboutTextBrowser,aboutHtml);
        if (i.second == tr("作者"))
            setTab(i.first,ui->authorTextBrowser,authorHtml);
        if (i.second == tr("致谢"))
            setTab(i.first,ui->thanksTextBrowser,thanksHtml);
        if (i.second == tr("译者"))
            setTab(i.first,ui->translatorsTextBrowser,translatorsHtml);
        if (i.second == tr("许可"))
            setTab(i.first,ui->licenseTextBrowser,licenseHtml);
        if (i.second == tr("第三方代码"))
            setTab(i.first,ui->thirdPartyBrowser,thirdPartyLibraryHtml);
    }
}   

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::setTab(int tabIndex, QTextBrowser* textBrowser,const QString& htmlString)
{
    if (!textBrowser)
        return;
    if (htmlString.isEmpty()){
        ui->tabWidget->widget(tabIndex)->deleteLater();
        ui->tabWidget->removeTab(tabIndex);
    }
    textBrowser->setHtml(htmlString);
}
