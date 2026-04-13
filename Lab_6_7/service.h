#pragma once
#include <vector>
#include <string>
#include <functional>
#include "entities.h"
#include "validator.h"
#include "masinaRepository.h"

class MasinaService {
	
private:
	MasinaValidator& validator;
	MasinaRepository& repo;
	

public:
	MasinaService(MasinaValidator& validator, MasinaRepository& repo) noexcept : validator{validator}, repo{repo} {}

	MasinaService(const MasinaService& ot) = delete;
	MasinaService() = default;

	void add(const std::string& id, const std::string& nrInmatriculare, const std::string& producator, const std::string& model, const std::string& tip);
	void sterge(const std::string& id);
	void modifica(std::string id, std::string nrInmatriculare_nou, std::string producator_nou, std::string model_nou, std::string tip_nou);
	//const Masina& cauta(const std::string& id, const std::string& nrInmatriculare, const std::string& producator, const std::string& model, const std::string& tip) const;
	const Masina& cauta(const Masina& m);
	std::vector<Masina> filtreaza(const std::function<bool(const Masina&)>& predicat) const;
	std::vector<Masina> filtreazaGeneral(const std::string criteriu, std::string valoare) const;
	std::vector<Masina> sorteaza(const std::function<bool(const Masina&, const Masina&)>& crescator) const;
	std::vector<Masina> sorteazaGeneral(std::string criteriu, bool crescator) const;
	const std::vector<Masina>& getAll() const noexcept;
};

//void testAdd();

