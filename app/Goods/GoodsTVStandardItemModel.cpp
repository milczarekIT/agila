#include "GoodsTVStandardItemModel.h"

GoodsTVStandardItemModel::GoodsTVStandardItemModel(QObject *parent) :
    QStandardItemModel(parent), GoodsFilters()
{
    this->sortColumn = 1;
    this->sortOrder = Qt::AscendingOrder;
}

void *GoodsTVStandardItemModel::getGoods() {

    QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_good, symbol, name, quantity, COALESCE((SELECT name FROM units WHERE id_unit = goods.unit), ''), "
                   "COALESCE((SELECT short_name FROM taxes WHERE id_tax = goods.tax), ''), "
                   "COALESCE((SELECT name FROM goods_groups WhERE id_group = goods.goods_group), 'BRAK'), "
                        "price_a_net, price_a_gross, price_b_net, price_b_gross, price_c_net, price_c_gross, price_mag_net, price_mag_gross "
                    "FROM goods, wh_goods wh "
                    "WHERE wh.good = goods.id_good AND warehouse = " + QString::number(ApplicationManager::getInstance()->getWarehouse()->getId()) +
                    " AND wh.is_active = true "
                   + getSymbolFilter() + getNameFilter() + getGoodsGroupFilter() + getGoodsTypeFilter() + getTaxForRRFilter() +
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"));
    query->exec();
    this->clear();//Unchecked();
    initData(query);
    this->initHeaders(2);
}

void GoodsTVStandardItemModel::initData(QSqlQuery *query) {
    for(int i = this->columnCount(); query->next(); i++) {
        QString id = query->value(0).toString();
        //if(!containsId(id)) {
            this->setItem(i, 0, createItem(id));
            this->setItem(i, 1, createCheckedItem());
            this->setItem(i, 2, createItem(query->value(1).toString()));
            this->setItem(i, 3, createItem(query->value(2).toString()));
            this->setItem(i, 4, createItem(query->value(3).toString()));
            this->setItem(i, 5, createItem(query->value(4).toString()));
            this->setItem(i, 6, createItem(query->value(5).toString()));
            this->setItem(i, 7, createItem(query->value(6).toString()));
            this->setItem(i, 8, createItem(query->value(7).toString()));
            this->setItem(i, 9, createItem(query->value(8).toString()));
            this->setItem(i, 10, createItem(query->value(9).toString()));
            this->setItem(i, 11, createItem(query->value(10).toString()));
            this->setItem(i, 12, createItem(query->value(11).toString()));
            this->setItem(i, 13, createItem(query->value(12).toString()));
            this->setItem(i, 14, createItem(query->value(13).toString()));
            this->setItem(i, 15, createItem(query->value(14).toString()));
        //}
    }
}

QStandardItem *GoodsTVStandardItemModel::createCheckedItem() {
    QStandardItem* item = new QStandardItem(true);
    item->setCheckable(true);
    item->setCheckState(Qt::Unchecked);
    item->setEditable(false);
    return item;
}

QStandardItem *GoodsTVStandardItemModel::createItem(QString value) {
    QStandardItem *item = new QStandardItem();
    item->setText(value);
    item->setEditable(false);
    return item;
}

void GoodsTVStandardItemModel::initHeaders(int off) {

    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Ilość"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("j.m."));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("VAT"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Grupa towarowa"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Cena A netto"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Cena A brutto"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Cena B netto"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Cena B brutto"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Cena C netto"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Cena C brutto"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Cena MAG netto"));
    this->setHeaderData(off++, Qt::Horizontal, QObject::tr("Cena MAG brutto"));

    if(off > 1) this->setHeaderData(1, Qt::Horizontal, QObject::tr(""));
}

bool GoodsTVStandardItemModel::containsId(QString id) {
    for(int i = 0; i < this->rowCount(); i++) {
        if(item(i,0)->text().contains(id)) {
            return true;
        }
    }
    return false;
}

int GoodsTVStandardItemModel::clearUnchecked() {
    for(int i = this->rowCount()-1; i >= 0; i--) {
        if(isUncheckedItem(i,1)) {
            this->removeRow(i);
        }
    }
}

bool GoodsTVStandardItemModel::isUncheckedItem(int row, int col) {
    return item(row,col)->checkState() == Qt::Unchecked;
}

bool GoodsTVStandardItemModel::isCheckedItem(int row, int col) {
    return item(row,col)->checkState() == Qt::Checked;
}

Qt::SortOrder GoodsTVStandardItemModel::getSortOrder(){
    return sortOrder;
}

int GoodsTVStandardItemModel::getSortColumn(){
    return sortColumn;
}
