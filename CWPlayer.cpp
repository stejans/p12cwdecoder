#define CW_PLAYER_DEBUG
#include "CWPlayer.h"
#include "CWSpeed.h"
#include "morse.h"

CWPlayer::CWPlayer(const CWSpeed& cwSpeed, void (*onCB)(), void (*offCB)())
: m_CWSpeed(cwSpeed), m_CWOnCB(onCB), m_CWOffCB(offCB), m_Message(""),
  m_pNextChar(nullptr),
  m_ElementsToPlay(0), m_MorseCode(0),
  m_NextEventTime(0), m_IsOnPhase(false),
  m_Repeat(false) {
    stop();
}

void CWPlayer::play(const String& message, bool addSpace, bool repeat) {
    stop();
    m_Message = message;
    m_Message.toUpperCase();
    if (addSpace && m_Message.length()>0 && !isSpace(m_Message[m_Message.length()-1])) {
        m_Message += ' ';
    }
    m_Repeat = repeat;
}

void CWPlayer::stop() {
#ifdef CW_PLAYER_DEBUG
    if (m_Message.length()>0) Serial.print("<AR>");
#endif
    restart(); // Setzt alle übrigen Werte zurück.
    m_Repeat = false;
    m_Message = "";
}

void CWPlayer::restart() {
    m_NextEventTime = 0;
    m_IsOnPhase = false;
    m_CWOffCB();
    m_ElementsToPlay = 0;
    m_MorseCode = 0;
    m_pNextChar = nullptr;
}

void CWPlayer::doWork() {
    // Wenn wir noch nicht mit der Ausgabe begonnen haben, setzen wir uns auf
    // das erste Zeichen.
    if (m_pNextChar==nullptr && m_Message.length()>0) {
        m_pNextChar = m_Message.c_str();
#ifdef CW_PLAYER_DEBUG
        Serial.print("<CT>");
#endif
    }
    if (millis()<m_NextEventTime) {
        // Wir sind gerade dabei, ein Dit, Dah oder eine Pause auszugeben.
        // Wir warten einfach, bis bei einem der nächsten Durchläufe die 
        // Zeit um ist.
    } else if (m_NextEventTime>0 && millis()>=m_NextEventTime) {
        // Die Zeit ist um.
        if (m_IsOnPhase) {
            // Wenn das gerade der aktive Teil eines Dit oder Dah war, dann
            // geben wir jetzt die Pause aus.
            m_CWOffCB();
            m_IsOnPhase = false;
            if (m_ElementsToPlay>0) {
                m_NextEventTime = millis()+m_CWSpeed.dotDuration();
            } else if (*m_pNextChar && isSpace(*m_pNextChar)) {
                m_NextEventTime = millis()+m_CWSpeed.wordPause();
            } else {
                m_NextEventTime = millis()+m_CWSpeed.letterPause();
            }
        } else {
            // Ausgabe des aktuellen Elements beenden.
            // Beim nächsten Durchlauf geht's weiter.
            m_NextEventTime = 0;
            m_IsOnPhase = false;
        }
    } else if (m_ElementsToPlay>0) {
        // Wenn wir gerade ein Zeichen ausgeben, dann damit weitermachen.
        m_IsOnPhase = true;
        if (m_MorseCode&0x80) {
            m_NextEventTime = millis()+m_CWSpeed.dashDuration();
#ifdef CW_PLAYER_DEBUG
            Serial.print("-");
#endif
        } else {
            m_NextEventTime = millis()+m_CWSpeed.dotDuration();
#ifdef CW_PLAYER_DEBUG
            Serial.print(".");
#endif
        }
        m_CWOnCB();
        m_MorseCode <<= 1;
        m_ElementsToPlay--;
    } else if (m_pNextChar!=nullptr) {
        // Wenn wir auf einem gültigen Zeichen sitzen, dann dieses als nächstes
        // in Angriff nehmen.
        if (*m_pNextChar) {
#ifdef CW_PLAYER_DEBUG
            Serial.print(*m_pNextChar);
#endif
            if (!isSpace(*m_pNextChar)) {
                // Zeichen nachschlagen und ausgeben.
                m_MorseCode = char2morse(*m_pNextChar).code;
                m_ElementsToPlay = 7;
                while (m_ElementsToPlay>0 && !(m_MorseCode&0x80)) {
                    m_ElementsToPlay--;
                    m_MorseCode <<= 1;
                }
                m_MorseCode <<= 1; // Startbit rausschieben.
            }
            m_pNextChar++;
        } else if (m_Repeat) {
            restart();
        } else {
            stop();
        }
    } 
}
