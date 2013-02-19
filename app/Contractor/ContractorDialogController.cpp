#include "ContractorDialogController.h"

ContractorDialogController::ContractorDialogController(QWidget *parent)
{
    this->view = new ContractorDialogView(parent,this);
    validator = new ContractorValidator(view);
    somModel = new SOMModel();
    contractorGroupModel = new ContractorGroupModel();
    contractorAdditionalTypeIdModel = new ContractorAdditionalTypeIdModel();
    view->getBoxSOM()->addItem("BRAK", 0);
    fillBox(view->getBoxSOM(),somModel->getSourcesOfMember());
    view->getBoxConGroup()->addItem("BRAK", 0);
    fillBox(view->getBoxConGroup(),contractorGroupModel->getContractorGroups());
    view->getBoxAdditionalId()->addItem("Brak",0);
    fillBox(view->getBoxAdditionalId(),contractorAdditionalTypeIdModel->getTypeIds());
    autoSymbol=true;
    this->initTablePhone();
    service = new ContractorService();

    restoreTableState();
}

ContractorDialogController::~ContractorDialogController() {
    saveTableState();
    delete validator;
    delete service;
}

Contractor *ContractorDialogController::exec ()
{
    Contractor *c;
    view->getCheckBoxBuyer()->setChecked(true);
    view->getRadioBusiness()->setChecked(true);
    view->setWindowTitle("Dodaj kontrahenta");

    if (view->exec())
    {
        c = new Contractor();
        *c = getContractorData();

        int id = service->addContractor(*c);

        if(id == -1)
            return NULL;
        else {
            c->setId(id);
            return c;
        }
    }
    return NULL;
}
bool ContractorDialogController::exec (int id)
{
    this->contractor = service->getContractor(id);
    this->oldContractor = contractor;
    view->setWindowTitle("Edytuj kontrahenta: " + contractor.getName());
    if(contractor.isCompany())
    {
        view->getRadioBusiness()->setChecked(true);
        view->getTextCompany()->setText(contractor.getName());
        view->getLineName()->setText(contractor.getRepresentative());
    }
    else
    {
        view->getRadioIndividial()->setChecked(true);
        view->getTextCompany()->setText(contractor.getName());
    }

    if(contractor.getType()== Contractor::BUYER)
        view->getCheckBoxBuyer()->setChecked(true);
    else if(contractor.getType()==Contractor::SUPPLIER)
        view->getCheckBoxSupplier()->setChecked(true);
    else if(contractor.getType()== (Contractor::BUYER | Contractor::SUPPLIER))
    { view->getCheckBoxSupplier()->setChecked(true);
        view->getCheckBoxBuyer()->setChecked(true);
    }
    else
    {
    view->getCheckBoxSupplier()->setChecked(false);
    view->getCheckBoxBuyer()->setChecked(false);
    }
    view->getLineSymbol() ->setText (contractor.getSymbol());
    view->getLinePostCode() ->setText (contractor.getPostcode());
    view->getLineCity() ->setText (contractor.getCity());
    view->getLineAdress() ->setText (contractor.getAddress());
    view->getLineTIN() ->setText (contractor.getNip());
    view->getLineRegon() ->setText (contractor.getAdditionalId().getValue());
    view->getLineAccount() ->setText (contractor.getAccountNumber());
    view->getLineWebsite() ->setText (contractor.getWebsite());
    view->getLineEmail() ->setText (contractor.getEmail());
    view->getTextComments() ->setText (contractor.getComments());
    view->getLineAdditional() ->setText (contractor.getAdditional());
    QString discount;
    view->getLineDiscount()->setText(discount.setNum(contractor.getDiscount(), 'f', 2));
    view->getBoxConGroup()->setCurrentIndex(view->getBoxConGroup()->findData(QVariant::fromValue(contractor.getContractorGroup().getId())));
    view->getBoxSOM()->setCurrentIndex(view->getBoxSOM()->findData(QVariant::fromValue(contractor.getSourceOfMember().getId())));
    view->getBoxAdditionalId()->setCurrentIndex(view->getBoxAdditionalId()->findData(QVariant::fromValue(contractor.getAdditionalId().getType().getId())));
    QVector<Phone> phones = contractor.getPhones();
    for (int i=0; i<phones.size() ; i++)
    {
        QStandardItem *defaultPhone = new QStandardItem();
        Phone p = phones.at(i);
        phoneModel->setItem(i,0,new QStandardItem(QString::number(p.getId())));
        phoneModel->setItem(i,1,new QStandardItem(p.getName()));
        phoneModel->setItem(i,2, new QStandardItem(p.getNumber()));
        phoneModel->setItem(i,3,defaultPhone);
        defaultPhone->setCheckable(true);
        defaultPhone->setEditable(false);
        if(p.isDefault())
            phoneModel->setData(defaultPhone->index(), Qt::Checked, Qt::CheckStateRole);
        else
            phoneModel->setData(defaultPhone->index(), Qt::Unchecked, Qt::CheckStateRole);
    }

    if (view->exec())
    {
        contractor = getContractorData();
        contractor.setId(id);
        if(isChangesOccured())
        {
        service->editContractor(contractor);
    }
        return true;
    }
    return false;
}

Contractor ContractorDialogController::getContractorData ()
{
    Contractor c;
    if(view->getRadioBusiness()->isChecked())
    {
        c.setCompany(true);
        c.setName(view->getTextCompany()->text().trimmed());
        c.setRepresetative(view->getLineName()->text().trimmed());
    }
    else
    {
        c.setCompany(false);
        c.setName(view->getTextCompany()->text().trimmed());
        c.setRepresetative("");
    }
    c.setSymbol(view->getLineSymbol()->text().trimmed());
    c.setPostcode(view->getLinePostCode()->text());
    c.setCity(view->getLineCity()->text());
    c.setAddress(view->getLineAdress()->text());
    c.setNip(view->getLineTIN()->text()) ;
    SimpleStructure simStr;
    simStr.setId(view->getBoxAdditionalId()->itemData(view->getBoxAdditionalId()->currentIndex()).toInt());
    c.setAdditionalId(simStr, view->getLineRegon()->text());
    c.setDiscount (view->getLineDiscount()->text().toFloat()) ;
    c.setAccountNumber ( view->getLineAccount()->text()) ;
    c.setWebsite ( view->getLineWebsite()->text()) ;
    c.setEmail ( view->getLineEmail()->text()) ;
    c.setComments ( view->getTextComments()->toPlainText()) ;
    c.setAdditional ( view->getLineAdditional()->text()) ;

    if (view->getCheckBoxBuyer()->isChecked() && view->getCheckBoxSupplier()->isChecked())
        c.setType(Contractor::BUYER | Contractor::SUPPLIER);
    else if(view->getCheckBoxBuyer()->isChecked() && view->getCheckBoxSupplier()->isChecked()==false)
        c.setType(Contractor::BUYER);
    else if (view->getCheckBoxSupplier()->isChecked() && view->getCheckBoxBuyer()->isChecked()==false)
        c.setType(Contractor::SUPPLIER);
    else
        c.setType(0);


    int cgId = view->getBoxConGroup()->itemData(view->getBoxConGroup()->currentIndex()).toInt();
    if(cgId == 0)
    {
        ContractorGroup cg;
        cg.setId(0);
    }
    else
    {
        ContractorGroup cg = contractorGroupModel->getContractorGroup(cgId);
        c.setContractorGroup(cg);
    }
    int somId = view->getBoxSOM()->itemData(view->getBoxSOM()->currentIndex()).toInt();
    SourceOfMember som = somModel->getSourceOfMember(somId);
    c.setSourceOfMember(som);
    Phone p;
    QVector<Phone> pv;
    for (int i=0 ; i<phoneModel->rowCount() ;i++)
    {
        p.setId(phoneModel->item(i,0)->text().toInt());
        p.setName(phoneModel->item(i,1)->text().left(60));
        p.setNumber(phoneModel->item(i,2)->text().left(20));
        p.setDefault(phoneModel->item(i, 3)->checkState());
        pv.push_back(p);
    }
    c.setPhones(pv);
    return c;
}

void ContractorDialogController::checkRequiredFields () {
    if(validator->isEmptyForm())
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Uzupełnij formularz!");
    }
    else
    validator->validateForm();
}

void ContractorDialogController::checkChanges()
{
    contractor = getContractorData();
    contractor.setId(oldContractor.getId());
    if(validator->isEmptyForm())
        view->reject();
    else if(isChangesOccured())
    {
        MessageBox *messageBox = new MessageBox();
        if (messageBox->createQuestionBox("Dokonano zmian") == MessageBox::YES)
            validator->validateForm();
        else
            view->reject(); // zmiany dokonane, ale użytkowik chce anulować
    }
    else
        view->reject(); // nie dokonano zmian, anuluj

}

bool ContractorDialogController::isChangesOccured() {
    return !(oldContractor == contractor);
}

void ContractorDialogController::addContractorGroup(){

    ContractorGroup cg;
    InsertTextDialog dialog(this);
    dialog.setWindowTitle("Dodaj grupę");
    if(dialog.exec())
    {
        dialog.getLineEdit()->setMaxLength(60);
        cg.setName(dialog.getLineEdit()->text());
        contractorGroupModel->addContractorGroup(cg);

        // refresh (nowododana grupa pojawi się w comboboxie)
        view->getBoxConGroup()->clear();
        view->getBoxConGroup()->addItem("BRAK", 0);
        fillBox(view->getBoxConGroup(),contractorGroupModel->getContractorGroups());

        // ustawienie nowododanej grupy
        int currentIndex = view->getBoxConGroup()->findText(cg.getName());
        view->getBoxConGroup()->setCurrentIndex(currentIndex);

        view->settingsChanged("ContractorGroup");
    }

}


void ContractorDialogController::removeContractorGroup ()
{
    int currentIndex = view->getBoxConGroup()->currentIndex();
    int conGroupId = view->getBoxConGroup()->itemData(currentIndex).toInt();

    if(conGroupId != 0)
    {
        MessageBox messageBox;
        int ret = messageBox.createQuestionBox("Usuwanie grupy " + view->getBoxConGroup()->currentText());

        if(ret == MessageBox::YES)
        {
            contractorGroupModel->removeContractorGroup(conGroupId);

            // refresh
            view->getBoxConGroup()->clear();
            view->getBoxConGroup()->addItem("BRAK", 0);
            fillBox(view->getBoxConGroup(),contractorGroupModel->getContractorGroups());
        }
    }


}

void ContractorDialogController::addSourceOfMember()
{
    SourceOfMember som;
    InsertTextDialog dialog(this);
    dialog.setWindowTitle("Dodaj źródło pozyskania klienta");
    if(dialog.exec())
    {
        dialog.getLineEdit()->setMaxLength(60);
        som.setName(dialog.getLineEdit()->text());
        somModel->addSourceOfMember(som);

        // refresh (nowododana grupa pojawi się w comboboxie)
        view->getBoxSOM()->clear();
        view->getBoxSOM()->addItem("BRAK");
        fillBox(view->getBoxSOM(),somModel->getSourcesOfMember());

        // ustawienie nowododanej grupy
        int currentIndex = view->getBoxSOM()->findText(som.getName());
        view->getBoxSOM()->setCurrentIndex(currentIndex);
    }
}

void ContractorDialogController::removeSourceOfMember()
{
    MessageBox messageBox;
    int ret = messageBox.createQuestionBox("Usuwanie " + view->getBoxSOM()->currentText());

    if(ret == MessageBox::YES)
    {
        int currentIndex = view->getBoxSOM()->currentIndex();

        int sourceId = view->getBoxSOM()->itemData(currentIndex).toInt();
        somModel->removeSourceOfMember(sourceId);

        // refresh
        view->getBoxSOM()->clear();
        view->getBoxSOM()->addItem("BRAK", 0);
        fillBox(view->getBoxSOM(),somModel->getSourcesOfMember());
    }
}

void ContractorDialogController::nameTyping ()
{
    if (!autoSymbol) return;
    QString symbol = view->getTextCompany()->text();
    symbol.remove(QRegExp("[%$*+?()[{}\\]\\/\\^\"]"));
    symbol.remove("\\");
    view->getLineSymbol()->setText(symbol.toUpper());
}
void ContractorDialogController::checkAutoSymbol (const QString & text )
{
    if(text.isEmpty()) {autoSymbol=true;
                nameTyping();}
    else autoSymbol=false;
}


void  ContractorDialogController:: fillBox(QComboBox *box,QVector<ContractorGroup> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}
void  ContractorDialogController:: fillBox(QComboBox *box,QVector<SourceOfMember> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void  ContractorDialogController::fillBox(QComboBox *box,QVector<SimpleStructure> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void ContractorDialogController::addPhone()
{
    QStandardItem *defaultPhone = new QStandardItem();
    int row = phoneModel->rowCount();
    defaultPhone->setCheckable(true);
    defaultPhone->setEditable(false);
    defaultPhone->setCheckState(Qt::Unchecked);

    phoneModel->setItem(row,0,new QStandardItem(QString::number(0)));
    phoneModel->setItem(row,1,new QStandardItem());
    phoneModel->setItem(row,2, new QStandardItem());
    phoneModel->setItem(row,3,defaultPhone);

    if(row == 0) // pierwszy telefon jako główny
        phoneModel->setData(defaultPhone->index(), Qt::Checked, Qt::CheckStateRole);
    else
        phoneModel->setData(defaultPhone->index(), Qt::Unchecked, Qt::CheckStateRole);

}

void ContractorDialogController::removePhone()
{
    QModelIndex index = view->getTablePhones()->currentIndex();
    phoneModel->removeRow(index.row());
    if(phoneModel->rowCount() > 0) // jeśli był więcej niz jeden telefon
    {
        for(int i = 0; i < phoneModel->rowCount(); i++)
        {
            if(phoneModel->item(0, 3)->checkState() == Qt::Checked) // jeśli istnieje tel. główny to nie szukaj dalej
                return;
        }
        phoneModel->item(0, 3)->setCheckState(Qt::Checked); // zaznacz w tabeli pierwszy tel jako główny
    }
}

void ContractorDialogController::clearFields()
{
        view->getLineSymbol()->clear();
        view->getLineName()->clear();
        view->getLinePostCode()->clear();
        view->getLineCity()->clear();
        view->getLineAdress()->clear();
        view->getLineTIN()->clear();
        view->getLineRegon()->clear();
        view->getLineAccount()->clear();
        view->getLineWebsite()->clear();
        view->getLineEmail()->clear();
        view->getLineAdditional()->clear();
        view->getTextComments()->clear();
}

ContractorDialogView* ContractorDialogController::getView()
{
    return view;
}

void ContractorDialogController::autoPostalCode()
{
    QString postalCode = view->getLinePostCode()->text().trimmed();
    OtherService *otherService = new OtherService();
    QString city = otherService->getCityByPostalCode(postalCode);
    view->getLineCity()->setText(city);
    view->getLineCity()->setCursorPosition(city.length());
}


void ContractorDialogController::selectedBusinessContractor(bool selectedBusiness)
{
    if(selectedBusiness) // firma
    {
        view->getLineName()->show();
        view->getLabelName()->setText("Reprezentant:");
        view->getLabelName()->show();
        view->getLabelCompany()->setText("<b>Firma: </b>");
        view->getLabelTIN()->setText("<b>NIP: </b>");
        connect(view->getTextCompany(),SIGNAL(textChanged(QString)),this,SLOT(nameTyping()));
    }
}

void ContractorDialogController::selectedIndividualContractor(bool selectedIndividual)
{
    if(selectedIndividual) // osoba fizyczna
    {
        view->getLineName()->setText("");
        view->getLineName()->hide();
        view->getLabelName()->hide();
        view->getLabelCompany()->setText("<b>Nazwisko i imię:</b>");
        view->getLabelTIN()->setText("NIP: ");
    }
}

void ContractorDialogController::phoneChanged(QModelIndex topLeft,QModelIndex bottomRight)
{
    QModelIndex index = bottomRight = topLeft;
    if(index.column() == 3) // 3 - główny telefon
    {
        // jeśli zmieniony wiersz jest zaznaczony jako tel główny
        if(phoneModel->item(index.row(), 3)->checkState() == Qt::Checked)
        {
            for(int i = 0; i < phoneModel->rowCount(); i++)
            {
                if(i != index.row())
                    phoneModel->item(i, 3)->setCheckState(Qt::Unchecked); // odznacz pozostałe tele
            }
        }
    }
}

void ContractorDialogController::initTablePhone()
{
    phoneModel=new QStandardItemModel();
    QStringList phoneHeaders; phoneHeaders<<"id"<<"Nazwa"<<"Numer"<<"Główny";
    phoneModel->setHorizontalHeaderLabels(phoneHeaders);
    view->getTablePhones()->setModel(phoneModel);
    view->getTablePhones()->setColumnHidden(0,true);
    view->getTablePhones()->setColumnWidth(1,200);
    view->getTablePhones()->setColumnWidth(2,160);
    view->getTablePhones()->setColumnWidth(3,60);
    view->getTablePhones()->verticalHeader()->setDefaultSectionSize(20);
    view->getTablePhones()->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->getTablePhones()->setSelectionMode(QAbstractItemView::SingleSelection);;
    view->getTablePhones()->horizontalHeader()->setStretchLastSection(true);
    view->getTablePhones()->horizontalHeader()->setMaximumHeight(20);
    connect(phoneModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(phoneChanged(QModelIndex,QModelIndex)));
}

void ContractorDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = tableStateManager->getState("CONTRACTOR_DIAL_TAB_PHONES");
    view->getTablePhones()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void ContractorDialogController::saveTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = view->getTablePhones()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("CONTRACTOR_DIAL_TAB_PHONES");
    if(state != oldState)
        tableStateManager->saveState("CONTRACTOR_DIAL_TAB_PHONES", state);

    delete tableStateManager;
}

