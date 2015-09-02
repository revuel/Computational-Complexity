/* _____________________________________________________________________________
 Nombre: Miguel Revuelta Espinosa                                                                           
 Asignatura: Complejidad Computacional
 Curso: 2º Ingeniería Informática
 Fecha: 15/10/2013 - 
 Título: PRÁCTICA 1
______________________________________________________________________________*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                LIBRERÍAS

#include<stdio.h>     // Funciones printf(), scanf()...
#include<stdlib.h>    // Funciones rand(), system("pause"), system("cls")...
#include<vector>      // Clase vector...
#include <iostream> // Funciones cin cout...

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                  ESTRUCTURAS, CABECERAS, VARIABLES GLOBALES

// Variables Globales

vector <int> mivector;
vector<int> salvavector;
//vector <int> vectoraux;
vector <int> aux;



// Cabeceras de funciones y procedimientos

void pintamenu_elegir_llenado();      // Imprimir menú selección vector
void menu_llenar();                   // Menú de selección vector

void pintamenu_elegir_ordenacion();   // Imprimir menú selección ordenación
void menu_ordenar();                  // Menú de selección vector

void llenar_vector();                 // Llenar un vector con enteros (teclado)
void llenar_aleatorio();              // Generación de un vector aleatorio
void imprimir_vector(vector<int>);    // Mostrar un vector por pantalla

void ordenar_insercion(vector <int>*, int); // Insertion Sort

void ordena_rapido(vector<int>*, int, int); // Quick sort
int particionar(vector<int>*, int, int);    // Particionar

//void ordena_mezcla(vector <int>*, vector<int>*, int,int); Ver memoria
//void fusion (vector<int>*, vector<int>*, int, int, int);  Ver memoria
void mergeSort(vector <int>&,vector<int>&, int, int);
void combine( vector <int>&,vector <int>&, int, int, int);

// Variables para estadísticas (Ver memoria para detalles)
int nefis = 0;  //
int newis = 0;  // Variables para el insertion
int niis = 0;   //

int nefqs = 0;  //
int niqs = 0;   // Variables para el quicksort
int nllrqs = 0; //
int nnrqs = 0;  //

int nefms = 0;  //
int newms = 0;  //
int neobms = 0; // Variables para el merge sort
int nims = 0;   //
int nllrms = 0; //
int nnrms = 0;  //


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                    MAIN

// Función principal
int main(void)
{
     vector <int> copiaglobal;
     
     
     pintamenu_elegir_llenado();    // Ver opciones de llenado        
     
     salvavector = mivector;
     
     pintamenu_elegir_ordenacion(); // Elegir estilo de ordenación
     
     cout << "\n";
     cout << "\n";
     system("pause");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                         CUERPOS DE FUNCIONES Y PROCEDIMIENTOS

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Imprimir opciones de llenado
// PARÁMETROS DE ENTRADA: vacío
// PARÁMETROS DE SALIDA: ninguno
// DESCRIPCIÓN: Este procedimiento tras limpiar la consola de comandos imprime 
// por pantalla una serie de opciones. Llama al procedimiento "menu_llenar"

void pintamenu_elegir_llenado()
{
     // Debido al flujo de la aplicacion, las variables de estadística se 
     // reinician aquí a cero
     nefis = 0, newis = 0, niis = 0;
     nefqs = 0, niqs = 0, nllrqs = 0, nnrqs = 0;
     nefms = 0, newms = 0, nims = 0, nllrms = 0, nnrms = 0;
     // También deben reincializarse las demás variables globales
     mivector.clear();
     salvavector.clear();
     aux.clear();
     
     system("cls"); // Limpiamos la consola
     cout << "\n";
     cout << "\t";
     cout << "Seleccione una operaci\xA2n para continuar:";
     cout << "\n";
     cout << "\n";
     cout << "1) Crear vector: elegir su tama\xA4o y valores por teclado.";
     cout << "\n";
     cout << "2) Crear vector: elegir su tama\xA4o, valores aleatorios.";
     cout << "\n";
     cout << "3) Salir de la aplicaci\xA2n.";
     cout << "\n\t";  
     
     
     menu_llenar();  
}

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Seleccionar creación de vector
// PARÁMETROS DE ENTRADA: vacío
// PARÁMETROS DE SALIDA: ninguno
// DESCRIPCIÓN: Este procedimiento mediante un switch permitirá al usuario ele-
// gir entre llenar un vector manualmente por teclado, o que la aplicación gene-
// re un vector con valores aleatorios. Llama a los procedimientos
// "llenar_vector" y "generar_vector"
void menu_llenar()
{
     cout << "\n";
     cout << "Opcion: ";
     int op; // Variable donde se guardará la opción elegida por el usuario
     
     cin >> op;
     fflush(stdin); // Limpiando el buffer de memoria
     
     switch (op)
     {
            case 1: // Caso "llenar vector manualmente"
                 cout << "Ha elegido generar un vector manualmente";
                 cout << "\n";
                 cout << "\n";
                 llenar_vector();
                 cout << "\n";
                 system("pause");
                 break;
            case 2: // Caso "generar vector aleatorio"
                 cout << "Ha elegido generar un vector aleatoriamente";
                 cout << "\n";
                 cout << "\n";
                 llenar_aleatorio();
                 cout << "\n";
                 system("pause");
                 break;
            case 3: // Salir de la aplicación
                 exit(1);
                 break;
            default: // El usuario no ha elegido una opción determinada
                 cout << "Ha elegido una opcion no valida";
                 cout << "\n";
                 system("pause");
                 cout << "\n";
                 fflush(stdin);
                 pintamenu_elegir_llenado();                      
     }     
}

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Imprimir opciones ordenación
// PARÁMETROS DE ENTRADA: vacío
// PARÁMETROS DE SALIDA: ninguno
// DESCRIPCIÓN: Este procedimiento tras limpiar la consola de comandos imprime 
// por pantalla una serie de opciones. Llama al procedimiento "menu_ordenar"

void pintamenu_elegir_ordenacion(void)
{
    system("cls"); // Limpiamos la consola
    imprimir_vector(mivector);
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\t";
    cout << "\xA8Qu\x82 tipo de algoritmo de ordenaci\xA2n desea utilizar?";
    cout << "\n";
    cout << "\n";
    cout << "1) Ordenamiento por inserci\xA2n.";
    cout << "\n";
    cout << "2) Ordenamiento por mezcla.";
    cout << "\n";
    cout << "3) Ordenamiento r\xA0pido.";
    cout << "\n";
    cout << "4) Volver atr\xA0s.";
    cout << "\n\t";
    
    menu_ordenar();                                                              
}

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Elegir método de ordenación
// PARÁMETROS DE ENTRADA: vacío
// PARÁMETROS DE SALIDA: ninguno
// DESCRIPCIÓN: Este procedimiento mediante un switch permitirá al usuario ele-
// gir entre ordenar un vector mediante tres técnicas distintas de ordenación.
// Llama a los procedimientos "ordenar_insercion", "ordenar_rapido" y
// "ordenar_mezcla"

void menu_ordenar()
{
     cout << "\n";
     cout << "Opci\xA2n: ";
     int op;
     vector <int> copialocal;
     vector <int> aux;
     aux.resize(mivector.size());
     copialocal = salvavector;
     
     int p = 0;
     int q = mivector.size()-1;
     
     cin >> op;
     fflush(stdin);
     
     switch (op)
     {
            case 1:
                 cout << "Ha elegido ordenar por inserci\xA2n.";
                 cout << "\n";
                 system("pause");
                 ordenar_insercion(&salvavector,salvavector.size());
                 cout << "\n";
                 imprimir_vector(salvavector);
                 
                 cout << "\n";
                 cout << "Estadisticas algoritmo Insercion";
                 cout << "\n\n";
                 cout << "Entradas al FOR: " << nefis << "\tEntradas al WHILE: " << newis << "\tIntercambios: " << niis;
                 cout << "\n";
                 system("pause");
                 pintamenu_elegir_ordenacion();
                 break;
            case 2:
                 cout << "Ha elegido ordenar por mezcla";
                 cout << "\n";
                 system("pause");
                 //ordena_mezcla(&mivector,0,mivector.size());
                 mergeSort(copialocal,aux,p,q);
                 cout << "\n";
                 imprimir_vector(salvavector);
                 
                 cout << "\n";
                 cout << "Estadisticas algoritmo mezcla";
                 cout << "\n\n";
                 cout << "Entradas al FOR: " << nefms << "\tIntercambios: " << nims << "\tLlamadas recursivas: " << nllrms - 1<<"\n"; 
                 cout<<"Llamadas no recursivas: " << nnrms << "\tEntradas a los WHILE: " << newms;
                 cout << "\n";
                 system("pause");
                 pintamenu_elegir_ordenacion();
                 break;
            case 3:
                 cout << "Ha elegido ordenamiento rapido";
                 cout << "\n";
                 system("pause");
                 ordena_rapido(&salvavector,0, salvavector.size());
                 cout << "\n";
                 imprimir_vector(salvavector);
                 
                 cout << "\n";
                 cout << "Estadisticas algoritmo rapido";
                 cout << "\n\n";
                 cout << "Entradas al FOR: " << nefqs << "\tIntercambios: " << niqs << "\tLlamadas recursivas: " << nllrqs - 1<<"\n"; 
                 cout<<"Llamadas no recursivas: " << nnrqs;
                 cout << "\n";
                 system("pause");
                 pintamenu_elegir_ordenacion();
                 break;
            case 4:
                 fflush(stdin);
                 pintamenu_elegir_llenado();
                 break;
            default:
                 cout << "Ha elegido una opcion no valida";
                 cout << "\n";
                 system("pause");
                 cout << "\n";
                 fflush(stdin);
                 pintamenu_elegir_ordenacion();                    
     }                  
}

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Introducir valores por teclado para un vector
// PARÁMETROS DE ENTRADA: ninguno
// PARÁMETROS DE SALIDA: ninguno
// DESCRIPCIÓN: Se le solicita al usuario que determine el tamaño del vector
// para posteriormente pedirle que introduzca valores para el mismo.
void llenar_vector()
{
     // Variables locales
     int aux; // Variable local donde iremos guardando el valor a introducir 
     int i;   // Variable de índice
     int n;
     
     cout << "\n";
     cout << "Elija el tama\xA5o del vector: ";
     cin >> n;
     cout << "\n";
     
     for(i=0; i<n; i++) // LLenado del vector hasta n
     {
          cout <<"Introduzca un nuevo valor: "; // Pedimos dato
          cin >> aux;                           // Guardamos dato
          mivector.push_back(aux);              // Insertamos dato en vector     
     }
     
     cout << "\n";
     
     imprimir_vector(mivector);                             
}
//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Se genera un vector aleatoriamente
// PARÁMETROS DE ENTRADA: ninguno
// PARÁMETROS DE SALIDA: ninguno
// DESCRIPCIÓN: Se le solicita al usuario que determine el tamaño del vector
// para posteriormente el sistema darle valores
void llenar_aleatorio()
{
     int i, random, n;
     
     cout << "\n";
     cout << "Elija el tama\xA5o del vector: ";
     cin >> n;
     cout << "\n";
     
     for (i=0;i<n;i++)
     {
         random = rand()%100;
         mivector.push_back(random);
         
     }
     
     imprimir_vector(mivector);        

}

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Mostrar por pantalla un vector
// PARÁMETROS DE ENTRADA: vector
// PARÁMETROS DE SALIDA: ninguno
// DESCRIPCIÓN: Recibe un vector, y seguún lo recorre va mostrando por pantalla
// sus valores

void imprimir_vector(vector<int> v)
{
     printf("\n\n");
     printf("Vector almacenado: ");
     
     for(vector<int>::iterator it = v.begin(); it < v.end(); it++) // recorrido
     {
          cout << *it << " "; // mostrando posición actual
     }
     cout << "\n";     
}
//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Insertion sort
// PARÁMETROS DE ENTRADA: puntero a vector, un entero
// PARÁMETROS DE SALIDA: entero
// DESCRIPCIÓN: Este procedimiento recorre un vector desde la segunda posición, 
// hasta el final, comparando el valor de la posición actual con todos los demás
// elementos a su izquierda, realizando los intercambios necesarios para ordenar
// dicho vector

void ordenar_insercion(vector<int> *v, int n) 
{
     int i, j, x;
     
     for(i=1; i<n; i++) // Bucle que recorre el vector una vez
     {  
        nefis ++; // Estadistica: Entrada en un for      
        x = v->at(i); // A la variable auxiliar x se le da el valor actual 
        j = i-1;  // Variable del indice del bucle interno
  
        while(j>=0 && v->at(j)>x) // Comparamos con todos a la izquierda
        {                     
            newis++; //Estadística: Entrada en un while                  
            v->at(j+1) = v->at(j); // Vamos moviendo hacia la izquierda
            niis++; // Estadística: Intercambio de variables
            j = j-1;      
                  
        }         
        
        v->at(j+1) = x; // Reposicionamos x en el indice siguiente
        niis++; // Estadística: Intercambio de variables  
     }
}

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Quicksort
// PARÁMETROS DE ENTRADA: puntero a vector, dos enteros
// PARÁMETROS DE SALIDA: ninguno
// DESCRIPCIÓN: Este procedimiento ordena recursivamente un vector, basándose
// en la colocación de los pivotes de los subvectores de las llamadas recur-
// sivas

void ordena_rapido(vector<int> *v, int p, int q)
{
     nllrqs++; // Estadistica: llamada recursiva
     
     int i; // Aquí se almacena la posiciÃ³n definitiva del pivote

     if (p < q) // Si el pivote no está ya colocado
     {   
           i = particionar(v, p, q); // Posición definitiva del pivote
           ordena_rapido(v,p,i);     // Llamadas recursiva
           ordena_rapido(v,i+1,q);   // Llamada recursiva 
     }
}

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// FUNCIÓN: Colocar el pivote en su posición correcta
// PARÁMETROS DE ENTRADA: puntero a vector, dos enteros
// PARÁMETROS DE SALIDA: entero
// DESCRIPCIÓN: Esta función va colocando los elementos posteriores al pivote, 
// y los reordena de menor a mayor, hasta que el pivote alcanza su posicón 
// ordenada en el vector

int particionar(vector<int> *v, int p, int q)
{
    nnrqs++; // Estadistica: llamada NO recursiva
    
    int j;
    int x = v->at(p); // El pivote es el elemento de índice p
    int i = p;    // Posición del pivote
    int aux;      // Variable auxiliar para intercambio

    for (j = p+1; j<q; j++) // Recorrido, los siguientes al pivote
    {   
        nefqs++; // Estadistica: entrada en FOR
           
        if (v->at(j) <= x) // Si el elemento es menor o igual que el pivote
        {
           i = i+1;
           aux = v->at(i);      //
           v->at(i) = v->at(j); // - Zona de intercambio
           v->at(j) = aux;      //
           niqs++; // Estadistica: intercambio de variables
        }    
    }
    
    aux = v->at(p);       //
    v->at(p) = v->at(i);  // - Zona de intercambio
    v->at(i) = aux;       //
    niqs++; // Estadistica: intercambio de variables
         
    return i; // Devolvemos el valor i
}  


//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Merge Sort
// PARÁMETROS DE ENTRADA: un puntero a vector, dos enteros
// PARÁMETROS DE SALIDA: ninguna
// DESCRIPCIÓN: Tenemos
// - El vector original que hemos de ordenar: v
// - La primera posición del vector v: ini
// - El tamaño de v: fin
void mergeSort(vector <int> &v, vector <int> &aux, int inicio, int final)
{
    nllrms++; // Estadística, llamadas recursivas 
    
    int mitad;
    if(final > inicio)
    {
        mitad = (final + inicio) / 2;
        mergeSort(v, aux, inicio, mitad);
        mergeSort(v, aux, mitad+1, final);
        combine(v, aux, inicio, mitad+1, final);
        //imprimir_vector(v);
    }
}
//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: combinar los resultados
// PARÁMETROS DE ENTRADA: dos puntero a vector, tres enteros
// PARÁMETROS DE SALIDA: ninguna
// DESCRIPCIÓN: Tenemos
// - El vector original que hemos de ordenar: v
// - Vector auxiliar: aux
// - La primera posición del vector v: ini
// - Posición central
// - El tamaño de v: fin

void combine( vector <int> &v,vector <int> &aux, int ini, int med, int fin)
{
    nnrms++;// Estadística, llamadas NO recursivas 
    int i, inicio_end, num_elementos, pos_aux;
    inicio_end = med-1;
    pos_aux = ini;
    num_elementos = fin-ini+1;

    while((ini<=inicio_end) &&(med <= fin))
    {
        newms++; // Estadística, entrada al WHILE                    
        if(v[ini] <= v[med])
        {
            aux[pos_aux] = v[ini];
            pos_aux = pos_aux + 1;
            ini=ini+1;
            nims++; // Estadística, colocación de variables
        }
        else
        {
            aux[pos_aux] = v[med];
            pos_aux = pos_aux + 1;
            med = med + 1;
            nims++; // Estadística, colocación de variables
        }
    }
    while(ini<=inicio_end)
    {
        newms++; // Estadística, entrada al WHILE 
        aux[pos_aux] = v[ini];
        ini=ini+1;
        pos_aux = pos_aux + 1;
        nims++; // Estadística, colocación de variables
    }
    while(med <= fin)
    {
        newms++; // Estadística, entrada al WHILE 
        aux[pos_aux] = v[med];
        med = med + 1;
        pos_aux = pos_aux + 1;
        nims++; // Estadística, colocación de variables

    }
    
    for(i=0; i <= num_elementos; i++)
    {
        nefms++; // Estadística, iteraciones del for     
        v[fin] = aux[fin];
        fin=fin-1;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                               OTROS

// Aquí está comentada otra implementación de merge que no me funciona :(
// Ver la memoria para mas detalles

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: Merge Sort
// PARÁMETROS DE ENTRADA: un puntero a vector, dos enteros
// PARÁMETROS DE SALIDA: ninguna
// DESCRIPCIÓN: Tenemos
// - El vector original que hemos de ordenar: v
// - La primera posición del vector v: ini
// - El tamaño de v: fin
/*void ordena_mezcla(vector<int> *v, int ini, int fin)
{
     int mitad; // Variable donde alojaremos el resultado del cálculo de v
     
     if (fin > ini)
     {
        mitad = (ini + fin)/2; // Cálculo de la posición central
        
        ordena_mezcla(v, ini, mitad);    // Llamada recursiva
        ordena_mezcla(v, mitad+1, fin);  // Llamada recursiva
        fusion(v, ini, mitad, fin);      // Combinar los resultados     
     }
} 

//~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~  ~~
// PROCEDIMIENTO: combinar los resultados
// PARÁMETROS DE ENTRADA: un puntero a vector, tres enteros
// PARÁMETROS DE SALIDA: ninguna
// DESCRIPCIÓN: Tenemos
// - El vector original que hemos de ordenar: v
// - Posición central: mitad
// - La primera posición del vector v: ini
// - El tamaño de v: fin

void fusion (vector<int> *v, int ini, int mitad, int fin)
{
     int i= ini, j=mitad, k=0; 
     
     //while (i < mitad && j < fin)
     while (ini < j && mitad < fin) // Recorremos mientras no excedamos el ta-
     {                              // maño del vector recibido
           if (v->at(i) < v->at(j)) // Comparamos elementos en ambas mitades
           {         
              aux.push_back(v->at(ini)); // Guardamos el valor mas pequeño
              ini++;
           }
           else if (v->at(i) > v->at(j)) // Comparamos elementos...
           {

              aux.push_back(v->at(mitad)); // Guardamos el valor mas pequeño
              mitad++;
           }      
     }
     if (i == mitad)
     {
         while (j <= fin)
         {
              //aux->push_back(v->at(j));
              aux.push_back(v->at(j));
              j++;
         }        
     }
     if (j == fin)
     {
         while (i <= mitad)
         {
              //aux->push_back(v->at(i));
              aux.push_back(v->at(i));
              i++;
         }        
     }
         
     for ( k = 0; k < aux->size(); k++)
     {
         
         v->push_back(aux->at(k));
 
     } 
}*/
