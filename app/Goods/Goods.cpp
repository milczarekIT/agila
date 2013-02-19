#include "Goods.h"

Goods::Goods()
{
    prices = new QVector<Price>(8);
    type = GOOD;
}

Goods::~Goods()
{
}

void Goods::setSymbol(QString symbol) {
    this->symbol = symbol;
}
void Goods::setType(int type) {
    this->type = type;
}

void Goods::setQuantity(float quantity) {
    this->quantity = quantity;
}
void Goods::setTax(Tax tax) {
    this->tax = tax;
}
void Goods::setUnit(Unit unit) {
    this->unit = unit;
}
void Goods::setPkwiu (QString pkwiu) {
    this->pkwiu = pkwiu;
}
void Goods::setGoodsGroup (GoodsGroup goodsGroup) {
    this->goodsGroup = goodsGroup;
}
void Goods::setPriceNet(int priceType, double priceValue) {
    prices->replace(priceType + Price::NET, Price(priceValue));
}

void Goods::setPriceGross(int priceType, double priceValue) {
    prices->replace(priceType + Price::GROSS, Price(priceValue));
}
void Goods::setDescription(QString description) {
    this->description = description;
}
void Goods::setFoto(QString foto) {
    this->foto = foto;
}
void Goods::setWeight(float weight) {
    this->weight = weight;
}
void Goods::setFeatures(QVector<Feature> features) {
    this->features = features;
}

QString Goods::getSymbol() {
    return symbol;
}
int Goods::getType() {
    return type;
}

float Goods::getQuantity() {
    return quantity;
}
Tax Goods::getTax() {
    return tax;
}
Unit Goods::getUnit() {
    return unit;
}
QString Goods::getPkwiu() {
    return pkwiu;
}
GoodsGroup Goods::getGoodsGroup() {
    return goodsGroup;
}
QVector<Price> *Goods::getPrices() {
    return prices;
}
Price Goods::getPriceNet(int priceType) {
    return prices->value(priceType + Price::NET);
}
Price Goods::getPriceGross(int priceType) {
    return prices->value(priceType + Price::GROSS);
}
QString Goods::getDescription() {
    return description;
}
QString Goods::getFoto() {
    return foto;
}
float Goods::getWeight() {
    return weight;
}
QVector<Feature> Goods::getFeatures() {
    return features;
}

int Goods::operator ==(Goods g)
{
    if(this->id != g.getId())
        return 0;
    else if(this->name != g.getName())
        return 0;
    else if(this->symbol != g.getSymbol())
        return 0;
    else if(this->type != g.getType())
        return 0;
    else if(!(this->tax == g.getTax()))
        return 0;
    else if(!(this->unit == g.getUnit()))
        return 0;
    else if(this->pkwiu != g.getPkwiu())
        return 0;
    else if(this->weight != g.getWeight())
        return 0;
    else if(!(this->goodsGroup == g.getGoodsGroup()))
        return 0;
    else if(!isEqualsPrices(g.getPrices()))
        return 0;
    else
        return 1;
}

bool Goods::isEqualsPrices(QVector<Price> *prices) {
    if(this->prices->size() != prices->size())
        return false;

    QVector<Price> prices1 = *this->prices;
    QVector<Price> prices2 = *prices;

    for(int i = 0; i < this->prices->size(); i++)
    {
        if(prices1[i].value() != prices2[i].value())
            return false;
    }

    return true;
}

QString Goods::toString()
{
    return QString("1) Id: ").append(QVariant(this->getId()).toString()) + QString(", 2) Symbol: ").append(this->getSymbol())
            + QString(", 3) Nazwa: ").append(this->getName()) + QString(", 4) Ilość: ").append(QVariant(this->getQuantity()).toString())
            + QString(", 5) VAT: ").append(QVariant(this->getTax().getId()).toString()) + QString(", 6) j.m.: ").append(this->getUnit().getName())
            + QString(", 7) PKWiU: ").append(this->getPkwiu()) + QString(", 8) Grupa: ").append(this->getGoodsGroup().getId())
            + QString(", 9) Cena A netto: ").append(this->getPriceNet(Price::A).toString())
            + QString(", 10) Cena A brutto: ").append(this->getPriceGross(Price::A).toString())
            + QString(", 11) Cena mag netto: ").append(this->getPriceNet(Price::MAG).toString())
            + QString(", 12) Cena mag brutto: ").append(this->getPriceGross(Price::MAG).toString())
            + QString(", 13) Cena B netto: ").append(this->getPriceNet(Price::B).toString())
            + QString(", 14) Cena B brutto: ").append(this->getPriceGross(Price::B).toString())
            + QString(", 15) Cena C netto: ").append(this->getPriceNet(Price::C).toString())
            + QString(", 16) Cena C brutto: ").append(this->getPriceGross(Price::C).toString())
            + QString(", 17) Opis: ").append(this->getDescription()) + QString(", 18) Foto: ").append(this->getFoto())
            + QString(", 19) Masa: ").append(QVariant(this->getWeight()).toString());
}
