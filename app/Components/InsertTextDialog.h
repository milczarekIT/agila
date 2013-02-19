#ifndef INSERTTEXTDIALOG_H
#define INSERTTEXTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include "Components/ButtonBox.h"

/**
  @author Janiu
  Klasa prostego okienka dialogowego, używanego wielokrotnie do przejmowania wpisanej w lineEdit danej
  wykorzystywanej do najróżniejszych celów
 */
class InsertTextDialog : public QDialog
{
    Q_OBJECT

public:
/**
  Konstruktor inicjujący wskaźnik do okienka dialogowego dla danej klasy
  @param
  parent - wskaźnik określający rodzica okna, wykorzystywany w programie
*/
    explicit InsertTextDialog(QWidget *parent = 0);
    ~InsertTextDialog();

    QLineEdit *getLineEdit();

protected:
  /**
     Pole, w którym umieszczamy pewne dane, które przekazywane są po akceptacji do dalszego przetwarzania
     w programie
  */
    QLineEdit *lineEdit;

public:
    ButtonBox *buttonBox;
    QGridLayout *mainLayout;
public slots:
    void signGenerating(QString value);
};

#endif
