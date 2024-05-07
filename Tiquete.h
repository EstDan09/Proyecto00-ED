#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::time_t;
using std::ostringstream;

class Tiquete
{
private:
	string codigo;
	std::chrono::system_clock::time_point fechaCreacion;
	int prioridadFinal = 0;
public:
	Tiquete() {

	}
	Tiquete(int ticketCounter, string codArea, int prioUser, int prioServ) {
		string intStr = std::to_string(ticketCounter);
		this->codigo = codArea + intStr;
		this->setPrioridadFinal(prioUser, prioServ);
		this->prioridadFinal = getPrioridadFinal();
	}

	~Tiquete() {
	}

	void setPrioridadFinal(int prioridadUsuario, int prioridadServicio) {
		this->prioridadFinal = (prioridadUsuario * 10) + prioridadServicio;
	}

	string getCodigo() {
		return this->codigo;
	}

	string getFecha() const {
		std::time_t tiempo_actual = std::chrono::system_clock::to_time_t(fechaCreacion);
		std::tm tiempo;
		localtime_s(&tiempo, &tiempo_actual); // Utiliza localtime_s para evitar la advertencia
		const int buffer_size = 9; // Tamaño suficiente para la hora (HH:MM:SS) + el carácter nulo
		char buffer[buffer_size];
		std::strftime(buffer, buffer_size, "%H:%M:%S", &tiempo); // Formatear la hora en formato de 24 horas con minutos y segundos
		return string(buffer);
	}

	int getPrioridadFinal() {
		return this->prioridadFinal;
	}

	friend ostream& operator<<(ostream& os, const Tiquete& tiquete) {
		os << "Codigo: " << tiquete.codigo << ", Prioridad: " << tiquete.prioridadFinal << ", Fecha de Creación: " << tiquete.getFecha();
		return os;
	}
	
};

