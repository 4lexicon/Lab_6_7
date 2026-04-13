#pragma once
#include "entities.h"
#include <string>

class ValidatorException {
private:
	std::string msg;
public:
	ValidatorException(std::string m) : msg{ m } {

	}

	std::string getMessage() const {
		return msg;
	}

};

class MasinaValidator {

public:
	MasinaValidator(const MasinaValidator& ot) = delete; // ca sa nu mai poata fi copiat 
	MasinaValidator() = default;						 // constructor default

	bool valideaza(const Masina& m) const;
};
