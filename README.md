# Drone_3_ESP32
 Custom Drone 

PPM_recive.ino == Nano Upload
Drone_3_ESP32.ino  == ESP32

 Esp32 

 Saftey Options
 
 1. LM355Z Temp sensor directly mounted next to LM7805 Voltage Reg constant readings of internal temps
 2. Diode on VIN Line For short circut protection
 3.10a Fuse on 5v Line 


 VIN= upto 36V
 2200uf capacitor to help with load spikes to ensure ESP32 has a constant 5v supply
 10a fuse for board protection on 5v line


