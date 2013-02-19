#include "GoodsFilters.h"

GoodsFilters::GoodsFilters() {
    symbolFilter = "";
    nameFilter = "";
    goodsGroupFilter = "";
    goodsTypeFilter = "";
    taxForRRFilter = "";
}

void GoodsFilters::setGoodsGroupFilter(int idGroup){
    if(idGroup == -1)
        goodsGroupFilter = "";
    else
    {
        goodsGroupFilter = "AND goods_group =  " + QString::number(idGroup) + " ";
    }
}

void GoodsFilters::setNameFilter(QString value)
{
    if(value.isEmpty())
        nameFilter = "";
    else
        nameFilter="AND LOWER(goods.name) LIKE LOWER('" + value + "%') ";
}
void GoodsFilters::setSymbolFilter(QString value)
{
    if(value.isEmpty())
        symbolFilter = "";
    else
        symbolFilter="AND LOWER(goods.symbol) LIKE LOWER('" + value + "%') ";
}

void GoodsFilters::setGoodsTypeFilter(int type) {
    if(type == (Goods::GOOD | Goods::SERVICE))
        goodsTypeFilter = "";
    else if(type == Goods::GOOD)
        goodsTypeFilter = "AND goods.type = 1 ";
    else if(type == Goods::SERVICE)
        goodsTypeFilter = "AND goods.type = 2 ";
}

void GoodsFilters::setTaxForRRFilter(int idTax)
{
    if(idTax == -1)
        taxForRRFilter = "";
    else
    {
        taxForRRFilter = "AND tax =  " + QString::number(idTax) + " ";
    }
}

QString GoodsFilters::getSymbolFilter() {
    return symbolFilter;
}

QString GoodsFilters::getNameFilter() {
    return nameFilter;
}

QString GoodsFilters::getGoodsGroupFilter() {
    return goodsGroupFilter;
}

QString GoodsFilters::getGoodsTypeFilter() {
    return goodsTypeFilter;
}

QString GoodsFilters::getTaxForRRFilter() {
    return taxForRRFilter;
}
