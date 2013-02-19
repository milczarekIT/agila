#include "DocumentPositionModel.h"

DocumentPositionModel::DocumentPositionModel()
{
    warehouseId = ApplicationManager::getInstance()->getWarehouse()->getId();
}

QVector<DocumentPosition> DocumentPositionModel::getPositions(QString documentSymbol)
{
    GoodsService *gservice = new GoodsService();
    SettingsModel *smodel = new SettingsModel();
    TaxModel *taxModel = new TaxModel();
    QVector<DocumentPosition> positions;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT good, quantity, tax_id, price_level FROM documents_positions "
                   "WHERE document = ? AND warehouse = " + QString::number(warehouseId));
    query->addBindValue(documentSymbol);
    query->exec();

    DocumentPosition dp;
    while(query->next())
    {
        dp.setGood(gservice->getGood(query->value(0).toInt()));
        dp.setQuantity(query->value(1).toDouble());
        dp.setTax(taxModel->getTax(query->value(2).toInt()));
        dp.setPriceLevel(Price::priceLevelToInt(query->value(3).toString()));

        int goodId = dp.getGood().getId();
        dp.setPriceNet(gservice->getPriceNet(goodId, dp.getPriceLevel()));
        dp.setPriceGross(gservice->getPriceGross(goodId, dp.getPriceLevel()));

        positions.push_back(dp);
    }

    delete taxModel;
    delete gservice;
    delete smodel;
    delete query;

    return positions;
}

void DocumentPositionModel::addPosition(QString documentSymbol, DocumentPosition position)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO documents_positions (document, good, quantity, tax_id, warehouse, price_level) "
                        "VALUES (?, ?, ?, ?, ?, ?)");
    query->addBindValue(documentSymbol);
    query->addBindValue(position.getGood().getId());
    query->addBindValue(position.getQuantity());
    query->addBindValue(position.getTax().getId());
    query->addBindValue(warehouseId);
    query->addBindValue(Price::priceLevelToString(position.getPriceLevel()));
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentPositionModel::addPosition", query);

    delete query;
}

void DocumentPositionModel::editPosition(QString documentSymbol, DocumentPosition oldPosition, DocumentPosition newPosition)
{
   query = new QSqlQuery(Database::getInstance().db);
   query->prepare("UPDATE documents_positions SET quantity = ?, tax_id = ?, price_level = ? "
                   "WHERE document = ? AND good = ? AND warehouse = ?");
   query->addBindValue(newPosition.getQuantity());
   query->addBindValue(newPosition.getTax().getId());
   query->addBindValue(Price::priceLevelToString(newPosition.getPriceLevel()));
   query->addBindValue(documentSymbol);
   query->addBindValue(oldPosition.getGood().getId());
   query->addBindValue(warehouseId);
   query->exec();

   if(this->isQueryError(query))
       throw new SQLException("DocumentPositionModel::editPosition", query);

   delete query;
}

void DocumentPositionModel::removePosition(QString documentSymbol, DocumentPosition position)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM documents_positions "
                    "WHERE document = ? AND good = ? AND warehouse = ?");
    query->addBindValue(documentSymbol);
    query->addBindValue(position.getGood().getId());
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentPositionModel::removePosition", query);

    delete query;
}

void DocumentPositionModel::removePositions(QString documentSymbol) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM documents_positions "
                    "WHERE document = ? AND warehouse = ?");
    query->addBindValue(documentSymbol);
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentPositionModel::removePositions", query);

    delete query;
}
