#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define capF A0
#define capm 12
#define DHTPIN 4
#define DHTTYPE DHT11
#define TOPIC "t"
#define TOPIC1 "h"
#define TOPIC2 "capm"
#define TOPIC3 "wc"
#define TOPIC4 "ip"
#define TOPIC5 "capF"

DHT dht(DHTPIN, DHTTYPE);  //type nom paramètres .
float t, h, f;
WiFiClient espClient;
PubSubClient mqtt(espClient);
const char* mqtt_server = "broker.emqx.io";  //broker.emqx.io" //IP
String statWifi;
IPAddress ip;
void setup() {

  pinMode(DHTPIN, INPUT);
  pinMode(capm, INPUT);
  pinMode(capF, INPUT);
  Serial.begin(9600);

  Serial.println("check_wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin("Ooredoo _M30_3E7A", "6DB5D10D");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);

    Serial.println("...echec");
    Serial.println(statWifi);  //si le wifi n'est pas connecté
  }
  Serial.println("");
  statWifi = "connecté";
  Serial.println(statWifi);
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  ip = WiFi.localIP();
  Serial.println(ip);
  //wifi connecté
  delay(100);
  mqtt.setServer(mqtt_server, 1883);
  dht.begin();
   delay(1000);
}

void loop() {


  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  String data_t = String(t);
  String data_h = String(h);
  String data_c = String(capm);
  String data_f = String(capF);

  int stat1 = digitalRead(capm);
  int stat = analogRead(capF);
if (mqtt.connected()) {
    // publish
    mqtt.publish(TOPIC, data_t.c_str());
    mqtt.publish(TOPIC1, data_h.c_str());
    mqtt.publish(TOPIC2, data_c.c_str());
    mqtt.publish(TOPIC4, ip.toString().c_str(), true);
    mqtt.publish(TOPIC5, data_f.c_str());
    mqtt.publish(TOPIC3, statWifi.c_str());
    delay(1000);
    mqtt.loop();
  } else {
    while (!mqtt.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Attempt to connect
      if (mqtt.connect("oha")) {
        Serial.println("connected");
        // Once connected, publish an announcement...
      } else {
        Serial.print("failed, rc=");
        Serial.print(mqtt.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }
}
