#include "dialogeditetudiant.h"
#include "ui_dialogeditetudiant.h"

DialogEditEtudiant::DialogEditEtudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditEtudiant)
{
    ui->setupUi(this);
}

DialogEditEtudiant::~DialogEditEtudiant()
{
    delete ui;
}
