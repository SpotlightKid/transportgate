//
//  EnvelopeAR.cpp
//

#include <math.h>

#include "EnvelopeAR.hpp"


EnvelopeAR::EnvelopeAR(float sr)
    : attackBase(0.0), releaseBase(0.0), sampleRate(sr)
{
    reset();
    setAttackTime(0.0);
    setReleaseTime(0.0);
}

EnvelopeAR::~EnvelopeAR(void) {}

void EnvelopeAR::setAttackTime(float time) {
    attackTime = time;
    attackCoef = calcCoef(time, attackBase);
}

void EnvelopeAR::setReleaseTime(float time) {
    releaseTime = time;
    releaseCoef = calcCoef(time, releaseBase);
}

void EnvelopeAR::setAttackBase(float amp) {
    attackBase = amp;
    attackCoef = calcCoef(attackTime, attackBase);

    if (state == ENV_IDLE) output = amp;
}

void EnvelopeAR::setReleaseBase(float amp) {
    releaseBase = amp;
    releaseCoef = calcCoef(releaseTime, releaseBase);

    if (state == ENV_IDLE) output = amp;
}

void EnvelopeAR::setSampleRate(float rate) {
    sampleRate = rate;
    attackCoef = calcCoef(attackTime, attackBase);
    releaseCoef = calcCoef(releaseTime, releaseBase);
}

float EnvelopeAR::calcCoef(float time, float amp) {
    return (1 - amp) / (time * sampleRate);
}
