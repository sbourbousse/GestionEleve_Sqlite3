#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void loadDatabase();

    void loadQTableWidget();

    void loadQComboBox();

    void on_pushButtonRemove_clicked();

    void on_pushButtonAdd_clicked();


    void on_pushButtonEdit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
