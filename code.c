#define BLYNK_TEMPLATE_ID "TMPL2hZhxNTDR"
#define BLYNK_TEMPLATE_NAME "smart agriculture"
#define BLYNK_AUTH_TOKEN "qbMzhzMruwxfLiGlemLSxSB4fWx7FCO3"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// --- Identifiants WiFi ---
char ssid[] = "John jml";
char pass[] = "johnmulonga10";

// --- Définition des capteurs ---
#define TRIG_PIN 33 // Ultrason Trigger
#define ECHO_PIN 25 // Ultrason Echo
#define DHTPIN 26   // Pin du capteur DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define RAIN_PIN 12  // Capteur de pluie (digital)
#define SOIL_PIN 27  // Capteur humidité sol (analogique)
#define RELAY_PIN 4 // Relais sur GPIO35

// --- Setup Blynk ---
BlynkTimer timer;

// Variables pour mode manuel/auto
bool manualMode = false;
bool manualPumpState = false;

// --- Fonction lecture capteurs ---
void sendSensor() {
  // Distance Ultrason
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // cm
  Blynk.virtualWrite(V1, distance);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Température
  float temp = dht.readTemperature();
  Blynk.virtualWrite(V2, temp);
  Serial.print("Température: ");
  Serial.print(temp);
  Serial.println(" °C");

  // Pluie (digital : 0/1)
  int rainDigital = digitalRead(RAIN_PIN);
  int pluie = (rainDigital == HIGH) ? 1 : 0;
  Blynk.virtualWrite(V3, pluie);
  Serial.print("Pluie: ");
  Serial.println(pluie);

  // Humidité du sol (analogique)
  int soilValue = analogRead(SOIL_PIN);
  Serial.print("Humidité sol brute: ");
  Serial.println(soilValue);
  int seuil = 2000;
  int soilState = (soilValue > seuil) ? 1 : 0; // 1 = sec, 0 = humide
  Blynk.virtualWrite(V5, soilState);

  // --- Gestion pompe ---
  if (!manualMode) {
    if (soilState == 1) {
      digitalWrite(RELAY_PIN, HIGH);
      Blynk.virtualWrite(V4, 1);
      Serial.println("Mode AUTO → Sol sec → Pompe activée !");
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Blynk.virtualWrite(V4, 0);
      Serial.println("Mode AUTO → Sol humide → Pompe arrêtée !");
    }
  } else {
    digitalWrite(RELAY_PIN, manualPumpState ? HIGH : LOW);
    Blynk.virtualWrite(V4, manualPumpState ? 1 : 0);
    Serial.print("Mode MANUEL → Pompe ");
    Serial.println(manualPumpState ? "activée !" : "arrêtée !");
  }
}

// --- Bouton Blynk pour activer/désactiver le mode manuel ---
BLYNK_WRITE(V8) {
  manualMode = param.asInt(); // 1 = manuel, 0 = auto
  Serial.print("Mode changé : ");
  Serial.println(manualMode ? "MANUEL" : "AUTO");
}

// --- Bouton Blynk pour contrôler la pompe en manuel ---
BLYNK_WRITE(V9) {
  manualPumpState = param.asInt(); // 1 = ON, 0 = OFF
  Serial.print("Commande manuelle pompe : ");
  Serial.println(manualPumpState ? "ON" : "OFF");
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  dht.begin();

  // Connexion WiFi
  Serial.print("Connexion au WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi connecté !");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  // Connexion Blynk
  Serial.println("Connexion à Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Envoi des données toutes les 2 secondes
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
#define BLYNK_TEMPLATE_ID "TMPL2hZhxNTDR"
#define BLYNK_TEMPLATE_NAME "smart agriculture"
#define BLYNK_AUTH_TOKEN "qbMzhzMruwxfLiGlemLSxSB4fWx7FCO3"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// --- Identifiants WiFi ---
char ssid[] = "John jml";
char pass[] = "johnmulonga10";

// --- Définition des capteurs ---
#define TRIG_PIN 33 // Ultrason Trigger
#define ECHO_PIN 25 // Ultrason Echo
#define DHTPIN 26   // Pin du capteur DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define RAIN_PIN 12  // Capteur de pluie (digital)
#define SOIL_PIN 27  // Capteur humidité sol (analogique)
#define RELAY_PIN 4 // Relais sur GPIO35

// --- Setup Blynk ---
BlynkTimer timer;

// Variables pour mode manuel/auto
bool manualMode = false;
bool manualPumpState = false;

// --- Fonction lecture capteurs ---
void sendSensor() {
  // Distance Ultrason
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // cm
  Blynk.virtualWrite(V1, distance);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Température
  float temp = dht.readTemperature();
  Blynk.virtualWrite(V2, temp);
  Serial.print("Température: ");
  Serial.print(temp);
  Serial.println(" °C");

  // Pluie (digital : 0/1)
  int rainDigital = digitalRead(RAIN_PIN);
  int pluie = (rainDigital == HIGH) ? 1 : 0;
  Blynk.virtualWrite(V3, pluie);
  Serial.print("Pluie: ");
  Serial.println(pluie);

  // Humidité du sol (analogique)
  int soilValue = analogRead(SOIL_PIN);
  Serial.print("Humidité sol brute: ");
  Serial.println(soilValue);
  int seuil = 2000;
  int soilState = (soilValue > seuil) ? 1 : 0; // 1 = sec, 0 = humide
  Blynk.virtualWrite(V5, soilState);

  // --- Gestion pompe ---
  if (!manualMode) {
    if (soilState == 1) {
      digitalWrite(RELAY_PIN, HIGH);
      Blynk.virtualWrite(V4, 1);
      Serial.println("Mode AUTO → Sol sec → Pompe activée !");
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Blynk.virtualWrite(V4, 0);
      Serial.println("Mode AUTO → Sol humide → Pompe arrêtée !");
    }
  } else {
    digitalWrite(RELAY_PIN, manualPumpState ? HIGH : LOW);
    Blynk.virtualWrite(V4, manualPumpState ? 1 : 0);
    Serial.print("Mode MANUEL → Pompe ");
    Serial.println(manualPumpState ? "activée !" : "arrêtée !");
  }
}

// --- Bouton Blynk pour activer/désactiver le mode manuel ---
BLYNK_WRITE(V8) {
  manualMode = param.asInt(); // 1 = manuel, 0 = auto
  Serial.print("Mode changé : ");
  Serial.println(manualMode ? "MANUEL" : "AUTO");
}

// --- Bouton Blynk pour contrôler la pompe en manuel ---
BLYNK_WRITE(V9) {
  manualPumpState = param.asInt(); // 1 = ON, 0 = OFF
  Serial.print("Commande manuelle pompe : ");
  Serial.println(manualPumpState ? "ON" : "OFF");
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  dht.begin();

  // Connexion WiFi
  Serial.print("Connexion au WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi connecté !");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  // Connexion Blynk
  Serial.println("Connexion à Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Envoi des données toutes les 2 secondes
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
