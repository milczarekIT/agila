#include "HelpDialogView.h"
#include "QMessageBox"

HelpDialogView::HelpDialogView(QWidget *parent) :
    QDialog(parent)
{
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void HelpDialogView::initGraphicElements()
{
    this->setLayout(mainLayout = new QGridLayout);
    mainLayout->addWidget(panel = new QSplitter(Qt::Horizontal),1,1,1,1);

    //QFileInfo fileInfo(QLibraryInfo::location(QLibraryInfo::ExamplesPath)
    //                   + QLatin1String("/help/simpletextviewer/documentation/simpletextviewer.qhc"));
    QFileInfo fileInfo("./help/help.qhc");
    helpEngine = new QHelpEngine(fileInfo.absoluteFilePath());

    if (!helpEngine->setupData())
          qDebug() << helpEngine->error();

    qDebug() << fileInfo.absoluteFilePath();
    qDebug() << helpEngine->error();

    helpBrowser = new HelpBrowser(helpEngine);

    panel->insertWidget(0, helpEngine->contentWidget());
    panel->insertWidget(1, helpBrowser);
    panel->setStretchFactor(1, 1);
    connect(helpEngine->contentWidget(), SIGNAL(linkActivated(const QUrl &)), helpBrowser, SLOT(setSource(const QUrl &)));
}

void HelpDialogView::setGraphicSettings()
{
    this->setMinimumSize(900,500);
    panel->widget(0)->setMaximumWidth(300);
}

void HelpDialogView::setInterfaceController()
{

}
