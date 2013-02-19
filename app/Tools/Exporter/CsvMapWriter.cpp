#include "CsvMapWriter.h"

CsvMapWriter::CsvMapWriter(QString filePath)
{
    this->filePath  = filePath;

    file = new QFile(filePath);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    out = new QTextStream(file);

    delimiter = ";";
}

CsvMapWriter::~CsvMapWriter()
{
    file->close();
    delete file;
}

void CsvMapWriter::write(QMap<QString, QString> values, QStringList nameMapping) {

    this->nameMapping = nameMapping;
    QString *stringMap = toStringMap(values, nameMapping);

    write(stringMap);
}

QString* CsvMapWriter::toStringMap(QMap<QString, QString> values, QStringList nameMapping) {
    QString *res = new QString[nameMapping.length()];

    for(int i = 0; i < nameMapping.length(); i++)
        res[i] = values.value(nameMapping.at(i));

    return res;
}

void CsvMapWriter::write(QString *content) {
    QString *strarr = new QString[nameMapping.length()];
    for(int i = 0; i < nameMapping.length(); i++) {
        if(content[i] == NULL)
            strarr[i] = "";
        else
            strarr[i] = content[i];
    }

    writeToFile(strarr);
}

void CsvMapWriter::writeToFile(QString *content) {

        int i = 0;
        switch(nameMapping.length()) {

            case 0:
                *out << "Brak zawartości do zapisania ";

            case 1: // zapisze jeden (ostatni element) po instrukcji switch
                break;

            default:
                // zapisuje elementy od 1 do N-1
                for(; i < nameMapping.length() - 1; i++ ) {
                    *out << content[i] << delimiter << " ";
                }
                break;

         };

        // write last elem (without delimiter) and the EOL
        *out << content[i];
        *out << "\r\n";

        return;
}

void CsvMapWriter::writeHeader(QStringList nameMapping) {
    for(int i = 0; i < nameMapping.length() - 1; i++)
        *out << nameMapping.at(i) << delimiter << " ";

    *out << nameMapping.last() << "\r\n";
}
