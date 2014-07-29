#include <NewPing.h>
#define TRIGGER_PIN  12
#define ECHO_PIN     13
#define MAX_DISTANCE 200
#define DISTANCIA_MAX 70
#define POTENCIA 42
#define controlPin1  2
#define controlPin2  3
#define controlPin3  4
#define controlPin4  5
#define enablePin2  10
#define enablePin  9
int cont = 0 ;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(controlPin3, OUTPUT);
  pinMode(controlPin4, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  digitalWrite(enablePin, LOW);
  digitalWrite(enablePin2, LOW);
  Serial.begin(9600);

}

void loop() {
  int distancia= promedioDistancia();
  if(distancia <= DISTANCIA_MAX){
    direccion("atras");
    traccion("izquierda");
    delay(500);
  }
  else if(distancia <= (DISTANCIA_MAX+50) && distancia > DISTANCIA_MAX ){
    traccion("derecha");
    direccion("adelante"); 
  }
  else if(distancia > DISTANCIA_MAX){
    direccion("adelante");
    traccion("stop");
  }
}

void direccion(String direccion){
  if(direccion == "adelante"){
    analogWrite(enablePin,POTENCIA);
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }
  else if(direccion == "atras"){
    analogWrite(enablePin,POTENCIA);
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }
  else if(direccion == "stop"){
    analogWrite(enablePin,0);
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
  }
}

void traccion(String direccion){
  if(direccion == "izquierda"){
    analogWrite(enablePin2,POTENCIA);
    digitalWrite(controlPin3, HIGH);
    digitalWrite(controlPin4, LOW);
  }
  else if(direccion == "derecha"){
    analogWrite(enablePin2,POTENCIA);
    digitalWrite(controlPin3, LOW);
    digitalWrite(controlPin4, HIGH);
  }
  else if(direccion == "stop"){
    analogWrite(enablePin2,0);
    digitalWrite(controlPin3, LOW);
    digitalWrite(controlPin4, LOW);
  }
}

int distancia(){
  delay(25);
  int uS = sonar.ping_median();
  Serial.print("Distancia: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm"); 
  return (uS/US_ROUNDTRIP_CM);
}

int promedioDistancia(){
  int acumulador = 0;
  int dist;
  for(int i=0;i<5;i++){
    dist = distancia();
    acumulador = acumulador + (dist == 0? 90 : dist);
  }
  return (acumulador/5);
}







