#ifndef CONSTRUCCION_UTILES_H
#define CONSTRUCCION_UTILES_H
#include <string>

using namespace std;

const int MAX_TIPO_MATERIALES = 100;
const int MAX_TIPO_EDIFICIOS = 100;

const string PIEDRA = "Piedra";
const string MADERA = "Madera";
const string METAL = "Metal";

const char OPCION_1 = '1';
const char OPCION_2 = '2';
const char OPCION_3 = '3';
const char OPCION_4 = '4';
const char OPCION_5 = '5';
const char OPCION_6 = '6';

const string NOMBRE_ARCH_MATERIALES = "materiales.txt";
const string NOMBRE_ARCH_EDIFICIOS = "edificios.txt";

struct material_t{
   int cantidad;
   string nombre;
};

struct inventario_t{
   int tipo_materiales = 0;
   material_t materiales[MAX_TIPO_MATERIALES];
};

struct edificio_t{
   string nombre;
   material_t materiales_requeridos[MAX_TIPO_MATERIALES];
   int max_cantidad = 0;
   int construidos = 0;
};

struct ciudad_t{
   edificio_t edificios[MAX_TIPO_EDIFICIOS];
   int tipo_edificios = 0;
   int tipo_materiales = 0;    
};

// Precondiciones: -
// Postcondiciones: Imprime por panatlla el menu de la terminal.
void generar_menu();

// Preconciones: -
// Veelve al menu de la terminal al oprimir 0.
void volver_menu();

// Precondiciones: -
// Postcondiciones: Imprime por pantalla los detalles, dependiendo la opcion.
void mostrar_detalles();

// Precondicion: La variable opcion debe ser un caracter.
// Postcondiciones: Devuelve true en el caso de que las opcion sea valida, y false en caso de que no.
bool validar_opcion(char opcion);

// Precondiciones: El archivo materiales.txt debe estar cargado correctamente, y se le debe cargar la variable inventario.
// Postcondiciones: En caso de existir el archivo, cargar los datos de este en la variable inventario y devuelve true, sino
// no se carga nada y devuelve false.
bool cargar_inventario(inventario_t &inventario);

// Precondiciones: El archivo edificios.txt debe estar caragdo correctamente, y se le debe cargar 
// tanto la variable ciudad, como inventario.
// Postcondiciones: En caso de existir el archivo, cargar los datos de este en la variable ciudad y devuelve true, sino
// no se carga nada y devuelve false.
bool cargar_ciudad(ciudad_t &ciudad, inventario_t inventario);

// Precondiciones: Recive dos variables del tipo bool.
// Postcondiciones: Devuelve true o false dependiendo de las variables.
bool validar_archivos(bool retorno_ciudad, bool retorno_inventario);

// Precondiciones: Se deben cargar las variables inventario, ciudad, posicion, opcion (2 o 5) y cantidades correctamente.
// Postcondiciones: Modifica el contendio de la variable inventario dependiendo la opcion.
void modificar_inventario(inventario_t &inventario, ciudad_t ciudad, int posicion, char opcion, int cantidad_piedra, int cantidad_madera, int cantidad_metal);

// Precondiciones: Se deben cargar las variables de inventario, ciudad y posicion.
//Postcondiciones: Devuelve la cantidad de tipo de materiales que cumplen las condiciones de construccion.
int contador_materiales(inventario_t inventario, ciudad_t ciudad, int posicion);

// Precondiciones: El archivo edificios.txt debe estar cargado correctamente, y se debe cargar la variable ciudad.
// Postcondiciones: En caso de existir el archvio, lo modifica con los datos la de variable ciudad; en caso de
// que no exista el archivo, se imprime por pantalla un aviso.
void modificar_archivo_edificios(ciudad_t ciudad);

// Precondiciones: El archivo materiales.txt debe estar caragdo correctamente,  y se le debe cargar la variable inventario.
// Postcondiciones: En caso de exisitr el archivo, lo modifica con los datos de la variable inventario; en caso de
// que no exista el archivo, se imprime por pantalla un aviso.
void modificar_archivo_materiales(inventario_t inventario);


// Precondiciones: Se debe cargar la variable con los datos del inventario.
// Postcondiciones: Imprime por pantalla el nombre de los materiales utilizados y sus cantidades actuales.
void listar_materiales(inventario_t inventario);

/* Precondiciones: Se debe cargar ambas variables, la primera con los datos del inventario; y la 
   segunda con los datos de la ciudad.
   Tambien es necesario que los archivos materiales.txt y edificios.txt esten bien formados.
*/
/* Postcondiciones: Dado el nombre del edificio, se agrega a ciudad dicho edificio y se
   eliminan los costos de construccion del inventario.
   Tambien se modfician los datos de los archivos materiales.txt y edificios.txt.
*/
void construir_edificio(inventario_t &inventario, ciudad_t &ciudad);

// Precondiciones: Se debe cargar la variable con los datos de la ciudad.
// Postcondiciones: Imprime por pantalla el nombre y la cantidad de edificios construidos en la ciudad.
void listar_edificios_construidos(ciudad_t ciudad);

// Precondiciones: Se deben cargar ambas variable, la primera con los datos de la ciudad; y la 
// segunda con los datos del inventario.
/* Postcondiciones: Imprime por pantalla los siguientes datos:
   - Nombre de los tipos de edificios disponibles para construir.
   - Cantidad de materiales necesaria para la construccion de cada tipo de edificio.
   - Cantidad maxima de edificios construidos.
   - Cantidad actual de edificios construidos.
   - Cantidad de edficios que se pueden construir.
*/
void listar_todos_edificios(ciudad_t ciudad, inventario_t inventario);

/* Precondiciones: Se debe cargar ambas variables, la primera con los datos del inventario; y 
   la segunda con los datos de la ciudad.
   Tambien es necesario que exista la ruta de los archivos materiales.txt y edificios.txt.
*/
/* Postcondiciones: Dado el nombre del edificio, se elimina de la ciudad dicho edificio y 
   se agregan la mitad de los materiales de su costo de construccion al inventario.
   Tambien actualizara los datos de los archivos materiales.txt y edificios.txt.
*/
void eliminar_edificio(ciudad_t &ciudad, inventario_t &inventario);

// Precondiciones: Se debe cargar ambas variables, la primera con los datos del inventario; y la segunda con los datos de la ciudad.
// Postcondiciones: Se generaran las opciones mostradas en el menu.
void generar_opciones(inventario_t inventario, ciudad_t ciudad);

#endif //CONSTRUCCION_UTILES_H

