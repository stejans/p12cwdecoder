#include "CWSpeed.h"
#include <Arduino.h>

CWSpeed::CWSpeed(unsigned int cpm, unsigned int minSpeed, unsigned int maxSpeed)
: m_MinSpeed(min(minSpeed,maxSpeed)), m_MaxSpeed(max(minSpeed,maxSpeed)) {
    setSpeed(cpm);
}

/**
 * Setze CW-Geschwindigkeit in Zeichen pro Minute.
 * Ermittle daraus die Werte für die Dauer eines Dit, Dah und der Pausen
 * zwischen Zeichen und Wörtern.
 */
bool CWSpeed::setSpeed(unsigned int newcpm = 0) {
	const unsigned int oldcpm = m_cpm;
	if (newcpm==0) {
	    newcpm = 60;
    }
	if (newcpm<m_MinSpeed) {
	    newcpm = m_MinSpeed;
	} else if (newcpm>m_MaxSpeed) {
	    newcpm = m_MaxSpeed;
    }
    m_cpm = newcpm;
	m_wpm = m_cpm/5;
	m_DotDuration = 6000/m_cpm; // 60s/(m_wpm*50), da paris 50 Einheiten lang ist.
	m_DashDuration = m_DotDuration * 3;
	m_LetterPause = m_DotDuration * 3;
	m_WordPause = m_DotDuration * 7;
	return (m_cpm!=oldcpm);
}

bool CWSpeed::incSpeed() {
	return setSpeed(m_cpm+1);
}

bool CWSpeed::decSpeed() {
	return setSpeed(m_cpm-1);
}

unsigned int CWSpeed::cpm() const {
	return m_cpm;
}

unsigned int CWSpeed::wpm() const {
	return m_wpm;
}

unsigned int CWSpeed::dotDuration() const {
	return m_DotDuration;
}

unsigned int CWSpeed::dashDuration() const {
	return m_DashDuration;
}

unsigned int CWSpeed::letterPause() const {
	return m_LetterPause;
}

unsigned int CWSpeed::wordPause() const {
	return m_WordPause;
}
