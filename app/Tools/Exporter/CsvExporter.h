#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include <QMap>
#include <QVariant>
#include <QStringList>
#include "Goods/GoodsService.h"
#include "Tools/Exporter/CsvMapWriter.h"

class CsvExporter
{
protected:
    QMap<QString, QString> row;
    QStringList header;
    virtual void initAvailableHeader() = 0;
public:
    CsvExporter();
    QStringList getAvailableHeader();
};

#endif // CSVEXPORTER_H
