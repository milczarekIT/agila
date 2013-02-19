#ifndef SETTINGSDEFAULTDOCPLACECONTROLLER_H
#define SETTINGSDEFAULTDOCPLACECONTROLLER_H

#include <QObject>
#include "Settings/SettingsModel.h"
#include "SettingsDefaultDocPlaceView.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsDefaultDocPlaceView;

class SettingsDefaultDocPlaceController : public SettingsAbstractItemController
{
    Q_OBJECT
private:

    SettingsDefaultDocPlaceView *view;
    SettingsModel *smodel;
    bool checkFillInTheFields();

public:
    explicit SettingsDefaultDocPlaceController(QObject *parent = 0);
    ~SettingsDefaultDocPlaceController();
    SettingsDefaultDocPlaceView *getView();
    SettingsModel *getModel();
    void setModel();

signals:

public slots:
    void defaultDocPlaceChanged();

};

#endif // SETTINGSDEFAULTDOCPLACECONTROLLER_H
