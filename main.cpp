//
// Created by Erick on 18/09/25.
//

// main.cpp
#include "LogsManager.h"
#include "MenuInterface.h"

int main() {
    const int NUMERO_EQUIPO = 3; // puse tres por poner no se cual somos la neta pero la tarea dice que se guarda con el numero DN--------
    /* Probar el menu de seleccion
    // Debug o pa probar que si jala el selector o menu
    MenuInterface menu;
    menu.ejecutar();

    // Por el momento se cicla el menu. osea despues de seleccioar una opcion valida. este
    // te vuelve a preguntar lo mismo hasya que lo termines. 5
*/

    // Para leer y vectorizar los logs
    //Si es necesario el ../ es referencia q lo busyq en root
    LogManager::generarArchivoVectorizado("bitacora.txt", "../logsRawVectorizado.txt");

    //Agarra y lee el archivo linea por linea y lo ordena con el traductor DN--------
    LogManager::traductor("bitacora.txt", 3);

    return 0;
}