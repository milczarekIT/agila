#ifndef BUTTONSLIST_H
#define BUTTONSLIST_H

#include <QComboBox>
#include <QListView>
#include <QStandardItemModel>
#include "Other/Application/ApplicationManager.h"

class ButtonsList : public QComboBox
{
    Q_OBJECT

private:
    QStandardItemModel *model;
    QListView *tV;
    int row;
    int col;

public:
    explicit ButtonsList(QWidget *parent = 0);
    void addItem(const QString &text, QString status, QString icon);

    QStandardItemModel *getModel();
    QListView *getTableView();

signals:

public slots:

};

#endif // BUTTONSLIST_H
