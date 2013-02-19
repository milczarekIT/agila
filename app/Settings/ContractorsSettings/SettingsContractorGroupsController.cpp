#include "SettingsContractorGroupsController.h"

SettingsContractorGroupsController::SettingsContractorGroupsController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsContractorGroupsView(this,parent);
    contractorGroupModel = new ContractorGroupModel();
    setModel();
}


SettingsContractorGroupsController::~SettingsContractorGroupsController()
{
    delete contractorGroupModel;
}

void SettingsContractorGroupsController::setModel(QString currentValue)
{
    fillBox(view->getBoxGroup(),contractorGroupModel->getContractorGroups());

    int currentIndex;
    if (currentValue == "") currentIndex = 0;
    else currentIndex = view->getBoxGroup()->findText(currentValue);
    view->getBoxGroup()->setCurrentIndex(currentIndex);

    chooseGroup();
}

void SettingsContractorGroupsController::fillBox(QComboBox *box,QVector<ContractorGroup> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void SettingsContractorGroupsController::chooseGroup()
{
    view->getLineName()->setText(view->getBoxGroup()->currentText());
    view->getLineName()->setDisabled(true);
    view->getPushEdit()->setEnabled(true);
    view->getPushDelete()->setEnabled(true);
    buttonStatus = SettingsAbstractItemController::IDLE;
}

void SettingsContractorGroupsController::editGroup()
{
    view->getPushDelete()->setDisabled(true);
    view->getLineName()->setEnabled(true);
    buttonStatus = SettingsAbstractItemController::EDIT;
}

void SettingsContractorGroupsController::newGroup()
{
    view->getPushEdit()->setDisabled(true);
    view->getPushDelete()->setDisabled(true);
    view->getLineName()->setEnabled(true);
    view->getLineName()->setText("");
    buttonStatus = SettingsAbstractItemController::ADD;
}

void SettingsContractorGroupsController::saveGroup()
{
    if (checkFillInTheFields()) return;

    ContractorGroup cg(view->getBoxGroup()->itemData(view->getBoxGroup()->currentIndex()).toInt(),
                            view->getLineName()->text());

    if(buttonStatus == SettingsAbstractItemController::EDIT)
    {
        if (view->getMessageBox()->createQuestionBox("Edycja wybranej grupy kontrahenckiej!") == MessageBox::YES)
        {
            contractorGroupModel->editContractorGroup(cg);
            view->emitChangesWereMade();
        }
    }
    else if(buttonStatus == SettingsAbstractItemController::ADD)
    {
        if (view->getMessageBox()->createQuestionBox("Definiowanie nowej grupy kontrahenckiej!") == MessageBox::YES)
        {
            contractorGroupModel->addContractorGroup(cg);
            view->emitChangesWereMade();
        }
    }

    setModel(cg.getName());
}

void SettingsContractorGroupsController::deleteGroup()
{
    if (view->getMessageBox()->createQuestionBox("Usuwanie wybranej grupy kontrahentów !") == MessageBox::YES)
    {
         contractorGroupModel->removeContractorGroup(
                 view->getBoxGroup()->itemData(view->getBoxGroup()->currentIndex()).toInt());
         view->emitChangesWereMade();
    }

    setModel();
}

bool SettingsContractorGroupsController::checkFillInTheFields()
{
    if (view->getLineName()->text().isEmpty())
    {
        view->getMessageBox()->createInfoBox("Uzupełnij wymagane pola. ");
        return true;
    }
    return false;
}


ContractorGroupModel *SettingsContractorGroupsController::getContractorGroupModel() { return contractorGroupModel;}
SettingsContractorGroupsView *SettingsContractorGroupsController::getView() {return view;}
