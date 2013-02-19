#ifndef DOCUMENTCONTROLLER_H
#define DOCUMENTCONTROLLER_H

#include "Document/DocumentManager.h"
#include "Document/DocumentView.h"
#include "Document/DocumentValidator.h"
#include "Settings/SettingsModel.h"
#include "Document/DocumentNumeratorController.h"
#include "Other/TableStateManager.h"
#include "Other/ITableStateManager.h"
#include "Other/Preferences/SettingsPreferencesService.h"

class DocumentView;
class DocumentValidator;

class DocumentController : public QObject, public ITableStateManager
{
    Q_OBJECT

public:

    virtual void exec() = 0;
    virtual void exec(QString symbol) = 0;

    explicit DocumentController();
    ~DocumentController();
    DocumentManager* getDocumentManager();
    QString getSymbol();
    bool getEdition();

protected:

    virtual void addGood() = 0;
    virtual void setGoodsValue() =0;
    virtual bool isQuantityColumn(int column) = 0;
    void addContractor();
    void insertGood(int i, int id, QTableWidgetItem *text);
    virtual bool isChangesOccured() = 0;

    DocumentNumeratorController *dnc;
    DocumentManager* manager;
    bool edition;
    bool totalFromBase;
    QString symbol;
    DocumentView* view;
    DocumentValidator *validator;
    SettingsModel *smodel;
    bool changingContractor;
    TableStateManager *tableStateManager;
    SettingsPreferencesService* preferences;

public slots:

    virtual void printDoc() = 0;
    virtual void updatePaymentDate();
    virtual void selectOrderOrFacture();
    virtual void selectZAL();
    virtual void selectGoods();
    virtual void changedRealizedOrSymbol();
    void checkChanges();
    void checkRequiredFields();
    void selectContractor();
    void editGood(int row, int column);
    void removeGood();
    virtual void getDocumentData() =0;
    void discountChanged();
    virtual void changedPaid();
    virtual void removeZal();
};

#endif // DOCUMENTCONTROLLER_H
