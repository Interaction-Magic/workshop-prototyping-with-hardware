/*
 * BluetoothUART.h
 * A class to handle Bluetooth Low Energy functionality for Arduino
 * Requires Adafruit Bluefruit library
 */

#ifndef BLUETOOTH_UART_H
#define BLUETOOTH_UART_H

#include <bluefruit.h>

class BluetoothUART {
private:
    BLEUart bleuart;
    bool isConnected;
    
public:
    // Constructor
    BluetoothUART();
    
    // Initialize and connect with device name
    bool connect(const char* deviceName);
    
    // Send a message via Bluetooth
    bool send(const char* message);
    bool send(const uint8_t* data, uint16_t length);
    
    // Receive data (returns number of bytes available)
    int available();
    
    // Read a single byte
    uint8_t read();
    
    // Read multiple bytes into buffer
    int read(uint8_t* buffer, int maxLength);
    
    // Check connection status
    bool connected();
    
    // Get the BLEUart reference for advanced usage
    BLEUart& getUart();
};

// Implementation
BluetoothUART::BluetoothUART() {
    isConnected = false;
}

bool BluetoothUART::connect(const char* deviceName) {
    // Enable connection LED
    Bluefruit.autoConnLed(true);
    
    // Configure peripheral connection with max bandwidth
    Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
    
    // Initialize Bluefruit
    Bluefruit.begin();
    
    // Set transmission power (check bluefruit.h for supported values)
    Bluefruit.setTxPower(4);
    
    // Set the device name
    Bluefruit.setName(deviceName);
    
    // Force name to be set by calling getName
    char fetchedName[64];
    Bluefruit.getName(fetchedName, 64);
    
    // Configure and start BLE UART service
    bleuart.begin();
    
    // Set up advertising
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    
    // Include bleuart 128-bit UUID
    Bluefruit.Advertising.addService(bleuart);
    
    // Add device name to scan response
    Bluefruit.ScanResponse.addName();
    
    // Configure advertising intervals (Apple recommended)
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);    // in units of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // seconds in fast mode
    
    // Start advertising (0 = don't stop after n seconds)
    Bluefruit.Advertising.start(0);
    
    isConnected = true;
    return true;
}

bool BluetoothUART::send(const char* message) {
    if (!isConnected) return false;
    
    size_t length = strlen(message);
    return bleuart.write(message, length) == length;
}

bool BluetoothUART::send(const uint8_t* data, uint16_t length) {
    if (!isConnected) return false;
    
    return bleuart.write(data, length) == length;
}

int BluetoothUART::available() {
    if (!isConnected) return 0;
    return bleuart.available();
}

uint8_t BluetoothUART::read() {
    if (!isConnected) return 0;
    return (uint8_t)bleuart.read();
}

int BluetoothUART::read(uint8_t* buffer, int maxLength) {
    if (!isConnected) return 0;
    
    int bytesRead = 0;
    while (bleuart.available() && bytesRead < maxLength) {
        buffer[bytesRead] = (uint8_t)bleuart.read();
        bytesRead++;
    }
    return bytesRead;
}

bool BluetoothUART::connected() {
    return isConnected && Bluefruit.connected();
}

BLEUart& BluetoothUART::getUart() {
    return bleuart;
}

#endif // BLUETOOTH_UART_H