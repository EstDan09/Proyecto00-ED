#pragma once
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

class TipoUsuario
{
private:
	string descripcion;
	int prioridad;

public:
	TipoUsuario(){
		this->descripcion = "";
		this->prioridad = 99;
	}
	TipoUsuario(string descripcion, int prioridad) {
		this->descripcion = descripcion;
		this->prioridad = prioridad;
	}
	~TipoUsuario() {
	}

	string getDescripcion() {
		return descripcion;
	}

	int getPrioridad() {
		return prioridad;
	}

	friend ostream& operator<<(ostream& os, const TipoUsuario& usuario) {
		os << "Descripción: " << usuario.descripcion << ", Prioridad: " << usuario.prioridad;
		return os;
	}

};