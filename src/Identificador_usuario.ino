/*
  Este programa identidica los usuarios que antes han sido leidos
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

int cont1 = 0;          //Contadores para cada usuario 
int cont2 = 0;          //Más adelante seran eliminados cuando sepa guardar este valor en el propio chip

/*VARIABLES PARA PANTALLA LCD --> DECLARACION PINES LCD --- VALORES PINES ARDUINOS  */
int rs = 12;
int e = 11;
int d4 = 5; 
int d5 = 4;
int d6 = 3;
int d7 = 2;

LiquidCrystal lcd(rs, e, d4, d5 ,d6, d7);       //Creo la pantalla lcd



void setup() {
  Serial.begin(9600);			// inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();				    // inicializa bus SPI
  mfrc522.PCD_Init();			// inicializa modulo lector
  Serial.println("Listo");		// Muestra texto Listo


  lcd.begin(16, 2)              //Declaro que la lcd es de 16*2

}

void loop() {
    
    lcd.setCursor(0,0);                 //Cuando se empiece a escribir algo en la pantalla sera desde la posición 0, 0
    lcd.print("Pase su tarjeta");       //Se imprime en la pantalla pase su tarjeta

  if ( ! mfrc522.PICC_IsNewCardPresent())		// vuelve al loop hasta que haya una tarjeta
    return;						                

  if ( ! mfrc522.PICC_ReadCardSerial()) 		// vuelve al loop si no se puede leer esa tarjeta
    return;						                
    

      /*a
        PARSEA UID PARA IMPRIMIR , ESTO LO QUITARE
      */

    Serial.print("UID:");				// muestra texto UID:
    
    for (byte i = 0; i < mfrc522.uid.size; i++) {	// bucle recorre de a un byte por vez el UID
      if (mfrc522.uid.uidByte[i] < 0x10){		// si el byte leido es menor a 0x10
        Serial.print(" 0");				// imprime espacio en blanco y numero cero
        }
        else{						// sino
          Serial.print(" ");				// imprime un espacio en blanco
          }
          Serial.print(mfrc522.uid.uidByte[i], HEX);   	// imprime el byte del UID leido en hexadecimal
          LecturaUID[i]=mfrc522.uid.uidByte[i];   	// almacena en array el byte del UID leido      
          }
          
          Serial.print("\t");   			// imprime un espacio de tabulacion             

    /*
    FIN PARSEO UID
    */                
            /***************************************************************************/
            /***COMPARADOR IF PARA ESCRIBIR SOBRE LA TERMINAL LA TARJETA IDENTIFICADA***/
            /***************************************************************************/

          if(comparaUID(LecturaUID, Usuario1))		// llama a funcion comparaUID con Usuario1

            /*Muestro información relevante en el terminal*/
            Serial.println(); 
            Serial.println("Bienvenido Usuario 1");	// si retorna verdadero muestra texto bienvenida
            Serial.println("Numero de veces que Usuario1 visitado la casa"+cont1);
            cont1 +=1;

          else if(comparaUID(LecturaUID, Usuario2))	// llama a funcion comparaUID con Usuario2
            Serial.println("Bienvenido Usuario 2");	// si retorna verdadero muestra texto bienvenida
            cont2 +=1;
            
           else						// si retorna falso
            Serial.println("No te conozco"); 		// muestra texto equivalente a acceso denegado          
                  
                  mfrc522.PICC_HaltA();  		// detiene comunicacion con tarjeta     

            /***************************************************************************/
            /***COMPARADOR IF PARA ESCRIBIR SOBRE LA PANTALLA LA TARJETA IDENTIFICADA***/
            /***************************************************************************/

            

            if(comparaUID(LecturaUID, Usuario1))		// llama a funcion comparaUID con Usuario1
            /*Muestro informacion relevante en la pantalla lcd*/
            /*Imprime por pantalla: 
                Bienvenido usuario 1
                Visitas: n

                Como la primera linea tiene mas de 16 lineas, se usa scrolldisplay para ver todo lo impreso
                */

            //TO DO --> Convertir esto en una función para que el if no sea tan largo
            lcd.SetCursor(0,0);
            lcd.print("Bienvenido usuario 1");
            lcd.SetCursor(0,1);
            lcd.print("Visitas: "+cont1);
            delay(2000);

            /*Uso bucle para ver lo que pone en toda la primera linea*/
            for(int i = 0; i<10; i++){
                led.scrolldisplayLeft();
                delay(300);
            }

            lcd.clear;

            /*****
                MÁS ADELANTE ESCRIBIRE EL CONTADOR DIRECTAMENTE SOBRE LA TARJETA PARA NO TENER QUE USAR LA MEMORIA DEL ARDUINO
            ****/
          else if(comparaUID(LecturaUID, Usuario2))	// llama a funcion comparaUID con Usuario
            lcd.SetCursor(0,0);
            lcd.print("Bienvenido usuario 2");
            lcd.clear
           else						// si retorna fals
           lcd.print("Illo tu quien ere");
           lcd.clear
                  mfrc522.PICC_HaltA();  		// detiene comunicacion con tarjeta                

}

boolean comparaUID(byte lectura[],byte usuario[])	// funcion que comprueba si la tarjeta leida es una de las almacenadas en el programa
{
  for (byte i=0; i < mfrc522.uid.size; i++){		// recorre Bs de UID
  if(lectura[i] != usuario[i])				        // si B UID leido != B UID usuario
    return(false);					                // false        
  }
  return(true);						                // si los 4 B coinciden, return true
}