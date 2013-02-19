#ifndef SETTINGSTRANSPORTCONTROLLER_H
#define SETTINGSTRANSPORTCONTROLLER_H

#include <QWidget>
#include "Database/Database.h"
#include "Components/MessageBox.h"
#include "SettingsTransportView.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsTransportView;

class SettingsTransportController : public SettingsAbstractItemController
{
    Q_OBJECT

   SettingsTransportView *view;

public:

    explicit SettingsTransportController(QWidget *parent = 0);
    ~SettingsTransportController();

    SettingsTransportView *getView();

public slots:
    void showTransports();
    void addTransport();
    void editTransport();
    void deleteTransport();
    void saveTransport();
};

#endif // SETTINGSTRANSPORTCONTROLLER_H
