#ifndef MY_POTI_H
#define MY_POTI_H

/**
 * Verwaltet ein Poti samt Abbildung auf einen gegebenen Wertebereich.
 * Verwendet eine bessere map-Funktion als das eingebaute map().
 */
class MyPoti {
public:
    /**
     *Anlegen des MyPoti-objekts mit Ausgabewertebereich.
     * Optional kann ein Schwellwert angegeben werden, der auf dem
     * Eingabebereich wirkt. Der Eingabewert muss sich mindestens um diesen Betrag ändern, bevor
     * eine neue Umrechnng erfolgt. Beruhigt den Wert.
     */
    MyPoti(unsigned int pin, int outMin, int outMax, unsigned int minThreshhold = 1);
    /**
     * Erstmaliges Einlesen des aktuellen Werts.
     */
    void init();
    /**
     * Liest aktuellen Wert ein und rechnet ggf. neu auf den Ausgabebereich um.
     * Liefert true, wenn sch der Ausgabewert geändert hat.
     */
    bool read();
    unsigned int threshhold() const;
    /**
     * Hat sich der Ausgabewert beim letzten read() geändert?
     */
    bool hasChanged() const;
    /**
     * Ausgabewert abrufen.
     */
    int value() const;
private:
    /**
     * Bessere Mappingfunktion. Gleichmäßiger als das eingebaute map(),
     * insbesondere an den Randbereichen.
     */
    void doMapping();
    const unsigned int m_Pin;
    const int m_OutMin;
    const int m_OutMax;
    const float m_InStepSize;
    const unsigned int m_Threshhold;
    unsigned int m_InValue;
    int m_OutValue;
    bool m_HasChanged;
};

#endif
