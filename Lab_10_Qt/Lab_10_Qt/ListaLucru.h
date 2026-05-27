#pragma once
#include <vector>
#include "entities.h"


class ListaLucru {
private:
	std::vector<Masina> listaLucru;

public:

	using value_type = Masina;
	using const_reference = const Masina&;

	ListaLucru() = default;
	/*
	* Declara ce face push_back
	* pre: m valid
	* post: m este adaugat in vectorul listaLucru
	*/
	void push_back(const Masina& m) {
		listaLucru.push_back(m);
	}

	/*
	* Sterge toate elementele din listaLucru
	* pre: -
	* post: lista este golita
	*/
	void goleste() noexcept {
		listaLucru.clear();
	}


	/*
	* Adauga m in lista de lucru
	* pre: m valid
	* post: m este adaugat in lista de lucru
	*/
	void adauga(const Masina& m) {
		push_back(m);
	}

	/*
	* Returneaza toate masinile din lista de lucru
	* pre: -
	* post: este returnata o referinta constanta la vectorul listaLucru
	*/
	const std::vector<Masina>& getAll() const noexcept {
		return listaLucru;
	}

	/*
	* Returneaza dimensiunea listei
	* pre: -
	* post: este returnata o dimensiunea listei de lucru
	*/
	size_t dimensiune() const noexcept {
		return listaLucru.size();
	}

};