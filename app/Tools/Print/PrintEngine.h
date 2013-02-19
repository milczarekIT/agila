#ifndef PRINTENGINE_H
#define PRINTENGINE_H
#include <QString>
#include <QWebPage>
#include <QtWebKit/QWebFrame>
#include <QWebElement>
#include <QFile>
#include <QDomDocument>
#include <QDir>
#include <QTextDocument>
#include <QPainter>
#include "Tools/Print/PrintDialogController.h"
#include "Tools/Print/HtmlStringReplacer.h"

class PrintEngine : public HtmlStringReplacer
{
private:
    QWebPage page;
    QString jsCode;
    QString templatePrefix; // Invoice, FM, etc...
    bool isSetHtml;
    void positionToDOM (QDomDocument &doc, QDomElement &node, DocumentPosition *data, float discount);
    void previousToDOM(QDomDocument &doc, QDomElement &node, SimpleDocumentInfo *data);

    /**
      * Metoda ukrywająca element img w szablonie wyświetlajacy logo. Element jest pomijany (ukrywany), gdy użytkownik nie zdefiniował logo w danych podmiotu
      */
    void hideLogoIfNotDefined();

    /**
      * Metoda oczekująca na załadowanie elementów graficznych, css itp.
      */
    void waitForLoad();
public:
    bool loadTemplate(QString templatePrefix);

    void addDocumentPosition(DocumentPosition *data,float discount=0);
    void addPreviousAdvances(SimpleDocumentInfo *data);
    void addCorrectionPosition(DocumentPosition *before, DocumentPosition *after, float discount);
    void addVatSummary (QString vatName, float valNet, float taxVal, float priceBrutto);
    void print(QPrinter *drukarka,bool paid=0);    
    void setHtml();
    PrintEngine();
};

#endif // PRINTENGINE_H
