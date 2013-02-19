#include "CsvContractorExporter.h"

CsvContractorExporter::CsvContractorExporter()
{
    initAvailableHeader();
}

void CsvContractorExporter::initAvailableHeader() {
    header << "Symbol" << "Nazwa" << "Grupa" << "Kod pocztowy" << "Miejscowość" << "Adres" << "Telefon" << "NIP"
           << "e-mail" << "Strona internetowa" << "Rabat";
}

void CsvContractorExporter::exportData(QVector<Contractor> contractors, QString filePath, QStringList selectedColumns) {

     CsvMapWriter *writer = new CsvMapWriter(filePath);

     writer->writeHeader(selectedColumns);
     foreach(Contractor c, contractors) {
         row.insert("Symbol", c.getSymbol());
         row.insert("Nazwa", c.getName());
         row.insert("Grupa", c.getContractorGroup().getName());


         row.insert("Kod pocztowy", c.getPostcode());
         row.insert("Miejscowość", c.getCity());
         row.insert("Adres", c.getAddress());
         row.insert("Telefon", c.getDefultPhone());
         row.insert("NIP", c.getNip());
         row.insert("e-mail", c.getEmail());
         row.insert("Strona internetowa", c.getWebsite());
         row.insert("Rabat", QVariant(c.getDiscount()).toString());

         writer->write(row, selectedColumns);
     }
     delete writer;
 }
