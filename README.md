# Marguerite

# Collier IoT pour le Suivi du Bétail

## Description du Projet
Ce projet vise à développer un collier connecté permettant le suivi en temps réel de la **température corporelle** et du **comportement** des animaux d'élevage. Il s'appuie sur l'**ESP32**, le capteur **DHT22** et la plateforme **Blynk** pour l'affichage des données.

## Objectifs
- Suivi de la **température et de l'humidité**
- Alertes en cas de **fièvre**
- Notification en **temps réel**
- **Interaction à distance** via Blynk

---
## Matériel Utilisé
- **ESP32** (Microcontrôleur)
- **Capteur DHT22** (Température & Humidité)
- **Buzzer** (Signaux sonores)
- **WiFi Module** pour connexion à Blynk

---
## Installation & Configuration
### 1 Prérequis
- Arduino IDE installé
- Bibliothèques suivantes installées :
  - `WiFi.h`
  - `WiFiMulti.h`
  - `HTTPClient.h`
  - `DHT.h`
  - `BlynkSimpleEsp32.h`

### 2 Configuration de Blynk
1. Créer un projet sur [Blynk Cloud](https://blynk.cloud/)
2. Récupérer le `BLYNK_AUTH_TOKEN`
3. Modifier le fichier `main.ino` en insérant vos informations WiFi et Token Blynk

---
## Utilisation
1. **Compiler & téléverser** le code sur l'ESP32
2. Lancer l'application **Blynk** et observer les données en temps réel
3. L'ESP32 envoie **température et humidité** toutes les 5 secondes
4. Un **buzzer** se déclenche à volonté

---
## Fonctionnalités
**Suivi Température / Humidité**
**Alerte Fièvre**
**Mise à jour en temps réel sur Blynk**
**Mélodie sonore activable à distance**

---
## Contributeurs
- **MAYA** - Hackathon "CReATE an IoT Product for Good"
- Anaîs de la Rivière - Ariane Maccou - Augustin Poisson

