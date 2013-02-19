#ifndef DOCUMENTPLACEMODEL_H
#define DOCUMENTPLACEMODEL_H

#include "Database/Model.h"
#include "Other/SimpleStructure.h"

class DocumentPlaceModel : public Model
{
    int addDocumentPlace(QString name);
public:
    DocumentPlaceModel();

    SimpleStructure getDocumentPlace(int id);

    /**
      * Pobiera id miasta wystawienia dokumentu
      * Jeśli nie ma miejsca name, to dodaje do bazy i zwraca nowododany id
      */
    int getDocumentPlaceId(QString name);
};

#endif // DOCUMENTPLACEMODEL_H
