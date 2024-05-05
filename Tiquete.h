#pragma once
#include <string>

using std::string;
class Tiquete
{
private:
	string codigo;
	string fecha;
	int prioridadFinal = 0;
public:
	Tiquete(int ticketCounter, string codArea) {
		string intStr = std::to_string(ticketCounter);
		this->codigo = codArea + intStr;
	}

	~Tiquete() {
	}

	void setPrioridadFinal(int prioridadUsuario, int prioridadServicio) {
		this->prioridadFinal = (prioridadUsuario * 10) + prioridadServicio;
	}

	string getCodigo() {
		return this->codigo;
	}

	string getFecha() {
		return this->fecha;
	}

	int getPrioridadFinal() {
		return this->prioridadFinal;
	}
	
};

