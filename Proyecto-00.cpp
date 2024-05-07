#include <iostream>
#include <conio.h>
#include "PriorityQueue.h" 
#include "TipoUsuario.h"
#include "HeapPriorityQueue.h"
#include "Area.h"
#include "Control.h"
#include "TipoUsuarioClientes.h"
#include <vector>

using namespace std;

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

extern "C" {
    __declspec(dllimport) int __stdcall SetConsoleCursorPosition(void*, struct COORD);
    __declspec(dllimport) void* __stdcall GetStdHandle(int);
}

// Define COORD structure manually
struct COORD {
    short X;
    short Y;
};

// Define function prototype for gotoxy
void gotoxy(int x, int y);

// Implementation of gotoxy function
void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(-11), coord); // STD_OUTPUT_HANDLE = -11
}

/*
settings
*/
int ticketCounter = 0;
int priorityLvlsUsers = 5;

/*
* listas de administrador para los tipos disponibles
*/
Control* controlPrincipal = new Control();
//List<TipoUsuario>* listaTiposUsuario = new DLinkedList<TipoUsuario>();
//
//List<Area>* listaAreas = new DLinkedList<Area>();

int menu(const char* titulo, const char* opciones[], int n) {
    int opcionSelect = 1;
    int tecla;
    bool on = true;

    do {
        system("cls");
        gotoxy(5, 3 + opcionSelect); cout << "==>";
        gotoxy(15, 2); cout << titulo;

        for (int i = 0; i < n; i++) {
            gotoxy(10, 4 + i); cout << i + 1 << ") " << opciones[i];
        }

        do {
            tecla = _getch();
        } while (tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);

        switch (tecla) {
        case TECLA_ARRIBA:
            opcionSelect--;
            if (opcionSelect == 0) {
                opcionSelect = n;
            }
            break;
        case TECLA_ABAJO:
            opcionSelect++;
            if (opcionSelect > n) {
                opcionSelect = 1;
            }
            break;
        case ENTER:
            on = false;
            break;
        }

    } while (on);

    return opcionSelect;
}
void agregarTipoUsuario() {
    
    string descripcion;
    int prioridad;

    system("cls");    
    cout << "\n\t\t\Agrear Tipo de Usuario" << endl;
    cout << "\n\tDescripción: ";
    cin >> descripcion;
    cout << "\n\tPrioridad: ";
    cin >> prioridad;  

    //Falta agregar validacion para descripcion y prioridad ***************
    
    //insetar el tipo de usuario segun la prioridad
    //TipoUsuario nuevoTipoUsuario = TipoUsuario(descripcion, prioridad);
    
    controlPrincipal->agregarTipoUsuarioAdmin(descripcion, prioridad);

    cout << "\n\tUsuario agregado exitosamente!";
    _getch();
    system("cls");

}
void eliminarTipoUsuario() {
    bool on = true;
    int opcion;
    const char* titulo = "Eliminar Tipos de Usuario";
    int n = controlPrincipal->getTiposAdmin()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios para eliminar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getTiposAdmin()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 0; i < controlPrincipal->getTiposAdmin()->getSize(); ++i) {
            TipoUsuario current = controlPrincipal->getTiposAdmin()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i]= descripcion;
            controlPrincipal->getTiposAdmin()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getTiposAdmin()->next();
        }
        controlPrincipal->getTiposAdmin()->remove();
        cout << "\n\n\tUsuario eliminado exitosamente!\n";
        controlPrincipal->getTiposAdmin()->print();
    }
    _getch();
    system("cls");
}
void menuTiposUsuario() {
    bool on = true;
    int opcion;
    const char* titulo = "Menu Tipos de Usuario";
    const char* opciones[] = { "Agregar", "Eliminar", "Regresar" };
    int n = 3;

    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            agregarTipoUsuario();
            break;
        case 2:
            eliminarTipoUsuario();
            break;
        case 3:
            on = false;
            break;            
        }
    } while (on);
}
void agregarArea() {
    string descripcion;
    string codigo;
    int cantVentanillas;

    system("cls");
    cout << "\n\t\t\Agrear Area" << endl;
    cout << "\n\tDescripción: ";
    cin >> descripcion;
    cout << "\n\tCodigo: ";
    cin >> codigo; //verificar que en la lista de areas no haya una con codigo igual
    cout << "\n\tCantidad de Ventanillas: ";
    cin >> cantVentanillas; 

    controlPrincipal->agregarArea(descripcion, codigo, cantVentanillas);
    cout << "\n\Area agregada exitosamente!";
    _getch();
    system("cls");
}
void modificarVentanillasArea() {
    bool on = true;
    int opcion;
    const char* titulo = "Modificar Cantidad de Ventanillas";
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay areas cuyas ventanillas puedes modificar :( que triste";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getAreas()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area& current = controlPrincipal->getAreas()->getElement();
            const string::size_type size = current.getCodigo().size();
            char* codigo = new char[size + 1];
            memcpy(codigo, current.getCodigo().c_str(), size + 1);
            opciones[i] = codigo;
            controlPrincipal->getAreas()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);

        int cantVentanillas;

        system("cls");
        cout << "\n\tCantidad de Ventanillas Nueva: ";
        cin >> cantVentanillas;

        controlPrincipal->getAreas()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getAreas()->next();
        }
        Area& areaToManip = controlPrincipal->getAreas()->getElement();
        areaToManip.setCantVentanillas(cantVentanillas);
        cout << "\n\n\tArea editada exitosamente!\n";
        controlPrincipal->getAreas()->print();
    }
    _getch();
    system("cls");
}
void eliminarArea() {
    bool on = true;
    int opcion;
    const char* titulo = "Eliminar Tipos de Usuario";
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios para eliminar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getAreas()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getAreas()->goToStart();
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area& current = controlPrincipal->getAreas()->getElement();
            const string::size_type size = current.getCodigo().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getCodigo().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getAreas()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getAreas()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getAreas()->next();
        }
        controlPrincipal->getAreas()->remove();
        cout << "\n\n\tUsuario eliminado exitosamente!\n";
        controlPrincipal->getAreas()->print();
    }
    _getch();
    system("cls");
}
void menuGestorAreas() {
    bool on = true;
    int opcion;
    const char* titulo = "Menu Gestor de Areas";
    const char* opciones[] = { "Agregar Area","Modificar Cantidad de Ventanillas", "Eliminar", "Regresar" };
    int n = 4;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            agregarArea();
            break;
        case 2:
            modificarVentanillasArea();
            break;
        case 3:
            eliminarArea();
            break;
        case 4:
            on = false;
            break;
        }
    } while (on);
}
void agregarServicio() {
    int opcion;
    string descripcion;
    int prioridad;

    system("cls");
    cout << "\n\t\t\tAgregar Servicio" << endl;
    cout << "\n\tDescripción: ";
    cin >> descripcion;
    cout << "\n\tPrioridad: ";
    cin >> prioridad; //verificar que en la lista de areas no haya una con codigo igual
    system("cls");
    const char* titulo = "Area para Agregar";
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay Areas para generar servicios";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getAreas()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getAreas()->goToStart();
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area& current = controlPrincipal->getAreas()->getElement();
            const string::size_type size = current.getCodigo().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getCodigo().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getAreas()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getAreas()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getAreas()->next();
        }
        Area& areaToManip = controlPrincipal->getAreas()->getElement();
        Area* areaToManipPtr = &areaToManip;
        controlPrincipal->agregarServicio(descripcion, areaToManipPtr, prioridad);
        cout << "\n\Area agregada exitosamente!";
        controlPrincipal->getServicios()->print();
    }
    _getch();
    system("cls");
}
void eliminarServicio() {
    bool on = true;
    int opcion;
    const char* titulo = "Eliminar Servicio";
    int n = controlPrincipal->getServicios()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios para eliminar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getServicios()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getServicios()->goToStart();
        for (int i = 0; i < controlPrincipal->getServicios()->getSize(); ++i) {
            Servicio& current = controlPrincipal->getServicios()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getServicios()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getServicios()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getServicios()->next();
        }
        controlPrincipal->getServicios()->remove();
        cout << "\n\n\tServicio eliminado exitosamente!\n";
        controlPrincipal->getServicios()->print();
    }
    _getch();
    system("cls");
}
void reordenarServicio() {
    bool on = true;
    int opcion;
    const char* titulo = "Modificar Cantidad de Ventanillas";
    int n = controlPrincipal->getServicios()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay areas cuyas ventanillas puedes modificar :( que triste";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getServicios()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        for (int i = 0; i < controlPrincipal->getServicios()->getSize(); ++i) {
            Servicio& current = controlPrincipal->getServicios()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* codigo = new char[size + 1];
            memcpy(codigo, current.getDescripcion().c_str(), size + 1);
            opciones[i] = codigo;
            controlPrincipal->getServicios()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);

        int newPos;

        system("cls");
        cout << "\n\tPosicion que deseas para el servicio seleccionado: ";
        cin >> newPos;

        controlPrincipal->getServicios()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getServicios()->next();
        }
        int posServ = controlPrincipal->getServicios()->getPos();
        controlPrincipal->reordenarServicios(posServ, newPos);
        cout << "\n\n\tLista de servicios editada exitosamente!\n";
        controlPrincipal->getServicios()->print();
    }
    _getch();
    system("cls");
}
void menuGestorServicios() {
    bool on = true;
    int opcion;
    const char* titulo = "Menu Gestor de Servicios";
    const char* opciones[] = { "Agregar Servicio","Eliminar Servicio", "Reordenar Servicios", "Regresar" };
    int n = 4;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            agregarServicio();
            break;
        case 2:
            eliminarServicio();
            break;
        case 3:
            reordenarServicio();
            break;
        case 4:
            on = false;
            break;
        }
    } while (on);
}
void menuAdmin() {
    bool on = true;
    int opcion;
    const char* titulo = "Menu Administrativo";
    const char* opciones[] = { "Gestor de Tipos de Usuarios", "Gestor Areas", "Gestor Servicios", "Modo Oppenheimer", "Regresar"};
    int n = 5;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            menuTiposUsuario();
            break;
        case 2:
            menuGestorAreas();
            break;
        case 3:
            menuGestorServicios();
            break;
        case 4:
            break;
        case 5:
            on = false;
            break;
        }
    } while (on);
}
void menuTiquetes() {
    bool on = true;
    int opcion;
    const char* titulo = "Eliminar Tipos de Usuario";
    int n = controlPrincipal->getTiposAdmin()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    int priorityToGiveUsr;
    int pripriorityToGiveServ;
    string areaCode;
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios para eliminar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getTiposAdmin()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 0; i < controlPrincipal->getTiposAdmin()->getSize(); ++i) {
            TipoUsuario current = controlPrincipal->getTiposAdmin()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getTiposAdmin()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getTiposAdmin()->next();
        }
       
        priorityToGiveUsr = controlPrincipal->getTiposAdmin()->getElement().getPrioridad();
        cout << "\n\n\tUsuario seleccionado exitosamente!\n";

    }
    _getch();
    on = true;
    titulo = "Modificar Cantidad de Ventanillas";
    n = controlPrincipal->getServicios()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay areas cuyas ventanillas puedes modificar :( que triste";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getServicios()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        for (int i = 0; i < controlPrincipal->getServicios()->getSize(); ++i) {
            Servicio& current = controlPrincipal->getServicios()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* codigo = new char[size + 1];
            memcpy(codigo, current.getDescripcion().c_str(), size + 1);
            opciones[i] = codigo;
            controlPrincipal->getServicios()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);

        controlPrincipal->getServicios()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getServicios()->next();
        }
        pripriorityToGiveServ = controlPrincipal->getServicios()->getElement().getPrioridad();
        areaCode = controlPrincipal->getServicios()->getElement().getArea()->getCodigo();
        controlPrincipal->agregarTiquete(ticketCounter, areaCode, priorityToGiveUsr, pripriorityToGiveServ);
        ticketCounter++;
        cout << "\n\n\tTiquete creado exitosamente!\n";
        controlPrincipal->getTiquetes()->print();
    }

}
void menuPrincipal() {
   
    bool on = true;
    int opcion;
    const char* titulo = "Menu Principale";
    const char* opciones[] = { "Revisar Colas", "Generar Tiquetes", "Atender", "Modo Administrativo", "Estadisitcas", "Salir" };
    int n = 6;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            
            break;
        case 2:
            menuTiquetes();
            break;
        case 3:
            break;
        case 4:
            menuAdmin();
            break;
        case 5:
            break;
        case 6:
            on = false;
            break;
        }

    } while (on);
}
int main()
{   
   setlocale(LC_ALL, "spanish"); // para evitar errores en las tildes
   menuPrincipal();
   //poUsuarioClientes clienteP = TipoUsuarioClientes("sd", 5);
   //ut << clienteP.obtenerFechaComoCadena() << endl;
   //cFienteP.obtenerFechaComoCadena();
}