#include <Wire.h>
#include "RTClib.h"
#include <SD.h>
#include <string.h>
#include <TimeLib.h>
#include "MQ135.h"

const int pin=A0;
const int pin2=A1;
const int led=8;
int horas=0;
int minutos=30;
bool overF=0;
int objh=0;
int objm=0;

MQ135 gasSensor = MQ135(pin);


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
//String name=printDate(DateTime rtc.now());

/*void getFileName() {

  // store the date in this empty string
  String date = "";

  // check the day each loop
  tmElements_t tm;

 
  if (rtc.read(tm)) {

    date = String(tmYearToCalendar(tm.Year)) + "-" + 
               String(tm.Month) + "-" +
               String(tm.Day) + ".txt";

    date.toCharArray(filename, 16);

    Serial.println("filename: " + String(filename));

    //dataFile = SD.open(str, FILE_WRITE);
    }
}*/

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
  //Serial.print("Initializing SD card...");
//Inicializando SD
//delay(100);
  if (!SD.begin(4)) {
    //Serial.println("initialization failed!");
    //while (1);
  }
  //Serial.println("initialization done.");
//delay(100);
  
/* Prueba de SD
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

*/
//filename = (char*)malloc(13*sizeof(char)); // allocate memory to store 10 characters

inicio=rtc.now();
//Serial.println("imprimiendo");
//Serial.println(inicio.year());
/*memcpy(filename,inicio.year(),4);
memcpy(filename+4,inicio.month(),2);
memcpy(filename+6,inicio.day(),2);
memcpy(filename+8,inicio.hour(),2);
memcpy(filename+10,inicio.minute(),2);
memcpy(filename+12,inicio.second(),2);
filename[14]='\0';*/
//char*filename2=AppendStrings(inicio.year(),inicio.month());
//strcpy(filename2,inicio.year());
   date =// String(inicio.year()) + "-" + 
               String(inicio.month()) +// "-" +
               String(inicio.day()) +// " "+
               String(inicio.hour())+ //"_"+
               String(inicio.minute())+ //"_"+
              // String(inicio.second())+
               ".txt";

    date.toCharArray(filename, 24);
/*filename2=(int*)inicio.year();
filename2[1]=(int*)(inicio.year() +1);
filename2[2]=(int*)inicio.year()+2;
filename2[3]=(int*)inicio.year()+3;*/
//filename=inicio.year(); //+inicio.month();
//strcat(filename,inicio.month()); strcat(filename,inicio.day()); strcat(filename," "); strcat(filename,inicio.hour());
//strcat(filename,inicio.minute()); strcat(filename,inicio.second());
/*char an[4]=(char*)inicio.year());
char mes[2]=(char*)inicio.month());
char dia[2]=(char*)inicio.day());
char hora[4]=(char*)inicio.hour());
char minuto[2]=(char*)inicio.minute());
char segundo[2]=(char*)inicio.second());*/
//char*filename2=&año;
/*
Serial.println("begin filename");
Serial.println(filename);
Serial.println("end filename");
*/
  data = SD.open(String(filename), FILE_WRITE);
  //data.close();
   min_timer(minutos);
   hor_timer(horas);
}
void record(){
float medida = gasSensor.getPPM();
float medida2 = pow(analogRead(pin2),2.888)*4.47E-7;
long tiempo=millis()/10+100*inicio.second()+100*60*inicio.minute()+100*3600*inicio.hour();
//Serial.print("\r\n");
//Serial.print(tiempo);
Serial.print("\r\n");
Serial.print(medida);
Serial.print("\r\n");
Serial.print(medida2);
//Serial.print("\x03");
//Serial.print(",");
}


void loop() {
  DateTime actual = rtc.now();
  int n=10;
  //printDate(actual);
  //Serial.print(objh);
  //Serial.print(".");
  //Serial.print(objm);
  //Serial.println("");
  while(n>0){
   n--;;
   
   if(actual.minute()==objm)// && actual.hour()==objh)
   {
   //Serial.println("Hemos alcanzado la meta");
   data.close();
   digitalWrite(led, HIGH);
   delay(43200000);           //12 hour
   }
   
   record();
     delay(100);}
     
   }
 
