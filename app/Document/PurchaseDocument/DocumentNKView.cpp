#include "DocumentNKView.h"

DocumentNKView::DocumentNKView(QWidget *parent, DocumentNKController* controller)
{
    this->controller = controller;
    this->parent = parent;

    this->mainLayout = new QGridLayout;
    mainLayout->setColumnMinimumWidth(0,140);
    this->setLayout(mainLayout);

    QSize parentSize = parent->size(); //rozmiar okna, ktore wywołało to okno dialogowe, czyli rozmiar okna głównego
    this->setMaximumSize(parentSize); //rozmiar okna dialogowego jest taki jak okna aplikacji
    this->setWindowTitle(trUtf8("Nowy dokument: Nota Korygująca"));

    initLabels();
    initLineEdits();
    initDateEdits();
    initButtons();
    initConnections();
    addAllComponents();
}

void DocumentNKView::initLabels()
{
    labelDocumentSymbol = new QLabel(tr("Symbol dokumentu:"));
    labelDocumentPlace = new QLabel(tr("Miejsce wystawienia:"));
    labelDocumentDate = new QLabel(tr("Data wystawienia:"));

    labelRelatedTo = new QLabel(tr("Dotyczy faktury nr:"));
    labelInvoiceDate = new QLabel(tr("z dn.:"));

    labelReceiver = new QLabel(tr("Odbiorca noty:"));

    labelCorrectedContents = new QLabel(tr("Treść korygowana:"));
    labelCorrectContents = new QLabel(tr("Treść prawidłowa:"));

    labelReceiveName = new QLabel(tr("Dokument odebrał:"));
    labelIssueName = new QLabel(tr("Dokument wystawił:"));
}

void DocumentNKView::initLineEdits()
{
    lineDocumentSymbol = new QLineEdit();
    lineDocumentPlace = new QLineEdit();

    lineRelatedTo = new QLineEdit();

    textReceiver = new QTextEdit();

    textCorrected = new QTextEdit();
    textCorrect = new QTextEdit();

    lineIssueName = new QLineEdit();
    lineReceiveName = new QLineEdit();
}

void DocumentNKView::initDateEdits()
{
    dateEditDocumentDate = new DateEdit(); // issueDate
    dateEditInvoiceDate = new DateEdit(); // invoiceDate

    dateEditDocumentDate->setMinimumWidth(130);

}

void DocumentNKView::initButtons()
{
    buttonSelectReceiver = new Button(ButtonStruct("Wybierz",QSize(100,28)));
    buttonSelectInvoice = new Button(ButtonStruct("Wybierz fakturę",QSize(150,28)));

    buttonBox = new ButtonBox(this);
}

void DocumentNKView::addAllComponents()
{
    mainLayout->setColumnMinimumWidth(4, 150);
    mainLayout->setColumnMinimumWidth(9, 50);

    int col = 0; int row = 0;
    mainLayout->addWidget(labelDocumentSymbol, row, col++);
    this->lineDocumentSymbol->setMinimumWidth(120);
    mainLayout->addWidget(lineDocumentSymbol, row, col++);

    mainLayout->addWidget(labelDocumentPlace, row, col++);
    mainLayout->addWidget(lineDocumentPlace, row, col++);
    this->lineDocumentPlace->setMinimumWidth(120);

    row++; col = 2; // row = 1
    mainLayout->addWidget(labelDocumentDate, row, col++);
    mainLayout->addWidget(dateEditDocumentDate, row, col++);

    row++; col = 0; // row = 2
    mainLayout->addWidget(labelRelatedTo, row, col++);
    mainLayout->addWidget(lineRelatedTo, row, col++);

    mainLayout->addWidget(labelInvoiceDate, row, col++);
    mainLayout->addWidget(dateEditInvoiceDate, row, col++);

    mainLayout->addWidget(buttonSelectInvoice, row, col++);

    int row3, row1 = ++row; col = 0; // row1 = 2
    row3 = row1;
    /* row1 - odbiorca noty = row 3 - tekst korygowany */
    mainLayout->addWidget(labelReceiver, row1, col);
    mainLayout->addWidget(textReceiver, ++row1, col++, 3, 2);
    mainLayout->addWidget(buttonSelectReceiver, row1++, ++col);
    textReceiver->setMaximumHeight(100);

    col = 3;
    mainLayout->addWidget(labelCorrectedContents, row3, col);
    mainLayout->addWidget(textCorrected, ++row3, col++, 3, 3);
    textCorrected->setMaximumWidth(300);
    textCorrected->setMaximumHeight(100);


    col = 3; int row4 = row3+3;
    mainLayout->addWidget(labelCorrectContents, ++row4, col);
    mainLayout->addWidget(textCorrect, ++row4, col++, 3, 3);
    textCorrect->setMaximumWidth(300);
    textCorrect->setMaximumHeight(100);

    int row2 = row4+3;
    ++row2; col = 0;
    mainLayout->addWidget(labelReceiveName, row2, col++);
    mainLayout->addWidget(lineReceiveName, row2, col++, 1, 2);
    this->lineReceiveName->setMaximumWidth(150);

    col++;
    mainLayout->addWidget(labelIssueName, row2, col++);
    mainLayout->addWidget(lineIssueName, row2, col++);

    mainLayout->addWidget(buttonBox, ++row2, 0, 1, 6, Qt::AlignRight);

}

void DocumentNKView::initConnections()
{
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), controller, SLOT(checkChanges()));
    connect(buttonSelectReceiver, SIGNAL(clicked()), controller, SLOT(selectReceiver()));
    connect(buttonSelectInvoice, SIGNAL(clicked()), controller, SLOT(selectInvoice()));
}

void DocumentNKView::setReceiver(Contractor receiver)
{
        QString text;
        text = receiver.getName() + " \n";
        if(receiver.isCompany())
            text.append(receiver.getRepresentative() + "\n");

        text.append(receiver.getAddress() + "\n");
        text.append(receiver.getPostcode() + " " + receiver.getCity() + " \n");
        if(!receiver.getDefultPhone().isEmpty())
            text.append("tel. " + receiver.getDefultPhone() + "\n");
        if(!receiver.getNip().isEmpty())
            text.append("NIP: " + receiver.getNip());

        textReceiver->setText(text);

        textCorrected->setText("");
        textCorrect->setText("");
}

QLineEdit *DocumentNKView::getLineDocumentSymbol() { return lineDocumentSymbol; }
QLineEdit *DocumentNKView::getLineDocumentPlace() { return lineDocumentPlace; }
QLineEdit *DocumentNKView::getLineIssueName() { return lineIssueName; }
QLineEdit *DocumentNKView::getLineReceiveName() { return lineReceiveName; }
QLineEdit *DocumentNKView::getLineRelatedTo() { return lineRelatedTo; }
QTextEdit *DocumentNKView::getTextReceiver() { return textReceiver; }
QTextEdit *DocumentNKView::getTextCorrected() { return textCorrected; }
QTextEdit *DocumentNKView::getTextCorrect() { return textCorrect; }
DateEdit *DocumentNKView::getDateEditDocumentDate() { return dateEditDocumentDate; }
DateEdit *DocumentNKView::getDateEditInvoiceDate() { return dateEditInvoiceDate; }


DocumentNKView::~DocumentNKView()
{
   delete mainLayout;
}
