#include <RF2272.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IniciarRF2272();

}


void MultiplicaZ2(int *palabra, int palabraSize, int Matriz[7][3], int ColMatriz, char* salida){

    int sum = 0;
    for (int i =0; i < ColMatriz; i++){
        for (int j =0; j<palabraSize; j++){
             sum += Matriz[j][i] * palabra[j];
        }
        salida[i] = (char) (sum %2) ;
        sum = 0;
    }
}

unsigned int sindrome(const uint8_t codigo, int *palabra, int palabraSize, int Matriz[7][3], int ColMatriz){
  char p[3];
  MultiplicaZ2(palabra,palabraSize,Matriz,ColMatriz,p);
  return strtol(p,NULL,2);
  
}



bool decodificar(const uint8_t codigo, bool pulsados[4]) {

    bool bitpar1 = ((codigo & (1<<0)) > 0);  // 0
    bool bitpar2 = ((codigo & (1<<1)) > 0);  // 1
    bool bitpar3 = ((codigo & (1<<3)) > 0);  // 3

    pulsados[0] = ((codigo & (1<<2)) > 0);   // 2
    pulsados[1] = ((codigo & (1<<4)) > 0);   // 4
    pulsados[2] = ((codigo & (1<<5)) > 0);   // 5
    pulsados[3] = ((codigo & (1<<6)) > 0);   // 6

    int error1 = (bitpar1 ^ pulsados[0] ^ pulsados[1] ^ pulsados[3]);
    int error2 = (bitpar2 ^ pulsados[0] ^ pulsados[2] ^ pulsados[3]);
    int error3 = (bitpar3 ^ pulsados[1] ^ pulsados[2] ^ pulsados[3]);

    // bit6 XOR BIT4 XOR BIT2 XOR BIT0
    // bit5 XOR BIT4 XOR BIT1 XOR BIT0
    // bit3 XOR BIT2 XOR BIT1 XOR BIT0

    return error1 + error2 + error1;
}

void loop() {
  bool botones[4]; 
  int palabra[7];
  int matriz[7][3] = {
    {1,1,1},
    {1,1,0},
    {1,0,1},
    {1,0,0},
    {0,1,1},
    {0,1,0},
    {0,0,1}};
  
  uint8_t v = leerRF2272();  
  if (decodificar(v , botones)){
    if (botones[0] || botones[1] || botones[2] || botones[3]){
          Serial.println("No se ha detectado ningun error.");

      Serial.print("El codigo recibido es: ");

      for (int i=6; i>=0; i--){
        if ( (v&(1<<i)) > 0 ){
          palabra[i] = 1;
          Serial.print(palabra[i]);
        }
        else{
          palabra[i] = 0;
          Serial.print(palabra[i]);
        }
      }
        
        Serial.print(", se ha pulsado: ");
        if (botones[0])
          Serial.print("A");
        if (botones[1])
          Serial.print("B");
        if (botones[2])
          Serial.print("C");
        if (botones[3])
          Serial.print("D");
        Serial.println();
      }
      
  }else{
    Serial.println("Se ha detectado un error.");
    // Arreglamos el error
    unsigned int err = sindrome(v,palabra,7,matriz,3);
    v = v^(1<<(err-1));

    if(decodificar(v, botones)){
      if (botones[0] || botones[1] || botones[2] || botones[3]){
        for (int i=6; i>=0; i--) {
          if ( (v&(1<<i)) > 0 )
            Serial.print("1");
          else
            Serial.print("0");
        }
        Serial.print(" ");
        if (botones[0])
          Serial.print("A");
        if (botones[1])
          Serial.print("B");
        if (botones[2])
          Serial.print("C");
        if (botones[3])
          Serial.print("D");
        Serial.println();
      }
    }
  }
  delay(100);
   
}
