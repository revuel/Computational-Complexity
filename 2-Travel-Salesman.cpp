/* �����������������������������������������������������������������������������
   
   T�tulo: Pr�ctica 2, El problema del viajero. ("Travel Salesman Problem")
   
   Resumen: Solucionar el Problema del viajero mediante el algoritmo del
            vecino m�s cercano.
   
   Asignatura: Complejidad Computacional
   Profesor: �ngel Serrano S�nchez de Le�n
   Alumno: Miguel Revuelta Espinosa (revuel22@hotmail.com)
   Fecha: 6/11/2013 - 5/12/2013
   
����������������������������������������������������������������������������� */

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   LIBRER�AS Y ESPACIOS DE NOMBRES
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
#include <sstream>    // |
#include <fstream>    // |- Librer�as tratamiento de ficheros
#include <string.h>   // |
#include <stdlib.h>   // Para usar la funci�n "system("")"
#include <iostream>   // Para usar las funciones cin & cout
#include <vector>     // Para usar la clase vector

using namespace std;  // Para reconocer librer�as de la STL (vector)


/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   DECLARACI�N DE FUNCIONES DE LA APLICACI�N
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
// Mostrar un men� y seleccionar opci�n, para posterior ejecuci�n de operaciones
void menu(vector <vector<int> > *, int, vector<int>*, vector<int>*, int, vector<string>*);
      
// Cargar datos desde un .txt en nuestra matriz
int cargar_matriz(vector <vector<int> > *);

// Visualizar por consola una matriz 
void mostrar_matriz(vector <vector<int> > *, int); 

// Funci�n que decide el recorrido
// (Ciudades, n�mero de ciudades, visitadas, recorrido, ciudad de origen, distancia total)
void problema_viajante(vector <vector<int> > *, int, vector<int>*, vector<int>*, int);

// Funci�n que haya la ciudad vecina m�s cercana
// (Ciudades, n�mero de ciudades, ciudad actual, visitadas)
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
   FUNCI�N PRINCIPAL (MAIN)
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
int main(void)
{
    // Declaraciones de variables
    
    int siz; // Tama�o de la matriz, (n�mero de ciudades)
    int origen; // Ciudad de partida
    vector <vector<int> > matriz; // Nuestra matriz de adyacencia (aristas)
    vector <int> fila; // Cada fila de la matriz ser� un vector
    vector <int> visitadas; // (0,1) indicar� que ciudades fueron visitadas
    vector <int> recorrido; // Soluci�n ciudades (v�rices)
    vector <string> nombres; // Nombres de las ciudades
    

    // Inicio del flujo del programa
    
    // Parte 1 (Carga de datos)
    nombrar(&nombres); // Cargar el vector de los nombres de las ciudades
    siz = cargar_matriz(&matriz); // Cargamos la matriz y devolvemos el n�mero de ciudades
    cout << "\n\n\n" << "N\xA3mero de ciudades: " << siz; // Mostramos el n�mero de ciudades
    cout << "\n\n";
    cout << "Matriz de adyacencia cargada con \x82xito:";
    cout << "\n";
    mostrar_matriz(&matriz,siz); // Mostramos la matriz de adyacencia
    cout << "\n\n";
    system("pause");

    // Parte 2 (Operaciones)
    //nombrar(&nombres);
    inicializar_visitadas(&visitadas, siz); // Inicializamos el estado de las ciudades
    menu(&matriz, siz, &visitadas, &recorrido, origen, &nombres); // Nos trasladamos al men� de opciones
    
    // Saliendo de la aplicaci�n
    cout << "\n\n" << "El programa finalizar\xA0" << "\n";
    system("pause");
    return 0;
}


/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   FUNCIONES Y PROCEDIMIENTOS DE LA PR�CTICA
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Problema del viajante
  Par�metros de entrada: Matriz, 2 vectores de enteros, 2 enteros
  Resumen: Calcula el recorrido desde una ciudad de partida usando el algoritmo
           del vecino m�s cercano.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void problema_viajante(vector <vector<int> > *matriz, int siz, vector<int> *visitadas, vector<int> *recorrido, int origen)
{
    // Variables locales
    int i; // �ndice 
    int ciudadactual = origen; // Ciudad actual (la primera es el origen)
    int ciudadanterior; // �ltima ciudad visitada
    int auxdistancia; // Distancia entre ciudades (arista)
    
    (*recorrido).push_back(ciudadactual);    // A�adiendo el origen a la soluci�n
    
    // A�adiendo ciudades al recorrido
    for (i = 0; i < siz-1; i++) // Explicar la perplejidad en la memoria sobre siz-1
    {
        ciudadanterior = ciudadactual; // La �ltima ciudad es la actual
        (*visitadas)[ciudadanterior] = 1; // La ciudad actual es visitada
        ciudadactual = maxcercana(&(*matriz), siz, ciudadanterior, &(*visitadas)); // El kit de la cuesti�n, seguir pasando referencias
        
        auxdistancia = (*matriz)[ciudadanterior][ciudadactual]; // Determinando distancia entre ciudades (arista)
        (*recorrido).push_back(auxdistancia); // A�adiendo distancia a la soluci�n (arista)
        (*recorrido).push_back(ciudadactual); // Guardando la nueva ciudad actual (v�rcice)        
    }
    auxdistancia = (*matriz)[ciudadactual][origen];// |
    (*recorrido).push_back(auxdistancia);          // |- A�adiendo �ltima arista y �ltimo vertice (vuelta a casa)
    (*recorrido).push_back(origen);                // |
}

/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Funci�n: C�lculo de la vecina m�s cercana
  Par�metros de entrada: Matriz, vector de enteros, 2 enteros.
  Par�metros de salida: Entero
  Resumen: Esta funci�n haya la ciudad m�s cercana que no haya sido visitada, 
           y devuelve la posici�n de dicha ciudad.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
int maxcercana(vector <vector<int> > *matriz, int siz, int cactual, vector<int>* visitadas)
{
    int i, j; // �ndices de recorrido la matriz
    int candidata = 999999; // Variable de sobreescritura de la distancia de la ciudad m�s cercana
    int cercana; // Guardaremos la posici�n de la ciudad m�s cercana

    for (j = 0; j < siz; j++) // Recorriendo la fila correspondiente a la ciudad actual
    {
        // Comprobaci�n: �Es la misma ciudad (0)?, �la distancia es menor que la �ltima candidata?, �est� marcada como visitada?
        if ((*matriz)[cactual][j] > 0 && (*matriz)[cactual][j] < candidata && (*visitadas)[j] != 1)
        {
           candidata = (*matriz)[cactual][j]; // Nueva menor distancia encontrada
           cercana = j; // Nueva ciudad m�s cercana encontrada
          
        } 
    }    
    return cercana; // Devolvemos ciudad m�s cercana   
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Funci�n: Cargar datos en la matriz
  Par�metros de entrada: Matriz
  Par�metros de salida: Entero
  Resumen: Cargamos los datos desde un fichero para guardarlos en nuestra matriz 
           y devolvemos el n�mero de ciudades (l�neas leidas).
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
int cargar_matriz(vector <vector<int> > *matriz)
{
   // Variables locales
   ifstream inFile("tcc.txt"); // Seleccionar archivo
   string line; // Iremos leyendo l�nea a l�nea
   int linenum = 0; // Contaremos las l�neas leidas
   int aux; // Variable auxiliar donde volcaremos conversiones string a int
   vector <int> fila; // Vector de llenado de filas para la matriz
   
   // Lectura del fichero (l�nea a l�nea)
   while (getline (inFile, line))  
   { 
         linenum++;
         cout << "\nCiudad: " << linenum << ":" << endl; 
         istringstream linestream(line); 
         string item; // Variable para formateo de l�neas de fichero
         int itemnum = 1; // Variable contador del n�mero de items por l�nea
         
         // Lectura de items: car�cter de discriminaci�n: espacio
         while (getline (linestream, item, ' '))
         { 
               cout << "Distancia a: " << itemnum << ": " << item << endl;
               itemnum++; // Pasamos al siguiente item de la l�nea
               
               istringstream (item) >> aux; // Conversi�n de string a integer
               fila.push_back(aux); // A�adiendo enteros a vector
         } 
         (*matriz).push_back(fila); // A�adiendo vectores la matriz
         fila.clear(); // Borramos la fila para reutilizarla en la siguiente iteraci�n
   }
   return linenum; // Devolvemos la cantidad de l�neas leidas (es decir, el n�mero de ciudades)
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Mostrar una matriz
  Par�metros de entrada: Matriz, entero.
  Resumen: Este procedimiento recorre una mariz mostr�ndola por pantalla
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void mostrar_matriz(vector <vector<int> > *matriz, int siz)
{
     int i, j; // �ndices
     
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
  Funci�n: Seleccionar ciudad de origen
  Par�metros de entrada: Un vector de strings
  Par�metros de salida: Entero
  Resumen: Se muestra una lista de ciudades para que el usuario elija desde
           que ciudad partir�. 
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */ 
// Elegimos un origen y lo devolvemos
int seleccionar_origen(vector<string>* nombres, int n)
{
    int nuevoorigen; // Ciudad elegida
    string auxciudad; // Variable auxiliar para capturar nombre de ciudad
    
    // Visualizaci�n por pantalla
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
    
    if (nuevoorigen <0 || nuevoorigen > 46) // Comprobaci�n de que la opci�n sea v�lida
    {
       cout << "\n\n" << "Opcion no v\xA0lida" << "\n\n";
       system("pause");
       fflush(stdin); // Limpiando b�ffer de memoria
       nuevoorigen = seleccionar_origen(&(*nombres),0); // Al no haber sido v�lida la opci�n, recursivamente volvemos a solicitar la ciudad de partida            
    }
    
    return nuevoorigen; // Devolvemos la ciudad elegida por el usuario
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimento: Men� principal
  Par�metros de entrada: Matriz, 2 vectores de enteros, 2 enteros.
  Resumen: Aqu� el usuario decidir� entre seleccionar una ciudad de origen, ver
           cu�l es la ciudad �ptima para partir, reiniciar la aplicaci�n, o 
           salir de la misma.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void menu(vector <vector<int> > *matriz, int siz, vector<int>* visitadas, vector<int>* recorrido, int origen, vector<string>* nombres)
{
     // Variables locales
     int op; // Opci�n del switch
     int auxdist; // Variable donde guardaremos el resultado del c�lculo del kilometraje del recorrido
     int ciudadoptima; // Variable donde guardaremos el resultado del c�lculo de la ciudad de partida �ptima
     string ciu; // Variable donde guardaremos el nombre de la ciudad �ptima de partida
     int minrecorrido = 999999; // Variable de sobreescritura del recorrido m�nimo
     int i = 0; // �ndice
     //vector <int> 
     
     // Visualizaci�n por pantalla
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
     
     fflush(stdin); // Limpiando b�ffer de memoria
     
     cin >> op; // Almacenamos la opci�n elegida por el usuario

     switch (op) // Bifurcaci�n del flujo del programa seg�n la opci�n
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
                 auxdist = determinar_distanciatotal(&(*recorrido)); // LLamada a la funci�n que determina los km recorridos
                 cout << "Distancia total recorrida: " << auxdist << " km"; // Mostramos los km recorridos
                 cout << "\n\n"; // |
                 system("pause");// |- En espera
                 // Volviendo a men�
                 fflush(stdin);
                 (*recorrido).clear(); // Renovamos vector soluci�n
                 (*visitadas).clear(); // Renovamos el vector ciudades visitadas
                 inicializar_visitadas(&(*visitadas), siz); // Reinicializamos las ciudades visitadas a 0
                 menu(&(*matriz), siz, &(*visitadas), &(*recorrido), origen, &(*nombres));
                 break;
            case 2:
                 // Determinar ciudad �ptima de salida
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
                     (*recorrido).clear(); // Renovamos vector soluci�n
                     (*visitadas).clear(); // Renovamos el vector ciudades visitadas
                     inicializar_visitadas(&(*visitadas), siz); // Reinicializamos las ciudades visitadas a 0
                     // Determinando ruta �ptima
                     if (auxdist < minrecorrido) // Si la �ltima distancia recorrida es menor que el valor del recorrido m�nimo
                     {
                        minrecorrido = auxdist; // Se actualiza el recorrido m�nimo
                        ciudadoptima = i;       // Se actualiza la ciudad �ptima de partida          
                     }
                     i++; // Aumentamos �ndice para el bucle
                 }
                 ciu = devolver_ciudad(&(*nombres), ciudadoptima); // Mostramos el resultado por pantalla.
                 cout << "\n\n\n";
                 cout << "- Ciudad \xA2ptima de partida: " << ciu << "\n" << "- Kil\xA2metros recorridos en esa ruta: " << minrecorrido;
                 cout << "\n\n"; // |
                 system("pause");// |- En espera
                 // Volviendo a men�
                 fflush(stdin);
                 (*recorrido).clear(); // Renovamos vector soluci�n
                 (*visitadas).clear(); // Renovamos el vector ciudades visitadas
                 inicializar_visitadas(&(*visitadas), siz); // Reinicializamos las ciudades visitadas a 0
                 menu(&(*matriz), siz, &(*visitadas), &(*recorrido), origen, &(*nombres));
                 break;
            case 3:
                 // Volver al men� principal
                 cout << "\n\n";
                 system("pause");
                 fflush(stdin); 
                 main();
                 break;
            case 4:
                 // Salir de la aplicaci�n
                 cout << "\n\n" << "El programa finalizar\xA0" << "\n";
                 system("pause");
                 exit(1); // Salir de la aplicaci�n
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
  Par�metros de entrada: Vector de enteros y entero.
  Resumen: Inicializar el vector de las ciudades visitadas con "siz" n�mero de 
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
  Par�metros de entrada: Vector
  Resumen: Recorrido de un vector cualquiera mostr�ndolo por pantalla
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
  Funci�n: Calcular la distancia total de un recorrido
  Par�metros de entrada: Vector de enteros
  Par�metros de salida: Entero
  Resumen: Recorre el vector del recorrido acumulando los valores de las 
           posiciones pares del vector, para posteriormente devolver el 
           resultado; la suma de los pesos de las aristas.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
int determinar_distanciatotal(vector<int>* recorrido)
{
    int i, dist = 0;
    
    for (i = 0; i < (*recorrido).size(); i++)
    {
        if ( i % 2 != 0) // Las aristas est�n en posiciones pares
        {
            dist = dist + (*recorrido)[i]; // Acumulaci�n de kil�metros   
        }    
    }    
    
    return dist; // Devolvemos el sumatorio de los pesos de las aristas (total kilometraje)
}
/* -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
  Procedimiento: Carga de los nombres de las ciudades
  Par�metros de entrada: Vector de strings
  Resumen: Recibe un vector de strings y lo carga con los nombres de las
           ciudades. Requiere de un peque�o apa�o para poder escribir correcta-
           mente "La Coru�a".
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
// Establecer los nombres de las ciudades
void nombrar(vector<string>* nombres)
{
     // Escribiendo correctamente "La Coru�a".
     stringstream ss; // Concatenar
     string s; // Variable donde guardaremos la concatenaci�n
     ss << "La Coru" << "\xA4" << "a"; // Concatenaci�n
     s = ss.str(); // Guardando la concatenaci�n
     
     
     // Introduciendo nombres de ciudades en el vector
     
     (*nombres).push_back("Albacete");
    (*nombres).push_back("Alicante");
    (*nombres).push_back("Almer\xA1""a");
    (*nombres).push_back("\xA0vila"); // No he encontrado como usar t�ldes en may�sculas
    (*nombres).push_back("Badajoz");
    (*nombres).push_back("Barcelona");
    (*nombres).push_back("Bilbao");
    (*nombres).push_back("Burgos");
    (*nombres).push_back("C\xA0""ceres");
    (*nombres).push_back("C\xA0""diz");
    (*nombres).push_back("Castell\xA2n");
    (*nombres).push_back("Ciudad Real");
    (*nombres).push_back("C\xA2rdoba");
    (*nombres).push_back(s); // La Coru�a
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
  Procedimiento: Recorrer el vector de la soluci�n
  Par�metros de entrada: Vector de enteros, vector de strings
  Resumen: Se recorre el vector de la soluci�n y dependiendo de si estamos en
           una arista o en un v�rtice se llamar� a la funci�n que devuelve el 
           nombre de la ciudad.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
void recorrido_verticesyaristas(vector<int>* recorrido, vector<string>* nombres)
{
    int i; // �ndice
    string tem; // Nombre de la ciudad requerida
    
    for (i = 0; i < (*recorrido).size(); i++)
    {

            if (i % 2 == 0) // Se requiere el nombre de ciudad (v�rtice)
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
  Funci�n: Devolver el nombre de la ciudad
  Par�metros de entrada: Vector de strings, entero
  Par�metros de salida: string
  Resumen: Esta funci�n devuelve el string del vector de strings en la posici�n
           n. El vector y la posici�n son pasados como par�metro de entrada.
-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   - */
string devolver_ciudad(vector <string>* nombres, int n)
{
      return (*nombres)[n];        
}
