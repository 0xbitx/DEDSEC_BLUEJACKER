
<p align="center">
<img src="https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExZWJ2MGZobjl3YW00cmRrNHY5ZnE1NnJrczdld3gwbzNweDN2eW5mdiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/lcEKnwUvk2d7isZ09s/giphy.webp" width="60%" height="60%">
</p>

<h1 align="center"> DEDSEC_BLUEJACKER </h1>

## DESCRIPTION
DEDSEC_BLUEJACKER is a sophisticated Bluetooth jamming device/tool that uses an ESP32 NodeMCU and an nRF module. This tool can effectively disrupt Bluetooth communication, causing a Denial of Service (DoS) attack on various Bluetooth devices such as Bluetooth speakers, smartphones, IoT devices, and more. By jamming Bluetooth frequencies, DEDSEC_BLUEJACKER renders targeted devices non-functional. It can stop Bluetooth speakers from playing audio, prevent Bluetooth communication on smartphones, affect IoT devices that rely on Bluetooth for communication, and disrupt Bluetooth-dependent industrial equipment.

## requirements:
	
    ESP32-devkit v1 nodeMCU                     
    2x nRF24L01   
    2x 10UF 16v Capacitor
    Data usb cable 


## installation: 

    1. git clone https://github.com/0xbitx/DEDSEC_BLUEJACKER.git
    2. cd DEDSEC_BLUEJACKER
    3. pip install esptool
    4. ./esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 115200 write_flash 0x1000 dedsec_bluejacker.bin

## WIRING DIAGRAM

<p align="center">
<img src="https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExZWJ2MGZobjl3YW00cmRrNHY5ZnE1NnJrczdld3gwbzNweDN2eW5mdiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/lcEKnwUvk2d7isZ09s/giphy.webp" width" width="50%" height="50%">
</p>


## Pinout Configuration

Below are the pinout mappings from the ESP32 to the nRF24L01+ modules for both HSPI and VSPI configurations.

### HSPI Configuration

| nRF24L01+ Pin | HSPI Pin (ESP32) |
|---------------|------------------|
| VCC           | 3.3V             |
| GND           | GND              |
| CE            | GPIO 16          |
| CSN           | GPIO 15          |
| SCK           | GPIO 14          |
| MOSI          | GPIO 13          |
| MISO          | GPIO 12          |
| IRQ           | Not Connected    |

### VSPI Configuration

| nRF24L01+ Pin | VSPI Pin (ESP32) |
|---------------|------------------|
| VCC           | 3.3V             |
| GND           | GND              |
| CE            | GPIO 22          |
| CSN           | GPIO 21          |
| SCK           | GPIO 18          |
| MOSI          | GPIO 23          |
| MISO          | GPIO 19          |
| IRQ           | Not Connected    |


<h1 align="center"> DISCLAIMER </h1>

<h4 align="center">I'm not responsible for anything you do with this program, so please only use it for good and educational purposes. </h4>

