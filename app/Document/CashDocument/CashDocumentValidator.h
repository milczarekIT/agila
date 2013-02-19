#ifndef CASHDOCUMENTVALIDATOR_H
#define CASHDOCUMENTVALIDATOR_H

#include <QWidget>
#include "Other/Validator.h"
#include "Document/CashDocument/CashDocumentView.h"
#include "Document/DocumentNumeratorController.h"
class CashDocumentView;

class CashDocumentValidator : public Validator
{
private:
    CashDocumentView *view;
    DocumentNumeratorController *dnc;
    QString symbol;

public:
    CashDocumentValidator(CashDocumentView *view, QString symbol);
    bool isEmptyForm();
    void validateDocForm( bool edition);
    void validateForm();
};

#endif // CASHDOCUMENTVALIDATOR_H
