//
// Created by Erick on 18/09/25.
//

// main.cpp
#include "LogsManager.h"
#include "MenuInterface.h"


/*
 *github https://github.com/uno21858/Situacion-problema-TC1031.602
 */



int main() {
    const int NUMERO_EQUIPO = 4;

    //lee el archivo linea por linea y lo ordena
    //O(n log n)
    LogManager::genArchivoOrdenado("bitacora.txt", NUMERO_EQUIPO);

    MenuInterface menu;
    menu.ejecutar();

    return 0;
}