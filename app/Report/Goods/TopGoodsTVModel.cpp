#include "TopGoodsTVModel.h"

TopGoodsTVModel::TopGoodsTVModel()
{
    limit = 50;
    fromDateFilter = "";
    toDateFilter = "";
}

void TopGoodsTVModel::getData()
{
    /* dp.price_level */
    QString getPriceNetInSelectQuery = "(CASE WHEN dp.price_level = 'A' THEN (SELECT price_a_net FROM goods WHERE id_good = dp.good) ";
    getPriceNetInSelectQuery += "WHEN dp.price_level = 'B' THEN (SELECT price_b_net FROM goods WHERE id_good = dp.good) ";
    getPriceNetInSelectQuery += "WHEN dp.price_level = 'C' THEN (SELECT price_c_net FROM goods WHERE id_good = dp.good) ";
    getPriceNetInSelectQuery += "WHEN dp.price_level = 'MAG' THEN (SELECT price_mag_net FROM goods WHERE id_good = dp.good) ";
    getPriceNetInSelectQuery += "ELSE 0.00 END) ";

    /* price_level */
    QString getPriceNetInSelectQueryVer2 = "(CASE WHEN price_level = 'A' THEN (SELECT price_a_net FROM goods WHERE id_good = good) ";
    getPriceNetInSelectQueryVer2 += "WHEN price_level = 'B' THEN (SELECT price_b_net FROM goods WHERE id_good = good) ";
    getPriceNetInSelectQueryVer2 += "WHEN price_level = 'C' THEN (SELECT price_c_net FROM goods WHERE id_good = good) ";
    getPriceNetInSelectQueryVer2 += "WHEN price_level = 'MAG' THEN (SELECT price_mag_net FROM goods WHERE id_good = good) ";
    getPriceNetInSelectQueryVer2 += "ELSE 3*0.00 END) ";


    this->setQuery("SELECT g.id_good, g.symbol, g.name, COALESCE((SELECT name FROM goods_groups WHERE id_group = g.goods_group), 'BRAK'), "
                   /** ilość sprzedanych */
                   "((COALESCE((SELECT SUM(dp.quantity) "
                                "FROM goods, documents_positions dp, sale_documents sd "
                                "WHERE dp.document = sd.symbol "
                                + fromDateFilter + toDateFilter +
                                "AND dp.good = goods.id_good "
                                "AND sd.type IN (SELECT TYPE FROM documents "
                                                "WHERE family = 'SALE' AND NOT type IN ('FK', 'ZAL')) "
                                                "AND dp.good = g.id_good), 0)) + "
                   "(COALESCE((SELECT SUM((SELECT quantity FROM documents_positions "
                                            "WHERE document = ld.linked_document "
                                            "AND good = dp.good)-(SELECT quantity "
                                                                    "FROM documents_positions "
                                                                    "WHERE document = ld.base_document "
                                                                    "AND good = dp.good ) ) AS roznicazFK "
                            "FROM linked_documents ld, documents_positions dp, sale_documents sd "
                            "WHERE linked_document IN (SELECT symbol "
                                                        "FROM sale_documents "
                                                        "WHERE TYPE = 'FK') "
                            "AND dp.document = ld.linked_document "
                            "AND sd.symbol = dp.document "
                            + fromDateFilter + toDateFilter +
                            "AND dp.good = g.id_good), 0))) AS ile, g.price_a_net, g.price_a_gross, "

                   /** wartość netto sprzedaży */
                   "((COALESCE((SELECT SUM(dp.quantity*" + getPriceNetInSelectQuery +
                                ") FROM goods, documents_positions dp, sale_documents sd "
                                "WHERE dp.document = sd.symbol "
                                + fromDateFilter + toDateFilter +
                                "AND dp.good = goods.id_good "
                                "AND sd.type IN (SELECT TYPE FROM documents "
                                                "WHERE family = 'SALE' AND NOT type IN ('FK', 'ZAL')) "
                                                "AND dp.good = g.id_good), 0)) + "
                   "(COALESCE((SELECT SUM((SELECT quantity*" + getPriceNetInSelectQueryVer2 + "FROM documents_positions "
                                            "WHERE document = ld.linked_document "
                                            "AND good = dp.good)-(SELECT quantity*" + getPriceNetInSelectQueryVer2 +
                                                                    "FROM documents_positions "
                                                                    "WHERE document = ld.base_document "
                                                                    "AND good = dp.good ) ) AS roznicazFK "
                            "FROM linked_documents ld, documents_positions dp, sale_documents sd "
                            "WHERE linked_document IN (SELECT symbol "
                                                        "FROM sale_documents "
                                                        "WHERE TYPE = 'FK') "
                            "AND dp.document = ld.linked_document "
                            + fromDateFilter + toDateFilter +
                            "AND sd.symbol = dp.document "
                            "AND dp.good = g.id_good), 0))) as wartosc_netto "
                   "FROM goods g, documents_positions dp "
                   "WHERE g.id_good = dp.good "

                   /** warunek dla poz powyżej zera */
                   "AND ((COALESCE((SELECT SUM(dp.quantity) "
                                   "FROM goods, documents_positions dp, sale_documents sd "
                                   "WHERE dp.document = sd.symbol "
                                   + fromDateFilter + toDateFilter +
                                   "AND dp.good = goods.id_good "
                                   "AND sd.type IN (SELECT TYPE FROM documents "
                                                   "WHERE family = 'SALE' AND NOT type IN ('FK', 'ZAL')) "
                                                   "AND dp.good = g.id_good), 0)) + "
                      "(COALESCE((SELECT SUM((SELECT quantity FROM documents_positions "
                                               "WHERE document = ld.linked_document "
                                               "AND good = dp.good)-(SELECT quantity "
                                                                       "FROM documents_positions "
                                                                       "WHERE document = ld.base_document "
                                                                       "AND good = dp.good ) ) AS roznicazFK "
                               "FROM linked_documents ld, documents_positions dp, sale_documents sd "
                               "WHERE linked_document IN (SELECT symbol "
                                                           "FROM sale_documents "
                                                           "WHERE TYPE = 'FK') "
                               "AND dp.document = ld.linked_document "
                               "AND sd.symbol = dp.document "
                               + fromDateFilter + toDateFilter +
                               "AND dp.good = g.id_good), 0))) > 0 "
                   "GROUP BY g.id_good "
                   "ORDER BY ile DESC "
                   "LIMIT " + QString::number(limit), Database::getInstance().db);

    this->initHeaders();
}

void TopGoodsTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Grupa towarowa"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Sprzedano"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Cena netto"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("Cena brutto"));
    this->setHeaderData(7, Qt::Horizontal, QObject::tr("Wartość sprz. netto"));
}

QVariant TopGoodsTVModel::data(const QModelIndex & index, int role) const
{
    TopGoodsTVDisplayer displayer(index, role, this);
    return displayer.display();
}

QVariant TopGoodsTVModel::data(int row, int column, int role) {
    QModelIndex modelIndex = this->index(row, column);
    return data(modelIndex, role);
}

void TopGoodsTVModel::setListLimitFilter(int limit)
{
    this->limit = limit;
}

void TopGoodsTVModel::setDateFromFilter(QDate fromDate)
{
    this->fromDateFilter = "AND sale_date >= '" + fromDate.toString("yyyy-MM-dd") + "' ";
}

void TopGoodsTVModel::setDateToFilter(QDate toDate)
{
    this->toDateFilter = "AND sale_date <= '" + toDate.toString("yyyy-MM-dd") + "' ";
}
