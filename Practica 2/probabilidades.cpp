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


void ordenacionPorInsercion(double *probabilidades, char *alfabeto, int tamanio){
    int i, j;
    double probabilidadesObjetivo;
    char alfabetoObjetivo;
    for (i = 1; i < tamanio; i++)
    {
        probabilidadesObjetivo = probabilidades[i];
        alfabetoObjetivo = alfabeto[i];
        j = i-1;
        while (j >= 0 && probabilidades[j] < probabilidadesObjetivo){
            probabilidades[j+1] = probabilidades[j];
            alfabeto[j+1] = alfabeto[j];
            j = j-1;
        }
        probabilidades[j+1] = probabilidadesObjetivo;
        alfabeto[j+1] = alfabetoObjetivo;
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


void creaArbolHuffmann(char *alfabeto, double * probabilidades, int matriz[64][4], int tree_size){

    const int TAMALFABETO = tree_size;

    int orden[TAMALFABETO]; //vector que guarda las posiciones de los códigos
    //char *orden = new char[TAMALFABETO];

    for (int i = 0; i < TAMALFABETO; i++){
        orden[i] = i;
    }

    // Inicializamos los nodos raiz.
    for(int i = 0; i < TAMALFABETO;  i++){
        matriz[i][0] = alfabeto[i];
        matriz[i][1] = -1;
        matriz[i][2] = -1;
    }

    for(int i = TAMALFABETO; i < 64; i++){
        matriz[i][0] = '\0';
    }

    //Definimos las variables para el tamaño del arbol y para el tamaño
    // del vector de orden:
    int tam_orden = TAMALFABETO;

    // comenzamos a rellenar el arbol mediante Huffman hasta
    // que tam_orden sea igual a 1, es decir, hasta que lleguemos a la raiz:
    while(tam_orden != 1){

        //Sumamos la probabilidad de los dos elementos con menor probabilidades:
        probabilidades[tam_orden-2]=probabilidades[tam_orden - 2]+ probabilidades[tam_orden-1];

        //Asignamos al nuevo nodo generado sus dos hijos:
        matriz[tree_size][1] = orden[tam_orden-2];
        matriz[tree_size][2] = orden[tam_orden-1];

        //Ahora asignamos a los dos nodos hijos su nuevo padre:
        matriz[ orden[tam_orden-2] ][3] = tree_size;
        matriz[ orden[tam_orden-1] ][3] = tree_size;

        // Modificamos el vector orden
        orden[tam_orden-2]= tree_size;

        //reducimos el tamaño del vector orden:
        tam_orden--;

        //En caso de que hayamos terminado, indicamos en el nodo que este es la raiz:
        if(tam_orden == 1){
            matriz[tree_size][3] = -1;
            //int raiz = hf[tree_size][3];
        }

        //Aumentamos el tamaño del arbol:
        tree_size++;

        //Reordenamos el vector de probabilidades y el de orden:
        ordenacionPorInsercion(probabilidades, orden, tam_orden);
    }

}




// Codificar un mensaje con el árbol de Huffman
void codificarHuffman(char * cadena, int hf[64][4], bool * &codificado, int &tree_size){

    unsigned short c;
    int tam;
    char simbolo;
    int pos;
    int padre;
    codificado = new bool[20];
    int contador;

    //Obtenemos el tamaño de la cadena
    int n = strlen(cadena);
    cadena[n] = '*';

    for (int i=0;i<=n; i++){
        simbolo = cadena[i];

        // Buscar símbolo en hf
        pos = -1;
        for (int j=0; j<tree_size and pos==-1; j++){
            if (hf[j][0] == simbolo){
                pos = j;
            }
        }

        contador = 0;

        while (hf[pos][3] != -1){
            int padre = hf[pos][3];

            if (pos == hf[padre][1]){ // hijo izquierda // es un cero
                codificado[contador] = false;
                contador++;

            } else { // hijo derecha // es un uno
                codificado[contador] = true;
                contador++;
            }

            pos = padre;
        }

        // Enviar () --> sendLaserBit
        for (int j=contador-1; j>=0; j--){
            cout << (int)codificado[j];
        }

        cout << " ";
    }

    for(int i=0; i<contador; i++,contador--){
        bool aux = codificado[i];
        codificado[i] = codificado[contador];
        codificado[contador] = aux;
    }
}

// -------------------------------------------------------------------------------- //

// Decodificar una secuencia de bits con el ábrol de Huffman
void decodificarHuffman(char *codificado, int hf[64][4], int tree_size){

    int pos_dec = -1;
    int contador_dec = 0;
    char mensaje[100];
    bool recibido ;
    char letra = '\0';
    char bufferSalida[101];
    int utilbufferSalida;
    int poscodificado = 0;

    // Decodificado mensaje
    utilbufferSalida=0;

    while (letra != '*'){

        pos_dec = tree_size-1; // raíz
        letra = '\0';

        // Decodificado bit a bit
        while (letra=='\0') {

            // Simulación de recvLaserBit
            recibido = ((char)(codificado[poscodificado]))=='1';
            poscodificado++;

            // es hijo izquierda
            if (!recibido){
                pos_dec = hf[pos_dec][1];
            } else { // es hijo derecha
                pos_dec = hf[pos_dec][2];
            }

            if (hf[pos_dec][1] == -1 and hf[pos_dec][2] == -1){
                // nodo hoja y decodificamos
                letra = hf[pos_dec][0];
                bufferSalida[utilbufferSalida] = letra;
                utilbufferSalida++;

                pos_dec = tree_size-1; // raíz
            }
        }
    }

    // Enviar usb
    bufferSalida[utilbufferSalida-1] = '\0';

    for (int i= 0; i<utilbufferSalida;i++)
        cout << bufferSalida[i];

    cout << endl;
}





int main(int argc, char ** argv){
  string cadena;
  string linea;
  double probabilidades[30];
  char alfabeto[30];

  int tamanio = 30;

  for(int i = 0; i < 30; i++)
    probabilidades[i] = 0;

  std::ifstream t("quijote.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();


  int matriz[64][4];

  calcularProbabilidades(buffer.str(), probabilidades, alfabeto);
  ordenacionPorInsercion(probabilidades, alfabeto, tamanio);
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


  return 0;
}
