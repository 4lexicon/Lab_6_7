#pragma once

#include <string>
#include <vector>
#include <iostream>

class Masina {
private:
	std::string id;
	std::string nrInmatriculare;
	std::string producator;
	std::string model;
	std::string tip;

public:

	Masina(std::string id, std::string nrInmatriculare, std::string producator, std::string model, std::string tip) :id{ id }, nrInmatriculare{ nrInmatriculare }, producator{ producator }, model{ model }, tip{ tip } {

	} // Constructor obisnuit
	

	std::string getId() const;
	std::string getNrInmatriculare() const;
	std::string getProducator() const;
	std::string getModel() const;
	std::string getTip() const;

	//void adaugare(std::string nrInmatriculare, std::string producator, std::string model, std::string tip);
	//void stergere(std::string nrInmatriculare, std::string producator, std::string model, std::string tip);
	//void modificare(std::string id, std::string nrInmatriculare_nou, std::string producator_nou, std::string model_nou, std::string tip_nou);


	Masina(const Masina& ot) : id{ ot.id }, nrInmatriculare{ ot.nrInmatriculare }, producator{ ot.producator }, model{ ot.model }, tip{ ot.tip } {
		std::cout << "COPIE " << "\n";
	} // Copy Constructor

	//Copy Assignment Operator
	Masina& operator  = (const Masina& ot) {

		if (this == &ot) { // pentru autoatribuire
			return *this;
		}

		Masina copie(ot);

		std::swap(this->id, copie.id);
		std::swap(this->nrInmatriculare, copie.nrInmatriculare);
		std::swap(this->producator, copie.producator);
		std::swap(this->model, copie.model);
		std::swap(this->tip, copie.tip);

		return *this;
	}


	// Move Constructor ver 1
	//Masina(Masina&& other) noexcept : id(other.id), nrInmatriculare(other.nrInmatriculare), producator(other.producator), model(other.model), tip(other.tip) {
	//	other.id = "";
	//	other.nrInmatriculare = "";
	//	other.producator = "";
	//	other.model = "";
	//	other.tip = "";
	//}
	// && = referinta la rvalue

	// Move Constructor ver 2
	Masina(Masina&& other) noexcept :
		id(std::move(other.id)),
		nrInmatriculare(std::move(other.nrInmatriculare)),
		producator(std::move(other.producator)),
		model(std::move(other.model)),
		tip(std::move(other.tip))
	{

	}// move e mai eficient
	 // valorile care sunt mutate vor fi "resetate" la ""

	// Move Assignment Operator
	Masina& operator = (Masina&& other) noexcept {
		if (this != &other) {
			id = std::move(other.id);
			nrInmatriculare = std::move(other.nrInmatriculare);
			producator = std::move(other.producator);
			model = std::move(other.model);
			tip = std::move(other.tip);
		}
		return *this;
	}

	// constructor manual de distrugere
	~Masina(){};
};