#ifndef PRINTDIALOGVIEW_H
#define PRINTDIALOGVIEW_H

#include <QDialog>
#include <QGridLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QPrinterInfo>
#include <QLabel>
#include <QTableWidget>
#include "Components/Button.h"
#include "Tools/Print/PrintDialogController.h"

class PrintDialogController;

class PrintDialogView : public QDialog
{
    Q_OBJECT
public:
    PrintDialogView(QWidget *parent, PrintDialogController *controller);
    ~PrintDialogView();
    void initComponents();
    void addComponents();
    void initConnections();
    void initTable();
    void addData();
    QLineEdit* getPath();
    QSpinBox* getSpinBox();
    QComboBox* getBoxPrint();
    QTableWidget* getTable();
    bool ifSetAsDefualtPath();
    bool isDuplicate();
    PrintDialogController* getController();
    void setController(PrintDialogController* controller);
    QGridLayout* getLayout();
    void setMainLayout(QGridLayout* layout);
    void setPrinterInfo(QPrinterInfo* info);
    QPrinterInfo * getPrinterInfo();

private:

    PrintDialogController * controller;
    QPrinterInfo * inf;
    QGridLayout* mainLayout;
    QTableWidget* table;
    QComboBox* boxPrint;
    QCheckBox* checkBox;
    QCheckBox* checkDuplicate;
    QComboBox* boxPrinter;
    QSpinBox* boxCopies;
    QLineEdit* linePath;
    Button* buttonPreview;
    Button* browsePath;
    Button* buttonPrint;
    Button* buttonCancel;

};

#endif // PRINTDIALOGVIEW_H
