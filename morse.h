#ifndef MORSE_H
#define MORSE_H
#include <Arduino.h>

/**
 * Umwandlung von Morsecodes in Zeichen und umgekehrt.
 * Bei der Umwandlung gibt der parameter replace an, was passiert, wenn in
 * der Codetabelle kein passender Eintrag gefunden wird.
 * Bei false wird 0 zurückgegeben, bei true wird jedes nicht gefundene Zeichen
 * auf ein Fragezeichen abgebildet.
 *
 * Idee von Matthias Kühlewein, DL2SDO:
 * Morsezeichen werden als einzelnes Byte (8 Bit) kodiert. Ein auf 1 gesetztes Bit 
 * entspricht einem Dah, ein auf 0 gesetztes Bit einem Dit. Man könnte theoretisch
 * also 8 Dits oder Dahs in einem Byte unterbringen. Aber man braucht noch
 * die Information, aus wie vielen Elementen das Morsezeichen tatsächlich besteht.
 * Daher wird das erste auf 1 gesetzte Bit von links (höherwertig) als Anfangsbit
 * oder Startbit interpretiert. Alle weiteren Bits stellen das Morsezeichen dar.
 * Es passen also letztendlich 7 Elemente in ein Byte.
 * Die Bytewerte 0x0 und 0x1 sind ungültig. 0x0 enthält kein Startbit und 0x1
 * Wäre ein Morsezeichen mit 0 Elementen. Diese Werte können für spezielle
 * Situationen genutzt werden.
 */

struct MorseMap {
    char letter;
    byte code;
};

char morse2char(byte m, bool replace = true);
const MorseMap& char2morse(char c);

#endif