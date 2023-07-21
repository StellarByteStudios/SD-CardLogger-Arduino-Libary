/*
*   English below
*
*   Libary um ein MikroSD-Karten für Arduino zu
*   benutzen und zu verwalten
*   
*   Die Libary ist geschrieben für den 
*   AZ-Delivery SPI Reader Micro
*   Dieser Unterstützt SD-Karten formatiert mit
*   FAT16/FAT32 bis 32 GB
*   
*   Die Libary soll mit c++ Objectorientiert arbeiten,
*   sodass das ganze Handling von Abspeicherungen in
*   ein entsprechendes Objekt abstrahiert wird
*   
*   Anschlüssen an den Arduino:
*   GRD  -> GRD
*   VCC  -> 5V
*   MOSI -> D11
*   MISO -> D12
*   SCK  -> D13
*   CS   -> Platformabhängig
*           -> Arduino Uno:  D10
*           -> Arduino Mega: D53
*
*
*
*   Libary used to handle MicroSD-Cards with Arduino
*   
*   The libary is written for the AZ-Delivery SPI Reader Micro
*   It supports SD-Kards formated with FAT16/FAT32 up to 32 GB
*   
*   The libary works object-oriented with c++ 
*   so as to wrap the complete handling of saving Data
*   into a simple, easy-use object.
*   
*   Conections to the Arduino:
*   GRD  -> GRD
*   VCC  -> 5V
*   MOSI -> D11
*   MISO -> D12
*   SCK  -> D13
*   CS   -> Chip-dependend
*           -> Arduino Uno:  D10
*           -> Arduino Mega: D53
*   
*     
*/

#ifndef SD_HANDLING_LIB_H
#define SD_HANDLING_LIB_H

// Imports von Arduino-Libaries
#include <SPI.h>
#include <SD.h>


class SdHandler{

    private:
        // * * objectvariables * * //

        // DataPort depending on the Microcontroller
        // Arduio standard CS = 10
        int dataPortCS;
        // serial port of the Console
        int serialPort;
        // name of file in which data is saved
        String filePath;

        // * * private helping-methods * * //

        // helping-method, which saves String on Card
        // returns true if error occurs
        // ! buggy: but i dont know the cause. Doesn´t return true
        // if Card is removed! 
        bool printToCard(String);

        // initialize of SD-Card while set-up
        // called in constructor
        // returns true if error occurs
        bool initialize();


    public:
        // * * Construktor und Destructor * * //

        // construktor (CS-port, serial port, file name)
        SdHandler(int, int, String);

        // destructor
        ~SdHandler();

        // * * instance-methods * * //

        // writes string to SD-Card and tells
        // success via serial-monitor 
        // returns true if error occurs
        bool println(String);



        // * * Debugging * * //
        
        // writes all instanz-variables to console
        void dumpObjectDataToSerial();

        // prints data of SD-Card to Console
        // returns true if error occurs
        // ! buggy: sometimes just breaks the programm
        // mostly runs one time, but than program behaviour is not defined
        bool dumpCardDataToSerial();

};

#endif