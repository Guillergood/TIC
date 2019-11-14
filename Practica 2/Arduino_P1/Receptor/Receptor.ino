
#define TAM 100
#define FRACCION 2
#define TAU 50


char almacenador[TAM];
int totalUtilizados = 0;
String cadena = "";
char salida[TAM] ;
/*
int mat[64][4]= {
{'A',-1,-1,52},
{'B',-1,-1,39},
{'C',-1,-1,44},
{'D',-1,-1,46},
{'E',-1,-1,53},
{'F',-1,-1,35},
{'G',-1,-1,38},
{'H',-1,-1,37},
{'I',-1,-1,47},
{'J',-1,-1,34},
{'K',-1,-1,30},
{'L',-1,-1,47},
{'M',-1,-1,42},
{'N',-1,-1,48},
{'O',-1,-1,51},
{'P',-1,-1,40},
{'Q',-1,-1,39},
{'R',-1,-1,48},
{'S',-1,-1,49},
{'T',-1,-1,43},
{'U',-1,-1,45},
{'V',-1,-1,36},
{'W',-1,-1,30},
{'X',-1,-1,31},
{'Y',-1,-1,38},
{'Z',-1,-1,33},
{' '-1,-1,55},
{'.',-1,-1,34},
{',',-1,-1,41},
{';',-1,-1,32},
{0,10,22,31},
{0,23,30,32},
{0,29,31,33},
{0,25,32,35},
{0,9,27,36},
{0,33,5,37},
{0,21,34,40},
{0,35,7,41},
{0,24,6,42},
{0,16,1,43},
{0,15,36,44},
{0,28,37,45},
{0,12,38,46},
{0,19,39,49},
{0,40,2,50},
{0,20,41,50},
{0,42,3,51},
{0,11,8,52},
{0,13,17,53},
{0,18,43,54},
{0,45,44,54},
{0,46,14,55},
{0,0,47,56},
{0,4,48,56},
{0,50,49,57},
{0,26,51,57},
{0,53,52,58},
{0,55,54,58},
{0,57,56,-1}
};*/

int mat[64][4]=
{{'A',-1,-1,52},
{'B',-1,-1,39},
{'C',-1,-1,44},
{'D',-1,-1,46},
{'E',-1,-1,53},
{'F',-1,-1,35},
{'G',-1,-1,38},
{'H',-1,-1,37},
{'I',-1,-1,47},
{'J',-1,-1,34},
{'K',-1,-1,30},
{'L',-1,-1,47},
{'M',-1,-1,42},
{'N',-1,-1,48},
{'O',-1,-1,51},
{'P',-1,-1,40},
{'Q',-1,-1,39},
{'R',-1,-1,48},
{'S',-1,-1,49},
{'T',-1,-1,43},
{'U',-1,-1,45},
{'V',-1,-1,36},
{'W',-1,-1,30},
{'X',-1,-1,31},
{'Y',-1,-1,38},
{'Z',-1,-1,33},
{' ',-1,-1,55},
{'.',-1,-1,34},
{',',-1,-1,41},
{';',-1,-1,32},
{'\0',10,22,31},
{'\0',23,30,32},
{'\0',29,31,33},
{'\0',25,32,35},
{'\0',9,27,36},
{'\0',33,5,37},
{'\0',21,34,40},
{'\0',35,7,41},
{'\0',24,6,42},
{'\0',16,1,43},
{'\0',15,36,44},
{'\0',28,37,45},
{'\0',12,38,46},
{'\0',19,39,49},
{'\0',40,2,50},
{'\0',20,41,50},
{'\0',42,3,51},
{'\0',11,8,52},
{'\0',13,17,53},
{'\0',18,43,54},
{'\0',45,44,54},
{'\0',46,14,55},
{'\0',0,47,56},
{'\0',4,48,56},
{'\0',50,49,57},
{'\0',26,51,57},
{'\0',53,52,58},
{'\0',55,54,58},
{'\0',57,56,-1},
};


int recvBit(){
  int contador = 0;

  while(contador <= FRACCION && digitalRead(7) == LOW){
    contador++;
    delay(TAU/FRACCION);
  }
  if (contador > FRACCION){
    return -1;
  }
  else{
    contador = 0;
    while(digitalRead(7) == HIGH){
      contador++;
      delay(TAU/FRACCION);
    }
    if(contador > FRACCION){
      return 1;
    }
    else{
      return 0;
    }
  }
}

// Decodificar una secuencia de bits con el ábrol de Huffman
void decodificarHuffman(char codificado[], char salida[], int hf[64][4], int tamanioArbol){

    int pos_dec=tamanioArbol -1;//raiz
    bool h_dch ;
    int cnt_salida = 0;
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  totalUtilizados = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  int elBit = 0;
  while(elBit != -1){
    elBit = recvBit();
    if (elBit != -1) {
      almacenador[totalUtilizados] = '0'+elBit;
      ++totalUtilizados;
    }
  }

  if(totalUtilizados != 0){
   decodificarHuffman(almacenador,salida,mat,59);
   totalUtilizados = 0;
   Serial.println(salida);
   Serial.println('\n');
  }


}
