#include "DocumentNumeratorController.h"

DocumentNumeratorController::DocumentNumeratorController(QString documentType)
{
    today = QDate::currentDate();
    this->documentType = documentType;
    initAllowedSequences(documentType);


    previousSymbol = new Symbol();
    model = new DocumentNumeratorModel();

    DocumentInfoModel *documentInfoModel = new DocumentInfoModel();
    QString tableName = documentInfoModel->getTableNameByDocumentType(documentType);

    previousSymbolStr = model->getPrevoiusSymbol(documentType, tableName);
    numberingFormat = model->getNumberingFormat(documentType);

    this->initFormatSequences(numberingFormat);

    formatPattern = this->getRexExpPattern();
}

DocumentNumeratorController::~DocumentNumeratorController()
{
    delete previousSymbol;
    delete model;
}

QString DocumentNumeratorController::getNextSymbol()
{
    if(isSameFormat()) // sprawdź czy format numerowania jest taki sam dla poprzedniego symbolu i obecnego formatu
    {
        readVariablesFromPrevious();

        return prepareNextSymbol();
    }
    else
        return prepareNextSymbol(false);

}

bool  DocumentNumeratorController::isValidSymbol(QString symbol)
{
    QRegExp rx;
    rx.setPattern(formatPattern);
    return rx.exactMatch(symbol);
}

bool DocumentNumeratorController::isAvailableSymbol(QString symbol)
{
    return model->isAvailableSymbol(documentType, symbol);
}

void DocumentNumeratorController::initAllowedSequences(QString documentType)
{
    allowedSequence.push_back(documentType);
    allowedSequence.push_back("#");
    allowedSequence.push_back("YYYY");
    allowedSequence.push_back("MM");
    allowedSequence.push_back("DD");
    allowedSequence.push_back("/");
    allowedSequence.push_back(" ");

}

bool DocumentNumeratorController::isSameFormat()
{
    QRegExp rx;
    rx.setPattern(formatPattern);
    return rx.exactMatch(previousSymbolStr);
}

void DocumentNumeratorController::initFormatSequences(QString numberingFormat)
{
    SymbolSequence *sequence = new SymbolSequence();

    for(int i = 0; i < allowedSequence.size(); i++)
    {
        if(allowedSequence[i] != "/" && allowedSequence[i] != " ")  // single occurrence
        {
            if(numberingFormat.contains(allowedSequence[i]))
            {
                sequence->setSequence(allowedSequence[i]);
                sequence->setIndex(numberingFormat.indexOf(allowedSequence[i]));
                formatSequences.push_back(*sequence);
            }


        }
        else // multiple occurrence
        {
            searchSequence(numberingFormat, allowedSequence[i]);
        }

    }
    delete sequence;


    sortSequences();

    readUserChars();


}

QString DocumentNumeratorController::getRexExpPattern()
{
    QString pattern = "\\b";

    for(int i = 0; i < formatSequences.size(); i++)
    {
        if(formatSequences[i].getSequence() == QString("#"))
            pattern.append("\\d+");
        else if(formatSequences[i].getSequence() == QString("YYYY"))
            pattern.append("[0-9]{4}");
        else if(formatSequences[i].getSequence() == QString("MM"))
            pattern.append("[0-9]{2}");
        else if(formatSequences[i].getSequence() == QString("DD"))
            pattern.append("[0-9]{2}");
        else
            pattern.append(formatSequences[i].getSequence());
    }
    pattern.append("\\b");

    return pattern;
}

void DocumentNumeratorController::readUserChars()
{
    int charPosition = 0;
    int i = 0;
    do
    {
        if(charPosition == formatSequences[i].getIndex()) // czy znak z dozwolonej sekwencji
        {
            charPosition += formatSequences[i].getSequence().length();

            if(i < formatSequences.size()-1) i++;

        }
        else // znak użytkownika
        {
                QString charSequence = this->numberingFormat.at(charPosition);
                SymbolSequence *sequence = new SymbolSequence();
                sequence->setIndex(charPosition);
                sequence->setSequence(charSequence);

                formatSequences.push_back(*sequence);
                delete sequence;

                charPosition++;
         }



    } while(charPosition < this->numberingFormat.length());

    this->sortSequences();

}

void DocumentNumeratorController::readVariablesFromPrevious()
{
    QString nextChar; // nextChar in numberingFormat
    int nrLenght = 0; // liczba cyfr numeru (#.lenght)
    for(int i = 0; i < formatSequences.size(); i++)
    {
        if(formatSequences[i].getSequence() == "#")
        {
            // dodaj jesli i-1
            QString nrString;
            nextChar = formatSequences[i+1].getSequence().at(0); // pierwszy znak następnego sequence
            int index = formatSequences[i].getIndex();
            do
            {
                nrString.append(previousSymbolStr.at(index));
                nrLenght++;
                index++;
            } while(QString(previousSymbolStr.at(index)) != nextChar && index < 10);

            previousSymbol->setNr(QVariant(nrString).toInt());
            break;
        }

    }

    int charPosition = 0;
    for(int i = 0; i < formatSequences.size(); i++)
    {
        if(formatSequences[i].getSequence() == "#")
        {
            charPosition += nrLenght;
        }
        else if(formatSequences[i].getSequence() == "MM")
        {
            QString tempString = previousSymbolStr.at(charPosition);
            tempString.append(previousSymbolStr.at(++charPosition));

            charPosition++;
            previousSymbol->setMonth(QVariant(tempString).toInt());
        }
        else if(formatSequences[i].getSequence() == "DD")
        {
            QString tempString = previousSymbolStr.at(charPosition);
            tempString.append(previousSymbolStr.at(++charPosition));

            charPosition++;
            previousSymbol->setDay(QVariant(tempString).toInt());
        }
        else if(formatSequences[i].getSequence() == "YYYY")
        {
            QString tempString;
            for(int i = 0; i< 4; i++, charPosition++)
            {
                tempString.append(previousSymbolStr.at(charPosition));
            }

            previousSymbol->setYear(QVariant(tempString).toInt());
        }
        else
        {
            charPosition += formatSequences[i].getSequence().length();
        }


    }
}

QString DocumentNumeratorController::prepareNextSymbol(bool sameFormat)
{
    QString newSymbol = "";

        int tempData = 0;

        for(int i = 0; i < formatSequences.size(); i++)
        {
            if(formatSequences[i].getSequence() == "#")
            {
                if(sameFormat)
                {
                    tempData = this->getNextNr();
                    newSymbol.append(QVariant(tempData).toString());
                }
                else
                {
                   tempData = 1; // nr: 1
                   newSymbol.append(QVariant(tempData).toString());
                }
            }
            else if(formatSequences[i].getSequence() == "MM")
            {
                if(today.month() < 10) newSymbol.append(QVariant(0).toString());
                newSymbol.append(QVariant(today.month()).toString());
            }
            else if(formatSequences[i].getSequence() == "DD")
            {
                if(today.day() < 10) newSymbol.append(QVariant(0).toString());
                newSymbol.append(QVariant(today.day()).toString());
            }
            else if(formatSequences[i].getSequence() == "YYYY")
            {
                newSymbol.append(QVariant(today.year()).toString());
            }
            else
            {
                newSymbol.append(formatSequences[i].getSequence());
            }
        }

        return newSymbol;

}

int DocumentNumeratorController::getNextNr()
{
    int prevNr = previousSymbol->getNr();
    int nextNr;

    if(today.year() != previousSymbol->getYear()) // różne lata
    {
        nextNr = 1;
        return nextNr;
    }
    else // lata się zgadzają
    {
        if(numberingFormat.contains("MM")) // MM, YYYY
        {
            if(today.month() == previousSymbol->getMonth())
            {
                if(numberingFormat.contains("DD")) // DD, MM, YYYY
                {
                    if(today.day() == previousSymbol->getDay())
                    {
                        nextNr = prevNr+1;
                        return nextNr;
                    }
                    else
                    {
                        nextNr = 1;
                        return nextNr;
                    }

                }
                else // MM, YYYY; bez DD
                {
                    nextNr = prevNr+1;
                    return nextNr;
                }
            }
            else
            {
                nextNr = 1;
                return nextNr;
            }

        }
        else // YYYY; bez MM
        {
            if(numberingFormat.contains("DD")) // DD, YYYY; bez MM
            {
                // nieracjonalne numerowanie, ale aplikacja obsłuży
                if(today.day() == previousSymbol->getDay())
                {
                    nextNr = prevNr+1;
                    return nextNr;
                }
                else
                {
                    nextNr = 1;
                    return nextNr;
                }

            }
            else // tylko YYYY
            {
                nextNr = prevNr+1;
                return nextNr;
            }

        }
    }
}

void DocumentNumeratorController::searchSequence(QString numberingFormat, QString substring)
{
    SymbolSequence *sequence = new SymbolSequence();
    for(int i = 0; i < numberingFormat.size(); i++)
    {
        if(numberingFormat.at(i) == substring.at(0))
        {
            sequence->setSequence(QString(substring[0]));
            sequence->setIndex(i);
            formatSequences.push_back(*sequence);
        }

    }
    delete sequence;
}

void DocumentNumeratorController::sortSequences()
{
    SymbolSequence *tempSequence = new SymbolSequence();

    for(int i = 0; i < formatSequences.size(); i++)
    {
        for(int j = 0; j < formatSequences.size() - 1; j++)
        {
            if(formatSequences[j+1].getIndex() < formatSequences[j].getIndex())
            {
                *tempSequence = formatSequences[j];
                formatSequences[j] = formatSequences[j+1];
                formatSequences[j+1] = *tempSequence;
            }
        }
    }
    delete tempSequence;
}
