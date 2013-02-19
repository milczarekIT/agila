#ifndef GOODS_H
#define GOODS_H

#include <QDebug>
#include <cstdlib>
#include <iostream>
#include <QString>
#include <QVector>
#include <QVariant>
#include "Other/SimpleStructure.h"
#include "Goods/GoodsGroup.h"
#include "Goods/Unit.h"
#include "Goods/Tax.h"
#include "Goods/Feature.h"
#include "Goods/Price.h"

using namespace std;

class Goods : public SimpleStructure
{
private:
    QString symbol;
    int type;
    float quantity;
    Tax tax;
    Unit unit;
    QString pkwiu;
    GoodsGroup goodsGroup;
    QVector<Price> *prices;
    QString description;
    QString foto;
    float weight;
    QVector<Feature> features;

    bool isEqualsPrices(QVector<Price> *prices);

public:
    Goods();
    ~Goods();

    // typy
    static const int GOOD = 1;
    static const int SERVICE = 2;

    void setSymbol(QString symbol);
    void setType(int type);
    void setQuantity(float quantity);
    void setTax(Tax tax);
    void setUnit(Unit unit);
    void setPkwiu (QString pkwiu);
    void setGoodsGroup (GoodsGroup goodsGroup);
    void setPriceNet(int priceType, double priceValue);
    void setPriceGross(int priceType, double priceValue);
    void setDescription(QString description);
    void setFoto(QString foto);
    void setWeight(float weight);
    void setFeatures(QVector<Feature> features);

    QString getSymbol();
    int getType();
    float getQuantity();
    Tax getTax();
    Unit getUnit();
    QString getPkwiu();
    GoodsGroup getGoodsGroup();
    QVector<Price>* getPrices();
    Price getPriceNet(int priceType);
    Price getPriceGross(int priceType);
    QString getDescription();
    QString getFoto();
    float getWeight();
    QVector<Feature> getFeatures();

    int operator ==(Goods g);
    QString toString();

};

#endif // GOODS_H
