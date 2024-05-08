#pragma once

#include "Area.h"
#include "Ventanilla.h"
#include "TipoUsuario.h"
#include "Servicio.h"
#include "DLinkedList.h"
#include "PriorityQueue.h"
#include "Tiquete.h"
#include "TipoUsuarioClientes.h"

using namespace std;
class Control {
private:
	List<TipoUsuario>* tiposAdmin;
	List<Servicio>* servicios;
	List<Area>* areas;

public:
	Control() {
		this->areas = new DLinkedList<Area>();
		this->servicios = new DLinkedList<Servicio>();
		this->tiposAdmin = new DLinkedList<TipoUsuario>();
	}
	~Control() {
		delete tiposAdmin;
		delete servicios;
		delete areas;
	}

	//getters//
	List<TipoUsuario>* getTiposAdmin() {
		return tiposAdmin;
	}
	List<Area>* getAreas() {
		return areas;
	}

	//metodos TipoUsuario//
	void agregarTipoUsuarioAdmin(string descripcion, int prioridad) {
		TipoUsuario t = TipoUsuario(descripcion, prioridad);
		tiposAdmin->insert(t);
		cout << "dasdasd";
		tiposAdmin->print();
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

	//metodos Tiquetes//
	void agregarTiquete(int numTiquete, Area* area, int prioUser, int prioServ) {
		Tiquete t = Tiquete(numTiquete, area->getCodigo(), prioUser, prioServ);
		int prioridad = t.getPrioridadFinal();
		area->getTiquetes()->insert(t, prioridad);
	}

};