/* Anmerkung:
  Ich habe keinen Zugang zu eurer Gruppendiskussion. Daher konnte ich keine Fragen zur Hausarbeit stellen.
  Den Aufgabenstellungen nach, gehe ich davon aus, dass in allen Teilprüfungsleistungen nur der Quellcode
  hochgeladen werden soll. 

  Bei der Teilprüfungsleistung 3 sind 5 LEDs zur Simulation eines Würfels gefordert. Damit kann man allerdings
  nicht die Würfelzahl 6 demonstrieren.  Das geht nur mit 6 bzw. 7 LEDs. Habt ihr euch da vertan?
  Ich hatte mich für 6 LEDs entschieden, um die Würfelsimulation zu vollenden. Solltet ihr 7 gemeint haben,
  kann ich die Aufgabe gerne nachbearbeiten.
*/

#include "DHT.h"
#include "DHT118266.h"
#define DHTPIN A0 // Festlegung der Pin
#define DHTTYPE DHT11 // Festlegung der Sensorvariante


/* Temperatursensor DHT11 einrichten */
DHT dht(DHTPIN, DHTTYPE); // Deklaration des DHT11 Temperatursensors

/* Pinbelegung der RGB-LED */
const int blauerPin = 6;
const int gruenerPin = 5;
const int roterPin = 3;


void setup() {
  // Serielle Schnittstelle mit der Baudrate 9600
  Serial.begin(9600);

  // dht starten
  dht.begin();

  // RGB-LED Pins als Output festlegen
  pinMode(roterPin, OUTPUT);
  pinMode(gruenerPin, OUTPUT);
  pinMode(blauerPin, OUTPUT);

}

void loop() {
  // Verweilzeit zur Auslesung der Sensorwerte
  delay(2000); 

  // Liest die Analogwwerte des Sensors
  int analog = analogRead(DHTPIN);
  
  // Berechnet aus dem Analogwert die  Temperatur in Celsius
  float temperatur = temperatureInCelsius(analog);

  // Farbanzeige gemäß der Temperatur
  farbanzeige(temperatur);

  // Ausgabe über die serielle Schnittstelle
  Serial.println("Temperatur: " + String(temperatur) + " °C");
}

/* Funktion zur Berechnung der Temperatur in °C */
float temperatureInCelsius(int a) {
  float celsius = 0; 
  // Formel zur Umrechnung in °C 
  celsius =  (a / 1024.0) * 500;;

  return celsius;
}

/*Funktion, zur Farbanzeige der entsprechenden Temperatur*/
void farbanzeige(float t) {
  // Falls die Temperatur unter 20 °C liegt
  if(t < 20 ) {
    // ...leuchtet die LED grün
    analogWrite(roterPin, 0);
    analogWrite(gruenerPin, 255);
    analogWrite(blauerPin, 0);
  }
  // Falls die Temperatur zwischen 20 °C und 30 °C ist 
  if(t >= 20 || t <= 30) {
    // ...leuchtet die LED gelb
    analogWrite(roterPin, 255);
    analogWrite(gruenerPin, 255);
    analogWrite(blauerPin, 0);
  }

  // Falls die Temperatur über 30 °C liegt
  if(t > 30) {
    // ...leuchtet die LED rot
    analogWrite(roterPin, 255);
    analogWrite(gruenerPin, 0);
    analogWrite(blauerPin, 0);
  }
}

