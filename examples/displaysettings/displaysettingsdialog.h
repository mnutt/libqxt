#ifndef DISPLAYSETTINGSDIALOG_H
#define DISPLAYSETTINGSDIALOG_H

#include <QxtScreen>
#include "ui_displaysettingsdialog.h"

class DisplaySettingsDialog : public QDialog
{
    Q_OBJECT

public:
    DisplaySettingsDialog(QWidget* parent = 0);

private slots:
    void apply();
    void refresh();

    void fillScreens();
    void selectScreen(int screenNumber);
    void fillResolutions();
    void fillRefreshRates();
    void fillColorDepths();

    void updateUi(bool init = false);

private:
    Ui::DisplaySettingsDialog ui;
    QxtScreen screen;
};

#endif // DISPLAYSETTINGSDIALOG_H
