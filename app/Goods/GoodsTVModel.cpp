#include "GoodsTVModel.h"

GoodsTVModel::GoodsTVModel() : TVModel(), GoodsFilters()
{
    sortColumn=3;
    sortOrder=Qt::AscendingOrder;
}

GoodsTVModel::~GoodsTVModel() {

}

void GoodsTVModel::getGoods()
{
    this->setQuery("SELECT id_good, symbol, name, quantity, COALESCE((SELECT name FROM units WHERE id_unit = goods.unit), ''), "
                   "COALESCE((SELECT short_name FROM taxes WHERE id_tax = goods.tax), ''), "
                   "COALESCE((SELECT name FROM goods_groups WhERE id_group = goods.goods_group), 'BRAK'), "
                        "price_a_net, price_a_gross, price_b_net, price_b_gross, price_c_net, price_c_gross, price_mag_net, price_mag_gross "
                    "FROM goods, wh_goods wh "
                    "WHERE wh.good = goods.id_good AND warehouse = " + QString::number(ApplicationManager::getInstance()->getWarehouse()->getId()) +
                    " AND wh.is_active = true "
                   + getSymbolFilter() + getNameFilter() + getGoodsGroupFilter() + getGoodsTypeFilter() + getTaxForRRFilter() +
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);
    this->initHeaders();
}

void GoodsTVModel::getGoodsForRR()
{
    this->setQuery("SELECT id_good, symbol, name, quantity, COALESCE((SELECT name FROM units WHERE id_unit = goods.unit), ''), "
                   "COALESCE((SELECT short_name FROM taxes WHERE id_tax = goods.tax), ''), "
                   "COALESCE((SELECT name FROM goods_groups WhERE id_group = goods.goods_group), 'BRAK'), "
                        "price_a_net, price_a_gross, price_b_net, price_b_gross, price_c_net, price_c_gross, price_mag_net, price_mag_gross "
                    "FROM goods, wh_goods wh "
                    "WHERE wh.good = goods.id_good AND warehouse = " + QString::number(ApplicationManager::getInstance()->getWarehouse()->getId()) +
                    " AND wh.is_active = true  and tax > 1"
                   + getSymbolFilter() + getNameFilter() + getGoodsGroupFilter() + getGoodsTypeFilter() +
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);
    this->initHeaders();
}

void GoodsTVModel::initHeaders() {
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Ilość"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("j.m."));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("VAT"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("Grupa towarowa"));
    this->setHeaderData(7, Qt::Horizontal, QObject::tr("Cena A netto"));
    this->setHeaderData(8, Qt::Horizontal, QObject::tr("Cena A brutto"));
    this->setHeaderData(9, Qt::Horizontal, QObject::tr("Cena B netto"));
    this->setHeaderData(10, Qt::Horizontal, QObject::tr("Cena B brutto"));
    this->setHeaderData(11, Qt::Horizontal, QObject::tr("Cena C netto"));
    this->setHeaderData(12, Qt::Horizontal, QObject::tr("Cena C brutto"));
    this->setHeaderData(13, Qt::Horizontal, QObject::tr("Cena MAG netto"));
    this->setHeaderData(14, Qt::Horizontal, QObject::tr("Cena MAG brutto"));
}

void GoodsTVModel::sort(int column, Qt::SortOrder order)
{
    this->sortColumn=column+1;
    this->sortOrder=order;
    getGoods();
}

QVariant GoodsTVModel::data(const QModelIndex & index, int role) const
{
    GoodsTVDisplayer displayer(index, role, this);
    return displayer.display();
}
