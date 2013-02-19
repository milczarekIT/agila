#ifndef FILEINFO_H
#define FILEINFO_H

#include <QFileInfo>
#include <QDateTime>
#include <QRegExp>

class FileInfo : public QFileInfo
{
public:
    FileInfo();

    static QDateTime lowerDate(QFileInfo fileInfo);
    static QString sizeToStringWithUnit(QFileInfo fileInfo);
};

#endif // FILEINFO_H
