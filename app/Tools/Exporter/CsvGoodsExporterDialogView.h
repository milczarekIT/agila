#ifndef CSVGOODSEXPORTERDIALOGVIEW_H
#define CSVGOODSEXPORTERDIALOGVIEW_H

#include <QDialog>
#include "Tools/Exporter/CsvGoodsExporterDialogController.h"
#include "Tools/Exporter/"
class CsvGoodsExporterDialogController;

class CsvGoodsExporterDialogView
{
public:
    CsvGoodsExporterDialogView(CsvGoodsExporterDialogController *controller, QStringList availableColumns, QWidget *parent = 0);


};

#endif // CSVGOODSEXPORTERDIALOGVIEW_H
