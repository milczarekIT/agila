#include "FileInfo.h"

FileInfo::FileInfo()
{
}

QDateTime FileInfo::lowerDate(QFileInfo fileInfo)
{
    if(fileInfo.created() < fileInfo.lastModified())
        return fileInfo.created();
    else
        return fileInfo.lastModified();
}

QString FileInfo::sizeToStringWithUnit(QFileInfo fileInfo)
{
    int counter = 0;
    double size = fileInfo.size();
    while(size > 1000 && counter < 4)
    {
        size /= 1000;
        counter ++;
    }
    QString unit;
    if(counter == 0)
        unit = "B";
    else if(counter == 1)
        unit = "kB";
    else if(counter == 2)
        unit = "MB";
    else if(counter == 3)
        unit = "GB";

    return QString::number(size, ',', 1).replace(QRegExp("[.]"), ",") + " " + unit;
}
