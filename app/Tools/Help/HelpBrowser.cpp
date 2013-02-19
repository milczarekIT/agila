#include "HelpBrowser.h"

HelpBrowser::HelpBrowser(QHelpEngine *helpEngine, QWidget *parent)
    : QTextBrowser(parent), helpEngine(helpEngine)
{
}

QVariant HelpBrowser::loadResource(int type, const QUrl &url)
{
    if (url.scheme() == "qthelp")
        return QVariant(helpEngine->fileData(url));
    else
        return QTextBrowser::loadResource(type, url);
}
