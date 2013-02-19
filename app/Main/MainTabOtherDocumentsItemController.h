#ifndef MAINTABOTHERDOCUMENTSITEMCONTROLLER_H
#define MAINTABOTHERDOCUMENTSITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabOtherDocumentsItem.h"
#include "Document/DocumentInfoModel.h"
#include "Document/PurchaseDocument/DocumentNKController.h"

class MainTabOtherDocumentsItem;

class MainTabOtherDocumentsItemController : public QWidget
{
    Q_OBJECT

private:
    MainTabOtherDocumentsItem *view;
    //OtherDocumentTVModel *otherDocumentTVModel;
    void initComboBox();
    void initDateEdits();
    void fillBox(QComboBox *box,QVector<DocumentInfo> values);

public:
    MainTabOtherDocumentsItemController();
    MainTabOtherDocumentsItem *getView();
    void initModel();

public slots:
    void dialogDocumentNKEdit();
    void dialogDocumentNKAdd();
    void setOtherDocTypeFilter(int index);
    void setOtherDocFromDateFilter(QDate fromDate);
    void setOtherDocToDateFilter(QDate toDate);
    void dialogEditDocument(QModelIndex index);
};

#endif // MAINTABOTHERDOCUMENTSITEMCONTROLLER_H
