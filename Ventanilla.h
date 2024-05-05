#pragma once
#include <string>
#include "Tiquete.h"

using std::string;
using std::ostream;

class Ventanilla
{
private:
	string nombre;
	Tiquete* currentTiquete;
public:
	Ventanilla() {
		this->nombre = "";
		this->currentTiquete = nullptr;
	}
	Ventanilla(string codeArea, int numVentana) {
		string intStr = std::to_string(numVentana);
		this->nombre = codeArea + intStr;
		this->currentTiquete = nullptr;
	}

	bool operator==(const Ventanilla& other) const {
		// Compare the 'nombre' attribute of the Ventanilla objects
		return this->nombre == other.nombre;
	}

	friend ostream& operator<<(ostream& os, const Ventanilla& ventanilla) {
		os << "Nombre: " << ventanilla.nombre;
		return os;
	}
};

