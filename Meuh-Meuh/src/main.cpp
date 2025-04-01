#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <DHT.h>

#define BLYNK_TEMPLATE_ID "TMPL5qJhRIOVk"
#define BLYNK_TEMPLATE_NAME "Marguerite"
#define BLYNK_AUTH_TOKEN "wwkkEue-oSGgnusy7tw14l0gou2J6iY9"

#include <BlynkSimpleEsp32.h> 


#define BUZZER_PIN 27  
#define DHTPIN 14        
#define DHTTYPE DHT22    
#define SAMPLING_TIME 5000  

WiFiMulti wifiMulti;
DHT dht(DHTPIN, DHTTYPE);

#define TEMPO 10  // Ralentir la musique (avant : 1000)

#define  c3    7634
#define  d3    6803
#define  e3    6061
#define  f3    5714
#define  g3    5102
#define  a3    4545
#define  b3    4049
#define  c4    3816
#define  d4    3401
#define  e4    3030
#define  f4    2865
#define  g4    2551
#define  a4    2272
#define  a4s   2146
#define  b4    2028
#define  c5    1912
#define  d5    1706
#define  d5s   1608
#define  e5    1517
#define  f5    1433
#define  g5    1276
#define  a5    1136
#define  a5s   1073
#define  b5    1012
#define  c6    955

#define  R     0      // Définir une note spéciale, 'R', pour représenter une pause

// Mélodie Star Wars Theme avec une durée de note augmentée pour ralentir la musique
int melody[] = {  a4, R,  a4, R,  a4, R,  f4, R, c5, R,  a4, R,  f4, R, c5, R, a4, R,  e5, R,  e5, R,  e5, R,  f5, R, c5, R,  g5, R,  f5, R,  c5, R, a4, R};
int beats[]  = {  100, 40, 100, 40, 100, 40, 80, 10, 40, 10, 120, 20, 80, 10, 40, 10, 120, 160, 100, 40, 100, 40, 100, 40, 80, 10, 40, 10, 120, 20, 80, 10, 40, 10, 120, 80};

int noteIndex = 0;  
unsigned long lastNoteTime = 0;
bool playMelody = false;  
unsigned long lastSendTime = 0; 

BLYNK_WRITE(V2) {  
    int buttonState = param.asInt();  
    playMelody = (buttonState == 1);
}

void setup() {
    Serial.begin(115200);
    Serial.println();

    dht.begin();

    WiFi.mode(WIFI_STA);
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, IPAddress(8, 8, 8, 8)); 
    wifiMulti.addAP("Daydream", "cntw929fqkn4j8y");

    Serial.print("Connexion WiFi...");
    while (wifiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\n✅ Connecté au WiFi!");

    Blynk.config(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);  
    Blynk.connect();

    pinMode(BUZZER_PIN, OUTPUT);
    ledcSetup(0, 5000, 8);  
    ledcAttachPin(BUZZER_PIN, 0);
}


void playMelodyFunction() {
  if (playMelody) {
      unsigned long currentMillis = millis();

      // Vérifie si le temps écoulé est plus grand ou égal à la durée de la note
      if (currentMillis - lastNoteTime >= beats[noteIndex]*TEMPO) {  
          lastNoteTime = currentMillis;  // Met à jour le temps de la dernière note

          if (melody[noteIndex] != R) {
              ledcWriteTone(0, melody[noteIndex]);  // Joue la note
          } else {
              ledcWriteTone(0, 0);  // Aucun son (pause)
          }

          noteIndex++;  // Passe à la note suivante

          if (noteIndex >= sizeof(melody) / sizeof(melody[0])) {
              noteIndex = 0;  // Recommence la mélodie
              playMelody = false;  // Arrête la lecture
          }
      }
  }
}
void sendTemperatureAndHumidity() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int fever = 0;

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("❌ Échec de lecture du capteur DHT!");
        return;
    }

    Serial.printf("🌡 Temp: %.2f°C | 💧 Hum: %.2f%%\n", temperature, humidity);
    if(temperature > 39 || temperature < 38){
      fever = 1;
    }

    if (Blynk.connected()) {
        Blynk.virtualWrite(V1, temperature);
        Blynk.virtualWrite(V0, humidity);
        Blynk.virtualWrite(V3, fever);
        Serial.println("✅ Données envoyées à Blynk !");
    } else {
        Serial.println("❌ Blynk non connecté, tentative de reconnexion...");
        Blynk.connect();
    }
}

void loop() {
    Blynk.run();

    if (playMelody) {
        playMelodyFunction();
    }

    unsigned long currentMillis = millis();
    if (currentMillis - lastSendTime >= SAMPLING_TIME) {
        sendTemperatureAndHumidity();
        lastSendTime = currentMillis;
    }
}
