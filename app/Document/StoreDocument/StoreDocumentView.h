#ifndef StoreDocumentView_H
#define StoreDocumentView_H

#include "Document/DocumentView.h"

class StoreDocumentView : public DocumentView
{

public:
   explicit StoreDocumentView(QWidget* parent);
    ~StoreDocumentView();
    bool isStoreUpdating();
    void setLineGoodsValueNet(double valueNet);

    void setCheckStoreUpdate(bool update);

    double getLineGoodsValueNet();

protected:
    void initGoodsTable() ;
    void initOptionalLineEdits();
    void initOptionalButtons();
    void initOptionalConnections();
    void addOptionalComponents();

    QLineEdit *lineGoodsValueNet;
    QCheckBox* checkStoreUpdating;


};

#endif // StoreDocumentView_H
