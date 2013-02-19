#ifndef TAXCHANGERMODEL_H
#define TAXCHANGERMODEL_H

#include "Database/Model.h"
#include "Goods/Goods.h"

/**
  * Model zmieniacza stawek VAT
  * @author Bartosz Milczarek
  */
class TaxChangerModel : public Model
{
public:
    TaxChangerModel();

    /**
      * Metoda zmieniająca stawki VAT, dla wszystkich towarów, które do tej pory miały oldTax.
      * Od teraz wszystkie towary będą miały newTax.
      *
      * Metoda wylicza nowe ceny towarom
      * @param basePrice - cena bazowa netto lub brutto na podstawie której odbywa się przeliczenie
      *        basePrice = Price::NET - na podstawie cen netto wylicza nowe ceny brutto (domyślnie)
      *        basePrice = Price::GROSS - na podstawie cen brutto wylica nowe ceny netto
      *
      * @param priceType = typ cen jaki ma być przeliczony: ceny ABC, ceny zakupu, wszystkie ceny
      *        priceType = Price::ABC - przeliczone zostaną ceny A,B,C
      *        priceType = Price::MAG - przeliczone zostaną ceny magazynowe
      *        priceType = Price::ABC + Price::MAG - przeliczone zostaną wszystkie ceny
      */
    void changeTaxesForAll(Tax oldTax, Tax newTax, int basePrice = Price::NET, int priceType = Price::ABC + Price::MAG);

    /**
      * Metoda zmieniająca stawki VAT, dla wszystkich towarów należącej do danej grupy towarowej
      */
    void changeTaxesForGroup(int goodGroup, Tax newTax, int basePrice, int priceType);
};

#endif // TAXCHANGERMODEL_H
