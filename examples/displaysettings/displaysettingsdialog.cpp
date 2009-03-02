#include "displaysettingsdialog.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QEventLoop>
#include <QTimer>

static int greatestCommonDivisor(int a, int b)
{
    if (b == 0)
        return a;
    return greatestCommonDivisor(b, a % b);
}

DisplaySettingsDialog::DisplaySettingsDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this);
    ui.letterBoxWidget->setMargin(20);
    ui.letterBoxWidget->setWidget(ui.labelBox);
    ui.letterBoxWidget->setBackgroundColor(QColor("wheat"));
    connect(ui.buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), SLOT(apply()));

    fillScreens();
    selectScreen(qApp->desktop()->primaryScreen());
    fillRefreshRates();

    connect(ui.comboBoxScreen, SIGNAL(currentIndexChanged(int)), SLOT(selectScreen(int)));
    connect(ui.comboBoxReso, SIGNAL(currentIndexChanged(int)), SLOT(fillRefreshRates()));

    updateUi(true);
    connect(ui.comboBoxScreen, SIGNAL(currentIndexChanged(int)), SLOT(updateUi()));
    connect(ui.comboBoxReso, SIGNAL(currentIndexChanged(int)), SLOT(updateUi()));
    connect(ui.comboBoxRate, SIGNAL(currentIndexChanged(int)), SLOT(updateUi()));
}

void DisplaySettingsDialog::apply()
{
    int resoIndex = ui.comboBoxReso->currentIndex();
    if (resoIndex != -1)
    {
        const QSize reso = ui.comboBoxReso->itemData(resoIndex).toSize();
        screen.setResolution(reso);
    }

    int rateIndex = ui.comboBoxRate->currentIndex();
    if (rateIndex != -1)
    {
        const int rate = ui.comboBoxRate->itemData(rateIndex).toInt();
        screen.setRefreshRate(rate);
    }

    screen.apply();

    QMessageBox messageBox(this);
    messageBox.setWindowTitle(windowTitle());
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setText(tr("Your desktop has been reconfigured. Do you want to keep these settings?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    messageBox.setWindowModality(Qt::WindowModal);
    messageBox.show();

    QEventLoop eventLoop;
    connect(messageBox.button(QMessageBox::Yes), SIGNAL(clicked()), &eventLoop, SLOT(quit()));
    connect(messageBox.button(QMessageBox::No), SIGNAL(clicked()), &eventLoop, SLOT(quit()));
    for (int i = 15; i > 0; --i)
    {
        messageBox.setInformativeText(tr("Reverting in %1 seconds").arg(i));
        QTimer::singleShot(1000, &eventLoop, SLOT(quit()));
        eventLoop.exec();

        if (messageBox.clickedButton())
            break;
    }

    if (messageBox.clickedButton() == messageBox.button(QMessageBox::Yes))
        ui.buttonBox->button(QDialogButtonBox::Apply)->setDisabled(true);
    else
        screen.cancel();
}

void DisplaySettingsDialog::fillScreens()
{
    ui.comboBoxScreen->clear();
    int numScreens = qApp->desktop()->numScreens();
    for (int i = 0; i < numScreens; ++i)
        ui.comboBoxScreen->addItem(tr("Screen %1").arg(i));
}

void DisplaySettingsDialog::selectScreen(int screenNumber)
{
    screen.setScreenNumber(screenNumber);
    fillResolutions();
}

void DisplaySettingsDialog::fillResolutions()
{
    ui.comboBoxReso->clear();
    const QList<QSize> resos = screen.availableResolutions();
    foreach (const QSize& reso, resos)
    {
        QSize ratio = reso / greatestCommonDivisor(reso.width(), reso.height());
        QString text = tr("%1 x %2 (%3:%4)")
        .arg(reso.width()).arg(reso.height())
        .arg(ratio.width()).arg(ratio.height());
        ui.comboBoxReso->addItem(text, reso);
    }

    const QSize reso = screen.resolution();
    ui.comboBoxReso->setCurrentIndex(resos.indexOf(reso));
}

void DisplaySettingsDialog::fillRefreshRates()
{
    const int resoIndex = ui.comboBoxReso->currentIndex();
    if (resoIndex != -1)
    {
        const QSize reso = ui.comboBoxReso->itemData(resoIndex).toSize();

        ui.comboBoxRate->clear();
        const QList<int> rates = screen.availableRefreshRates(reso);
        foreach (int rate, rates)
        {
            QString text = tr("%1 Hz").arg(rate);
            ui.comboBoxRate->addItem(text, rate);
        }
    }
}

void DisplaySettingsDialog::updateUi(bool init)
{
    if (init)
    {
        const QSize reso = screen.resolution();
        const QList<QSize> resos = screen.availableResolutions();
        ui.comboBoxReso->setCurrentIndex(resos.indexOf(reso));

        const int rate = screen.refreshRate();
        const QList<int> rates = screen.availableRefreshRates(reso);
        ui.comboBoxRate->setCurrentIndex(rates.indexOf(rate));
    }

    const int resoIndex = ui.comboBoxReso->currentIndex();
    const QSize reso = ui.comboBoxReso->itemData(resoIndex).toSize();
    QSize ratio = reso / greatestCommonDivisor(reso.width(), reso.height());

    QString text = tr("%1 x %2 (%3:%4)")
        .arg(reso.width()).arg(reso.height())
        .arg(ratio.width()).arg(ratio.height());

    ui.labelBox->setText(text);
    ui.labelBox->setSizeIncrement(reso);
    ui.letterBoxWidget->resizeWidget();

    ui.buttonBox->button(QDialogButtonBox::Apply)->setEnabled(!init);
}
