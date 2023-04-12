/* 
Este módulo sirve para probar el funcionamineto de la panralla LCD 
Tambien sirve para probar la funcion printLCD(byte usuario, int cont)
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

  lcd.begin(16, 2);              //Declaro que la lcd es de 16*2
}

void loop(){
    lcd.setCursor(0,0);                 //Cuando se empiece a escribir algo en la pantalla sera desde la posición 0, 0
    lcd.print("Pase su tarjeta");       //Se imprime en la pantalla pase su tarjeta

  if ( ! mfrc522.PICC_IsNewCardPresent())		// vuelve al loop hasta que haya una tarjeta
    return;						                

  if ( ! mfrc522.PICC_ReadCardSerial()) 		// vuelve al loop si no se puede leer esa tarjeta
    return;						                
    
 if(comparaUID(LecturaUID, Usuario1)){	// llama a funcion comparaUID con Usuario1
            /*Muestro informacion relevante en la pantalla lcd*/
            /*Imprime por pantalla: 
                Bienvenido usuario 1
                Visitas: n

                Como la primera linea tiene mas de 16 lineas, se usa scrolldisplay para ver todo lo impreso
                */

            //TO DO --> Convertir esto en una función para que el if no sea tan largo
            lcd.setCursor(0,0);
            lcd.print("Bienvenido usuario 1");
            lcd.setCursor(0,1);
            lcd.print("Visitas: "+cont1);
            delay(2000);

            /*Uso bucle para ver lo que pone en toda la primera linea*/
            for(int i = 0; i<10; i++){
                lcd.scrollDisplayLeft();
                delay(300);
            }

            lcd.clear();

            /*****
                MÁS ADELANTE ESCRIBIRE EL CONTADOR DIRECTAMENTE SOBRE LA TARJETA PARA NO TENER QUE USAR LA MEMORIA DEL ARDUINO
            ****/
             } else if(comparaUID(LecturaUID, Usuario2)){	// llama a funcion comparaUID con Usuario
                printLCD(Usuario2, cont2);
             }else{						// si retorna fals
           lcd.print("Illo tu quien ere");
          // delay(200);
           lcd.clear();
                  mfrc522.PICC_HaltA();  		// detiene comunicacion con tarjeta                
             }
}


void printLCD(byte usuario, int cont){
  lcd.setCursor(0,0);
  lcd.print("Bienvenido usuario"+usuario);
  lcd.setCursor(0,1);
  lcd.print("Visitas: "+cont);
  delay(2000);
  /*Uso bucle para ver lo que pone en toda la primera linea*/
  for(int i = 0; i<10; i++){
      lcd.scrollDisplayLeft();
      delay(300);
  }
  lcd.clear();
  
}