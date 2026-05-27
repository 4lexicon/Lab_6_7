#include "validator.h"
#include <string>
#include <algorithm> // pentru all_of
#include <cctype> // pentru isdigit
bool MasinaValidator::valideaza(const Masina& m) const {

	std::string errors = "";
	if (m.getId().empty()) {
		errors += "Id-ul nu poate fi vid\n";
	}
	for (int i = 0; i < m.getId().size(); i++) {
		if (!(std::isdigit(m.getId().at(i)))) {
			errors += "Id-ul trebuie sa contina doar cifre\n";
			break;
		}
	}

	if (m.getNrInmatriculare().empty()) {
		errors += "Nr. inmatriculare nu poate fi vid\n";
	}

	if (m.getNrInmatriculare().size() != 7) {
		errors += "Nr. inmatriculare trebuie sa aiba 7 caractere\n";
	}

	else if (!(std::isalpha(m.getNrInmatriculare().at(0))) ||
		!(std::isalpha(m.getNrInmatriculare().at(1))) ||
		!(std::isdigit(m.getNrInmatriculare().at(2))) ||
		!(std::isdigit(m.getNrInmatriculare().at(3))) ||
		!(std::isalpha(m.getNrInmatriculare().at(4))) ||
		!(std::isalpha(m.getNrInmatriculare().at(5))) ||
		!(std::isalpha(m.getNrInmatriculare().at(6)))
		) {
		errors += "Nr. inmatriculare trebuie sa fie in formatul: AA00AAA, unde A = litera si 0 = cifra\n";
	}
	if (m.getProducator().empty()) {
		errors += "Producatorul nu poate fi vid\n";
	}
	if (m.getModel().empty()) {
		errors += "Modelul nu poate fi vid\n";
	}
	if (m.getTip().empty()) {
		errors += "Tipul nu poate fi vid\n";
	}

	if (!errors.empty()) {
		throw ValidatorException(errors);
	}
	return true;

}
