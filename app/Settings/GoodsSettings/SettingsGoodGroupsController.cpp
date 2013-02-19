#include "SettingsGoodGroupsController.h"

SettingsGoodGroupsController::SettingsGoodGroupsController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsGoodGroupsView(this,parent);
    featureModel = new FeatureModel();
    featureForRestModel = new FeatureModel();
    featureTVModel = new SettingsTVModel();
    featureForRestTVModel = new SettingsTVModel();
    goodsGroupModel = new GoodsGroupModel();

    setModel();
    setTablesModel();
}

SettingsGoodGroupsController::~SettingsGoodGroupsController()
{
    delete featureTVModel;
    delete featureForRestTVModel;
    delete featureModel;
    delete featureForRestModel;
    delete goodsGroupModel;
}

void SettingsGoodGroupsController::setModel(QString currentValue)
{
    fillBox(view->getBoxGroup(),goodsGroupModel->getGoodsGroups());

    int currentIndex;
    if (currentValue == "") currentIndex = 0;
    else currentIndex = view->getBoxGroup()->findText(currentValue);
    view->getBoxGroup()->setCurrentIndex(currentIndex);

    chooseGroup();
}

void SettingsGoodGroupsController::setTablesModel()
{
    setTables(1);
    view->getTableFeatures()->setFeatureModel(featureForRestTVModel);
    view->getTableGGFeatures()->setFeatureModel(featureTVModel);
}

void SettingsGoodGroupsController::fillBox(QComboBox *box,QVector<GoodsGroup> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void SettingsGoodGroupsController::setTables(int groupId)
{
    featureTVModel->getFeaturesForGroup(groupId);
    featureForRestTVModel->getRestFeaturesForGroup(groupId);
}

void SettingsGoodGroupsController::chooseGroup()
{
    view->getLineName()->setText(view->getBoxGroup()->currentText());
    view->getLineName()->setDisabled(true);
    view->getPushEdit()->setEnabled(true);
    view->getPushDelete()->setEnabled(true);
    buttonStatus = SettingsAbstractItemController::IDLE;

    setTables(view->getBoxGroup()->itemData(view->getBoxGroup()->currentIndex()).toInt());
}

void SettingsGoodGroupsController::editGroup()
{
    view->getPushDelete()->setDisabled(true);
    view->getLineName()->setEnabled(true);
    buttonStatus = SettingsAbstractItemController::EDIT;
}

void SettingsGoodGroupsController::newGroup()
{
    view->getPushEdit()->setDisabled(true);
    view->getPushDelete()->setDisabled(true);
    view->getLineName()->setEnabled(true);
    view->getLineName()->setText("");
    buttonStatus = SettingsAbstractItemController::ADD;
}

void SettingsGoodGroupsController::saveGroup()
{
    if (checkFillInTheFields()) return;
    GoodsGroup gg(view->getBoxGroup()->itemData(view->getBoxGroup()->currentIndex()).toInt(),
                                                        view->getLineName()->text());

    if(buttonStatus == SettingsAbstractItemController::EDIT)
    {
        if (view->getMessageBox()->createQuestionBox("Edycja wybranej grupy dóbr!") == MessageBox::YES)
        {
            goodsGroupModel->editGoodsGroup(gg);
            view->emitChangesWereMade();
        }
    }
    else if(buttonStatus == SettingsAbstractItemController::ADD)
    {
        if (view->getMessageBox()->createQuestionBox("Definiowanie nowej grupy dóbr!") == MessageBox::YES)
        {
            goodsGroupModel->addGoodsGroup(gg);
            view->emitChangesWereMade();
        }
    }

    setModel(gg.getName());
}

void SettingsGoodGroupsController::deleteGroup()
{
    if (view->getMessageBox()->createQuestionBox("Usuwanie wybranej grupy dóbr !") == MessageBox::YES)
    {
        goodsGroupModel->removeGoodsGroup(view->getBoxGroup()->itemData(view->getBoxGroup()->currentIndex()).toInt());
        view->emitChangesWereMade();
    }

    setModel();
}

void SettingsGoodGroupsController::addFeature()
{
    if(view->getTableFeatures()->currentIndex().isValid())
    {
        int goodGroup = view->getBoxGroup()->itemData(view->getBoxGroup()->currentIndex()).toInt();
        featureModel->addFeatureToGroup(view->getTableFeatures()->getId(),goodGroup);
        setTables(goodGroup);
        view->emitChangesWereMade();
    }
    else
    {
        view->getMessageBox()->createInfoBox("Zaznacz cechę, którą chcesz dodać!");
    }
}

void SettingsGoodGroupsController::deleteFeature()
{
    if(view->getTableGGFeatures()->currentIndex().isValid())
    {
        int currentIndex = view->getBoxGroup()->itemData(view->getBoxGroup()->currentIndex()).toInt();
        featureForRestModel->removeFeatureFromGroup(view->getTableGGFeatures()->getId(),currentIndex);
        setTables(currentIndex);
        view->emitChangesWereMade();
    }
    else
    {
        view->getMessageBox()->createInfoBox("Zaznacz cechę, którą chcesz usunąć!");
    }
}

bool SettingsGoodGroupsController::checkFillInTheFields()
{
    if (view->getLineName()->text().isEmpty())
    {
        view->getMessageBox()->createInfoBox("Uzupełnij wymagane pola. ");
        return true;
    }
    return false;
}

SettingsGoodGroupsView *SettingsGoodGroupsController::getView() { return view;}
FeatureModel *SettingsGoodGroupsController::getFeatureForRestModel() { return featureForRestModel; }
FeatureModel *SettingsGoodGroupsController::getFeatureModel() {return featureModel;}
GoodsGroupModel *SettingsGoodGroupsController::getGoodsGroupModel() { return goodsGroupModel; }
