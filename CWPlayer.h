#ifndef CW_PLAYER_H
#define CW_PLAYER_H
#include <Arduino.h>

/** Forward declarations. Man muss so die entsprechenden .h-Dateien nicht 
** einbinden und kann trotzdem die Datentypen dem Compiler bekanntgeben.
 */
class CWSpeed;

/**
 * Klasse zum Umwandeln von Text in Morsezeichen und Ausgeben mit zwei Callback-Funktionen.
 */
class CWPlayer {
public:
    CWPlayer(const CWSpeed& cwSpeed, void (*onCB)(), void (*offCB)());
    void play(const String& message, bool addSpace = false, bool repeat = false);
    void stop();
    /**
     * doWork() muss in jedem Durchlauf der globalen loop()-Funktion aufgerufen werden.
     * Es gibt Schritt für Schritt den String aus play() aus und blockiert
     * dabei die CPU nicht.
     */
    void doWork();
private:
    void restart();
    const CWSpeed& m_CWSpeed;
    void (* const m_CWOnCB)();
    void (*const m_CWOffCB)();
    String m_Message;
    char* m_pNextChar;
    byte m_ElementsToPlay;
    byte m_MorseCode;
    unsigned int m_NextEventTime;
    bool m_IsOnPhase; 
    bool m_Repeat;
};

#endif