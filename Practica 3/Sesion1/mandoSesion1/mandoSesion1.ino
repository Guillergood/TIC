#include <RF2272.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IniciarRF2272();
  
}

int decode(const uint8_t codigo, bool pulsados[4]){
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
  // put your main code here, to run repeatedly:
  String codigo="";
  bool botones[4];
  uint8_t v = leerRF2272();
  
  int bit;
  if (v!=0){
    if (!decode(v,botones)){
      Serial.print(" No hay fallos.");
      for (int i=6; i>=0;i--){
        bit = (1<<i);
        if ((v&bit)>0){
          codigo= codigo + '1';
          
          }else{
            codigo=codigo+'0';
            }
        }
       Serial.print("El codigo recibido es: ");
       Serial.println(codigo);

      Serial.print("Se ha pulsado: ");
      if (botones[0])
          Serial.print("A");
      if (botones[1])
          Serial.print("B");
      if (botones[2])
          Serial.print("C");
      if (botones[3])
          Serial.print("D");
      Serial.println();
    }else
      Serial.println("Se ha producido un error. ");


    delay(100);
   }
}
