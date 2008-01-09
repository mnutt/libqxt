#include "mainwindow.h"
#include <QTreeWidgetItem>
#include <QDebug>
MainWindow::MainWindow()
{
    ui.setupUi(this);
    tree.open("contacts.db");
    initTree();
}

void MainWindow::initTree()
{

    XmlNode n1;
    n1.name="n1";
    n1.value="fish";
    n1.type=8;

    XmlNode n2;
    n2.name="n2";
    n2.value="boom";
    n2.type=8;


    XmlNode n3;
    n3.name="n3";
    n3.value="voom";
    n3.type=8;

    tree.clear();


    qDebug()<<tree.root().append(n1).value().name;
    qDebug()<<tree.root().append(n2).append(n3).value().name;
    qDebug()<<tree.root().append(n1).append(n2).append(n3).append(n2).value().name;


    tree.dumpTree();





    ui.treeWidget->clear();
    QxtBdbTreeIterator<XmlNode> it=tree.root().child();
    readTree(it,0);
}

void MainWindow::readTree(QxtBdbTreeIterator<XmlNode> it,QTreeWidgetItem * itema)
{
    while(it.isValid())
    {
        XmlNode c=it.value();
        QTreeWidgetItem *item;
        if(itema)
            item=new QTreeWidgetItem(itema);
        else
            item=new QTreeWidgetItem(ui.treeWidget);


        item->setText(0,"<"+c.name+">"+c.value+"</"+c.name+">");

        QxtBdbTreeIterator<XmlNode> it2=it.child();
        if(it2.isValid())
            readTree(it2,item);

        ++it;
    }
}







