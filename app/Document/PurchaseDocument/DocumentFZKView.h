#ifndef DOCUMENTFZKVIEW_H
#define DOCUMENTFZKVIEW_H

#include "Document/SaleDocument/DocumentFKView.h"
#include "Document/PurchaseDocument/DocumentFZKController.h"

class DocumentFZKController;

class DocumentFZKView : public DocumentFKView
{

public:
    DocumentFZKView(QWidget *parent, DocumentFZKController *controller);

private:

    void addAdditionalComopnent();
};

#endif // DOCUMENTFZKVIEW_H
