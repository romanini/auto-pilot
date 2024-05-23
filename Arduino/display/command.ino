#include <WiFiNINA.h>

#define REAL_SEND false
#define TIMEOUT_MS 1000 // Set your desired timeout value in milliseconds
#define COMMAND_PORT 8023

IPAddress processor_ip(10, 20, 1, 2);
WiFiClient client;

void setup_command() { 
  // Set the timeout for WiFiClient
  client.setTimeout(TIMEOUT_MS);
#ifndef MOCK_SEND 
  connect();
#endif  
}

void adjustHeading(float change) {
#ifndef MOCK_SEND 
    if (connect()) { 
      client.print("a");
      client.println(change);
      client.flush();
      DEBUG_PRINT("adjusting heading ");
      DEBUG_PRINTLN(change);
    } else {
      DEBUG_PRINTLN("Could not adjust heading.");
    }
#endif
}

void setMode(int mode) {
#ifndef MOCK_SEND 
    if (connect()) { 
      client.print("m");
      client.println(mode);
      client.flush();
      DEBUG_PRINT("set mode ");
      DEBUG_PRINTLN(mode);
    } else {
      DEBUG_PRINTLN("Could not set mode.");      
    }
#endif  
}

boolean connect() {
  if (!client.connected()) {
    if (!client.connect(processor_ip, COMMAND_PORT)) { 
      DEBUG_PRINTLN("Could not connect to processor.");    
      return false;
    }
  }  
  return true;
}