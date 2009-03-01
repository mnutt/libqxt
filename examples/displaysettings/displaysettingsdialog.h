#ifndef DISPLAYSETTINGSDIALOG_H
#define DISPLAYSETTINGSDIALOG_H

#include "ui_displaysettingsdialog.h"

class DisplaySettingsDialog : public QDialog
{
    Q_OBJECT

public:
    DisplaySettingsDialog(QWidget* parent = 0);

private slots:
    void apply();

    void fillResolutions();
    void fillRefreshRates();
    void updateUi(bool init = false);

private:
    Ui::DisplaySettingsDialog ui;
};

#endif // DISPLAYSETTINGSDIALOG_H
