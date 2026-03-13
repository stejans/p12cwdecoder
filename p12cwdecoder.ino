/**
 * P12 CW Decoder
 * Stefan Jansen,  DK7STJ, 02/2026
 * Für weitere Erläuterungen bitte README.md lesen.
 */

// Arduino-Befehle. Wird standardmäßig im Hauptsketch eingebunden.
#include <Arduino.h>

// Bibliotheken
#include <LiquidCrystal.h>
#include <Encoder.h>

// Eigene Hilfsklassen
#include "MyButton.h"
#include "MyPoti.h"
#include "CWSpeed.h"
#include "CWPlayer.h"

// LCD-Pins: RS, E, D4, D5, D6, D7
///LiquidCrystal lcd(2,3,4,5,6,7);
//  Taster
MyButton cwKey(12);
MyButton qsvKey(11);

// Poti für CW-Geschwindigkeit
MyPoti speedPoti(A0,30,200);

// Pins
const int ledPin = 10;
const int buzzerPin = 9;

const int cwFreq = 500;
bool CWPinsInit = false;

/**
 * CW Ton und LED einschalten.
 */
void cwToneOn() {
	if (CWPinsInit) {
		digitalWrite(ledPin, HIGH);
		tone(buzzerPin, cwFreq);
	}
}

/**
 * CW Ton und LED ausschalten.
 */
void cwToneOff() {
	if (CWPinsInit) {
		digitalWrite(ledPin, LOW);
		noTone(buzzerPin);
	}
}

// CW setup
CWSpeed cwSpeed(60,30,200);
CWPlayer cwOut(cwSpeed, cwToneOn, cwToneOff);

// Aktueller Zustand des Systems
enum UIState {
	INIT, // Initialisierungsphase
	DECODE, // Morsezeichen decodieren
	QSV // V ausgeben
} uiState = UIState::INIT;

// Globale Variablen

/**
 * Initialisierung des Arduino-Sketchs
 */
void setup() {
	// setup pins
    cwKey.init();
    qsvKey.init();
	speedPoti.init();
	pinMode(ledPin, OUTPUT);
	pinMode(buzzerPin, OUTPUT);
	digitalWrite(ledPin, LOW);
	digitalWrite(buzzerPin, LOW);
	CWPinsInit = true;
	// init seriel port and wait for availability
	Serial.begin(9600);
	while (!Serial) delay(100);
	// Warte, evtl. entprellung Reset
	delay(100);
	Serial.println("\nStartup");
	uiState = UIState::DECODE;
	Serial.print(speedPoti.value());
	Serial.print(" ");
}

/**
 * Schleifenfunktion des Arduino-Sketchs
 */
void loop() {
	cwKey.read();
	qsvKey.read();
	if (speedPoti.read()) {
		Serial.print(speedPoti.value());
		Serial.print(" ");
	}
	if (cwKey.isPressed()) {
		cwToneOn();
	} else if (cwKey.isReleased()) {
		cwToneOff();
	}
	if (qsvKey.isPressed()) {
		cwOut.play("Das ist ein Test.");
	}
	// Hällt alle Aktivitäten am Laufen
	cwOut.doWork();
}
