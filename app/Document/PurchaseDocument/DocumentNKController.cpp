#include "DocumentNKController.h"

DocumentNKController::DocumentNKController(QWidget* parent)
{
    view = new DocumentNKView(parent, this);
    service = new DocumentNKService();

    Contractor issuer;
    Contractor receiver;
}

/**
  Wyświetla okno dokumentu Nota Korygująca.
  Zwraca utworzony dokument lub NULL w przypadku anulowania operacji.
  */
void DocumentNKController::exec()   {
    DocumentNK document;

    // symbol
    dnc = new DocumentNumeratorController("NK");
    QString symbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(symbol);
    delete dnc;
    dnc = NULL;

    // miejsce wystawienia
    SettingsModel *sm = new SettingsModel();
    QString documentPlace = sm->getDefualtDocumentPlace().getName();
    view->getLineDocumentPlace()->setText(documentPlace);
    delete sm;
    sm = NULL;

    this->view->getLineIssueName()->setText(ApplicationManager::getInstance()->getLoggedUser().getName());

    int signal = view->exec();

    document = getDocumentNK();
    if(signal == QDialog::Accepted)
    {
        service->addDocumentNK(document);
        this->printDoc();
        return ;
    }


    return;
}

void DocumentNKController::exec(QString symbol)
{
    document = service->getDocumentNK(symbol);
    oldDocument = document;

    initData();

    int signal = view->exec();
    document = getDocumentNK();

    if(signal == QDialog::Accepted)
    {
        if(!(oldDocument == document)) // jeśli nie było edycji, to nie ma potrzeby wywoływać modelu
        {
            service->editDocumentNK(document);
            this->printDoc();
        }

        return ;
    }


    return;
}

void DocumentNKController::initData()
{
    this->receiver=document.getContractor();
    view->getLineDocumentSymbol()->setText(document.getSymbol());
    view->getLineDocumentPlace()->setText(document.getDocumentPlace());
    view->getDateEditDocumentDate()->setDate(document.getDocumentDate());
    view->getLineRelatedTo()->setText(document.getInvoiceSymbol());
    view->getDateEditInvoiceDate()->setDate(document.getInvoiceDate());
    view->getLineIssueName()->setText(document.getIssueName());
    view->getLineReceiveName()->setText(document.getReceiveName());
    view->getTextReceiver()->setText(document.getContractor().getContractorData());
    view->getTextCorrected()->setText(document.getCorrectedContent());
    view->getTextCorrect()->setText(document.getCorrectContent());
}

void DocumentNKController::setReceiveName(Contractor receiver)
{
    if(receiver.isCompany())
        view->getLineReceiveName()->setText(receiver.getRepresentative());
    else
        view->getLineReceiveName()->setText(receiver.getName());
}


void DocumentNKController::setIssueName(QString name)
{
    view->getLineIssueName()->setText(name);
}

DocumentNK DocumentNKController::getDocumentNK()
{
    DocumentNK document;
    document.setSymbol(view->getLineDocumentSymbol()->text());
    document.setDocumentDate(view->getDateEditDocumentDate()->date());
    document.setDocumentPlace(view->getLineDocumentPlace()->text());
    document.setContractor(receiver);
    document.setInvoiceSymbol(view->getLineRelatedTo()->text());
    document.setInvoiceDate(view->getDateEditInvoiceDate()->date());
    document.setCorrectedContent(view->getTextCorrected()->toPlainText());
    document.setCorrectContent(view->getTextCorrect()->toPlainText());
    document.setIssueName(view->getLineIssueName()->text());
    document.setReceiveName(view->getLineReceiveName()->text());

    return document;
}


void DocumentNKController::selectReceiver()
{
    SelectContractorController* contractorSelect = new SelectContractorController(view);
    contractorSelect->setContractorTypeFilter(Contractor::SUPPLIER); // tylko dostawcy
    contractorSelect->showDialog();

    if(contractorSelect->getView()->getContractorsTable()->getId() > 0)
    {
        receiver = contractorSelect->addContractor();
        view->setReceiver(receiver);
        this->setReceiveName(receiver);
    }

    delete contractorSelect;
}

void DocumentNKController::selectInvoice()
{
    SelectInvoiceController dialog(view, "PURCHASE");
    dialog.setDocumentNotTypeFilter("NK"); // nie wyświetli dokumentów NK
    dialog.showDialog();

    Document invoice;

    if(dialog.getCancel() !=1)
    {
       invoice = dialog.addInvoice();
       insertInvoiceData(invoice);
    }
}

void DocumentNKController::insertInvoiceData(Document invoice)
{
    view->getLineRelatedTo()->setText(invoice.getSymbol());
    view->getDateEditInvoiceDate()->setDate(invoice.getDocumentDate()); 

    receiver = invoice.getContractor();
    view->setReceiver(receiver);
    this->setReceiveName(receiver);

}

void DocumentNKController::checkChanges()
{
    document = getDocumentNK();
    if(this->isEmptyForm())
    {
        view->reject();
    }
    else
    {
        if(!(oldDocument == document)) // jeśli kliknięto anuluj, ale nastąpiły zmiany
        {
            MessageBox *messageBox = new MessageBox();
            if (messageBox->createQuestionBox("Dokonano zmian") == MessageBox::YES)
            {
                //this->checkRequiredFields(); // jesli bedzie walidacja to tutaj
                view->accept();
            }
            else
                view->reject(); // zmiany dokonane, ale użytkowik chce anulować
        }
        else
        {
             view->reject(); // nie dokonano zmian, anuluj
        }
    }

}

bool DocumentNKController::isEmptyForm()
{
    if(!view->getLineRelatedTo()->text().isEmpty())
        return false;
    else if(!view->getTextReceiver()->toPlainText().isEmpty())
        return false;
    else if(!view->getTextCorrected()->toPlainText().isEmpty())
        return false;
    else if(!view->getTextCorrect()->toPlainText().isEmpty())
        return false;
    else
        return true;
}
void DocumentNKController::printDoc()
{
    DocumentNK nk = service->getDocumentNK(view->getLineDocumentSymbol()->text());
    PrintPurchaseDocumentController *pc = new PrintPurchaseDocumentController(view->getLineDocumentSymbol()->text());
    pc->print(&nk);
    delete pc;
}

DocumentNKController::~DocumentNKController()
{
    delete service;
}

