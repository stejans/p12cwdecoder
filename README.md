# p12cwedecoder
Morsedecoder für P12 DARC e.V. Tübingen

Stefan Jansen,  DK7STJ, 02/2026

Dieses Projekt darf unbegrenzt weitergegeben und modifiziert werden.
Die Nennung des Autors (DK7STJ) ist bei Weitergabe und Modifikation
erwünscht.
 *
## Projektziel

Entwicklung eines Morsedecoders, speziell für Vorführungen und für den Stand von P12 auf dem Tübinger Weihnachtsmarkt.

## Funktionen
- Bedienbar durch Handtaste (straight key) oder Taster.
- Mithörton und LED-Anzeige.
- Geschwindigkeit über Poti einstellbar, muss zum Gebetempo passen.
- QSV-Modus, gibt kontinuierlich ein V zur besseren Einschätzung der Geschwindigkeit.
- Reset-Taster
- LCD-Display mit regelbarem Kontrast
- Ausgabe aller Aktionen über RS232 bzw. USB.

## Hardware / Stückliste
- Breadboard zum temporären oder Platine zum festen Aufbau.
- Arduino Uno oder vergleichbares Board, evtl. anpassungen und weitere Teile notwendig.
- Jumperdrähte in passender Länge
- 16×2 LCD (HD44780 kompatibel)
- Vorwiderstand für Hintergrundbeleuchtung des Displays, z.B. 220Ohm
- 2 Potentiometer zu 10kOhm (für Geschwindigkeit und Kontrast)
- passiver Piezzo-Buzzer, evtl. mit Vorwiderstand für Lautstärkenanpassung 220Ohm
- 3 Taster (Taster parallel zur Morsetaste und Resettaster können je nach Bedarf weggelassen werden)
- 2 Kondensatoren zur Entprellung der Taster, z.B. 100nf. Der Reset-taster wird absichtlich nicht entprellt, um die interne Logik (Flankenerkennung) und das Zusammenspiel mit der RTS-Leitung der seriellen Schnittstelle nicht zu beeinflussen.
- LED mit Vorwiderstand, z.B. 220Ohm bis 1kOhm

## Verdrahtung

### LCD (4-Bit-Modus):

| Display | Arduino |
|:--------|:--------|
| RS      | D2      |
| E       | D3      |
| D4      | D4      |
| D5      | D5      |
| D6      | D6      |
| D7      | D7      |
| VSS     | GND     |
| VDD     | +5V     |
| VO      | Mittelpin Kontrast-Poti, Poti zwischen +5V und GND. |
| A (Backlight +) | +5V (je nach Display über Widerstand 220Ohm) |
| K (Backlight -) | GND |

## Andere Bauteile
- RESET --> Taster --> GND
- D12 --> Taster für CW --> GND.
  - Parallel zum Taster Entprellkondensator.
  - Ebenfalls parallel dazu Morsetaste. 
- D11 --> Taster für QSV --> GND
  -  Parallel zum Taster Entprellkondensator.
- D10 --> Vorwiderstand --> LED --> GND 
- D9 --> evtl. 220Ohm --> passiver Buzzer --> GND
- Poti für Geschwindigkeit zwischen 5V und GND, Mittelpin an A0
