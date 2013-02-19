#include "DocumentModel.h"

DocumentModel::DocumentModel() {
    peopleModel = new PeopleModel();
    documentPlaceModel = new DocumentPlaceModel();
    currentWarehouse = ApplicationManager::getInstance()->getWarehouse();
}

DocumentModel::~DocumentModel() {
    delete peopleModel;
    delete documentPlaceModel;
}

