#ifndef SETTINGSDEFAULTDOCPLACEVIEW_H
#define SETTINGSDEFAULTDOCPLACEVIEW_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include "Components/Button.h"
#include "SettingsDefaultDocPlaceController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsDefaultDocPlaceController;

class SettingsDefaultDocPlaceView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
    SettingsDefaultDocPlaceController *controller;
    /**
      LineEdit, który przechowuje domyślne miejsce wystawiania dokumentów
     */
    QLineEdit *defaultDocumentPlace;
    Button *pushSave;

public:
    explicit SettingsDefaultDocPlaceView(SettingsDefaultDocPlaceController *controller, QWidget *parent = 0);
    QLineEdit *getDefaultDocumentPlace();
    Button *getPushSave();

};

#endif // SETTINGSDEFAULTDOCPLACEVIEW_H
