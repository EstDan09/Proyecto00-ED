#pragma once

#include "DLinkedList.h"
#include "DLinkedList.h"
#include "Servicio.h"

using std::string;

class Servicio {
private:
	string descripcion;
	int prioridad;
	Area* area;

public:
	Servicio(string descripcion, int prioridad, Area area) {
		this->area = area;
		this->descripcion = descripcion;
		this->prioridad = prioridad;
	}
	~Servicio() {

	}
	int getPrioridad() {
		return this->prioridad;
	}
	Area getArea() {
		return this->area;
	}
};