#include "service.h"
#include "masinaRepository.h"
#include "validator.h"
#include "entities.h"
#include <assert.h>
#include <functional> // pentru std::function
#include <algorithm> // pentru std::sort
//#include <gsl/gsl>



void MasinaService::add(const std::string& id, const std::string& nrInmatriculare, const std::string& producator, const std::string& model, const std::string& tip) {
	Masina m{ id, nrInmatriculare, producator, model, tip };

	validator.valideaza(m);
	repo.add(m);
	

	
}

void MasinaService::sterge(const std::string& id) {

	repo.sterge(id);
	

}

void MasinaService::modifica(std::string id, std::string nrInmatriculare_nou, std::string producator_nou, std::string model_nou, std::string tip_nou) {

	Masina m = Masina(id, nrInmatriculare_nou, producator_nou, model_nou, tip_nou);
	validator.valideaza(m);
	repo.modifica(id, m);

}

//const Masina& MasinaService::cauta(const std::string& id, const std::string& nrInmatriculare, const std::string& producator, const std::string& model, const std::string& tip) const {
const Masina& MasinaService::cauta(const Masina& m){
	

	return repo.cauta(m);
}

std::vector<Masina> MasinaService::filtreaza(const std::function<bool(const Masina&)>& predicat) const{
	std::vector<Masina> rezultat;
	for (const Masina& m : repo.getAll()) {
		if (predicat(m)) {
			rezultat.push_back(m);
		}
	}
	return rezultat;
}

std::vector<Masina> MasinaService::filtreazaGeneral(const std::string criteriu, std::string valoare) const{
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

std::vector<Masina> MasinaService::sorteaza(const std::function<bool(const Masina&, const Masina&)>& crescator) const{
	
	std::vector<Masina> toateMasinile = repo.getAll();

	std::sort(toateMasinile.begin(), toateMasinile.end(), crescator);
	return toateMasinile;
}

std::vector<Masina> MasinaService::sorteazaGeneral(const std::string criteriu, bool crescator) const{
	return sorteaza([criteriu, crescator](const Masina& m1, const Masina& m2) {
		if (criteriu == "nr") {
			return crescator ? m1.getNrInmatriculare() < m2.getNrInmatriculare()
				: m1.getNrInmatriculare() > m2.getNrInmatriculare();
		}

		if (criteriu == "tip") {
			return crescator ? m1.getTip() < m2.getTip()
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

const std::vector<Masina>& MasinaService::getAll() const noexcept{
	return repo.getAll();
}

//void testAdd() {
//	MasinaRepository repo;
//	MasinaValidator validator;
//	MasinaService srv{ validator, repo };
//	srv.add("1", "CJ01ABC", "Dacia", "Logan", "Sedan");
//	const auto& masini = srv.getAll();
//	assert(masini.size() == 1);
//
//}