#include <Arduino.h>
#include "MyButton.h"

MyButton::MyButton(unsigned int pin)
: m_Pin(pin), m_IsDown(false), m_HasChanged(false)
{}

void MyButton::init() {
    pinMode(m_Pin, INPUT_PULLUP);
    m_IsDown = (digitalRead(m_Pin)==LOW);
    m_HasChanged = false;
}

bool MyButton::read() {
    bool oldState = m_IsDown;
    m_IsDown = (digitalRead(m_Pin)==LOW);
    m_HasChanged = (m_IsDown!=oldState);
    return m_HasChanged;
}

bool MyButton::hasChanged() const {
    return m_HasChanged;
}

bool MyButton::isDown() const {
    return m_IsDown;
}

bool MyButton::isUp() const {
    return !m_IsDown;
}

bool MyButton::isPressed() const {
    return m_HasChanged && m_IsDown;
}

bool MyButton::isReleased() const {
    return m_HasChanged && !m_IsDown;
}
