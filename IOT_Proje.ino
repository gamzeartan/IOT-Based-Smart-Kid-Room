
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include <Servo.h>

// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).

BlynkTimer timer;

SimpleTimer timer1;

SimpleTimer timer2;


char auth[] = "132pBXxQTaoxQT-671X4S7m5RaGDCpsB"; //Auth code sent via Email
char ssid[] = "sila"; //Wifi name
char pass[] = "silasila";  //Wifi Password


Servo servo;
int mq135 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0;



// Your threshold value. You might need to change it.
int sensorThres = 600;



int flag=0;
void notifyOnFire()
{
  int isButtonPressed = digitalRead(D1);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Fire in the House");
    Blynk.notify(" ALARM:YANGIN VAR!");
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    flag=0;
  }
}



 
// sensors 
int vs = D0; 
int sdata = 0; 
 
String vdata = ""; 
 

void myTimerEvent()
{
 
  Blynk.virtualWrite(V1, millis() / 1000);
 
}

BLYNK_WRITE(V3) {

servo.write(param.asInt());

}
BLYNK_WRITE(V5) {

servo.write(0);

}
BLYNK_WRITE(V6) {

servo.write(90);

}

void setup() {

// Debug console Serial.begin(115200);

Blynk.begin(auth, ssid, pass);
Serial.begin(9600);
 Serial.begin(115200);
// You can also specify server:

//Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);

//Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

servo.attach(15); // 15 means D8 pin of ESP8266
pinMode(D1,INPUT_PULLUP);
timer.setInterval(1000L,notifyOnFire); 
 pinMode(vs ,INPUT); 
  
  timer.setInterval(10L,sensorvalue); // 1000L
  timer2.setInterval(1000L, getSendData);



}

void loop()

{

Blynk.run(); // You can inject your own code or combine it with other sketches.
 timer.run();
  timer1.run();
timer2.run();




   
}



void sensorvalue()
{
  long measurement =vibration();
 //delay(50);
  Serial.println(measurement);
  Blynk.virtualWrite(V4, measurement);
  if( measurement > 1000 )
  {
    Blynk.notify(" ÇOCUK UYANDI! ");
  }
vdata = vdata + "Vibration: " + measurement;  
  
  Blynk.virtualWrite(V2, vdata);
vdata = ""; 
}
long vibration(){
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}






void getSendData()
{
data = analogRead(mq135); 
  Blynk.virtualWrite(V2, data); //virtual pin V3
 
  if (data > 150 )
  {
    Blynk.notify("HAVA KALİTESİ DÜŞTÜ!"); 
  }
 
}
