#include "mainwindow.h"
#include <QTreeWidgetItem>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow()
{
    ui.setupUi(this);
    model.open("xml.db");
    ui.treeView->setModel(&model);
}

void MainWindow::on_actionLoad_triggered()
{
    QString f=QFileDialog::getOpenFileName (this, "Load Xml file",QString(), "Xml File (*.xml)");
    QFile file(f);
    file.open(QIODevice::ReadOnly);
    model.loadXml(&file);
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}




