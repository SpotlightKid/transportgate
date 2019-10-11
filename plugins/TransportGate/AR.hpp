//
//  AR.hpp
//
//  Created by Nigel Redmon on 12/18/12.
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the ADSR envelope generator and code,
//  read the series of articles by the author, starting here:
//  http://www.earlevel.com/main/2013/06/01/envelope-generators/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code for your
//  own purposes, free or commercial.
//

#ifndef AR_H
#define AR_H


class AR {
public:
    AR(void);
    ~AR(void);
    float process(void);
    float getOutput(void);
    int getState(void);
    void gate(int on);
    void setAttackRate(float rate);
    void setReleaseRate(float rate);
    void setTargetRatioA(float targetRatio);
    void setTargetRatioR(float targetRatio);
    void reset(void);

    enum envState {
        ENV_IDLE = 0,
        ENV_ATTACK,
        ENV_SUSTAIN,
        ENV_RELEASE
    };

protected:
    int state;
    float output;
    float attackRate;
    float releaseRate;
    float attackCoef;
    float releaseCoef;
    float targetRatioA;
    float targetRatioR;
    float attackBase;
    float releaseBase;

    float calcCoef(float rate, float targetRatio);
};

inline float AR::process() {
    switch (state) {
        case ENV_IDLE:
            break;
        case ENV_ATTACK:
            output = attackBase + output * attackCoef;

            if (output >= 1.0) {
                output = 1.0;
                state = ENV_SUSTAIN;
            }

            break;
        case ENV_SUSTAIN:
            break;
        case ENV_RELEASE:
            output = releaseBase + output * releaseCoef;

            if (output <= 0.0) {
                output = 0.0;
                state = ENV_IDLE;
            }
    }
    return output;
}

inline void AR::gate(int gate) {
    if (gate) {
        state = ENV_ATTACK;
    }
    else if (state != ENV_IDLE) {
        state = ENV_RELEASE;
    }
}

inline int AR::getState() {
    return state;
}

inline void AR::reset() {
    state = ENV_IDLE;
    output = 0.0;
}

inline float AR::getOutput() {
    return output;
}

#endif  // ADSR_H
