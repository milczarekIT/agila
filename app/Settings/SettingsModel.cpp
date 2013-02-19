#include "SettingsModel.h"

SettingsModel::SettingsModel()
{
}

SettingsModel::~SettingsModel()
{
}

/**************************
 * Default Document Place *
 **************************/

void SettingsModel::setDefaultDocumentPlace(QString name)
{
    DocumentPlaceModel *documentPlaceModel = new DocumentPlaceModel();
    int documentPlaceId = documentPlaceModel->getDocumentPlaceId(name);

    try {
        query = new QSqlQuery(Database::getInstance().db);
        query->prepare("UPDATE document_places SET is_default = true WHERE id_place = ?");
        query->addBindValue(documentPlaceId);
        query->exec();

        if(query->lastError().isValid())
            throw new SQLException("SettingsModel::setDefaultDocumentPlace", query);

    } catch(SQLException *e) {
         qDebug() << e->getMessage();
    }
}

SimpleStructure SettingsModel::getDefualtDocumentPlace()
{
    SimpleStructure defaultDocumentPlace;
    try {
        query = new QSqlQuery(Database::getInstance().db);
        query->prepare("SELECT id_place, name FROM document_places WHERE is_default = true");
        query->exec();

        if(query->lastError().isValid())
            throw new SQLException("SettingsModel::getDefualtDocumentPlace", query);

        if(query->size() > 0)
        {
            query->first();

            defaultDocumentPlace.setId(query->value(0).toInt());
            defaultDocumentPlace.setName(query->value(1).toString());
        }

    } catch(SQLException *e) {
         qDebug() << e->getMessage();
    }

    return defaultDocumentPlace;
}
