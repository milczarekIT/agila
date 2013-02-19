#include "DocumentValidator.h"

DocumentValidator::DocumentValidator(DocumentView *view,QString symbol)
{
    this->view=view;
    this->symbol=symbol;
}

DocumentValidator::DocumentValidator(DocumentFKView *view,QString symbol)
{
    this->viewFK = view;
    this->symbol=symbol;
}
void DocumentValidator::validateForm(){}

DocumentValidator::~DocumentValidator(){}

void DocumentValidator::validateDocForm( bool edition)
{
    QMessageBox msgBox(view); MessageBox *messageBox = new MessageBox();
    dnc = new DocumentNumeratorController(view->getLineDocumentSymbol()->text().section("/",0,0));

    if(edition == false)
    {
        if(view->getLineDocumentSymbol()->text().isEmpty()){
            view->getLineDocumentSymbol()->setFocus();
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
        else
        {
           if(!dnc->isValidSymbol(view->getLineDocumentSymbol()->text()))
           {
               msgBox.setText("Format Numeru dokumentu niepoprawny");
               msgBox.exec();
               return;
           }
           if(!dnc->isAvailableSymbol(view->getLineDocumentSymbol()->text()))
           {
               msgBox.setText("Numer dokumentu zajęty ustawiono pierwszy wolny.");
               view->setLineDocumentSymbol(dnc->getNextSymbol());
               msgBox.exec();
               return;

           }
        }
    }
    if(!(this->symbol.contains("PA")||this->symbol.contains("MM")||this->symbol.contains("RW")||this->symbol.contains("PW")))
    {
        if(view->getContractorData()->toPlainText()=="Wprowadź dane kontrahenta")
    {
        if (messageBox->createQuestionBox("Nie wybrano kontrahenta!") == MessageBox::YES)
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
    if(view->getController()->getDocumentManager()->getDocumentPosition().isEmpty())
    {
        if (messageBox->createQuestionBox("Nie wybrano towarów!") == MessageBox::YES)
        {
            view->accept();
            return;
        }
        else
        {
             return;
        }
    }

    if(view->getLineDocumentPlace()->text().isEmpty())
    {
      view->getLineDocumentPlace()->setFocus();
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

    delete dnc;
    view->accept();
}

void DocumentValidator::validateDocFormFK( bool edition)
{
    QMessageBox msgBox(viewFK);
    MessageBox *messageBox = new MessageBox();
    dnc = new DocumentNumeratorController(viewFK->getController()->getSymbol());

    if(edition == false)
    {

        if(viewFK->getLineDocumentSymbol()->text().isEmpty()){
            viewFK->getLineDocumentSymbol()->setFocus();

            if (messageBox->createQuestionBox("Nie wprowadzono wymaganych danych!") == MessageBox::YES)
            {
                viewFK->accept();
                return;
            }
            else
            {
                 return;
            }
        }
        else
        {
           if(!dnc->isValidSymbol(viewFK->getLineDocumentSymbol()->text()))
           {
               msgBox.setText("Format Numeru dokumentu niepoprawny");
               msgBox.exec();
               return;
           }

           if(!dnc->isAvailableSymbol(viewFK->getLineDocumentSymbol()->text()))
           {
               msgBox.setText("Numer dokumentu zajęty ustawiono pierwszy wolny.");
               viewFK->setLineDocumentSymbol(dnc->getNextSymbol());
               msgBox.exec();
               return;

           }
        }
    }

    if(viewFK->getLineDocumentPlace()->text().isEmpty())
    {
      viewFK->getLineDocumentPlace()->setFocus();
      if (messageBox->createQuestionBox("Nie wprowadzono wymaganych danych!") == MessageBox::YES)
      {
          viewFK->accept();
          return;
      }
      else
      {
           return;
      }
    }

    if(viewFK->getLineRelatedTo()->text().isEmpty())
    {
        viewFK->getLineRelatedTo()->setFocus();
        if (messageBox->createQuestionBox("Nie wprowadzono wymaganych danych!") == MessageBox::YES)
        {
            viewFK->accept();
            return;
        }
        else
        {
             return;
        }
    }
    if(viewFK->getContractorDataOld()->toPlainText().isEmpty())
    {
        viewFK->getContractorDataOld()->setFocus();
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

    delete dnc;
    viewFK->accept();
}

bool DocumentValidator::isEmptyForm()
{
    if(!(this->symbol.contains("PA")||this->symbol.contains("PW")||this->symbol.contains("RW")||this->symbol.contains("MM")))
    {
    if(!(view->getContractorData()->toPlainText()=="Wprowadź dane kontrahenta"))
        return false;
    }
    if(!view->getController()->getDocumentManager()->getDocumentPosition().isEmpty())
        return false;
    else
        return true;
}

bool DocumentValidator::isEmptyFormFK()
{

    if(!(viewFK->getContractorDataNew()->toPlainText().isEmpty()))
        return false;
    if(!(viewFK->getContractorDataOld()->toPlainText()=="Wybierz fakturę aby wprowadzić dane kontrahenta"))
        return false;
    if(!viewFK->getController()->getManager()->getDocumentPositionNew().isEmpty())
        return false;
    if(!viewFK->getController()->getManager()->getDocumentPositionOld().isEmpty())
        return false;
    else
        return true;
}

