#ifndef SETTINGSPRICESVIEW_H
#define SETTINGSPRICESVIEW_H

#include "Settings/SettingsAbstractItemView.h"
#include "Settings/GoodsSettings/SettingsPricesController.h"
#include <QLineEdit>
#include <QLabel>
#include <Components/Button.h>

class SettingsPricesController;

class SettingsPricesView : public SettingsAbstractItemView
{
    Q_OBJECT
public:
    SettingsPricesView(SettingsPricesController *controller,QWidget *parent);
    ~SettingsPricesView();
    QLineEdit* getLineMarginaA();
    QLineEdit* getLineDiscountB();
    QLineEdit* getLineDiscountC();

private:
    /**
     Metoda ustawiająca widgety okna w odpowiednich miejscach layoutu
    */
    void initGraphicElements() ;
    /**
     Metoda ingerująca w ustawienia layoutu oraz stan i wygląd widgetów
    */
     void setGraphicSettings();
    /**
     Metoda nadająca kontrolę odpowiednim widgetom w module
    */
    void setInterfaceController();

    QLineEdit * lineMarginA;
    QLineEdit * lineDiscountB;
    QLineEdit * lineDiscountC;
    Button * buttonSave;
    SettingsPricesController* controller;
};

#endif // SETTINGSPRICESVIEW_H
