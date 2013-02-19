#ifndef PRICEDOCUMENTSVALIDATOR_H
#define PRICEDOCUMENTSVALIDATOR_H

#include "Other/Validator.h"
#include "Document/PriceDocument/PriceDocumentView.h"
#include "Document/DocumentNumeratorController.h"
class PriceDocumentView;

class PriceDocumentsValidator : public Validator
{

private:
    PriceDocumentView *view;
    DocumentNumeratorController *dnc;

public:
    PriceDocumentsValidator(PriceDocumentView *view);

    void validateForm();
    void validateForm(bool edition);
    bool isEmptyForm();
    bool isImportantDataSet();
    bool isGoodsSet();
    void importantDataNoSetMessage(int edition);
    void changesWereMadeMessage();
};

#endif // PRICEDOCUMENTSVALIDATOR_H
