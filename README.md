# Proyecto de identificación de tarjetas RFID mediante el uso de Arduino 1

Autores: <\Sergio Isidoro De Anca Garabito\>   uvus:\<Serdegar1\>

TODO descripción del proyecto (objetivos, más tarde se detallará su funcionamiento)

## Estructura de ficheros del proyecto

* **/src**: Contiene los ficheros .ino útiles para el funcionamiento del programa.
  * **\<Identificador_pases.ino\>**: Este módulo es un ejemplo de la librería MRFC22, el cúal vamos a usar para conococer el UID de las tarjetas. A futuro se personalizara para faciltar esta tarea
  * **\<Identificador_usuario.ino\>**: Este módulo es el que se enviara a la placa aurduino 1 para su funcionamiento.
* **/Modelos**: Contiene posibles modelos del circuito a construir
    * **\<.PNG\>**: 

## Ideas/objetivos para añadir en un futuro
 * Guardar el contador de las veces que se ha leido la tarjeta/llavero en su propia memoria y no en la de arduino
 * Reconocer cuando el usuario esta dentro o fuera del edificio(es decir que el usuario pique al entrar y al salir)
 * Registrar la hora en la que se produce cada lectura
 * Reproducir un sonido concreto según que usuario ha sido identificado
