#include "dialogeditetudiant.h"
#include "ui_dialogeditetudiant.h"
#include <QSqlQuery>
#include <QDebug>
#include "mainwindow.h"

DialogEditEtudiant::DialogEditEtudiant(QWidget *parent, QString id) :
    QDialog(parent),
    ui(new Ui::DialogEditEtudiant)
{
    ui->setupUi(this);
    myId=id;
    loadComboBox();
    loadEtudiant();

}

DialogEditEtudiant::~DialogEditEtudiant()
{
    delete ui;
}

void DialogEditEtudiant::loadEtudiant()
{
    QSqlQuery myRequest("select etudiantPrenom,etudiantNom,optionId from Etudiant where etudiantId="+myId);

    myRequest.first();

    ui->lineEditNom->setText(myRequest.value(1).toString());
    ui->lineEditPrenom->setText(myRequest.value(0).toString());
    ui->comboBoxOption->setCurrentIndex(ui->comboBoxOption->findData(myRequest.value(2)));
}

void DialogEditEtudiant::loadComboBox()
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

void DialogEditEtudiant::on_pushButtonEdit_clicked()
{
    QString firstName = ui->lineEditPrenom->text();
    QString lastName = ui->lineEditNom->text();
    QString optionId = ui->comboBoxOption->currentData().toString();

    QSqlQuery myRequest("update Etudiant set etudiantPrenom=\""+firstName+"\", etudiantNom=\""+lastName+"\", optionId="+optionId+" where etudiantId="+myId);
    qDebug()<<"update Etudiant set etudiantPrenom=\""<<firstName<<"\", etudiantNom=\""<<lastName<<"\", optionId="<<optionId<<" where etudiantId="<<myId;


    ((MainWindow*)parent())->loadQTableWidget();

    close();

}

void DialogEditEtudiant::on_pushButtonCancel_clicked()
{
    close();
}
