#pragma once

#include "Area.h"
#include "Ventanilla.h"
#include "TipoUsuario.h"
#include "Servicio.h"
#include "DLinkedList.h"
#include "PriorityQueue.h"


class Control {
private:
	PriorityQueue<TipoUsuario>* tipos;
	List<Servicio>* servicios;
	List<Area>* areas;

public:
	Control() {
		this->areas = new DLinkedList<Area>();
		this->servicios = new DLinkedList<Servicio>();
		this->tiposUsuario = new HeapPriorityQueue<TipoUsuario>();
	}
	~Control() {
		delete tiposUsuario;
		delete servicios;
		delete areas;
	}

	//metodos TipoUsuario//
	void agregarTipoUsuario(string descripcion, int prioridad) {
		TipoUsuario t = new TipoUsuario(descripcion, prioridad);
		tipos->insert(t, prioridad);
	}

	//metodos Area//
	void agregarArea(string descripcion, string codigo, int cantVentanillas) {
		Area a = new Area(descripcion, codigo, cantVentanillas);
		areas->append(a);
	}
	void modificarCantidadVent(int numArea, int nuevaCantV) {
		areas->goToPos(numArea - 1);
		Area a = areas->getElement();
		a.setCantVentanillas(nuevaCantV);
	}
	void eliminarArea(int numArea) {
		areas->goToPos(numArea - 1);
		Area a = areas->remove();
		for (Servicio s; servicios) {
			if (s.getArea == a) {
				eliminarServicio2(s);
			}
		}
		delete a;
	}

	//metodos Servicio//
	void agregarServicio(string descripcion, Area area, int prioridad) {
		Servicio s = new Servicio(descripcion, prioridad, area);
		servicios->append(s);
	}
	void eliminarServicio2(Servicio s) {
		if (servicios->contains(s)) {
			int index = servicios->indexOf(s);
			eliminarServicio(index);
		}
	}
	void eliminarServicio(int numServicio) {
		servicios->goToPos(numServicio - 1);
		Servicio s = servicios->remove();
		delete s;
	}
	void reordenarServicios(int numServicio, int posDestino) {
		servicios->goToPos(numServicio);
		Servicio s = servicios->remove();
		servicios->goToPos(posDestino);
		servicios->insert(s);
	}
};