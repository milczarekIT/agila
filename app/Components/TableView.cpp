#include "TableView.h"

TableView::TableView(QWidget * parent) : QTableView(parent)
{
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setMenu();
    this->setFocusPolicy(Qt::StrongFocus);
    this->setSortingEnabled(true);
    horizontalHeader()->setSortIndicatorShown(true);
    this->verticalHeader()->setDefaultSectionSize(20);
}

TableView::~TableView()
{
    delete tableViewExtendedMenu;
}

void TableView::setContractorModel (TVModel *model)
{
    horizontalHeader()->setSortIndicator(model->getSortColumn()-1,model->getSortOrder());
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,150);
    setColumnWidth(2,250);
    setColumnWidth(3,200);
    setColumnWidth(4,100);
    setColumnWidth(5,150);
    setColumnWidth(6,150);
}

void TableView::setGoodsModel (TVModel *model)
{
    horizontalHeader()->setSortIndicator(model->getSortColumn()-1,model->getSortOrder());
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,250);
    setColumnWidth(2,350);
    setColumnWidth(3,75);
    setColumnWidth(4,50);
    setColumnWidth(5,50);
    setColumnWidth(6,150);
    setColumnWidth(7,100);
    setColumnWidth(8,100);
    setColumnWidth(9,100);
    setColumnWidth(10,100);
    setColumnWidth(11,100);
    setColumnWidth(12,100);
    setColumnWidth(13,100);
    setColumnWidth(14,100);
}

void TableView::setGoodsModel(GoodsTVStandardItemModel *goodsTVModel)
{
    horizontalHeader()->setSortIndicator(goodsTVModel->getSortColumn()-1, goodsTVModel->getSortOrder());
    setModel(goodsTVModel);
    setColumnHidden(0,true);
    setColumnWidth(1,30);
    setColumnWidth(2,250);
    setColumnWidth(3,350);
    setColumnWidth(4,75);
    setColumnWidth(5,50);
    setColumnWidth(6,50);
    setColumnWidth(7,150);
    setColumnWidth(8,100);
    setColumnWidth(9,100);
    setColumnWidth(10,100);
    setColumnWidth(11,100);
    setColumnWidth(12,100);
    setColumnWidth(13,100);
    setColumnWidth(14,100);
    setColumnWidth(15,100);
}

void TableView::setSaleDocumentModel (TVModel *model)
{
    horizontalHeader()->setSortIndicator(model->getSortColumn()-1,model->getSortOrder());
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,150);
    setColumnWidth(2,250);
    setColumnWidth(3,150);
    setColumnWidth(4,150);
    setColumnWidth(5,150);
}

void TableView::setPurchaseDocumentModel (TVModel *model) {
    horizontalHeader()->setSortIndicator(model->getSortColumn()-1,model->getSortOrder());
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,150);
    setColumnWidth(2,250);
    setColumnWidth(3,150);
    setColumnWidth(4,150);
    setColumnWidth(5,150);
}

void TableView::setOrderDocumentModel (TVModel *model) {
    horizontalHeader()->setSortIndicator(model->getSortColumn()-1,model->getSortOrder());
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,150);
    setColumnWidth(2,250);
    setColumnWidth(3,150);
    setColumnWidth(4,150);
    setColumnWidth(5,150);
}

void TableView::setStoreDocumentModel(TVModel *model)
{
    horizontalHeader()->setSortIndicator(model->getSortColumn()-1,model->getSortOrder());
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,150);
    setColumnWidth(2,250);
    setColumnWidth(3,150);
    setColumnWidth(4,150);
    setColumnWidth(5,150);
    setColumnWidth(6,150);
}

void TableView::setCashDocumentModel(TVModel *model)
{
    horizontalHeader()->setSortIndicator(model->getSortColumn()-1,model->getSortOrder());
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,150);
    setColumnWidth(2,250);
    setColumnWidth(3,200);
    setColumnWidth(4,150);
    setColumnWidth(5,150);
}

void TableView::setPriceDocumentModel (TVModel *model)
{
    horizontalHeader()->setSortIndicator(model->getSortColumn()-1,model->getSortOrder());
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,100);
    setColumnWidth(2,150);
    setColumnWidth(3,250);
    setColumnWidth(4,170);
    setColumnWidth(5,170);
    setColumnWidth(6,170);
    setColumnWidth(7,300);
}

void TableView::setFeatureModel(QSqlQueryModel *model)
{
    setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,293);
}

void TableView::hideIdColumn() {
    for(int i = 0; i < model()->columnCount(); i++)
    {
        if(model()->headerData(i, Qt::Horizontal).toString() == "id")
            this->hideColumn(i);
    }
}

int TableView::getId()
{
    if(currentIndex().row() != -1)
        return getId(currentIndex());
    else
        return -1;
}

int TableView::getId(QModelIndex index)
{
    return model()->data(index.model()->index(index.row(),0)).toInt();
}

QString TableView::getSymbol()
{
    if(currentIndex().row() != -1)
        return getSymbol(currentIndex());
    else
        return "";
}

QString TableView::getSymbol(QModelIndex index)
{
    int symbolColumn = 2;
    return index.model()->data(index.model()->index(index.row(),symbolColumn)).toString();
}

void TableView::setMenu()
{
    tableViewExtendedMenu = new TableViewExtendedMenu();
    this->addActions(tableViewExtendedMenu->getStandardMenu()->actions());
}

TableViewExtendedMenu * TableView::getExtendedMenu()
{
    return this->tableViewExtendedMenu;
}

void TableView::contextMenuEvent(QContextMenuEvent *event)
{
    tableViewExtendedMenu->exec(event);
}

