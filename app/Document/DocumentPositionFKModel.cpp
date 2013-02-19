#include "DocumentPositionFKModel.h"

DocumentPositionFKModel::DocumentPositionFKModel()
{
}

DocumentPositionFKModel::~DocumentPositionFKModel()
{
}

void DocumentPositionFKModel::addPosition(QString documentSymbol, DocumentPosition position)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO documents_positions (document, good, quantity, price_level, tax_id, warehouse) "
                        "VALUES (?, ?, ?, ?, ?, ?)");
    query->addBindValue(documentSymbol);
    query->addBindValue(position.getGood().getId());
    query->addBindValue(position.getQuantity());
    query->addBindValue(Price::priceLevelToString(position.getPriceLevel()));
    query->addBindValue(position.getTax().getId());
    query->addBindValue(ApplicationManager::getInstance()->getWarehouse()->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentPositionFKModel::addPosition", query);

    delete query;
}
