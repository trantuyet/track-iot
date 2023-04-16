#include <SoftwareSerial.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6AVlbVaNR"
#define BLYNK_TEMPLATE_NAME "MindS IoT System"
#define BLYNK_AUTH_TOKEN "mjT_rKxi2BZei360c7qBUxYalr8P-6uU"

#include <WiFi.h>
#include <WiFiClient.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Viettel Academy";
char pass[] = "";

#define RXPin D27
#define TXPin D26
SoftwareSerial sim7020eSerial(D27, D26); // Use hardware serial port 2
char auth[] = "mjT_rKxi2BZei360c7qBUxYalr8P-6uU";

void setup() {
  // ...
  Serial.begin(115200);
  delay(10);
  // Initialize SIM7020E module
  sim7020eSerial.begin(115200, SERIAL_8N1, 2, 4); // RX, TX
  

  sim7020eSerial.println("AT+CFUN=0"); // Set module to minimum functionality
  delay(1000);

  sim7020eSerial.println("AT+CPIN?"); // Check if SIM card is inserted
  delay(1000);

  sim7020eSerial.println("AT+CREG?"); // Check network registration status
  delay(1000);

  sim7020eSerial.println("AT+CGATT?"); // Check GPRS attach status
  delay(1000);

  sim7020eSerial.println("AT+CFUN=1"); // Set module to full functionality
  delay(1000);

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);

}


void loop() {


  // Monitor MMC, MNC, TAC, and cell band
  sim7020eSerial.println("AT+COPS=3,0");
  delay(1000);

  sim7020eSerial.println("AT+COPS?");
  delay(1000);

  while (sim7020eSerial.available()) {
    String response = sim7020eSerial.readStringUntil('\n');

    if (response.startsWith("+COPS:")) {
      int mmcIndex = response.indexOf(",")+2;
      int mmcEndIndex = response.indexOf(",", mmcIndex)-1;
      String mmc = response.substring(mmcIndex, mmcEndIndex);
      Serial.println("MMC: " + mmc);

      int mncIndex = response.indexOf(",", mmcEndIndex+2)+2;
      int mncEndIndex = response.indexOf(",", mncIndex)-1;
      String mnc = response.substring(mncIndex, mncEndIndex);
      Serial.println("MNC: " + mnc);

      int tacIndex = response.indexOf(",", mncEndIndex+2)+2;
      int tacEndIndex = response.indexOf(",", tacIndex)-1;
      String tac = response.substring(tacIndex, tacEndIndex);
      Serial.println("TAC: " + tac);

      int bandIndex = response.lastIndexOf(",")+1;
      String band = response.substring(bandIndex);
      Serial.println("Frequency Band: " + band);

      Blynk.virtualWrite(V2, mmc);
      Blynk.virtualWrite(V3, mnc);
      Blynk.virtualWrite(V4, tac);
      Blynk.virtualWrite(V5, band);
    }
  }

  // Monitor RSRP and RSRQ
  
  // Monitor PCI
  sim7020eSerial.println("AT+CENG=\"SERVINGCELL\"");
  delay(1000);

  while (sim7020eSerial.available()) {
    String response = sim7020eSerial.readStringUntil('\n');


    if (response.startsWith("+CENG:")) {
      int pciIndex = response.indexOf(",")+1;
      int pciEndIndex = response.indexOf(",", pciIndex);
      String pci = response.substring(pciIndex, pciEndIndex);
      Serial.println("PCI: " + pci);

      // Extract RSRP value
      int rsrpStartIndex = response.indexOf(",") + 1;
      int rsrpEndIndex = response.indexOf(",", rsrpStartIndex);
      String rsrpStr = response.substring(rsrpStartIndex, rsrpEndIndex);
      int rsrp = rsrpStr.toInt();

      // Extract RSRQ value
      int rsrqStartIndex = rsrpEndIndex + 1;
      int rsrqEndIndex = response.indexOf(",", rsrqStartIndex);
      String rsrqStr = response.substring(rsrqStartIndex, rsrqEndIndex);
      int rsrq = rsrqStr.toInt();

      Serial.println("RSRP: " + String(rsrp) + " dBm");
      Serial.println("RSRQ: " + String(rsrq) + " dB");
      

      Blynk.virtualWrite(V6, rsrp);
      Blynk.virtualWrite(V7, rsrq);

    }
  }
  Blynk.run();
}
