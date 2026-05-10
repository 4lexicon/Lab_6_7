#pragma once
#include "entities.h"
#include <string.h>
#include <map>

/*
* Aduce informatii despre frecventa unui producator
*
*/

class DTO {
private:
	std::string cheie; // aparitii este dictionar
	int valoare = 0;

public:

	/*
	* Returneaza cheia (producatorul)
	* pre: -
	* post: returneaza cheia (producatorul)
	*/
	const std::string getCheie() const noexcept {
		return cheie;
	}

	/*
	* Returneaza valoarea (frecventa)
	* pre: -
	* post: returneaza valoare (frecventa)
	*/
	const int getValoare() const noexcept {
		return valoare;
	}

	/*
	* Seteaza cheia (producatorul)
	* pre: cheie_noua string valid
	* post: modifica cheia (producatorul)
	*/
	void setCheie(std::string cheie_noua) {
		cheie = cheie_noua;
	}

	/*
	* Seteaza valoarea (frecventa)
	* pre: valoare_noua numar natural valid
	* post: modifica valoarea (frecventa)
	*/
	void setValoare(int valoare_noua) {
		valoare = valoare_noua;
	}
};