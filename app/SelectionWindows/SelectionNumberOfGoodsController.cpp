#include "SelectionNumberOfGoodsController.h"

SelectionNumberOfGoodsController::SelectionNumberOfGoodsController(Goods *good,QString symbol)  {

    this->good=good;
    this->symbol=symbol;
    view = new SelectionNumberOfGoodsView(this);
    view->setUnitName(good->getUnit().getName());
    view->setZeroPlaces(good->getUnit().getZeroPlaces());
    if(symbol=="PZ"||symbol=="PW")
        view->setMaxNumberOfGoods(-1);
    else
    {
        if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
            view->setMaxNumberOfGoods(good->getQuantity());
        else
            view->setMaxNumberOfGoods(100000000000.0);
    }
}

SelectionNumberOfGoodsController::~SelectionNumberOfGoodsController(){}

/**
  Zwraca ilośc towaru wybraną przez użytkownika lub -1 w przypadku gdy nie zaakceptował wyboru.
  */
int SelectionNumberOfGoodsController::exec()  {

   int signal= view->exec();
   return signal;
}

SelectionNumberOfGoodsView *SelectionNumberOfGoodsController::getView()
{
    return this->view;
}

Goods* SelectionNumberOfGoodsController::getGood()
{
    return this->good;
}

QString SelectionNumberOfGoodsController::getSymbol()
{
    return this->symbol;
}

