//prueba final configuraciones arduino Leonardo
#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial XBee(10,11); 
Servo myservo;
int pos = 0; 
int servoActivator=7;
String readString; //main captured String 
String idlocal="1";
String id; //data String
String action;

volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor = 2;    //Sensor conectado en el pin 2
float factor_conversion=7.11; //para convertir de frecuencia a caudal
float volumen=0;
long dt=0; //variación de tiempo por cada bucle
long t0=0; //millis() del bucle anterior

int ind1; // , locations
int ind2;
void ContarPulsos ()  
{ 
  NumPulsos++;  //incrementamos la variable de pulsos
}
int ObtenerFrecuecia() 
{
  int frecuencia;
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Deshabilitamos  las interrupciones
  frecuencia=NumPulsos; //Hz(pulsos por segundo)
  return frecuencia;
}
 
void setup() {
  Serial.begin(9600);
  XBee.begin(9600);
  myservo.attach(6); //senal servo pin 6
  pinMode(PinSensor, INPUT);
  pinMode(servoActivator, OUTPUT);//Activador servo
  attachInterrupt(1,ContarPulsos,RISING);///depende del arduino
  t0=millis();
}

void loop() {
  //expect a string like 1,2*
  float frecuencia=ObtenerFrecuecia(); //obtenemos la frecuencia de los pulsos en Hz
  float caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m
  dt=millis()-t0; //calculamos la variación de tiempo
  t0=millis();
  volumen=volumen+(caudal_L_m/60)*(dt/1000);
  
  if (XBee.available())  {
    char c = XBee.read();  //gets one byte from serial buffer
    if (c == '*') {
      //do stuff
      
      Serial.println();
      Serial.print("captured String is : "); 
      Serial.println(readString); //prints string to serial port out
      
      ind1 = readString.indexOf(',');  //finds location of first ,
      id = readString.substring(0, ind1);   //captures first data String
      //ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
      //action = readString.substring(ind1+1, ind2);   //captures second data String
      action = readString.substring(ind1+1);
      Serial.print("id = ");
      Serial.println(id); 
      Serial.print("action = ");
      Serial.println(action);
      Serial.println();
      accion();
      clearValues();
    }  
    else {     
      readString += c; //makes the string readString
    }
  }


}

void accion(){
  
if(id==idlocal && action=="0")
{openWater();
}


if(id==idlocal && action=="1")
{closeWater();
}

if(id==idlocal && action=="2")
{sensorWater();
}
  
  }

void openWater(){
  
  digitalWrite(servoActivator, HIGH);
  delay(50);
   for (pos = 0; pos <= 90; pos += 1) { 
    // in steps of 1 degree
    myservo.write(pos);              
    delay(10);                       
  }
  delay(50);
  digitalWrite(servoActivator, LOW);
  
  }


void closeWater(){
  
   digitalWrite(servoActivator, HIGH);
  delay(50);
   for (pos = 90; pos >= 0; pos -= 1) { 
    // in steps of 1 degree
    myservo.write(pos);              
    delay(10);                       
  }
  delay(50);
  digitalWrite(servoActivator, LOW);

  }

void sensorWater(){
  XBee.println(volumen);
  //XBee.println (" L");
  volumen=0;
  ;}

void clearValues(){
  readString=""; //clears variable for new input
      id="";
      action="";
  }
