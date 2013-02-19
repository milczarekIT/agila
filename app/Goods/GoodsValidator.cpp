#include "GoodsValidator.h"

GoodsValidator::GoodsValidator(GoodsDialogView *view)
{
    this->view = view;
}
GoodsValidator::~GoodsValidator() {

}

void GoodsValidator::validateForm() {
    MessageBox *messageBox = new MessageBox();
    if (view->getLineName()->text().isEmpty()) {
        view->getLineName()->setFocus();
        if (messageBox->createQuestionBox("Nie wprowadzono wymaganych danych!") == MessageBox::YES)
        {
            view->accept();
            return;
        }
        else
        {
        return;
        }
    }

    bool almostOnePrice = false;

    if (!view->getLinePriceMagNet()->text().isEmpty()) almostOnePrice=true;
    if(!almostOnePrice)
    {
                view->getTabWidget()->setCurrentIndex(1);
                view->getTablePrices()->setFocus();
                if (messageBox->createQuestionBox("Nie wprowadzono wymaganych danych!") == MessageBox::YES)
                {
                    view->accept();
                    return;
                }
                else
                {
                return;
                }
    }
    view->accept();
}

bool GoodsValidator::isEmptyForm() {
    view->getTablePrices()->setDisabled(false);
    if(!view->getLineSymbol()->text().isEmpty()) {
        return false; }
    if(!view->getLineName()->text().isEmpty()) {
        return false;}
    if(!view->getLinePkwiu()->text().isEmpty()) {
        return false;}
    if(!view->getLineWeight()->text().isEmpty()) {
        return false;}
    if(!view->getTextDescription()->toPlainText().isEmpty()) {
        return false;}
    if(!view->getLinePriceMagNet()->text().isEmpty()){
        return false;}
    else
        return true;
}
