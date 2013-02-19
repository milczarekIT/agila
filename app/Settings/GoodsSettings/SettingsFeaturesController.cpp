#include "SettingsFeaturesController.h"

SettingsFeaturesController::SettingsFeaturesController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsFeaturesView(this,parent);
    featureModel = new FeatureModel();
    setModel();
}

SettingsFeaturesController::~SettingsFeaturesController()
{
    delete featureModel;
}

void SettingsFeaturesController::setModel(QString currentValue)
{
    fillBox(view->getBoxFeatures(),featureModel->getFeatures());

    int currentIndex;
    if (currentValue == "") currentIndex = 0;
    else currentIndex = view->getBoxFeatures()->findText(currentValue);
    view->getBoxFeatures()->setCurrentIndex(currentIndex);

    showFeatures();
}

void SettingsFeaturesController::fillBox(QComboBox *box,QVector<Feature> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void SettingsFeaturesController::showFeatures()
{
     Feature f = featureModel->getFeature(
                view->getBoxFeatures()->itemData(view->getBoxFeatures()->currentIndex()).toInt());
     view->getLineName()->setText(f.getName());
     view->getLineName()->setEnabled(false);
     view->getPushEdit()->setEnabled(true);
     view->getPushDelete()->setEnabled(true);
     buttonStatus = SettingsAbstractItemController::IDLE;
}

 void SettingsFeaturesController::addFeature()
 {
     view->getLineName()->setText("");
     view->getLineName()->setEnabled(true);
     view->getPushEdit()->setEnabled(false);
     view->getPushDelete()->setEnabled(false);
     buttonStatus = SettingsAbstractItemController::ADD;
 }

 void SettingsFeaturesController::editFeature()
 {
     view->getLineName()->setEnabled(true);
     view->getPushDelete()->setEnabled(false);
     buttonStatus = SettingsAbstractItemController::EDIT;
 }

 void SettingsFeaturesController::deleteFeature()
 {
     if (view->getMessageBox()->createQuestionBox("Usuwanie wybranej  cechy towarowej !") == MessageBox::YES)
     {
        featureModel->removeFeature(view->getBoxFeatures()->itemData(
                                                view->getBoxFeatures()->currentIndex()).toInt());
        setModel();
        view->emitChangesWereMade();
     }
 }

 void SettingsFeaturesController::saveFeature()
 {
     if (checkFillInTheFields()) return ;

     Feature f(view->getBoxFeatures()->itemData(view->getBoxFeatures()->currentIndex()).toInt(),
                                                        view->getLineName()->text());

     if(buttonStatus == SettingsAbstractItemController::EDIT)
     {
         if (view->getMessageBox()->createQuestionBox("Edycja wybranej cechy towarowej !") == MessageBox::YES)
         {
            featureModel->editFeature(f);
            view->emitChangesWereMade();
         }
     }
     else if(buttonStatus == SettingsAbstractItemController::ADD)
     {
         if (view->getMessageBox()->createQuestionBox("Definiowanie nowej cechy towarowej !") == MessageBox::YES)
         {
            featureModel->addFeature(f);
            view->emitChangesWereMade();
        }
     }

     setModel(f.getName());
 }

 bool SettingsFeaturesController::checkFillInTheFields()
 {
     if (view->getLineName()->text().isEmpty())
     {
         view->getMessageBox()->createInfoBox("Uzupełnij wymagane pola. ");
         return true;
     }
     return false;
 }

 SettingsFeaturesView * SettingsFeaturesController::getView() {return view;}
 FeatureModel *SettingsFeaturesController::getModel() {return featureModel;}


