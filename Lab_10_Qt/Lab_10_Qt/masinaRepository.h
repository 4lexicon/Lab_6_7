#pragma once
#include "entities.h"
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
/*
* Clasa de exceptii pentru repository
*/
class RepoException {
private:
	std::string msg;
public:
	// Constructor
	RepoException(std::string m) : msg{ m } {

	}

	/*
	* Returneaza mesajul de eroare
	* pre: -
	* post: este returnat mesajul de eroare
	*/
	std::string getMessage() const {
		return msg;
	}
};

class MasinaRepositoryAbstract {
private:
	std::map<int, double> map;
	double probabilitate = 0;

public:
	MasinaRepositoryAbstract() = default;
	MasinaRepositoryAbstract(double chance) : probabilitate{ chance } {}
	virtual void add(Masina masina) = 0;
	virtual void sterge(const std::string& id) = 0;
	virtual void modifica(const std::string& id, Masina masinaNoua) = 0;
	virtual const Masina& cauta(const std::string& id) const = 0;
	virtual const Masina& cautaNrInmatriculare(const std::string& nrInmatriculare) const = 0;
	virtual const std::vector<Masina>& getAll() const = 0;
	virtual ~MasinaRepositoryAbstract() = default;
};

class MasinaRepository : public MasinaRepositoryAbstract {
private:
	std::vector<Masina> masini;

public:

	MasinaRepository(const MasinaRepository& ot) = delete; // pentru a nu mai putea fi copiat
	MasinaRepository() = default; // constructorul default, va fi generat de compilator


	/*
	* Adauga o masina in repository
	* pre: masina valida
	* post: masina este adaugata in repository
	*/
	void add(Masina masina) override;

	/*
	* Sterge o masina din repository
	* pre: id valid
	* post: masina cu id-ul id este stearsa din repository
	*/
	void sterge(const std::string& id) override;

	/*
	* Modifica o masina din repository
	* pre: id, masinaNoua sunt date valide
	* post: masina cu id-ul id este modificata in repository,
	*		fiind inlocuita cu masinaNoua
	*/
	void modifica(const std::string& id, Masina masinaNoua) override;

	/*
	* Cauta o masina in repository
	* pre: id valid
	* post: masina cu id-ul id este returnata din repository
	*/
	const Masina& cauta(const std::string& id) const override;

	/*
	* Cauta o masina in repository, dupa nrInmatriculare
	* pre: nrInmatriculare valid
	* post: masina cu nr de inmatriculare = nrInmatriculare este returnata din repository
	*/
	const Masina& cautaNrInmatriculare(const std::string& nrInmatriculare) const override;

	/*
	* Returneaza toate masinile din repository
	* pre: -
	* post: sunt returnate toate masinile din repository
	*/
	const std::vector<Masina>& getAll() const noexcept override; // primul const face sa poti doar citi ce returneaza vectorul
	// const de la final promite ca functia nu va modifica nimic

// Destructor 
	~MasinaRepository() = default;

};

//void testRepo();

class MasinaRepositoryFile : public MasinaRepository {
private:
	std::string fileName;
	void loadFromFile();
	void writeToFile();

public:
	MasinaRepositoryFile(std::string fileName) : fileName{ fileName } {
		loadFromFile();
	}

	void add(Masina masina) override {
		MasinaRepository::add(masina);
		writeToFile();
	}

	void sterge(const std::string& id) override {
		MasinaRepository::sterge(id);
		writeToFile();
	}

	void modifica(const std::string& id, Masina masinaNoua) override {
		MasinaRepository::modifica(id, masinaNoua);
		writeToFile();
	}

	const Masina& cauta(const std::string& id) const override {
		return MasinaRepository::cauta(id);
	}

	const Masina& cautaNrInmatriculare(const std::string& nrInmatriculare) const override {
		return MasinaRepository::cautaNrInmatriculare(nrInmatriculare);
	}

	const std::vector<Masina>& getAll() const noexcept override {
		return MasinaRepository::getAll();
	}

	~MasinaRepositoryFile() = default;

};

class MasinaRepositoryNou : public MasinaRepositoryAbstract {
private:
	std::map<int, double> probabilitate;

	void verificaProbabilitate() const {
		const int randomNum = rand() % 101; // intre 0 si 100
		if (randomNum <= probabilitate.at(0) * 100) {
			throw RepoException("Eroare abstracta\n");
		}
	}

public:
	MasinaRepositoryNou() = default;
	MasinaRepositoryNou(double chance) {
		probabilitate[0] = chance;
	}
	void add(Masina masina) override {
		(void)masina;
		verificaProbabilitate();
	}

	void sterge(const std::string& id) override {
		(void)id;
		verificaProbabilitate();
	}

	void modifica(const std::string& id, Masina masinaNoua) override {
		(void)id, masinaNoua;
		verificaProbabilitate();
	}

	const Masina& cauta(const std::string& id) const override {
		(void)id;
		verificaProbabilitate();

		throw RepoException("Metoda nu are date in acest Repo Abstract\n");
	}

	const Masina& cautaNrInmatriculare(const std::string& nrInmatriculare) const override {
		(void)nrInmatriculare;
		verificaProbabilitate();

		throw RepoException("Metoda nu are date in acest Repo Abstract\n");
	}
	const std::vector<Masina>& getAll() const override {
		verificaProbabilitate();

		throw RepoException("Metoda nu are date in acest Repo Abstract\n");
	}
	~MasinaRepositoryNou() override = default;
};
