//
//  EnvelopeAR.hpp
//

#ifndef ENVELOPE_AR_H
#define ENVELOPE_AR_H


class EnvelopeAR {
public:
    EnvelopeAR(float sr);
    ~EnvelopeAR(void);
    float getOutput(void);
    float process(void);
    int getState(void);
    void gate(int on);
    void reset(void);
    void setAttackBase(float amp);
    void setAttackTime(float time);
    void setReleaseBase(float amp);
    void setReleaseTime(float time);
    void setSampleRate(float rate);

    enum envState {
        ENV_IDLE = 0,
        ENV_ATTACK,
        ENV_SUSTAIN,
        ENV_RELEASE
    };

protected:
    float attackBase;
    float attackCoef;
    float attackTime;
    float output;
    float releaseBase;
    float releaseCoef;
    float releaseTime;
    float sampleRate;
    int state;

    float calcCoef(float rate, float amp);
};

inline float EnvelopeAR::process() {
    switch (state) {
        case ENV_IDLE:
            break;
        case ENV_ATTACK:
            output = output + attackCoef;

            if (output >= 1.0) {
                output = 1.0;
                state = ENV_SUSTAIN;
            }

            break;
        case ENV_SUSTAIN:
            break;
        case ENV_RELEASE:
            output = output - releaseCoef;

            if (output <= releaseBase) {
                output = releaseBase;
                state = ENV_IDLE;
            }
    }
    return output;
}

inline void EnvelopeAR::gate(int gate) {
    if (gate) {
        state = ENV_ATTACK;
    }
    else if (state != ENV_IDLE) {
        state = ENV_RELEASE;
    }
}

inline int EnvelopeAR::getState() {
    return state;
}

inline void EnvelopeAR::reset() {
    state = ENV_IDLE;
    output = attackBase;
}

inline float EnvelopeAR::getOutput() {
    return output;
}

#endif  // ENVELOPE_AR_H
