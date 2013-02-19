#ifndef PROGRESSBARDIALOG_H
#define PROGRESSBARDIALOG_H

#include <QFuture>
#include <QProgressDialog>
#include <QFutureWatcher>
#include <QtConcurrentRun>

class ProgressBarDialog : public QProgressDialog
{
    Q_OBJECT
private:
    void setGraphicSettings();
    QTimer *t;
    int steps;

public:
    explicit ProgressBarDialog(QWidget *parent = 0);
    static ProgressBarDialog& getInstance();
    void showProgresBar(QString labelText,int minimum, int maximum);
    void setText(QString labelText);
public slots:
    void perform();
    void cancel();

};

#endif // PROGRESSBARDIALOG_H
