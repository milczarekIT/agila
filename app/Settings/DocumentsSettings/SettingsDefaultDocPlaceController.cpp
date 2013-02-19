#include "SettingsDefaultDocPlaceController.h"

SettingsDefaultDocPlaceController::SettingsDefaultDocPlaceController(QObject *parent) :
    SettingsAbstractItemController(parent)
{
    view = new SettingsDefaultDocPlaceView(this);
    smodel = new SettingsModel();
    setModel();
}

void SettingsDefaultDocPlaceController::setModel()
{
    view->getDefaultDocumentPlace()->setText(smodel->getDefualtDocumentPlace().getName());
}

SettingsDefaultDocPlaceController::~SettingsDefaultDocPlaceController()
{
    delete smodel;
}

void SettingsDefaultDocPlaceController::defaultDocPlaceChanged()
{
    if(checkFillInTheFields()) return;

    QString currentValue = smodel->getDefualtDocumentPlace().getName();
    QString changedValue = view->getDefaultDocumentPlace()->text();

    if (currentValue != changedValue)
    {
        if(view->getMessageBox()->createQuestionBox("Edycja domyślnego miejsca wystawiania dokumentów !") == MessageBox::YES)
        {
            smodel->setDefaultDocumentPlace(changedValue);
            view->emitChangesWereMade();
        }
    }
}

bool SettingsDefaultDocPlaceController::checkFillInTheFields()
{
    if (view->getDefaultDocumentPlace()->text().isEmpty())
    {
        view->getMessageBox()->createInfoBox("Uzupełnij wymagane pola. ");
        return true;
    }
    return false;
}

SettingsDefaultDocPlaceView *SettingsDefaultDocPlaceController::getView() {return view;}
SettingsModel *SettingsDefaultDocPlaceController::getModel() { return smodel; }
