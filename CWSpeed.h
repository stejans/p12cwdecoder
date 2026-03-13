#ifndef CW_SPEED_H
#define CW_SPEED_H

class CWSpeed {
public:
    CWSpeed(unsigned int cmp = 60, unsigned int minSpeed = 30, unsigned int maxSpeed = 200);
    bool setSpeed(unsigned int cpm);
    bool incSpeed();
    bool decSpeed();
    unsigned int cpm() const;
    unsigned int wpm() const;
    unsigned int dotDuration() const;
    unsigned int dashDuration() const;
    unsigned int letterPause() const;
    unsigned int wordPause() const;
private:
    const unsigned int m_MinSpeed;
    const unsigned int m_MaxSpeed;
    unsigned int m_cpm;
    unsigned int m_wpm;
    // Zeitparameter für CW in ms
    unsigned int m_DotDuration;
    unsigned int m_DashDuration;
    unsigned int m_LetterPause;
    unsigned int m_WordPause;
};

#endif