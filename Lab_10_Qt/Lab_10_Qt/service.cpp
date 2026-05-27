#include "service.h"
#include "masinaRepository.h"
#include "validator.h"
#include "entities.h"
#include "DTO.h"
#include <assert.h>
#include <functional> // pentru std::function
#include <algorithm> // pentru std::sort, copy_n
#include <iterator> // pentru back_inserter
#include <random>
#include <chrono>
#include <fstream>
#include <map>
#include "undo.h"
//#include <gsl/gsl>



void MasinaService::add(const std::string& id, const std::string& nrInmatriculare, const std::string& producator, const std::string& model, const std::string& tip) {

	Masina m{ id, nrInmatriculare, producator, model, tip };
	validator.valideaza(m);
	//repo.add(m);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, m));
	repo.add(std::move(m));

}

void MasinaService::sterge(const std::string& id) {
	const Masina m = repo.cauta(id);

	undoActions.push_back(std::make_unique<UndoSterge>(repo, m));
	repo.sterge(id);


}

void MasinaService::modifica(const std::string& id, const std::string& nrInmatriculare_nou, const std::string& producator_nou, const std::string& model_nou, const std::string& tip_nou) {

	Masina m{ id, nrInmatriculare_nou, producator_nou, model_nou, tip_nou };
	validator.valideaza(m);
	const Masina masinaVeche = repo.cauta(id); // fara copie, pentru ca altfel ar modifica obiectul original
	undoActions.push_back(std::make_unique<UndoModifica>(repo, masinaVeche));
	repo.modifica(id, std::move(m));

}

//const Masina& MasinaService::cauta(const std::string& id, const std::string& nrInmatriculare, const std::string& producator, const std::string& model, const std::string& tip) const {
const Masina& MasinaService::cauta(const std::string& id) {

	return repo.cauta(id);
}

const Masina& MasinaService::cautaNrInmatriculare(const std::string& nrInmatriculare) {
	return repo.cautaNrInmatriculare(nrInmatriculare);
}


std::vector<Masina> MasinaService::filtreaza(const std::function<bool(const Masina&)>& predicat) const {
	std::vector<Masina> rezultat;
	//for (const Masina& m : repo.getAll()) {

		//if (predicat(m)) {
		//	rezultat.push_back(m);
		//}
	//}

	const std::vector<Masina>& toateMasinile = repo.getAll();
	rezultat.reserve(toateMasinile.size()); // pt ca vectorul sa nu se tot redimensioneze

	std::copy_if(toateMasinile.begin(), toateMasinile.end(), back_inserter(rezultat), predicat);
	// back_inserter apeleaza practic rezultat.push_back(element)
	return rezultat;
}

std::vector<Masina> MasinaService::filtreazaGeneral(const std::string criteriu, std::string valoare) const {
	return filtreaza([criteriu, valoare](const Masina& m) {
		if (criteriu == "model") {
			return m.getModel() == valoare;
		}
		if (criteriu == "tip") {
			return m.getTip() == valoare;
		}
		return false;
		});
}

std::vector<Masina> MasinaService::sorteaza(const std::function<bool(const Masina&, const Masina&)>& crescator) const {

	std::vector<Masina> toateMasinile = repo.getAll();

	std::sort(toateMasinile.begin(), toateMasinile.end(), crescator); // sort foloseste std::move() in mod automat
	return toateMasinile;
}

std::vector<Masina> MasinaService::sorteazaGeneral(const std::string criteriu, bool crescator) const {
	return sorteaza([criteriu, crescator](const Masina& m1, const Masina& m2) {
		if (criteriu == "nr") {
			return crescator ? m1.getNrInmatriculare() < m2.getNrInmatriculare()
				: m1.getNrInmatriculare() > m2.getNrInmatriculare();
		}

		if (criteriu == "tip") {
			return crescator ? m1.getTip() < m2.getTip() // !!! "<" si ">" STRICT, NU "<=" sau "=>" !!!
				: m1.getTip() > m2.getTip();
		}

		if (criteriu == "pm") {
			if (m1.getProducator() == m2.getProducator()) {
				return crescator ? m1.getModel() < m2.getModel()
					: m1.getModel() > m2.getModel();
			}
			return crescator ? m1.getProducator() < m2.getProducator()
				: m1.getProducator() > m2.getProducator();
		}
		return false;
		});
}

const std::vector<Masina>& MasinaService::getAll() const noexcept {
	return repo.getAll();
}
///////////////////////////////////
void MasinaService::golesteLista() {
	listaLucru.goleste();
}

void MasinaService::adaugaInLista(const std::string& nrInmatriculare) {
	const Masina& m = cautaNrInmatriculare(nrInmatriculare);
	// nrInmatriculare poate fi si validat
	listaLucru.adauga(m);

}

void MasinaService::genereazaListaAleatorie(int n) {

	auto toateMasinile = repo.getAll();

	//listaLucru.goleste(); // nu e obligatoriu

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(toateMasinile.begin(), toateMasinile.end(), std::default_random_engine(static_cast<unsigned int>(seed)));

	const size_t limita = std::min(size_t(n), toateMasinile.size());
	// in caz ca cerem mai multe masini decat avem

	std::copy_n(toateMasinile.begin(), limita, std::back_inserter(listaLucru));

}

void MasinaService::exportaListaCSV(std::string numeFisier) const {
	// fara & la string, pentru a avea o copie locala, ca sa nu modificam numele de intrare al fisierului
	if (numeFisier.find('.') == std::string::npos) {
		numeFisier += ".csv";
	}

	std::ofstream fout(numeFisier);

	if (!fout.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul " + numeFisier);
	}



	const auto& toate = listaLucru.getAll();

	for (const auto& m : toate) {
		fout << m.getId() << ","
			<< m.getNrInmatriculare() << ","
			<< m.getProducator() << ","
			<< m.getModel() << ","
			<< m.getTip() << "\n";
	}

	fout.close();
}

const std::vector<Masina>& MasinaService::getAllLista() const noexcept {
	return listaLucru.getAll();
}

const std::map<std::string, DTO> MasinaService::frecventaProducator(const std::string& cheie) {

	std::map<std::string, DTO> counter; // care numara
	const std::vector<Masina>& toateMasinile = repo.getAll();
	counter[cheie].setCheie(cheie);
	counter[cheie].setValoare(static_cast<int>(std::count_if(toateMasinile.begin(), toateMasinile.end(), [cheie](const Masina& masina) {
		return masina.getProducator() == cheie;
		})));

	return counter;
}

void MasinaService::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu exista operatie pentru undo\n");
	}

	undoActions.back()->doUndo();
	undoActions.pop_back();
}