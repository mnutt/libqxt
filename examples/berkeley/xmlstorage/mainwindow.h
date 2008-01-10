#include "ui_mainwindow.h"
#include "node.h"
#include <QxtBdbTree>

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow();
private:
    Ui::MainWindow ui;
    QxtBdbTree<XmlNode>  tree;
    void initTree();
    void readTree (QxtBdbTreeIterator<XmlNode> it,QTreeWidgetItem * item);

private slots:
    void on_actionQuit_triggered();
    void on_actionLoad_triggered();

};

