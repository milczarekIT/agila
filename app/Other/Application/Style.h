#ifndef STYLE_H
#define STYLE_H

#include <QFile>
#include <QSettings>
#include <QApplication>

class Style
{
public:
    enum StyleSheet {
        GREY,
        BLUE,
        STANDARD
    };

private:
    static Style* instance;
    StyleSheet actualStyle;
    QString qssPath;

public:
    Style();
    ~Style();

    static Style *getInstance();
    void setStyleSheet(StyleSheet newStyle);
    void setApplicationStyle(QApplication *app);
    void initActualStyle();
    QString getPath();
    QString getLogginUserInfo();
    bool isBlueStyleSheet();
    bool isGreyStyleSheet();
    bool isStandardStyleSheet();
    void changeApplicationStyle(StyleSheet newStyle);
};

#endif // STYLE_H
