#ifndef MY_BUTTON_H
#define MY_BUTTON_H

/**
 * Diese Klasse verwaltet einen Taster und vereinfacht die Erkennung von
 * Tastendrücken. Es findet keine Entprellung statt.
 */
class MyButton {
public:
    /**
     *Tasterobjekt anlegen, Angabe des Input-Pins. Nutzt internen PullUp.
     */
    MyButton(unsigned int pin);
    /**
     * Initialisierung, für setup()-Funktion.
     * Stellt den Eingangspin korrekt ein und liest einmalig den aktuellen
     * Tastenzustand ein. Dies wird aber nicht als Drücken oder Loslassen
     * gewertet, nur als Initialisierung.
     */
    void init();
    /**
     * Liest den aktuellen Tastenzustand ein und ermittelt, ob die Taste seit
     * dem letzten Aufruf gedrückt oder losgelassen wurde.
     * Rückgabewert: true, falls sich der Zustand der Taste geändert hat.
     */
    bool read();
    /**
     * Zeigt an, ob sich der Zustand der Taste geändert hat. Entspricht dem
     * Rückgabewert des letzten read().
     */
    bool hasChanged() const;
    /**
     * Ist die Taste gedrückt im Sinne von durchgeschaltet?
     */
    bool isDown() const;
    /**
     * Ist die Taste nicht gedrückt, d.h. sie ist hochohmig?
     */
    bool isUp() const;
    /**
     * Wurde die Taste gedrückt, d.h. ist sie durchgescaltet und es gab beim
     * letzten read() eine Zustandsänderung?
     */
    bool isPressed() const;
    /**
     * Wurde die Taste losgelassen, d.h. ist sie hochohmig und es gab beim
     * letzten read() eine Zustandsänderung?
     */
    bool isReleased() const;
private:
    const unsigned int m_Pin; // Pinnummer
    bool m_IsDown; // aktueller Tastenzustand
    bool m_HasChanged; // Zustandsänderung ja/nein  
};

#endif