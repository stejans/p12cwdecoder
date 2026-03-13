#include <Arduino.h>
#include "MyPoti.h"

MyPoti::MyPoti(unsigned int pin, int outMin, int outMax, unsigned int minThreshhold)
: m_Pin(pin), 
  m_OutMin(min(outMin,outMax)), m_OutMax(max(outMin,outMax)),
  m_InStepSize(1023.0/(abs(outMax-outMin)+1)),
  m_Threshhold(max((1024/(abs(outMax-outMin)+1)), minThreshhold)),
  m_InValue(0), m_OutValue(0),
  m_HasChanged(false)
{}

void MyPoti::init() {
    m_InValue = analogRead(m_Pin);
    doMapping();
    m_HasChanged = false;
}

bool MyPoti::read() {
    unsigned int val = analogRead(m_Pin);
    if (abs(m_InValue-val)>=m_Threshhold) {
      int oldVal = m_OutValue;
        m_InValue = val;
        doMapping();
        m_HasChanged = (m_OutValue!=oldVal);
    } else {
        m_HasChanged = false;
    }
    return m_HasChanged;
}

bool MyPoti::hasChanged() const {
    return m_HasChanged;
}

int MyPoti::value() const {
    return m_OutValue;
}

unsigned int MyPoti::threshhold() const {
    return m_Threshhold;
}

void MyPoti::doMapping() {
	m_OutValue = int(m_OutMin+m_InValue/m_InStepSize);
	if (m_OutValue<m_OutMin) m_OutValue = m_OutMin;
	else if (m_OutValue>m_OutMax) m_OutValue = m_OutMax;
}
