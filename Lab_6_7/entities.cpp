#include "entities.h"

#include <string>
#include <vector>



std::string Masina::getId() const {
	return id; // sau this->id
}

std::string Masina::getNrInmatriculare() const{
	return nrInmatriculare;
}

std::string Masina::getProducator() const{
	return producator;
}

std::string Masina::getModel() const{
	return model;
}

std::string Masina::getTip() const{
	return tip;
}
