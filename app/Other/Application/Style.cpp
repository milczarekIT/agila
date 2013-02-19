#include "Style.h"

Style* Style::instance = 0;

Style::Style() {
    initActualStyle();
}

Style::~Style() {
    delete instance;
}

Style* Style::getInstance() {
    if(!instance) {
        instance = new Style();
    }
    return instance;
}

void Style::initActualStyle() {
    QSettings *settings = new QSettings();
    qssPath = settings->value("stylesheet", ":/themes/blue").toString();

    if(qssPath.contains("blue"))
        actualStyle = BLUE;
    else if(qssPath.contains("grey"))
        actualStyle = GREY;
    else
        actualStyle = STANDARD;
    delete settings;
}

void Style::setApplicationStyle(QApplication *app) {
    QFile qss(qssPath);
    qss.open(QFile::ReadOnly);

    QString readall = qss.readAll();
    app->setStyleSheet(readall);
    qss.close();
}

void Style::changeApplicationStyle(StyleSheet newStyle) {
    QSettings *settings = new QSettings();
    setStyleSheet(newStyle);

    if(isBlueStyleSheet())
        settings->setValue("stylesheet",":/themes/blue");
    else if(isGreyStyleSheet())
        settings->setValue("stylesheet",":/themes/grey");
    else if(isStandardStyleSheet())
        settings->setValue("stylesheet",":/themes/standard");
    delete settings;
}

QString Style::getLogginUserInfo() {
    if(isBlueStyleSheet())
        return "Zalogowany jako: <font color=\"#87dc44\">";
    else if(isGreyStyleSheet())
        return "<font color=\"grey\">Zalogowany jako: </font><font color=\"green\">";
    else if(isStandardStyleSheet())
        return "Zalogowany jako: ";
}

void  Style::setStyleSheet(StyleSheet newStyle) {
    actualStyle = newStyle;
}

QString Style::getPath() {
    return qssPath;
}


bool Style::isBlueStyleSheet() {
    return actualStyle == BLUE;
}

bool Style::isGreyStyleSheet() {
    return actualStyle == GREY;
}

bool Style::isStandardStyleSheet() {
    return actualStyle == STANDARD;
}
