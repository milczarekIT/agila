#include "MainTabOthersItemController.h"

MainTabOthersItemController::MainTabOthersItemController()
{
    view = new MainTabOthersItem(this);
}

MainTabOthersItem *MainTabOthersItemController::getView()
{
    return view;
}

void MainTabOthersItemController::archiveSql()
{
    ArchiverDialogController *archiver = new ArchiverDialogController(this);
    archiver->exec();
    delete archiver;
}

void MainTabOthersItemController::exportGoodsToCsv()
{
    CsvGoodsExporterDialogController *controller = new CsvGoodsExporterDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabOthersItemController::exportContractorsToCsv()
{
    CsvContractorExporterDialogController *controller = new CsvContractorExporterDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabOthersItemController::showHelp()
{
    HelpDialogView *dialog = new HelpDialogView();
    dialog->exec();
    delete dialog;
}
