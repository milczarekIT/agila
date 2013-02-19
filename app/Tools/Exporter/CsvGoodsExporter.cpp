    #include "CsvGoodsExporter.h"

CsvGoodsExporter::CsvGoodsExporter()
{
    initAvailableHeader();
}

void CsvGoodsExporter::initAvailableHeader() {
    header << "Symbol" << "Nazwa" << "Grupa" << "Towar/Usługa" << "VAT" << "j.m." << "Cena A netto" << "Cena A brutto"
           << "Cena B netto" << "Cena B brutto" << "Cena C netto" << "Cena C brutto" << "Cena zakupu netto" << "Cena zakupu brutto" << "Opis" << "Waga";
}

void CsvGoodsExporter::exportData(QVector<Goods> goods, QString filePath, QStringList selectedColumns) {

     CsvMapWriter *writer = new CsvMapWriter(filePath);

     writer->writeHeader(selectedColumns);
     foreach(Goods g, goods) {
         row.insert("Symbol", g.getSymbol());
         row.insert("Nazwa", g.getName());
         row.insert("Grupa", g.getGoodsGroup().getName());
         if(g.getType() == Goods::GOOD)
             row.insert("Towar/Usługa", "Towar");
         else if(g.getType() == Goods::SERVICE)
             row.insert("Towar/Usługa", "Usługa");

         if(g.getTax().getName().contains("zw."))
             row.insert("VAT", "zw.");
         else
             row.insert("VAT", QVariant(g.getTax().getValue()).toString().append("%"));

         row.insert("j.m.", g.getUnit().getName());
         row.insert("Cena A netto", g.getPriceNet(Price::A).toString());
         row.insert("Cena A brutto", g.getPriceGross(Price::A).toString());
         row.insert("Cena B netto", g.getPriceNet(Price::B).toString());
         row.insert("Cena B brutto", g.getPriceGross(Price::B).toString());
         row.insert("Cena C netto", g.getPriceNet(Price::C).toString());
         row.insert("Cena C brutto", g.getPriceGross(Price::C).toString());
         row.insert("Cena zakupu netto", g.getPriceNet(Price::MAG).toString());
         row.insert("Cena zakupu brutto", g.getPriceGross(Price::MAG).toString());
         row.insert("Opis", g.getDescription());
         row.insert("Waga", QVariant(g.getWeight()).toString());

         writer->write(row, selectedColumns);
     }
     delete writer;
 }
