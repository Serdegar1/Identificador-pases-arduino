/* 
Este módulo sirve para probar el funcionamineto del indentidicador de usuarios usadno las UID ya conocidas
Tambien sirve para probar la funcion comaraUID(LecturaUID, Usuario)
*/

#include <SPI.h>			    // libreria para bus SPI
#include <MFRC522.h>			// libreria para MFRC522(nuestro lector)
#include <LiquidCrystal.h>      // libreria para pantalla lcd


#define RST_PIN  9			// pin reset del MFRC522
#define SS_PIN  10			// pin slave select del MFRC522

MFRC522 mfrc522(SS_PIN, RST_PIN);	// crea mfrc522 con ss y rst

byte LecturaUID[4]; 				                  // UID leido
byte Usuario1[4]= {/* 0xXX, 0xXX, 0xXX, 0xXX */} ;    // UID guardado del usuario 1 (obtenido con el programa de ejemplo de la libreria importada)
byte Usuario2[4]= {/* 0xXX, 0xXX, 0xXX, 0xXX */} ;    // UID guardado del usuario 2


void setup() {
  Serial.begin(9600);			// inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();				    // inicializa bus SPI
  mfrc522.PCD_Init();			// inicializa modulo lector
  Serial.println("Listo");		// Muestra texto Listo
}


void loop() {    
  if ( ! mfrc522.PICC_IsNewCardPresent())		// vuelve al loop hasta que haya una tarjeta
    return;						                

  if ( ! mfrc522.PICC_ReadCardSerial()) 		// vuelve al loop si no se puede leer esa tarjeta
    return;						                

        /****************/
        /***PARSEO UID***/
        /****************/

Serial.print("UID:");				            // muestra texto UID:
    
    for (byte i = 0; i < mfrc522.uid.size; i++) {	// bucle recorre de a un byte por vez el UID
      if (mfrc522.uid.uidByte[i] < 0x10){		    // si el byte leido es menor a 0x10
        Serial.print(" 0");				            // imprime espacio en blanco y numero cero
        }else{						                // sino
          Serial.print(" ");				        // imprime un espacio en blanco
        }
        Serial.print(mfrc522.uid.uidByte[i], HEX);// imprime el byte del UID leido en hexadecimal
        LecturaUID[i]=mfrc522.uid.uidByte[i];   	// almacena en array el byte del UID leido      
    }      
    Serial.print("\t");   			        // imprime un espacio de tabulacion             
          
        /***************************************************************************/
        /***COMPARADOR IF PARA ESCRIBIR SOBRE LA TERMINAL LA TARJETA IDENTIFICADA***/
        /***************************************************************************/

    if(comparaUID(LecturaUID, Usuario1)){		// llama a funcion comparaUID con Usuario1
        /*Muestro información relevante en el terminal*/
        Serial.println(); 
        Serial.println("Bienvenido Usuario 1");	// si retorna verdadero muestra texto bienvenida
        Serial.println("Numero de veces que Usuario1 visitado la casa"+cont1);
        cont1 +=1;
    }else if(comparaUID(LecturaUID, Usuario2)){	// llama a funcion comparaUID con Usuario2
        Serial.println("Bienvenido Usuario 2");	// si retorna verdadero muestra texto bienvenida
        cont2 +=1;
    }else{						// si retorna falso
        Serial.println("No te conozco"); 		// muestra texto equivalente a acceso denegado          
    }  
                  mfrc522.PICC_HaltA();  		// detiene comunicacion con tarjeta     
}

boolean comparaUID(byte lectura[],byte usuario[]){	// funcion que comprueba si la tarjeta leida es una de las almacenadas en el programa
  for (byte i=0; i < mfrc522.uid.size; i++){		// recorre Bs de UID
  if(lectura[i] != usuario[i])				        // si B UID leido != B UID usuario
    return(false);					                // false        
  }
  return(true);						                // si los 4 B coinciden, return true
}
