#include "PriceDocumentsValidator.h"

PriceDocumentsValidator::PriceDocumentsValidator(PriceDocumentView *view){
    this->view = view;
}

void PriceDocumentsValidator::validateForm() {
}

void PriceDocumentsValidator::validateForm(bool edition) {
    MessageBox *messageBox = new MessageBox();
    dnc = new DocumentNumeratorController(view->getSymbol());

    if(!edition) {
        if(!dnc->isValidSymbol(view->getSign()->text())) {
            messageBox->createInfoBox("Format numeru dokumentu niepoprawny");
            return;
        }

        if(!dnc->isAvailableSymbol(view->getSign()->text())){
            messageBox->createInfoBox("Numer dokumentu zajęty, ustawiono pierwszy wolny.");
            view->getSign()->setText(dnc->getNextSymbol());
            return;
        }
    }

    if(view->getSymbol().contains("CN")) {
        if(view->getName()->text().isEmpty()) {
            if(messageBox->createQuestionBox("Nie wprowadzono nazwy!") == MessageBox::YES)
                view->accept();
            return;
        }
    }

    if(view->getSymbol().contains("OF")) {
        if(view->getContractorData()->toPlainText().isEmpty()) {
            if(messageBox->createQuestionBox("Nie wybrano kontrahenta!") == MessageBox::YES)
                view->accept();
            return;
        }
    }

    if(view->getSign()->text().isEmpty()) {
        if(messageBox->createQuestionBox("Nie wprowadzono znaku!") == MessageBox::YES)
            view->accept();
        return;
    }


    if(view->getPositions()->model()->rowCount() < 1) {
         if(messageBox->createQuestionBox("Nie wybrano dóbr!") == MessageBox::YES)
             view->accept();
         return;
    }

    view->accept();
    delete messageBox;
}

bool PriceDocumentsValidator::isEmptyForm() {
    if(!view->getName()->text().isEmpty())
        return false;
    if(!view->getSign()->text().isEmpty())
        return false;
    if(!(view->getPositions()->model()->rowCount() < 1))
        return false;
    return true;
}

bool PriceDocumentsValidator::isImportantDataSet() {
    return view->getSign()->text().isEmpty() ||
           view->getName()->text().isEmpty();
}

bool PriceDocumentsValidator::isGoodsSet() {
    return view->getPositions()->rowCount() == 0;
}

void PriceDocumentsValidator::importantDataNoSetMessage(int edition) {
    if(isEmptyForm()) {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Uzupełnij formularz!");
        delete messageBox;
    }
    else validateForm(edition);
}

void PriceDocumentsValidator::changesWereMadeMessage() {
    MessageBox *messageBox = new MessageBox();
    int action = messageBox->createQuestionBox("Dokonano zmian");
    if (action == MessageBox::YES)
        validateForm(true);
    else
        view->reject();
    delete messageBox;
}
