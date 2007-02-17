#include "ui_test.h"
#include <QDialog>

class Test : public QDialog

{
	Q_OBJECT

	public:
        	Test(QWidget *parent = 0):QDialog(parent)
			{
			ui.setupUi(this);
			}


	private:
        	Ui::Test ui;
};

