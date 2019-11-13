
#define TAU 50
#define MAX_LEN 100
String leido;

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
{','-1,-1,55},
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
};
int tam = 59;
char salida[MAX_LEN];
// Codificar un mensaje con el árbol de Huffman
void codificarHuffman(char entrada[], int hf[64][4], char salida[], int &tamanioArbol){

    int pos=-1, len_salida, contador=0, inicio=0;
    char simbolo_cod [MAX_LEN];
    char simbolo;

    for (int i =0; i<MAX_LEN;i++){
      salida[i]='\0';
      simbolo_cod[i]='\0';
    }

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
      // Damos la vuelta a la codificación
      for(int j=inicio; j<inicio+len_salida; j++,contador--){
        salida[j] = simbolo_cod[contador-1];
      }
      inicio+=len_salida;
      pos=-1;
    }
    salida[inicio+len_salida]='\0';
}

void pulseDown(){
  digitalWrite(8,LOW);
  delay(TAU);
}

void sendBit(char bit){
  digitalWrite(8,HIGH);
  if(bit == '1'){
      delay(TAU*2);
  }else{
      delay(TAU);
  }
  pulseDown();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available()){
      leido = Serial.readString();
      char leido_c[MAX_LEN];
      strcpy(leido_c,leido.c_str());
      codificarHuffman(leido_c,mat, salida,tam);
      for (int i =0; i< strlen(salida); i++){
        sendBit(salida[i]);
      }
        
     }
}
    
