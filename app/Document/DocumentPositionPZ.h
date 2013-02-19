#ifndef DOCUMENTPOSITIONPZ_H
#define DOCUMENTPOSITIONPZ_H

#include "Document/DocumentPosition.h"
/**
  Rozszerza DocumentPosition o pole określające ilośc towaru jaką dostarczono do magazynu.
  Ta ilość nie musi być taka sama jak ilość przyjętego towaru, może być większa lub równa.
  @author Daniel Wojda
  */

class DocumentPositionPZ : public DocumentPosition
{

private:
    float amountDelivered;

public:
    DocumentPositionPZ();
    float getAmountDelivered();   //ilość towaru dostarczona
    void setAmountDelivered(float amount);
};

#endif // DOCUMENTPOSITIONPZ_H
