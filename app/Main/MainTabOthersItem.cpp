#include "MainTabOthersItem.h"
#include <QToolButton>

MainTabOthersItem::MainTabOthersItem(MainTabOthersItemController * controller)
{
    this->controller = controller;
    setInterface();
    setConnections();
}

void MainTabOthersItem::setInterface()
{
    buttonArchiveSql = new Button(ButtonStruct("    Archiwizacja bazy danych","Archiwizacja sql","archive", QSize(440,50)),QSize(45,40));
    buttonExportGoodsToCsv = new ToolButton(ButtonStruct("Eksport dóbr do CSV", "Eksport towarów do CSV","export", QSize(250,250)));
    buttonExportContractorsToCsv = new ToolButton(ButtonStruct("Eksport kontrahentów do CSV", "Eksport kontrahentów do CSV","export", QSize(250,250)));
    buttonHelp = new Button(ButtonStruct("", "Pomoc dla programu","help", QSize(50,50)),QSize(40,40)); // nie wiem jak tu normalnie ustawić ikonę

    buttonExportGoodsToCsv->setTopBottomLayout();
    buttonExportContractorsToCsv->setTopBottomLayout();

    this->layout->addWidget(setCentralPanel());
}

QWidget *MainTabOthersItem::setCentralPanel() {

    QWidget *centralPane = new QWidget();
    QGridLayout *layout = new QGridLayout();
    centralPane->setLayout(layout);
    centralPane->setMaximumSize(520,320);

    layout->addWidget(buttonArchiveSql,2,1,1,2);
    layout->addWidget(buttonExportGoodsToCsv, 1, 1);
    layout->addWidget(buttonExportContractorsToCsv, 1,2,1,2);
    layout->addWidget(buttonHelp,2,3,1,1);

    return centralPane;
}

void MainTabOthersItem::setConnections()
{
    connect(buttonArchiveSql, SIGNAL(clicked()),controller, SLOT(archiveSql()));
    connect(buttonExportGoodsToCsv, SIGNAL(clicked()), controller, SLOT(exportGoodsToCsv()));
    connect(buttonExportContractorsToCsv, SIGNAL(clicked()), controller, SLOT(exportContractorsToCsv()));
    connect(buttonHelp,SIGNAL(clicked()),controller,SLOT(showHelp()));
}
