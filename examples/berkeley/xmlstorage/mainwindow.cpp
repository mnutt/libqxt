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
    model.loadXml(QFileDialog::getOpenFileNames (this, "Load Xml file",QString(), "Xml File (*.xml)"));
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}




