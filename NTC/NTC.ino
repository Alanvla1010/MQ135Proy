#include <Wire.h>
#include "RTClib.h"
#include <SD.h>
#include <string.h>
#include <TimeLib.h>

const int pin=A0;
const int pin2=A1;
const int led=8;
int horas=0;
int minutos=30;
bool overF=0;
int objh=0;
int objm=0;

RTC_DS1307 rtc;
/*
RTC -> Arduino
SDA=A4
SCL=A5
*/
String date="";
DateTime inicio;

String monthsNames[12] = { "01", "02", "03", "04", "05",  "06", "07","08","09","10","11","12" };
void printDate(DateTime date)
{
	Serial.print(date.year(), DEC);
	Serial.print('/');
	Serial.print(date.month(), DEC);
	Serial.print('/');
	Serial.print(date.day(), DEC);
	Serial.print(" ");
   	Serial.print(date.hour(), DEC);
   	Serial.print(':');
   	Serial.print(date.minute(), DEC);
   	Serial.print(':');
   	Serial.print(date.second(), DEC);
   	Serial.println();
}

char filename[24]={0};

void min_timer(int cant){
  int temp=inicio.minute()+cant;
  if(temp>=60){
    overF=1;
    objm=temp-60;
  }
  else{overF=0;
    objm=temp;}
}

void hor_timer(int cant){
int temp=inicio.hour()+cant;
if(temp>=24){
  overF=1;
  objh=temp-24;
}
else{overF=0;
objh=temp;}
}

File data;
 tmElements_t tm;
void setup() {
   Serial.begin(9600);
   //delay(1000); 
   pinMode(led, OUTPUT);


//RTC
   if (!rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      while (1);
   }
//SD
  Serial.print("Initializing SD card...");
//Inicializando SD
//delay(100);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
inicio=rtc.now();
Serial.println("imprimiendo");
Serial.println(inicio.year());
 date =// String(inicio.year()) + "-" + 
               String(inicio.month()) +// "-" +
               String(inicio.day()) +// " "+
               String(inicio.hour())+ //"_"+
               String(inicio.minute())+ //"_"+
              // String(inicio.second())+
               ".txt";

    date.toCharArray(filename, 24);
Serial.println("begin filename");
Serial.println(filename);
Serial.println("end filename");

  data = SD.open(String(filename), FILE_WRITE);
  //data.close();
   min_timer(minutos);
   hor_timer(horas);
}

void record(){
long medida = analogRead(pin);
long medida2 = analogRead(pin2);
long tiempo=millis()/10+100*inicio.second()+100*60*inicio.minute()+100*3600*inicio.hour();
data.println("");
data.print(tiempo);
data.print("  ");
data.print(medida);
data.print("  ");
data.print(medida2);
}


void loop() {
  DateTime actual = rtc.now();
  int n=10;
  printDate(actual);
  Serial.print(objh);
  Serial.print(".");
  Serial.print(objm);
  Serial.println("");
  while(n>0){
   n--;;
   
   if(actual.minute()==objm)// && actual.hour()==objh)
   {
   Serial.println("Hemos alcanzado la meta");
   data.close();
   digitalWrite(led, HIGH);
   delay(43200000);           //12 hour
   }
   
   record();
     delay(100);}
     
   }
 
