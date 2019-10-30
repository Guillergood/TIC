#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include<vector>
using namespace std;


void calcularProbabilidades(string cadena, vector<double>& probabilidades, char *alfabeto){
  double sumatoria = 0;
  double sumatoria2 = 0;
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
      probabilidades[posicion]+=1;
      sumatoria++;
    }
    else{
      bool continua = true;
      posicion = 27;
      for(; posicion < 32 && continua; ++posicion){
        if(cadena[i] != '\n'){
          if(alfabeto[posicion] == '\0'){
            continua = false;
            probabilidades[posicion]+=1;
            sumatoria++;
            alfabeto[posicion] = cadena[i];
          }
          else if(alfabeto[posicion] == cadena[i]){
            continua = false;
            probabilidades[posicion]+=1;
            sumatoria++;
          }
        }
      }
    }
  }

  for (size_t i = 0; i < 32; i++) {
    probabilidades[i]/= sumatoria;
    sumatoria2 += probabilidades[i];
    if(alfabeto[i] != '\0'){
      simbolos++;
      std::cout << " SIMBOLO: "<< simbolos << " -> " << alfabeto[i] << endl;
    }

  }




  std::cout << " SUMATORIA: "<< sumatoria << endl;
  std::cout << " SUMATORIA2: "<< sumatoria2 << endl;
  std::cout << " SIMBOLOS: "<< simbolos << endl;
}


void ordenacionPorInsercion(vector<double>& probabilidades, char *alfabeto){
    int i, j;
    double probabilidadesObjetivo;
    char alfabetoObjetivo;
    for (i = 1; i < probabilidades.size(); i++)
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

void ordenacionPorInsercionNodo(vector<double>& probabilidades, char *alfabeto, vector<int>& nodos){
    int i, j, nodoObjetivo;
    double probabilidadesObjetivo;
    char alfabetoObjetivo;
    for (i = 1; i < probabilidades.size(); i++)
    {
        probabilidadesObjetivo = probabilidades[i];
        alfabetoObjetivo = alfabeto[i];
        nodoObjetivo = nodos[i];
        j = i-1;
        while (j >= 0 && probabilidades[j] < probabilidadesObjetivo){
            probabilidades[j+1] = probabilidades[j];
            alfabeto[j+1] = alfabeto[j];
            nodos[j+1] = nodos[j];
            j = j-1;

        }

        probabilidades[j+1] = probabilidadesObjetivo;
        alfabeto[j+1] = alfabetoObjetivo;
        nodos[j+1] = nodoObjetivo;
    }
        for (int i = 0; i<probabilidades.size(); i++){
      cout << probabilidades[i] << endl;
    }
}

// void creaArbolHuffman(int ** matriz, vector<double>probabilidades, char *alfabeto, int k){

//   int n = pow(2,k+1)-1;
//   int matrix[n][4];

//   //Inicializacion
//   for (size_t i = 0; i < n; i++) {
//     matrix[i][0] = '\0';
//     matrix[i][1] = -1;
//     matrix[i][2] = -1;
//     matrix[i][3] = -1;
//   }

// }




int main(int argc, char ** argv){
  string cadena;
  string linea;
  vector<double> probabilidades(32,0);
  char alfabeto[32];
  vector<int> nodos(32);
  for (int i = 0; i< nodos.size();i++){
    nodos[i]=i;
  }
  std::ifstream t("quijote.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();
  t.close();

  calcularProbabilidades(buffer.str(), probabilidades, alfabeto);
  ordenacionPorInsercionNodo(probabilidades, alfabeto,nodos);


  //creaArbolHuffmann(matriz,probabilidades,alfabeto, 30);

  cout << "asdfasdfad" << endl;
//   double suma = 0;
//   for (int i = 0; i < 32; i++) {
//     if(alfabeto[i] != '\0'){
//       std::cout << probabilidades[i];
//       if(i != 29){
//         std::cout << ",";
//       }
//     }

//   }
//   for (int i = 0; i < 32; i++) {
//     if(alfabeto[i] != '\0'){
//       std::cout << alfabeto[i];
//       if(i != 29){
//         std::cout << ",";
//       }
//     }
//   }
// }

}
