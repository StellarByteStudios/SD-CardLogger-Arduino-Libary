#ifndef SD_HANDLING_LIB_CPP
#define SD_HANDLING_LIB_CPP

#include "sdHandlingLib.h";


// * * * Konstruktor und Destruktor * * * // 
SdHandler::SdHandler(int dataPortCS0, int serialPort0, String filePath0){
    dataPortCS = dataPortCS0;
    serialPort = serialPort0;
    filePath = "";
    filePath += filePath0;

    // Serieller Port initialisieren
    Serial.begin(serialPort);

    // SD-Karte initialisieren
    bool error = this->initialize();

    // Bei Fehler dauerLoop
    if (error){
      Serial.println(F("Error: sdHandler - initializing Card failed"));
        while(1);
    }
    
}

SdHandler::~SdHandler(){
    Serial.println(F("SD-Card-Handler was destroyed"));
}






// * * * öffentliche Methoden * * * // 
bool SdHandler::println(String printString){

    // Auf Konsole ausgeben
    Serial.println("Write to SD: " + printString);
    // Auf SD-Karte speichern
    bool error = this->printToCard(printString);

    // Fehlerbehandlung
    if (error){
        Serial.println(F("Error: sdHandler - writing to SD-Card failed"));
        return true;
    }
    

    return false;
}






// * * * private Hilfsmethoden * * * // 
bool SdHandler::printToCard(String printString){
    // File-Variable
    File file;

    // Datei Öffnen
    file = SD.open(filePath, FILE_WRITE);

    // String auf Datei speichern
    if (file) {    
        file.println(printString);
        file.close(); // close the file
        return false;
    }

    // Fehlerbehandlung
    //Serial.println("error opening file: " + fileName);
    return true;
}

bool SdHandler::initialize(){

    Serial.println(F("Initializing SD card..."));

    // see if the card is present and can be initialized:
    if (!SD.begin(dataPortCS)) {
        Serial.println(F("\tCard failed, or not present"));
        this->dumpObjectDataToSerial();
        return true;
    }
    Serial.println(F("\tcard initialized."));
    return false;
}











// * * * Debugging * * * //
void SdHandler::dumpObjectDataToSerial(){
    Serial.println(F("* * Dumping all Data from sd-Object: * *"));
    Serial.println("dataPortCS: " + String(dataPortCS));
    Serial.println("serialPort: " + String(serialPort));
    Serial.println("filePath: " + String(filePath));
}



// Basiert hauptsächlich auf der Methode aus dem Beispiel-Skript
// von der SPI Libary
bool SdHandler::dumpCardDataToSerial(){
    Serial.println(F("* * Data of the inserted SD-Card: * *"));

    
    // Größen der SD-Karte
    Sd2Card card;
    SdVolume volume;
    SdFile root;

    // Card Objekt initialisieren
    if (!card.init(SPI_HALF_SPEED, dataPortCS)) {
    Serial.println(F("initialization failed:"));
    Serial.println(F("* is a card inserted?"));
    Serial.println(F("* is your wiring correct?"));
    Serial.println(F("* did you change the chipSelect pin to match your shield or module?"));
    return true;
    } else {
      Serial.println(F("Wiring is correct and a card is present."));
    }

    // print the type of card
    Serial.println();
    Serial.print(F("Card type:         "));
    switch (card.type()) {
        case SD_CARD_TYPE_SD1:
        Serial.println(F("SD1"));
        break;
        case SD_CARD_TYPE_SD2:
        Serial.println(F("SD2"));
        break;
        case SD_CARD_TYPE_SDHC:
        Serial.println(F("SDHC"));
        break;
        default:
        Serial.println(F("Unknown"));
    }

    // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
    if (!volume.init(card)) {
        Serial.println(F("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card"));
        return true;
    }

    Serial.print(F("Clusters:          "));
    Serial.println(volume.clusterCount());
    Serial.print(F("Blocks x Cluster:  "));
    Serial.println(volume.blocksPerCluster());

    Serial.print(F("Total Blocks:      "));
    Serial.println(volume.blocksPerCluster() * volume.clusterCount());
    Serial.println();

    // print the type and size of the first FAT-type volume
    uint32_t volumesize;
    Serial.print(F("Volume type is:    FAT"));
    Serial.println(volume.fatType(), DEC);

    volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
    volumesize *= volume.clusterCount();       // we'll have a lot of clusters
    volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
    Serial.print(F("Volume size (Kb):  "));
    Serial.println(volumesize);
    Serial.print(F("Volume size (Mb):  "));
    volumesize /= 1024;
    Serial.println(volumesize);
    Serial.print(F("Volume size (Gb):  "));
    Serial.println((float)volumesize / 1024.0);

    Serial.println(F("\nFiles found on the card (name, date and size in bytes): "));
    root.openRoot(volume);

    // list all files in the card with date and size
    root.ls(LS_R | LS_DATE | LS_SIZE);

    root.close();
    volume.cacheClear();
    card.readEnd();
}


#endif