#ifndef __TARJETERO__H_
#define __TARJETERO__H_
#include <Arduino.h>
// Inicializa el módulo MF RC522 con probabilidad de errores en 1 ó 1 bit dadas
void initMFRC522(float pError1=0.1, float pError2=0.2);

// Devuelve true si detecta una nueva tarjeta cerca. False en otro caso
bool isCardDetected();


// Lee el UID de la tarjeta cercana al lector y lo devuelve como cadena (max 32 bytes)
// Devuelve false y cadena vacía "" si no se leyó el UID
bool readUIDCard(char *uid);


// Lee 64 bytes de la tarjeta
bool readCard(uint16_t data[32]);

// Escribe 64 bytes en la tarjeta
bool writeCard(uint16_t data[32]);

// Cierra las comunicaciones con la tarjeta actual activa
void closeCard();
#endif
