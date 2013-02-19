#ifndef CSVMAPWRITER_H
#define CSVMAPWRITER_H

#include <QMap>
#include <QStringList>
#include <QDebug>
#include <QFile>

class CsvMapWriter
{
    QFile *file;
    QTextStream *out;

    QString filePath;
    QStringList nameMapping;
    QString delimiter;
    void write(QString *content);
    void writeToFile(QString *content);
    QString* toStringMap(QMap<QString, QString> values, QStringList nameMapping);

public:
    CsvMapWriter(QString file);
    ~CsvMapWriter();
    void writeHeader(QStringList nameMapping);
    void write(QMap<QString, QString> data, QStringList header);
};

#endif // CSVMAPWRITER_H
