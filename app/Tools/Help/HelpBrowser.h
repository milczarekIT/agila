#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QTextBrowser>
#include <QHelpEngine>

class QHelpEngine;

class HelpBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    HelpBrowser(QHelpEngine *helpEngine, QWidget *parent = 0);
    QVariant loadResource(int type, const QUrl &url);

private:
    QHelpEngine *helpEngine;
};

#endif // HELPBROWSER_H
