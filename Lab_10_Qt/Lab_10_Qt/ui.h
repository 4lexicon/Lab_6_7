#pragma once
#include "service.h"
#include "entities.h"
#include <vector>

class UI {
	MasinaService& srv;
public:
	UI(MasinaService& service) noexcept : srv{ service } {

	}

	/*
	* Afiseaza UI
	*/
	void showUI();

	/*
	* Afiseaza o lista de masini, pe baze unui vector de masini
	*/
	void afiseazaLista(const std::vector<Masina>& masini);
};