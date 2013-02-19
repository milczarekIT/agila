#include "SettingsDocumentNumberingController.h"

SettingsDocumentNumberingController::SettingsDocumentNumberingController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsDocumentNumberingView(this,parent);
    documentInfoModel = new DocumentInfoModel();
    whichSymbols="SALE";
    setModel();
}

void SettingsDocumentNumberingController::setModel()
{
    fillBox(view->getKindsOfNumbering(), documentInfoModel->getDocumentsInfo(whichSymbols));
    showDocumentNumbering();
}

void  SettingsDocumentNumberingController::fillBox(QComboBox *box,QVector<DocumentInfo> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getType()));
}

void SettingsDocumentNumberingController::showDocumentNumbering()
{
    checkIfChanged();
    QString docType = view->getKindsOfNumbering()->itemData(view->getKindsOfNumbering()->currentIndex()).toString();
    DocumentInfo info = documentInfoModel->getDocumentInfo(docType);

    view->getNumberingDocument()->setText(docType);
    numberingState = info.getNumbering().remove(docType + "/");
    view->getNumberingRest()->setText(numberingState);
    matchUsedForm(info.getNumbering());
}

void SettingsDocumentNumberingController::clickedLineNumbering()
{
    if(view->getSign()->text() == "Znak specjalny")
        view->getSign()->setText("");
}

bool SettingsDocumentNumberingController::containsString(QString value)
{
    QString str = view->getNumberingRest()->text();
    if (str.contains(value)) return true;
    else return false;
}

void SettingsDocumentNumberingController::actionYear()
{
    if (view->getYear()->isChecked()) insertElementToNumbering("YYYY");
        else deleteElementFromNumbering("YYYY");
}

void SettingsDocumentNumberingController::actionDay()
{
    if (view->getDay()->isChecked()) insertElementToNumbering("DD");
    else deleteElementFromNumbering("DD");
}

void SettingsDocumentNumberingController::actionMonth()
{
    if (view->getMonth()->isChecked()) insertElementToNumbering("MM");
    else deleteElementFromNumbering("MM");
}

void SettingsDocumentNumberingController::actionNumbering()
{
    deleteElementFromNumbering("#");
    insertElementToNumbering("#");
    view->getNumbering()->setChecked(true);
}

void SettingsDocumentNumberingController::setWhichSymbols()
{
    if(view->getWhichModule()->currentText().contains("Sprzedaży"))
        this->whichSymbols="SALE";
    else if(view->getWhichModule()->currentText().contains("Zakupu"))
        this->whichSymbols="PURCHASE";
    else if(view->getWhichModule()->currentText().contains("Kasowych"))
        this->whichSymbols="CASH";
    else if(view->getWhichModule()->currentText().contains("Zamówień"))
        this->whichSymbols="ORDER";
    else if(view->getWhichModule()->currentText().contains("Magazynowych"))
        this->whichSymbols="STORE";
    setModel();
}

void SettingsDocumentNumberingController::insertElementToNumbering(QString value)
{
    QString str = view->getNumberingRest()->text();
    if(str == "") view->getNumberingRest()->setText(value);
    else view->getNumberingRest()->setText(view->getNumberingRest()->text() + "/" + value);
}

void SettingsDocumentNumberingController::deleteElementFromNumbering(QString value)
{
    QString str = view->getNumberingRest()->text();
    str = str.remove(QRegExp("/" + value +"|"  + value + "/" + "|" + value));
    view->getNumberingRest()->setText(str);
}

QString SettingsDocumentNumberingController::findSignText()
{
    QString str = view->getNumberingRest()->text();
    return str = str.remove(QRegExp("YYYY|MM|DD|#|/"));
}

void SettingsDocumentNumberingController::editDocumentNumbering()
{
    QString documentType = view->getNumberingDocument()->text();
    QString numbering = documentType + "/" + view->getNumberingRest()->text();
    documentInfoModel->editDocumentNumbering(documentType, numbering);
}

void SettingsDocumentNumberingController::matchUsedForm(QString str)
{
    view->getYear()->setChecked(false);
    view->getDay()->setChecked(false);
    view->getMonth()->setChecked(false);
    view->getNumbering()->setChecked(true);

    if(str.contains("YYYY")) view->getYear()->setChecked(true);
    if (str.contains("DD")) view->getDay()->setChecked(true);
    if (str.contains("MM")) view->getMonth()->setChecked(true);
    if (findSignText() != "") view->getSign()->setText(findSignText());
    else view->getSign()->setText("Znak specjalny");
}

void SettingsDocumentNumberingController::checkIfChanged()
{
    if(view->getNumberingRest()->text() != numberingState)
        if (view->getMessageBox()->createQuestionBox("Tekst dokumentu został zmodyfikowany !") == MessageBox::YES)
        {
            editDocumentNumbering();
            view->emitChangesWereMade();
        }
}

void SettingsDocumentNumberingController::releaseLineNumbering()
{
     QString str = findSignText();
     if(str != "") deleteElementFromNumbering(str);

     QString value = view->getSign()->text();

     if (value == "Znak specjalny") ;
     else if (value == "")
     {
         view->getSign()->setText("Znak specjalny");
     }
     else
     {
         if( !value.contains(QRegExp("(M|m)[M|m]+")) && !value.contains(QRegExp("(D|d)[D|d]+"))
             && !value.contains(QRegExp("(Y|y)[Y|y]+")) && !value.contains(QRegExp("(#)[#]*")))
         {
             insertElementToNumbering(value);
         }
         else
         {
             view->getMessageBox()->createInfoBox("Niedozwolona formuła.");
         }
     }
}

SettingsDocumentNumberingController::~SettingsDocumentNumberingController()
{
    delete documentInfoModel;
}

SettingsDocumentNumberingView *SettingsDocumentNumberingController::getView() {return view;}
DocumentInfoModel *SettingsDocumentNumberingController::getModel() {return documentInfoModel;}

