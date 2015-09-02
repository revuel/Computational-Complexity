/* �����������������������������������������������������������������������������
   
   T�tulo: Pr�ctica 3, El problema de la devoluci�n de cambio
   
   Resumen: Soluciones mediante los paradigmas de Programaci�n Voraz y Programa-
            ci�n Din�mica.
   
   Asignatura: Complejidad Computacional
   Profesor: �ngel Serrano S�nchez de Le�n
   Alumno: Miguel Revuelta Espinosa (revuel22@hotmail.com)
   Fecha: 17/12/2013 - 14/01/2014
   
����������������������������������������������������������������������������� */

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   LIBRER�AS Y ESPACIOS DE NOMBRES
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
#include <cmath>      // Para usar la funci�n fmin
#include <math.h>     // Para usar la funci�n floor
#include <stdlib.h>   // Para usar la funci�n "system("")"
#include <iostream>   // Para usar las funciones cin & cout
#include <vector>     // Para usar la clase vector

using namespace std;  // Para reconocer librer�as de la STL (vector)


/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   DECLARACI�N DE FUNCIONES DE LA APLICACI�N
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
// Men� para elegir el sistema monetario
void menu_mone(vector <int>*, vector <int>*);

// Men� para elegir el paradigma de programaci�n
void menu_prog(vector <int>*, vector <int>*, int, char);

// Inicializar sistema monetario europeo
void iniciar_siseuro(vector <int>* );

// Inventar sistema monetario
void generar_sistema(vector <int>*);

// Ordenar monedas
void quicksort(vector <int>*, int, int, int);

// Ordernar monedas (particionar)
int particionar(vector<int>* , int, int, int);

// Mostrar por pantalla vector de floats
void mostrar_vector(vector <int>* );

// Determinar el cambio a devolver
int determinar_cambio();

// Comprobar que no haya valores repetidos
bool impedir_repeticiones(vector <int>* , int);

// Algoritmo del paradigma voraz
void devcam_voraz(vector <int>*, vector <int>*, int);

// Algoritmo del paradigma de programaci�n din�mica
void devcam_pd(vector <int>*, vector <int>*, int);

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   FUNCI�N PRINCIPAL (MAIN)
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
int main (void)
{
    // Variables locales
    
    vector <int> siseuro;
    vector <int> custom;
    
    //
    iniciar_siseuro(&siseuro); // A�adir valores al vector de euros
    
    //mostrar_vector(&siseuro);
    
    //system("pause");
    
    menu_mone(&siseuro, &custom);   

    cout << "\n\n";   // |
    system("pause");  // |- Secuencia de salida de la aplicaci�n (en realidad no llega aqu� nunca)
    return 0;         // |
}

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   FUNCIONES Y PROCEDIMIENTOS DE LA PR�CTICA
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

void menu_mone(vector <int>* siseuro, vector <int>* custom)
{
     // Variables locales
     int op;
     int cambio;
     char sis; // e: para euros, p: para personalizado 
     
     // Men� monetario
     system("cls");
     
     cout << "\n\n\n";
     cout << "\xA8Qu\x82 sistema monetario desea utilizar?" << "\t" << "(1|2)";
     cout << "\n\n";
     cout << "\t1) Euro";
     cout << "\n";
     cout << "\t2) Personalizado";
     cout << "\n\n\n" << "Los sitemas est\xA0n representados en c\x82ntimos" << "\n\n" << "Opci\xA2n elegida: ";
     
     cin >> op;
     
     switch (op)
     {
            case 1: // Aqu� deberiamos llamar a menu-prog pasandole el vector euro
                 sis = 'e';
                 cambio = determinar_cambio();
                 menu_prog(&(*siseuro), &(*custom), cambio, sis);
                 break;
            case 2: // Aqui llamamos a generar sistema pasandole el vector personalizado
                 sis = 'p';
                 cambio = determinar_cambio();
                 generar_sistema(&(*custom));
                 menu_prog(&(*siseuro), &(*custom), cambio, sis);
                 break;
            default:
                 cout << "\n\n";
                 cout << "Usted ha elegido una opci\xA2n no contemplada" << "\n";
                 system("pause");
                 menu_mone(&(*siseuro), &(*custom));  
                 break;       
     }
               
}

void menu_prog(vector <int>* siseuro, vector <int>* custom, int cambio, char sis)
{
    // Variables locales
     int op;
     
     vector <int> cambio_monedas; // Vector de la soluci�n del cambio
     
     // Men� monetario
     system("cls");
     
     cout << "\n\n";
     cout << "Cambio a devolver: " << cambio;
     cout << "\n\n";
     cout << "Sistema monetario: ";
     
     if (sis == 'e')
     {
        cout << "[Euros], monedas: ";
        mostrar_vector(&(*siseuro));
     }
     else
     {
        cout << "[Personalizado], monedas: ";
        mostrar_vector(&(*custom)); 
     }
     
     cout << "\n\n\n";
     cout << "\xA8Qu\x82 paradigma de programaci\xA2n desea utilizar?" << "\t" << "(1|2|3|4|5)";
     cout << "\n\n";
     cout << "\t1) Paradigma Voraz";
     cout << "\n";
     cout << "\t2) Paradigma de Programaci\xA2n Din\xA0mica";
     cout << "\n";
     cout << "\t3) Solucionar empleando ambos paradigmas";
     cout << "\n";
     cout << "\t4) Volver a elegir un sistema monetario";
     cout << "\n";
     cout << "\t5) Salir de la aplicaci\xA2n";
     cout << "\n\n\n" << "Opci\xA2n elegida: ";
     
     cin >> op; 
     
     switch (op)
     {
            case 1: // Soluci�n Programaci�n Voraz
                 if (sis == 'e')
                 {
                    devcam_voraz(&cambio_monedas, &(*siseuro), cambio);
                    
                    cout << "\n\n" <<"Volviendo al men\xA3 principal" << "\n";
                    system("pause");
                    main();
                 }
                 else
                 {
                    devcam_voraz(&cambio_monedas, &(*custom), cambio);
                    
                    cout << "\n\n" <<"Volviendo al men\xA3 principal" << "\n";
                    system("pause");
                    main();
                 }
                 break;
            case 2: // Soluci�n Programaci�n Din�mica
                 if (sis == 'e')
                 {
                    devcam_pd(&cambio_monedas, &(*siseuro), cambio);
                   
                    cout << "\n\n" <<"Volviendo al men\xA3 principal" << "\n";
                    system("pause");
                    main();
                 }
                 else
                 {
                    devcam_pd(&cambio_monedas, &(*custom), cambio);
                    
                    cout << "\n\n" <<"Volviendo al men\xA3 principal" << "\n";
                    system("pause");
                    main();
                 }
                 break;
            case 4: // Atr�s
                 (*custom).clear();
                 cout << "\n\n";
                 cout << "Volviendo al men\xA3 de selecci\xA2n de sistema monetario" << "\n";
                 system("pause");
                 menu_mone(&(*siseuro),&(*custom));
                 break;
            case 3: // Usar ambos paradigmas uno de tras de otro
                 if (sis == 'e')
                 {
                    cout << "\n\n\n\n";
                    cout << "\t" << "---- Soluci\xA2n voraz ----" << "\n";
                    devcam_voraz(&cambio_monedas, &(*siseuro), cambio);
                    
                    cout << "\n\n\n\n";
                    cout << "\t" << "---- Soluci\xA2n de programaci\xA2n din\xA0mica ----" << "\n";
                    devcam_pd(&cambio_monedas, &(*siseuro), cambio);
                    
                    cout << "\n\n" <<"Volviendo al men\xA3 principal" << "\n";
                    system("pause");
                    main();
                 }
                 else
                 {
                    cout << "\n\n\n\n"; 
                    cout << "\t" << "---- Soluci\xA2n voraz ----" << "\n"; 
                    devcam_voraz(&cambio_monedas, &(*custom), cambio);
                    
                    cout << "\n\n\n\n";
                    cout << "\t" << "---- Soluci\xA2n de programaci\xA2n din\xA0mica ----" << "\n";
                    devcam_pd(&cambio_monedas, &(*custom), cambio);
                    
                    cout << "\n\n" <<"Volviendo al men\xA3 principal" << "\n";
                    system("pause");
                    main();
                    
                 }
                 break;
            case 5: // Salir
                 cout << "\n\n";
                 cout << "Saliendo de la aplicaci\xA2n";
                 cout << "\n";
                 system("pause");
                 exit(1);
                 break;
            default:
                 cout << "\n\n";
                 cout << "Usted ha elegido una opci\xA2n no contemplada" << "\n";
                 system("pause");
                 menu_prog(&(*siseuro),&(*custom), cambio, sis);  
                 break;   
     }     

}

void iniciar_siseuro(vector <int>* siseuro)
{
     // A�adimos las monedas en orden para ahorrarnos la ordenaci�n (cosas de inform�ticos)
     (*siseuro).push_back(200);
     (*siseuro).push_back(100);
     (*siseuro).push_back(50);
     (*siseuro).push_back(20);
     (*siseuro).push_back(10);
     (*siseuro).push_back(5);
     (*siseuro).push_back(2);
     (*siseuro).push_back(1);
}

void mostrar_vector(vector <int>* v)
{
     // Variables locales
     int siz, i;
     
     //
     siz = (*v).size();
     
     cout <<"\n\n";
     
     for (i = 0; i < siz; i++)
     {
         cout << (*v)[i] << " ";    
     }       
}

void generar_sistema(vector <int>* custom)
{
     // Variables locales
     int i = 0, siz; 
     int aux;// = 1;
     
     //
     system("cls");
     cout << "Proceso de creaci\xA2n de sistema monetario personalizado";
     cout << "\n";
     cout << "Pulse la tecla 0 (cero) cuando haya terminado de introducir monedas";     
     cout << "\n\n\n";
     
     while (true)
     {
          cout << "Por favor, introduzca una mondeda en el sistema: ";
          cin >> aux;
          
          if (aux == 0) // Terminando de a�adir monedas
          {
             if ((*custom).size() > 0) // Comprobamos haber a�adido al menos una moneda
             {
                 cout << "\n" << "Nuevo sistema monetario creado";
                 cout << "\n";
                 break; // En caso afirmativo interrumpimos la ejecuci�n
             }
             else
             {
                 cout << "\n" << "Debe introducir al menos una moneda";
                 cout << "\n";      
             }        
          }
          else
          {
             if (impedir_repeticiones(&(*custom),aux) == false)
             {
                 (*custom).push_back(aux);
             }
             else
             {
                 cout << "\n";
                 cout << "Esta moneda, " << aux << ", ya existe en este sistema, por favor, elija una distinta" << "\n";
             }
          }
          cout << "\n";  
     }
     
     // Iniciando ordenaci�n
     siz = (*custom).size();
     
     quicksort(&(*custom),0,siz, 1);
     
     cout << "\n" << "Monedas del sistema: ";
     
     mostrar_vector(&(*custom));
     
     cout << "\n\n";
     system("pause");     

}

int determinar_cambio()
{
    // Variables locales
    int n;
    
    //
    cout << "\n\n" << "Por favor, indique la cantidad a devolver: ";
    cin >> n;
    
    return n;    
}

void quicksort(vector<int>* v, int p, int q, int sentido)
{
     int i; 

     if (p < q)
     {   
           i = particionar(&(*v), p, q, sentido); 
           quicksort(&(*v),p,i,sentido);    
           quicksort(&(*v),i+1,q, sentido);    
     }
     
}

int particionar(vector<int>* v, int p, int q, int sentido)
{
    // Variables locales
    int j; // �ndice
    int x = (*v)[p]; // Valor del pivote
    int i = p; // Posici�n del pivote   
    int aux; // Variable para intercambios     

    if (sentido == 1)
    {
        for (j = p+1; j<q; j++) // Recorriendo el subvector
        {      
            if ((*v)[j] > x) // Condici�n: Que el valor del �ndice sea mayor que el valor del pivote
            {
               i++; // Incremento del �ndice
               aux = (*v)[i];     // |
               (*v)[i] = (*v)[j]; // |- Reordenando
               (*v)[j] = aux;     // |
            }    
        }
        
        aux = (*v)[p];     // |
        (*v)[p] = (*v)[i]; // |- Colocando al pivote en su sitio
        (*v)[i] = aux;     // |
          
        return i; // Devolvemos la posici�n del pivote
    }
    else
    {
        for (j = p+1; j<q; j++) // Recorriendo el subvector
        {      
            if ((*v)[j] < x) // Condici�n: Que el valor del �ndice sea menor que el valor del pivote
            {
               i++; // Incremento del �ndice
               aux = (*v)[i];     // |
               (*v)[i] = (*v)[j]; // |- Reordenando
               (*v)[j] = aux;     // |
            }    
        }
        
        aux = (*v)[p];     // |
        (*v)[p] = (*v)[i]; // |- Colocando al pivote en su sitio
        (*v)[i] = aux;     // |
          
        return i; // Devolvemos la posici�n del pivote
    }
}  

bool impedir_repeticiones(vector <int>* custom, int actual)
{
     // Variables locales
     int i, siz;
     
     //
     siz = (*custom).size(); // Salvamos el tama�o (por pulcritud, podr�a usar la funcion size() dentro del for)
     
     for (i = 0; i < siz; i++) // Recorremos todo el vector
     {
         if (actual == (*custom)[i]) // Buscando coincidencia
         {
            return true; // El elemento a introducir ya existe, devolvemos verdadero          
         }    
     }
     
     return false; // El elemento a introducir no existe en el vector, devolvemos falso          
}

void devcam_voraz(vector <int>* cambio_monedas, vector <int>* sistema, int cambio)
{
     // Variables locales
     int i = 0, aux;
     //float aux, zero = 0.00;
     
     //
     while (cambio > 0)
     {
           if ( i == (*sistema).size() && (*sistema)[i] > cambio ) // Este ser�a el caso de haber llegado a la �ltima moneda
           {                                                       // del sistema, que es mayor que la cantidad a devolver.        
                break;                                             // Por ello debemos interrumpir la ejecuci�n del while.   
           }
                 
           while ( (*sistema)[i] <= cambio )  // Mientras haya cambio que devolver
           {
                 aux = ((*sistema)[i]);
                 (*cambio_monedas).push_back(aux); // Incluimos monedas en el cambio
                 cambio = cambio - aux;      
           }
           i++;      
     }
     
     cout << "\n\n" << "Su cambio: ";
     mostrar_vector(&(*cambio_monedas)); // Mostramos el cambio
     cout << "\n\n" << "La m\xA0quina se ha quedado: " << cambio << " c\x82ntimos"; // Mostramos cu�nto dinero se ha quedado
}

void devcam_pd(vector <int>* cambio_monedas, vector <int>* sistema, int cambio)
{
    // Inicializaci�n del algoritmo (variables y configuraci�n previa)
     
    // Matriz de las monedas del sistema 
    vector <int> fila_monedas;
    vector <vector<int> > matriz_monedas;
    
    // Matriz de booleanos para el cambio
    vector <bool> fila_boolean;
    vector <vector<bool> > matriz_boolean;
    
    // Otras variables
    int i = 0, j = 0, n = (*sistema).size(), L = cambio + 1 ;
    
    quicksort(&(*sistema), 0, n, 2); //Ordenando de menor a mayor
    
    mostrar_vector(&(*sistema));
    cout << "\n";
    
    // Inicializaci�n (a cero/false) de las matrices
    for (i = 0; i < n; i++) // Tantas filas como tipos de moneda
    {
        for (j = 0; j < L; j++) // Tantas columnas como la cantidad a devolver + 1
        {
            fila_monedas.push_back(0);
            fila_boolean.push_back(false);    
        }
        
        matriz_monedas.push_back(fila_monedas); 
        fila_monedas.clear();
        
        matriz_boolean.push_back(fila_boolean);
        fila_boolean.clear();
    }
    
    // Desarrollo del algoritmo
    
    //            1) Poner los valores de las matrices
    
    for ( i = 0; i < n; i++) // Recorrido de filas
    {
        for (j = 1; j < L; j++) // Recorrido de columnas
        {
            
            if ( i == 0 && j < (*sistema)[i]) 
            {
               matriz_monedas[i][j] = 9999; // Valores infinitos para sistemas monetarios extra�os
               matriz_boolean[i][j] = false; // Un valor infinito, obviamente no puede ser    
            }                                // un elemento a devolver
            
            else if (i == 0 && j >= (*sistema)[i]) // Primera fila
            {
                 // Para evitar "infinitos verdaderos", o dicho de otra manera;
                 // que no escriba valores monetarios 10000, que al ser diferentes de la columna superior
                 // implicar�a a�adir verdaderos en lugares donde deber�a haber un falso
                 if (matriz_monedas[i][j - (*sistema)[i]] == 9999) //Si la celda anterior es un infinito
                 {
                         matriz_monedas[i][j] = (matriz_monedas[i][j - (*sistema)[i]]); //copiamos el infinito
                         matriz_boolean[i][j] = false;   // escribimos falso                
                 }
                 else
                 {
                         matriz_monedas[i][j] = 1 + (matriz_monedas[i][j - (*sistema)[i]]); //Para los dem�s casos
                         matriz_boolean[i][j] = true; // aparte de escribir el valor correspondiente asignamos verda-
                 }                                    // dero en la tabla de booleanos
            }
            else if (i > 0 && j < (*sistema)[i]) // 
            {
                 matriz_monedas[i][j] = matriz_monedas[i - 1][j]; // Copiamos la celda de arriba
                 matriz_boolean[i][j] = false; // Esta celda no ser�a un valor a devolver, puesto que es igual a
            }                                  // la celda de arriba
            else
            {   // Este corresponde al caso mayoritario, elegir un m�nimo, uso fmin por comodidad
                // esta funci�n esta en la libreria cmath de la stl, pero devuelve un double... el dev c++ hace las
                // conversiones autom�ticamente y no me ha dado problemas m�s all� de un warning
                matriz_monedas[i][j] =  fmin(matriz_monedas[i - 1 ][j], 1 + matriz_monedas[i][j - (*sistema)[i]]);
                           
                if ( matriz_monedas[i][j] == matriz_monedas[i - 1][j]) // Determinando el campo en la tabla de booleanos
                {
                  matriz_boolean[i][j] = false;  // El valor de la fila de arriba es id�ntico, luego    
                }                                 // ponemos falso en la matriz boolean
                else
                {
                  matriz_boolean[i][j] = true;   // Los valores son distintos, esta celda a true
                }
            }
            
        }
     }

    //              2) Visualizar las matrices        
    cout << "\n";
    
    for (i = 0; i < n; i++) // Tantas filas como tipos de moneda
    {
        for (j = 0; j < L; j++) // Tantas columnas como la cantidad a devolver + 1
        {
            cout << matriz_monedas[i][j] << "|" << matriz_boolean[i][j] << "|" << " ";
            
        }
        
        cout << "\n";
    }
    
    //              3) Determinar el cambio
     
     (*cambio_monedas).clear(); // Ponemos el vector del cambio a 0 por si acaso
     
     i = n - 1;                     // Ponemos los �ndices en la �ltima celda de las tablas
     j = L - 1;                     
     
     while ( i != 0 && j != 0)
     {
           if ( matriz_boolean[i][j] == false)
           {
              i--; // Subiendo a la celda superior     
           }
           else
           {
              (*cambio_monedas).push_back((*sistema)[i]); // A�adiendo moneda a la soluci�n
              j = j - (*sistema)[i]; 
              cambio = cambio - (*sistema)[i];  // Actualizando cambio restante  
           }      
     }
     
     //           3) Imprimir por pantalla el vector de la soluci�n
     cout << "\n\n" << "Su cambio: ";
     mostrar_vector(&(*cambio_monedas)); // Mostramos el cambio*/
     cout << "\n\n" << "La m\xA0quina se ha quedado: " << cambio 
     << " c\x82ntimos"; // Mostramos cu�nto dinero se ha quedado
}


