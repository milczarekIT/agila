#ifndef DOCUMENTNKCONTROLLER_H
#define DOCUMENTNKCONTROLLER_H

#include "Document/PurchaseDocument/DocumentNK.h"
#include "Document/PurchaseDocument/DocumentNKView.h"
#include "Document/DocumentNumeratorController.h"
#include "SelectionWindows/SelectContractorController.h"
#include "Settings/OtherSettings/SettingsOwnerController.h"
#include "SelectionWindows/SelectInvoiceController.h"
#include "Settings/SettingsModel.h"
#include "Document/PurchaseDocument/DocumentNKService.h"
#include "Tools/Print/PrintPurchaseDocumentController.h"

class DocumentNKView;

class DocumentNKController : public QObject
{
    Q_OBJECT

    DocumentNKView *view;
    DocumentNumeratorController *dnc;
    SettingsOwnerController *ownerController;
    DocumentNKService *service;

    Contractor receiver;

    DocumentNK document;
    DocumentNK oldDocument;

    void initData();
    /**
      * Ustawia nazwisko odbierającego
      */
    void setReceiveName(Contractor receiver);

    /**
      * Ustawia nazwisko wystawiajacego
      */
    void setIssueName(QString name);


    /**
      * Sprawdza czy formularz nie jest czysty (niewypełniony)
      */
    bool isEmptyForm();
public:
    DocumentNKController(QWidget* parent);
    ~DocumentNKController();

    void exec();
    void exec(QString symbol);

    void insertInvoiceData(Document invoice);
    DocumentNK getDocumentNK();

public slots:
    void selectReceiver();
    void selectInvoice();
    void printDoc();

    /**
      * Sprawdza czy w formularzu wystąpiły zmiany
      */
    void checkChanges();
};

#endif // DOCUMENTNKCONTROLLER_H
