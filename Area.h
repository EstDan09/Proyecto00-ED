#pragma once
#include <string>
#include "Ventanilla.h"
#include "DLinkedList.h"
#include "PriorityQueue.h"
#include "HeapPriorityQueue.h"
#include "List.h"

using std::string;
class Area
{
private:
	string codigo;
	int numVentana;
	string descripcion;
	int cantVentanas;
	DLinkedList<Ventanilla>* ventanillas;
	PriorityQueue<Tiquete>* tiquetes;

public:
	Area() {
		this->descripcion = "";
		this->codigo = "";
		this->cantVentanas = 0;
		this->numVentana = 0;
	}
	Area(string descripcion, string codigo, int cantVentanas) {
		this->descripcion = descripcion;
		this->codigo = codigo;
		this->cantVentanas = cantVentanas;
		this->numVentana = 0;
		ventanillas = new DLinkedList<Ventanilla>();
		for (int i = 0; i < cantVentanas; i++) {
			numVentana++;
			Ventanilla ventanaNueva(this->codigo, numVentana);
			ventanillas->append(ventanaNueva);
		}
		ventanillas->print();
	}
	string getCodigo() {
		return this->codigo;
	}
	DLinkedList<Ventanilla>* getVentanillas() {
		return ventanillas;
	}
	void setCantVentanillas(int cantVentanas) {
		this->numVentana = 0;
		ventanillas->clear();
		this->cantVentanas = cantVentanas;
		for (int i = 0; i < cantVentanas; i++) {
			numVentana++;
			Ventanilla ventanaNueva(this->codigo, numVentana);
			ventanillas->append(ventanaNueva);
		}
		ventanillas->print();
	}
	void setCodigo() {
		this->codigo = "Z";
	}
	friend ostream& operator<<(ostream& os, const Area& area) {
		os << "Descripción: " << area.descripcion << ", Codigo: " << area.codigo << ", Cant.Ventanillas: " << area.cantVentanas;
		return os;
	}//test

};

