/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
   
   Título: Práctica 4, Resolución de laberintos
   
   Resumen: Aplicar el algoritmo del Paradigma de Vuelta Atrás para resolver un
            laberinto.
   
   Asignatura: Complejidad Computacional
   Profesor: Ángel Serrano Sánchez de León
   Alumno: Miguel Revuelta Espinosa (revuel22@hotmail.com)
   Fecha: 23/01/2014 - 
   
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   LIBRERÍAS Y ESPACIOS DE NOMBRES
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
#include <stdlib.h>   // Para usar la función "system("")"
#include <iostream>   // Para usar las funciones cin & cout
#include <vector>     // Para usar la clase vector

using namespace std;  // Espacio de nombres de la Standard Template Library

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   DECLARACIÓN DE VARIABLES GLOBALES
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
#define N 17          // Tamaño del laberinto
#define PARED -1      // Valor para la pared

// Salida del laberinto
int salida [2] = {11, 15}; //{fila,columna}

// Declaración e inicialización del laberinto propuesto (f = fila)

int lab[N][N] = {{PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED, 
      PARED, PARED, PARED, PARED, PARED, PARED, PARED, PARED}, // f1
     {PARED, 0, 0, 0, 0, 0, PARED, 0, 0, 0, 0, 0, 0, 0, PARED, 0, PARED}, // f2
     {PARED, 0, PARED, PARED, PARED, PARED, PARED, 0, PARED, 0, PARED, PARED, 
      PARED, 0, PARED, 0, PARED}, // f3
     {PARED, 0, 0, 0, 0, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, PARED, 0, PARED},
     {PARED, 0, PARED, PARED, PARED, PARED, PARED, PARED, PARED, 0, PARED, 0, 
      PARED, PARED, PARED, 0, PARED}, // f5
     {PARED, 0, 0, 0, 0, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, 0, 0, PARED}, // f6
     {PARED, 0, PARED, PARED, PARED, PARED, PARED, PARED, PARED, 0, PARED, 
      PARED, PARED, PARED, PARED, 0, PARED}, // f7
     {PARED, 0, PARED, 0, 0, 0, 0, 0, 0, 0, PARED, 0, 0, 0, 0, 0, PARED}, // f8
     {PARED, 0, PARED, 0, PARED, PARED, PARED, PARED, PARED, PARED, PARED, 0, 
      PARED, PARED, PARED, PARED, PARED}, // f9
    {PARED, 0, PARED, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, PARED, 0, 0, 0, PARED},
     {PARED, PARED, PARED, PARED, PARED, 0, PARED, 0, PARED, 0, PARED, PARED, 
      PARED, 0, PARED, 0, PARED}, // f 11
     {PARED, 0, 0, 0, 0, 0, PARED, 0, 0, 0, PARED, 0, 0, 0, PARED, 0, -2},
     {PARED, 0, PARED, PARED, PARED, PARED, PARED, 0, PARED, PARED, PARED, 0, 
      PARED, 0, PARED, PARED, PARED}, // f 13
    {PARED, 0, PARED, 0, 0, 0, PARED, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, PARED},
     {PARED, 0, PARED, 0, PARED, 0, PARED, PARED, PARED, 0, PARED, PARED, PARED, 
      PARED, PARED, 0, PARED}, // f 15
     {PARED, 0, 0, 0, PARED, 0, PARED, 0, 0, 0, 0, 0, 0, 0, 0, 0, PARED},
     {PARED, PARED, PARED, PARED, PARED, 1, PARED, PARED, PARED, PARED, PARED, 
      PARED, PARED, PARED, PARED, PARED, PARED}}; // f 17

int desplazaX[4], desplazaY[4];       

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   DECLARACIÓN DE FUNCIONES/PROCEDIMIENTOS DE LA APLICACIÓN
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

// Procedimiento de resolución del laberinto
void resolverlaberinto(int, int, int, bool);

// Determinar secuencia de movimientos (elegido por el usuario)
void elegirmovimientos(void);

// Mostrar el camino de la solución
void imprimirlaberinto(int[N][N]);

// Procedimiento para inicializar desplazamientos
void inicializadesplazamientos(void);

// Función para evitar la repetición de valores en las direcciones 
bool controlrepeticion (int, vector <int>);

// Función para controlar rango de las direcciones
bool controlrango (int);


/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   FUNCIÓN PRINCIPAL (MAIN)
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

int main (void)
{
    // Flujo
    cout << "   Laberinto:" << "\n\n\n"; // Título
    
    imprimirlaberinto(lab); // Visualizar en pantalla el laberinto no resuelto
    
    cout << "\n\n";
    
    inicializadesplazamientos(); // Especificar la secuencia de movimientos
    
    cout << "\n\n"; 
    
    lab[16][5] = 1; // Posición de la entrada del laberinto
    resolverlaberinto(2, 16, 5, false); // Resolver el laberinto
       
    cout << "\n\n";   // |
    //system("pause");// |- Secuencia de salida de la aplicación 
    return 0;         // |
}

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
   FUNCIONES Y PROCEDIMIENTOS DE LA PRÁCTICA
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·
    
       Procedimiento: Imprimir el laberinto por pantalla
            
    Parámetros de entrada: un array de arrays de enteros
    Resumen: Muestra por pantalla el contenido de una matríz, recorriendola
             mediante dos estructuras de control "for" anidadas.

·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  */

void imprimirlaberinto (int lab[N][N])
{
     // Índices 
     int i = 0, j = 0;
     
     for (i = 0; i < N; i++) // filas
     {
         for (j = 0; j < N; j++) // columnas
         {
             if (lab[i][j] >= 0 && lab[i][j] <= 9)
             {
                cout << " ";  //espacio adicional para cifras de un dígito            
             }
             cout << " " << lab[i][j];  // coordenada  
         }
         cout << "\n";    
     }    
}

/*  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·
    
       Procedimiento: Inicializa la secuencia de los desplazamientos
            
    Parámetros de entrada: Ninguno
    Resumen: El usuario decidirá cuál será el orden de movimientos indicándolo
             mediante este procedimiento.

·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  */
void inicializadesplazamientos()
{
     // Variables locales
     int i = 0, j = 0, k = 0, num;
     vector <int> secdireccion;
     
     // Flujo
     cout << "Introduzca el orden de direcciones: " << "\n";
     cout << "1 = Izquierda" << "\n";
     cout << "2 = Arriba" << "\n";
     cout << "3 = Derecha" << "\n";
     cout << "4 = Abajo" << "\n";
     
     // El usuario escogerá el orden de las direcciones posibles.
     while (i <= 3)
     {
           fflush(stdin); // Limpiando búffer de teclado
           
           cout << "\n" << "Direcci\xA2n (" << i + 1 << "): ";
           cin >> num; // Guardamos la nueva posible dirección
           
           if ( controlrango(num) == true) // Controlando rango...     
           {
               if (i == 0) // Es la primera dirección elegida, entra siempre
               {
                      secdireccion.push_back(num);
               }
               else // Otras direcciones
               {
                   // Control de repeticiones 
                   if ( controlrepeticion(num,secdireccion) == false )
                   {
                        secdireccion.push_back(num); // Número válido (añadir)
                   }
                   else
                   {
                       //Número no valido (repetido)
                   cout << "\n" << "Esa dirección fue previamente elegida." <<
                       "\n" << "Por favor, elija una nueva dirección" << "\n";
                       i--; // La última iteración no cuenta, hay que repetirla
                   }
               }
           }
           else
           {
               i--; // Número fuera de rango
           }
           i++;   
     }
     
     // Recorremos el vector que representa el orden de las direcciones, para
     // establecer los valores correspondientes en los arrays de dirección
     for (k = 0; k < 4; k++)
     {
         if ( secdireccion[k] == 1) // Izquierda
         {
              desplazaX[k] = -1;
              desplazaY[k] = 0;    
         }
         if ( secdireccion[k] == 2) // Arriba
         {
              desplazaX[k] = 0;
              desplazaY[k] = 1;
         }
         if ( secdireccion[k] == 3) // Derecha
         {
              desplazaX[k] = 1;
              desplazaY[k] = 0;
         }
         if ( secdireccion[k] == 4) // Abajo  
         {
              desplazaX[k] = 0;
              desplazaY[k] = -1;
         }
     }
     
     // Mostrando por pantalla para verificar que todo ha salido correctamente
     cout << "\n\n";
     for (j = 0; j < 4; j++)
     {
         cout << "|" << secdireccion[j] << "| ";   // Vector de direcciones
         cout << "x: " << desplazaX[j] << " ";     // Coordenada X
         cout << "y: " << desplazaY[j] << "   ";   // Coordenada Y
     }
}

/*  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·
    
       Función: controlrepeticion
            
    Parámetros de entrada: Un entero y un vector
    Parámetros de salida: Un booleano
    Resumen: Controlar que no haya direcciones repetidas, retornará un verdadero
             si el número que se pretende introducir está ya en el vector.

·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  */
bool controlrepeticion (int num, vector <int> direc)
{
     // Variables locales
     int i = 0;
     
     // Recorrido del vector
     for (i = 0; i < direc.size(); i++)
     {
         if (num == direc[i]) // El numero introducido se encuentra en el vector
         {
            return true; // Devolvemos "true" para impedir que sea introducido
         }
     }
     
     return false; // No se ha encontrado el número en el vector
}

/*  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·
    
       Función: controlrango
            
    Parámetros de entrada: Un entero
    Parámetros de salida: Un booleano
    Resumen: Recibe un entero; devuelve falso si este entero es menor que uno o
             mayor que cuatro.

·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  */
bool controlrango (int num)
{
     // Comprobación de que el número esta fuera de rango
     if (num < 1 || num > 4)
     {
        cout << "\n" << "Número fuera de rango" << "\n" <<
        "Por favor, elija un número entre 1 y 4" << "\n";
        
        return false; // Fuera de rango, el número no servirá        
     }     
     else
     {
        return true; // El número entra en el rango
     }
}

/*  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·
    
       Procedimiento: resolverlaberinto
            
    Parámetros de entrada: Tres enteros y un booleano
    Resumen: Dada una secuencia de movimientos definida por el usuario, este al-
             goritmo resuelve el laberinto probando los posibles caminos.
             Si llega a un callejón sin salida, volverá a la última posición 
             donde probará realizar el siguiente movimiento, es decir, avanzar 
             por otro camino.
             Una vez que llega a la salida, el programa finaliza.
·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  ·  */
void resolverlaberinto(int paso, int x, int y, bool exito)
{
     // X son las filas, Y son las columnas
     
     // Variables locales
     int orden = -1; // Para poder empezar en orden 0
     exito = false;
     
     do {
         orden++; // Incrementamos orden para ir probando todas las direcciones
         x = x + desplazaX[orden]; // |Ajustamos las coordenadas
         y = y + desplazaY[orden]; // |según el orden 
         
         // Si podemos movernos por un pasillo sin salirnos del laberinto...
         if ( (0 <= x) && (x < N) && ( 0 <= y) && ( y < N) && lab[x][y] == 0)
         {
              lab[x][y] = paso; // Accedemos a la siguiente casilla
              
              imprimirlaberinto(lab);
              cout << "\n\n";
              cout << "Paso: " << paso << " " << "Orden: " << orden;
              cout << "\n\n";
              cout << "X: " << x << " " << "Y: " << y;
              cout << "\n\n";
              cout << "\x82xito: " << exito;
              cout << "\n\n";
              //system("pause"); // lo comento para que no sufras
              cout << "\n\n";
              
              if (x == salida[0] && y == salida[1]) // Alcanzada la salida
              { 
                  cout << "   Soluci\xA2n al laberinto:" << "\n\n\n";
                  imprimirlaberinto(lab); // Visualizar en pantalla resuelto 
                  cout << "\n\n";
                  //system("pause");
                  cin >> orden;
                  exit(1); // Explicación en la memoria
                  
                  exito = true;  // Ya casi es completamente innecesario         
              }
              else
              {    // Llamada recursiva al procedimiento (nueva posición)     
                   resolverlaberinto(paso + 1, x, y, exito);
                   
                   if (exito == false)
                   {
                      lab[x][y] = 0; // Liberamos la posición  
                   }
              } 
         }
         // Deshacemos el movimiento pues no lleva a solución
         x = x - desplazaX[orden];
         y = y - desplazaY[orden];

     } while(exito == false && orden < 4);
}

