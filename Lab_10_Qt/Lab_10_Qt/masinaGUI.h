#pragma once
#include <QtWidgets/QWidget.h>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/qformlayout.h>

#include <vector>
#include "entities.h"
#include "service.h"

class MasinaGUI : public QWidget{
private:
	MasinaService& ctr;
	QHBoxLayout* lyMain = new QHBoxLayout;
	QHBoxLayout* lyButtons = new QHBoxLayout;
	QHBoxLayout* lyListLineEdit = new QHBoxLayout;
	QVBoxLayout* ly1 = new QVBoxLayout;
	QVBoxLayout* btnDyLy = new QVBoxLayout;

	QListWidget* lst = new QListWidget;
	int nrLinii = 15;
	int nrColoane = 5;
	//QTableWidget* tbl = new QTableWidget{ nrLinii, nrColoane };
	QTableWidget* tbl;


	QPushButton* btnAdd = new QPushButton{"Add"};
	QPushButton* btnSterge = new QPushButton{"Sterge"};
	QPushButton* btnModifica = new QPushButton{"Modifica"};
	QPushButton* btnCauta = new QPushButton{"Cauta"};
	QPushButton* btnCautaNrInmatriculare = new QPushButton{"Cauta nr inmat"};

	QPushButton* btnClose = new QPushButton{"Close"};

	QPushButton* filtreazaModel = new QPushButton{ "Filtreaza model" };
	QPushButton* filtreazaTip  = new QPushButton{"Filtreaza tip"};

	QPushButton* sorteazaNrCrescator = new QPushButton{"Sorteaza Nr Crescator"};
	QPushButton* sorteazaNrDescrescator = new QPushButton{"Sorteaza Nr Desc"};

	QPushButton* sorteazaTipCrescator = new QPushButton{"Sorteaza Tip Crescator"};
	QPushButton* sorteazaTipDescrescator = new QPushButton{"Sorteaza Tip Descrescator"};

	QPushButton* sorteazaPmCrescator = new QPushButton{"Sorteaza Pm Crescator"};
	QPushButton* sorteazaPmDescrescator = new QPushButton{ "Sorteaza Pm Descrescator" };

	QPushButton* btnCos = new QPushButton{ "Cos" };

	QLabel* txtIdLabel = new QLabel{"Id: "};
	QLabel* txtNrInmatriculareLabel = new QLabel{"Nr: "};
	QLabel* txtProducatorLabel = new QLabel{"Producator: "};
	QLabel* txtModelLabel = new QLabel{ "Model: " };
	QLabel* txtTipLabel = new QLabel{ "Tip: " };

	QLineEdit* txtIdLineEdit = new QLineEdit;
	QLineEdit* txtNrInmatriculareLineEdit = new QLineEdit;
	QLineEdit* txtProducatorLineEdit = new QLineEdit;
	QLineEdit* txtModelLineEdit = new QLineEdit;
	QLineEdit* txtTipLineEdit = new QLineEdit;

	QFormLayout* formLy = new QFormLayout;
	

	void initGUICmps();
	void connectSignalSlots();
	void reloadList(const std::vector<Masina>& masini);
	void reloadTable(const std::vector<Masina>& masini);
	void addMasina();
	void stergeMasina();
	void modificaMasina();
	void cautaMasina();
	void cautaNrInmatriculare();
	void adaugaBtnDy(const std::vector<Masina>& masini);
public:

	MasinaGUI(MasinaService& ctr) : ctr{ ctr } {
		initGUICmps();
		connectSignalSlots();
		reloadList(ctr.getAll());
		reloadTable(ctr.getAll());
		adaugaBtnDy(ctr.getAll());
	}



};

