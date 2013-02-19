#ifndef HELPDIALOGVIEW_H
#define HELPDIALOGVIEW_H

#include <QtHelp>
#include <QDialog>
#include <QSplitter>
#include <QHelpEngine>
#include <QGridLayout>
#include <QDockWidget>
#include "HelpBrowser.h"

class HelpDialogView : public QDialog
{
    Q_OBJECT
private:
    QHelpEngine *helpEngine;
    HelpBrowser *helpBrowser;
    QGridLayout *mainLayout;
    QSplitter *panel;
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();

public:
    explicit HelpDialogView(QWidget *parent = 0);

signals:

public slots:

};

#endif // HELPDIALOGVIEW_H
