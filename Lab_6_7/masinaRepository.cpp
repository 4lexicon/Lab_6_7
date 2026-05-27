	#include "masinaRepository.h"
	#include <assert.h>
	#include <algorithm>
	#include <fstream>

	void MasinaRepository::add(Masina masina) {



		//const auto it = std::find_if(masini.begin(), masini.end(), [&](const Masina& m) {return m.getId() == masina.getId(); });
		//if (it != masini.end()) {
		//	throw RepoException("Masina cu id-ul specificat exista deja\n");
		//}

		for (const Masina& m : masini) {
			if (m.getId() == masina.getId()) {
				throw RepoException("Masina cu id-ul specificat exista deja\n");
			}
		}

		masini.push_back(std::move(masina));
		//masini.push_back(masina);
		//masini.emplace_back(masina.getId(), ... etc. // si asa merge
	}

	void MasinaRepository::sterge(const std::string& id) {
	
		auto it = find_if(masini.begin(), masini.end(), [id](const Masina& m) {return m.getId() == id; });
	
		if (it == masini.end()) {
			throw RepoException("Masina cu ID-ul specificat nu exista\n");
		}

		masini.erase(it);
	}

	void MasinaRepository::modifica(const std::string& id, Masina masinaNoua) {
		bool gasit = false;
	

		for (Masina& m : masini) {
			if (m.getId() == id) {
				m = std::move(masinaNoua);
				gasit = true;
				break;
			}
		}
		if (!gasit) {
			throw RepoException("Masina cu ID-ul specificat nu exista\n");
		}
	}

	const Masina& MasinaRepository::cauta(const std::string& id) const {
	
		auto it = std::find_if(masini.begin(), masini.end(), [&](const Masina& m) {
			return m.getId() == id;
			});

	

		if (it == masini.end()) {	
			throw RepoException("Masina specificata nu exista\n");	
		}		
		// Asa e mai bine
		return *it;

	}

	const Masina& MasinaRepository::cautaNrInmatriculare(const std::string& nrInmatriculare) const {
		auto it = std::find_if(masini.begin(), masini.end(), [&](const Masina& m) {
			return m.getNrInmatriculare() == nrInmatriculare;
			});



		if (it == masini.end()) {
			throw RepoException("Masina specificata nu exista\n");
		}
		// Asa e mai bine
		return *it;
	}


	const std::vector<Masina>& MasinaRepository::getAll() const noexcept{ // primul const face sa poti doar citi ce returneaza vectorul
		return masini;					  // const de la final promite ca functia nu va modifica nimic
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void MasinaRepositoryFile::loadFromFile() {
		std::ifstream fin(fileName);
		if (!fin.is_open()) {
			throw RepoException("Error open: " + fileName);
		}

		while (!fin.eof()) {
			std::string id;
			fin >> id;
		
			if (fin.eof()) { // poate am linii goale
				break;
			}

			std::string nrInmatriculare;
			fin >> nrInmatriculare;;
			std::string producator;
			fin >> producator;
			std::string model;
			fin >> model;
			std::string tip;
			fin >> tip;

			Masina m{ id, nrInmatriculare, producator, model, tip };
			//Masina m{ id.c_str(), nrInmatriculare.c_str(), producator.c_str(), model.c_str(), tip.c_str() }; 
			// sau asa
		
			MasinaRepository::add(std::move(m)); // !!! din clasa de baza !!!
												 // altfel, intram intr-un ciclu infinit
		}
		fin.close();
	}

	void MasinaRepositoryFile::writeToFile() {
		std::ofstream fout(fileName);
		if (!fout.is_open()) {
			std::string msg("Error opening file: " + fileName);
			throw RepoException(msg);
		}

		for (auto& m : getAll()) { // endl in loc de "," in exemplul profului
			fout << m.getId() << " "
				<< m.getNrInmatriculare() << " "
				<< m.getProducator() << " "
				<< m.getModel() << " "
				<< m.getTip() << "\n";
		}
		fout.close();

	}