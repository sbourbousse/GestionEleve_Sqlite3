#ifndef DIALOGEDITETUDIANT_H
#define DIALOGEDITETUDIANT_H

#include <QDialog>

namespace Ui {
class DialogEditEtudiant;
}

class DialogEditEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditEtudiant(QWidget *parent = 0, QString id = "0");
    ~DialogEditEtudiant();


private slots:

    void loadEtudiant();

    void loadComboBox();

    void on_pushButtonEdit_clicked();

    void on_pushButtonCancel_clicked();

private:
    QString myId;

    Ui::DialogEditEtudiant *ui;
};

#endif // DIALOGEDITETUDIANT_H
