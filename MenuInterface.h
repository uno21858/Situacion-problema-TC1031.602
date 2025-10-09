//
// Created by Erick on 18/09/25.
//

#ifndef SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H
#define SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H

#include "LogsManager.h"
#include <string>


class MenuInterface {
private:
    MyLinkedList<LogManager> logsOrdenados;
    int contadorBusquedas = 0;
    const int NUMERO_EQUIPO = 4;

public:
    MenuInterface();
    void ejecutar();
};


#endif //SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H