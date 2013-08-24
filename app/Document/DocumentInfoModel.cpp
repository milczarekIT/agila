#include "DocumentInfoModel.h"

DocumentInfoModel::DocumentInfoModel()
{
}


QVector<DocumentInfo> DocumentInfoModel::getDocumentsInfo() {
    QVector<DocumentInfo> docsInfo;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT documents.type, name, numbering, after_text, family "
                   "FROM documents, wh_numbering WHERE documents.type = wh_numbering.type AND warehouse =  ?");
    query->addBindValue(ApplicationManager::getInstance()->getWarehouse()->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentInfoModel::getDocumentsInfo", query);

    DocumentInfo info;
    while(query->next())
    {
        info.setType(query->value(0).toString());
        info.setName(query->value(1).toString());
        info.setNumbering(query->value(2).toString());
        info.setAfterText(query->value(3).toString());
        info.setFamily(this->getFamily(query->value(4).toString()));
        docsInfo.push_back(info);
    }

    delete query;

    return docsInfo;
}

QVector<DocumentInfo> DocumentInfoModel::getDocumentsInfo(QString familyId) {
    QVector<DocumentInfo> docsInfo;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT documents.type, name, numbering, after_text, family "
                   "FROM documents, wh_numbering WHERE documents.type = wh_numbering.type AND warehouse =  ? AND family = ?");
    query->addBindValue(ApplicationManager::getInstance()->getWarehouse()->getId());
    query->addBindValue(familyId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentInfoModel::getDocumentsInfo", query);

    DocumentInfo info;
    while(query->next())
    {
        info.setType(query->value(0).toString());
        info.setName(query->value(1).toString());
        info.setNumbering(query->value(2).toString());
        info.setAfterText(query->value(3).toString());
        info.setFamily(this->getFamily(query->value(4).toString()));
        docsInfo.push_back(info);
    }

    delete query;

    return docsInfo;
}

DocumentInfo DocumentInfoModel::getDocumentInfo(QString type) {
    DocumentInfo info;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT documents.type, documents.name, numbering, after_text, family "
                   "FROM documents, wh_numbering WHERE documents.type = wh_numbering.type AND warehouse =  ? AND documents.type = ?");
    query->addBindValue(ApplicationManager::getInstance()->getWarehouse()->getId());
    query->addBindValue(type);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentInfoModel::getDocumentInfo", query);

    if(query->size() > 0) {
        query->first();

        info.setType(query->value(0).toString());
        info.setName(query->value(1).toString());
        info.setNumbering(query->value(2).toString());
        info.setAfterText(query->value(3).toString());
        info.setFamily(this->getFamily(query->value(4).toString()));
    }

    delete query;

    return info;
}

QString DocumentInfoModel::getDocumentTypeBySymbol(QString symbol) {
    QVector<DocumentInfo> documentInfos = this->getDocumentsInfo();
    for(int i = 0; i < documentInfos.size(); i++) {
        if(symbol.contains(documentInfos[i].getType() + "/"))
            return documentInfos[i].getType();
    }
    return "";
}

SimpleStringStructure DocumentInfoModel::getDocumentFamilyBySymbol(QString symbol) {
    QVector<DocumentInfo> documentInfos = this->getDocumentsInfo();

    for(int i = 0; i < documentInfos.size(); i++) {
        if(symbol.contains(documentInfos[i].getType() + "/"))
            return documentInfos[i].getFamily();
    }
    return SimpleStringStructure();
}

void DocumentInfoModel::editAfterText(QString documentType, QString afterText)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE documents SET after_text = ? WHERE type = ?");
    query->addBindValue(afterText);
    query->addBindValue(documentType);
    query->exec();

    if(this->isQueryError(query))
       throw new SQLException("DocumentInfoModel::editAfterText", query);

    delete query;
}

void DocumentInfoModel::editDocumentNumbering(QString documentType, QString numbering)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE wh_numbering SET numbering = ? WHERE type = ? AND warehouse = ?");
    query->addBindValue(numbering);
    query->addBindValue(documentType);
    query->addBindValue(ApplicationManager::getInstance()->getWarehouse()->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentInfoModel::editDocumentNumbering", query);

    delete query;
}

SimpleStringStructure DocumentInfoModel::getFamily(QString id)
{
    SimpleStringStructure family;
    QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM documents_family WHERE id = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentInfoModel::getFamily", query);

    if(query->size() > 0)
    {
        query->first();

        family.setId(id);
        family.setName(query->value(0).toString());
    }
    delete query;

    return family;
}

QVector<QString> DocumentInfoModel::getTypesByFamily(QString family) {
    QVector<QString> types;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type FROM documents WHERE family = ?");
    query->addBindValue(family);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentInfoModel::getTypesByFamily", query);

    while(query->next())
    {
        types.push_back(query->value(0).toString());
    }

    delete query;

    return types;
}

QString DocumentInfoModel::getTableNameByDocumentType(QString documentType) {
    if(documentType == "KW" || documentType == "KP")
        return "cash_documents";
    else if(documentType == "ZD" || documentType == "ZK")
        return "orders";
    else if(documentType == "RR" || documentType == "FZ" || documentType == "FZK")
        return "purchase_documents";
    else if(documentType == "NK")
        return "documents_nk";
    else if(documentType == "FV" || documentType == "FMP" || documentType == "FM" || documentType == "FK" || documentType == "PRO" || documentType == "PA" || documentType == "PI" || documentType == "ZAL" || documentType == "RZL")
        return "sale_documents";
    else if(documentType == "WZ" || documentType == "PZ" || documentType == "RW" || documentType == "PW" || documentType == "MM+" || documentType == "MM-")
        return "warehouse_documents";
    else if(documentType == "CN" || documentType == "OF")
        return "price_lists";
    else if(documentType == "REP")
        return "reports";
    else
        return "";
}
