#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QMap>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMap<int, std::vector<int> > mapF;
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void cReadLine(QFile*, int);
    void nero();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
