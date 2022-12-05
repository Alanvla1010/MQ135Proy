float Ro;//define  Ro como variable de punto flotante.
void setup() {
   Serial.begin(9600);//inicia la comunicación serial a 9600 bps.
   Serial.println("El sensor debe estar precalentado 48 horas o más");
   Serial.println("El sensor debe encontrarse expuesto al aire, a temperatura y humedad relativa constante");
} 
void loop() {
   int sensorValue = analogRead(A0);//define la variable sensorValue como una variable tipo entero
   float volts = sensorValue * 5;//multiplica la lectura analoga por 5 voltios.
   volts = volts / 1023;//obtenemos el voltaje dividiendo por los niveles correspondientes a 10 bits.
   Ro = (((5*2000)/volts) - 2000);// el valor de 2000 ohmios debe verificarse entre A0 y GND
   Serial.print("A0 (voltios) = ");//imprime lo indicado entre comillas
   Serial.print(volts);//imprime el voltaje
   Serial.print(" , ");//imprime lo indicado entre comillas
   Serial.print("Ro (Ω) = ");//imprime lo indicado entre comillas
   Serial.println(Ro);//imprime la resistencia expuesta al aire sin contaminantes a T y P cosntantes
   delay(1000); //espera un segundo para volver a medir.
}
