#include "stergereGUI.h"

void StergereGUI::initGUIstergere() {
	setLayout(stergereLy);
	
	formLy->addRow(lbl, le);
	stergereLy->addLayout(formLy);
	stergereLy->addWidget(btnStergere);
}

void StergereGUI::connectSignalSlots() {
	QObject::connect(btnStergere, &QPushButton::clicked, this, &StergereGUI::stergeMasina);

}

void StergereGUI::stergeMasina() {
	try {
		ctr.sterge(le->text().toStdString());
		emit dateSalvate();
		//close(); // necesar?
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
}