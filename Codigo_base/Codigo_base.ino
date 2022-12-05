/* Para cambiar el número de datos, ir a línea 22
Se se trabaja en serial: descomentar línea 67, elminar lineas 49-57, 65, 74
*/

#include <SD.h> //librería para acceder a SD
const int pin=A0; //pin donde se coloca el sensor MQ135
const int pin2=A1; //pin donde se coloca el thermistor

/* Esquema de conexión tarjeta SD
SD reader -> Arduino

+3.3 -> 3v3
Gnd -> Gnd
CS -> 4
MOSI -> 11
SCK -> 13
MISO -> 12
*/


int nombre=1; //nombre del archivo
int n=500; //contador, números de datos que se quieren

File archivo; //declarando variale archivo

void medir(){ //función que mide desde el sensor y guarda en archivo abierto
unsigned long dato=analogRead(pin);	 //mide el pin1 y almacena en "dato"
unsigned long dato2=analogRead(pin2);	//mide el pin2 y almacena en "dato2"
archivo.println("");	//crea nueva fila
archivo.print(dato);	//imprime medida 1
archivo.print(" ");	//separación entre medidas
archivo.print(dato2);	//imrpime medida 2
}

void medir_serial(){ //función que mide y envía a serial (igual que void medir(), adaptado para serial)
unsigned long dato=analogRead(pin);
unsigned long dato2=analogRead(pin2);
Serial.prinln("");
Serial.print(dato);
Serial.print(" ");
Serial.print(dato2);

}

void setup(){ //configuración inicial 
	Serial.begin(9600); //inicia el puerto serial para comprobar errores

//Si se va a medir a serial, eliminar las siguientes 9 líneas (o comentarlas)
 	if (!SD.begin(4)) {
    		Serial.println("Fallo en SD"); //si no logra abrir la sd, no continúa y muestra el mensaje en serial
    	while (1);
  }
 	Serial.println("Inicio de SD correcto"); //si logra iniciar correctmente la SD muestra el mensaje
 	while(SD.exists(nombre)){
		nombre++; //si el nombre existe en sd, cambiar nombre sumando 1 hasta llegar a un nombre que no exista
	}
archivo = SD.open(nombre,FILE_WRITE); //abre archivo con el nombre asignado
}

void loop(){ //función que se ejecuta en bucle (principal)

while(n>0){  //mientras el contador no llegue a 0
n-- ;   //disminuye 1 al contador

medir(); //mide y guarda en SD

//medir_serial();     //descomentar (y comentar medir()) para medir en serial.


delay(1000); //tiempo de espera en ms
}

if(n<=0){ //cuando el contador sea menor o igual a 0
archivo.close(); //cierra el archivo  (comentar o eliminar esta linea si se trabaja en serial)
delay(2500000); //espera una gran cantidad de tiempo
}
}
