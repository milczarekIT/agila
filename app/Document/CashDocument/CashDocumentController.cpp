#include "CashDocumentController.h"

CashDocumentController::CashDocumentController(QString symbol, bool edit, QWidget *parent)
{
    service = new CashDocumentService();
    this->symbol = symbol;
    edition = edit;
    view = new CashDocumentView(this,parent);
    validator = new CashDocumentValidator(view,symbol);
    this->setIssueName(getMyData());
}

CashDocumentView *CashDocumentController::getView()
{
    return view;
}


Contractor CashDocumentController::getContractor()
{
    return c;
}

void CashDocumentController::selectInvoice()
{
    QStringList docTypeFilter;

        docTypeFilter << "FV" << "FMP" << "PRO"; // faktura VAT, VAT-MP, PROFORMA

    SelectInvoiceController dialog(view, docTypeFilter);
    dialog.showDialog();

    Document invoice;

    if(dialog.getCancel() !=1)
    {
       invoice = dialog.addInvoice();
       insertInvoiceData(invoice);
    }
}

void CashDocumentController::insertInvoiceData(Document invoice)
{
    QString str;
    view->getLineIssuedForDocument()->setText(invoice.getSymbol());//LineRelatedTo

    c = invoice.getContractor();
    view->getContractorData()->setText(c.getContractorData());

    if(symbol.contains("KP"))
        view->getLineTitle()->setText("Wpłata za: " + invoice.getSymbol());
    else
        view->getLineTitle()->setText("Wypłata za: " + invoice.getSymbol());
    view->getLineAmountOfPayment()->setText(str.setNum(invoice.getTotal(),',',2).replace(QRegExp("[.]"),","));

    setReceiveName(c);
    setIssueName(getMyData());
}

void CashDocumentController::setReceiveName(Contractor receiver)
{
    if(receiver.isCompany())
        view->getLineReceiveName()->setText(receiver.getRepresentative());
    else
        view->getLineReceiveName()->setText(receiver.getName());
}

void CashDocumentController::setIssueName(Contractor issuer)
{
    if(issuer.isCompany())
        view->getLineIssueName()->setText(issuer.getRepresentative());
    else
        view->getLineIssueName()->setText(issuer.getName());
}

void CashDocumentController::setReceiveName(QString name)
{
     view->getLineReceiveName()->setText(name);
}

void CashDocumentController::setIssueName(QString name)
{
     view->getLineIssueName()->setText(name);
}

Contractor CashDocumentController::getMyData()
{
    OwnerService *ownerService = new OwnerService();
    Owner o = ownerService->getActualOwner();
    delete ownerService;

    Contractor issuer;

    issuer.setId(0);
    issuer.setName(o.getName());
    issuer.setCompany(false);
    this->setReceiveName(""); // todo logowanie osób, zalogowana osoba

    return issuer;
}

void CashDocumentController::selectContractor()
{
    SelectContractorController* contractorSelect = new SelectContractorController(view);
    contractorSelect->showDialog();

    if(contractorSelect->getView()->getContractorsTable()->getId() > 0)
    {
        c = contractorSelect->addContractor();
        setReceiveName(c);
        view->getContractorData()->setText(c.getContractorData());
    }

    delete contractorSelect;
}

void CashDocumentController::exec()
{
    CashDocument document;

    // symbol
    dnc = new DocumentNumeratorController(symbol);
    QString symbol = dnc->getNextSymbol();
    view->getLineSymbol()->setText(symbol);
    delete dnc;
    dnc = NULL;

    // miejsce wystawienia
    SettingsModel *sm = new SettingsModel();
    QString documentPlace = sm->getDefualtDocumentPlace().getName();
    view->getLineDocumentPlace()->setText(documentPlace);
    delete sm;
    sm = NULL;

    //setIssueName(getMyData());
    int signal = view->exec();

    document = getCashDocument();
    if(signal == QDialog::Accepted)
    {
        service->addCashDocument(document);
        return ;
    }
    return;
}

CashDocument CashDocumentController::getCashDocument()
{
    CashDocument document;

    document.setDocumentType(symbol);
    document.setSymbol(view->getLineSymbol()->text());
    document.setDocumentDate(view->getDateOfIssue()->date());
    document.setDocumentPlace(view->getLineDocumentPlace()->text());
    document.setBaseDocumentSymbol(view->getLineIssuedForDocument()->text());
    document.setIssueName(view->getLineIssueName()->text());
    document.setReceiveName(view->getLineReceiveName()->text());
    document.setContractor(c);
    document.setDescription(view->getTextDescription()->toPlainText());
    document.setPaymentDate(view->getDateOfPayment()->date());
    document.setTitle(view->getLineTitle()->text());
    document.setTotal(view->getLineAmountOfPayment()->text().toFloat());

    return document;
}

void CashDocumentController::exec(QString symbol)
{
    document = service->getCashDocument(symbol);
    oldDocument = document;

    initData();

    int signal = view->exec();
    document = getCashDocument();

    if(signal == QDialog::Accepted)
    {
        if(!(oldDocument == document)) // jeśli nie było edycji, to nie ma potrzeby wywoływać modelu
        {
            service->editCashDocument(document);
        }
        return ;
    }
    return;
}

void CashDocumentController::initData()
{
    QString text;
    view->getLineSymbol()->setText(document.getSymbol());
    view->getLineDocumentPlace()->setText(document.getDocumentPlace());
    view->getDateOfIssue()->setDate(document.getDocumentDate());
    view->getLineIssuedForDocument()->setText(document.getBaseDocumentSymbol()); // tutaj nie wiem czy to tak ma byc

    view->getLineIssueName()->setText(document.getIssueName());
    view->getLineReceiveName()->setText(document.getReceiveName());
    view->getTextDescription()->setText(document.getDescription());
    view->getLineAmountOfPayment()->setText(text.setNum(document.getTotal(),',',2).replace(QRegExp("[.]"),","));
    view->getDateOfPayment()->setDate(document.getPaymentDate());
    view->getLineTitle()->setText(document.getTitle());

    c = document.getContractor();
    view->getContractorData()->setText(c.getContractorData());
}

void CashDocumentController::print()
{
    CashDocument kp = service->getCashDocument("KP/1/2011");
    //PrintManager pm; pm.print(&kp);
}

void CashDocumentController::checkRequiredFields()
{
    this->validator->validateDocForm(edition);
}

void CashDocumentController::checkChanges()
{
    document = getCashDocument();
    if(validator->isEmptyForm())
    {
        view->reject();
    }
    else if(!(oldDocument == document)) // jeśli kliknięto anuluj, ale nastąpiły zmiany
        {
            MessageBox *messageBox = new MessageBox(view);
            if (messageBox->createQuestionBox("Dokonano zmian") == MessageBox::YES)
            {
                this->checkRequiredFields();
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

CashDocumentController::~CashDocumentController()
{
    delete service;
}

QString CashDocumentController::getSymbol()
{
    return symbol;
}
