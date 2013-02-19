#ifndef PRINTDIALOGCONTROLLER_H
#define PRINTDIALOGCONTROLLER_H

#include <QObject>
#include <QPrinter>
#include <QDir>
#include <QFileDialog>
#include <QCheckBox>
#include <QSettings>
#include "Tools/Print/PrintPreviewDialog.h"
#include "Other/Application/ApplicationManager.h"
#include "Document/SaleDocument/Invoice.h"
#include "Document/StoreDocument/StoreDocument.h"
#include "Document/StoreDocument/DocumentWZ.h"
#include "Document/StoreDocument/DocumentPZ.h"
#include "Document/SaleDocument/DocumentFK.h"
#include "Document/SaleDocument/DocumentZAL.h"
#include "Document/PurchaseDocument/DocumentNK.h"
#include "Tools/Print/DocumentServices.h"
#include "Tools/Print/PrintManager.h"
#include "Tools/Print/PrintDialogView.h"
#include "Other/Preferences/SettingsPreferencesService.h"

class PrintDialogView;
class PrintManager;

class PrintDialogController : public QObject
{
    Q_OBJECT

public:

    PrintDialogController(QString symbol, QWidget *parent=0);
    ~PrintDialogController();

    void options(QString symbol,int print, QString copy);
    void addDocToTable(QVector<SimpleDocumentInfo> vectorDoc);
    void printRelated(QVector<SimpleDocumentInfo> vectorDoc);
    QString getUserSaveToPdfDirectories();
    void restoreDefaultPrintPreferences();
    virtual void createDirectories() =0;
    void setUserSaveToPdfDirectories();
    void setDefaultPrintPreferences();
    bool arePrintPreferencesChanged();
    virtual void setOutputFile() =0;
    void directories();
    void initOptions();
    void setOptions();
    int show();

    QString getSymbol();
    void setSymbol(QString symbol);
    QString getType();
    void setType(QString Type);
    bool getPrintReleated();
    void setPrintReleated(bool printReleated);
    PrintDialogView* getView();
    void setView(PrintDialogView* view);
    int getPrintAndSave();
    void setPrintAndSave(int printAndSave);
    PrintManager* getManager();
    void setManager(PrintManager* manager);
    QString getCopyOrOriginal();
    void setCopyOrOriginal(QString copyOrOriginal);
    QPrinter* getPrinter();
    void setPrinter(QPrinter* printer);
    bool getSaveToPdf();
    void setSaveToPdf(bool saveToPdf);
    DocumentServices* getDocumentService();
    void setDocumentService(DocumentServices* docService);
    SettingsPreferencesService *getPreferences();
    void setPreferences(SettingsPreferencesService* preferences);
    QSettings * getSettings();
    void setSettings(QSettings* settings);
private:

    SettingsPreferencesService* preferences;
    DocumentServices *docServ;
    PrintDialogView * view;
    QFileDialog * fDialog;
    PrintManager* manager;
    QString copyOriginal;
    QSettings* settings;
    QPrinter* printer;
    QString symbol;
    bool saveToPdf;
    bool printReleatedDoc;
    QString type;
    /**
      *Jesli wartosc jest 1 tzn ze petla wykona sie raz i albo sie tylko wydrukuje albo tylko zapisze do pdf
      *Jesli wartosc jest 2 tzn ze petla drukwoania wykona sie dwa razy i zapisze do pdfa i tez przekieruje na drukarke
      **/
    int printAndSave;

public slots:

    void browsePath();
    void printPreview();
    virtual void printPreviewFile() = 0;
    void printerChooser(QString name);
};

#endif // PRINTDIALOGCONTROLLER_H
