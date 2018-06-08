#ifndef MYICONPROVIDER_H
#define MYICONPROVIDER_H

#include <QString>
#include <QIcon>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QStringList>
class myiconprovider
{
public:
    myiconprovider();
    QFileIconProvider provider;
    ~myiconprovider();
    QFileInfo fileinfo;
    QStringList icon_List;
public:
    QIcon seticon(QString Path);
};

#endif // MYICONPROVIDER_H
