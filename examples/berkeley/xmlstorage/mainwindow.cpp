#include "mainwindow.h"
#include <QTreeWidgetItem>
#include <QDebug>
#include <QFileDialog>
#include "xml2bdb.h"

MainWindow::MainWindow()
{
    ui.setupUi(this);
    tree.open("xml.db");
    initTree();
}

void MainWindow::initTree()
{
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


        item->setText(0,c.name);
        item->setText(2,c.value);

        switch(c.type)
        {
            case QXmlStreamReader::NoToken:
                item->setText(1,"NoToken");
                break;
            case QXmlStreamReader::Invalid:
                item->setText(1,"Invalid");
                break;
            case QXmlStreamReader::StartDocument:
                item->setText(1,"StartDocument");
                break;
            case QXmlStreamReader::EndDocument:
                item->setText(1,"EndDocument");
                break;
            case QXmlStreamReader::StartElement:
                item->setText(1,"StartElement");
                break;
            case QXmlStreamReader::EndElement:
                item->setText(1,"EndElement");
                break;
            case QXmlStreamReader::Characters:
                item->setText(1,"Characters");
                break;
            case QXmlStreamReader::Comment:
                item->setText(1,"Comment");
                break;
            case QXmlStreamReader::DTD:
                item->setText(1,"DTD");
                break;
            case QXmlStreamReader::EntityReference:
                item->setText(1,"EntityReference");
                break;
            case QXmlStreamReader::ProcessingInstruction:
                item->setText(1,"ProcessingInstruction");
                break;
        };


        

        QxtBdbTreeIterator<XmlNode> it2=it.child();
        if(it2.isValid())
            readTree(it2,item);

        ++it;
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QString f=QFileDialog::getOpenFileName ( this, "Load Xml file",QString(), "Xml File (*.xml)" );
    QFile file(f);
    file.open(QIODevice::ReadOnly);
    Xml2Bdb x;
    x.setDevice(&file);
    tree.clear();
    x.read(tree.root());
    tree.dumpTree();
    initTree();
}


void MainWindow::on_actionQuit_triggered()
{
    close();
}




