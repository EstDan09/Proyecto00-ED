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
	PriorityQueue<Tiquete>* tiquetes;
	List<Servicio>* servicios;
	List<Area>* areas;

public:
	Control() {
		this->areas = new DLinkedList<Area>();
		this->servicios = new DLinkedList<Servicio>();
		this->tiposAdmin = new DLinkedList<TipoUsuario>();
		this->tiquetes = new HeapPriorityQueue<Tiquete>();
	}
	~Control() {
		delete tiposAdmin;
		delete tiquetes;
		delete servicios;
		delete areas;
	}

	//metodos TipoUsuario//
	List<TipoUsuario>* getTiposAdmin() {
		return tiposAdmin;
	}
	PriorityQueue<Tiquete>* getTiquetes() {
		return tiquetes;
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
	void agregarTiquete(int numTiquete, string areaCode, int prioUser, int prioServ) {
		Tiquete t = Tiquete(numTiquete, areaCode, prioUser, prioServ);
		int prioridad = t.getPrioridadFinal();
		tiquetes->insert(t, prioridad);
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