#include "displaysettingsdialog.h"
#include <QxtScreenUtil>
#include <QPushButton>

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

    fillResolutions();
    fillRefreshRates();
    connect(ui.comboBoxReso, SIGNAL(currentIndexChanged(int)), SLOT(fillRefreshRates()));

    updateUi(true);
    connect(ui.comboBoxReso, SIGNAL(currentIndexChanged(int)), SLOT(updateUi()));
    connect(ui.comboBoxRate, SIGNAL(currentIndexChanged(int)), SLOT(updateUi()));
}

void DisplaySettingsDialog::apply()
{
    QxtScreenUtil util;

    int resoIndex = ui.comboBoxReso->currentIndex();
    if (resoIndex != -1)
    {
        const QSize reso = ui.comboBoxReso->itemData(resoIndex).toSize();
        util.setResolution(reso);
    }

    int rateIndex = ui.comboBoxRate->currentIndex();
    if (rateIndex != -1)
    {
        const int rate = ui.comboBoxRate->itemData(rateIndex).toInt();
        util.setRefreshRate(rate);
    }

    ui.buttonBox->button(QDialogButtonBox::Apply)->setDisabled(true);
    util.apply();
}

void DisplaySettingsDialog::fillResolutions()
{
    QxtScreenUtil util;

    ui.comboBoxReso->clear();
    const QList<QSize> resos = util.availableResolutions();
    foreach (const QSize& reso, resos)
    {
        QSize ratio = reso / greatestCommonDivisor(reso.width(), reso.height());
        QString text = tr("%1 x %2 (%3:%4)")
        .arg(reso.width()).arg(reso.height())
        .arg(ratio.width()).arg(ratio.height());
        ui.comboBoxReso->addItem(text, reso);
    }

    const QSize reso = util.resolution();
    ui.comboBoxReso->setCurrentIndex(resos.indexOf(reso));
}

void DisplaySettingsDialog::fillRefreshRates()
{
    QxtScreenUtil util;

    const int resoIndex = ui.comboBoxReso->currentIndex();
    if (resoIndex != -1)
    {
        const QSize reso = ui.comboBoxReso->itemData(resoIndex).toSize();

        ui.comboBoxRate->clear();
        const QList<int> rates = util.availableRefreshRates(reso);
        foreach (int rate, rates)
        {
            QString text = tr("%1 Hz").arg(rate);
            ui.comboBoxRate->addItem(text, rate);
        }
    }
}

void DisplaySettingsDialog::updateUi(bool init)
{
    QxtScreenUtil util;

    if (init)
    {
        const QSize reso = util.resolution();
        const QList<QSize> resos = util.availableResolutions();
        ui.comboBoxReso->setCurrentIndex(resos.indexOf(reso));

        const int rate = util.refreshRate();
        const QList<int> rates = util.availableRefreshRates(reso);
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
