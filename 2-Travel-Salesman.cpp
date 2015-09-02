/* ·············································································
   
   Título: Práctica 2, El problema del viajero. ("Travel Salesman Problem")
   
   Resumen: Solucionar el Problema del viajero mediante el algoritmo del
            vecino más cercano.
   
   Asignatura: Complejidad Computacional
   Profesor: Ángel Serrano Sánchez de León
   Alumno: Miguel Revuelta Espinosa (revuel22@hotmail.com)
   Fecha: 6/11/2013 - 5/12/2013
   
············································································· */

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   LIBRERÍAS Y ESPACIOS DE NOMBRES
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
#include <sstream>    // |
#include <fstream>    // |- Librerías tratamiento de ficheros
#include <string.h>   // |
#include <stdlib.h>   // Para usar la función "system("")"
#include <iostream>   // Para usar las funciones cin & cout
#include <vector>     // Para usar la clase vector

using namespace std;  // Para reconocer librerías de la STL (vector)


/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   DECLARACIÓN DE FUNCIONES DE LA APLICACIÓN
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
// Mostrar un menú y seleccionar opción, para posterior ejecución de operaciones
void menu(vector <vector<int> > *, int, vector<int>*, vector<int>*, int, vector<string>*);
      
// Cargar datos desde un .txt en nuestra matriz
int cargar_matriz(vector <vector<int> > *);

// Visualizar por consola una matriz 
void mostrar_matriz(vector <vector<int> > *, int); 

// Función que decide el recorrido
// (Ciudades, número de ciudades, visitadas, recorrido, ciudad de origen, distancia total)
void problema_viajante(vector <vector<int> > *, int, vector<int>*, vector<int>*, int);

// Función que haya la ciudad vecina más cercana
// (Ciudades, número de ciudades, ciudad actual, visitadas)
int maxcercana(vector <vector<int> > *, int, int, vector<int>*);

// Seleccionar ciudad de partida
int seleccionar_origen(vector<string>*, int);

// Incializar visitadas a cero
void inicializar_visitadas(vector<int>*, int);

// Visualizar un vector
void ver_vector(vector<int>*, int);

// Determinar la distancia total de un recorrido
int determinar_distanciatotal(vector<int>*);

// Establecer nombres de ciudades
void nombrar(vector<string>*);

// Obtener el nombre de la ciudad
string devolver_ciudad(vector <string>* nombres, int n);

// Recorrer vector recorrido usando nombres de ciudades
void recorrido_verticesyaristas(vector<int>*, vector<string>*);


/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   FUNCIÓN PRINCIPAL (MAIN)
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
int main(void)
{
    // Declaraciones de variables
    
    int siz; // Tamaño de la matriz, (número de ciudades)
    int origen; // Ciudad de partida
    vector <vector<int> > matriz; // Nuestra matriz de adyacencia (aristas)
    vector <int> fila; // Cada fila de la matriz será un vector
    vector <int> visitadas; // (0,1) indicará que ciudades fueron visitadas
    vector <int> recorrido; // Solución ciudades (vérices)
    vector <string> nombres; // Nombres de las ciudades
    

    // Inicio del flujo del programa
    
    // Parte 1 (Carga de datos)
    nombrar(&nombres); // Cargar el vector de los nombres de las ciudades
    siz = cargar_matriz(&matriz); // Cargamos la matriz y devolvemos el número de ciudades
    cout << "\n\n\n" << "N\xA3mero de ciudades: " << siz; // Mostramos el número de ciudades
    cout << "\n\n";
    cout << "Matriz de adyacencia cargada con \x82xito:";
    cout << "\n";
    mostrar_matriz(&matriz,siz); // Mostramos la matriz de adyacencia
    cout << "\n\n";
    system("pause");

    // Parte 2 (Operaciones)
    //nombrar(&nombres);
    inicializar_visitadas(&visitadas, siz); // Inicializamos el estado de las ciudades
    menu(&matriz, siz, &visitadas, &recorrido, origen, &nombres); // Nos trasladamos al menú de opciones
    
    // Saliendo de la aplicación
    cout << "\n\n" << "El programa finalizar\xA0" << "\n";
    system("pause");
    return 0;
}


/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   FUNCIONES Y PROCEDIMIENTOS DE LA PRÁCTICA
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Problema del viajante
  Parámetros de entrada: Matriz, 2 vectores de enteros, 2 enteros
  Resumen: Calcula el recorrido desde una ciudad de partida usando el algoritmo
           del vecino más cercano.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void problema_viajante(vector <vector<int> > *matriz, int siz, vector<int> *visitadas, vector<int> *recorrido, int origen)
{
    // Variables locales
    int i; // Índice 
    int ciudadactual = origen; // Ciudad actual (la primera es el origen)
    int ciudadanterior; // Última ciudad visitada
    int auxdistancia; // Distancia entre ciudades (arista)
    
    (*recorrido).push_back(ciudadactual);    // Añadiendo el origen a la solución
    
    // Añadiendo ciudades al recorrido
    for (i = 0; i < siz-1; i++) // Explicar la perplejidad en la memoria sobre siz-1
    {
        ciudadanterior = ciudadactual; // La última ciudad es la actual
        (*visitadas)[ciudadanterior] = 1; // La ciudad actual es visitada
        ciudadactual = maxcercana(&(*matriz), siz, ciudadanterior, &(*visitadas)); // El kit de la cuestión, seguir pasando referencias
        
        auxdistancia = (*matriz)[ciudadanterior][ciudadactual]; // Determinando distancia entre ciudades (arista)
        (*recorrido).push_back(auxdistancia); // Añadiendo distancia a la solución (arista)
        (*recorrido).push_back(ciudadactual); // Guardando la nueva ciudad actual (vércice)        
    }
    auxdistancia = (*matriz)[ciudadactual][origen];// |
    (*recorrido).push_back(auxdistancia);          // |- Añadiendo última arista y último vertice (vuelta a casa)
    (*recorrido).push_back(origen);                // |
}

/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Función: Cálculo de la vecina más cercana
  Parámetros de entrada: Matriz, vector de enteros, 2 enteros.
  Parámetros de salida: Entero
  Resumen: Esta función haya la ciudad más cercana que no haya sido visitada, 
           y devuelve la posición de dicha ciudad.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
int maxcercana(vector <vector<int> > *matriz, int siz, int cactual, vector<int>* visitadas)
{
    int i, j; // Índices de recorrido la matriz
    int candidata = 999999; // Variable de sobreescritura de la distancia de la ciudad más cercana
    int cercana; // Guardaremos la posición de la ciudad más cercana

    for (j = 0; j < siz; j++) // Recorriendo la fila correspondiente a la ciudad actual
    {
        // Comprobación: ¿Es la misma ciudad (0)?, ¿la distancia es menor que la última candidata?, ¿está marcada como visitada?
        if ((*matriz)[cactual][j] > 0 && (*matriz)[cactual][j] < candidata && (*visitadas)[j] != 1)
        {
           candidata = (*matriz)[cactual][j]; // Nueva menor distancia encontrada
           cercana = j; // Nueva ciudad más cercana encontrada
          
        } 
    }    
    return cercana; // Devolvemos ciudad más cercana   
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Función: Cargar datos en la matriz
  Parámetros de entrada: Matriz
  Parámetros de salida: Entero
  Resumen: Cargamos los datos desde un fichero para guardarlos en nuestra matriz 
           y devolvemos el número de ciudades (líneas leidas).
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
int cargar_matriz(vector <vector<int> > *matriz)
{
   // Variables locales
   ifstream inFile("tcc.txt"); // Seleccionar archivo
   string line; // Iremos leyendo línea a línea
   int linenum = 0; // Contaremos las líneas leidas
   int aux; // Variable auxiliar donde volcaremos conversiones string a int
   vector <int> fila; // Vector de llenado de filas para la matriz
   
   // Lectura del fichero (línea a línea)
   while (getline (inFile, line))  
   { 
         linenum++;
         cout << "\nCiudad: " << linenum << ":" << endl; 
         istringstream linestream(line); 
         string item; // Variable para formateo de líneas de fichero
         int itemnum = 1; // Variable contador del número de items por línea
         
         // Lectura de items: carácter de discriminación: espacio
         while (getline (linestream, item, ' '))
         { 
               cout << "Distancia a: " << itemnum << ": " << item << endl;
               itemnum++; // Pasamos al siguiente item de la línea
               
               istringstream (item) >> aux; // Conversión de string a integer
               fila.push_back(aux); // Añadiendo enteros a vector
         } 
         (*matriz).push_back(fila); // Añadiendo vectores la matriz
         fila.clear(); // Borramos la fila para reutilizarla en la siguiente iteración
   }
   return linenum; // Devolvemos la cantidad de líneas leidas (es decir, el número de ciudades)
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Mostrar una matriz
  Parámetros de entrada: Matriz, entero.
  Resumen: Este procedimiento recorre una mariz mostrándola por pantalla
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void mostrar_matriz(vector <vector<int> > *matriz, int siz)
{
     int i, j; // Índices
     
     // Mostrar matriz
     for( i=0; i<siz; i++) // Filas
     {
        cout << "\n";  
        for ( j=0; j<siz; j++) // Columnas    
        {
            cout << (*matriz)[i][j]; // Arista (distancia entre ciudad i y ciudad j)
            cout << " ";
        }
     }  
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Función: Seleccionar ciudad de origen
  Parámetros de entrada: Un vector de strings
  Parámetros de salida: Entero
  Resumen: Se muestra una lista de ciudades para que el usuario elija desde
           que ciudad partirá. 
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */ 
// Elegimos un origen y lo devolvemos
int seleccionar_origen(vector<string>* nombres, int n)
{
    int nuevoorigen; // Ciudad elegida
    string auxciudad; // Variable auxiliar para capturar nombre de ciudad
    
    // Visualización por pantalla
    system("cls");
    cout << "\n\n";
    cout << "Por favor seleccione la ciudad de partida: " << "\n\n";
    
    // Mostrando listado de ciudades
    while (n < (*nombres).size())
    {
    auxciudad =  devolver_ciudad(&(*nombres), n);
    cout << n << "- " << auxciudad << "\n"; 
    n++; 
    }
    
    cout << "\n" << "Origen: ";
    
    cin >> nuevoorigen; // Almacenamos la ciudad de partida
    
    if (nuevoorigen <0 || nuevoorigen > 46) // Comprobación de que la opción sea válida
    {
       cout << "\n\n" << "Opcion no v\xA0lida" << "\n\n";
       system("pause");
       fflush(stdin); // Limpiando búffer de memoria
       nuevoorigen = seleccionar_origen(&(*nombres),0); // Al no haber sido válida la opción, recursivamente volvemos a solicitar la ciudad de partida            
    }
    
    return nuevoorigen; // Devolvemos la ciudad elegida por el usuario
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimento: Menú principal
  Parámetros de entrada: Matriz, 2 vectores de enteros, 2 enteros.
  Resumen: Aquí el usuario decidirá entre seleccionar una ciudad de origen, ver
           cuál es la ciudad óptima para partir, reiniciar la aplicación, o 
           salir de la misma.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void menu(vector <vector<int> > *matriz, int siz, vector<int>* visitadas, vector<int>* recorrido, int origen, vector<string>* nombres)
{
     // Variables locales
     int op; // Opción del switch
     int auxdist; // Variable donde guardaremos el resultado del cálculo del kilometraje del recorrido
     int ciudadoptima; // Variable donde guardaremos el resultado del cálculo de la ciudad de partida óptima
     string ciu; // Variable donde guardaremos el nombre de la ciudad óptima de partida
     int minrecorrido = 999999; // Variable de sobreescritura del recorrido mínimo
     int i = 0; // Índice
     //vector <int> 
     
     // Visualización por pantalla
     system("cls");
     cout << "Elija una operaci\xA2n:";
     cout << "\n\n";
     cout << "1) Seleccionar ciudad de partida ";
     cout << "\n";
     cout << "2) Determinar ciudad de partida \xA2ptima ";
     cout << "\n";
     cout << "3) Reiniciar la aplicaci\xA2n ";
     cout << "\n";
     cout << "4) Salir de la aplicaci\xA2n ";
     cout << "\n";
     
     fflush(stdin); // Limpiando búffer de memoria
     
     cin >> op; // Almacenamos la opción elegida por el usuario

     switch (op) // Bifurcación del flujo del programa según la opción
     {
            case 1:
                 // Elegir una cuidad de partida y calcular el recorrido
                 origen = seleccionar_origen(&(*nombres),0); // Seleccionamos origen
                 ciu = devolver_ciudad(&(*nombres), origen);
                 cout << "\n" << "Ciudad de origen: " << ciu; // Mostramos ciudad de origen
                 problema_viajante(&(*matriz), siz, &(*visitadas), &(*recorrido), origen); // LLamada al algoritmo del viajero
                 cout << "\n\n";
                 //ver_vector(&(*recorrido), siz+1); // Mostramos recorrido
                 recorrido_verticesyaristas(&(*recorrido), &(*nombres)); // Mostramos recorrido
                 cout << "\n\n";
                 auxdist = determinar_distanciatotal(&(*recorrido)); // LLamada a la función que determina los km recorridos
                 cout << "Distancia total recorrida: " << auxdist << " km"; // Mostramos los km recorridos
                 cout << "\n\n"; // |
                 system("pause");// |- En espera
                 // Volviendo a menú
                 fflush(stdin);
                 (*recorrido).clear(); // Renovamos vector solución
                 (*visitadas).clear(); // Renovamos el vector ciudades visitadas
                 inicializar_visitadas(&(*visitadas), siz); // Reinicializamos las ciudades visitadas a 0
                 menu(&(*matriz), siz, &(*visitadas), &(*recorrido), origen, &(*nombres));
                 break;
            case 2:
                 // Determinar ciudad óptima de salida
                 while (i < siz) // Recorreremos todas las ciudades
                 {
                     // Calculando todas las rutas  
                     cout << "\n" << "Ciudad de partida: " << i;  
                     problema_viajante(&(*matriz), siz, &(*visitadas), &(*recorrido), i); // LLamada al algoritmo del viajero
                     cout << "\n\n";
                     //ver_vector(&(*recorrido), siz+1); // Mostramos recorrido
                     recorrido_verticesyaristas(&(*recorrido), &(*nombres)); // Mostramos recorrido
                     cout << "\n\n";
                     auxdist = determinar_distanciatotal(&(*recorrido)); // Mostramos la distancia total recorrida
                     cout << "Distancia total recorrida: " << auxdist << " km" << "\n\n";
                     (*recorrido).clear(); // Renovamos vector solución
                     (*visitadas).clear(); // Renovamos el vector ciudades visitadas
                     inicializar_visitadas(&(*visitadas), siz); // Reinicializamos las ciudades visitadas a 0
                     // Determinando ruta óptima
                     if (auxdist < minrecorrido) // Si la última distancia recorrida es menor que el valor del recorrido mínimo
                     {
                        minrecorrido = auxdist; // Se actualiza el recorrido mínimo
                        ciudadoptima = i;       // Se actualiza la ciudad óptima de partida          
                     }
                     i++; // Aumentamos índice para el bucle
                 }
                 ciu = devolver_ciudad(&(*nombres), ciudadoptima); // Mostramos el resultado por pantalla.
                 cout << "\n\n\n";
                 cout << "- Ciudad \xA2ptima de partida: " << ciu << "\n" << "- Kil\xA2metros recorridos en esa ruta: " << minrecorrido;
                 cout << "\n\n"; // |
                 system("pause");// |- En espera
                 // Volviendo a menú
                 fflush(stdin);
                 (*recorrido).clear(); // Renovamos vector solución
                 (*visitadas).clear(); // Renovamos el vector ciudades visitadas
                 inicializar_visitadas(&(*visitadas), siz); // Reinicializamos las ciudades visitadas a 0
                 menu(&(*matriz), siz, &(*visitadas), &(*recorrido), origen, &(*nombres));
                 break;
            case 3:
                 // Volver al menú principal
                 cout << "\n\n";
                 system("pause");
                 fflush(stdin); 
                 main();
                 break;
            case 4:
                 // Salir de la aplicación
                 cout << "\n\n" << "El programa finalizar\xA0" << "\n";
                 system("pause");
                 exit(1); // Salir de la aplicación
                 break;
            default:
                 cout << "Ha elegido una operacion inv\xA0lida" << "\n\n";
                 system("pause");
                 fflush(stdin);
                 menu(&(*matriz), siz, &(*visitadas),&(*recorrido), origen, &(*nombres));           
     }    

}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Activar vector de ciudades "visitadas"
  Parámetros de entrada: Vector de enteros y entero.
  Resumen: Inicializar el vector de las ciudades visitadas con "siz" número de 
           ceros (no visitadas).
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void inicializar_visitadas(vector<int>* visitadas, int siz)
{
     int i;
     
     for (i = 0; i < siz; i++)
     {
         (*visitadas).push_back(0);    
     }
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Visualizar un vector por pantalla
  Parámetros de entrada: Vector
  Resumen: Recorrido de un vector cualquiera mostrándolo por pantalla
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void ver_vector(vector<int>* v, int t)
{
     int i;     

     for (i = 0; i < (*v).size(); i++)
     {
         cout << (*v)[i] << " ";   
     }
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Función: Calcular la distancia total de un recorrido
  Parámetros de entrada: Vector de enteros
  Parámetros de salida: Entero
  Resumen: Recorre el vector del recorrido acumulando los valores de las 
           posiciones pares del vector, para posteriormente devolver el 
           resultado; la suma de los pesos de las aristas.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
int determinar_distanciatotal(vector<int>* recorrido)
{
    int i, dist = 0;
    
    for (i = 0; i < (*recorrido).size(); i++)
    {
        if ( i % 2 != 0) // Las aristas están en posiciones pares
        {
            dist = dist + (*recorrido)[i]; // Acumulación de kilómetros   
        }    
    }    
    
    return dist; // Devolvemos el sumatorio de los pesos de las aristas (total kilometraje)
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Carga de los nombres de las ciudades
  Parámetros de entrada: Vector de strings
  Resumen: Recibe un vector de strings y lo carga con los nombres de las
           ciudades. Requiere de un pequeño apaño para poder escribir correcta-
           mente "La Coruña".
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
// Establecer los nombres de las ciudades
void nombrar(vector<string>* nombres)
{
     // Escribiendo correctamente "La Coruña".
     stringstream ss; // Concatenar
     string s; // Variable donde guardaremos la concatenación
     ss << "La Coru" << "\xA4" << "a"; // Concatenación
     s = ss.str(); // Guardando la concatenación
     
     
     // Introduciendo nombres de ciudades en el vector
     
     (*nombres).push_back("Albacete");
    (*nombres).push_back("Alicante");
    (*nombres).push_back("Almer\xA1""a");
    (*nombres).push_back("\xA0vila"); // No he encontrado como usar tíldes en mayúsculas
    (*nombres).push_back("Badajoz");
    (*nombres).push_back("Barcelona");
    (*nombres).push_back("Bilbao");
    (*nombres).push_back("Burgos");
    (*nombres).push_back("C\xA0""ceres");
    (*nombres).push_back("C\xA0""diz");
    (*nombres).push_back("Castell\xA2n");
    (*nombres).push_back("Ciudad Real");
    (*nombres).push_back("C\xA2rdoba");
    (*nombres).push_back(s); // La Coruña
    (*nombres).push_back("Cuenca");
    (*nombres).push_back("Gerona");
    (*nombres).push_back("Granada");
    (*nombres).push_back("Guadalajara");
    (*nombres).push_back("Huelva");
    (*nombres).push_back("Huesca");
    (*nombres).push_back("Ja\x82n");
    (*nombres).push_back("Le\xA2n");
    (*nombres).push_back("L\x82rida");
    (*nombres).push_back("Logro\xA4o");
    (*nombres).push_back("Lugo");
    (*nombres).push_back("Madrid");
    (*nombres).push_back("M\xA0laga");
    (*nombres).push_back("Murcia");
    (*nombres).push_back("Orense");
    (*nombres).push_back("Oviedo");
    (*nombres).push_back("Palencia");
    (*nombres).push_back("Pamplona");
    (*nombres).push_back("Pontevedra");
    (*nombres).push_back("Salamanca");
    (*nombres).push_back("San Sebasti\xA0n (Donostia)");
    (*nombres).push_back("Santander");
    (*nombres).push_back("Segovia");
    (*nombres).push_back("Sevilla");
    (*nombres).push_back("Soria");
    (*nombres).push_back("Tarragona");
    (*nombres).push_back("Teruel");
    (*nombres).push_back("Toledo");
    (*nombres).push_back("Valencia");
    (*nombres).push_back("Valladolid");
    (*nombres).push_back("Vitoria (Gasteiz)");
    (*nombres).push_back("Zamora");
    (*nombres).push_back("Zaragoza");
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Recorrer el vector de la solución
  Parámetros de entrada: Vector de enteros, vector de strings
  Resumen: Se recorre el vector de la solución y dependiendo de si estamos en
           una arista o en un vértice se llamará a la función que devuelve el 
           nombre de la ciudad.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void recorrido_verticesyaristas(vector<int>* recorrido, vector<string>* nombres)
{
    int i; // Índice
    string tem; // Nombre de la ciudad requerida
    
    for (i = 0; i < (*recorrido).size(); i++)
    {

            if (i % 2 == 0) // Se requiere el nombre de ciudad (vértice)
            {
                 tem = devolver_ciudad(&(*nombres), (*recorrido)[i]);
                 cout << tem << " ";        
            }
            if (i  % 2 != 0) // Se requiere distancia entre ciudades (arista)
            {
                 cout << (*recorrido)[i] << " km " << "-> "; 
            } 
    }           
} 

/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Función: Devolver el nombre de la ciudad
  Parámetros de entrada: Vector de strings, entero
  Parámetros de salida: string
  Resumen: Esta función devuelve el string del vector de strings en la posición
           n. El vector y la posición son pasados como parámetro de entrada.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
string devolver_ciudad(vector <string>* nombres, int n)
{
      return (*nombres)[n];        
}
