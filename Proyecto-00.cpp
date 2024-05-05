#include <iostream>
#include <conio.h>
#include "PriorityQueue.h" 
#include "TipoUsuario.h"
#include "HeapPriorityQueue.h"
#include "Area.h"
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
List<TipoUsuario>* listaTiposUsuario = new DLinkedList<TipoUsuario>();

List<Area>* listaAreas = new DLinkedList<Area>();

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
    TipoUsuario nuevoTipoUsuario = TipoUsuario(descripcion, prioridad);
    if (listaTiposUsuario->getSize() == 0) {
        listaTiposUsuario->insert(nuevoTipoUsuario);
    }
    else {
        listaTiposUsuario->goToStart();
        while (!listaTiposUsuario->atEnd() && listaTiposUsuario->getElement().getPrioridad() < prioridad) {
            listaTiposUsuario->next();
        }
        listaTiposUsuario->insert(nuevoTipoUsuario);
    }
    cout << "\n\tUsuario agregado exitosamente!";
    _getch();
    system("cls");

}
void eliminarTipoUsuario() {
    bool on = true;
    int opcion;
    const char* titulo = "Eliminar Tipos de Usuario";
    int n = listaTiposUsuario->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios para eliminar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        listaTiposUsuario->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        listaTiposUsuario->goToStart();
        for (int i = 0; i < listaTiposUsuario->getSize(); ++i) {
            TipoUsuario current = listaTiposUsuario->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i]= descripcion;
            listaTiposUsuario->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        listaTiposUsuario->goToStart();
        for (int i = 1; i < opcion; ++i) {
            listaTiposUsuario->next();
        }
        listaTiposUsuario->remove();
        cout << "\n\n\tUsuario eliminado exitosamente!";
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
    cin >> codigo;
    cout << "\n\tCantidad de Ventanillas: ";
    cin >> cantVentanillas;

    Area nuevaArea = Area(descripcion, codigo, cantVentanillas);
    
    listaAreas->insert(nuevaArea);
    listaAreas->print();
    cout << "\n\Area agregada exitosamente!";
    _getch();
    system("cls");
}
void modificarVentanillasArea() {
    bool on = true;
    int opcion;
    const char* titulo = "Modificar Cantidad de Ventanillas";
    int n = listaAreas->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay areas cuyas ventanillas puedes modificar :( que triste";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        listaAreas->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        listaAreas->goToStart();
        for (int i = 0; i < listaAreas->getSize(); ++i) {
            Area current = listaAreas->getElement();
            const string::size_type size = current.getCodigo().size();
            char* codigo = new char[size + 1];
            memcpy(codigo, current.getCodigo().c_str(), size + 1);
            opciones[i] = codigo;
            listaAreas->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        listaAreas->goToStart();
        for (int i = 1; i < opcion; ++i) {
            listaAreas->next();
        }
        Area areaToManip = listaAreas->getElement();
        cout << "\n\n\tUsuario eliminado exitosamente!";
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
            break;
        case 4:
            break;
        case 5:
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
    system("cls");
    bool on = true;
    int opcion;
    do {
        cout << "\n\t\t\tGenerar Tiquete" << endl;
        cout << "\n\t\tTipo de Usuario" << endl;
        cout << "\n\t1. " << endl;
        cout << "\n\t5. Salir" << endl;
        cout << "\n\tOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            on = false;
            break;
        }
    } while (on);
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
   /* PriorityQueue<TipoUsuario>* colaUsuarios = new HeapPriorityQueue<TipoUsuario>(priorityLvlsUsers);
    TipoUsuario juan ("DescripcionJuan", 1);
    TipoUsuario juan2("DescripcionJuan2", 0);
    colaUsuarios->insert(juan, juan.getPrioridad());
    colaUsuarios->insert(juan2, juan2.getPrioridad());
    colaUsuarios->print();
    cout << juan.getPrioridad() << endl;
    Area area("Pagos", "c", 5);
    area.getVentanillas()->print();*/
    menuPrincipal();
}



