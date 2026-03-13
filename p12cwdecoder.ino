/**
 * P12 CW Decoder
 *
 * Stefan Jansen,  DK7STJ, 02/2026
 *
 * Dieses Projekt darf unbegrenzt weitergegeben und modifiziert werden.
 * Die Nennung des Autors (DK7STJ) ist bei Weitergabe und Modifikation
 * erwünscht.
 *
 * Projektziel:
 * Entwicklung eines Morsedecoders, speziell für Vorführungen und für den 
 * Stand von P12 auf dem Tübinger Weihnachtsmarkt.
 *
 * Funktionen:
 * - Bedienbar durch Handtaste (straight key) oder Taster.
 * - Mithörton und LED-Anzeige.
 * - Geschwindigkeit über Poti einstellbar, muss zum Gebetempo passen.
 * - V-Modus, macht QSV zur besseren Einschätzung der Geschwindigkeit.
 * - Reset-Taster
 * - LCD-Display mit regelbaren Kontrast
 * - Ausgabe aller Aktionen über RS232 bzw. USB.
 *
 * Hardware / Stückliste:
 * - Breadboard oder Platine zum festen Aufbau.
 * - Arduino Uno oder vergleichbares Board, evtl. anpassungen und weitere
 *   Teile notwendig.
 * - Jumperdrähte in passender Länge
 * - 16×2 LCD (HD44780 kompatibel)
 * - Vorwiderstand für Hintergrundbeleuchtung des Displays, z.B. 220Ohm
 * - 2 Potentiometer zu 10kOhm (für Geschwindigkeit und Kontrast)
 * - passiver Piezzo-Buzzer, evtl. mit Vorwiderstand für
 *   Lautstärkenanpassung 220Ohm
 * - 3 Taster (Taster parallel zur Morsetaste und Resettaster können je nach
 *   Bedarf weggelassen werden)
 * - 2 Kondensatoren zur Entprellung der Taster, z.B. 100nf. Der
 *   Reset-taster wird absichtlich nicht entprellt, um die interne Logik 
 *   (Flankenerkennung) und das Zusammenspiel mit der RTS-Leitung der
 *   seriellen Schnittstelle nicht zu beeinflussen.
 *   Reset-Taster weggelassen werden
 * - LED mit Vorwiderstand, z.B. 220Ohm bis 1kOhm
 *
 * Verdrahtung:
 * - LCD (4-Bit-Modus):
 *   Display   -->   Arduino
 *   RS              D2
 *   E               D3
 *   D4              D4
 *   D5              D5
 *   D6              D6
 *   D7              D7
 *   VSS             GND
 *   VDD             5V
 *   VO              Mittelpin Kontrast-Poti, Poti zwischen 5V und GND.
 *   A (Backlight +) 5V (über Widerstand 220Ohm)
 *   K (Backlight -) GND
 * - Andere Bauteile:
 *   - RESET --> Taster --> GND
 *   - D12 --> Taster für CW --> GND
 *     Parallel zum Taster Entprellkondensator.
 *     Ebenfalls parallel dazu Morsetaste. 
 *   - D11 --> Taster für QSV --> GND
 *     Parallel zum Taster Entprellkondensator.
 *   - D10 --> Vorwiderstand --> LED --> GND 
 *   - D9 --> evtl. 220Ohm --> passiver Buzzer --> GND
 *   - Poti für Geschwindigkeit zwischen 5V und GND, Mittelpin an A0
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
