
#define TAM 200
#define FRACCION 2
#define TAU 50

char almacenador[TAM];
int totalUtilizados = 0;
//String alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,;. |";
char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,;. |";
unsigned int index = 0;
String cadena = "";

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  totalUtilizados = 0;
  index = 0;
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

    index = 0;
    for(int i = 0, k = 0; i < totalUtilizados; ++i,++k){
      if(k == 5){
        //Serial.println(index);
        Serial.print(alfabeto[index]);
        index=0;
        k=0;
      }
      index<<=1;
      if(almacenador[i] == '1'){
        index |= 1;
      }
    }
    //Serial.println(index);
    //cadena += alfabeto.charAt(index);
    Serial.print(alfabeto[index]);

    //Serial.println(cadena);
    totalUtilizados = 0;
  }


}
