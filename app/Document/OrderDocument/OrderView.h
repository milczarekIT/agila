#ifndef OrderView_H
#define OrderView_H

#include "Document/OrderDocument/OrderController.h"
#include "Document/SaleDocument/SaleView.h"

class OrderController;

class OrderView : public SaleView  {

public:
    OrderView(QWidget *parent, OrderController* controller);
    ~OrderView();

    void initOptionalLineEdits();
    void initOptionalConnections();
    void addOptionalComponents();
    void initOptionalButtons();
    QDate getRealizationDate();
    bool isRealized();
    void setRealized(bool realized);
    void setRealizationDate(QDate realizationDate);
    void setTabOrders();
private:
    DateEdit* dateRealization;
    QCheckBox *checkRealization;
};

#endif // OrderView_H
