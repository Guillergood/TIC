
#include "Tarjetero.h"
#include <string.h>

// UID de la tarjeta a leer
char UID[32];
char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,;. \0";
char opcion;
String leido;
uint16_t resultado[32];
int totalUtilizados = 0;



/**
 * ---------------------------------------
 * Declaración de las variables globales necesarias aquí (en caso de ser necesario)
 * (a realizar por el alumno)
 */

// ....


/**
 * Fin de declaración de variables globales
 * ---------------------------------------
 */



/**
 * ---------------------------------------------------------------
 * Funciones auxiliares de ayuda proporcionadas por el profesor
 */

// Función que tiene como entrada un array de len '0's y '1's, donde
// 0<len<=16, y transforma la secuencia de '0's y '1's codificándola
// a nivel de bits en un único dato de 16 bits (desde la posición del bit menos significativo)
// Se asime que codigo[0] es el bit menos significativo y codigo[len-1] el más significativo
uint16_t BytesToUint16(char *codigo, int len) {

  uint16_t salida= 0;
  for (int i= len-1; i>=0; i--) {
    salida= (salida<<1);
    if (codigo[i] == '1') salida= (salida|1);
  }
  return salida;
}


// Función que tiene como entrada codigo, un dato de 16 bits, y devuelve
//  como salida un array de len componentes, donde 0<len<=16,
//  con valores '0' y '1' en las posiciones de cada bit. Es la función
//  inversa a BytesToUint16
void Uint16ToBytes(uint16_t codigo, char *salida, int len) {

  for (int i= 0; i<len; i++) {
    if ((codigo & 1) > 0)
      salida[i]= '1';
    else salida[i]= '0';
    codigo= (codigo>>1);
  }

}


/**
 * Fin de funciones auxiliares de ayuda proporcionadas por el profesor
 * ---------------------------------------------------------------
 */






 int matrixG [5][12] = {{ 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0},
                      { 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0},
                      { 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
                      { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                      { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1}};


 int matrixH [12][4] = { { 1, 1, 0, 0},
                         { 1, 0, 1, 1},
                         { 1, 0, 1, 0},
                         { 1, 0, 0, 1},
                         { 1, 0, 0, 0},
                         { 0, 1, 1, 1},
                         { 0, 1, 1, 0},
                         { 0, 1, 0, 1},
                         { 0, 1, 0, 0},
                         { 0, 0, 1, 1},
                         { 0, 0, 1, 0},
                         { 0, 0, 0, 1}};







 void CodificaLineal(unsigned int posicion, uint16_t* resultado, const int& totalUtilizados){
   int bitsPosicion [5];
   uint16_t palabraCodificada = 0;

   bitsPosicion[4] = (posicion &  1);
   bitsPosicion[3] = (posicion & ( 2 )) >> 1;
   bitsPosicion[2] = (posicion & ( 4 )) >> 2;
   bitsPosicion[1] = (posicion & ( 8 )) >> 3;
   bitsPosicion[0] = (posicion & ( 16 )) >> 4;



   palabraCodificada<<=1;
   palabraCodificada<<=1;
   palabraCodificada<<=1;
   palabraCodificada<<=1;



   for(int i = 0; i < 12; ++i){
     int suma = 0;


     for(int k = 0; k < 5; ++k){



        suma ^= bitsPosicion[k] & matrixG[k][i];

     }

     palabraCodificada<<=1;
     palabraCodificada|=suma;

   }

   resultado[totalUtilizados] = palabraCodificada;
   int& x = const_cast<int&>(totalUtilizados);
   ++x;
 }

 void CalculaSindrome(int* palabraCodificada, int&resultado){

   int valorIntermedio = 0;
   int& x = const_cast<int&>(resultado);

   int valores[4];



   for(int i = 0; i < 4; ++i){

     for(int j = 0; j < 12; ++j){

            valorIntermedio ^= palabraCodificada[j] & matrixH[j][i];
     }

     x<<=1;
     x |= valorIntermedio;
     valorIntermedio = 0;

   }



 }

 void DecodificaLineal(uint16_t* resultado, int* frase){
   int palabraCodificada [12];
   int numero = 0;
   for(int i = 0; i < 32; ++i){
     uint16_t elemento = resultado[i];
     for(int j = 11; j >= 0; --j){
       palabraCodificada[j] = (elemento & 1);
       elemento>>=1;
     }

     CalculaSindrome(palabraCodificada, numero);
     if(numero > 0 && numero <= 12){
       palabraCodificada[12-numero+1]^=1;
       numero = 0;
     }
     int k = 0;
     int otro = 0;
     for(k = 12-5; k < 11; ++k){
       otro |= palabraCodificada[k];
       otro<<=1;
     }

     otro |= palabraCodificada[k];


     frase[i] = otro;
     numero = 0;
   }
 }



void setup() {

    /**
     * Declaración de variables locales a setup aquí (en caso de ser necesario)
     * (a realizar por el alumno)
     */



    /**
     * --------------------------------
     * Inicialización de variables locales o globales aquí (en caso de ser necesario)
     */

      

//...

    /**
     * FIN de inicialización de variables locales y globales
     * -----------------------
     */



    // Inicialización del tarjetero
    initMFRC522();

    opcion= ' ';


    Serial.begin(9600);
    while (!Serial); // Esperamos a que se abra el Monitor Serie

    Serial.println("Escoja una opción (L=leer/E=escribir)...");
    do {
      if (Serial.available()) {
        opcion= Serial.read();
        if (opcion != 'L' && opcion != 'E') {
          Serial.println("Opción no válida (L/E).");
        }
      }
    } while (opcion!='L' && opcion != 'E');

    if (opcion == 'E') {
      Serial.print("\nIntroduzca el mensaje a escribir (max. 32)...\n");


      while (Serial.available() < 2);

      leido= Serial.readString();


      /**
       * Leer 32 caracteres del alfabeto de la fuente desde Serial
       * (a implementar por el estudiante)
       */
      leido.trim();
      

      /**
       * Implementar aquí lo siguiente (a realizar por el alumno):
       * Para cada símbolo leído:
       *  Codificarlo en palabra de código uniforme
       *  Codificar la palabra de código uniforme en palabra del código lineal
       *  Transformar la palabra del código lineal a tipo uint16_t, usando las funciones auxiliares proporcionadas
       *  Guardar el dato resultante en un array de 32 datos de tipo uint16_t
       */
          Serial.println("Codificando datos...");
    
          for(int i = 0; i < 32 ; ++i){
           int posicion = 32-1;
           if(i < leido.length()){
             char elemento = leido.charAt(i);
             if(elemento >= 'A' && elemento <= 'Z'){
               posicion = elemento - 'A';
             }
             else{
               bool continua = true;
               posicion = 32 - 5;
    
               for(; posicion < 32 && continua; ++posicion){
                 if(alfabeto[posicion] == elemento){
                   continua = false;
                 }
               }
               posicion--;
             }
           }
           CodificaLineal(posicion, resultado, totalUtilizados);
           Serial.print(resultado[i]);
           Serial.print(" ");
         }
      
           int frase[32];
    
           
           DecodificaLineal(resultado, frase);
           for(int z = 0; z < 32; ++z){
            char elemento = alfabeto[frase[z]];
            if(elemento != '\0')
              Serial.println(alfabeto[frase[z]]);
           }


      /**
       * Fin de la implementación
       * ------------
       */


      Serial.println("Esperando a tarjeta para escribir...");
    } else {
      Serial.println("Esperando a tarjeta para leer...");
    }
}


void loop() {


    /**
     * Declaración de variables locales e inicialización de datos (si es necesario)
     * (a realizar por el alumno)
     */


    /**
     * Fin de Declaración de variables locales e inicialización de datos (si es necesario)
     */







    if (opcion != 'L' && opcion != 'E') return;

    if ( ! isCardDetected())return;

    Serial.print("Tarjeta detectada. ");
    if ( !readUIDCard(UID) )
        return;

    Serial.print(F("UID:"));
    Serial.println(UID);


    if (opcion == 'L') { // Lectura de la tarjeta

      /**
       * A implementar por el alumno:
       * 1. Lectura de 32 datos de tipo uint16_t de la tarjeta
       * 2. Para cada dato leído:
       * 2.1. Pasar el dato a array de '0's y '1's con las funciones auxiliares proporcionadas por el profesor
       * 2.2. Decodificar la palabra del código lineal dada en palabra del código uniforme
       * 2.3. Decodificar la palabra del código uniforme en símbolo de la fuente
       * 2.4. Insertar el símbolo de la fuente en un array
       * 3. Enviar por puerto serie el array de datos al PC
       */

       if (!readCard((uint16_t *)resultado)) {

         Serial.println("Error en lectura de tarjeta.");
         closeCard();
         return;
       }

       int frase[32];
       for(int z = 0; z < 32; ++z){
        Serial.println(resultado[z]);
       }

       
       DecodificaLineal(resultado, frase);
       for(int z = 0; z < 32; ++z){
        char elemento = alfabeto[frase[z]];
        if(elemento != '\0')
          Serial.print(alfabeto[frase[z]]);
       }

    } else if (opcion == 'E'){ // Escritura en tarjeta


      /**
       * Escritura de 32 datos de tipo uint16_t en la tarjeta
       * (a implementar por el alumno)
       */

       if (!writeCard((uint16_t *)resultado)) {
         Serial.println ("Error en escritura de tarjeta.");

         closeCard();
         return;
       }


      Serial.println("Datos escritos en la tarjeta.");
    }
    
    closeCard();
}
