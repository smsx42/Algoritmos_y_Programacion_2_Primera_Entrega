#include <iostream>
#include "construccion.h"

int main(){

    inventario_t inventario;
    bool retorno_inventario = cargar_inventario(inventario);

    ciudad_t ciudad;
    bool retorno_ciudad = cargar_ciudad(ciudad, inventario);

    if(validar_archivos(retorno_ciudad, retorno_inventario)){
        generar_opciones(inventario, ciudad);
    }

  

    return 0;
}
