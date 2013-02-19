#include "ContractorValidator.h"

ContractorValidator::ContractorValidator(ContractorDialogView *view)
{
    this->view = view;
}

ContractorValidator::~ContractorValidator() {

}

void ContractorValidator::validateForm()
{
    MessageBox *messageBox = new MessageBox();

    if(view->getTextCompany()->text().isEmpty()){
       view->getTextCompany()->setFocus();
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

    if (view->getLinePostCode()->text().isEmpty()) {
        view->getLinePostCode()->setFocus();
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
    if (view->getLineCity()->text().isEmpty()) {
        view->getLineCity()->setFocus();
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
    if (view->getLineAdress()->text().isEmpty()) {
        view->getLineAdress()->setFocus();
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
    if (!view->getLineAccount()->text().length()==6 and view->getLineAccount()->text().length()!=32)
    {
            view->getLineAccount()->setFocus();
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
    //przypadek gdy jest to firma
    if (view->getRadioBusiness()->isChecked())
    {

        if(view->getLineTIN()->text().isEmpty())
        {
            view->getLineTIN()->setFocus();
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
    }
    if(!view->getLineTIN()->text().isEmpty())
    {
        if(!isCorrectTIN())
        {
            view->getLineTIN()->setFocus();
           if (messageBox->createQuestionBox("Nie wprowadzono wymaganych danych!") == MessageBox::YES)
            {
               view->accept();
               return;
            }
            else
            {
                 return;
            };
        }
    }
    view->accept();
}

bool ContractorValidator::isEmptyForm()
{
    if(!view->getLineSymbol()->text().isEmpty())
        return false;
    if(!view->getTextCompany()->text().isEmpty())
        return false;
    if(!view->getLineName()->text().isEmpty())
        return false;
    if(!view->getLinePostCode()->text().isEmpty())
        return false;
    if(!view->getLineCity()->text().isEmpty())
        return false;
    if(!view->getLineAdress()->text().isEmpty())
        return false;
    if(!view->getLineTIN()->text().isEmpty())
        return false;
    if(!view->getLineRegon()->text().isEmpty())
        return false;
    if(!view->getLineWebsite()->text().isEmpty())
        return false;
    if(!view->getLineEmail()->text().isEmpty())
        return false;
    if(!view->getLineDiscount()->text().isEmpty())
        return false;
    if(!view->getLineAdditional()->text().isEmpty())
        return false;
    if(!view->getTextComments()->toPlainText().isEmpty())
        return false;
    /*if(phoneModel->rowCount() > 0)
        return false;*/
    else
        return true;

}

bool ContractorValidator::isCorrectTIN()
{
    QString tin = view->getLineTIN()->text();
    tin = tin.remove(QRegExp("[ -]")); // usuwa spacje i myślniki
    if(tin.length() != 10)
        return false;

    int tinInt[10], control[9] = { 6, 5, 7, 2, 3, 4, 5 ,6, 7 };

    // tablica kolejnych cyfr w NIPie
    for(int i = 0; i < 10; i++)
        tinInt[i] = QVariant(tin.at(i)).toInt() - 48;

    int sum = 0;
    for(int i = 0; i < 9; i++)
    {
        sum += tinInt[i]*control[i];
    }

    if(sum%11 == tinInt[9]) // modulo 11 z obliczonej sumy musi być równe ostatniej cyfrze
        return true;
    else
        return false;

}
