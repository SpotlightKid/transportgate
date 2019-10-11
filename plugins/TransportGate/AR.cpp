//
//  AR.cpp
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
//  1.01  2016-01-02  njr   added calcCoef to SetTargetRatio functions that were in the ADSR widget but missing in this code
//  1.02  2017-01-04  njr   in calcCoef, checked for rate 0, to support non-IEEE compliant compilers
//  2.0   2019-10-11  Christopher Arndt   Converted to simpler AR envelope.

#include <math.h>

#include "AR.hpp"


AR::AR(void) {
    reset();
    setAttackRate(0);
    setReleaseRate(0);
    setTargetRatioA(0.3);
    setTargetRatioR(0.0001);
}

AR::~AR(void) {}

void AR::setAttackRate(float rate) {
    attackRate = rate;
    attackCoef = calcCoef(rate, targetRatioA);
    attackBase = (1.0 + targetRatioA) * (1.0 - attackCoef);
}

void AR::setReleaseRate(float rate) {
    releaseRate = rate;
    releaseCoef = calcCoef(rate, targetRatioR);
    releaseBase = -targetRatioR * (1.0 - releaseCoef);
}

float AR::calcCoef(float rate, float targetRatio) {
    return (rate <= 0) ? 0.0 : exp(-log((1.0 + targetRatio) / targetRatio) / rate);
}

void AR::setTargetRatioA(float targetRatio) {
    if (targetRatio < 0.000000001) {
        targetRatio = 0.000000001;  // -180 dB
    }

    targetRatioA = targetRatio;
    attackCoef = calcCoef(attackRate, targetRatioA);
    attackBase = (1.0 + targetRatioA) * (1.0 - attackCoef);
}

void AR::setTargetRatioR(float targetRatio) {
    if (targetRatio < 0.000000001) {
        targetRatio = 0.000000001;  // -180 dB
    }

    targetRatioR = targetRatio;
    releaseCoef = calcCoef(releaseRate, targetRatioR);
    releaseBase = -targetRatioR * (1.0 - releaseCoef);
}
