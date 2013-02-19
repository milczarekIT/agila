#ifndef DOCUMENTNUMERATORMODEL_H
#define DOCUMENTNUMERATORMODEL_H

#include "Database/Model.h"
#include "Other/Application/ApplicationManager.h"

class DocumentNumeratorModel : public Model
{
public:
    DocumentNumeratorModel();

    QString getPrevoiusSymbol(QString documentType, QString tableName);
    QString getNumberingFormat(QString documentType);
    bool isAvailableSymbol(QString documentType, QString symbol);
};

#endif // DOCUMENTNUMERATORMODEL_H
