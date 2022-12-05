//incluimos las librerias necesarias
#include <SPI.h>
#include <SD.h>
#include <math.h>
float sensorValue; //define la variable sensorValue como flotante
float volts;//define la variable volts como flotante
File myFile; //declaramos el archivo como una variable
int Ro = 5200;//Ro calculado con el programa anterior
int R2 = 2000;//Valor de R entre los pines A0 y GND del sensor 
float razon;//establece "razon" como variable de tipo flotante
float RS;//establece "RS" como variable de tipo flotante
float ppm_gas;//establece "ppm_gas" o concentración como variable de tipo flotante
float base;//establece base como variable de tipo flotante

//THERMISTOR
const int Rc = 10000; //valor de la resistencia a 25° C
const int Vcc = 5;
const int SensorPIN = A2;//PIN DE ENTRADA
float A = 5.828901355e-3;// COEFICIENTES DE LA ECUACIÓN
float B = -2.57992903e-4;
float C = -1.34628836e-7;
float K = 12.0; //factor de disipacion en mW
//THERMISTOR
void setup() {
  Serial.begin(9600);//inicializa la comunicación serial.
  Serial.println("LABEL,Time,contador,sensorValue,volts,ppm_gas,TEMP");
  while (!Serial) {
; 
}

}


int contador = 0; //ajustamos el contador a 0
void loop() {

  int sensorValue = analogRead(A0);//realiza la lectura en el pin analogico A0
  float volts = sensorValue * 5; //Multipli la lectura por el voltaje de alimentación del sensor
  volts = volts / 1023;//convierte la lectura escalonada (10 bits) a voltaje

  RS = (((5*R2)/volts) - R2);//Calcula Rs en presencia del nuevo gas
  razon = (RS/Ro);//Calcula la razón entre RS y Ro
  
  base = ((RS/Ro)/5.154);//Calcula la base de la ecuación potencial donde 5.00 es la base
  ppm_gas = pow(base, (1/-0.34));//Determina la concentración del gas a partir de la ecuación potencial
  //Serial.print("[CO2]= ");//imprime lo indicado entre comillas
  //Serial.print(PPM_gas);//imprime la concentración del gas
  //Serial.println(" ppm");//imprime las unidades indicadas entre comilla
  //THERMISTOR
  float raw = analogRead(SensorPIN);
  float V =  raw / 1024 * Vcc;
  float R = (Rc * V ) / (Vcc - V);
  float logR  = log(R);
  float R_th = 1.0 / (A + B * logR + C * logR * logR * logR );
  float kelvin = R_th - V*V/(K * R)*1000;
  float celsius = kelvin - 273.15;
  //THERMISTOR
  Serial.print("DATA,TIME,");
  Serial.print(contador);
  Serial.print(" , ");
  Serial.print(sensorValue);
  Serial.print(" , ");
  Serial.print(volts);
  Serial.print(" , ");
  Serial.print(ppm_gas);
  Serial.print(" , ");
  Serial.println(celsius);
  
  

Serial.print("Initializing SD card...");//mensaje de inicialización de la tarjeta sd en el pin 10
if (!SD.begin(10)) {
Serial.println("initialization failed!");//mensaje de error
while (1);
}
Serial.println("initialization done.");//mensaje de inicialización exitosa
myFile = SD.open("test.txt", FILE_WRITE);//abrimos la tarjeta sd y escribimos el archivo test.txt
if (myFile) {
Serial.print("Writing to test.txt...");//mensaje "escribiendo en el archivo"
myFile.print(contador);//se escribe el valor del contador en el archivo.
myFile.print(" , ");//se escribe una coma espaciada entre datos.
myFile.print(sensorValue);
myFile.print(" , ");
myFile.print(volts);
myFile.print(" , ");
myFile.print(ppm_gas);
myFile.print(" , ");
myFile.print(RS);
myFile.print(" , ");
myFile.println(celsius);

myFile.close();
Serial.println("done.");//escritura finalizada
} else {
Serial.println("error opening test.txt");// mensaje de error si no puede abrir el archivo
}
  
  contador++;// adiciona 1 al contador

 delay(1000);//espera mil milisegundos o 1 s antes de realizar otra medida. 
}
