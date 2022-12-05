
int Ro = 7400;//Ro calculado con el programa anterior
int R2 = 2000;//Valor de R entre los pines A0 y GND del sensor 

float razon;//establece "razon" como variable de tipo flotante
float RS;//establece "RS" como variable de tipo flotante
//float ppm_gas;//establece "PPM_gas" o concentración como variable de tipo flotante

void setup() {
  Serial.begin(9600);//inicializa la comunicación serial a 9600 bps.
Serial.println("El sensor debe estar expuesto al gas de interes");//imprime el aviso entre comillas
}

void loop() {
  int sensorValue = analogRead(A0);//realiza la lectura en el pin analogico A0
  float volts = sensorValue * 5; //Multipli la lectura por el voltaje de alimentación del sensor
  volts = volts / 1023;//convierte la lectura escalonada (10 bits) a voltaje

  RS = (((5*R2)/volts) - R2);//Calcula Rs en presencia del nuevo gas
  razon = (RS/Ro);//Calcula la razón entre RS y Ro
  Serial.print("sensor = ");//imprime lo indicado entre comillas
  Serial.print(sensorValue);//imprime la lectura analoga
  Serial.print(", A0 = ");//imprime lo indicado entre comillas
  Serial.print(volts);//imprime el voltaje correspondiente a la lectura
  Serial.print(", Ro = ");//imprime lo indicado entre comillas
  Serial.print(Ro);//imprime la resistencia del sensor expuesto al aire sin contaminantes
  Serial.print(", RS = ");//imprime lo indicado entre comillas
  Serial.print(RS);//imprime el valor de la resistencia en presencia del gas de interés
  Serial.print(", RS/Ro = ");//imprime lo indicado entre comillas
  Serial.println(razon);//imprime la razón entre RS y Ro.
  delay(1000);//espera mil milisegundos o 1 s antes de realizar otra medida.
}
