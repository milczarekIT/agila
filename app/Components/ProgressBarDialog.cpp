#include "ProgressBarDialog.h"
#include "QThread"
#include <QTimer>
#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include <QDesktopWidget>

ProgressBarDialog::ProgressBarDialog(QWidget *parent)
{

}

ProgressBarDialog &ProgressBarDialog::getInstance()
{

        static ProgressBarDialog instance;
        return instance;

}

void ProgressBarDialog::showProgresBar(QString labelText, int minimum, int maximum) {

    this->setLabelText(labelText);
    this->setRange(minimum,maximum);
    QRect scr = QApplication::desktop()->screenGeometry();
    this->move( scr.center() - this->rect().center() - QPoint(this->rect().center().x(),0));
    setGraphicSettings();
    this->show();
}

void ProgressBarDialog::setText(QString labelText) {

    this->setLabelText(labelText);
}

void ProgressBarDialog::setGraphicSettings()
{
    steps = 1;
    this->setWindowModality(Qt::WindowModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setCancelButton(0);
    this->resize(400,150);

    t = new QTimer();

    connect(this, SIGNAL(canceled()), this, SLOT(cancel()));
    connect(t,SIGNAL(timeout()),this,SLOT(perform()));

    t->start(0);
}

void ProgressBarDialog::perform()
{
    this->setValue(steps);
    steps++;
    if (steps > this->maximum())
        t->stop();
}

void ProgressBarDialog::cancel()
{
    t->stop();
}

