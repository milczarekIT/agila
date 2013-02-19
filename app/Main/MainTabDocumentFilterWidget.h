#ifndef MAINTABDOCUMENTFILTERWIDGET_H
#define MAINTABDOCUMENTFILTERWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include "Components/DateEdit.h"
#include "Document/DocumentInfoModel.h"

class MainTabDocumentFilterWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *layout;
    QComboBox *comboboxDocumentsTypes;
    DateEdit *fromDateEdit;
    DateEdit *toDateEdit;
    QString documentFamily;

    void addAllComponents();
    void initData();
    void fillComboBox(QComboBox *box,QVector<DocumentInfo> values);
public:
    explicit MainTabDocumentFilterWidget(QString documentFamily, QWidget *parent = 0);

    QString getDocumentType();
    QDate getFromDate();
    QDate getToDate();
    
signals:
    void documentTypeChanged(QString type);
    void fromDateChanged(QDate fromDate);
    void toDateChanged(QDate toDate);

private slots:
    void documentTypeChanged(int index);
    
};

#endif // MAINTABDOCUMENTFILTERWIDGET_H
