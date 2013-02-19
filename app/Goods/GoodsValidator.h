#ifndef GOODSVALIDATOR_H
#define GOODSVALIDATOR_H

#include "Other/Validator.h"
#include "Goods/GoodsDialogView.h"
class GoodsDialogView;

class GoodsValidator : public Validator
{
    GoodsDialogView *view;

public:
    GoodsValidator(GoodsDialogView *view);
    ~GoodsValidator();

    void validateForm();
    bool isEmptyForm();
};

#endif // GOODSVALIDATOR_H
