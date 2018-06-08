#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QString>
#include <myiconprovider.h>
#include <QAction>
#include <QMenuBar>
#include <QStringList>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString path;
    myiconprovider i_provider;
    QStringList histroy_path;
    int i;
private:
    Ui::MainWindow *ui;
    void showinfo();
private slots:
    void showinfo(int , int);
    void showinfo2();
    void showinfo1();
};

#endif // MAINWINDOW_H
