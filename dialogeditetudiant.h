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
    explicit DialogEditEtudiant(QWidget *parent = 0);
    ~DialogEditEtudiant();

private:
    Ui::DialogEditEtudiant *ui;
};

#endif // DIALOGEDITETUDIANT_H
