#include "mainwindow.h"
#include "tab.h"
#include <QxtConfirmationMessage>
#include <QxtGlobalShortcut>
#include <QxtProgressLabel>
#include <QxtConfigDialog>
#ifndef Q_WS_MAC
#include <QxtWindowSystem>
#endif
#include <QxtApplication>
#include <QProgressBar>
#include <QMessageBox>
#include <QListWidget>
#include <QCloseEvent>
#include <QTreeView>
#include <QDirModel>
#include <QTimer>
#include <QLabel>
#include <QCalendarWidget>
#include <QTimeLine>

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	createProgressBar();
	ui.tabWidget->setTabContextMenuPolicy(Qt::ActionsContextMenu);

	connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionAddTab, SIGNAL(triggered()), this, SLOT(addTab()));
	connect(ui.actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(ui.actionAboutQxtGui, SIGNAL(triggered()), this, SLOT(aboutQxtGui()));
	connect(ui.actionSwitchLayoutDirection, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));
	connect(ui.actionConfigure, SIGNAL(triggered()), this, SLOT(configure()));

    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(toggleVisibility()));
    QKeySequence key("Ctrl+Alt+S");
    if (shortcut->setShortcut(key))
        ui.labelVisibility->setText(ui.labelVisibility->text().arg(key.toString(QKeySequence::NativeText)));
    else
        ui.labelVisibility->hide();

#ifndef Q_WS_MAC
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateIdleTime()));
    timer->start(150);
    updateIdleTime();
#endif
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	static const QString title("QxtConfirmationMessage");
	static const QString text(tr("Are you sure you want to quit?"));
	if (QxtConfirmationMessage::confirm(this, title, text) == QMessageBox::No)
		event->ignore();
}

void MainWindow::aboutQxtGui()
{
	QMessageBox::information(this, tr("About QxtGui"),
		tr("<h3>About QxtGui</h3>"
		"<p>QxtGui is part of Qxt, the Qxt library &lt;"
		"<a href=\"http://libqxt.sf.net\">http://libqxt.sf.net</a>&gt;.</p>"));
}

void MainWindow::addTab()
{
	Tab* tab = new Tab(ui.tabWidget);
	ui.tabWidget->addTab(tab, tr("Tab %1").arg(ui.tabWidget->count() + 1));
	QAction* act = ui.tabWidget->addTabAction(ui.tabWidget->indexOf(tab), tr("Close"), tab, SLOT(close()), tr("Ctrl+W"));
	tab->addAction(act);
	ui.tabWidget->setCurrentWidget(tab);
	connect(tab, SIGNAL(somethingHappened(const QString&)), statusBar(), SLOT(showMessage(const QString&)));
}

void MainWindow::switchLayoutDirection()
{
	qApp->setLayoutDirection(layoutDirection() == Qt::LeftToRight ? Qt::RightToLeft : Qt::LeftToRight);
}

void MainWindow::toggleVisibility()
{
	setVisible(!isVisible());
}

void MainWindow::updateIdleTime()
{
#ifndef Q_WS_MAC
    setWindowTitle(tr("QxtDemo - System Idle: %1ms").arg(QxtWindowSystem::idleTime()));
#endif
}

void MainWindow::createProgressBar()
{
	QxtProgressLabel* label = new QxtProgressLabel(statusBar());

	QProgressBar* bar = new QProgressBar(statusBar());
	bar->setMaximumWidth(label->sizeHint().width() * 2);
	bar->setRange(0, 120);

	QTimeLine* timeLine = new QTimeLine(120000, this);
	timeLine->setFrameRange(0, 120);

	connect(timeLine, SIGNAL(frameChanged(int)), bar, SLOT(setValue(int)));
	connect(timeLine, SIGNAL(finished()), label, SLOT(restart()));
	connect(bar, SIGNAL(valueChanged(int)), label, SLOT(setValue(int)));
	timeLine->start();

    statusBar()->addPermanentWidget(new QLabel(tr("Dummy Progress:"), this));
	statusBar()->addPermanentWidget(bar);
	statusBar()->addPermanentWidget(label);
}

void MainWindow::configure()
{
	QxtConfigDialog dialog(this);
	dialog.setWindowTitle(tr("QxtConfigDialog"));
	QTreeView* page2 = new QTreeView(&dialog);
	page2->setModel(new QDirModel(page2));
	QListWidget* page3 = new QListWidget(&dialog);
	for (int i = 0; i < 100; ++i)
		page3->addItem(QString::number(i));
	dialog.configWidget()->addPage(page2, QIcon(":tree.png"), "A directory tree");
    dialog.configWidget()->addPage(page3, QIcon(":list.png"), "Some kind of list");
	QCalendarWidget* page1 = new QCalendarWidget(&dialog);
    dialog.configWidget()->addPage(page1, QIcon(":calendar.png"), "Calendar");
	dialog.exec();
}
