#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QFileIconProvider>
#include <QScrollBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    path = "/";
    ui->setupUi(this);
    histroy_path.insert(0,"/");
    qDebug() << histroy_path.last();
    showinfo();
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showinfo(int,int)));

    QToolBar* pToolBar = ui->mainToolBar;

    QAction* back = new QAction(QIcon(QPixmap(":/icon/left.ico")), QObject::tr("后退"),this);
    QAction* front = new QAction(QIcon(QPixmap(":/icon/right.ico")), QObject::tr("前进"),this);
    //QLineEdit a;
   // QAction* fro = new QAction(QAction(&a));
    pToolBar->addAction(back);
    pToolBar->addAction(front);
    connect(back,SIGNAL(triggered(bool)),this,SLOT(showinfo2()));
    connect(front,SIGNAL(triggered(bool)),this,SLOT(showinfo1()));
    //QObject::connect(pActionC, SIGNAL(triggered(bool)), this, SLOT(onMsg()));

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::showinfo()
{
        QStringList header;
        header<<"Name"<<"Date"<<"Type"<<"Size";
        ui->tableWidget->setColumnCount(4);   //设置列数为5
        // 判断路径是否存在
        //path ="/";
        i=0;
        QDir dir(path);
        if (!dir.exists()) {
           // qDebug() << "目录不存在"<<ui->tableWidget->item(row,1)->text();
            return;
        }
        // 设置过滤器
        dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Dirs);
        dir.setSorting(QDir::DirsFirst);
        QStringList Dir_List;
        Dir_List = dir.entryList();
        if (Dir_List.count() <= 0) {
            qDebug() << "Dir_List的数量为0";
            return;
        }
        QFileInfo fileinfo;
        ui->tableWidget->setRowCount(Dir_List.count()); //设置行数
        QFileIconProvider provider;
        for (int i = 0; i<Dir_List.count(); ++i) {
            fileinfo.setFile(path+Dir_List.at(i));
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(i_provider.seticon(path+Dir_List.at(i)),Dir_List.at(i)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(fileinfo.lastModified().date().toString()));
            ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);

            QString strType = provider.type(path+Dir_List.at(i)); //返回文件的类型

            ui->tableWidget->setItem(i,2,new QTableWidgetItem(strType));
            ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            if(fileinfo.isDir())
            {
                QDir dir;
                dir.setPath(path+Dir_List.at(i));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(dir.count())+"items"));

            }
            else
            {
                if(fileinfo.size()<1048576)
                    ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(fileinfo.size()/(1024),0, 'G',4)+"KB"));//qint64转qstring的方法 QString str = tr("%1").arg(fileinfo.size());
                else
                    ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(fileinfo.size()/(1024.0*1024),0, 'G',4)+"MB"));
            }
            ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        }
        ui->tableWidget->removeRow(1);
        ui->tableWidget->removeRow(0);
        ui->tableWidget->setHorizontalHeaderLabels(header);  //设置表头

        ui->tableWidget->setShowGrid(0);  //显示是否有网格
        ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //不可编辑
        //ui->tableWidget->resizeColumnsToContents();//长度适应内容
        ui->tableWidget->verticalHeader()->setHidden(1);

        ui->tableWidget->setColumnWidth(0,200);
        ui->tableWidget->setColumnWidth(1,200);
        ui->tableWidget->setColumnWidth(2,100);
        ui->tableWidget->setColumnWidth(3,90);
        ui->tableWidget->resize(600,400);
        //设置表头的格式
        ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignRight);
        ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
        ui->tableWidget->setFrameShape(QFrame::NoFrame);//设置无边框
        ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置可多选
        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:white;}"); //设置表头背景色
        ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent;width:10px}"
                                                            "QScrollBar::handle{background:black; border:0px ;solid black; border-radius:5px;}"

////                                                            "QScrollBar::sub-line{background:transparent;}"
                                                            /*"QScrollBar::add-line{background:transparent;}*/);
}
void MainWindow::showinfo(int row,int col)
{
        QStringList header;
        header<<"Name"<<"Date"<<"Type"<<"Size";
        ui->tableWidget->setColumnCount(4);   //设置列数为5
        // 判断路径是否存在
        path = path+ui->tableWidget->item(row,0)->text();
        i++;
        histroy_path.insert(i,path);
        if(i<histroy_path.count()-1)
        {
            while(i!=histroy_path.count()-1)
            histroy_path.removeAt(i+1);
        }
        path = path + "/";
        qDebug() << histroy_path.last();
        QDir dir(path);
        if (!dir.exists()) {
            qDebug() << "目录不存在"<<ui->tableWidget->item(row,1)->text();
            return;
        }
        // 设置过滤器
        dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Dirs);
        dir.setSorting(QDir::DirsFirst);
        QStringList Dir_List;
        Dir_List = dir.entryList();
        if (Dir_List.count() <= 0) {
            qDebug() << "Dir_List的数量为0";
            return;
        }
        QFileInfo fileinfo;
        ui->tableWidget->setRowCount(Dir_List.count()); //设置行数
        QFileIconProvider provider;
        for (int i = 0; i<Dir_List.count(); ++i) {
            fileinfo.setFile(path+Dir_List.at(i));
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(i_provider.seticon(path+Dir_List.at(i)),Dir_List.at(i)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(fileinfo.lastModified().date().toString()));
            ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);

            QString strType = provider.type(path+Dir_List.at(i)); //返回文件的类型

            ui->tableWidget->setItem(i,2,new QTableWidgetItem(strType));
            ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            if(fileinfo.isDir())
            {
                QDir dir;
                dir.setPath(path+Dir_List.at(i));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(dir.count())+"items"));

            }
            else
            {
                if(fileinfo.size()<1048576)
                    ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(fileinfo.size()/(1024),0, 'G',4)+"KB"));//qint64转qstring的方法 QString str = tr("%1").arg(fileinfo.size());
                else
                    ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(fileinfo.size()/(1024.0*1024),0, 'G',4)+"MB"));
            }
            ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        }
        ui->tableWidget->removeRow(1);
        ui->tableWidget->removeRow(0);
//        ui->tableWidget->setHorizontalHeaderLabels(header);  //设置表头

//        ui->tableWidget->setShowGrid(0);  //显示是否有网格
//        ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
//        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //不可编辑
//        //ui->tableWidget->resizeColumnsToContents();//长度适应内容
//        ui->tableWidget->verticalHeader()->setHidden(1);

//        ui->tableWidget->setColumnWidth(0,200);
//        ui->tableWidget->setColumnWidth(1,200);
//        ui->tableWidget->setColumnWidth(2,100);
//        ui->tableWidget->setColumnWidth(3,90);
//        ui->tableWidget->resize(605,400);
        //设置表头的格式
//        ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignRight);
//        ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
        //connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,showinfo(QTableWidgetItem*));
}

void MainWindow::showinfo2()
{
    qDebug() << "here";

    if(i == 0)
        return;
    i--;
        qDebug() << i;
    QStringList header;
    header<<"Name"<<"Date"<<"Type"<<"Size";
    ui->tableWidget->setColumnCount(4);   //设置列数为5
    // 判断路径是否存在
    path = histroy_path.at(i);
    if(path!="/")
        path = path + "/";
    //histroy_path.append(path);
    QDir dir(path);

    // 设置过滤器
    dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Dirs);
    dir.setSorting(QDir::DirsFirst);
    QStringList Dir_List;
    Dir_List = dir.entryList();
    if (Dir_List.count() <= 0) {
        qDebug() << "Dir_List的数量为0";
        return;
    }
    QFileInfo fileinfo;
    ui->tableWidget->setRowCount(Dir_List.count()); //设置行数
    QFileIconProvider provider;
    for (int i = 0; i<Dir_List.count(); ++i) {
        fileinfo.setFile(path+Dir_List.at(i));
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(i_provider.seticon(path+Dir_List.at(i)),Dir_List.at(i)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(fileinfo.lastModified().date().toString()));
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);

        QString strType = provider.type(path+Dir_List.at(i)); //返回文件的类型

        ui->tableWidget->setItem(i,2,new QTableWidgetItem(strType));
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        if(fileinfo.isDir())
        {
            QDir dir;
            dir.setPath(path+Dir_List.at(i));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(dir.count())+"items"));

        }
        else
        {
            if(fileinfo.size()<1048576)
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(fileinfo.size()/(1024),0, 'G',4)+"KB"));//qint64转qstring的方法 QString str = tr("%1").arg(fileinfo.size());
            else
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(fileinfo.size()/(1024.0*1024),0, 'G',4)+"MB"));
        }
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    ui->tableWidget->removeRow(1);
    ui->tableWidget->removeRow(0);
}

void MainWindow::showinfo1()
{
    if(i == histroy_path.count()-1)
        return;
    i++;
    qDebug() << i;
    QStringList header;
    header<<"Name"<<"Date"<<"Type"<<"Size";
    ui->tableWidget->setColumnCount(4);   //设置列数为5
    // 判断路径是否存在
    path = histroy_path.at(i);
    path = path + "/";
    //histroy_path.append(path);
    QDir dir(path);

    // 设置过滤器
    dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Dirs);
    dir.setSorting(QDir::DirsFirst);
    QStringList Dir_List;
    Dir_List = dir.entryList();
    if (Dir_List.count() <= 0) {
        qDebug() << "Dir_List的数量为0";
        return;
    }
    QFileInfo fileinfo;
    ui->tableWidget->setRowCount(Dir_List.count()); //设置行数
    QFileIconProvider provider;
    for (int i = 0; i<Dir_List.count(); ++i) {
        fileinfo.setFile(path+Dir_List.at(i));
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(i_provider.seticon(path+Dir_List.at(i)),Dir_List.at(i)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(fileinfo.lastModified().date().toString()));
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);

        QString strType = provider.type(path+Dir_List.at(i)); //返回文件的类型

        ui->tableWidget->setItem(i,2,new QTableWidgetItem(strType));
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        if(fileinfo.isDir())
        {
            QDir dir;
            dir.setPath(path+Dir_List.at(i));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(dir.count())+"items"));

        }
        else
        {
            if(fileinfo.size()<1048576)
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(fileinfo.size()/(1024),0, 'G',4)+"KB"));//qint64转qstring的方法 QString str = tr("%1").arg(fileinfo.size());
            else
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(fileinfo.size()/(1024.0*1024),0, 'G',4)+"MB"));
        }
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    ui->tableWidget->removeRow(1);
    ui->tableWidget->removeRow(0);
}
