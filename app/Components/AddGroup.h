#ifndef ADDGROUP_H
#define ADDGROUP_H

#include "QGridLayout"
#include "Components/InsertTextDialog.h"
#include <QDialog>
#include "QComboBox"
#include "ButtonBox.h"
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
class AddGroup: public InsertTextDialog
{

public:
    explicit AddGroup(QWidget *parent = 0);
    ~AddGroup();
    QComboBox*getBoxName();
    QLineEdit*getLineValue();

private:
      QComboBox *boxName;
      QLineEdit *lineSign;


};

#endif // ADDGROUP_H
