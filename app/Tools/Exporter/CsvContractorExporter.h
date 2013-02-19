#ifndef CSVCONTRACTOREXPORTER_H
#define CSVCONTRACTOREXPORTER_H

#include "Tools/Exporter/CsvExporter.h"

class CsvContractorExporter : public CsvExporter
{
    void initAvailableHeader();
public:
    CsvContractorExporter();
    void exportData(QVector<Contractor> contractors, QString filePath, QStringList selectedColumns);
};

#endif // CSVCONTRACTOREXPORTER_H
