#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>
#include <QDebug>

/**
  @author Janiu
  Klasa będąca rozszerzeniem QMessageBoxa, udostepniajaca wiele form tego okienka
  */
class MessageBox : public QMessageBox
{
    Q_OBJECT

public:
  /**
    Konstruktor MessageBox'a
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
   */
    explicit MessageBox(QWidget *parent = 0);

    static const int N0 = 1;
    static const int YES = 2;
    static QString INFORMATIVE_TEXT;

  /**
    Metoda, która tworzy okienko dialogowe z zapytaniem o potwierdzenie akcji
    */
    int createQuestionBox(QString text, QString informativeText = MessageBox::INFORMATIVE_TEXT, Icon icon = QMessageBox::Question);
  /**
    Metoda, która tworzy okienko dialogowe z zawarta informacja
    */
    void createInfoBox(QString text);
    void createWarningBox(QString text);
};

#endif // MESSAGEBOX_H
