#ifndef WatchDetector_h
#define WatchDetector_h

#include "Arduino.h"
#include <NimBLEDevice.h>

class WatchDetector {
  public:
    void main();             // The loop that runs the scan
    void start();            // Start tracking
    void stop();             // Stop tracking
    bool scanning = false;   // State check
  
  private:
    int last_rssi = -100;    // Store signal strength
};

extern WatchDetector watchDetector;

#endif
