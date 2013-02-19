#ifndef MAINTABDOCUMENTITEM_H
#define MAINTABDOCUMENTITEM_H

#include "Main/MainTabItem.h"
#include "Main/MainTabDocumentFilterWidget.h"

class MainTabDocumentItem : public MainTabItem
{
protected:
    MainTabDocumentFilterWidget *filterWidget;

public:
    MainTabDocumentItem();

    MainTabDocumentFilterWidget *getFilterWidget();

};

#endif // MAINTABDOCUMENTITEM_H
