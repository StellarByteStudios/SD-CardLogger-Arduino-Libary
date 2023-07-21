English below  

Libary um ein MikroSD-Karten für Arduino zu benutzen und zu verwalten  

Die Libary ist geschrieben für den AZ-Delivery SPI Reader Micro. Dieser Unterstützt SD-Karten formatiert mit FAT16/FAT32 bis 32 GB  

Die Libary soll mit c++ Objectorientiert arbeiten, sodass das ganze Handling von Abspeicherungen in ein entsprechendes Objekt abstrahiert wird  

Anschlüssen an den Arduino:  
  GRD  -> GRD  
  VCC  -> 5V  
  MOSI -> D11  
  MISO -> D12  
  SCK  -> D13  
  CS   -> Platformabhängig  
            -----> Arduino Uno:  D10  
            -----> Arduino Mega: D53  
<br>
<br>
<br>
<br>



Libary used to handle MicroSD-Cards with Arduino  

The libary is written for the AZ-Delivery SPI Reader Micro. It supports SD-Kards formated with FAT16/FAT32 up to 32 GB  

The libary works object-oriented with c++ so as to wrap the complete handling of saving Data into a simple, easy-use object.  

Conections to the Arduino:  
  GRD  -> GRD  
  VCC  -> 5V  
  MOSI -> D11  
  MISO -> D12  
  SCK  -> D13  
  CS   -> Chip-dependend  
            -----> Arduino Uno:  D10  
            -----> Arduino Mega: D53  
