//
// Created by Erick on 18/09/25.
//

#ifndef SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H
#define SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H

#include "LogsManager.h"
#include <vector>
#include <string>


class MenuInterface {
private:
    vector<LogManager> logsOrdenados; // se cargan para buscar
    string archivoFuente = "bitacoraOrdenada3.txt"; // por defecto
    int contadorBusquedas = 0; // contador para numeroBusqueda
    const int NUMERO_EQUIPO = 4; // numero de equipo

public:
    MenuInterface();

    void ejecutar();
    void mostrarOpciones();
    int leerOpcion(int min, int max);
    void hacerBusqueda(int opcion);
    void clearScreen();
};


#endif //SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H