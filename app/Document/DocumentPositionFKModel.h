#ifndef DOCUMENTPOSITIONFKMODEL_H
#define DOCUMENTPOSITIONFKMODEL_H

#include "Database/Model.h"
#include "Document/DocumentPosition.h"
#include "Other/Application/ApplicationManager.h"

class DocumentPositionFKModel : public Model
{
public:
    DocumentPositionFKModel();
    ~DocumentPositionFKModel();

    void addPosition(QString documentSymbol, DocumentPosition position);
};

#endif // DOCUMENTPOSITIONFKMODEL_H
