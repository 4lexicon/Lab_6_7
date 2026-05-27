#pragma once

#include <service.h>

#include <QtWidgets/QWidget.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>

class StergereGUI : public QWidget {
	Q_OBJECT
private:
	MasinaService& ctr;

	QVBoxLayout* stergereLy = new QVBoxLayout;

	QFormLayout* formLy = new QFormLayout;
	QLabel* lbl = new QLabel;
	QLineEdit* le = new QLineEdit;
	QPushButton* btnStergere = new QPushButton{ "Sterge" };
	

	void initGUIstergere();
	void connectSignalSlots();

	void stergeMasina();
public:
	StergereGUI(MasinaService& ctr) : ctr { ctr } {

		initGUIstergere();
		connectSignalSlots();
	}
signals:
	void dateSalvate();
};