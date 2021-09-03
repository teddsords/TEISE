#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <MPU9250.h>
#include <Wire.h>

#define FIREBASE_HOST "https://esp32-and-gps-module-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "Lqtv981CPz9Zrt4T02dyJFI8gxZmFgYOawKd2gJJ"
#define WIFI_SSID "2G_H504"
#define WIFI_PASSWORD "94500519"

//Define FirebaseEsp32 data object
FirebaseData firebaseData;
FirebaseJson json, lngJson, latJson, tmpJson;

static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;
int status;
float tmp, lati = 0, lnge = 0;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// The MPU9250 object
MPU9250 IMU(Wire, 0x68);

void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
  status = IMU.begin();

  //Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("WiFi connected.");

  // Firebase configs
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.


  Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
  Serial.println(gps.time.hour()); // Hour (0-23) (u8)
  Serial.println(gps.time.minute()); // Minute (0-59) (u8)
  Serial.println(gps.time.second()); // Second (0-59) (u8)
  Serial.println(gps.satellites.value()); // Number of satellites in use (u32)
  Serial.println("-------------------------------");

  IMU.readSensor();
  Serial.print("Temperature: ");
  tmp = IMU.getTemperature_C();
  Serial.println(tmp, 2);

  while (ss.available() > 0)
  {
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid()) {
        Serial.print("Latitude= ");
        lati = gps.location.lat();
        Serial.println(lati);
        Serial.print(" Longitude= ");
        lnge = gps.location.lng();
        Serial.println(lnge);

        // Writing to database
        enviarDados();
      }
    }
  }
  //enviarDados();
  delay(60000);
}

// Function to be called when writing to database
bool enviarDados()
{
  //json.add("_data2", "_value2");
  //updateData.add("data1", "value1");
  lngJson.add("lat", lati);
  Firebase.RTDB.updateNode(&firebaseData, "/", &lngJson);

  latJson.add("lng", lnge);
  Firebase.RTDB.updateNode(&firebaseData, "/", &latJson);

  tmpJson.add("tmp", tmp);
  Firebase.RTDB.updateNode(&firebaseData, "/", &tmpJson);

}

// Function to be called to read data from database
void lerDados()
{
  if (Firebase.getInt(firebaseData, "/lat"))
  {
    Serial.println("Estou dentro o primeiro if");
    if (firebaseData.dataType()) {
      Serial.println("Estou apos o segundo if");
      Serial.println(firebaseData.intData());
    }

  } else {
    Serial.println("Estou dentro o else");
    Serial.println(firebaseData.errorReason());
  }
}
