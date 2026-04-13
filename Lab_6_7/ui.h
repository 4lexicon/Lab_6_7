#pragma once
#include "service.h"
#include "entities.h"
#include <vector>

class UI {
	MasinaService& srv;
public:
	UI(MasinaService& service) noexcept : srv{ service } {
		
	}
	void showUI();
	void afiseazaLista(const std::vector<Masina>& masini);
};