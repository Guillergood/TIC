#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include <cstring>

using namespace std;

void calcularProbabilidades(string cadena, double *probabilidades, char *alfabeto){
  double sumatoria = 0;
  double sumatoria2 = 0;
  int posicion = 0;
  int simbolos = 0;

  for(int i = 0; i < 30; ++i){
    alfabeto[i] = '\0';
  }


  for (size_t i = 0; i < cadena.length(); i++) {
    char elemento = toupper(cadena[i]);
    if(elemento >= 'A' && elemento <= 'Z'){
      posicion = elemento - 'A';
      alfabeto[posicion] = elemento;
      probabilidades[posicion]++;
      sumatoria++;
    }
    else{
      bool continua = true;
      posicion = 26;
      for(; posicion < 30 && continua; ++posicion){
        if(cadena[i] != '\n'){
          if(alfabeto[posicion] == '\0'){
            continua = false;
            probabilidades[posicion]++;
            sumatoria++;
            alfabeto[posicion] = cadena[i];
          }
          else if(alfabeto[posicion] == cadena[i]){
            continua = false;
            probabilidades[posicion]++;
            sumatoria++;
          }
        }
      }
    }
  }
  for (size_t i = 0; i < 30; i++) {
    if(alfabeto[i] != '\0'){
      std::cout << "alfabeto(" << i << ") -> " << alfabeto[i] << '\n';
    }
    else{
      std::cout << "alfabeto(" << i << ") -> ES NULO" << '\n';
    }

  }

}

void ordenacionPorInsercion(double *probabilidades, int *orden, int tamanio){
    int i, j;
    double probabilidadesObjetivo;
    int ordenObjetivo;
    for (i = 1; i < tamanio; i++)
    {
        probabilidadesObjetivo = probabilidades[i];
        ordenObjetivo = orden[i];
        j = i-1;
        while (j >= 0 && probabilidades[j] < probabilidadesObjetivo){
            probabilidades[j+1] = probabilidades[j];
            orden[j+1] = orden[j];
            j = j-1;
        }
        probabilidades[j+1] = probabilidadesObjetivo;
        orden[j+1] = ordenObjetivo;
    }
}

void creaArbolHuffmann(char *alfabeto, double * probabilidades,  int matriz[64][4], int &tamanioArbol){

    const int TAMALFABETO = tamanioArbol;
    int tam_orden = TAMALFABETO;

    int orden[TAMALFABETO]; //vector que guarda las posiciones de los códigos

    // Inicializamos los nodos raiz.
    for(int i = 0; i < TAMALFABETO;  i++){
        matriz[i][0] = alfabeto[i];
        matriz[i][1] = -1;
        matriz[i][2] = -1;
        orden[i] = i;

    }
    ordenacionPorInsercion(probabilidades,orden,tam_orden);
    for(int i = TAMALFABETO; i < 64; i++){
        matriz[i][0] = '\0';
    }
    // comenzamos a rellenar el arbol mediante Huffman hasta
    // que tam_orden sea igual a 1, es decir, hasta que lleguemos a la raiz:
    while(tam_orden != 1){

        //Sumamos la probabilidad de los dos elementos con menor probabilidades:
        probabilidades[tam_orden-2] = probabilidades[tam_orden - 2] + probabilidades[tam_orden-1];

        //Asignamos al nuevo nodo generado sus dos hijos:
        matriz[tamanioArbol][1] = orden[tam_orden-2];
        matriz[tamanioArbol][2] = orden[tam_orden-1];

        //Ahora asignamos a los dos nodos hijos su nuevo padre:
        matriz[ orden[tam_orden-2] ][3] = tamanioArbol;
        matriz[ orden[tam_orden-1] ][3] = tamanioArbol;

        // Modificamos el vector orden
        orden[tam_orden-2]= tamanioArbol;

        //reducimos el tamaño del vector orden:
        tam_orden--;

        //En caso de que hayamos terminado, indicamos en el nodo que este es la raiz:
        if(tam_orden == 1){
            matriz[tamanioArbol][3] = -1;
        }

        //Aumentamos el tamaño del arbol:
        tamanioArbol++;

        //Reordenamos el vector de probabilidades y el de orden:
        ordenacionPorInsercion(probabilidades, orden, tam_orden);
    }

}

// Codificar un mensaje con el árbol de Huffman
void codificarCaracterHuffman(char *entrada, int hf[64][4], char * &salida, int &tamanioArbol){

    int pos=-1, len_salida;
    char *simbolo_cod = new char[20];
    int contador=0;
    char simbolo;
    for (int i =0; i<strlen(entrada);i++){
      simbolo = entrada[i];
      // Buscar símbolo en hf
      for (int j=0; j<tamanioArbol and pos==-1; j++){
          if (hf[j][0] == simbolo){
              pos = j;
          }
      }
      while (hf[pos][3] != -1){

          if (pos == hf[hf[pos][3]][1]){ // hijo izquierda // es un cero
              simbolo_cod[contador] = '0';
              contador++;

          } else { // hijo derecha // es un uno
              simbolo_cod[contador] = '1';
              contador++;
          }

          pos = hf[pos][3];
      }

      len_salida = contador;
      salida = new char[len_salida];
      // Damos la vuelta a la codificación
      for(int j=0; j<len_salida; j++,contador--){
        salida[j] = simbolo_cod[contador-1];
      }
    }
    salida[len_salida]='\0';
}

// -------------------------------------------------------------------------------- //

// Decodificar una secuencia de bits con el ábrol de Huffman
void decodificarHuffman(char *codificado, char *& salida, int hf[64][4], int tamanioArbol){

    int pos_dec=tamanioArbol -1;//raiz
    bool h_dch ;
    int cnt_salida = 0;
    salida=new char[strlen(codificado)];

    // Decodificado mensaje
    for (int i =0; i<strlen(codificado);i++){
      h_dch = codificado[i]=='1';

      if (h_dch)
        pos_dec = hf[pos_dec][2];
       else
        pos_dec = hf[pos_dec][1];

      if (hf[pos_dec][0]!='\0'){
        salida[cnt_salida] = hf[pos_dec][0];
        pos_dec = tamanioArbol-1;
        cnt_salida++;
      }
    }
    salida[cnt_salida]='\0';

}

int main(int argc, char ** argv){
  string cadena;
  string linea;
  double probabilidades[30];
  char alfabeto[30];
  int orden[30];
  int tamanio = 30;

  for(int i = 0; i < 30; i++){
    probabilidades[i] = 0;
  }

  std::ifstream archivo("quijote.txt");
	std::stringstream buffer;
	buffer << archivo.rdbuf();


  int matriz[64][4];

  calcularProbabilidades(buffer.str(), probabilidades, alfabeto);
  creaArbolHuffmann(alfabeto,probabilidades,matriz, tamanio);


  cout << "MATRIZ ÁRBOL DE CODIFICACIÓN:" << endl;
  for (int i = 0; i < tamanio; i++){
     cout << i << " ";
      for (int j = 0; j < 4; j++){
          if (j==0){
              cout << (char)(matriz[i][j]) << " ";
          } else {
              cout << (matriz[i][j]) << " ";
          }
      }
      cout << endl;
  }

  char* ba, *cod ;
  codificarCaracterHuffman(" ", matriz,ba ,tamanio );
  for (int j=0; j<strlen(ba); j++){
       cout << "codificado ["<< j << "] =" << ba[j] << endl;
  }
  decodificarHuffman(ba,cod,matriz,tamanio);
  for (int i = 0 ; i<strlen(cod); i++){
    cout << cod[i] << " " ;
  }
  return 0;
}
