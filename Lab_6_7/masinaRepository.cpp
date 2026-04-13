#include "masinaRepository.h"
#include <assert.h>


void MasinaRepository::add(const Masina& masina) {
	for (const Masina& m : masini) {
		if (m.getId() == masina.getId()) {
			throw RepoException("Masina cu id-ul specificat exista deja\n");
		}
	}
	masini.push_back(masina);
}

void MasinaRepository::sterge(const std::string& id) {
	for (int i = 0; i < masini.size(); i++) {
		if (masini.at(i).getId() == id) {
			masini.erase(masini.begin() + i);
			return;
		}
	}
	throw RepoException("Masina cu ID-ul specificat nu exista\n");
}

void MasinaRepository::modifica(const std::string& id, const Masina& masinaNoua) {
	for (int i = 0; i < masini.size(); i++) {
		if (masini.at(i).getId() == id) {
			masini.at(i) = masinaNoua;
			return;
		}
	}
	throw RepoException("Masina cu ID-ul specificat nu exista\n");
}

const Masina& MasinaRepository::cauta(const Masina& masina) const {
	//for(const Masina& m : masini)
	//	if (//m.getId() == masina.getId() && FARA ID
	//		m.getNrInmatriculare() == masina.getNrInmatriculare() &&
	//		m.getProducator() == masina.getProducator() &&
	//		m.getModel() == masina.getModel() &&
	//		m.getTip() == masina.getTip()
	//		) {
	//		
	//		return m;

	//	}
	//throw (RepoException("Masina specificata nu exista\n"));


	// metoda 2
	auto it = std::find_if(masini.begin(), masini.end(), [&](const Masina& m) {
		return m.getNrInmatriculare() == masina.getNrInmatriculare() &&
			m.getProducator() == masina.getProducator() &&
			m.getModel() == masina.getModel() &&
			m.getTip() == masina.getTip();
		});

	if (it != masini.end()) {
		return *it;
	}

	throw RepoException("Masina specificata nu exista\n");

	//metoda 3
	//const std::vector<Masina>& toate = masini;
	//for (size_t i = 0; i < toate.size(); i++) {
	//	if (//m.getId() == masina.getId() && FARA ID
	//		masini.at(i).getNrInmatriculare() == masina.getNrInmatriculare() &&
	//		masini.at(i).getProducator() == masina.getProducator() &&
	//		masini.at(i).getModel() == masina.getModel() &&
	//		masini.at(i).getTip() == masina.getTip()
	//		) {

	//		return masini.at(i);

	//	}
	//}
	//throw RepoException("Masina specificata nu exista\n");
}

const std::vector<Masina>& MasinaRepository::getAll() const noexcept{ // primul const face sa poti doar citi ce returneaza vectorul
	return masini;					  // const de la final promite ca functia nu va modifica nimic
}


//void testRepo() {
//	MasinaRepository repo;
//	Masina m1{ "1", "CJ01ABC", "Dacia", "Logan", "Sedan" };
//	repo.add(m1);
//	const auto& masini  = repo.getAll();
//	assert(masini.size() == 1);
//	try {
//		repo.add(m1);
//		assert(false);
//	}
//	catch (RepoException&) {
//		assert(true);
//	}
//	
//}