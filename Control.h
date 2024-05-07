#pragma once

#include "Area.h"
#include "Ventanilla.h"
#include "TipoUsuario.h"
#include "Servicio.h"
#include "DLinkedList.h"
#include "PriorityQueue.h"
#include "TipoUsuarioClientes.h"

using namespace std;
class Control {
private:
	List<TipoUsuario>* tiposAdmin;
	PriorityQueue<TipoUsuarioClientes>* tiposPublica;
	List<Servicio>* servicios;
	List<Area>* areas;

public:
	Control() {
		this->areas = new DLinkedList<Area>();
		this->servicios = new DLinkedList<Servicio>();
		this->tiposAdmin = new DLinkedList<TipoUsuario>();
		this->tiposPublica = new HeapPriorityQueue<TipoUsuarioClientes>();
	}
	~Control() {
		delete tiposAdmin;
		delete tiposPublica;
		delete servicios;
		delete areas;
	}

	//metodos TipoUsuario//
	List<TipoUsuario>* getTiposAdmin() {
		return tiposAdmin;
	}
	PriorityQueue<TipoUsuarioClientes>* getTiposPublica() {
		return tiposPublica;
	}
	List<Area>* getAreas() {
		return areas;
	}
	void agregarTipoUsuarioAdmin(string descripcion, int prioridad) {
		TipoUsuario t = TipoUsuario(descripcion, prioridad);
		tiposAdmin->insert(t);
		cout << "dasdasd";
		tiposAdmin->print();
	}
	void agregarTipoUsuarioActivos(string descripcion, int prioridad) {
		TipoUsuarioClientes t = TipoUsuarioClientes(descripcion, prioridad);
		tiposPublica->insert(t, prioridad);
	}

	//metodos Area//
	void agregarArea(string descripcion, string codigo, int cantVentanillas) {
		Area a = Area(descripcion, codigo, cantVentanillas);
		areas->append(a);
		areas->print();
	}
	void modificarCantidadVent(int numArea, int nuevaCantV) {
		areas->goToPos(numArea - 1);
		Area a = areas->getElement();
		a.setCantVentanillas(nuevaCantV);
	}


	//metodos Servicio//
	List<Servicio>* getServicios() {
		return servicios;
	}
	void agregarServicio(string descripcion, Area* area, int prioridad) {
		Servicio s = Servicio(descripcion, prioridad, area);
		servicios->append(s);
	}
	void reordenarServicios(int numServicio, int posDestino) {
		servicios->goToPos(numServicio);
		Servicio s = servicios->remove();
		servicios->goToPos(posDestino);
		servicios->insert(s);
	}
};