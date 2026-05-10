#pragma once
#include <vector>
#include <string>
#include <functional>
#include "entities.h"
#include "validator.h"
#include "masinaRepository.h"
#include "ListaLucru.h"
#include "DTO.h"
#include "undo.h"

class MasinaService {
	
private:
	MasinaValidator& validator;
	MasinaRepositoryAbstract& repo;
	ListaLucru& listaLucru;
	std::vector<std::unique_ptr<ActiuneUndo>> undoActions;

public:
	MasinaService(MasinaValidator& validator, MasinaRepositoryAbstract& repo, ListaLucru& listaLucru) noexcept : validator{ validator }, repo{ repo }, listaLucru{ listaLucru } {}

	MasinaService(const MasinaService& ot) = delete;
	MasinaService() = default;

	/*
	* Adauga o masina in repository
	* pre: id, nrInmatriculare, producator, model, tip sunt date valide
	* post: masina cu id-ul id este adaugata in repository
	*/
	void add(const std::string& id, const std::string& nrInmatriculare, const std::string& producator, const std::string& model, const std::string& tip);
	
	/*
	* Sterge o masina din repository
	* pre: id valid
	* post: masina cu id-ul id este stearsa din repository
	*/
	void sterge(const std::string& id);

	/*
	* Modifica o masina din repository
	* pre: id, masinaNoua sunt date valide
	* post: masina cu id-ul id este modificata in repository,
	*		fiind inlocuita cu masinaNoua
	*/
	void modifica(const std::string& id, const std::string& nrInmatriculare_nou, const std::string& producator_nou, const std::string& model_nou, const std::string& tip_nou);
	//const Masina& cauta(const std::string& id, const std::string& nrInmatriculare, const std::string& producator, const std::string& model, const std::string& tip) const;
	
	/*
	* Cauta o masina in repository
	* pre: id valid
	* post: masina cu id-ul id este returnata din repository
	*/
	const Masina& cauta(const std::string& id);
	
	/*
	* Cauta o masina in repository, dupa nrInmatriculare
	* pre: nrInmatriculare valid
	* post: masina cu nr de inmatriculare = nrInmatriculare este returnata din repository
	*/
	const Masina& cautaNrInmatriculare(const std::string& nrInmatriculare);
	
	/*
	* Filtreaza masinile din repository, dupa un predicat dat
	* pre: predicat valid
	* post: masinile care corespund predicatului sunt returnate intr-un vector
	*/
	std::vector<Masina> filtreaza(const std::function<bool(const Masina&)>& predicat) const;
	
	/*
	* Functie generica de filtrare, care primeste ca parametru un criteriu de filtrare (nr, producator, model, tip) si o valoare pentru filtrare
	* pre: criteriu, valoare sunt date valide
	* post: masinile care corespund criteriului de filtrare sunt returnate intr-un vector
	*/
	std::vector<Masina> filtreazaGeneral(const std::string criteriu, std::string valoare) const;
	
	/*
	* Sorteaza masinile din repository, dupa un predicat dat
	* pre: crescator valid
	* post: masinile sunt ordonate dupa predicat si returnate intr-un vector
	*/
	std::vector<Masina> sorteaza(const std::function<bool(const Masina&, const Masina&)>& crescator) const;
	
	/*
	* Functie generica de filtrare, care primeste ca parametru un criteriu de filtrare (nr, producator, model, tip) si o valoare pentru filtrare
	* pre: criteriu, crescator date valide
	* post: masinile sunt ordonate dupa predicat si returnate intr-un vector
	*/
	std::vector<Masina> sorteazaGeneral(std::string criteriu, bool crescator) const;
	
	/*
	* Returneaza toate masinile din repository
	* pre: -
	* post: toate masinile sunt returnate intr-un vector
	*/
	const std::vector<Masina>& getAll() const noexcept;
	
	/*
	* Goleste lista de lucru
	* pre: -
	* post: lista de lucru este goala
	*/
	void golesteLista();
	
	/*
	* Adauga o masina in lista de lucru, dupa nrInmatriculare
	* pre: nrInmatriculare valid si masina cu nrInmatriculare exista in repository
	* post: masina cu nr inmatriculare = nrInmatriculare este adaugata in lista de lucru
	*/
	void adaugaInLista(const std::string& nrInmatriculare);
	
	/*
	* Genereaza o lista de lucru cu n masini, alese aleator din repository
	* pre: n valid
	* post: sunt adaugate in lista de lucru n masini, alese aleator din repository. Daca n e mai mare decat numarul de masini din repository, atunci se adauga toate masinile din repository
	*/
	void genereazaListaAleatorie(int n);
	
	/*
	* Exporteaza lista de lucru intr-un fisier CSV, cu numele dat ca parametru
	* pre: numeFisier valid
	* post: fisierul numeFisier.csv este creat (sau suprascris) cu datele din listaLucru
	*/
	void exportaListaCSV(std::string numeFisier) const;
	
	/*
	* Returneaza toate masinile din lista de lucru
	* pre: -
	* post: sunt returnate toate masinile din lista de lucru, intr-un vector 
	*/
	const std::vector<Masina>& getAllLista() const noexcept;

	/*
	* Returneaza frecventa unui producator din Repository
	* pre: cheie valid
	* post: este returnat un map care contine numele producatorului si un DTO cu acest nume si frecventa acestuia in Repository
	*/
	const std::map<std::string, DTO> frecventaProducator(const std::string& cheie);

	/*
	* Undo la ultima operatie de adaugare, stergere, modificare
	* pre: -
	* post: ultima operatie de adaugare, stergere, modificare este anulata
			daca nu exista nicio operatie de acest fel, se arunca o exceptie
	*/
	void undo();
};

//void testAdd();

