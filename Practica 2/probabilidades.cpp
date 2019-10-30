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

  for(int i = 0; i < 31; ++i){
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
      for(; posicion < 31 && continua; ++posicion){
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

  for (size_t i = 0; i < 31; i++) {
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

}

void creaArbolHuffman(int **matriz, vector<double>probabilidades, char *alfabeto,vector<int>& nodos,int tamAlfabeto){

  //int n = pow(2,tamAlfabeto+1)-1;
  //int matriz[n][4];
  std::cout << "NODOS" << '\n';
  for(int i = 0; i < nodos.size(); i++)
    std::cout << nodos[i] << '\n';
  std::cout << "nodos.size() =" << nodos.size()<< '\n';
  // Inicializacion del alfabeto en la matriz
  int i;
  for (i = 0; i < tamAlfabeto; i++) {
    matriz[i][0] = alfabeto[i];
    matriz[i][1] = -1;
    matriz[i][2] = -1;
    matriz[i][3] = -1;
  }
  // Una vez que se ha inicializado la matriz con el alfabeto, se ponen
  // las demas casillas a caracter nulo.
  for (;i < 64;i++) {
    matriz[i][0] = '\0';
    matriz[i][1] = -1;
    matriz[i][2] = -1;
    matriz[i][3] = -1;
  }

  // El arbol de Huffman empieza teniendo los nodos hoja como orden.
  int arbolOrden = tamAlfabeto;
  // Empezamos el algoritmo de Huffman
  while(probabilidades.size() != 1){
    // Se escogen las probabilidades de los simbolos con menor probabilidad:
    probabilidades.push_back(probabilidades[probabilidades.size()-1]+ probabilidades[probabilidades.size()-2]);

    //TODO POP

    // Se le asigna al nuevo nodo sus hijos
    matriz[nodos.size()][1] = nodos[probabilidades.size()-2];
    matriz[nodos.size()][2] = nodos[probabilidades.size()-1];
    // Y por ultimo el padre
    matriz[nodos[probabilidades.size()-2]][3] = nodos.size();
    matriz[nodos[probabilidades.size()-1]][3] = nodos.size();

    // Se modifica el vector de nodos (Se eliminan los dos ultimos y se añade el nodo padre)
    nodos.pop_back();
    nodos.pop_back();
    nodos.push_back(arbolOrden);

    // En el caso de que solo quede uno
    // se ha terminado el algoritmo y solo queda definir el nodo raiz
    /*if(nodos.size() == 1){
      matriz[arbolOrden][3] = -1;
    }*/

    ordenacionPorInsercionNodo(probabilidades,alfabeto,nodos);

  }

  if(probabilidades.size() == 1){
    cout << "TERMINE!" << endl;
  }

}




int main(int argc, char ** argv){
  string cadena;
  string linea;
  vector<double> probabilidades(31,0);
  char alfabeto[31];
  vector<int> nodos(31);
  //int matriz[64][4];

  int** matriz = new int*[100];
  for (int i = 0; i < 100; ++i)
    matriz[i] = new int[4];

  for (int i = 0; i< nodos.size();i++){
    nodos[i]=i;
  }
  std::ifstream t("quijote.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();
  t.close();

  calcularProbabilidades(buffer.str(), probabilidades, alfabeto);
  ordenacionPorInsercionNodo(probabilidades, alfabeto,nodos);
  creaArbolHuffman(matriz,probabilidades,alfabeto,nodos, 31);

  std::cout << "MATRIZ" << endl;
  for (int i = 0; i < 31; i++){
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
//   double suma = 0;
//   for (int i = 0; i < 31; i++) {
//     if(alfabeto[i] != '\0'){
//       std::cout << probabilidades[i];
//       if(i != 29){
//         std::cout << ",";
//       }
//     }

//   }
//   for (int i = 0; i < 31; i++) {
//     if(alfabeto[i] != '\0'){
//       std::cout << alfabeto[i];
//       if(i != 29){
//         std::cout << ",";
//       }
//     }
//   }
// }

}
