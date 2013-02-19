#ifndef SELECTGOODVIEW_H
#define SELECTGOODVIEW_H

#include <QLabel>
#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QToolButton>
#include "Components/TableView.h"
#include "Components/Button.h"
#include "SelectionWindows/SelectGoodController.h"
class SelectGoodController;

class SelectGoodView : public QDialog {
    Q_OBJECT

private:
    Button* buttonOk;
    Button* buttonCancel;
    Button* buttonAddNewGood;
    Button* buttonEdit;
    Button* buttonSelectColumns;
    QGridLayout* mainLayout;
    QWidget *filterWidget;
    QGridLayout *filterLayout;
    QLineEdit *lineSymbolFilter;
    QLineEdit *lineNameFilter;
    QComboBox *chooseGoodGroup;
    TableView* goodsTable;
    SelectGoodController *controller;
    QCheckBox *markAll;

    void initButtons();
    void initConnection();
    void initTableConnections();
    void initTable();
    void initFilterWidget();
    virtual void addAllComponents();

public:
    explicit SelectGoodView( QWidget *parent, SelectGoodController * controller);
    ~SelectGoodView();    
    TableView* getGoodsTable();
    QComboBox *getChooseGoodGroup();
    void closeEvent(QCloseEvent *event);
    QWidget *getFilterWidget();
    QGridLayout *getFilterLayout();
    QGridLayout* getMainLayout();
    QCheckBox *getMarkAll();

};

#endif // SELECTGOODVIEW.H



