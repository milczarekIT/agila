#ifndef MAINTABOTHERSITEMCONTROLLER_H
#define MAINTABOTHERSITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabOthersItem.h"
#include "Tools/Help/HelpDialogView.h"
#include "User/LoggingSystemController.h"
#include "Tools/Archiver/ArchiverDialogController.h"
#include "Tools/Exporter/CsvGoodsExporterDialogController.h"
#include "Tools/Exporter/CsvContractorExporterDialogController.h"
class MainTabOthersItem;

class MainTabOthersItemController : public QWidget
{
    Q_OBJECT
private:
    MainTabOthersItem *view;

public:
    MainTabOthersItemController();
    MainTabOthersItem *getView();

public slots:
    void archiveSql();
    void exportGoodsToCsv();
    void exportContractorsToCsv();
    void showHelp();

};

#endif // MAINTABOTHERSITEMCONTROLLER_H
