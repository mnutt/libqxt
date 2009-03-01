#include <QtGui>
#include "displaysettingsdialog.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    DisplaySettingsDialog dialog;
    return dialog.exec();
}
