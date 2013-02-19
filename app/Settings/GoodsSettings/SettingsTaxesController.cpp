#include "SettingsTaxesController.h"

SettingsTaxesController::SettingsTaxesController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsTaxesView(this,parent);
    taxModel = new TaxModel();
    preferences = new SettingsPreferencesService();
    setModel();
}

SettingsTaxesController::~SettingsTaxesController()
{
    delete taxModel;
}

void SettingsTaxesController::setModel(QString currentValue)
{
    updateTable();
    qDebug()<<preferences->getTaxIdForRR();
    view->getLineTaxId()->setText(taxModel->getTax(preferences->getTaxIdForRR()).getName());
    if (currentValue != "")
        setItemForValue(currentValue);
}

void SettingsTaxesController::updateTable()
{
    view->setTaxes(taxModel->getTaxes(false));
    view->getTableTaxes()->setRowCount(view->getTaxes().size());
    for(int i=0;i<view->getTaxes().size();i++)
        view->createItem(new QTableWidgetItem(), i);

}

void SettingsTaxesController::setItemForValue(QString value)
{
    for (int i=0; i<view->getTableTaxes()->rowCount(); i++ )
        if (value == view->getTableTaxes()->item(i,0)->text())
            view->getTableTaxes()->setCurrentCell(i,0);
}

void SettingsTaxesController::setData()
{
    QString value;
    Tax t = taxModel->getTax(view->getTableTaxes()->currentItem()->data(Qt::UserRole).toInt());

    if(t.getName().contains("Stawka podstawowa")) view->getBoxName()->setCurrentIndex(0);
    else if(t.getName().contains("Stawka obniżona")) view->getBoxName()->setCurrentIndex(1);
    else if(t.getName().contains("Stawka zw.")) view->getBoxName()->setCurrentIndex(2);

    view->getLineValue()->setText(value.setNum(t.getValue()));
    view->getLineShortName()->setText(t.getShortName());
    view->getBoxName()->setDisabled(true);
    view->getLineValue()->setDisabled(true);
    view->getPushEdit()->setEnabled(true);
    view->getPushNew()->setEnabled(true);
    buttonStatus = SettingsAbstractItemController::IDLE;
}

void SettingsTaxesController::setTaxIdData()
{
   Tax t = taxModel->getTax(view->getTableTaxes()->currentItem()->data(Qt::UserRole).toInt());
   preferences->setTaxIdForRR(t.getId());
   view->getLineTaxId()->setText(t.getName());
   qDebug()<<preferences->getTaxIdForRR();
}
void SettingsTaxesController::signGenerating(QString value)
{
    if (value == "") view->getLineShortName()->setText("");
    else view->getLineShortName()->setText(value + "%");
}

void SettingsTaxesController::editTax()
{
    int index = view->getTableTaxes()->currentItem()->data(Qt::UserRole).toInt();
    if(taxModel->getTax(index).getName().contains("Stawka zw."))
    {
        view->getMessageBox()->createInfoBox("Stawka zw. nie podlega edycji !");
        buttonStatus = SettingsAbstractItemController::IDLE;
    }
    else
    {
        view->getBoxName()->setEnabled(true);
        buttonStatus = SettingsAbstractItemController::EDIT;
    }
}

void SettingsTaxesController::newTax()
{
    view->getBoxName()->setCurrentIndex(0);
    view->getLineShortName()->setText("");
    view->getLineValue()->setText("");
    view->getBoxName()->setEnabled(true);
    view->getLineValue()->setEnabled(true);
    view->getPushEdit()->setDisabled(true);
    buttonStatus = SettingsAbstractItemController::ADD;
}

void SettingsTaxesController::deleteTax()
{
    int index = view->getTableTaxes()->currentItem()->data(Qt::UserRole).toInt();
    if(taxModel->getTax(index).getName().contains("Stawka zw."))
    {
        view->getMessageBox()->createInfoBox("Nie można usunąć stawki zw. !");
        buttonStatus = SettingsAbstractItemController::IDLE;
    }
    else
    {
        if (view->getMessageBox()->createQuestionBox("Usuwanie wybranej stawki podatkowej!") == MessageBox::YES)
        {
            taxModel->removeTax(index);
            updateTable();
            view->emitChangesWereMade();
        }
    }
    setData();
}

void SettingsTaxesController::saveTax()
{
    if (checkFillInTheFields()) return;

    int index = view->getTableTaxes()->currentItem()->data(Qt::UserRole).toInt();
    QString value;
    Tax t;

    if(buttonStatus == SettingsAbstractItemController::EDIT)
    {
        if (view->getMessageBox()->createQuestionBox("Edycja wybranej stawki podatkowej!") == MessageBox::YES)
        {
            t = taxModel->getTax(index);
            t.setName(view->getBoxName()->currentText() + " " + value.setNum(t.getValue()) + "%");
            t.setShortName(view->getLineShortName()->text());
            taxModel->editTax(t);
            view->emitChangesWereMade();
        }
    }
    else if(buttonStatus == SettingsAbstractItemController::ADD)
    {
        if (view->getMessageBox()->createQuestionBox("Definiowanie nowej stawki podatkowej!") == MessageBox::YES)
        {
            t.setName(view->getBoxName()->currentText() + " " + view->getLineValue()->text() + "%");
            t.setValue(view->getLineValue()->text().toFloat());
            t.setShortName(view->getLineShortName()->text());
            t.setActiveInApp(true);
            taxModel->addTax(t);
            setModel(t.getName());
            view->emitChangesWereMade();
        }
    }
    setData();
}

void SettingsTaxesController::changeActivate()
{
    int index = view->getTableTaxes()->currentItem()->data(Qt::UserRole).toInt();
    Tax t = taxModel->getTax(index);

    if(view->getTableTaxes()->currentItem()->checkState() == Qt::Checked)
    {
        t.setActiveInApp(true);
        taxModel->editTax(t);
    }
    else
    {
        t.setActiveInApp(false);
        taxModel->editTax(t);
    }
    view->emitChangesWereMade();
}

void SettingsTaxesController::enableRateNull()
{
    if (view->getBoxName()->currentText().contains("Stawka zw."))
        view->getBoxName()->setCurrentIndex(0);
}

bool SettingsTaxesController::checkFillInTheFields()
{
    if (view->getLineValue()->text().isEmpty() | view->getLineShortName()->text().isEmpty())
    {
        view->getMessageBox()->createInfoBox("Uzupełnij wymagane pola. ");
        return true;
    }
    return false;
}

SettingsTaxesView *SettingsTaxesController::getView() {return view;}
