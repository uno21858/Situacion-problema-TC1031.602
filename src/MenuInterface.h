//
// Created by Erick on 18/09/25.
//

#ifndef SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H
#define SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H




class MenuInterface {

public:
    MenuInterface();
    ~MenuInterface();

    void ejecutar();
    void mostrarOpciones();
    int leerOpcion(int min, int max);
    void hacerBusqueda(int opcion);

};


#endif //SITUACION_PROBLEMA_TC1031_602_MENUINTERFACE_H