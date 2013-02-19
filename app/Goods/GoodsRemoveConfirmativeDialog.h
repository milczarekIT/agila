#ifndef GOODSREMOVECONFIRMATIVEDIALOG_H
#define GOODSREMOVECONFIRMATIVEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QHBoxLayout>
#include "Goods/GoodsService.h"

class GoodsRemoveConfirmativeDialog : public QDialog
{
    Q_OBJECT
private:
    GoodsService *service;
    int idGood;

    QDialogButtonBox *buttonBox;
    QLabel *text;
    QGridLayout *layout;
    QHBoxLayout *buttonsLayout;

    QPushButton *removeButton;
    QPushButton *removeAllButton;
    QPushButton *cancelButton;

    void initView();
    void initViewForGoodOnlyAtActualWarehouse();
    void initViewForGoodsInFewWarehouses();
    void initConnections();
public:
    GoodsRemoveConfirmativeDialog(int id,QWidget *parent);

public slots:
    void removeGood();
    void removeGoodFromAllWarehouses();
};

#endif // GOODSREMOVECONFIRMATIVEDIALOG_H
