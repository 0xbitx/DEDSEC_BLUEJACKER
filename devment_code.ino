 
#include "RF24.h"
#include <SPI.h>
#include "esp_bt.h"
#include "esp_wifi.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"

SPIClass *hspi = nullptr;
RF24 hspiRadio(16, 15, 16000000);
int hspiChannel = 45;
bool wifiJammingActive = false;
bool bluetoothJammingActive = false;
bool droneControllerJammingActive = false;

void setRandomChannel() {
    int newChannel = random(80);
    hspiRadio.setChannel(newChannel);
    Serial.print("RF24: Set to random channel: ");
    Serial.println(newChannel);
    delayMicroseconds(random(60));
}

void initializeHSPI() {
    hspi = new SPIClass(HSPI);
    hspi->begin(14, 12, 13, 15);
    Serial.println("HSPI: SPI initialized with SCK=14, MISO=12, MOSI=13, SS=15");

    if (hspiRadio.begin(hspi)) {
        hspiRadio.setAutoAck(false);
        hspiRadio.stopListening();
        hspiRadio.setRetries(0, 0);
        hspiRadio.setPALevel(RF24_PA_MAX, true);
        hspiRadio.setDataRate(RF24_2MBPS);
        hspiRadio.setCRCLength(RF24_CRC_DISABLED);
        hspiRadio.startConstCarrier(RF24_PA_MAX, hspiChannel);
        Serial.println("RF24: NRF24L01+ module initialized on HSPI");
        Serial.print("RF24: Initial channel set to: ");
        Serial.println(hspiChannel);
    } else {
        Serial.println("RF24: Failed to initialize NRF24L01+ module");
    }
}


void jamWiFi() {
    Serial.println("WiFi jamming: Starting channel hopping...");
    for (int channel = 1; channel <= 13; ++channel) {
        esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
        Serial.print("WiFi jamming: Switched to channel ");
        Serial.println(channel);
        delay(random(5, 50));
    }
    Serial.println("WiFi jamming: Completed one round of channel hopping.");
}

void jamBluetooth() {
    Serial.println("Bluetooth jamming: Starting frequency hopping...");
    for (int i = 0; i < 79; ++i) {
        esp_bt_gap_set_scan_mode(ESP_BT_NON_CONNECTABLE, ESP_BT_NON_DISCOVERABLE);
        Serial.print("Bluetooth jamming: Switched to channel ");
        Serial.println(i);
        delay(random(5, 50));
    }
    Serial.println("Bluetooth jamming: Completed one round of frequency hopping.");
}

void jamDroneController() {
    Serial.println("Drone controller jamming: Starting channel hopping...");

    for (int channel = 1; channel <= 13; ++channel) {
        esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
        Serial.print("Drone controller jamming (2.4 GHz): Switched to channel ");
        Serial.println(channel);
        delay(random(5, 50));
    }

    for (int channel = 149; channel <= 165; ++channel) {
        esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
        Serial.print("Drone controller jamming (5.8 GHz): Switched to channel ");
        Serial.println(channel);
        delay(random(5, 50));
    }

    Serial.println("Drone controller jamming: Completed one round of channel hopping.");
}

void toggleWiFiJamming(bool activate) {
    if (activate) {
        wifiJammingActive = true;
        Serial.println("WiFi jamming: Activated.");
    } else {
        wifiJammingActive = false;
        Serial.println("WiFi jamming: Deactivated.");
    }
}

void toggleBluetoothJamming(bool activate) {
    if (activate) {
        bluetoothJammingActive = true;
        esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
        Serial.println("Bluetooth jamming: Activated.");
    } else {
        bluetoothJammingActive = false;
        esp_bt_controller_disable();
        Serial.println("Bluetooth jamming: Deactivated.");
    }
}

void toggleDroneControllerJamming(bool activate) {
    if (activate) {
        droneControllerJammingActive = true;
        Serial.println("Drone controller jamming: Activated.");
    } else {
        droneControllerJammingActive = false;
        Serial.println("Drone controller jamming: Deactivated.");
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("System: Starting...");
    esp_bt_controller_deinit();
    esp_wifi_stop();
    esp_wifi_deinit();
    esp_wifi_disconnect();
    Serial.println("System: WiFi and Bluetooth deinitialized.");

    initializeHSPI();
}

void loop() {
    setRandomChannel();

    if (wifiJammingActive) {
        jamWiFi();
    }

    if (bluetoothJammingActive) {
        jamBluetooth();
    }

    if (droneControllerJammingActive) {
        jamDroneController();
    }

    delay(100);
}

void activateJamming() {
    toggleBluetoothJamming(true);
}

// void deactivateJamming() {
//     toggleWiFiJamming(false);      // Deactivate WiFi jamming
//     toggleBluetoothJamming(false); // Deactivate Bluetooth jamming
//     toggleDroneControllerJamming(false); // Deactivate drone controller jamming
// }
