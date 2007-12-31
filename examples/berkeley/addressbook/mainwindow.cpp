#include "mainwindow.h"
#include <QTreeWidgetItem>
#include <QDebug>
MainWindow::MainWindow()
{
    ui.setupUi(this);
    hash.open("contacts.db");
    initTree();
}
void MainWindow::initTree()
{
    ui.treeWidget->clear();
    QxtBdbHashIterator<QString,Contact> it=hash.begin();
    do
    {
        Contact c=it.value();
        QTreeWidgetItem *item=new QTreeWidgetItem(ui.treeWidget);
        item->setText(0,c.name);
        item->setText(1,c.phone);
        item->setText(2,c.address);

    }
    while((++it).isValid());
}


void MainWindow::on_addButton_clicked()
{
    Contact c;
    c.name=ui.inputName->text();
    c.phone=ui.inputPhone->text();
    c.address=ui.inputAddress->text();
    qDebug()<<hash.insert(c.name,c);
    initTree();
}

