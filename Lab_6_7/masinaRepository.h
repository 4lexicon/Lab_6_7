#pragma once
#include "entities.h"
#include <vector>
#include <string>
class RepoException {
private:
	std::string msg;
public:
	RepoException(std::string m) : msg{ m } {

	}

	std::string getMessage() const {
		return msg;
	}
};

class MasinaRepository {
	private:
		std::vector<Masina> masini;

	public:

		MasinaRepository(const MasinaRepository& ot) = delete; // pentru a nu mai putea fi copiat
		MasinaRepository() = default; // constructorul default, va fi generat de compilator

		void add(const Masina& masina);
		void sterge(const std::string& id);
		void modifica(const std::string& id, const Masina& masinaNoua);
		const Masina& cauta(const Masina& masina) const;

		const std::vector<Masina>& getAll() const noexcept; // primul const face sa poti doar citi ce returneaza vectorul
											       // const de la final promite ca functia nu va modifica nimic

		~MasinaRepository() = default;

};

//void testRepo();
