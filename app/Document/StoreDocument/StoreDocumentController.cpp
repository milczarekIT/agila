#include "StoreDocumentController.h"
#include "Tools/Print/PrintManager.h"

StoreDocumentController::StoreDocumentController() : DocumentController()  {

}

void StoreDocumentController::addGood()
{
   view->getGoodsTable()->setRowCount(manager->getDocumentPosition().size());
   for (int i=0; i<manager->getDocumentPosition().size(); i++)
   {
       insertGood(i,0,new QTableWidgetItem(manager->getDocumentPosition().value(i).getGood().getName()));
       view->getGoodsTable()->item(i,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,1,new QTableWidgetItem(manager->getDocumentPosition().value(i).getGood().getSymbol()));
       view->getGoodsTable()->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,2,new QTableWidgetItem(QString::number(manager->getDocumentPosition().value(i).getPriceNet(),',',2).replace(QRegExp("[.]"),",")));
       view->getGoodsTable()->item(i,2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,3,new QTableWidgetItem(QString::number(manager->getDocumentPosition().value(i).getPriceGross(), ',', 2).replace(QRegExp("[.]"),",")));
       view->getGoodsTable()->item(i,3)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,5,new QTableWidgetItem(QString::number(manager->getDocumentPosition().value(i).getPriceGross()*
                                                           manager->getDocumentPosition().value(i).getQuantity(), ',', 2).replace(QRegExp("[.]"),",")));
       view->getGoodsTable()->item(i,5)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,4,new QTableWidgetItem(QString::number(manager->getDocumentPosition().value(i).getQuantity(),',',
                                                           manager->getDocumentPosition().value(i).getGood().getUnit().getZeroPlaces()).replace(QRegExp("[.]"),",")));

   }
}

bool StoreDocumentController::isQuantityColumn(int column)
{
    if (column==4)
        return true;
    else
        return false;
}

void StoreDocumentController::setGoodsValue()
{
   if(this->manager->getDocumentPosition().empty()==1)
       manager->setTotalNet(0.0);

    if(totalFromBase==false)
 view->setLineGoodsValueNet(manager->getTotalNet());
}


StoreDocumentController::~StoreDocumentController() {
}
