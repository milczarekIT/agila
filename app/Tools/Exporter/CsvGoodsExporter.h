#ifndef CSVGOODSEXPORTER_H
#define CSVGOODSEXPORTER_H

#include "Tools/Exporter/CsvExporter.h"

class CsvGoodsExporter : public CsvExporter
{
    void initAvailableHeader();
public:
    CsvGoodsExporter();
    void exportData(QVector<Goods> goods, QString filePath, QStringList selectedColumns);
};

#endif // CSVGOODSEXPORTER_H
