#ifndef CONTRACTORVALIDATOR_H
#define CONTRACTORVALIDATOR_H

#include "Contractor/ContractorDialogView.h"
#include "Other/Validator.h"
class ContractorDialogView;

class ContractorValidator : public Validator
{
    ContractorDialogView *view;

    bool isCorrectTIN();
public:
    ContractorValidator(ContractorDialogView *view);
    ~ContractorValidator();

    void validateForm();
    bool isEmptyForm();

};

#endif // CONTRACTORVALIDATOR_H
