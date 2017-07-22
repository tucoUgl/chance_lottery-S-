#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <numeric>

using std::vector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("23.txt");
    if(file.open(QIODevice::ReadOnly)){
        qDebug() << "Ошибка открытия для чтения";
    }

    QByteArray nBlocksize;
    while(!file.atEnd()){
        file.readLine();

        int s = 2;
        QString strn;
        while(s){
            nBlocksize = file.readLine();
            strn = nBlocksize;
            strn.truncate(strn.size() -1);
            if(strn.toInt()) s = 0;
            else s--;
        }


        vector<int> vs;
        for(int i = 0 ; i < 6; i++){
            QByteArray byts = file.readLine();
            QString str(byts);
            str.truncate(str.size() - 2);
            vs.push_back(str.toInt());            
        }
        mapF.insert(strn.toInt(), vs);
        file.readLine();
        file.readLine();
    }
    mapF.remove(0);
    ui->tableWidget_4->setSortingEnabled(true);
    ui->tableWidget_4->setShowGrid(true);
    ui->tableWidget_4->setColumnCount(8);
    ui->tableWidget_4->hideColumn(0);
    ui->tableWidget_4->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_4->setHorizontalHeaderItem(1, new QTableWidgetItem("Games"));
    for(int i = 0 ; i < mapF.size(); i++){
        ui->tableWidget_4->insertRow(i);
        int key = mapF.keys().at(i);
        vector<int> vc = mapF.value(key);
        ui->tableWidget_4->setItem(i, 1, new QTableWidgetItem(QString::number(key)));
        for(int j = 0 ; j < 6; j++){
            ui->tableWidget_4->setItem(i, 2 + j, new QTableWidgetItem(QString::number(vc.at(j))));
        }
    }
    nero();

}

void MainWindow::nero(){
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    vector<int> vc(46);

    for(int i = 0 ; i < mapF.size(); i++){
        int key = mapF.keys().at(i);
        vector<int> maPe = mapF.value(key);
        for(int j = 0 ; j < 6; j++){
            vc.at(maPe.at(j))++;
        }
    }
    vc.erase(vc.begin());

    int sum = std::accumulate(vc.begin(), vc.end(), 0);


    for(int i = 0 ; i < vc.size(); i++){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number((double)vc.at(i))));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number((double)vc.at(i) / sum)));

    }
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("number"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Количество выпадений"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Вероятность"));

}

void MainWindow::cReadLine(QFile * file, int count){
//    for(int i  = 0 ; i < count; i++)
//        file.readLine();
}

MainWindow::~MainWindow()
{
    delete ui;
}
