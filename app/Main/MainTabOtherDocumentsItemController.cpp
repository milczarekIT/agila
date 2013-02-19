#include "MainTabOtherDocumentsItemController.h"

MainTabOtherDocumentsItemController::MainTabOtherDocumentsItemController()
{
    view = new MainTabOtherDocumentsItem(this);
    otherDocumentTVModel = new OtherDocumentTVModel();
    initModel();
    initComboBox();
    initDateEdits();
}

MainTabOtherDocumentsItem *MainTabOtherDocumentsItemController::getView()
{
    return view;
}

void MainTabOtherDocumentsItemController::dialogDocumentNKEdit()
{
    QString symbol = view->getTableView()->getSymbol();
    if(symbol.isEmpty())
    {
         MessageBox *messageBox = new MessageBox();
         messageBox->createInfoBox("Zaznacz dokument do edycji");
         delete messageBox;
    }
    else
    {
         DocumentNKController *controller = new DocumentNKController(this);
         controller->exec(symbol);
         delete controller;

         otherDocumentTVModel->getOtherDocuments();
    }
}

void MainTabOtherDocumentsItemController::dialogDocumentNKAdd()
{
    DocumentNKController *controller = new DocumentNKController(this);
    controller->exec();
    delete controller;
}

void MainTabOtherDocumentsItemController::setOtherDocTypeFilter(int index)
{
    QString documentType = view->getOtherDocuments()->itemData(index).toString();

    otherDocumentTVModel->setDocTypeFilter(documentType);
    otherDocumentTVModel->getOtherDocuments();
}

void MainTabOtherDocumentsItemController::initComboBox()
{
    DocumentInfoModel *docInfoModel = new DocumentInfoModel();
    view->getOtherDocuments()->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    view->getOtherDocuments()->setStatusTip("Wybierz typ dokumentów");
    view->getOtherDocuments()->addItem("Wszystkie", QVariant(""));
    fillBox(view->getOtherDocuments(), docInfoModel->getDocumentsInfo("OTHER"));
    connect(view->getOtherDocuments(), SIGNAL(currentIndexChanged(int)), this, SLOT(setOtherDocTypeFilter(int)));
}

void MainTabOtherDocumentsItemController::fillBox(QComboBox *box,QVector<DocumentInfo> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getType()));
}

void MainTabOtherDocumentsItemController::initDateEdits()
{
    CalendarWidget *otherDocFromCalWidget = new CalendarWidget;
    CalendarWidget *otherDocToCalWidget = new CalendarWidget;

    view->getOtherDocFrom()->setCalendarWidget(otherDocFromCalWidget);
    view->getOtherDocFrom()->setDate(QDate(QDate::currentDate().year(), 1, 1));
    otherDocumentTVModel->setFromDateFilter(view->getOtherDocFrom()->date());

    view->getOtherDocTo()->setCalendarWidget(otherDocToCalWidget);
    view->getOtherDocTo()->setDate(QDate(QDate::currentDate().year(), 12, 31));
    otherDocumentTVModel->setToDateFilter(view->getOtherDocTo()->date());
}

void MainTabOtherDocumentsItemController::setOtherDocFromDateFilter(QDate fromDate)
{
    otherDocumentTVModel->setFromDateFilter(fromDate);
    otherDocumentTVModel->getOtherDocuments();
}

void MainTabOtherDocumentsItemController::setOtherDocToDateFilter(QDate toDate)
{
    otherDocumentTVModel->setToDateFilter(toDate);
    otherDocumentTVModel->getOtherDocuments();
}

void MainTabOtherDocumentsItemController::initModel()
{
    otherDocumentTVModel->getOtherDocuments();
    view->getTableView()->setOtherDocumentModel(otherDocumentTVModel);
}

void MainTabOtherDocumentsItemController::dialogEditDocument(QModelIndex index)
{
       QString symbol = view->getTableView()->getSymbol(index);
           if(symbol.contains("KP"))
               qDebug() << "TODO: Edytuj Kasa przyjmie " << symbol;
           else if(symbol.contains("NK"))
               dialogDocumentNKEdit();
}
