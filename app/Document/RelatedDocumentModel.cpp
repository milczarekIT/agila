#include "RelatedDocumentModel.h"

RelatedDocumentModel::RelatedDocumentModel()
{
}

QVector<SimpleDocumentInfo> RelatedDocumentModel::getRelatedDocuments(QString symbol)
{
    QStringList relatedDocumentsSymbols = this->getRelatedDocumentsSymbols(symbol);
    QVector<SimpleDocumentInfo> relatedDocuments;

    for(int i = 0; i < relatedDocumentsSymbols.size(); i++)
        relatedDocuments.push_back(getSimpleDocumentInfo(relatedDocumentsSymbols.at(i)));

    return relatedDocuments;
}

QStringList RelatedDocumentModel::getRelatedDocumentsSymbols(QString symbol)
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    QStringList relatedDocumentsSymbols;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT base_document FROM  linked_documents WHERE linked_document = ? AND warehouse = ? "
                    "UNION "
                    "SELECT linked_document FROM linked_documents WHERE base_document = ? AND warehouse = ? ");
    query->addBindValue(symbol);
    query->addBindValue(warehouseId);
    query->addBindValue(symbol);
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("RelatedDocumentModel::getRelatedDocumentsSymbols", query);

    while(query->next())
        relatedDocumentsSymbols.append(query->value(0).toString());

    delete query;

    return relatedDocumentsSymbols;
}

QVector<SimpleDocumentInfo> RelatedDocumentModel::getRelatedDocumentsByType(QString symbol, QString type) {
    QVector<SimpleDocumentInfo> relatedDocumentsInType;
    QVector<SimpleDocumentInfo> relatedDocuments = this->getRelatedDocuments(symbol);

    for(int i = 0; i < relatedDocuments.size(); i++) {
        if(relatedDocuments[i].getType() == type)
            relatedDocumentsInType.push_back(relatedDocuments[i]);
    }

    return relatedDocumentsInType;
}

SimpleDocumentInfo RelatedDocumentModel::getSimpleDocumentInfo(QString symbol) {
    DocumentInfoModel *documentInfoModel = new DocumentInfoModel();
    QString familyId = documentInfoModel->getDocumentFamilyBySymbol(symbol).getId();
    delete documentInfoModel;


    SimpleDocumentInfo simpleInfo;
    simpleInfo.setSymbol(symbol);

    if(familyId != "")
    {
        QString queryString;
        if(familyId == "SALE")
            queryString = "SELECT type, document_date, total FROM sale_documents WHERE symbol = ? AND warehouse = ?";
        else if(familyId == "STORE")
            queryString = "SELECT type, document_date, total FROM warehouse_documents WHERE symbol = ? AND warehouse = ?";
        else if(familyId == "CASH")
            queryString = "SELECT type, document_date, value FROM cash_documents WHERE symbol = ?  AND warehouse = ?";
        else if(familyId == "ORDER")
            queryString = "SELECT type, document_date, total FROM orders WHERE symbol = ?  AND warehouse = ?";
        else if(familyId == "PURCHASE") {
            queryString = QString("SELECT type, document_date, total FROM purchase_documents WHERE symbol = ?  AND warehouse = ? ")
                          + QString("UNION SELECT type, document_date, 0 FROM documents_nk WHERE symbol = ?  AND warehouse = ?");
        }

        if(queryString.isEmpty())
            return simpleInfo;
        else
        {
            QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
            query->prepare(queryString);
            query->addBindValue(symbol);
            QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
            query->addBindValue(warehouseId);
            if(familyId == "PURCHASE") {
                query->addBindValue(symbol);
                query->addBindValue(warehouseId);

            }
            query->exec();

            if(this->isQueryError(query)) {
                throw new SQLException("RelatedDocumentModel::getSimpleDocumentInfo", query);
            }

            if(query->size() > 0) {
                query->first();

                simpleInfo.setSymbol(symbol);
                simpleInfo.setType(query->value(0).toString());
                simpleInfo.setDocumentDate(query->value(1).toDate());
                simpleInfo.setTotal(query->value(2).toDouble());
            }

            delete query;
        }
    }

    return simpleInfo;
}

void RelatedDocumentModel::addLinkToDocument(QString baseDocument, QString linkedDocument)
{
    if(linkedDocument != "" && baseDocument != "")
    {
        QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
        query = new QSqlQuery(Database::getInstance().db);

        query->prepare("INSERT INTO linked_documents (base_document, linked_document, warehouse) VALUES (?, ?, ?) ");
        query->addBindValue(baseDocument);
        query->addBindValue(linkedDocument);
        query->addBindValue(warehouseId);
        query->exec();

        if(this->isQueryError(query))
            throw new SQLException("RelatedDocumentModel::addLinkToDocument", query);

        delete query;
    }
}

void RelatedDocumentModel::editLinkToBaseDocument(QString baseDocument, QString linkedDocument)
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE linked_documents SET base_document = ? WHERE linked_document = ? AND warehouse = ?");
    query->addBindValue(baseDocument);
    query->addBindValue(linkedDocument);
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("RelatedDocumentModel::editLinkToBaseDocument", query);
}

void RelatedDocumentModel::editLinkToLinkedDocument(QString baseDocument, QString linkedDocument)
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE linked_documents SET linked_document = ? WHERE base_document = ? AND warehouse = ?");
    query->addBindValue(linkedDocument);
    query->addBindValue(baseDocument);
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("RelatedDocumentModel::editLinkToLinkedDocument", query);

    delete query;
}

void RelatedDocumentModel::removeLinkToDocument(QString baseDocument, QString linkedDocument)
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM linked_documents WHERE base_document = ? AND linked_document = ? AND warehouse = ?");
    query->addBindValue(baseDocument);
    query->addBindValue(linkedDocument);
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("RelatedDocumentModel::deleteLinkToDocument", query);

    delete query;
}

void RelatedDocumentModel::removeLinksToDocument(QString document) {
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM linked_documents WHERE base_document = ? OR linked_document = ? AND warehouse = ?");
    query->addBindValue(document);
    query->addBindValue(document);
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("RelatedDocumentModel::deleteLinkToDocument", query);

    delete query;
}

bool RelatedDocumentModel::isDocumentSymbolInVector(QString documentSymbol, QVector<SimpleDocumentInfo> vector)
{
    for(int i =0; i < vector.size(); i++)
    {
        if(vector[i].getSymbol() == documentSymbol)
            return true;
    }

    return false;
}

bool RelatedDocumentModel::isDocumentInApp(QString symbol) {
    bool documentInApp = false;

    DocumentInfoModel *documentInfoModel = new DocumentInfoModel();
    QString familyId = documentInfoModel->getDocumentFamilyBySymbol(symbol).getId();
    delete documentInfoModel;

    if(!familyId.isEmpty())
    {
        QString queryString;
        if(familyId == "SALE")
            queryString = "SELECT * FROM sale_documents WHERE symbol = ? AND warehouse = ?";
        else if(familyId == "STORE")
            queryString = "SELECT * FROM store_documents WHERE symbol = ? AND warehouse = ?";
        else if(familyId == "CASH")
            queryString = "SELECT * FROM cash_documents WHERE symbol = ? AND warehouse = ?";
        else if(familyId == "ORDER")
            queryString = "SELECT * FROM orders WHERE symbol = ? AND warehouse = ?";
        else if(familyId == "PURCHASE")
        {
            queryString = "SELECT symbol FROM purchase_documents WHERE symbol = ? AND warehouse = ? ";
            queryString += "UNION SELECT symbol FROM documents_nk  WHERE symbol = ? AND warehouse = ?";
        }

        if(!queryString.isEmpty())
        {
            QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
            query = new QSqlQuery(Database::getInstance().db);
            query->prepare(queryString);
            query->addBindValue(symbol);
            query->addBindValue(warehouseId);
            query->exec();

            if(this->isQueryError(query))
                throw new SQLException("RelatedDocumentModel::isDocumentInApp", query);

            documentInApp = (query->size() > 0);
            delete query;
        }
    }

    return documentInApp;
}
