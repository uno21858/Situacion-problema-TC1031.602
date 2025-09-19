//
// Created by Erick on 18/09/25.
//

#include "LogsManager.h"
#include "MenuInterface.h"

int main() {
    /* Probar el menu de seleccion
    // Debug o pa probar que si jala el selector o menu
    MenuInterface menu;
    menu.ejecutar();

    // Por el momento se cicla el menu. osea despues de seleccioar una opcion valida. este
    // te vuelve a preguntar lo mismo hasya que lo termines. 5
*/

    // Para leer y vectorizar los logs

    LogManager::generarArchivoVectorizado("../data/bitacora.txt", "logsRawVectorizado.txt");

    return 0;
}