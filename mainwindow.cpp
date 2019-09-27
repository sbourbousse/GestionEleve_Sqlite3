#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "dialogeditetudiant.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadDatabase();
    loadQTableWidget();
    loadQComboBox();
}

void MainWindow::loadDatabase()
{
    /*
     * OPENING SQLITE DATABASE
     */

}

void MainWindow::loadQTableWidget()
{
    ui->tableWidgetEtudiant->setRowCount(0);

    //Select query
    QSqlQuery tableQuery("select etudiantId,etudiantPrenom, etudiantNom ,optionLibelle from Etudiant natural join Option");

    int numberOfColumns = 4 ; //3 columns : etudiantPrenom, etudiantNom, optionLibelle

    ui->tableWidgetEtudiant->setColumnCount(numberOfColumns);

    int rowCount=0;

    //Adding rows to my TableWidget
    while(tableQuery.next())
    {
        //Adding a row
        ui->tableWidgetEtudiant->insertRow(rowCount);

        //Adding items to my row
        for(int i = 0 ; i<=numberOfColumns ; i++)
        {
            //Creates a new item for my row
            QTableWidgetItem *myTableItem = new QTableWidgetItem;

            //Puts text in my row
            myTableItem->setText(tableQuery.value(i).toString());

            //Insert the Item in the right spot
            ui->tableWidgetEtudiant->setItem(rowCount,i,myTableItem);
        }
        rowCount++;
    }

    //Hide the id column
    ui->tableWidgetEtudiant->hideColumn(0);

    QStringList mesEntetes= {"Id","Prenom","Nom","Option"};
    ui->tableWidgetEtudiant->setHorizontalHeaderLabels(mesEntetes);
    ui->tableWidgetEtudiant->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetEtudiant->verticalHeader()->setVisible(false);

}

void MainWindow::loadQComboBox()
{
    //Select query
    QSqlQuery comboBoxQuery("select optionId,optionLibelle from Option");

    //Adding row to my combo box
    while(comboBoxQuery.next())
    {
        //Adding Items to my row with id as data
        ui->comboBoxOption->addItem(comboBoxQuery.value(1).toString(),comboBoxQuery.value(0).toInt());
    }

}

void MainWindow::on_pushButtonRemove_clicked()
{
    if(ui->tableWidgetEtudiant->currentRow()==-1)
        QMessageBox::warning(this,"Aucune ligne selectionné","Selectionnez un etudiant à modifer");
    else
    {

        QList<QTableWidgetItem*> itemSelected = ui->tableWidgetEtudiant->selectedItems();

        //Get every row by counting 3 by 3
        for(int rowCount = 0 ; rowCount<itemSelected.size() ; rowCount+=3)
        {
            QString idToDelete = ui->tableWidgetEtudiant->item(itemSelected[rowCount]->row(),0)->text(); //0 is the id column

            //Delete query

            QSqlQuery deleteQuery("delete from Etudiant where etudiantId="+idToDelete);

        }

        //Reset the tableWidget to load changes
        ui->tableWidgetEtudiant->setRowCount(0);

        loadQTableWidget();
     }
}

void MainWindow::on_pushButtonAdd_clicked()
{
    //Gets max id
    QSqlQuery queryEtudiantUniqueId("select max(etudiantId) from Etudiant");
    queryEtudiantUniqueId.first(); //Read the first row
    int calculateId = queryEtudiantUniqueId.value(0).toInt()+1; //Unique Identifier will be the max id + 1

    //Variable

    QString id = QString::number(calculateId);
    QString firstName = ui->lineEditFirstName->text();
    QString lastName = ui->lineEditLastName->text();
    QString optionId = ui->comboBoxOption->itemData(ui->comboBoxOption->currentIndex()).toString();

    //If there are empty inputs
    if(firstName.length()==0 || lastName.length()==0)
    //Gives an error message on the bottom of the MainWindow
    ui->labelErrorMessage->setText("Impossible d'ajouter un etudiant sans prenom et/ou sans nom");
    else
    {
       //Adding Etudiant in table Etudiant
       QSqlQuery addQuery("insert into Etudiant values ("+id+",\""+firstName+"\",\""+lastName+"\","+optionId+")");
       //qDebug()<<"insert into Etudiant values ("+id+",\""+firstName+"\",\""+lastName+"\","+optionId+")";

       //Reset the tableWidget to load changes
       ui->tableWidgetEtudiant->setRowCount(0);

       ui->lineEditFirstName->setText("");
       ui->lineEditLastName->setText("");
       ui->comboBoxOption->setCurrentIndex(0);

       loadQTableWidget();
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonEdit_clicked()
{
    if(ui->tableWidgetEtudiant->currentRow()==-1)
        QMessageBox::warning(this,"Aucune ligne selectionné","Selectionnez un etudiant à modifer");
    else
    {
        QString myId = ui->tableWidgetEtudiant->item(ui->tableWidgetEtudiant->currentRow(),0)->text();

        DialogEditEtudiant *editDialog = new DialogEditEtudiant(this,myId);
        editDialog->show();
    }
}
