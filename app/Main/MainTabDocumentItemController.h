#ifndef MAINTABDOCUMENTITEMCONTROLLER_H
#define MAINTABDOCUMENTITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabItemController.h"
#include "Document/DocumentTVModel.h"
#include "Other/TableStateManager.h"
#include "Other/ITableStateManager.h"
#include "SelectionWindows/SelectVisibleColumns.h"

class MainTabDocumentItemController : public MainTabItemController, public ITableStateManager
{
    Q_OBJECT

protected:
    DocumentTVModel *documentTVModel;
    SelectVisibleColumns *selectColumnsDialog;

    virtual void initFilters() = 0;
    virtual void initSelectingColumnVisibility() = 0;

public:
    MainTabDocumentItemController();
    ~MainTabDocumentItemController();

    void refreshTable();

public slots:
    void setDocTypeFilter(QString documentType);
    void setFromDateFilter(QDate fromDate);
    void setToDateFilter(QDate toDate);
    void dialogSelectColumns();
    virtual void sortByColumn(int column) = 0;
    virtual void changeColumnVisiblity(QList<int> visibleColumns) = 0;
    virtual void printDocument()=0;

};

#endif // MAINTABDOCUMENTITEMCONTROLLER_H
