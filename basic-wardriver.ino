#include <MKRGSM.h>

const char PINNUMBER[] = " ";
// APN data
const char GPRS_APN[]      = "hologram";
const char GPRS_LOGIN[]    = " ";
const char GPRS_PASSWORD[] = " ";

// initialize the library instances
GSMLocation location;
GPRS gprs;
GSM gsmAccess;
GSMScanner scannerNetworks;
GSMModem modemTest;

// Save data variables
String IMEI = "";

// serial monitor result messages
String errortext = "ERROR";

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

//  changeBand(GSM_MODE_GSM850_PCS); // if you want to change the band
  
  Serial.println("GSM networks scanner");
  scannerNetworks.begin();
  
  Serial.println("Starting GSM location.");
  // connection state
  bool connected = false;

  // After starting the modem with GSM.begin()
  // attach the shield to the GPRS network with the APN, login and password
   while (!connected) {
    if ((gsmAccess.begin(PINNUMBER) == GSM_READY) &&
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  // get modem parameters
  // IMEI, modem unique identifier
  Serial.print("Modem IMEI: ");
  IMEI = modemTest.getIMEI();
  IMEI.replace("\n", "");
  if (IMEI != NULL) {
    Serial.println(IMEI);
  }
  
  location.begin(); 
  
}

void loop() {
  
  if (location.available()) {
    Serial.println(scannerNetworks.readNetworks());
    Serial.print("Current carrier: ");
    Serial.println(scannerNetworks.getCurrentCarrier());

    Serial.print("Signal Strength: ");
    Serial.print(scannerNetworks.getSignalStrength());
    Serial.println(" [0-31]");
    
    Serial.print("Location: ");
    Serial.print(location.latitude(), 7);
    Serial.print(", ");
    Serial.println(location.longitude(), 7);

    Serial.print("Altitude: ");
    Serial.print(location.altitude());
    Serial.println("m");

    Serial.print("Accuracy: +/- ");
    Serial.print(location.accuracy());
    Serial.println("m");

    Serial.println();
  }
}
