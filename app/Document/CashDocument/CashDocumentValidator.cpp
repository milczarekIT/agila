#include "CashDocumentValidator.h"

CashDocumentValidator::CashDocumentValidator(CashDocumentView *view, QString symbol)
{
    this->view = view;
    this->symbol = symbol;
}

void CashDocumentValidator::validateForm(){}

bool CashDocumentValidator::isEmptyForm()
{
    if(!view->getLineIssuedForDocument()->text().isEmpty())
        return false;
    else if(!view->getContractorData()->toPlainText().isEmpty())
        return false;
    else if(!view->getLineAmountOfPayment()->text().isEmpty())
        return false;
    else if(!view->getLineTitle()->text().isEmpty())
        return false;
    else
        return true;
};

void CashDocumentValidator::validateDocForm( bool edition)
{
    MessageBox msgBox(view);
    dnc = new DocumentNumeratorController(symbol);

    if(edition == false)
    {
        if(view->getLineSymbol()->text().isEmpty()){
            msgBox.createInfoBox("Proszę uzupełnić wymagane pola.");
            return;
        }
        else
        {
           if(!dnc->isValidSymbol(view->getLineSymbol()->text()))
           {
               msgBox.createInfoBox("Format numeru dokumentu niepoprawny");
               return;
           }
           if(!dnc->isAvailableSymbol(view->getLineSymbol()->text()))
           {
               msgBox.createInfoBox("Numer dokumentu zajęty, ustawiono pierwszy wolny.");
               view->getLineSymbol()->setText(dnc->getNextSymbol());
               return;
           }
        }
    }

    if(view->getContractorData()->toPlainText().isEmpty())
    {
        msgBox.createInfoBox("Nie wybrano kontrahenta.");
        return;
    }

    if(view->getLineAmountOfPayment()->text().isEmpty())
    {
        view->getLineDocumentPlace()->setFocus();
        msgBox.createInfoBox("Nie ustalono wysokości wpłaty.");
        return;
    }

    if(view->getLineDocumentPlace()->text().isEmpty())
    {
        view->getLineDocumentPlace()->setFocus();
        msgBox.createInfoBox("Nie wybrano miejsca wystawienia dokumentu");
        return;
    }

    if(view->getLineTitle()->text().isEmpty())
    {
        view->getLineTitle()->setFocus();
        msgBox.createInfoBox("Nie uzupełniono pola tytułem");
        return;
    }

    if(view->getLineIssueName()->text().isEmpty())
    {
        view->getLineIssueName()->setFocus();
        msgBox.createInfoBox("Nie wybrano wystawcy dokumentu");
        return;
    }

    if(view->getLineReceiveName()->text().isEmpty())
    {
        view->getLineReceiveName()->setFocus();
        msgBox.createInfoBox("Nie wybrano odbiorcy dokumentu");
        return;
    }

    delete dnc;
    view->accept();
};
