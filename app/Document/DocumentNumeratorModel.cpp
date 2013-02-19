#include "DocumentNumeratorModel.h"

DocumentNumeratorModel::DocumentNumeratorModel()
{
}

QString DocumentNumeratorModel::getPrevoiusSymbol(QString documentType, QString tableName)
{
    QString previousSymbol;
    QString queryString;
    queryString = "SELECT symbol, id FROM " + tableName + " WHERE type = '" + documentType + "' AND warehouse = " + QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());

    if(documentType == "FV" || documentType == "FMP") {
        queryString += " UNION SELECT symbol, id FROM sale_documents WHERE type IN ('ZAL', 'RZL')  AND symbol LIKE '" + documentType + "/%' AND warehouse = "
                + QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    }
    queryString += "ORDER BY id DESC LIMIT 1";

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare(queryString);
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("DocumentNumeratorModel::getPrevoiusSymbol", query);

    if(query->size() > 0)
    {
        query->first();
        previousSymbol = query->value(0).toString();
    }

    return previousSymbol;
}

QString DocumentNumeratorModel::getNumberingFormat(QString documentType)
{
    QString numberingFormat;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT numbering FROM wh_numbering WHERE type = ? AND warehouse = ?");
    query->addBindValue(documentType);
    query->addBindValue(ApplicationManager::getInstance()->getWarehouse()->getId());
    query->exec();
    query->first();

    if(this->isQueryError(query))
            throw new SQLException("DocumentNumeratorModel::getNumberingFormat", query);

    numberingFormat = query->value(0).toString();

    return numberingFormat;
}

bool DocumentNumeratorModel::isAvailableSymbol(QString documentType, QString symbol)
{
    QString table = "";
    if(documentType == "FV" || documentType == "FK" || documentType == "FMP" || documentType == "PRO" || documentType == "PI"
    || documentType == "PA"|| documentType =="FM" || documentType == "RR"||documentType=="ZAL"||documentType=="RZL")
        table = "sale_documents";
    else if(documentType == "PZ" || documentType == "WZ" || documentType == "PW" || documentType == "RW")
        table = "warehouse_documents";
    else if(documentType == "KP" || documentType == "KW")
        table = "cash_documents";
    else if(documentType =="ZK" || documentType=="ZD")
        table = "orders";
    else if(documentType =="FZ"||documentType =="FZK")
        table ="purchase_documents";
    else if(documentType =="CN" || documentType == "OF")
        table = "price_lists";

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT symbol FROM " + table + " WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(ApplicationManager::getInstance()->getWarehouse()->getId());
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("DocumentNumeratorModel::isAvailableSymbol", query);

    if(query->size() == 0)
        return true;
    else
        return false;
}


