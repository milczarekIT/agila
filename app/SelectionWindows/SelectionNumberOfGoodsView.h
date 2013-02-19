#ifndef SELECTIONNUMBEROFGOODSVIEW_H
#define SELECTIONNUMBEROFGOODSVIEW_H

#include <QDialog>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QRadioButton>
#include <QComboBox>
#include <QLineEdit>
#include "Components/ButtonBox.h"
#include "SelectionWindows/SelectionNumberOfGoodsController.h"
#include "Other/Application/ApplicationManager.h"
#include "Goods/Unit.h"

class SelectionNumberOfGoodsController;

class SelectionNumberOfGoodsView : public QDialog   {

    Q_OBJECT
public:

    SelectionNumberOfGoodsView(SelectionNumberOfGoodsController*controller,QWidget *parent=0);
    void setMaxNumberOfGoods(double max);
    void setUnitName(QString unitName);
    void setZeroPlaces(int zeroPlaces);
    QComboBox* getComoboBox();
    void setPrices(QString priceNet,QString priceGross);
    double getPriceGross();
    double getPriceNet();
    bool isCheckMaxQuantity();
    bool isCheckQuantity();
    double getMaxQuantity();
    double getQuantity();
    int getSelectedPriceLevel();
private:

    void initLabels();
    void initLineEdits();
    void initButtons();
    void initConnections();
    void addAllComponents();

    QLabel* labelUnitQuantityMax;
    QLabel* labelUnitQuantity;
    QLabel* labelPriceNet;
    QLabel* labelPriceGross;
    QLabel* labelLevelOfPrices;

    QDoubleSpinBox* spinboxNumberOfGoods;
    QLineEdit* lineEditMaxQuantity;
    QRadioButton* checkQuantity;
    QRadioButton* checkMaxQuantity;
    ButtonBox* buttonBox;
    QComboBox* boxLevelOfPrices;
    SelectionNumberOfGoodsController *controller;

public slots:
    void setPrice(int index=0);
};

#endif // SELECTIONNUMBEROFGOODSVIEW_H
