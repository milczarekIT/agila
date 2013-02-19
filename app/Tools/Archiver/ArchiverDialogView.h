#ifndef ARCHIVERDIALOGVIEW_H
#define ARCHIVERDIALOGVIEW_H

#include <QDialog>
#include <QRadioButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QSpinBox>
#include <QLabel>
#include "Components/ButtonBox.h"
#include "Tools/Archiver/ArchiverDialogController.h"
class ArchiverDialogController;

/**
  * Widok okna Archiwizacji
  * @author Bartosz Milczarek
  */
class ArchiverDialogView : public QDialog
{
    Q_OBJECT

    /** controller */
    ArchiverDialogController *controller;

    QGridLayout *mainLayout;

    QGroupBox *groupRemind;
    QGroupBox *groupRemoveOld;
    QRadioButton *radioRemind;
    QRadioButton *radioDontRemind;
    QRadioButton *radioRemove;
    QRadioButton *radioDontRemove;
    QSpinBox *spinRemind;
    QSpinBox *spinRemove;
    QLabel *labelRemind;
    QLabel *labelRemove;

    QPushButton *buttonCreate;
    QPushButton *buttonRestore;
    QPushButton *buttonRemove;

    QTableView *table;
    QStandardItemModel *tableModel;

    ButtonBox *buttonBox;

    void initRadioButtons();
    void initButtons();
    void initTable();
    void initOther();
    void initConnections();
    void addAllComponents();
public:
    ArchiverDialogView(QWidget *parent, ArchiverDialogController *controller);
    ~ArchiverDialogView();

    QRadioButton *getRadioRemind();
    QRadioButton *getRadioDontRemind();
    QRadioButton *getRadioRemove();
    QRadioButton *getRadioDontRemove();
    QSpinBox *getSpinRemind();
    QSpinBox *getSpinRemove();
    QTableView *getTable();
    QStandardItemModel *getTableModel();

    QString getSelectedFileName();
};

#endif // ARCHIVERDIALOGVIEW_H
