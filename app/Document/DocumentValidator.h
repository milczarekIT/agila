#ifndef DOCUMENTVALIDATOR_H
#define DOCUMENTVALIDATOR_H

#include "Other/Validator.h"
#include "Document/DocumentView.h"
#include "Document/SaleDocument/DocumentFKView.h"

class DocumentView;
class DocumentFKView;

class DocumentValidator : public Validator
{
    DocumentView * view;
    DocumentFKView * viewFK;
    QString symbol;
    DocumentNumeratorController * dnc;
public:

    DocumentValidator(DocumentFKView *view,QString symbol);
    DocumentValidator(DocumentView* view,QString symbol);
    ~DocumentValidator();
    bool isEmptyForm();
    bool isEmptyFormFK();
    void validateForm();
public:
     void validateDocForm(bool edition);
     void validateDocFormFK(bool edition);
};

#endif // DOCUMENTVALIDATOR_H
