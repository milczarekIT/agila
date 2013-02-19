#include "SettingsMOPController.h"

SettingsMOPController::SettingsMOPController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsMOPView(this);
    mopModel = new MOPModel();
    setModel();
}

SettingsMOPController::~SettingsMOPController()
{
    delete mopModel;
}

void SettingsMOPController::setModel(QString currentValue)
{
    fillBox(view->getBoxMOPs(), mopModel->getMethodsOfPayment());

    int currentIndex;
    if (currentValue == "") currentIndex = 0;
    else currentIndex = view->getBoxMOPs()->findText(currentValue);
    view->getBoxMOPs()->setCurrentIndex(currentIndex);

    showMOPs();
}

void SettingsMOPController::fillBox(QComboBox *box,QVector<MethodOfPayment> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void SettingsMOPController::showMOPs()
{
    MethodOfPayment m = mopModel->getMethodOfPayment(view->getBoxMOPs()->itemData(
                                      view->getBoxMOPs()->currentIndex()).toInt());
    view->getLineName()->setText(m.getName());
    view->getSpinNumberOfDays()->setValue(m.getMaturity());
    view->getLineName()->setEnabled(false);
    view->getSpinNumberOfDays()->setEnabled(false);
    view->getPushEdit()->setEnabled(true);
    view->getPushDelete()->setEnabled(true);
    buttonStatus = SettingsAbstractItemController::IDLE;
}

void SettingsMOPController::addMOP()
{
    view->getLineName()->setText("");
    view->getSpinNumberOfDays()->setValue(0);
    view->getLineName()->setEnabled(true);
    view->getSpinNumberOfDays()->setEnabled(true);
    view->getPushEdit()->setEnabled(false);
    view->getPushDelete()->setEnabled(false);
    buttonStatus = SettingsAbstractItemController::ADD;
}

void SettingsMOPController::editMOP()
{
    view->getLineName()->setEnabled(true);
    view->getSpinNumberOfDays()->setEnabled(true);
    view->getPushDelete()->setEnabled(false);
    buttonStatus = SettingsAbstractItemController::EDIT;
}

void SettingsMOPController::deleteMOP()
{
    if (view->getMessageBox()->createQuestionBox("Usuwanie wybranego sposobu płatności !") == MessageBox::YES)
    {
        mopModel->removeMethodOfPayment(view->getBoxMOPs()->itemData(
                                                view->getBoxMOPs()->currentIndex()).toInt());
        setModel();
        view->emitChangesWereMade();
    }
}

void SettingsMOPController::saveMOP()
{
    if (checkFillInTheFields()) return;

    MethodOfPayment mop(view->getBoxMOPs()->itemData(view->getBoxMOPs()->currentIndex()).toInt(),
                                view->getLineName()->text(),view->getSpinNumberOfDays()->value());

    if(buttonStatus == SettingsAbstractItemController::EDIT)
    {
        if (view->getMessageBox()->createQuestionBox("Edycja wybranego sposobu płatności !") == MessageBox::YES)
        {
            mopModel->editMethodOfPayment(mop);
            view->emitChangesWereMade();
        }
    }
    else if(buttonStatus == SettingsAbstractItemController::ADD)
    {
        if (view->getMessageBox()->createQuestionBox("Definiowanie nowego sposobu płatności !") == MessageBox::YES)
        {
            mopModel->addMethodOfPayment(mop);
            view->emitChangesWereMade();
        }
    }
    setModel(mop.getName());
}

bool SettingsMOPController::checkFillInTheFields()
{
    if (view->getLineName()->text().isEmpty())
    {
        view->getMessageBox()->createInfoBox("Uzupełnij wymagane pola. ");
        return true;
    }
    return false;
}

SettingsMOPView * SettingsMOPController::getView() {return view;}
MOPModel *SettingsMOPController::getModel() {return mopModel;}


