#include "myiconprovider.h"
#include <QFileIconProvider>
#include <QString>
myiconprovider::myiconprovider()
{

}

myiconprovider::~myiconprovider()
{

}

QIcon myiconprovider::seticon(QString Path)
{


    fileinfo.setFile(Path);
    //qDebug() << fileinfo.suffix();

    QDir dir(":/icon");
    if (!dir.exists()) {
        qDebug() << "目录不存在";
    }


    icon_List = dir.entryList();
    if (icon_List.count() <= 0) {
        qDebug() << "Dir_List的数量为0";
    }
    if(fileinfo.isDir())
    {
        QIcon icon(":/icon/dir.png");
        return icon;

    }
    else if(fileinfo.suffix()!="")
    {
        for (int i = 0; i<icon_List.count(); ++i)
        {
            if(icon_List.at(i) == "." ||icon_List.at(i) == "..")
                continue;

            if((QString(icon_List.at(i))).contains(fileinfo.suffix(), Qt::CaseSensitive))
            {
                QIcon icon(":/icon/"+icon_List.at(i));
                return icon;
            }

        }
        QIcon icon(":/icon/file.png");
        return icon;
    }
    else
    {

            QIcon icon(":/icon/file.png");
            return icon;

    }

}

