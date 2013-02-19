#include "SettingsUnitsController.h"

SettingsUnitsController::SettingsUnitsController(QWidget *parent) :
    SettingsAbstractItemController(parent)
{
    this->view = new SettingsUnitsView(this,parent);
    unitModel = new UnitModel();
    setModel();
}

SettingsUnitsController::~SettingsUnitsController()
{
    delete unitModel;
}

void SettingsUnitsController::setModel(QString currentValue)
{
    fillBox(view->getBoxUnits(),unitModel->getUnits());

    int currentIndex;
    if (currentValue == "") currentIndex = 0;
    else currentIndex = view->getBoxUnits()->findText(currentValue);
    view->getBoxUnits()->setCurrentIndex(currentIndex);

    showUnit();
}

void SettingsUnitsController::fillBox(QComboBox *box,QVector<Unit> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void SettingsUnitsController::showUnit()
{
    Unit u = unitModel->getUnit(view->getBoxUnits()->itemData(view->getBoxUnits()->currentIndex()).toInt());
    view->getLineName()->setText(u.getName());
    view->getSpinZeroPlaces()->setValue(u.getZeroPlaces());
    view->getLineName()->setEnabled(false);
    view->getSpinZeroPlaces()->setEnabled(false);
    view->getPushEdit()->setEnabled(true);
    view->getPushDelete()->setEnabled(true);
    buttonStatus = SettingsAbstractItemController::IDLE;
}

void SettingsUnitsController::addUnit()
{
    view->getLineName()->setText("");
    view->getSpinZeroPlaces()->setValue(0);
    view->getLineName()->setEnabled(true);
    view->getSpinZeroPlaces()->setEnabled(true);
    view->getPushEdit()->setEnabled(false);
    view->getPushDelete()->setEnabled(false);
    buttonStatus = SettingsAbstractItemController::ADD;
}

void SettingsUnitsController::editUnit()
{
    view->getLineName()->setEnabled(true);
    view->getSpinZeroPlaces()->setEnabled(true);
    view->getPushDelete()->setEnabled(false);
    buttonStatus = SettingsAbstractItemController::EDIT;
}

void SettingsUnitsController::deleteUnit()
{
    if (view->getMessageBox()->createQuestionBox("Usuwanie wybranej jednostki miary!") == MessageBox::YES)
    {
       unitModel->removeUnit(view->getBoxUnits()->itemData(view->getBoxUnits()->currentIndex()).toInt());
       setModel();
       view->emitChangesWereMade();
    }
}

void SettingsUnitsController::saveUnit()
{
    if (checkFillInTheFields()) return;

    Unit u(view->getBoxUnits()->itemData(view->getBoxUnits()->currentIndex()).toInt(),
           view->getLineName()->text(),view->getSpinZeroPlaces()->value());

    if(buttonStatus == SettingsAbstractItemController::EDIT)
    {
        if (view->getMessageBox()->createQuestionBox("Edycja wybranej jednostki miary!") == MessageBox::YES)
        {
            unitModel->editUnit(u);
            view->emitChangesWereMade();
        }
    }
    else if(buttonStatus == SettingsAbstractItemController::ADD)
    {
        if (view->getMessageBox()->createQuestionBox("Definiowanie nowej jednostki miary!") == MessageBox::YES)
        {
            unitModel->addUnit(u);
            view->emitChangesWereMade();
        }
    }

    setModel(u.getName());
}

bool SettingsUnitsController::checkFillInTheFields()
{
    if (view->getLineName()->text().isEmpty())
    {
        view->getMessageBox()->createInfoBox("Uzupełnij wymagane pola. ");
        return true;
    }
    return false;
}

SettingsUnitsView * SettingsUnitsController::getView() { return view;}
UnitModel *SettingsUnitsController::getModel() {return unitModel;}
