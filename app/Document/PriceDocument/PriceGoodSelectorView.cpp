#include "PriceGoodSelectorView.h"

PriceGoodSelectorView::PriceGoodSelectorView(QWidget *parent, PriceGoodSelectorController * controller)
    : SelectGoodView(parent,controller)
{
    setTableSettings();
}

void PriceGoodSelectorView::setTableSettings() {
    this->getGoodsTable()->setSelectionMode(QAbstractItemView::MultiSelection);
}
