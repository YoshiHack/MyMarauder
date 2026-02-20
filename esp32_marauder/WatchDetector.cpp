#include <NimBLEDevice.h>
#include "WatchDetector.h"
#include "Display.h" // Crucial for CYD screen support

void scanForWatch() {
    NimBLEScan* pScan = NimBLEDevice::getScan();
    pScan->setActiveScan(true); // Active scan gets more data
    pScan->setInterval(100);
    pScan->setWindow(99);

    // Scan for 2 seconds
    NimBLEScanResults results = pScan->start(2, false);

    for (int i = 0; i < results.getCount(); i++) {
        NimBLEAdvertisedDevice device = results.getDevice(i);
        
        // Check if it's an Apple device (Manufacturer Data starts with 0x4C 0x00)
        if (device.haveManufacturerData()) {
            std::string data = device.getManufacturerData();
            // Inside your for loop
if (data.length() >= 2 && (uint8_t)data[0] == 0x4C && (uint8_t)data[1] == 0x00) {
    int rssi = device.getRSSI();
    
    // Clear a small strip of the screen for the update
    display_obj.tft.fillRect(0, 60, 240, 40, TFT_BLACK); 
    display_obj.tft.setCursor(10, 70);
    
    // Color coding based on distance
    if (rssi > -55) display_obj.tft.setTextColor(TFT_RED);
    else if (rssi > -75) display_obj.tft.setTextColor(TFT_YELLOW);
    else display_obj.tft.setTextColor(TFT_GREEN);

    display_obj.tft.print("RSSI: ");
    display_obj.tft.print(rssi);
    
    display_obj.tft.setCursor(10, 90);
    if (rssi > -55) display_obj.tft.println("IMMEDIATE");
    else if (rssi > -75) display_obj.tft.println("NEAR");
    else display_obj.tft.println("FAR");
}

        }
    }
    pScan->clearResults(); 
}
