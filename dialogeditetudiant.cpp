#include "dialogeditetudiant.h"
#include "ui_dialogeditetudiant.h"
#include <QSqlQuery>
#include <QDebug>

DialogEditEtudiant::DialogEditEtudiant(QWidget *parent, QString idOfEtudiant) :
    QDialog(parent),
    ui(new Ui::DialogEditEtudiant)
{
    ui->setupUi(this);
    idToEdit=idOfEtudiant;
    loadEtudiant();
}

DialogEditEtudiant::~DialogEditEtudiant()
{
    delete ui;
}


void DialogEditEtudiant::loadEtudiant()
{
    //Get information about the Etudiant to edit
    QSqlQuery myQuery("select etudiantPrenom,etudiantNom,optionId from Etudiant where etudiantId="+idToEdit);
    //Select the first row
    myQuery.first();
    //Put informations in the line edits
    ui->lineEditPrenom->setText(myQuery.value(0).toString());
    ui->lineEditNom->setText(myQuery.value(1).toString());
    int optionId = myQuery.value(2).toInt();

    //Combo box option
    QSqlQuery myComboBoxQuery("select optionId,optionLibelle from Option");
    int i = 0;
    while(myComboBoxQuery.next())
    {
        ui->comboBoxOption->addItem(myComboBoxQuery.value(1).toString(),myComboBoxQuery.value(0).toInt());
        if (optionId==myComboBoxQuery.value(0).toInt())
            ui->comboBoxOption->setCurrentIndex(i);
        i++;

    }
}

void DialogEditEtudiant::on_pushButtonEdit_clicked()
{
    QString firstName = ui->lineEditPrenom->text();
    QString lastName = ui->lineEditNom->text();
    QString id = ui->comboBoxOption->currentData().toString();
    QString optionLib = ui->comboBoxOption->currentText();

    auto itemfirstName = w->getUI()->tableWidgetEtudiant->item(rowSelected, 1);
    auto itemlastName = w->getUI()->tableWidgetEtudiant->item(rowSelected, 2);
    auto itemId = w->getUI()->tableWidgetEtudiant->item(rowSelected, 0);
    auto itemOptionLib = w->getUI()->tableWidgetEtudiant->item(rowSelected,3);

    itemfirstName->setText(firstName);
    itemlastName->setText(lastName);
    itemId->setText(id);
    itemOptionLib->setText(optionLib);

    if(firstName.length()==0 || lastName.length()==0)
        ui->labelErrorMessage->setText("Un ou plusieurs champs ne sont pas remplis");
    else
    {
        QSqlQuery myQuery("update Etudiant set etudiantPrenom=\""+firstName+"\" ,etudiantNom=\""+lastName+"\", optionId="+id+" where etudiantId="+idToEdit);
        qDebug()<<"update Etudiant set etudiantPrenom=\""+firstName+"\" ,etudiantNom=\""+lastName+"\", optionId="+id+" where etudiantId="+idToEdit;
        close();
    }
}

void DialogEditEtudiant::on_pushButtonCancel_clicked()
{
    close();
}
