#include <iostream>
#include <fstream>
#include <string>
#include "construccion.h"
#include "colors.h"

using namespace std;

void generar_menu()
{

    cout << "\t" << TXT_GREEN_2 << "" << TXT_BOLD << endl;

    cout << "╔════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ Gestor de construccion de Andypolis, seleccione alguna de las opciones:║ " << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════╝" << endl;

    cout << "\t" << "╔════════════════════════════════════════╗" << endl;
    cout << "\t" << "║ 1)- Listar materiales de construccion. ║" << endl;
    cout << "\t" << "║                                        ║" << endl;
    cout << "\t" << "║ 2)- Construir edificio por nombre.     ║" << endl;
    cout << "\t" << "║                                        ║" << endl;
    cout << "\t" << "║ 3)- Listar edificios construidos.      ║" << endl;
    cout << "\t" << "║                                        ║" << endl;
    cout << "\t" << "║ 4)- Listar todos los edificios.        ║" << endl;
    cout << "\t" << "║                                        ║" << endl;
    cout << "\t" << "║ 5)- Demoler edificio por nombre.       ║" << endl;
    cout << "\t" << "║                                        ║" << endl;
    cout << "\t" << "║ 6)- Guardar y salir.                   ║" << endl;
    cout << "\t" << "╚════════════════════════════════════════╝" << endl;
}

void volver_menu()
{

    cout << endl;
    cout << "        "<< "╔══════════════════════════════╗" << endl;
    cout << "        " << "║Oprima 0 para volver al menu: ║" << endl;
    cout << "        " << "╚══════════════════════════════╝" << endl;

    char numero = '1';
    std::cin >> numero;

    while (numero != '0')
    {
        system("clear");
        cout << "             " << "╔══════════════════════════╗" << endl;
        cout << "             " << "║ ----CARACTER INVALIDO----║" << endl;
        cout << "             " << "╚══════════════════════════╝" << endl;

        cout << endl;
        cout << "           " << "╔══════════════════════════════╗" << endl;
        cout << "           " << "║Oprima 0 para volver al menu: ║" << endl;
        cout << "           " << "╚══════════════════════════════╝" << endl;

        std::cin >> numero;
    }

    system("clear");
}

void mostrar_detalles(int opcion)
{

    system("clear");

    if (opcion == OPCION_1)
    {
        cout << "            " << "╔═════════════════════╗" << endl;
        cout << "            " << "║ Lista de materiales ║" << endl;
        cout << "            " << "╚═════════════════════╝" << endl;
        cout << endl;
    }
    else if (opcion == OPCION_2)
    {
        cout << "          " << "╔═══════════════════════════╗" << endl;
        cout << "          " << "║ Construccion de edificios ║" << endl;
        cout << "          " << "╚═══════════════════════════╝" << endl;
        cout << endl;
    }
    else if (opcion == OPCION_3)
    {
        cout << "          " << "╔═══════════════════════╗" << endl;
        cout << "          " << "║ Edificios construidos ║" << endl;
        cout << "          " << "╚═══════════════════════╝" << endl;
        cout << endl;
    }
    else if (opcion == OPCION_4)
    {
        cout << "         " << "╔═══════════════════════════════════╗" << endl;
        cout << "         " << "║ Lista de general de los edificios ║  " << endl;
        cout << "         " << "╚═══════════════════════════════════╝" << endl;
        cout << endl;
    }
    else if (opcion == OPCION_5)
    {
        cout << "          " << "╔══════════════════════════╗" << endl;
        cout << "          " << "║ Eliminacion de edificios ║ " << endl;
        cout << "          " << "╚══════════════════════════╝" << endl;
        cout << endl;
    }
}

bool valida_opcion(char opcion)
{

    bool retorno;

    if (opcion == OPCION_1 ||
        opcion == OPCION_2 ||
        opcion == OPCION_3 ||
        opcion == OPCION_4 ||
        opcion == OPCION_5 ||
        opcion == OPCION_6)
    {

        retorno = true;
    }
    else
    {
        retorno = false;
    }

    return retorno;
}

bool cargar_inventario(inventario_t &inventario)
{

    ifstream archivo_materiales(NOMBRE_ARCH_MATERIALES);
    bool retorno;

    if (!archivo_materiales.fail())
    {

        material_t material;
        while ((archivo_materiales >> material.nombre))
        {
            (archivo_materiales >> material.cantidad);

            inventario.materiales[inventario.tipo_materiales].nombre = material.nombre;
            inventario.materiales[inventario.tipo_materiales].cantidad = material.cantidad;
            inventario.tipo_materiales++;
        }

        retorno = true;
    }
    else
    {
        cout << "\t" << TXT_GREEN_2 << "" << TXT_BOLD << endl;
        cout << "-----ERROR AL LEER EL ARCHIVO: " << NOMBRE_ARCH_MATERIALES << "-----" << endl;
        retorno = false;
    }

    archivo_materiales.close();

    return retorno;
}

bool cargar_ciudad(ciudad_t &ciudad, inventario_t inventario)
{

    ifstream archivo_edificios(NOMBRE_ARCH_EDIFICIOS);
    bool retorno;

    ciudad.tipo_materiales = 3;

    if (!archivo_edificios.fail())
    {
        edificio_t edificio;
        int cantidad_max;
        int construidos;

        while ((archivo_edificios >> edificio.nombre))
        {
            for (int i = 0; i < ciudad.tipo_materiales; i++)
            {
                (archivo_edificios >> edificio.materiales_requeridos[i].cantidad);
            }
            (archivo_edificios >> construidos);
            (archivo_edificios >> cantidad_max);

            ciudad.edificios[ciudad.tipo_edificios].nombre = edificio.nombre;
            for (int i = 0; i < ciudad.tipo_materiales; i++)
            {
                ciudad.edificios[ciudad.tipo_edificios].materiales_requeridos[i].cantidad = edificio.materiales_requeridos[i].cantidad;
            }
            ciudad.edificios[ciudad.tipo_edificios].construidos = construidos;
            ciudad.edificios[ciudad.tipo_edificios].max_cantidad = cantidad_max;
            ciudad.tipo_edificios++;
        }

        for (int i = 0; i < ciudad.tipo_edificios; i++)
        {
            ciudad.edificios[i].materiales_requeridos[0].nombre = PIEDRA;
            ciudad.edificios[i].materiales_requeridos[1].nombre = MADERA;
            ciudad.edificios[i].materiales_requeridos[2].nombre = METAL;
        }

        retorno = true;
    }
    else
    {
        cout << "\t" << TXT_GREEN_2 << "" << TXT_BOLD << endl;
        cout << "-----ERROR AL LEER EL ARCHIVO: " << NOMBRE_ARCH_EDIFICIOS << "-----" << endl;
        retorno = false;
    }

    archivo_edificios.close();

    return retorno;
}

bool validar_archivos(bool retorno_inventario, bool retorno_ciudad)
{

    bool retorno;

    if (retorno_inventario == true && retorno_ciudad == true)
    {
        retorno = true;
    }
    else
    {
        retorno = false;
    }
    return retorno;
}

void modificar_archivo_edificios(ciudad_t ciudad)
{

    ofstream archivo_ciudad(NOMBRE_ARCH_EDIFICIOS);

    if (!archivo_ciudad.fail())
    {
        for (int i = 0; i < ciudad.tipo_edificios; i++)
        {
            archivo_ciudad << ciudad.edificios[i].nombre << " ";
            for (int j = 0; j < ciudad.tipo_materiales; j++)
            {
                archivo_ciudad << ciudad.edificios[i].materiales_requeridos[j].cantidad << " ";
            }
            archivo_ciudad << ciudad.edificios[i].construidos << " ";
            archivo_ciudad << ciudad.edificios[i].max_cantidad << endl;
        }
    }
    else
    {
        cout << "\t" << TXT_GREEN_2 << "" << TXT_BOLD << endl;
        cout << "-----ERROR AL MODIFICAR EL ARCHIVO:  " << NOMBRE_ARCH_EDIFICIOS << "-----" << endl;
    }

    archivo_ciudad.close();
}

void modificar_archivo_materiales(inventario_t inventario)
{

    ofstream archivo_materiales(NOMBRE_ARCH_MATERIALES);

    if (!archivo_materiales.fail())
    {

        for (int i = 0; i < inventario.tipo_materiales; i++)
        {

            archivo_materiales << inventario.materiales[i].nombre << " ";
            archivo_materiales << inventario.materiales[i].cantidad;
            archivo_materiales << endl;
        }
    }
    else{
        cout << "\t" << TXT_GREEN_2 << "" << TXT_BOLD << endl;
        cout << "-----ERROR AL MODIFICAR EL ARCHIVO:  " << NOMBRE_ARCH_MATERIALES << "-----" << endl;
    }

    archivo_materiales.close();
}

void modificar_inventario(inventario_t &inventario, ciudad_t ciudad, int posicion, char opcion, int cantidad_piedra, int cantidad_madera, int cantidad_metal)
{

    for (int i = 0; i < inventario.tipo_materiales; i++)
    {
        if (inventario.materiales[i].nombre == PIEDRA)
        {
            if (opcion == OPCION_2)
            {
                inventario.materiales[i].cantidad -= cantidad_piedra;
            }
            else
            {
                inventario.materiales[i].cantidad += cantidad_piedra;
            }
        }
        else if (inventario.materiales[i].nombre == MADERA)
        {
            if (opcion == OPCION_2)
            {
                inventario.materiales[i].cantidad -= cantidad_madera;
            }
            else
            {
                inventario.materiales[i].cantidad += cantidad_madera;
            }
        }
        else if (inventario.materiales[i].nombre == METAL)
        {
            if (opcion == OPCION_2)
            {
                inventario.materiales[i].cantidad -= cantidad_metal;
            }
            else
            {
                inventario.materiales[i].cantidad += cantidad_metal;
            }
        }
    }

    cout << "Piedra: " << cantidad_piedra << "." << endl;
    cout << "Madera: " << cantidad_madera << "." << endl;
    cout << "Metal: " << cantidad_metal << "." << endl;
}

int contador_materiales(inventario_t inventario, ciudad_t ciudad, int posicion)
{

    int cantidad_tipos_mat = 0;

    for (int i = 0; i < inventario.tipo_materiales; i++)
    {
        if (ciudad.edificios[posicion].materiales_requeridos[0].nombre == inventario.materiales[i].nombre)
        {
            if (ciudad.edificios[posicion].materiales_requeridos[0].cantidad < inventario.materiales[i].cantidad)
            {
                cantidad_tipos_mat++;
            }
        }
        else if (ciudad.edificios[posicion].materiales_requeridos[1].nombre == inventario.materiales[i].nombre)
        {
            if (ciudad.edificios[posicion].materiales_requeridos[1].cantidad < inventario.materiales[i].cantidad)
            {
                cantidad_tipos_mat++;
            }
        }
        else if (ciudad.edificios[posicion].materiales_requeridos[2].nombre == inventario.materiales[i].nombre)
        {
            if (ciudad.edificios[posicion].materiales_requeridos[2].cantidad < inventario.materiales[i].cantidad)
            {
                cantidad_tipos_mat++;
            }
        }
    }

    return cantidad_tipos_mat;
}

void confirmar_construccion(inventario_t &inventario, ciudad_t &ciudad, int posicion)
{

    mostrar_detalles(OPCION_2);

    cout << "Cuenta con los materiales necesarios, confirme si quiere constuir el edificio: " << endl;

    cout << "           " << "╔═══════════════╗" << endl;
    cout << "           " << "║----Si - NO----║" << endl;
    cout << "           " << "╚═══════════════╝" << endl;
    cout << endl;

    string decision;
    std::cin >> decision;

    if (decision == "si" || decision == "Si")
    {

        mostrar_detalles(OPCION_2);

        cout << "Acaba de construir el siguiente edificio: " << ciudad.edificios[posicion].nombre << endl;
        cout << "Se eliminaron los siguientes materiales: " << endl;

        int cantidad_piedra = ciudad.edificios[posicion].materiales_requeridos[0].cantidad;
        int cantidad_madera = ciudad.edificios[posicion].materiales_requeridos[1].cantidad;
        int cantidad_metal = ciudad.edificios[posicion].materiales_requeridos[2].cantidad;

        modificar_inventario(inventario, ciudad, posicion, OPCION_2, cantidad_piedra, cantidad_madera, cantidad_metal);

        ciudad.edificios[posicion].construidos += 1;

        cout << endl;
    }
    else if (decision == "no" || decision == "No")
    {

        mostrar_detalles(OPCION_2);
        cout << "No se realizo la opereacion. " << endl;
        volver_menu();
    }
}

void listar_materiales(inventario_t inventario)
{

    mostrar_detalles(OPCION_1);

    for (int i = 0; i < inventario.tipo_materiales; i++)
    {
        cout << "Material: " << inventario.materiales[i].nombre << " --- "
             << "Cantidad: " << inventario.materiales[i].cantidad << endl;
        cout << endl;
    }

    volver_menu();
}

void construir_edificio(inventario_t &inventario, ciudad_t &ciudad)
{

    mostrar_detalles(OPCION_2);

    cout << "Indique que tipo de edificio queire construir: ";

    string nombre_edificio;
    std::cin >> nombre_edificio;
    int contador = 0;
    int posicion = 0;

    for (int i = 0; i < ciudad.tipo_edificios; i++)
    {
        if (ciudad.edificios[i].nombre == nombre_edificio)
        {
            contador++;
            posicion = i;
        }
    }

    if (contador == 0)
    {

        mostrar_detalles(OPCION_2);

        cout << "El edificio " << nombre_edificio << " no esta entre las opciones de construccion. " << endl;
    }
    else
    {

        bool anulador = true;

        int contador_tipos_mat = contador_materiales(inventario, ciudad, posicion);

        if (ciudad.edificios[posicion].max_cantidad == ciudad.edificios[posicion].construidos)
        {
            anulador = false;
        }
        if (contador_tipos_mat == ciudad.tipo_materiales && anulador == true)
        {

            confirmar_construccion(inventario, ciudad, posicion);
        }
        else if (!anulador)
        {

            mostrar_detalles(OPCION_2);
            cout << "Se excede la cantidad maxima de edificios del tipo " << nombre_edificio << endl;
        }
        else
        {

            mostrar_detalles(OPCION_2);
            cout << "No cuenta con la cantidad suficiente de materiales para constuir el edificio del tipo " << nombre_edificio << endl;
        }
    }

    volver_menu();
}

void listar_edificios_construidos(ciudad_t ciudad)
{

    mostrar_detalles(OPCION_3);

    for (int i = 0; i < ciudad.tipo_edificios; i++)
    {
        cout << "Nombre: " << ciudad.edificios[i].nombre << endl;
        cout << "Cantidad: " << ciudad.edificios[i].construidos << endl;
        cout << endl;
    }

    volver_menu();
}

void listar_todos_edificios(ciudad_t ciudad, inventario_t inventario)
{

    mostrar_detalles(OPCION_4);

    for (int i = 0; i < ciudad.tipo_edificios; i++)
    {
        cout << "Edificio: " << ciudad.edificios[i].nombre << endl;
        cout << endl;
        cout << "Materiales: " << endl;
        for (int j = 0; j < ciudad.tipo_materiales; j++)
        {
            cout << ciudad.edificios[i].materiales_requeridos[j].nombre << ":" << ciudad.edificios[i].materiales_requeridos[j].cantidad << endl;
        }
        cout << endl;
        cout << "Cantidad maxima: " << ciudad.edificios[i].max_cantidad << "." << endl;
        int diferencia = ciudad.edificios[i].max_cantidad - ciudad.edificios[i].construidos;
        if (ciudad.edificios[i].construidos < ciudad.edificios[i].max_cantidad)
        {
            cout << "Edificios construidos: " << ciudad.edificios[i].construidos << "." << endl;
            cout << "Puede construir: " << diferencia << "." << endl;
        }
        else if (ciudad.edificios[i].construidos == ciudad.edificios[i].max_cantidad)
        {
            cout << "Edificios construidos: " << ciudad.edificios[i].construidos << "." << endl;
            cout << "LLego a la cantiad maxima de edificios del tipo " << ciudad.edificios[i].nombre << "." << endl;
        }
        cout << endl;
    }

    volver_menu();
}

void eliminar_edificio(ciudad_t &ciudad, inventario_t &inventario)
{

    mostrar_detalles(OPCION_5);

    cout << "Indique que edificio queire destruir, se le dara la mitad de los materiales que costo su construccion:  ";
    string nombre_edificio;
    std::cin >> nombre_edificio;

    for (int i = 0; i < ciudad.tipo_edificios; i++)
    {
        if (ciudad.edificios[i].nombre == nombre_edificio && ciudad.edificios[i].construidos != 0)
        {
            ciudad.edificios[i].construidos--;

            mostrar_detalles(OPCION_5);

            cout << "Elimino un edificio del tipo " << nombre_edificio << ", se acaban de agregar los siguientes materiales a su inventario: " << endl;

            int cantidad_piedra = ciudad.edificios[i].materiales_requeridos[0].cantidad / 2;
            int cantidad_madera = ciudad.edificios[i].materiales_requeridos[1].cantidad / 2;
            int cantidad_metal = ciudad.edificios[i].materiales_requeridos[2].cantidad / 2;

            modificar_inventario(inventario, ciudad, i, OPCION_5, cantidad_piedra, cantidad_madera, cantidad_metal);
        }
        else if (ciudad.edificios[i].nombre == nombre_edificio && ciudad.edificios[i].construidos == 0)
        {

            mostrar_detalles(OPCION_5);

            cout << "Actualemte no hay edificios del tipo " << nombre_edificio << ", no se pudo eliminar." << endl;
        }
    }

    volver_menu();
}

void generar_opciones(inventario_t inventario, ciudad_t ciudad)
{

    char opcion;

    system("clear");

    while (opcion != OPCION_6)
    {

        generar_menu();

        std::cin >> opcion;

        if (valida_opcion(opcion))
        {

            if (opcion == OPCION_1)
            {

                system("clear");
                listar_materiales(inventario);
            }
            else if (opcion == OPCION_2)
            {

                system("clear");
                construir_edificio(inventario, ciudad);
            }
            else if (opcion == OPCION_3)
            {

                system("clear");
                listar_edificios_construidos(ciudad);
            }
            else if (opcion == OPCION_4)
            {

                system("clear");
                listar_todos_edificios(ciudad, inventario);
            }
            else if (opcion == OPCION_5)
            {

                system("clear");
                eliminar_edificio(ciudad, inventario);
            }
        }
        else
        {

            system("clear");
            cout << "             "     << "╔══════════════════════════╗" << endl;
            cout << "             "     << "║ ----CARACTER INVALIDO----║" << endl;
            cout << "             "     << "╚══════════════════════════╝" << endl;
        }
    }

    modificar_archivo_materiales(inventario);

    modificar_archivo_edificios(ciudad);
}
