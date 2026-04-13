#include "ui.h"
#include "service.h"
#include "validator.h"
#include "entities.h"
#include <iostream>
#include <string>
void UI::afiseazaLista(const std::vector<Masina>& masini) {
	if (masini.empty()) {
		std::cout << "Nu exista masini care sa corespunda criteriilor.\n";
		return;
	}
	for (const auto& m : masini) {
		std::cout << "Id: " << m.getId() << " | Nr: " << m.getNrInmatriculare()
				  << " | Producator: " << m.getProducator() << " | Model: " << m.getModel()
				  << " | Tip: " << m.getTip() << "\n";
	}
}


void UI::showUI() {
	while (true) {
		std::cout << "1. Adauga masina\n";
		std::cout << "2. Sterge masina\n";
		std::cout << "3. Modifica masina\n";
		std::cout << "4. Cauta masina\n";
		std::cout << "5. Filtreaza masini (producator sau tip)\n";
		std::cout << "6. Sorteaza masini (dupa nr. inmatriculare, tip, producator + model)\n";
		std::cout << "a. Afiseaza toate masinile\n";
		std::cout << "0. Iesire\n";

		std::string comanda;
		std::cout << "Comanda: ";
		std::cin >> comanda;

		if (comanda == "1") {
			std::cout << "Add\n";
			std::cout << "Id: ";
			std::string id;
			std::cin >> id;

			std::cout << "Nr. Inmatriculare: ";
			std::string nrInmatriculare;
			std::cin >> nrInmatriculare;

			std::cout << "Producator: ";
			std::string producator;
			std::cin >> producator;

			std::cout << "Model: ";
			std::string model;
			std::cin >> model;

			std::cout << "Tip: ";
			std::string tip;
			std::cin >> tip;

			try {
				srv.add(id, nrInmatriculare, producator, model, tip);
				std::cout << "Masina adaugata cu succes!\n";
			}
			

			catch (const ValidatorException& ve) {
				std::cout << ve.getMessage();
			}

			catch (const RepoException& re) {
				std::cout << re.getMessage();
			}

		}
		else if (comanda == "2") {
			std::cout << "Sterge masina cu id-ul: ";
			std::string id;
			std::cin >> id;
			try {
				srv.sterge(id);
				std::cout << "Masina stearsa cu succes!\n";
			}

			catch (const ValidatorException& ve) {
				std::cout << ve.getMessage();
			}

			catch (const RepoException& re) {
				std::cout << re.getMessage();
			}
		}

		else if (comanda == "3") {
			std::cout << "Modifica\n";
			std::cout << "Id: ";
			std::string id;
			std::cin >> id;

			std::cout << "Nr. Inmatriculare NOU: ";
			std::string nrInmatriculare_nou;
			std::cin >> nrInmatriculare_nou;

			std::cout << "Producator NOU: ";
			std::string producator_nou;
			std::cin >> producator_nou;

			std::cout << "Model NOU: ";
			std::string model_nou;
			std::cin >> model_nou;

			std::cout << "Tip NOU: ";
			std::string tip_nou;
			std::cin >> tip_nou;

			try {
				srv.modifica(id, nrInmatriculare_nou, producator_nou, model_nou, tip_nou);
				std::cout << "Masina modificata cu succes!\n";
			}

			catch (const ValidatorException& ve) {
				std::cout << ve.getMessage();
			}

			catch (const RepoException& e) {
				std::cout << e.getMessage();
			}

		}

		else if (comanda == "4") {
			std::cout << "Cauta masina\n";

			//std::cout << "Id: ";
			std::string id = "garbageValue";
			//std::cin >> id;

			std::cout << "Nr. Inmatriculare: ";
			std::string nrInmatriculare;
			std::cin >> nrInmatriculare;

			std::cout << "Producator: ";
			std::string producator;
			std::cin >> producator;

			std::cout << "Model: ";
			std::string model;
			std::cin >> model;

			std::cout << "Tip: ";
			std::string tip;
			std::cin >> tip;

			try {
				const Masina m = srv.cauta(Masina(id, nrInmatriculare, producator, model, tip));
				std::cout << "Masina gasita!\n";
				std::cout << "Id: " << m.getId() << " | " << "Nr. inmatriculare: " << m.getNrInmatriculare() << " | " << "Producator: " << m.getProducator() << " | " << "Model: " << m.getModel() << " | " << "Tip: " << m.getTip() << " | " << "\n";
			}
			catch (const RepoException& re) {
				std::cout << re.getMessage();
			}
		}

		else if (comanda == "5") {
			std::string criteriu, valoare;
			std::cout << "Filtreaza dupa (model/tip): ";
			std::cin >> criteriu;
			std::cout << "Valoarea cautata: ";
			std::cin >> valoare;

			afiseazaLista(srv.filtreazaGeneral(criteriu, valoare));
		}

		else if (comanda == "6") {
			std::string criteriu, mod;
			std::cout << "Sorteaza dupa (nr/tip/pm): ";
			std::cin >> criteriu;
			std::cout << "Crescator(c) sau Descrescator(d): ";
			std::cin >> mod;

			bool crescator;
			if (mod == "c")
				crescator = true;
			else if (mod == "d")
				crescator = false;
			else {
				std::cout << "Trebuie sa fie crecsator(c) sau descrescator(d)\n";
				continue;
			}
			
			afiseazaLista(srv.sorteazaGeneral(criteriu, crescator));

			
		}

		else if (comanda == "a") {
			afiseazaLista(srv.getAll());

		}
		else if (comanda == "0") {
			break;
		}
		else {
			std::cout << "\nHuh? " << "\"" << comanda << "\"? " << "N-am auzit de comanda aceea.\n\n";
		}
	}
}
