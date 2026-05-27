#include "masinaGUI.h"
#include "stergereGUI.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <map>

void MasinaGUI::initGUICmps() {
	tbl = new QTableWidget{ 15,5 };
	tbl->setHorizontalHeaderLabels(QStringList({ "Id", "Nr", "Producator", "Model", "Tip"}));
	setLayout(lyMain);


	QWidget* buttons = new QWidget;
	buttons->setLayout(lyButtons);
	lyButtons->addWidget(btnAdd);
	lyButtons->addWidget(btnSterge);
	lyButtons->addWidget(btnModifica);
	lyButtons->addWidget(btnCauta);
	lyButtons->addWidget(btnCautaNrInmatriculare);
	/////////////////////////////
	lyButtons->addWidget(btnCos);
	/////////////////////////////
	lyButtons->addWidget(btnClose);

	formLy->addRow(txtIdLabel, txtIdLineEdit);
	formLy->addRow(txtNrInmatriculareLabel, txtNrInmatriculareLineEdit);
	formLy->addRow(txtProducatorLabel, txtProducatorLineEdit);
	formLy->addRow(txtModelLabel, txtModelLineEdit);
	formLy->addRow(txtTipLabel, txtTipLineEdit);
	


	QWidget* listLine = new QWidget;
	listLine->setLayout(lyListLineEdit);
	lyListLineEdit->addWidget(lst);
	lyListLineEdit->addWidget(tbl);
	lyListLineEdit->addLayout(formLy);


	QWidget* window1 = new QWidget;
	window1->setLayout(ly1);
	ly1->addWidget(listLine);
	ly1->addWidget(buttons);

	QWidget* widFiltrareSortare = new QWidget;
	QVBoxLayout* lyVert = new QVBoxLayout;
	//widFiltrareSortare->setLayout(lyVert);

	lyVert->addWidget(filtreazaModel);
	lyVert->addWidget(filtreazaTip);
	lyVert->addWidget(sorteazaNrCrescator);
	lyVert->addWidget(sorteazaNrDescrescator);		 
	lyVert->addWidget(sorteazaTipCrescator);
	lyVert->addWidget(sorteazaTipDescrescator);
	lyVert->addWidget(sorteazaPmCrescator);
	lyVert->addWidget(sorteazaPmDescrescator);


	widFiltrareSortare->setLayout(lyVert);

	QWidget* btnDy = new QWidget;
	btnDy->setLayout(btnDyLy);

	lyMain->addWidget(window1);
	lyMain->addWidget(widFiltrareSortare);
	lyMain->addWidget(btnDy);
	//setLayout(lyMain);
}

void MasinaGUI::reloadList(const std::vector<Masina>& masini) {
	lst->clear();
	for (const auto& m : masini) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(m.getProducator()));
		item->setData(Qt::UserRole, QString::fromStdString(m.getId()));
		if (m.getProducator() == "Dacia") {
			item->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
		}
		lst->addItem(item);
	}
	reloadTable(masini);
}

void MasinaGUI::reloadTable(const std::vector<Masina>& masini) {
	tbl->clearContents();
	tbl->setRowCount(masini.size());
	int i = 0;
	for (const auto& m : masini) {
		QTableWidgetItem* itemId = new QTableWidgetItem(QString::fromStdString(m.getId()));
		QTableWidgetItem* itemNrInmatriculare= new QTableWidgetItem(QString::fromStdString(m.getNrInmatriculare()));
		QTableWidgetItem* itemProducator = new QTableWidgetItem(QString::fromStdString(m.getProducator()));
		QTableWidgetItem* itemModel = new QTableWidgetItem(QString::fromStdString(m.getModel()));
		QTableWidgetItem* itemTip = new QTableWidgetItem(QString::fromStdString(m.getTip()));
		//item->setData(Qt::UserRole, QString::fromStdString(m.getId()));
		
		tbl->setItem(i, 0, itemId);
		tbl->setItem(i, 1, itemNrInmatriculare);
		tbl->setItem(i, 2, itemProducator);
		tbl->setItem(i, 3, itemModel);
		tbl->setItem(i, 4, itemTip);
		if (m.getProducator() == "Dacia") {
			itemId->setBackground(Qt::red);
			itemNrInmatriculare->setBackground(Qt::red);
			itemProducator->setBackground(Qt::red);
			itemModel->setBackground(Qt::red);
			itemTip->setBackground(Qt::red);
		}
		i++;
	}
}

void MasinaGUI::adaugaBtnDy(const std::vector<Masina>& masini) {
	std::map<std::string, int> counter; //care numara

	for (const auto& m : masini) {
		counter[m.getProducator()]++;
	}

	for (const auto& producator : counter) {
		auto btn = new QPushButton{ QString::fromStdString(producator.first) };
		btnDyLy->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [producator, this, btn]() { // !!! prin VALOARE, altfel, vom avea date reziduale !!!
			QMessageBox::information(nullptr, "Info", QString::number(producator.second));
			//delete btn;
			});
	}

}

void MasinaGUI::connectSignalSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &MasinaGUI::addMasina);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &MasinaGUI::stergeMasina);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &MasinaGUI::modificaMasina);
	QObject::connect(btnCauta, &QPushButton::clicked, this, &MasinaGUI::cautaMasina);
	QObject::connect(btnCautaNrInmatriculare, &QPushButton::clicked, this, &MasinaGUI::cautaNrInmatriculare);

	QObject::connect(filtreazaModel, &QPushButton::clicked, [&]() {
		reloadList(ctr.filtreazaGeneral("model", txtModelLineEdit->text().toStdString()));
		});

	QObject::connect(filtreazaTip, &QPushButton::clicked, [&]() {
		reloadList(ctr.filtreazaGeneral("tip", txtTipLineEdit->text().toStdString()));
		});

	QObject::connect(sorteazaNrCrescator, &QPushButton::clicked, [&]() {
		reloadList(ctr.sorteazaGeneral("nr", 1));
		});

	QObject::connect(sorteazaNrDescrescator, &QPushButton::clicked, [&]() {
		reloadList(ctr.sorteazaGeneral("nr", 0));
		});

	QObject::connect(sorteazaTipCrescator, &QPushButton::clicked, [&]() {
		reloadList(ctr.sorteazaGeneral("tip", 1));
		});

	QObject::connect(sorteazaTipDescrescator, &QPushButton::clicked, [&]() {
		reloadList(ctr.sorteazaGeneral("tip", 0));
		});

	QObject::connect(sorteazaPmCrescator, &QPushButton::clicked, [&]() {
		reloadList(ctr.sorteazaGeneral("pm", 1));
		});

	QObject::connect(sorteazaPmDescrescator, &QPushButton::clicked, [&]() {
		reloadList(ctr.sorteazaGeneral("pm", 0));
		});

	QObject::connect(btnClose, &QPushButton::clicked, [&]() {
		close();
		});

	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			txtIdLineEdit->setText("");
			txtNrInmatriculareLineEdit->setText("");
			txtProducatorLineEdit->setText("");
			txtModelLineEdit->setText("");
			txtTipLineEdit->setText("");
		}
		else {
		
			auto selItem = sel.at(0);
			auto id = selItem->data(Qt::UserRole).toString();
			const Masina& m = ctr.cauta(id.toStdString());
			txtIdLineEdit->setText(QString::fromStdString(m.getId()));
			txtNrInmatriculareLineEdit->setText(QString::fromStdString(m.getNrInmatriculare()));
			txtProducatorLineEdit->setText(QString::fromStdString(m.getProducator()));
			txtModelLineEdit->setText(QString::fromStdString(m.getModel()));
			txtTipLineEdit->setText(QString::fromStdString(m.getTip()));
		}
		});
	
}

void MasinaGUI::addMasina() {
	try {
		ctr.add(txtIdLineEdit->text().toStdString(),
			txtNrInmatriculareLineEdit->text().toStdString(),
			txtProducatorLineEdit->text().toStdString(),
			txtModelLineEdit->text().toStdString(),
			txtTipLineEdit->text().toStdString());
		reloadList(ctr.getAll());
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
	catch (ValidatorException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMessage()));
	}
}

void MasinaGUI::stergeMasina() {
	
	try {
		StergereGUI* stergere = new StergereGUI{ ctr };
		stergere->setAttribute(Qt::WA_DeleteOnClose);
		QObject::connect(stergere, &StergereGUI::dateSalvate, [&]() {
			reloadList(ctr.getAll());
			});
		stergere->show();
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
	

	//try {
	//	ctr.sterge(txtIdLineEdit->text().toStdString());
	//	reloadList(ctr.getAll());
	//}
	//catch (RepoException& re) {
	//	QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	//}
}

void MasinaGUI::modificaMasina() {
	try {
		ctr.modifica(txtIdLineEdit->text().toStdString(),
			txtNrInmatriculareLineEdit->text().toStdString(),
			txtProducatorLineEdit->text().toStdString(),
			txtModelLineEdit->text().toStdString(),
			txtTipLineEdit->text().toStdString());
		reloadList(ctr.getAll());
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
}

void MasinaGUI::cautaMasina() {
	try {
		const Masina& m = ctr.cauta(txtIdLineEdit->text().toStdString());
		std::vector<Masina> masiniHelper;
		masiniHelper.push_back(m);
		reloadList(masiniHelper);
	}

	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
}

void MasinaGUI::cautaNrInmatriculare() {
	try {
		const Masina& m = ctr.cautaNrInmatriculare(txtNrInmatriculareLineEdit->text().toStdString());
		std::vector<Masina> masiniHelper;
		masiniHelper.push_back(m);
		reloadList(masiniHelper);
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
}