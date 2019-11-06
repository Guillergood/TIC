
#define TAU 50
String leido;
String alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,;. |";
const int TAMANIO = 31;
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
      for(int i = 0; i != leido.length(); ++i){
        char elemento = leido[i];
        int posicion;
        if(elemento >= 'A' && elemento <= 'Z'){
          posicion = elemento - 'A';
        }
        else{
          bool continua = true;
          posicion = alfabeto.length() - 5;

          for(; posicion < alfabeto.length() && continua; ++posicion){
            if(alfabeto.charAt(posicion) == elemento){
              /*Serial.println(posicion);
              Serial.println(alfabeto.charAt(posicion));*/
              continua = false;
            }
          }
          posicion--;
        }

        sendBit((posicion & ( 16 )) >> 4);
        sendBit((posicion & ( 8 )) >> 3);
        sendBit((posicion & ( 4 )) >> 2);
        sendBit((posicion & ( 2 )) >> 1);
        sendBit(posicion &  1);
      }
    }

}
