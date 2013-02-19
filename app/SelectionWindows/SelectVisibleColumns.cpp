#include "SelectVisibleColumns.h"

SelectVisibleColumns::SelectVisibleColumns(QTableView *table, QWidget *parent) : QDialog(parent)
{
    this->table = table;
    this->setLayout(layout = new QGridLayout());
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    this->setMinimumSize(400, 100);
    this->setWindowTitle("Wybierz, które kolumny mają być widoczne");

    initView();
    initConnections();
}

void SelectVisibleColumns::initView()
{
    groupBox = new QGroupBox();
    checkBoxesGroup = new QButtonGroup();
    checkBoxesGroup->setExclusive(false);

    QCheckBox *checkBox;
    for(int i = 0; i < table->model()->columnCount(); i++)
    {
        QString text = table->model()->headerData(i, Qt::Horizontal).toString();

        checkBox = new QCheckBox(text);
        checkBoxesGroup->addButton(checkBox, i);



    }

    QGridLayout *layout = new QGridLayout();
    checkBoxList = (QList<QAbstractButton*>) checkBoxesGroup->buttons();


    // add checkbox to layout
    int numberOfButtonColumns = 4;
    int buttonsPerColumn = qCeil(QVariant(checkBoxList.size()).toDouble()/numberOfButtonColumns);

    for(int i = 0, noCheckboxInRow = 0, row = 0, column = 0; i < checkBoxList.size(); i++) {
        if(noCheckboxInRow == buttonsPerColumn) {
            column++;
            row = 0;
            noCheckboxInRow = 0;
        }
        else if(!ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses) && checkBoxList.at(i)->text() == "Ilość")
        {
        }
        else if(noCheckboxInRow != 0)
            row++;

        if(!ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses) && checkBoxList.at(i)->text() == "Ilość")
        {
            // nie dodawaj checkobxa ilość
        }
        else if(checkBoxList.at(i)->text() == "id")
        {
            // nie dodawaj id
        }
        else
        {

            layout->addWidget(checkBoxList.at(i), row, column);
            noCheckboxInRow++;
        }
    }

    groupBox->setLayout(layout);
    this->layout->addWidget(groupBox, 0, 0);

    buttonBox = new ButtonBox(this);
    this->layout->addWidget(buttonBox, 1, 0, Qt::AlignRight);

}



bool SelectVisibleColumns::isNextColumn(int nrModuloButtuonsInColumn) {
    if(nrModuloButtuonsInColumn == 1 && isTableWithIdColumn())
        return true;
    else if(nrModuloButtuonsInColumn == 0 && !isTableWithIdColumn())
        return true;
    else
        return false;
}

bool SelectVisibleColumns::isTableWithIdColumn()
{
    for(int i = 0; i < table->model()->columnCount(); i++) {
        if(table->model()->headerData(i, Qt::Horizontal).toString() == "id")
            return true;
    }
    return false;
}

void SelectVisibleColumns::initConnections() {
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(buttonSave()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QList<int> SelectVisibleColumns::getSelectedColumns()
{
    QList<int> selectedColumns;
    for(int i = 0; i < checkBoxList.size(); i++)
    {
        if(checkBoxList.at(i)->isChecked())
            selectedColumns.push_back(i);
    }
    return selectedColumns;
}

void SelectVisibleColumns::buttonSave()
{
    emit this->selectedColumnsChanged(getSelectedColumns());
    this->close();
}

void SelectVisibleColumns::exec() {

    for(int i = 0; i < checkBoxList.size(); i++) {

        if(table->isColumnHidden(i))
            checkBoxList.at(i)->setChecked(false);
        else
            checkBoxList.at(i)->setChecked(true);

    }
    QDialog::exec();
}





