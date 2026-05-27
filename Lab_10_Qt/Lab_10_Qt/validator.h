#pragma once
#include "entities.h"
#include <string>

class ValidatorException {
private:
	std::string msg;
public:
	ValidatorException(std::string m) : msg{ m } {

	}
	/*
	* Returneaza mesajul de eroare
	* pre: -
	* post: mesajul de eroare este returnat
	*/
	std::string getMessage() const {
		return msg;
	}

};

class MasinaValidator {

public:
	MasinaValidator(const MasinaValidator& ot) = delete; // ca sa nu mai poata fi copiat 
	MasinaValidator() = default;						 // constructor default

	/*
	* Valideaza datele unei masini m
	* pre: m este o masina
	* post: m este validata, daca datele sunt valide, invalidata altfel
	*/
	bool valideaza(const Masina& m) const;
};
