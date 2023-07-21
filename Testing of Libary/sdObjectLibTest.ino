/*
*   Test Skript um die SD-Karten Libary zu testen
*   
*   Die Libary soll mit c++ Objectorientiert arbeiten,
*   sodass das ganze Handling von Abspeicherungen in
*   ein entsprechendes Objekt abstrahiert wird
*   
*   
*   
*   
*/

// Imports
#include "sdHandlingLib.h"

// Variablen
int serialPort = 9600;
int sdPortCS = 10;
String filePath = "data3.txt";
SdHandler* sdCard;


void setup() {

    Serial.begin(serialPort);
    Serial.println(F("\n\n ================= sdCard Handler =================\n"));
    Serial.println(F("Libary Testing of Object-Oriented SPI Reader Libary for SD Cards\n"));
    delay(500);

    

    sdCard = new SdHandler(sdPortCS, serialPort, filePath); 

    delay(2000);
    sdCard->dumpObjectDataToSerial();
    delay(2000);
    sdCard->dumpCardDataToSerial();


    delay(2000);
    Serial.println("Testdaten auf der SD-Karte speichern");
    sdCard->println("==== Krasser Headder der Datei 3 ====\n");
    sdCard->println("Daten 1;");
    sdCard->println("Daten 2;");


    delay(2000);
    sdCard->dumpCardDataToSerial();

    delay(2000);
    delete sdCard;

}

void loop() {
    // put your main code here, to run repeatedly:

}
