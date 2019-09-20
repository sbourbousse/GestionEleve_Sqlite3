#ifndef DIALOGEDITETUDIANT_H
#define DIALOGEDITETUDIANT_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui {
class DialogEditEtudiant;
}

class DialogEditEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditEtudiant(QWidget *parent = 0, QString idOfEtudiant = 0);
    ~DialogEditEtudiant();

public:
    int rowSelected;

private slots:
    void loadEtudiant();

    void on_pushButtonEdit_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::DialogEditEtudiant *ui;
    QString idToEdit;
};

#endif // DIALOGEDITETUDIANT_H
