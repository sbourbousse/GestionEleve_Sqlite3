#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    float currentVersion = 1.3;

    //Relative database file information
    auto nomFichier = "database.db";
    auto BDDPath = a.applicationDirPath()+"/";
    auto pathFichier = BDDPath+nomFichier;

    //My file
    QFile monFichierBDD(pathFichier); // myApp/database.db

    qDebug()<<pathFichier;

    //Case my file doesn exists
    if (!monFichierBDD.exists())
    {

        qDebug()<<"Le fichier n'existe pas";

        //Create database
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(pathFichier);
        db.open();

        /*
         * PROGRAMMING DATABASE
         */
        QSqlQuery createParametre("create table Parametre("
                                  "version float)");
        QSqlQuery createOption("create table Option("
                               "optionId smallint primary auto_increment key,"
                               "optionLibelle varchar(64))");
        QSqlQuery createEtudiant("create table Etudiant("
                                 "etudiantId int primary key,"
                                 "etudiantPrenom varchar(64),"
                                 "etudiantNom varchar(64),"
                                 "optionId smallint,"
                                 "FOREIGN KEY(optionId) REFERENCES Option(optionId))");

        QSqlQuery insertParametre("insert into Parametre values ("+QString::number(currentVersion)+")");
        QSqlQuery insertOption("insert into Option values (1,\"SLAM\"),"
                               "(2,\"SISR\"),"
                               "(3,\"SLAM ET SISR\")");


    }
    else
    {

        qDebug()<<"Le fichier existe";

        //Open File
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(pathFichier);
        db.open();

        //Query that gets the actual version
        QSqlQuery verifVersion("select version from Parametre");
        verifVersion.first();

        qDebug()<<"Version de la bdd = "<<verifVersion.value(0).toString()+" | Version de l'app = "+QString::number(currentVersion);

        /*
         * COMPARE THE APP VERSION TO USERS DATABASE VERSIONS
         */
        if(verifVersion.value(0).toFloat()==currentVersion)
        {
            //USER HAS ACTUAL VERSION
            qDebug()<<"you have ACTUAL VERSION";

        }
        else if (verifVersion.value(0).toFloat()<currentVersion)
        {
            //USER HAS OLD VERSION
            qDebug()<<"you have OLD VERSION";


            //Create the new table
            QSqlQuery createOption("create table Option("
                                   "optionId smallint auto_increment primary key,"
                                   "optionLibelle varchar(64))");

            //Rename old Etudiant
            QSqlQuery renameEtudiant("ALTER TABLE Etudiant RENAME TO EtudiantOld");

            //Create the new Etudiant
            QSqlQuery createEtudiant("create table Etudiant("
                                     "etudiantId int primary key,"
                                     "etudiantPrenom varchar(64),"
                                     "etudiantNom varchar(64),"
                                     "etudiantOption varchar(64)"
                                     "optionId smallint,"
                                     "FOREIGN KEY(optionId) REFERENCES Option(optionId))");

            //Copy data from old to new
            QSqlQuery copyDataEtudiant("INSERT INTO Etudiant(etudiantId,etudiantPrenom,etudiantNom,etudiantOption)"
                                       " SELECT etudiantId,etudiantPrenom,etudiantNom,etudiantOption FROM EtudiantOld");

            /*//Add column optionId
            QSqlQuery alterEtudiantAddOptionId("ALTER TABLE Etudiant ADD optionId smallint");
            //Add foreign key to this column (referes to table Option)
            QSqlQuery alterEtudiantOptionForeignKey("ALTER TABLE Option ADD CONSTRAINT fk_child_parent "
                                                    "FOREIGN KEY (parent_id) "
                                                    "REFERENCES parent(id);"); // not work*/

            //All different Options
            QSqlQuery queryAllOption("select distinct etudiantOption from Etudiant");

            while(queryAllOption.next())
            {
                //insert this new option in table Option
                QSqlQuery addOptionOption("insert into Option (optionLibelle) values (\""+queryAllOption.value(0).toString()+"\")");

                //Gets all Etudiant wich has this Option
                QSqlQuery queryAllEtudiantHasOption("select etudiantId from Etudiant where etudiantOption=\""+queryAllOption.value(0).toString()+"\"");
                //While each Etudiant has this Option
                while (queryAllEtudiantHasOption.next())
                {
                    //Give him the optionId
                    QSqlQuery updateOptionEtudiant("update Etudiant set optionId="+queryAllOption.value(0).toString()+" "
                                                   "where etudiantId="+queryAllEtudiantHasOption.value(0).toString());
                }
            }
            //QSqlQuery alterEtudiantDeleteOption("ALTER TABLE Etudiant DROP COLUMN etudiantOption"); need to copy data create new table and load

        }
        else
        {
            //USER HAS EARLIER VERSION
            qDebug()<<"you have EARLIER VERSION";

        }

    }


    MainWindow w;
    w.show();
    return a.exec();
}
