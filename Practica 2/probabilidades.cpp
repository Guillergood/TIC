#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

class Nodo{
  private int index;
  private
}

void calcularProbabilidades(string cadena, float *probabilidades, char *alfabeto){
  float sumatoria = 0;
  float sumatoria2 = 0;
  int posicion = 0;
  int simbolos = 0;

  for(int i = 0; i < 32; ++i){
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
      posicion = 27;
      for(; posicion < 32 && continua; ++posicion){
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

  for (size_t i = 0; i < 32; i++) {
    sumatoria2 += probabilidades[i];
    probabilidades[i]/= sumatoria;
    if(alfabeto[i] != '\0'){
      simbolos++;
      std::cout << " SIMBOLO: "<< simbolos << " -> " << alfabeto[i] << endl;
    }

  }




  std::cout << " SUMATORIA: "<< sumatoria << endl;
  std::cout << " SUMATORIA2: "<< sumatoria2 << endl;
  std::cout << " SIMBOLOS: "<< simbolos << endl;
}


void ordenacionPorInsercion(float *probabilidades, char *alfabeto, int tamanio){
    int i, j;
    float probabilidadesObjetivo;
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

void creaArbolHuffman(int ** matriz, float *probabilidades, char *alfabeto, int k){

  int n = pow(2,k+1)-1;
  int matrix[n][4];

  //Inicializacion

  for (size_t i = 0; i < n; i++) {
    matrix[i][0] = '\0';
    matrix[i][1] = -1;
    matrix[i][2] = -1;
    matrix[i][3] = -1;
  }


}




int main(int argc, char ** argv){
  string cadena;
  string linea;
  float probabilidades[30];
  char alfabeto[30];

  for(int i = 0; i < 30; i++)
    probabilidades[i] = 0;

  std::ifstream t("quijote.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();

  calcularProbabilidades(buffer.str(), probabilidades, alfabeto);
  ordenacionPorInsercion(probabilidades, alfabeto, 30);
  creaArbolHuffmann(matriz,probabilidades,alfabeto, 30);



  /*float suma = 0;
  std::cout << "{";
  for (size_t i = 0; i < 32; i++) {
    if(alfabeto[i] != '\0'){
      std::cout << probabilidades[i];
      if(i != 29){
        std::cout << ",";
      }
    }

  }
  std::cout << "}" << endl;

  std::cout << "{";
  for (size_t i = 0; i < 32; i++) {
    if(alfabeto[i] != '\0'){
      std::cout << alfabeto[i];
      if(i != 29){
        std::cout << ",";
      }
    }
  }
  std::cout << "}" << endl;*/



}
