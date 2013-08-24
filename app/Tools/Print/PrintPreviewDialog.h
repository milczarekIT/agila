#ifndef PRINTPREVIEWDIALOG_H
#define PRINTPREVIEWDIALOG_H

#include <QGridLayout>
#include <QDialog>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPrintPreviewWidget>
#include "Components/Button.h"

class PrintPreviewDialog : public QDialog
{
    Q_OBJECT

public:
    PrintPreviewDialog(QPrinter* drukarka, QString windowTitle = "");
    ~PrintPreviewDialog();
    QGridLayout*mainLayout;
    QPrintPreviewWidget* print;
    QPrintPreviewWidget* getPreview();
    void show();
    void addComponents();

private:

    Button* zoomPlus;
    Button* zoomMinus;
    Button* close;
    QDoubleSpinBox* zoomFactor;

public slots:
    void zoomPl();
    void zoomMi();
    void changeZoom();
};

#endif // PRINTPREVIEWDIALOG_H
