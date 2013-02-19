#ifndef STOREDOCUMENTTVDISPLAYER_H
#define STOREDOCUMENTTVDISPLAYER_H

#include "Other/TVDisplayer.h"

/**
  * Displayer customowych danych dla modelu StoreDocument w TableView
  * @author Bartosz Milczarek
  */
class StoreDocumentTVDisplayer : public TVDisplayer
{
private:
    bool isValueColumn() const;
public:
    StoreDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~StoreDocumentTVDisplayer();

    QVariant display() const;
};

#endif // STOREDOCUMENTTVDISPLAYER_H
